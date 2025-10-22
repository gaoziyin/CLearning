/*
 * 第九章：多线程编程
 * 9.5 线程池与实战应用
 * 
 * 学习目标：
 * 1. 理解线程池设计
 * 2. 掌握任务队列实现
 * 3. 学习工作线程模式
 * 4. 综合应用多线程知识
 * 
 * 编译命令：gcc 9.5_thread_pool.c -pthread -o 9.5
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

// ============ 简单任务队列 ============

#define TASK_QUEUE_SIZE 100
#define NUM_WORKER_THREADS 4

typedef void (*task_func)(void *);

typedef struct {
    task_func func;
    void *arg;
} Task;

typedef struct {
    Task tasks[TASK_QUEUE_SIZE];
    int front, rear, count;
    pthread_mutex_t mutex;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
    int shutdown;
} TaskQueue;

TaskQueue *queue = NULL;

// 初始化任务队列
TaskQueue *queue_create() {
    TaskQueue *q = (TaskQueue *)malloc(sizeof(TaskQueue));
    if (q) {
        q->front = q->rear = q->count = 0;
        q->shutdown = 0;
        pthread_mutex_init(&q->mutex, NULL);
        pthread_cond_init(&q->not_empty, NULL);
        pthread_cond_init(&q->not_full, NULL);
    }
    return q;
}

// 添加任务到队列
int queue_enqueue(TaskQueue *q, task_func func, void *arg) {
    if (!q) return -1;
    
    pthread_mutex_lock(&q->mutex);
    
    // 等待队列有空间
    while (q->count >= TASK_QUEUE_SIZE && !q->shutdown) {
        pthread_cond_wait(&q->not_full, &q->mutex);
    }
    
    if (q->shutdown) {
        pthread_mutex_unlock(&q->mutex);
        return -1;
    }
    
    // 添加任务
    q->tasks[q->rear].func = func;
    q->tasks[q->rear].arg = arg;
    q->rear = (q->rear + 1) % TASK_QUEUE_SIZE;
    q->count++;
    
    // 通知等待的工作线程
    pthread_cond_signal(&q->not_empty);
    
    pthread_mutex_unlock(&q->mutex);
    return 0;
}

// 从队列取出任务
int queue_dequeue(TaskQueue *q, Task *task) {
    if (!q || !task) return -1;
    
    pthread_mutex_lock(&q->mutex);
    
    // 等待队列非空或关闭
    while (q->count == 0 && !q->shutdown) {
        pthread_cond_wait(&q->not_empty, &q->mutex);
    }
    
    if (q->count == 0) {
        pthread_mutex_unlock(&q->mutex);
        return -1;
    }
    
    // 取出任务
    *task = q->tasks[q->front];
    q->front = (q->front + 1) % TASK_QUEUE_SIZE;
    q->count--;
    
    // 通知等待的生产者
    pthread_cond_signal(&q->not_full);
    
    pthread_mutex_unlock(&q->mutex);
    return 0;
}

// 关闭队列
void queue_shutdown(TaskQueue *q) {
    if (!q) return;
    
    pthread_mutex_lock(&q->mutex);
    q->shutdown = 1;
    pthread_cond_broadcast(&q->not_empty);
    pthread_mutex_unlock(&q->mutex);
}

// 销毁队列
void queue_destroy(TaskQueue *q) {
    if (!q) return;
    
    pthread_mutex_destroy(&q->mutex);
    pthread_cond_destroy(&q->not_empty);
    pthread_cond_destroy(&q->not_full);
    free(q);
}

// ============ 工作线程 ============

void *worker_thread(void *arg) {
    int worker_id = *(int*)arg;
    Task task;
    
    printf("[工作线程%d] 启动\n", worker_id);
    
    while (1) {
        // 从队列取任务
        if (queue_dequeue(queue, &task) != 0) {
            // 队列已关闭
            break;
        }
        
        printf("[工作线程%d] 执行任务\n", worker_id);
        
        // 执行任务
        if (task.func) {
            task.func(task.arg);
        }
        
        printf("[工作线程%d] 任务完成\n", worker_id);
    }
    
    printf("[工作线程%d] 退出\n", worker_id);
    free(arg);
    return NULL;
}

// ============ 任务函数 ============

void task_compute(void *arg) {
    int *task_id = (int*)arg;
    printf("  [任务%d] 执行计算\n", *task_id);
    sleep(1);
    printf("  [任务%d] 计算完成\n", *task_id);
    free(task_id);
}

void task_io(void *arg) {
    int *task_id = (int*)arg;
    printf("  [任务%d] 执行IO操作\n", *task_id);
    sleep(2);
    printf("  [任务%d] IO完成\n", *task_id);
    free(task_id);
}

void task_process_data(void *arg) {
    typedef struct {
        int task_id;
        int data;
    } TaskData;
    
    TaskData *data = (TaskData*)arg;
    printf("  [任务%d] 处理数据: %d\n", data->task_id, data->data);
    sleep(1);
    printf("  [任务%d] 数据处理完成\n", data->task_id);
    free(data);
}

// ============ 统计信息 ============

typedef struct {
    int total_tasks;
    int completed_tasks;
    int failed_tasks;
    pthread_mutex_t mutex;
} Statistics;

Statistics stats = {0, 0, 0, PTHREAD_MUTEX_INITIALIZER};

void update_stats(int success) {
    pthread_mutex_lock(&stats.mutex);
    if (success) {
        stats.completed_tasks++;
    } else {
        stats.failed_tasks++;
    }
    pthread_mutex_unlock(&stats.mutex);
}

// ============ 主函数 ============

int main() {
    printf("=== C语言线程池与实战应用 ===\n\n");
    
    // 示例1：基本线程池
    printf("示例1: 基本线程池\n");
    printf("================================\n");
    
    // 创建队列
    queue = queue_create();
    if (!queue) {
        fprintf(stderr, "队列创建失败\n");
        return 1;
    }
    printf("[主线程] 队列已创建\n");
    
    // 创建工作线程
    pthread_t workers[NUM_WORKER_THREADS];
    printf("[主线程] 创建 %d 个工作线程\n", NUM_WORKER_THREADS);
    
    for (int i = 0; i < NUM_WORKER_THREADS; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&workers[i], NULL, worker_thread, id);
    }
    
    sleep(1);
    
    // 添加任务
    printf("[主线程] 添加任务\n");
    stats.total_tasks = 8;
    
    for (int i = 0; i < 4; i++) {
        int *task_id = malloc(sizeof(int));
        *task_id = i + 1;
        queue_enqueue(queue, task_compute, task_id);
        printf("[主线程] 添加计算任务 %d\n", i + 1);
    }
    
    for (int i = 0; i < 4; i++) {
        int *task_id = malloc(sizeof(int));
        *task_id = i + 5;
        queue_enqueue(queue, task_io, task_id);
        printf("[主线程] 添加IO任务 %d\n", i + 5);
    }
    
    // 等待任务完成
    sleep(15);
    
    // 关闭线程池
    printf("[主线程] 关闭线程池\n");
    queue_shutdown(queue);
    
    // 等待工作线程完成
    for (int i = 0; i < NUM_WORKER_THREADS; i++) {
        pthread_join(workers[i], NULL);
    }
    
    printf("[主线程] 所有工作线程已退出\n\n");
    
    // 示例2：混合任务
    printf("示例2: 混合任务处理\n");
    printf("================================\n");
    
    // 重新创建队列和线程
    queue_destroy(queue);
    queue = queue_create();
    
    for (int i = 0; i < NUM_WORKER_THREADS; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&workers[i], NULL, worker_thread, id);
    }
    
    sleep(1);
    
    // 添加不同类型的任务
    printf("[主线程] 添加混合任务\n");
    
    for (int i = 0; i < 3; i++) {
        int *task_id = malloc(sizeof(int));
        *task_id = i + 1;
        queue_enqueue(queue, task_compute, task_id);
    }
    
    for (int i = 0; i < 3; i++) {
        typedef struct {
            int task_id;
            int data;
        } TaskData;
        
        TaskData *data = malloc(sizeof(TaskData));
        data->task_id = i + 4;
        data->data = (i + 1) * 100;
        queue_enqueue(queue, task_process_data, data);
    }
    
    // 等待完成
    sleep(10);
    
    queue_shutdown(queue);
    for (int i = 0; i < NUM_WORKER_THREADS; i++) {
        pthread_join(workers[i], NULL);
    }
    printf("[主线程] 混合任务处理完成\n\n");
    
    // 示例3：线程池设计模式
    printf("示例3: 线程池设计模式\n");
    printf("================================\n");
    printf("[主线程] 线程池设计特点:\n");
    printf("  1. 创建固定数量的工作线程\n");
    printf("  2. 任务存储在队列中\n");
    printf("  3. 工作线程从队列获取任务执行\n");
    printf("  4. 避免频繁创建销毁线程\n");
    printf("  5. 提高系统响应速度\n");
    printf("  6. 控制并发数量\n\n");
    
    // 示例4：线程池优势
    printf("示例4: 线程池优势\n");
    printf("================================\n");
    printf("[主线程] vs 直接创建线程:\n");
    printf("  + 避免线程创建销毁开销\n");
    printf("  + 自动控制并发数\n");
    printf("  + 更好的资源利用\n");
    printf("  + 响应时间更快\n");
    printf("  + 易于管理\n\n");
    
    // 示例5：应用场景
    printf("示例5: 应用场景\n");
    printf("================================\n");
    printf("[主线程] 适用场景:\n");
    printf("  - Web服务器（处理客户端请求）\n");
    printf("  - 数据库连接池（复用连接）\n");
    printf("  - 异步任务处理\n");
    printf("  - 并行计算\n");
    printf("  - 事件驱动系统\n");
    printf("  - 定时任务调度\n\n");
    
    // 示例6：扩展功能
    printf("示例6: 线程池扩展功能\n");
    printf("================================\n");
    printf("[主线程] 可添加功能:\n");
    printf("  - 优先级队列\n");
    printf("  - 动态线程数调整\n");
    printf("  - 任务超时处理\n");
    printf("  - 结果回调\n");
    printf("  - 任务取消\n");
    printf("  - 线程监控/统计\n");
    printf("  - 异常处理\n\n");
    
    // 示例7：性能考虑
    printf("示例7: 性能优化\n");
    printf("================================\n");
    printf("[主线程] 优化建议:\n");
    printf("  - 线程数 = CPU核数（计算密集）\n");
    printf("  - 线程数 > CPU核数（IO密集）\n");
    printf("  - 队列大小要合理\n");
    printf("  - 避免频繁上下文切换\n");
    printf("  - 监控队列长度\n");
    printf("  - 调整线程数进行优化\n\n");
    
    // 清理
    queue_destroy(queue);
    pthread_mutex_destroy(&stats.mutex);
    
    printf("=== 线程池示例完成 ===\n");
    
    return 0;
}

/*
 * 知识点总结：
 * 
 * 线程池 (Thread Pool)：
 * 
 * 定义：
 * 预先创建一定数量的工作线程，处理来自队列的任务
 * 
 * 核心组件：
 * 
 * 1. 任务队列 (Task Queue):
 *    - 存储待处理的任务
 *    - 通常是线程安全的队列
 *    - 使用互斥锁和条件变量保护
 * 
 * 2. 工作线程 (Worker Threads):
 *    - 从队列获取任务执行
 *    - 固定数量
 *    - 循环等待任务
 * 
 * 3. 任务函数 (Task Function):
 *    - 实际执行的工作
 *    - 可以是任何类型的工作
 *    - 完成后自动返回队列
 * 
 * 实现步骤：
 * 
 * 1. 创建任务队列
 *    - 定义队列数据结构
 *    - 初始化互斥锁和条件变量
 * 
 * 2. 创建工作线程
 *    - 启动固定数量的线程
 *    - 每个线程循环等待任务
 * 
 * 3. 提交任务
 *    - 将任务添加到队列
 *    - 通知等待的工作线程
 * 
 * 4. 执行任务
 *    - 工作线程获取任务
 *    - 执行任务函数
 *    - 返回结果（可选）
 * 
 * 5. 关闭线程池
 *    - 停止接收新任务
 *    - 等待现有任务完成
 *    - 关闭工作线程
 * 
 * 线程池大小选择：
 * 
 * CPU密集型：
 * threads = CPU_CORES
 * - 避免过多上下文切换
 * - 充分利用CPU
 * 
 * IO密集型：
 * threads = CPU_CORES * (1 + wait_ratio)
 * wait_ratio = IO等待时间 / 执行时间
 * - 例如：4核系统，等待占80%，则 4 * (1 + 4) = 20
 * 
 * 混合型：
 * threads = CPU_CORES + IO线程
 * - 分离计算和IO线程
 * 
 * 队列大小选择：
 * - 无界队列：简单但可能耗尽内存
 * - 有界队列：防止内存溢出，拒绝策略
 * - 建议：队列大小 = 1000 * 线程数（起点）
 * 
 * 任务提交方式：
 * 
 * 同步提交：
 * - 直接等待任务完成
 * - 阻塞调用线程
 * 
 * 异步提交：
 * - 提交后立即返回
 * - 使用Future/Promise获取结果
 * 
 * 队列满的处理策略：
 * 
 * 1. 阻塞 (Block):
 *    - 调用线程等待队列有空间
 *    - 实现简单
 * 
 * 2. 拒绝 (Reject):
 *    - 立即拒绝新任务
 *    - 快速失败
 * 
 * 3. 丢弃 (Discard):
 *    - 丢弃最旧或最新的任务
 *    - 风险较大
 * 
 * 4. 调用者运行 (Caller-Runs):
 *    - 调用线程自己执行任务
 *    - 避免队列溢出
 * 
 * 线程池的优势：
 * 
 * 性能：
 * + 避免频繁创建销毁线程
 * + 线程复用
 * + 更快的任务响应
 * 
 * 资源：
 * + 限制线程数量
 * + 防止资源耗尽
 * + 更好的内存管理
 * 
 * 管理：
 * + 集中控制并发
 * + 易于监控和统计
 * + 优雅的关闭
 * 
 * 应用场景：
 * 
 * Web服务器：
 * - 每个客户端请求分配工作线程
 * - 处理数百或数千连接
 * - 线程池控制并发
 * 
 * 数据库系统：
 * - 连接池复用数据库连接
 * - 查询线程池处理查询
 * - 后台任务线程池
 * 
 * 并行计算：
 * - 将大任务分解为小任务
 * - 线程池并行执行
 * - 收集结果
 * 
 * 定时任务：
 * - 调度线程池执行周期任务
 * - 避免任务堆积
 * 
 * 异步处理：
 * - 后台线程处理耗时操作
 * - 主线程继续处理
 * - 回调通知结果
 * 
 * 监控和统计：
 * 
 * 可以收集的指标：
 * - 总任务数
 * - 完成任务数
 * - 队列长度
 * - 活动线程数
 * - 平均响应时间
 * - 吞吐量
 * 
 * 最佳实践：
 * 
 * 1. 选择合理的线程数：
 *    - 根据负载类型调整
 *    - 进行性能测试
 * 
 * 2. 合理的队列大小：
 *    - 防止内存溢出
 *    - 适当的拒绝策略
 * 
 * 3. 任务函数独立性：
 *    - 避免任务间依赖
 *    - 异常处理
 *    - 资源清理
 * 
 * 4. 优雅关闭：
 *    - 停止新任务提交
 *    - 等待现有任务完成
 *    - 超时机制
 * 
 * 5. 监控告警：
 *    - 队列溢出告警
 *    - 响应时间监控
 *    - 线程异常检测
 * 
 * 6. 文档化：
 *    - 线程数配置
 *    - 队列大小
 *    - 拒绝策略
 * 
 * 常见问题：
 * 
 * Q: 线程数设多少？
 * A: 测试！一般从 CPU核数开始调整
 * 
 * Q: 队列满了怎么办？
 * A: 定义拒绝策略（阻塞/拒绝/调用者运行）
 * 
 * Q: 任务异常怎么处理？
 * A: 在工作线程中try-catch，记录日志
 * 
 * Q: 如何获取任务结果？
 * A: 使用Future或回调函数
 * 
 * Q: 如何动态调整线程数？
 * A: 监控队列，添加/删除线程
 * 
 * 扩展方向：
 * - 优先级任务队列
 * - 分布式线程池
 * - 动态线程数调整
 * - 任务超时处理
 * - 结果缓存
 * - 线程局部存储
 */
