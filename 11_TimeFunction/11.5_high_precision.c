/*
 * 第十一章：时间函数和相关库
 * 11.5 高精度时间和跨平台处理
 * 
 * 本文件展示高精度计时、性能测量和跨平台时间处理
 * 编译命令（Windows）：gcc 11.5_high_precision.c -o 11.5
 * 编译命令（Linux）：  gcc 11.5_high_precision.c -o 11.5 -lrt
 */

#include <stdio.h>
#include <time.h>

// 跨平台处理
#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/time.h>
    #include <unistd.h>
#endif

// 示例1：clock()基础性能测试
void example_clock_basic() {
    printf("=== 示例1：clock()基础性能测试 ===\n");
    
    printf("CLOCKS_PER_SEC = %ld\n", (long)CLOCKS_PER_SEC);
    printf("理论精度: %.6f 秒\n", 1.0 / CLOCKS_PER_SEC);
    
    clock_t start = clock();
    
    // 执行一些计算
    volatile long sum = 0;
    for (int i = 0; i < 10000000; i++) {
        sum += i;
    }
    
    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n执行1000万次循环：\n");
    printf("  开始时钟: %ld\n", (long)start);
    printf("  结束时钟: %ld\n", (long)end);
    printf("  时钟差:   %ld\n", (long)(end - start));
    printf("  CPU时间:  %.6f 秒\n", elapsed);
    printf("  sum = %ld (防止优化)\n", sum);
    
    printf("\n⚠ clock()测量的是CPU时间，不是实际流逝时间\n");
    printf("   如果程序sleep，clock()不会增加\n\n");
}

// 示例2：clock()测量多个任务
void example_clock_multiple_tasks() {
    printf("=== 示例2：测量多个任务的CPU时间 ===\n");
    
    clock_t total_start = clock();
    
    // 任务1：整数运算
    clock_t task1_start = clock();
    volatile long result1 = 0;
    for (int i = 0; i < 5000000; i++) {
        result1 += i * 2;
    }
    clock_t task1_end = clock();
    double task1_time = (double)(task1_end - task1_start) / CLOCKS_PER_SEC;
    
    // 任务2：浮点运算
    clock_t task2_start = clock();
    volatile double result2 = 0.0;
    for (int i = 0; i < 5000000; i++) {
        result2 += i * 3.14159;
    }
    clock_t task2_end = clock();
    double task2_time = (double)(task2_end - task2_start) / CLOCKS_PER_SEC;
    
    clock_t total_end = clock();
    double total_time = (double)(total_end - total_start) / CLOCKS_PER_SEC;
    
    printf("任务1 (整数运算): %.6f 秒\n", task1_time);
    printf("任务2 (浮点运算): %.6f 秒\n", task2_time);
    printf("总CPU时间:        %.6f 秒\n", total_time);
    printf("result1=%ld, result2=%.0f\n", result1, result2);
    
    printf("\n");
}

#ifdef _WIN32
// 示例3：Windows高精度计时 - QueryPerformanceCounter
void example_windows_qpc() {
    printf("=== 示例3：Windows QueryPerformanceCounter ===\n");
    
    LARGE_INTEGER frequency;
    LARGE_INTEGER start, end;
    
    // 获取计时器频率
    QueryPerformanceFrequency(&frequency);
    printf("计时器频率: %lld Hz\n", frequency.QuadPart);
    printf("理论精度:   %.9f 秒 (%.3f 纳秒)\n", 
           1.0 / frequency.QuadPart, 
           1e9 / frequency.QuadPart);
    
    // 测试1：快速操作
    QueryPerformanceCounter(&start);
    volatile int x = 0;
    for (int i = 0; i < 1000; i++) {
        x += i;
    }
    QueryPerformanceCounter(&end);
    
    double elapsed = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("\n1000次循环耗时: %.9f 秒 (%.3f 微秒)\n", 
           elapsed, elapsed * 1e6);
    printf("x = %d\n", x);
    
    // 测试2：较长操作
    QueryPerformanceCounter(&start);
    volatile long sum = 0;
    for (int i = 0; i < 10000000; i++) {
        sum += i;
    }
    QueryPerformanceCounter(&end);
    
    elapsed = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("\n1000万次循环耗时: %.6f 秒\n", elapsed);
    printf("sum = %ld\n", sum);
    
    printf("\nQueryPerformanceCounter特点：\n");
    printf("  • 精度极高（微秒/纳秒级）\n");
    printf("  • 测量真实流逝时间（wall-clock time）\n");
    printf("  • Windows专用API\n");
    
    printf("\n");
}

