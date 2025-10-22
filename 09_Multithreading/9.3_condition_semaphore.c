/*
 * 第九章：多线程编程
 * 9.3 条件变量与信号量
 * 
 * 学习目标：
 * 1. 掌握条件变量的使用
 * 2. 理解信号量的原理
 * 3. 学习生产者-消费者模式
 * 4. 掌握线程间协调机制
 * 
 * 编译命令：gcc 9.3_condition_semaphore.c -pthread -o 9.3
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>

// ============ 条件变量示例 ============

// 缓冲区
#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int buffer_count = 0;
int head = 0, tail = 0;

pthread_mutex_t buffer_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buffer_not_empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_not_full = PTHREAD_COND_INITIALIZER;

// 1. 生产者（使用条件变量）
void *producer_with_condition(void *arg) {
    int producer_id = *(int*)arg;
    
    for (int i = 0; i < 3; i++) {
        int item = producer_id * 10 + i;
        
        pthread_mutex_lock(&buffer_mutex);
        
        // 等待缓冲区不满
        while (buffer_count >= BUFFER_SIZE) {
            printf("[生产者%d] 缓冲区满，等待消费者...\n", producer_id);
            pthread_cond_wait(&buffer_not_full, &buffer_mutex);
        }
        
        // 生产
        buffer[tail] = item;
        tail = (tail + 1) % BUFFER_SIZE;
        buffer_count++;
        
        printf("[生产者%d] 生产了 %d (缓冲区: %d/%d)\n", 
               producer_id, item, buffer_count, BUFFER_SIZE);
        
        // 唤醒等待消费的消费者
        pthread_cond_signal(&buffer_not_empty);
        
        pthread_mutex_unlock(&buffer_mutex);
        
        sleep(1);
    }
    
    free(arg);
    return NULL;
}

// 2. 消费者（使用条件变量）
void *consumer_with_condition(void *arg) {
    int consumer_id = *(int*)arg;
    
    for (int i = 0; i < 3; i++) {
        pthread_mutex_lock(&buffer_mutex);
        
        // 等待缓冲区不空
        while (buffer_count <= 0) {
            printf("[消费者%d] 缓冲区空，等待生产者...\n", consumer_id);
            pthread_cond_wait(&buffer_not_empty, &buffer_mutex);
        }
        
        // 消费
        int item = buffer[head];
        head = (head + 1) % BUFFER_SIZE;
        buffer_count--;
        
        printf("[消费者%d] 消费了 %d (缓冲区: %d/%d)\n", 
               consumer_id, item, buffer_count, BUFFER_SIZE);
        
        // 唤醒等待生产的生产者
        pthread_cond_signal(&buffer_not_full);
        
        pthread_mutex_unlock(&buffer_mutex);
        
        sleep(1);
    }
    
    free(arg);
    return NULL;
}

// ============ 信号量示例 ============

#define POOL_SIZE 3
int resource_count = POOL_SIZE;
sem_t resource_sem;

// 3. 资源池生产者（使用信号量）
void *producer_with_semaphore(void *arg) {
    int producer_id = *(int*)arg;
    
    for (int i = 0; i < 2; i++) {
        // 检查资源
        int available;
        sem_getvalue(&resource_sem, &available);
        printf("[生产者%d] 可用资源: %d\n", producer_id, available);
        
        sleep(1);
    }
    
    free(arg);
    return NULL;
}

// 4. 资源池消费者（使用信号量）
void *consumer_with_semaphore(void *arg) {
    int consumer_id = *(int*)arg;
    
    printf("[消费者%d] 等待资源...\n", consumer_id);
    sem_wait(&resource_sem);
    
    printf("[消费者%d] 获得资源，开始工作\n", consumer_id);
    sleep(3);
    
    printf("[消费者%d] 工作完成，释放资源\n", consumer_id);
    sem_post(&resource_sem);
    
    free(arg);
    return NULL;
}

// ============ 条件变量高级用法 ============

pthread_mutex_t state_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t state_changed = PTHREAD_COND_INITIALIZER;
int state = 0;

// 5. 等待状态改变
void *waiter_thread(void *arg) {
    int waiter_id = *(int*)arg;
    
    pthread_mutex_lock(&state_mutex);
    
    printf("[等待线程%d] 等待状态改变...\n", waiter_id);
    
    // 等待条件
    while (state != 1) {
        pthread_cond_wait(&state_changed, &state_mutex);
    }
    
    printf("[等待线程%d] 状态已改变为: %d\n", waiter_id, state);
    
    pthread_mutex_unlock(&state_mutex);
    
    free(arg);
    return NULL;
}

// 6. 改变状态的线程
void *changer_thread(void *arg) {
    sleep(2);
    
    pthread_mutex_lock(&state_mutex);
    
    state = 1;
    printf("[改变线程] 改变状态为: %d\n", state);
    
    // 唤醒所有等待者
    pthread_cond_broadcast(&state_changed);
    printf("[改变线程] 已广播状态改变\n");
    
    pthread_mutex_unlock(&state_mutex);
    
    return NULL;
}

// ============ 超时等待 ============

#include <time.h>

void *timeout_waiter(void *arg) {
    int waiter_id = *(int*)arg;
    
    pthread_mutex_lock(&state_mutex);
    
    struct timespec timeout;
    clock_gettime(CLOCK_REALTIME, &timeout);
    timeout.tv_sec += 3;  // 3秒超时
    
    printf("[超时等待%d] 开始等待3秒...\n", waiter_id);
    
    int ret = pthread_cond_timedwait(&state_changed, &state_mutex, &timeout);
    
    if (ret == 0) {
        printf("[超时等待%d] 条件满足，状态: %d\n", waiter_id, state);
    } else if (ret == ETIMEDOUT) {
        printf("[超时等待%d] 等待超时！\n", waiter_id);
    } else {
        printf("[超时等待%d] 错误: %d\n", waiter_id, ret);
    }
    
    pthread_mutex_unlock(&state_mutex);
    
    free(arg);
    return NULL;
}

// ============ 主函数 ============

int main() {
    printf("=== C语言条件变量与信号量 ===\n\n");
    
    // 示例1：条件变量 - 生产者消费者
    printf("示例1: 条件变量 - 生产者消费者模式\n");
    printf("================================\n");
    
    buffer_count = 0;
    head = tail = 0;
    
    pthread_t producers[2], consumers[2];
    
    // 创建生产者
    for (int i = 0; i < 2; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&producers[i], NULL, producer_with_condition, id);
    }
    
    // 创建消费者
    for (int i = 0; i < 2; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&consumers[i], NULL, consumer_with_condition, id);
    }
    
    // 等待所有线程完成
    for (int i = 0; i < 2; i++) {
        pthread_join(producers[i], NULL);
        pthread_join(consumers[i], NULL);
    }
    
    printf("[主线程] 生产者消费者完成\n\n");
    
    // 示例2：信号量 - 资源池
    printf("示例2: 信号量 - 资源池管理\n");
    printf("================================\n");
    
    sem_init(&resource_sem, 0, POOL_SIZE);
    printf("[主线程] 初始化信号量: %d个资源\n", POOL_SIZE);
    
    pthread_t sem_consumers[5];
    
    // 创建消费者
    for (int i = 0; i < 5; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&sem_consumers[i], NULL, consumer_with_semaphore, id);
    }
    
    // 等待所有消费者完成
    for (int i = 0; i < 5; i++) {
        pthread_join(sem_consumers[i], NULL);
    }
    
    sem_destroy(&resource_sem);
    printf("[主线程] 信号量示例完成\n\n");
    
    // 示例3：条件变量 - 等待状态改变
    printf("示例3: 条件变量 - 状态改变通知\n");
    printf("================================\n");
    
    state = 0;
    pthread_t waiters[3], changer;
    
    // 创建等待线程
    for (int i = 0; i < 3; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&waiters[i], NULL, waiter_thread, id);
    }
    
    sleep(1);  // 让等待线程先启动
    
    // 创建改变线程
    pthread_create(&changer, NULL, changer_thread, NULL);
    
    // 等待所有线程完成
    for (int i = 0; i < 3; i++) {
        pthread_join(waiters[i], NULL);
    }
    pthread_join(changer, NULL);
    
    printf("[主线程] 状态改变通知完成\n\n");
    
    // 示例4：超时等待
    printf("示例4: 条件变量 - 超时等待\n");
    printf("================================\n");
    
    state = 0;
    pthread_t timeout_waiter_thread;
    
    int waiter_id = 1;
    pthread_create(&timeout_waiter_thread, NULL, timeout_waiter, &waiter_id);
    
    sleep(5);  // 不改变状态，让等待超时
    
    pthread_join(timeout_waiter_thread, NULL);
    printf("[主线程] 超时等待完成\n\n");
    
    // 示例5：pthread_cond_signal vs broadcast
    printf("示例5: signal vs broadcast\n");
    printf("================================\n");
    printf("[主线程] pthread_cond_signal:   唤醒一个等待线程\n");
    printf("[主线程] pthread_cond_broadcast: 唤醒所有等待线程\n\n");
    
    // 示例6：信号量与互斥锁
    printf("示例6: 信号量与互斥锁的区别\n");
    printf("================================\n");
    printf("[主线程] 互斥锁 (Mutex):\n");
    printf("  - 二值信号量（0或1）\n");
    printf("  - 只有持有者可释放\n");
    printf("  - 用于保护临界区\n");
    printf("  - 有所有权概念\n\n");
    
    printf("[主线程] 信号量 (Semaphore):\n");
    printf("  - 计数器（0或正整数）\n");
    printf("  - 任何线程可减少\n");
    printf("  - 用于资源计数\n");
    printf("  - 无所有权\n\n");
    
    // 示例7：条件变量使用模式
    printf("示例7: 条件变量典型用法\n");
    printf("================================\n");
    printf("[主线程] 典型模式:\n");
    printf("  pthread_mutex_lock(&mutex);\n");
    printf("  while (!condition) {\n");
    printf("    pthread_cond_wait(&cond, &mutex);\n");
    printf("  }\n");
    printf("  // 执行操作\n");
    printf("  pthread_mutex_unlock(&mutex);\n\n");
    
    // 清理
    pthread_cond_destroy(&buffer_not_empty);
    pthread_cond_destroy(&buffer_not_full);
    pthread_mutex_destroy(&buffer_mutex);
    pthread_cond_destroy(&state_changed);
    pthread_mutex_destroy(&state_mutex);
    
    printf("=== 条件变量与信号量示例完成 ===\n");
    
    return 0;
}

/*
 * 知识点总结：
 * 
 * 条件变量 (Condition Variable)：
 * 
 * 定义：
 * pthread_cond_t
 * 
 * 初始化：
 * 方式1 - 动态初始化：
 *   pthread_cond_t cond;
 *   pthread_cond_init(&cond, NULL);
 * 
 * 方式2 - 静态初始化：
 *   pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
 * 
 * 常用函数：
 * 
 * pthread_cond_wait(cond, mutex):
 * - 原子地释放互斥锁并等待条件
 * - 被唤醒时自动重新获取互斥锁
 * - 必须在互斥锁保护下调用
 * - 通常在 while 循环中（防止虚假唤醒）
 * 
 * pthread_cond_signal(cond):
 * - 唤醒一个等待条件的线程
 * - 未定义唤醒哪个线程
 * - 更高效（开销小）
 * 
 * pthread_cond_broadcast(cond):
 * - 唤醒所有等待条件的线程
 * - 所有线程都被唤醒
 * - 开销较大
 * 
 * pthread_cond_timedwait(cond, mutex, timeout):
 * - 带超时的等待
 * - 超时后返回 ETIMEDOUT
 * - 用于避免无限等待
 * 
 * pthread_cond_destroy(cond):
 * - 销毁条件变量
 * - 动态初始化后调用
 * 
 * 使用模式：
 * 
 * 等待方 (Consumer):
 * pthread_mutex_lock(&mutex);
 * while (condition_not_met) {
 *     pthread_cond_wait(&cond, &mutex);
 * }
 * // 执行操作
 * pthread_mutex_unlock(&mutex);
 * 
 * 通知方 (Producer):
 * pthread_mutex_lock(&mutex);
 * // 改变条件
 * condition = true;
 * pthread_cond_signal(&cond);  // 或 broadcast
 * pthread_mutex_unlock(&mutex);
 * 
 * 虚假唤醒 (Spurious Wakeup)：
 * - 线程可能在未被显式唤醒时醒来
 * - 必须在 while 循环中检查条件
 * - 不能使用 if 语句
 * 
 * 信号量 (Semaphore)：
 * 
 * 定义：
 * sem_t
 * 
 * 初始化：
 * sem_init(&sem, pshared, initial_value);
 * - pshared: 0 = 线程间，1 = 进程间
 * - initial_value: 初始计数值
 * 
 * 常用函数：
 * 
 * sem_wait(sem):
 * - 原子性递减计数
 * - 计数为0则阻塞
 * - 类似 "获取资源"
 * 
 * sem_post(sem):
 * - 原子性递增计数
 * - 可唤醒等待线程
 * - 类似 "释放资源"
 * 
 * sem_trywait(sem):
 * - 非阻塞递减
 * - 成功返回0
 * - 失败返回-1
 * 
 * sem_getvalue(sem, sval):
 * - 获取当前计数值
 * - 用于调试
 * 
 * sem_destroy(sem):
 * - 销毁信号量
 * 
 * 信号量分类：
 * 
 * 二值信号量：
 * - 计数为 0 或 1
 * - 等价于互斥锁
 * 
 * 计数信号量：
 * - 计数可为任意非负整数
 * - 用于管理资源池
 * 
 * 互斥锁 vs 信号量：
 * 
 * 互斥锁：
 * - 保护临界区
 * - 防止数据竞争
 * - 所有权概念（只有持有者能释放）
 * 
 * 信号量：
 * - 控制资源访问
 * - 管理资源计数
 * - 无所有权（任何线程都能释放）
 * 
 * 条件变量 vs 忙轮询：
 * 
 * 忙轮询（低效）：
 * while (condition) {
 *     sleep(1);
 * }
 * 
 * 条件变量（高效）：
 * pthread_cond_wait(&cond, &mutex);
 * 
 * 条件变量适用场景：
 * - 生产者-消费者
 * - 线程池
 * - 等待特定事件
 * - 任务队列
 * 
 * 信号量适用场景：
 * - 资源池管理
 * - 限制并发数
 * - 进程间同步
 * - 进度控制
 * 
 * 最佳实践：
 * 
 * 1. 条件变量始终在循环中检查：
 *    while (!condition) {
 *        pthread_cond_wait(&cond, &mutex);
 *    }
 * 
 * 2. 信号量用于计数：
 *    sem_wait() 对应 sem_post()
 * 
 * 3. 选择 signal 还是 broadcast：
 *    - 一对一：signal
 *    - 一对多：broadcast
 * 
 * 4. 注意临界区大小：
 *    pthread_cond_wait 会自动释放互斥锁
 *    重新获取时要检查条件
 * 
 * 5. 使用超时避免死锁：
 *    struct timespec timeout;
 *    pthread_cond_timedwait(&cond, &mutex, &timeout);
 * 
 * 常见错误：
 * 
 * 1. 不在互斥锁保护下调用 wait：
 *    pthread_cond_wait(&cond, NULL);  // 错误！
 * 
 * 2. 在 if 中检查条件（应用 while）：
 *    if (!ready) {
 *        pthread_cond_wait(&cond, &mutex);  // 错误！
 *    }
 * 
 * 3. 忘记唤醒：
 *    // 改变条件但不唤醒
 *    ready = true;
 *    // 忘记 pthread_cond_signal
 * 
 * 4. signal 用于广播场景：
 *    // 多个等待者，应该用 broadcast
 *    pthread_cond_signal(&cond);  // 可能不够
 * 
 * 5. 不初始化信号量：
 *    sem_wait(&sem);  // 错误！sem 未初始化
 * 
 * 调试提示：
 * - 条件变量问题通常表现为死锁
 * - 使用 gdb 的 info threads 检查线程状态
 * - 添加调试输出跟踪等待/唤醒
 * - 使用 valgrind 检查同步问题
 */
