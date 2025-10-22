/*
 * 第九章：多线程编程
 * 9.2 互斥锁与临界区
 * 
 * 学习目标：
 * 1. 理解竞态条件和数据竞争
 * 2. 掌握互斥锁的使用
 * 3. 学习临界区的保护
 * 4. 理解死锁问题
 * 
 * 编译命令：gcc 9.2_mutex.c -pthread -o 9.2
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

// 全局变量
int account_balance = 1000;  // 账户余额
pthread_mutex_t balance_mutex;  // 互斥锁

// 1. 不安全的转账（没有锁）
void *unsafe_transfer(void *arg) {
    int thread_id = *(int*)arg;
    int thread_amount = thread_id * 100;
    
    printf("[线程%d] 准备转账 %d 元\n", thread_id, thread_amount);
    
    // 模拟转账过程（3个步骤）
    int temp = account_balance;
    printf("[线程%d] 读取余额: %d\n", thread_id, temp);
    
    sleep(1);  // 模拟业务处理
    
    temp -= thread_amount;
    printf("[线程%d] 计算后: %d\n", thread_id, temp);
    
    sleep(1);  // 更多处理
    
    account_balance = temp;
    printf("[线程%d] 写回余额: %d\n", thread_id, account_balance);
    
    free(arg);
    return NULL;
}

// 2. 安全的转账（使用互斥锁）
void *safe_transfer(void *arg) {
    int thread_id = *(int*)arg;
    int thread_amount = thread_id * 100;
    
    printf("[线程%d] 准备转账 %d 元\n", thread_id, thread_amount);
    
    // 获取互斥锁
    pthread_mutex_lock(&balance_mutex);
    printf("[线程%d] 获得互斥锁\n", thread_id);
    
    // 临界区开始
    int temp = account_balance;
    printf("[线程%d] 读取余额: %d\n", thread_id, temp);
    
    sleep(1);  // 模拟业务处理
    
    temp -= thread_amount;
    printf("[线程%d] 计算后: %d\n", thread_id, temp);
    
    sleep(1);  // 更多处理
    
    account_balance = temp;
    printf("[线程%d] 写回余额: %d\n", thread_id, account_balance);
    // 临界区结束
    
    // 释放互斥锁
    pthread_mutex_unlock(&balance_mutex);
    printf("[线程%d] 释放互斥锁\n", thread_id);
    
    free(arg);
    return NULL;
}

// 3. 演示死锁
pthread_mutex_t lock1, lock2;

void *deadlock_thread1(void *arg) {
    printf("[线程1] 等待获取锁1...\n");
    pthread_mutex_lock(&lock1);
    printf("[线程1] 获得锁1\n");
    
    sleep(1);  // 给另一个线程机会
    
    printf("[线程1] 等待获取锁2...\n");
    pthread_mutex_lock(&lock2);  // 可能死锁这里
    printf("[线程1] 获得锁2\n");
    
    printf("[线程1] 获得两个锁，执行操作\n");
    sleep(1);
    
    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);
    printf("[线程1] 释放所有锁\n");
    
    return NULL;
}

void *deadlock_thread2(void *arg) {
    printf("[线程2] 等待获取锁2...\n");
    pthread_mutex_lock(&lock2);
    printf("[线程2] 获得锁2\n");
    
    sleep(1);  // 给另一个线程机会
    
    printf("[线程2] 等待获取锁1...\n");
    pthread_mutex_lock(&lock1);  // 可能死锁这里
    printf("[线程2] 获得锁1\n");
    
    printf("[线程2] 获得两个锁，执行操作\n");
    sleep(1);
    
    pthread_mutex_unlock(&lock1);
    pthread_mutex_unlock(&lock2);
    printf("[线程2] 释放所有锁\n");
    
    return NULL;
}

// 4. 避免死锁的版本
void *avoid_deadlock_thread1(void *arg) {
    printf("[避免死锁线程1] 按照固定顺序获取锁...\n");
    
    // 总是先获取编号小的锁
    pthread_mutex_lock(&lock1);
    printf("[避免死锁线程1] 获得锁1\n");
    
    sleep(1);
    
    pthread_mutex_lock(&lock2);
    printf("[避免死锁线程1] 获得锁2\n");
    
    printf("[避免死锁线程1] 执行操作\n");
    sleep(1);
    
    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);
    printf("[避免死锁线程1] 释放所有锁\n");
    
    return NULL;
}

void *avoid_deadlock_thread2(void *arg) {
    printf("[避免死锁线程2] 按照固定顺序获取锁...\n");
    
    // 也是先获取编号小的锁
    pthread_mutex_lock(&lock1);
    printf("[避免死锁线程2] 获得锁1\n");
    
    sleep(1);
    
    pthread_mutex_lock(&lock2);
    printf("[避免死锁线程2] 获得锁2\n");
    
    printf("[避免死锁线程2] 执行操作\n");
    sleep(1);
    
    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);
    printf("[避免死锁线程2] 释放所有锁\n");
    
    return NULL;
}

// 5. 非阻塞锁获取
void *trylock_thread(void *arg) {
    int thread_id = *(int*)arg;
    int retries = 0;
    
    printf("[线程%d] 尝试非阻塞获取锁...\n", thread_id);
    
    // 尝试获取锁，如果失败则重试
    while (pthread_mutex_trylock(&balance_mutex) != 0) {
        retries++;
        printf("[线程%d] 锁被占用，重试 #%d\n", thread_id, retries);
        usleep(100000);  // 等待100ms后重试
        
        if (retries > 10) {
            printf("[线程%d] 重试次数过多，放弃\n", thread_id);
            free(arg);
            return NULL;
        }
    }
    
    printf("[线程%d] 成功获得锁（耗时%d次重试）\n", thread_id, retries);
    sleep(1);
    pthread_mutex_unlock(&balance_mutex);
    printf("[线程%d] 释放锁\n", thread_id);
    
    free(arg);
    return NULL;
}

// 6. 锁的初始化方式
void *initialized_mutex_thread(void *arg) {
    printf("[线程] 演示互斥锁初始化\n");
    
    pthread_mutex_t local_mutex;
    
    // 方式1：动态初始化
    pthread_mutex_init(&local_mutex, NULL);
    printf("[线程] 互斥锁已初始化\n");
    
    pthread_mutex_lock(&local_mutex);
    printf("[线程] 获得了本地互斥锁\n");
    
    pthread_mutex_unlock(&local_mutex);
    
    pthread_mutex_destroy(&local_mutex);
    printf("[线程] 互斥锁已销毁\n");
    
    return NULL;
}

int main() {
    printf("=== C语言互斥锁与临界区 ===\n\n");
    
    // 示例1：不安全的数据共享
    printf("示例1: 不安全的多线程访问（竞态条件演示）\n");
    printf("================================\n");
    printf("[主线程] 账户初始余额: %d\n", account_balance);
    printf("[主线程] 创建2个线程，分别转账100和200...\n");
    
    pthread_t unsafe_threads[2];
    for (int i = 0; i < 2; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&unsafe_threads[i], NULL, unsafe_transfer, id);
    }
    
    for (int i = 0; i < 2; i++) {
        pthread_join(unsafe_threads[i], NULL);
    }
    
    printf("[主线程] 最终余额: %d (应该是 %d，但可能不对)\n", 
           account_balance, 1000 - 100 - 200);
    printf("[主线程] 注意: 由于竞态条件，结果不正确！\n\n");
    
    // 示例2：使用互斥锁保护
    printf("示例2: 使用互斥锁保护临界区\n");
    printf("================================\n");
    
    // 初始化互斥锁
    pthread_mutex_init(&balance_mutex, NULL);
    
    account_balance = 1000;
    printf("[主线程] 账户重置为: %d\n", account_balance);
    printf("[主线程] 创建2个线程，使用互斥锁保护...\n");
    
    pthread_t safe_threads[2];
    for (int i = 0; i < 2; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&safe_threads[i], NULL, safe_transfer, id);
    }
    
    for (int i = 0; i < 2; i++) {
        pthread_join(safe_threads[i], NULL);
    }
    
    printf("[主线程] 最终余额: %d (正确值)\n", account_balance);
    printf("\n");
    
    // 示例3：非阻塞锁获取
    printf("示例3: 非阻塞锁获取 (trylock)\n");
    printf("================================\n");
    pthread_mutex_lock(&balance_mutex);  // 主线程先获取锁
    
    pthread_t trylock_threads[2];
    for (int i = 0; i < 2; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&trylock_threads[i], NULL, trylock_thread, id);
    }
    
    sleep(2);  // 让子线程重试几次
    printf("[主线程] 释放互斥锁，让子线程继续...\n");
    pthread_mutex_unlock(&balance_mutex);
    
    for (int i = 0; i < 2; i++) {
        pthread_join(trylock_threads[i], NULL);
    }
    printf("\n");
    
    // 示例4：锁初始化方式
    printf("示例4: 互斥锁的初始化与销毁\n");
    printf("================================\n");
    pthread_t init_thread;
    pthread_create(&init_thread, NULL, initialized_mutex_thread, NULL);
    pthread_join(init_thread, NULL);
    printf("\n");
    
    // 示例5：演示死锁问题（注意：可能会卡住）
    printf("示例5: 死锁演示说明\n");
    printf("================================\n");
    printf("[主线程] 死锁示例会演示两个线程互相等待的情况\n");
    printf("[主线程] 线程1: 先获lock1，后需要lock2\n");
    printf("[主线程] 线程2: 先获lock2，后需要lock1\n");
    printf("[主线程] 结果: 两个线程都被阻塞 (已跳过实际演示)\n");
    printf("[主线程] 避免死锁: 所有线程按相同顺序获取锁\n\n");
    
    // 示例6：避免死锁的版本
    printf("示例6: 避免死锁的正确方式\n");
    printf("================================\n");
    pthread_mutex_init(&lock1, NULL);
    pthread_mutex_init(&lock2, NULL);
    
    pthread_t avoid_threads[2];
    pthread_create(&avoid_threads[0], NULL, avoid_deadlock_thread1, NULL);
    pthread_create(&avoid_threads[1], NULL, avoid_deadlock_thread2, NULL);
    
    pthread_join(avoid_threads[0], NULL);
    pthread_join(avoid_threads[1], NULL);
    printf("\n");
    
    // 清理资源
    pthread_mutex_destroy(&balance_mutex);
    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);
    
    printf("=== 互斥锁示例完成 ===\n");
    
    return 0;
}

/*
 * 知识点总结：
 * 
 * 竞态条件 (Race Condition)：
 * - 多个线程并发访问共享资源
 * - 执行顺序不确定
 * - 导致不可预测的结果
 * 
 * 临界区 (Critical Section)：
 * - 访问共享资源的代码段
 * - 一次只能有一个线程执行
 * - 需要同步机制保护
 * 
 * 互斥锁 (Mutex)：
 * 
 * 定义：
 * pthread_mutex_t
 * 
 * 初始化：
 * 方式1 - 动态初始化：
 *   pthread_mutex_t mutex;
 *   pthread_mutex_init(&mutex, NULL);
 * 
 * 方式2 - 静态初始化：
 *   pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
 * 
 * 常用函数：
 * 
 * pthread_mutex_lock():
 * - 获取互斥锁
 * - 如果锁已被占用，阻塞等待
 * - 线程获得锁后独占
 * 
 * pthread_mutex_unlock():
 * - 释放互斥锁
 * - 允许其他线程获取
 * - 必须由持有锁的线程调用
 * 
 * pthread_mutex_trylock():
 * - 非阻塞获取锁
 * - 成功返回0
 * - 失败返回EBUSY
 * - 适合避免死锁
 * 
 * pthread_mutex_destroy():
 * - 销毁互斥锁
 * - 只能销毁未被占用的锁
 * - 动态初始化后必须调用
 * 
 * 使用模式：
 * 
 * 基本模式：
 * pthread_mutex_lock(&mutex);
 * {
 *     // 临界区 - 只有一个线程执行
 *     shared_var++;
 * }
 * pthread_mutex_unlock(&mutex);
 * 
 * 死锁 (Deadlock)：
 * 
 * 定义：
 * - 两个或多个线程互相等待对方释放锁
 * - 导致程序永久阻塞
 * 
 * 死锁四个必要条件：
 * 1. 互斥 - 资源只能被一个线程使用
 * 2. 占有并等待 - 线程持有资源并等待其他资源
 * 3. 不可抢占 - 资源不能被强制取走
 * 4. 循环等待 - 形成线程->资源->线程的环
 * 
 * 典型死锁场景：
 * 线程A: lock(L1) -> 需要 lock(L2)
 * 线程B: lock(L2) -> 需要 lock(L1)
 * 
 * 避免死锁的方法：
 * 
 * 1. 锁排序（最可靠）：
 *    所有线程按相同顺序获取锁
 *    lock(L1) then lock(L2)
 *    禁止相反顺序
 * 
 * 2. 超时获取：
 *    pthread_mutex_timedlock(&mutex, &timeout)
 *    指定等待时间
 * 
 * 3. 非阻塞获取：
 *    pthread_mutex_trylock()
 *    失败则处理或重试
 * 
 * 4. 细粒度锁：
 *    减少互斥锁的粒度
 *    缩小临界区
 * 
 * 5. 单一锁原则：
 *    对一组资源使用单一锁
 *    避免多锁交互
 * 
 * 互斥锁属性：
 * 
 * PTHREAD_MUTEX_NORMAL:
 * - 默认行为
 * - 不检测死锁
 * - 快速
 * 
 * PTHREAD_MUTEX_ERRORCHECK:
 * - 检测错误
 * - 提供错误反馈
 * - 稍慢
 * 
 * PTHREAD_MUTEX_RECURSIVE:
 * - 同一线程可多次获取
 * - 必须多次释放
 * 
 * 最佳实践：
 * 
 * 1. 保持临界区最小：
 *    // 不好
 *    pthread_mutex_lock(&m);
 *    // 很多操作
 *    pthread_mutex_unlock(&m);
 *    
 *    // 更好
 *    prepare_data();
 *    pthread_mutex_lock(&m);
 *    update_shared();
 *    pthread_mutex_unlock(&m);
 *    process_result();
 * 
 * 2. 避免在临界区内进行耗时操作：
 *    // 不好 - 在锁内做I/O
 *    pthread_mutex_lock(&m);
 *    fwrite(...);  // I/O操作
 *    pthread_mutex_unlock(&m);
 * 
 * 3. 始终检查返回值：
 *    int ret = pthread_mutex_lock(&m);
 *    if (ret != 0) perror("lock failed");
 * 
 * 4. 使用 RAII 模式（C++）或手工清理：
 *    if (pthread_mutex_lock(&m) == 0) {
 *        // 执行
 *        pthread_mutex_unlock(&m);
 *    }
 * 
 * 5. 文档化锁的目的：
 *    pthread_mutex_t data_mutex;  // 保护 shared_data
 * 
 * 常见错误：
 * 
 * 1. 忘记初始化：
 *    pthread_mutex_t m;
 *    pthread_mutex_lock(&m);  // 错误！
 * 
 * 2. 忘记解锁：
 *    pthread_mutex_lock(&m);
 *    return;  // 忘记解锁
 * 
 * 3. 多次锁定：
 *    pthread_mutex_lock(&m);
 *    pthread_mutex_lock(&m);  // 死锁！
 * 
 * 4. 由不同线程解锁：
 *    // 线程1
 *    pthread_mutex_lock(&m);
 *    // 线程2
 *    pthread_mutex_unlock(&m);  // 错误！
 * 
 * 5. 销毁被占用的锁：
 *    pthread_mutex_lock(&m);
 *    pthread_mutex_destroy(&m);  // 错误！
 * 
 * 性能考虑：
 * - 互斥锁有获取/释放开销
 * - 竞争激烈时性能下降
 * - 临界区越小越好
 * - 考虑使用读写锁等高级机制
 */