// 示例4：Windows Sleep精度测试
void example_windows_sleep() {
    printf("=== 示例4：Windows Sleep精度 ===\n");
    
    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);
    
    int sleep_ms[] = {1, 10, 100, 1000};
    
    for (int i = 0; i < 4; i++) {
        QueryPerformanceCounter(&start);
        Sleep(sleep_ms[i]);
        QueryPerformanceCounter(&end);
        
        double actual = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
        printf("Sleep(%4d ms) → 实际: %.3f ms\n", 
               sleep_ms[i], actual * 1000);
    }
    
    printf("\n⚠ Windows Sleep精度约15-16ms\n");
    printf("   实际睡眠时间通常比请求的长\n");
    
    printf("\n");
}

#else
// 示例3：Linux高精度计时 - clock_gettime
void example_linux_clock_gettime() {
    printf("=== 示例3：Linux clock_gettime ===\n");
    
    struct timespec start, end;
    
    // CLOCK_REALTIME: 系统时钟（可调整）
    clock_gettime(CLOCK_REALTIME, &start);
    printf("CLOCK_REALTIME:\n");
    printf("  秒:      %ld\n", (long)start.tv_sec);
    printf("  纳秒:    %ld\n", (long)start.tv_nsec);
    printf("  精度:    纳秒级\n");
    
    // CLOCK_MONOTONIC: 单调时钟（不可调整，适合计时）
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    volatile long sum = 0;
    for (int i = 0; i < 10000000; i++) {
        sum += i;
    }
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    
    // 计算时间差
    long seconds = end.tv_sec - start.tv_sec;
    long nanoseconds = end.tv_nsec - start.tv_nsec;
    if (nanoseconds < 0) {
        seconds--;
        nanoseconds += 1000000000;
    }
    
    double elapsed = seconds + nanoseconds / 1e9;
    printf("\nCLOCK_MONOTONIC 性能测试:\n");
    printf("  1000万次循环耗时: %.9f 秒\n", elapsed);
    printf("  sum = %ld\n", sum);
    
    printf("\n可用的时钟类型：\n");
    printf("  CLOCK_REALTIME  - 系统实时时钟\n");
    printf("  CLOCK_MONOTONIC - 单调时钟（推荐用于计时）\n");
    printf("  CLOCK_PROCESS_CPUTIME_ID - 进程CPU时间\n");
    printf("  CLOCK_THREAD_CPUTIME_ID  - 线程CPU时间\n");
    
    printf("\n");
}

// 示例4：Linux gettimeofday
void example_linux_gettimeofday() {
    printf("=== 示例4：Linux gettimeofday ===\n");
    
    struct timeval start, end;
    
    gettimeofday(&start, NULL);
    printf("当前时间:\n");
    printf("  秒:      %ld\n", (long)start.tv_sec);
    printf("  微秒:    %ld\n", (long)start.tv_usec);
    
    volatile long sum = 0;
    for (int i = 0; i < 10000000; i++) {
        sum += i;
    }
    
    gettimeofday(&end, NULL);
    
    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    if (microseconds < 0) {
        seconds--;
        microseconds += 1000000;
    }
    
    double elapsed = seconds + microseconds / 1e6;
    printf("\n性能测试:\n");
    printf("  1000万次循环耗时: %.6f 秒\n", elapsed);
    printf("  sum = %ld\n", sum);
    
    printf("\n⚠ gettimeofday已过时，推荐使用clock_gettime\n");
    
    printf("\n");
}
#endif

// 示例5：跨平台高精度计时封装
typedef struct {
#ifdef _WIN32
    LARGE_INTEGER start;
    LARGE_INTEGER frequency;
#else
    struct timespec start;
#endif
} Timer;

