/*
 * 第九章：多线程编程
 * 9.4 读写锁与自旋锁
 * 
 * 学习目标：
 * 1. 掌握读写锁的使用
 * 2. 理解自旋锁的原理
 * 3. 学习不同锁的应用场景
 * 4. 理解性能优化
 * 
 * 编译命令：gcc 9.4_rwlock_spinlock.c -pthread -o 9.4
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

// ============ 读写锁示例 ============

// 数据库记录结构
typedef struct {
    int id;
    char name[64];
    int value;
} Record;

Record database[10];
int record_count = 0;

pthread_rwlock_t db_rwlock;

// 1. 多读者（读锁）
void *reader_thread(void *arg) {
    int reader_id = *(int*)arg;
    
    for (int i = 0; i < 3; i++) {
        // 获取读锁
        printf("[读线程%d] 申请读锁...\n", reader_id);
        pthread_rwlock_rdlock(&db_rwlock);
        
        printf("[读线程%d] 获得读锁，开始读取数据\n", reader_id);
        
        // 读取数据
        for (int j = 0; j < record_count; j++) {
            printf("[读线程%d] 读取记录 %d: %s = %d\n", 
                   reader_id, database[j].id, database[j].name, database[j].value);
        }
        
        sleep(1);
        
        // 释放读锁
        pthread_rwlock_unlock(&db_rwlock);
        printf("[读线程%d] 释放读锁\n", reader_id);
        
        usleep(500000);
    }
    
    free(arg);
    return NULL;
}

// 2. 单个写者（写锁）
void *writer_thread(void *arg) {
    int writer_id = *(int*)arg;
    
    for (int i = 0; i < 2; i++) {
        sleep(1);
        
        // 获取写锁
        printf("[写线程%d] 申请写锁...\n", writer_id);
        pthread_rwlock_wrlock(&db_rwlock);
        
        printf("[写线程%d] 获得写锁，开始写入数据\n", writer_id);
        
        // 写入数据
        if (record_count < 10) {
            Record r;
            r.id = writer_id * 100 + i;
            snprintf(r.name, sizeof(r.name), "Record-%d", r.id);
            r.value = rand() % 1000;
            
            database[record_count++] = r;
            printf("[写线程%d] 写入记录: %d, %s = %d\n", 
                   writer_id, r.id, r.name, r.value);
        }
        
        sleep(1);
        
        // 释放写锁
        pthread_rwlock_unlock(&db_rwlock);
        printf("[写线程%d] 释放写锁\n", writer_id);
    }
    
    free(arg);
    return NULL;
}

// ============ 自旋锁示例 ============

#ifdef __GLIBC__
#include <sys/spinlock.h>
#else
// 定义基本自旋锁（不同系统可能不支持）
typedef int pthread_spinlock_t;

// 简单的自旋锁实现
int my_spinlock = 0;

void my_spinlock_lock(int *lock) {
    while (__sync_lock_test_and_set(lock, 1)) {
        // 自旋
    }
}

void my_spinlock_unlock(int *lock) {
    __sync_lock_release(lock);
}
#endif

// 3. 使用自旋锁的计数器
int spin_counter = 0;
int my_spinlock = 0;

void *spinlock_increment(void *arg) {
    int thread_id = *(int*)arg;
    
    for (int i = 0; i < 100; i++) {
        // 获取自旋锁
        while (__sync_lock_test_and_set(&my_spinlock, 1)) {
            // 自旋等待
        }
        
        // 临界区
        spin_counter++;
        
        // 释放自旋锁
        __sync_lock_release(&my_spinlock);
    }
    
    free(arg);
    return NULL;
}

// ============ 锁性能比较 ============

// 普通互斥锁计数器
int mutex_counter = 0;
pthread_mutex_t mutex_lock = PTHREAD_MUTEX_INITIALIZER;

void *mutex_increment(void *arg) {
    int thread_id = *(int*)arg;
    
    for (int i = 0; i < 100; i++) {
        pthread_mutex_lock(&mutex_lock);
        mutex_counter++;
        pthread_mutex_unlock(&mutex_lock);
    }
    
    free(arg);
    return NULL;
}

// ============ 原子操作 ============

int atomic_counter = 0;

void *atomic_increment(void *arg) {
    int thread_id = *(int*)arg;
    
    for (int i = 0; i < 100; i++) {
        // 原子增加
        __sync_add_and_fetch(&atomic_counter, 1);
    }
    
    free(arg);
    return NULL;
}

// ============ 主函数 ============

int main() {
    printf("=== C语言读写锁与自旋锁 ===\n\n");
    
    // 示例1：读写锁 - 多读者单写者
    printf("示例1: 读写锁 - 多读者单写者\n");
    printf("================================\n");
    
    // 初始化数据库
    record_count = 2;
    Record init_records[] = {
        {1, "John", 100},
        {2, "Jane", 200}
    };
    memcpy(database, init_records, sizeof(init_records));
    
    pthread_rwlock_init(&db_rwlock, NULL);
    
    pthread_t readers[4], writers[2];
    
    // 创建读者
    for (int i = 0; i < 4; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&readers[i], NULL, reader_thread, id);
    }
    
    sleep(1);
    
    // 创建写者
    for (int i = 0; i < 2; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&writers[i], NULL, writer_thread, id);
    }
    
    // 等待所有线程完成
    for (int i = 0; i < 4; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }
    
    printf("[主线程] 最终数据库记录数: %d\n", record_count);
    pthread_rwlock_destroy(&db_rwlock);
    printf("\n");
    
    // 示例2：性能比较 - 自旋锁 vs 互斥锁 vs 原子操作
    printf("示例2: 锁性能比较\n");
    printf("================================\n");
    
    // 测试互斥锁
    printf("[主线程] 测试互斥锁性能...\n");
    mutex_counter = 0;
    pthread_t mutex_threads[4];
    
    clock_t start = clock();
    
    for (int i = 0; i < 4; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&mutex_threads[i], NULL, mutex_increment, id);
    }
    
    for (int i = 0; i < 4; i++) {
        pthread_join(mutex_threads[i], NULL);
    }
    
    clock_t end = clock();
    double mutex_time = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("[主线程] 互斥锁: 计数=%d, 耗时=%.4f秒\n", mutex_counter, mutex_time);
    printf("\n");
    
    // 测试自旋锁
    printf("[主线程] 测试自旋锁性能...\n");
    spin_counter = 0;
    pthread_t spinlock_threads[4];
    
    start = clock();
    
    for (int i = 0; i < 4; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&spinlock_threads[i], NULL, spinlock_increment, id);
    }
    
    for (int i = 0; i < 4; i++) {
        pthread_join(spinlock_threads[i], NULL);
    }
    
    end = clock();
    double spinlock_time = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("[主线程] 自旋锁: 计数=%d, 耗时=%.4f秒\n", spin_counter, spinlock_time);
    printf("\n");
    
    // 测试原子操作
    printf("[主线程] 测试原子操作性能...\n");
    atomic_counter = 0;
    pthread_t atomic_threads[4];
    
    start = clock();
    
    for (int i = 0; i < 4; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&atomic_threads[i], NULL, atomic_increment, id);
    }
    
    for (int i = 0; i < 4; i++) {
        pthread_join(atomic_threads[i], NULL);
    }
    
    end = clock();
    double atomic_time = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("[主线程] 原子操作: 计数=%d, 耗时=%.4f秒\n", atomic_counter, atomic_time);
    printf("\n");
    
    // 性能总结
    printf("示例3: 性能比较总结\n");
    printf("================================\n");
    printf("[主线程] 互斥锁耗时:   %.4f秒\n", mutex_time);
    printf("[主线程] 自旋锁耗时:   %.4f秒\n", spinlock_time);
    printf("[主线程] 原子操作耗时: %.4f秒\n", atomic_time);
    
    if (mutex_time < spinlock_time) {
        printf("[主线程] 互斥锁比自旋锁快 %.2f倍\n", spinlock_time / mutex_time);
    } else {
        printf("[主线程] 自旋锁比互斥锁快 %.2f倍\n", mutex_time / spinlock_time);
    }
    
    if (atomic_time < mutex_time) {
        printf("[主线程] 原子操作比互斥锁快 %.2f倍\n", mutex_time / atomic_time);
    }
    printf("\n");
    
    // 示例4：读写锁属性
    printf("示例4: 读写锁属性\n");
    printf("================================\n");
    printf("[主线程] 读写锁特性:\n");
    printf("  - 多个读者可以同时持有读锁\n");
    printf("  - 只有一个写者可以持有写锁\n");
    printf("  - 读和写互斥\n");
    printf("  - 写者优先级通常高于读者\n\n");
    
    // 示例5：自旋锁与互斥锁选择
    printf("示例5: 锁类型选择\n");
    printf("================================\n");
    printf("[主线程] 互斥锁 (Mutex):\n");
    printf("  - 获取失败时阻塞，自动睡眠\n");
    printf("  - 开销较大（上下文切换）\n");
    printf("  - 长期等待时性能好\n");
    printf("  - 适合：IO操作、长时间持有锁\n\n");
    
    printf("[主线程] 自旋锁 (Spinlock):\n");
    printf("  - 获取失败时持续自旋（忙等）\n");
    printf("  - CPU占用率高\n");
    printf("  - 短期等待时性能好\n");
    printf("  - 适合：超短临界区、多核系统\n\n");
    
    printf("[主线程] 读写锁 (RWLock):\n");
    printf("  - 允许多个读者并发\n");
    printf("  - 写者排他\n");
    printf("  - 读多写少时性能好\n");
    printf("  - 适合：缓存、配置数据、数据库\n\n");
    
    printf("[主线程] 原子操作 (Atomic):\n");
    printf("  - 不需要锁，硬件支持\n");
    printf("  - 最高性能\n");
    printf("  - 仅用于简单操作\n");
    printf("  - 适合：计数器、标志位\n\n");
    
    // 示例6：原子操作详解
    printf("示例6: 原子操作\n");
    printf("================================\n");
    printf("[主线程] GCC内置原子操作:\n");
    printf("  __sync_add_and_fetch()      - 原子增加\n");
    printf("  __sync_sub_and_fetch()      - 原子减少\n");
    printf("  __sync_lock_test_and_set()  - 测试并设置\n");
    printf("  __sync_lock_release()       - 释放\n");
    printf("  __sync_bool_compare_and_swap() - 比较交换\n");
    printf("  __sync_val_compare_and_swap()  - 比较交换返回值\n\n");
    
    // 示例7：读写锁应用场景
    printf("示例7: 读写锁应用场景\n");
    printf("================================\n");
    printf("[主线程] 适合读写锁的场景:\n");
    printf("  1. 缓存系统（大量查询，少量更新）\n");
    printf("  2. 配置管理（多个线程读配置，少数更新）\n");
    printf("  3. 数据库连接池（多连接读取）\n");
    printf("  4. 权限表（读多写少）\n\n");
    
    printf("=== 读写锁与自旋锁示例完成 ===\n");
    
    return 0;
}

/*
 * 知识点总结：
 * 
 * 读写锁 (Reader-Writer Lock)：
 * 
 * 定义：
 * pthread_rwlock_t
 * 
 * 初始化：
 * pthread_rwlock_init(&rwlock, NULL);
 * 或静态初始化：
 * pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;
 * 
 * 常用函数：
 * 
 * pthread_rwlock_rdlock(rwlock):
 * - 获取读锁
 * - 多个读者可同时持有
 * - 不能与写者同时
 * 
 * pthread_rwlock_wrlock(rwlock):
 * - 获取写锁
 * - 只有一个写者可持有
 * - 独占资源
 * 
 * pthread_rwlock_unlock(rwlock):
 * - 释放读锁或写锁
 * - 同一函数用于两种锁
 * 
 * pthread_rwlock_tryrdlock(rwlock):
 * - 非阻塞读锁获取
 * - 失败返回 EBUSY
 * 
 * pthread_rwlock_trywrlock(rwlock):
 * - 非阻塞写锁获取
 * - 失败返回 EBUSY
 * 
 * pthread_rwlock_destroy(rwlock):
 * - 销毁读写锁
 * 
 * 使用模式：
 * 
 * 读者：
 * pthread_rwlock_rdlock(&rwlock);
 * // 读取数据
 * pthread_rwlock_unlock(&rwlock);
 * 
 * 写者：
 * pthread_rwlock_wrlock(&rwlock);
 * // 修改数据
 * pthread_rwlock_unlock(&rwlock);
 * 
 * 特性：
 * - 多个读者并发
 * - 单个写者独占
 * - 读写互斥
 * - 通常写者优先
 * 
 * 自旋锁 (Spinlock)：
 * 
 * 定义：
 * pthread_spinlock_t (非所有系统都支持)
 * 或使用 GCC 原子操作模拟
 * 
 * 特点：
 * - 获取失败时不睡眠，持续自旋
 * - CPU占用率高
 * - 无法被中断
 * - 不适合长时间持有
 * 
 * 应用场景：
 * - 超短临界区（<1微秒）
 * - 多核系统
 * - 低延迟需求
 * 
 * 原子操作 (Atomic Operations)：
 * 
 * GCC 内置原子操作：
 * 
 * 增减操作：
 * __sync_add_and_fetch(&x, 1)
 * __sync_sub_and_fetch(&x, 1)
 * __sync_fetch_and_add(&x, 1)
 * __sync_fetch_and_sub(&x, 1)
 * 
 * 位操作：
 * __sync_or_and_fetch(&x, mask)
 * __sync_and_and_fetch(&x, mask)
 * __sync_xor_and_fetch(&x, mask)
 * 
 * 比较交换：
 * __sync_bool_compare_and_swap(ptr, oldval, newval)
 * __sync_val_compare_and_swap(ptr, oldval, newval)
 * 
 * 测试设置：
 * __sync_lock_test_and_set(&lock, 1)
 * __sync_lock_release(&lock)
 * 
 * 内存屏障：
 * __sync_synchronize()  - 全屏障
 * 
 * 锁的性能对比：
 * 
 * 速度排序（从快到慢）：
 * 1. 原子操作（无锁，硬件支持）
 * 2. 自旋锁（短等待时高效）
 * 3. 互斥锁（需要系统调用）
 * 
 * 权衡因素：
 * - 超短临界区：自旋锁或原子操作
 * - 中等临界区：互斥锁
 * - 长临界区：互斥锁
 * - 读多写少：读写锁
 * - IO密集：互斥锁
 * - CPU密集：自旋锁或原子操作
 * 
 * 何时使用各种锁：
 * 
 * 互斥锁 (Mutex)：
 * ✓ 保护复杂数据结构
 * ✓ 包含IO操作
 * ✓ 通用选择
 * ✗ 性能关键路径
 * 
 * 自旋锁 (Spinlock)：
 * ✓ 超短临界区
 * ✓ 多核系统
 * ✓ 实时系统
 * ✗ 单核系统
 * ✗ 包含IO操作
 * 
 * 读写锁 (RWLock)：
 * ✓ 读多写少
 * ✓ 缓存/配置
 * ✓ 并发读取
 * ✗ 读写均衡
 * ✗ 写入频繁
 * 
 * 原子操作 (Atomic)：
 * ✓ 简单计数
 * ✓ 标志位
 * ✓ 最高性能
 * ✗ 复杂数据结构
 * ✗ 条件判断
 * 
 * 最佳实践：
 * 
 * 1. 优先考虑锁：Atomic > RWLock > Spinlock > Mutex
 * 2. 根据场景调整：先用Mutex，性能瓶颈后优化
 * 3. 避免嵌套锁
 * 4. 保持临界区最小
 * 5. 文档化锁的目的
 * 6. 测试多线程场景
 * 7. 使用工具检测竞态条件
 * 
 * 常见错误：
 * 
 * 1. 自旋锁在单核系统上：
 *    资源浪费，永远无法获得
 * 
 * 2. 长时间持有自旋锁：
 *    CPU占用率爆炸
 * 
 * 3. 互斥锁用于超短操作：
 *    不必要的系统调用开销
 * 
 * 4. 读写锁用于读写均衡：
 *    不如互斥锁高效
 * 
 * 5. 混用不同锁类型：
 *    容易形成死锁
 * 
 * 调试建议：
 * - 使用 gdb 的 thread 命令监控线程
 * - 添加日志查看锁的获取/释放序列
 * - 使用 helgrind（valgrind 工具）检测数据竞争
 * - 性能分析工具：perf, callgrind
 */
