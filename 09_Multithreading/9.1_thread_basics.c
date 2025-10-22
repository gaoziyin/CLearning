/*
 * 第九章：多线程编程
 * 9.1 线程基础
 * 
 * 学习目标：
 * 1. 理解线程的概念和生命周期
 * 2. 掌握线程的创建和销毁
 * 3. 学习线程的基本操作（join/detach/exit）
 * 4. 理解线程与进程的区别
 * 
 * 编译命令（Linux/Mac）：gcc 9.1_thread_basics.c -pthread -o 9.1
 * 编译命令（Windows MinGW）：gcc 9.1_thread_basics.c -pthread -o 9.1.exe
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

// 1. 最简单的线程例子
void *simple_thread(void *arg) {
    printf("[线程] 简单线程运行，参数: %d\n", *(int*)arg);
    sleep(1);
    printf("[线程] 简单线程完成\n");
    return NULL;
}

// 2. 线程传递参数
void *thread_with_param(void *arg) {
    int *param = (int*)arg;
    printf("[线程%d] 开始执行，参数值: %d\n", *param, *param);
    for (int i = 0; i < 3; i++) {
        printf("[线程%d] 执行步骤 %d\n", *param, i+1);
        sleep(1);
    }
    printf("[线程%d] 执行完毕\n", *param);
    free(param);
    return NULL;
}

// 3. 线程返回值
void *thread_return_value(void *arg) {
    int *result = (int*)malloc(sizeof(int));
    *result = *(int*)arg * 2;
    printf("[线程] 计算 %d * 2 = %d\n", *(int*)arg, *result);
    pthread_exit((void*)(intptr_t)*result);
    return NULL;
}

// 4. 线程计数器示例
int global_counter = 0;

void *thread_counter(void *arg) {
    int thread_id = *(int*)arg;
    printf("[线程%d] 开始, 当前计数: %d\n", thread_id, global_counter);
    
    for (int i = 0; i < 5; i++) {
        global_counter++;
        printf("[线程%d] 递增计数: %d\n", thread_id, global_counter);
        sleep(1);
    }
    
    printf("[线程%d] 完成, 最终计数: %d\n", thread_id, global_counter);
    free(arg);
    return NULL;
}

// 5. 主函数演示各种线程操作
int main() {
    printf("=== C语言多线程基础 ===\n\n");
    
    // 示例1：创建单个线程
    printf("示例1: 创建单个线程\n");
    printf("================================\n");
    pthread_t thread1;
    int param1 = 42;
    
    if (pthread_create(&thread1, NULL, simple_thread, &param1) != 0) {
        perror("pthread_create");
        return 1;
    }
    printf("[主线程] 线程已创建\n");
    
    // 等待线程完成（join）
    pthread_join(thread1, NULL);
    printf("[主线程] 线程已结束\n\n");
    
    // 示例2：创建多个线程
    printf("示例2: 创建多个线程\n");
    printf("================================\n");
    pthread_t threads[3];
    
    for (int i = 0; i < 3; i++) {
        int *thread_param = (int*)malloc(sizeof(int));
        *thread_param = i + 1;
        
        if (pthread_create(&threads[i], NULL, thread_with_param, thread_param) != 0) {
            perror("pthread_create");
            return 1;
        }
        printf("[主线程] 创建线程 %d\n", i+1);
    }
    
    // 等待所有线程完成
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
        printf("[主线程] 线程 %d 已结束\n", i+1);
    }
    printf("\n");
    
    // 示例3：线程返回值
    printf("示例3: 获取线程返回值\n");
    printf("================================\n");
    pthread_t thread3;
    int input = 10;
    
    if (pthread_create(&thread3, NULL, thread_return_value, &input) != 0) {
        perror("pthread_create");
        return 1;
    }
    
    void *result;
    pthread_join(thread3, &result);
    printf("[主线程] 线程返回值: %ld\n\n", (long)result);
    
    // 示例4：线程分离（detach）
    printf("示例4: 线程分离 (detach)\n");
    printf("================================\n");
    pthread_t thread4;
    int detach_param = 100;
    
    if (pthread_create(&thread4, NULL, simple_thread, &detach_param) != 0) {
        perror("pthread_create");
        return 1;
    }
    
    // 分离线程（线程完成时自动释放资源，无需join）
    if (pthread_detach(thread4) != 0) {
        perror("pthread_detach");
        return 1;
    }
    printf("[主线程] 线程已分离（不需要join）\n");
    sleep(3);  // 等待分离的线程完成
    printf("[主线程] 分离线程应该已完成\n\n");
    
    // 示例5：获取当前线程ID
    printf("示例5: 线程ID\n");
    printf("================================\n");
    pthread_t main_thread = pthread_self();
    printf("[主线程] 主线程ID: %lu\n", (unsigned long)main_thread);
    
    pthread_t test_thread;
    int thread_id = 5;
    if (pthread_create(&test_thread, NULL, simple_thread, &thread_id) != 0) {
        perror("pthread_create");
        return 1;
    }
    printf("[主线程] 子线程ID: %lu\n", (unsigned long)test_thread);
    pthread_join(test_thread, NULL);
    printf("\n");
    
    // 示例6：线程安全问题演示
    printf("示例6: 线程不安全的计数器\n");
    printf("================================\n");
    pthread_t counter_threads[2];
    
    for (int i = 0; i < 2; i++) {
        int *id = (int*)malloc(sizeof(int));
        *id = i + 1;
        
        if (pthread_create(&counter_threads[i], NULL, thread_counter, id) != 0) {
            perror("pthread_create");
            return 1;
        }
    }
    
    // 等待计数线程完成
    for (int i = 0; i < 2; i++) {
        pthread_join(counter_threads[i], NULL);
    }
    printf("[主线程] 所有计数线程完成, 最终计数: %d\n", global_counter);
    printf("[主线程] 注意: 没有同步机制，结果可能不稳定\n\n");
    
    // 示例7：线程属性
    printf("示例7: 线程属性\n");
    printf("================================\n");
    pthread_attr_t attr;
    size_t stacksize;
    
    // 初始化线程属性
    pthread_attr_init(&attr);
    
    // 获取默认堆栈大小
    pthread_attr_getstacksize(&attr, &stacksize);
    printf("[主线程] 默认堆栈大小: %zu bytes\n", stacksize);
    
    // 设置堆栈大小为2MB
    pthread_attr_setstacksize(&attr, 2 * 1024 * 1024);
    printf("[主线程] 设置堆栈大小为: 2MB\n");
    
    // 销毁属性对象
    pthread_attr_destroy(&attr);
    printf("\n");
    
    // 示例8：线程取消
    printf("示例8: 线程取消演示\n");
    printf("================================\n");
    printf("[主线程] 本示例演示了线程的各种基本操作\n");
    printf("[主线程] 线程生命周期: 创建 -> 运行 -> 完成 -> 销毁\n");
    printf("[主线程] 关键操作: create(创建) -> join(等待) 或 detach(分离)\n\n");
    
    printf("=== 多线程基础示例完成 ===\n");
    
    return 0;
}

/*
 * 知识点总结：
 * 
 * 线程概念：
 * - 线程（Thread）是进程内的执行单位
 * - 同一进程的线程共享内存空间和文件描述符
 * - 每个线程有独立的栈、程序计数器、寄存器
 * - 创建线程比创建进程轻量
 * 
 * POSIX 线程库（pthread）：
 * - 标准线程库（Linux/Unix/Mac）
 * - Windows 需要 MinGW-pthreads 或使用 Windows API
 * - 编译时需链接 -pthread
 * 
 * 主要函数：
 * 
 * pthread_create():
 * int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
 *                    void *(*start_routine)(void *), void *arg);
 * - 创建新线程
 * - thread: 线程标识符
 * - attr: 线程属性（NULL 使用默认）
 * - start_routine: 线程函数
 * - arg: 传递给线程函数的参数
 * - 返回: 成功返回0，失败返回错误码
 * 
 * pthread_join():
 * int pthread_join(pthread_t thread, void **retval);
 * - 等待线程完成（阻塞）
 * - retval: 接收线程返回值
 * - 只能join未分离的线程
 * 
 * pthread_detach():
 * int pthread_detach(pthread_t thread);
 * - 分离线程
 * - 线程完成时自动释放资源
 * - 分离后不能 join
 * 
 * pthread_exit():
 * void pthread_exit(void *retval);
 * - 线程退出
 * - retval: 返回值（可由 pthread_join 获取）
 * - main 中调用会导致其他线程继续执行
 * 
 * pthread_self():
 * pthread_t pthread_self(void);
 * - 获取当前线程ID
 * 
 * 线程函数特点：
 * - 必须是 void* (*func)(void*) 签名
 * - 可返回 NULL 或通过 pthread_exit 返回值
 * - 自动调用一次即可
 * - 在线程结束时清理
 * 
 * 线程生命周期：
 * 1. 创建 (Create): pthread_create
 * 2. 就绪 (Ready): 等待调度
 * 3. 运行 (Running): 被调度执行
 * 4. 等待 (Wait): 等待事件/资源
 * 5. 完成 (Terminate): 线程函数返回或调用 pthread_exit
 * 
 * join vs detach：
 * 
 * join:
 * - 主线程等待子线程完成
 * - 子线程资源由主线程释放
 * - 可以获取子线程返回值
 * - 适合需要协调的场景
 * 
 * detach:
 * - 子线程完成时自动释放资源
 * - 主线程无需等待
 * - 无法获取返回值
 * - 适合独立任务
 * 
 * 线程属性 (pthread_attr_t)：
 * 
 * 初始化/销毁：
 * pthread_attr_init(attr)
 * pthread_attr_destroy(attr)
 * 
 * 常用属性：
 * pthread_attr_setdetachstate()  - 设置分离状态
 * pthread_attr_setstacksize()    - 设置堆栈大小
 * pthread_attr_setschedparam()   - 设置优先级
 * pthread_attr_setinheritsched() - 设置调度继承
 * 
 * 线程参数传递：
 * 
 * 方法1：传递地址
 * int *param = malloc(sizeof(int));
 * *param = 42;
 * pthread_create(&t, NULL, func, param);
 * 
 * 方法2：强转整数
 * pthread_create(&t, NULL, func, (void*)(intptr_t)42);
 * 
 * 方法3：传递结构体
 * struct MyStruct {int a; char b;};
 * struct MyStruct *ps = malloc(sizeof(*ps));
 * pthread_create(&t, NULL, func, ps);
 * 
 * 常见错误：
 * 
 * 1. 栈变量地址传递：
 *    int x = 5;
 *    pthread_create(&t, NULL, func, &x);  // 危险！x 可能被回收
 * 
 * 2. 忘记 free 分配的内存：
 *    int *p = malloc(sizeof(int));
 *    pthread_create(&t, NULL, func, p);  // 在 func 中需要 free
 * 
 * 3. join 后继续使用 thread ID：
 *    pthread_join(t, NULL);
 *    pthread_join(t, NULL);  // 错误！
 * 
 * 4. 未检查返回值：
 *    pthread_create(&t, NULL, func, arg);  // 应检查返回值
 * 
 * 5. 主线程过早退出：
 *    pthread_create(&t, NULL, func, NULL);
 *    return 0;  // 子线程可能未运行就进程结束
 * 
 * 实用建议：
 * 
 * 1. 使用 pthread_join 确保线程完成：
 *    for (int i = 0; i < N; i++) {
 *        pthread_join(threads[i], NULL);
 *    }
 * 
 * 2. 为传递参数分配内存：
 *    int *param = malloc(sizeof(int));
 *    *param = value;
 *    pthread_create(&t, NULL, func, param);
 * 
 * 3. 线程函数中必须释放参数内存：
 *    void *thread_func(void *arg) {
 *        int *param = (int*)arg;
 *        // 使用 param
 *        free(param);
 *        return NULL;
 *    }
 * 
 * 4. 返回值方式：
 *    a) 返回指针（注意生命周期）
 *    b) 修改全局变量（需要同步）
 *    c) 通过输出参数（也需要同步）
 * 
 * 5. 错误检查：
 *    int ret = pthread_create(&t, NULL, func, arg);
 *    if (ret != 0) {
 *        perror("pthread_create");
 *        exit(1);
 *    }
 * 
 * 编译与链接：
 * 
 * Linux/Mac:
 * gcc -pthread file.c -o output
 * gcc -lpthread file.c -o output  // 某些系统
 * 
 * Windows (MinGW):
 * gcc -pthread file.c -o output.exe
 * // 或使用 Windows API (CreateThread)
 * 
 * 调试建议：
 * - 使用 gdb 附加到线程程序
 * - info threads - 列表所有线程
 * - thread ID - 切换到特定线程
 * - thread apply all bt - 所有线程回溯
 * 
 * 性能考虑：
 * - 线程创建有开销，不要过度创建
 * - 考虑使用线程池避免频繁创建销毁
 * - 线程上下文切换有成本
 * - 线程间通信需要同步机制
 */