void timer_start(Timer *timer) {
#ifdef _WIN32
    QueryPerformanceFrequency(&timer->frequency);
    QueryPerformanceCounter(&timer->start);
#else
    clock_gettime(CLOCK_MONOTONIC, &timer->start);
#endif
}

double timer_elapsed(Timer *timer) {
#ifdef _WIN32
    LARGE_INTEGER end;
    QueryPerformanceCounter(&end);
    return (double)(end.QuadPart - timer->start.QuadPart) / timer->frequency.QuadPart;
#else
    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC, &end);
    long seconds = end.tv_sec - timer->start.tv_sec;
    long nanoseconds = end.tv_nsec - timer->start.tv_nsec;
    if (nanoseconds < 0) {
        seconds--;
        nanoseconds += 1000000000;
    }
    return seconds + nanoseconds / 1e9;
#endif
}

void example_cross_platform_timer() {
    printf("=== 示例5：跨平台高精度计时器 ===\n");
    
    Timer timer;
    timer_start(&timer);
    
    // 执行一些操作
    volatile long sum = 0;
    for (int i = 0; i < 10000000; i++) {
        sum += i;
    }
    
    double elapsed = timer_elapsed(&timer);
    
    printf("使用跨平台计时器:\n");
    printf("  1000万次循环耗时: %.6f 秒\n", elapsed);
    printf("  sum = %ld\n", sum);
    
    printf("\n这个Timer结构可以在Windows和Linux上通用\n");
    printf("自动选择最佳的高精度计时API\n");
    
    printf("\n");
}

// 示例6：性能分析工具
void example_performance_profiler() {
    printf("=== 示例6：简易性能分析器 ===\n");
    
    Timer timer;
    
    printf("测试不同操作的性能：\n\n");
    
    // 测试1：空循环
    timer_start(&timer);
    for (volatile int i = 0; i < 10000000; i++);
    printf("1. 空循环1000万次:     %.6f 秒\n", timer_elapsed(&timer));
    
    // 测试2：整数加法
    timer_start(&timer);
    volatile int sum_int = 0;
    for (int i = 0; i < 10000000; i++) sum_int += i;
    printf("2. 整数加法1000万次:   %.6f 秒\n", timer_elapsed(&timer));
    
    // 测试3：浮点乘法
    timer_start(&timer);
    volatile double sum_double = 0;
    for (int i = 0; i < 10000000; i++) sum_double += i * 3.14;
    printf("3. 浮点乘法1000万次:   %.6f 秒\n", timer_elapsed(&timer));
    
    // 测试4：函数调用
    timer_start(&timer);
    volatile int sum_func = 0;
    for (int i = 0; i < 1000000; i++) {
        sum_func += abs(i);
    }
    printf("4. 函数调用100万次:    %.6f 秒\n", timer_elapsed(&timer));
    
    // 测试5：time()调用
    timer_start(&timer);
    for (int i = 0; i < 100000; i++) {
        volatile time_t t = time(NULL);
        (void)t;
    }
    printf("5. time()调用10万次:   %.6f 秒\n", timer_elapsed(&timer));
    
    printf("\n");
}

// 示例7：FPS计数器（游戏/图形应用）
void example_fps_counter() {
    printf("=== 示例7：FPS计数器模拟 ===\n");
    
    Timer frame_timer, fps_timer;
    int frame_count = 0;
    double fps_update_interval = 1.0;  // 每秒更新一次FPS
    
    timer_start(&fps_timer);
    
    printf("模拟60帧...\n");
    
    for (int i = 0; i < 60; i++) {
        timer_start(&frame_timer);
        
        // 模拟渲染工作（10ms）
        Timer work_timer;
        timer_start(&work_timer);
        while (timer_elapsed(&work_timer) < 0.01);  // 10ms工作
        
        frame_count++;
        
        // 每秒更新FPS显示
        double fps_elapsed = timer_elapsed(&fps_timer);
        if (fps_elapsed >= fps_update_interval) {
            double fps = frame_count / fps_elapsed;
            printf("  FPS: %.2f (平均帧时间: %.2f ms)\n", 
                   fps, 1000.0 / fps);
            
            frame_count = 0;
            timer_start(&fps_timer);
        }
        
        double frame_time = timer_elapsed(&frame_timer);
        // 实际应用中这里会有帧率限制逻辑
    }
    
    printf("\n");
}

// 示例8：基准测试框架
typedef void (*BenchmarkFunc)(void);

void benchmark(const char *name, BenchmarkFunc func, int iterations) {
    printf("  %-30s ", name);
    fflush(stdout);
    
    Timer timer;
    timer_start(&timer);
    
    for (int i = 0; i < iterations; i++) {
        func();
    }
    
    double elapsed = timer_elapsed(&timer);
    printf("%.6f 秒 (%.0f ops/sec)\n", 
           elapsed, iterations / elapsed);
}

void dummy_operation() {
    volatile int x = 0;
    for (int i = 0; i < 1000; i++) x++;
}

void example_benchmark_framework() {
    printf("=== 示例8：基准测试框架 ===\n");
    
    printf("运行基准测试...\n");
    benchmark("简单操作", dummy_operation, 10000);
    
    printf("\n这个框架可以方便地测试不同函数的性能\n\n");
}

int main() {
    printf("╔═══════════════════════════════════════╗\n");
    printf("║   第11章：时间函数和相关库            ║\n");
    printf("║   11.5 高精度时间和跨平台处理         ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
    
    example_clock_basic();
    example_clock_multiple_tasks();
    
#ifdef _WIN32
    example_windows_qpc();
    example_windows_sleep();
#else
    example_linux_clock_gettime();
    example_linux_gettimeofday();
#endif
    
    example_cross_platform_timer();
    example_performance_profiler();
    example_fps_counter();
    example_benchmark_framework();
    
    printf("═════════════════════════════════════════\n");
    printf("高精度计时API总结：\n");
    printf("═════════════════════════════════════════\n");
    
#ifdef _WIN32
    printf("Windows平台：\n");
    printf("  • QueryPerformanceCounter - 高精度计时\n");
    printf("  • QueryPerformanceFrequency - 获取频率\n");
    printf("  • 精度：微秒/纳秒级\n");
    printf("  • 测量：真实流逝时间\n");
#else
    printf("Linux/Unix平台：\n");
    printf("  • clock_gettime() - 高精度计时（推荐）\n");
    printf("    - CLOCK_MONOTONIC: 单调时钟，适合性能测试\n");
    printf("    - CLOCK_REALTIME:  实时时钟，可调整\n");
    printf("  • gettimeofday() - 微秒精度（已过时）\n");
    printf("  • 精度：纳秒级\n");
#endif
    
    printf("\n标准C库（跨平台）：\n");
    printf("  • clock() - CPU时间，精度低\n");
    printf("  • time()  - 秒级精度\n");
    printf("\n");
    printf("使用建议：\n");
    printf("  1. 性能测试：使用高精度API\n");
    printf("     Windows: QueryPerformanceCounter\n");
    printf("     Linux:   clock_gettime(CLOCK_MONOTONIC)\n");
    printf("\n");
    printf("  2. 跨平台项目：封装统一接口\n");
    printf("     用 #ifdef 条件编译\n");
    printf("\n");
    printf("  3. 日常时间操作：time() + localtime()\n");
    printf("     精度够用且跨平台\n");
    printf("\n");
    printf("  4. CPU时间测量：clock()\n");
    printf("     测量进程实际占用CPU时间\n");
    printf("═════════════════════════════════════════\n");
    
    return 0;
}

/*
 * 编译和运行：
 *   Windows: gcc 11.5_high_precision.c -o 11.5
 *            11.5.exe
 * 
 *   Linux:   gcc 11.5_high_precision.c -o 11.5 -lrt
 *            ./11.5
 * 
 * 学习要点：
 *   1. 理解不同平台的高精度计时API
 *   2. 掌握跨平台计时的封装方法
 *   3. 学会使用计时器进行性能分析
 *   4. 了解CPU时间与墙上时钟时间的区别
 * 
 * 实际应用：
 *   • 游戏引擎的帧率控制
 *   • 性能基准测试
 *   • 算法效率对比
 *   • 实时系统的延迟测量
 */
