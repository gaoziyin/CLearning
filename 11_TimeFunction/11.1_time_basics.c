/*
 * 第十一章：时间函数和相关库
 * 11.1 时间基础概念
 * 
 * 本文件展示实际可运行的时间基础示例代码
 * 编译命令：gcc 11.1_time_basics.c -o 11.1
 */

#include <stdio.h>
#include <time.h>
#include <string.h>

// 示例1：获取Unix时间戳
void example_unix_timestamp() {
    printf("=== 示例1：Unix时间戳 ===\n");
    
    // 获取当前时间戳
    time_t now = time(NULL);
    
    printf("当前Unix时间戳: %ld\n", (long)now);
    printf("说明：从1970-01-01 00:00:00 UTC到现在的秒数\n");
    printf("用途：时间的标准存储格式，易于比较和计算\n\n");
}

// 示例2：time_t类型大小
void example_time_t_size() {
    printf("=== 示例2：time_t类型大小 ===\n");
    
    printf("time_t的大小: %zu 字节\n", sizeof(time_t));
    printf("sizeof(time_t) == %zu  =>  ", sizeof(time_t));
    
    if (sizeof(time_t) == 4) {
        printf("32位系统 - 2038年会溢出!\n");
    } else if (sizeof(time_t) == 8) {
        printf("64位系统 - 安全，可用到2^63年\n");
    }
    printf("\n");
}

// 示例3：ctime()快速显示时间
void example_ctime() {
    printf("=== 示例3：ctime()快速显示 ===\n");
    
    time_t now = time(NULL);
    char *timestr = ctime(&now);
    
    printf("当前时间: %s", timestr);  // ctime已包含换行符
    printf("注意：ctime()返回的字符串自带换行符\n\n");
}

// 示例4：时间比较
void example_time_comparison() {
    printf("=== 示例4：时间比较 ===\n");
    
    time_t time1 = time(NULL);
    time_t time2 = time1 + 3600;  // 1小时后
    
    printf("时间1: %ld\n", (long)time1);
    printf("时间2: %ld (1小时后)\n", (long)time2);
    
    if (time2 > time1) {
        printf("时间2 > 时间1\n");
        printf("时间差: %ld 秒 = %ld 小时\n", 
               (long)(time2 - time1), (long)(time2 - time1) / 3600);
    }
    printf("\n");
}

// 示例5：difftime()计算时间差
void example_difftime() {
    printf("=== 示例5：difftime()计算时间差 ===\n");
    
    time_t start = time(NULL);
    
    // 模拟一些操作（计算100万次）
    volatile int sum = 0;
    for (int i = 0; i < 1000000; i++) {
        sum += i;
    }
    
    time_t end = time(NULL);
    double elapsed = difftime(end, start);
    
    printf("开始时间: %ld\n", (long)start);
    printf("结束时间: %ld\n", (long)end);
    printf("耗时: %.0f 秒\n", elapsed);
    printf("sum = %d (防止编译器优化)\n", sum);
    printf("\n");
}

// 示例6：struct tm基本结构
void example_struct_tm() {
    printf("=== 示例6：struct tm结构体 ===\n");
    
    time_t now = time(NULL);
    struct tm *local_time = localtime(&now);
    
    printf("struct tm的各个成员：\n");
    printf("  tm_year = %d (需要+1900 = %d年)\n", 
           local_time->tm_year, local_time->tm_year + 1900);
    printf("  tm_mon  = %d (需要+1 = %d月)\n", 
           local_time->tm_mon, local_time->tm_mon + 1);
    printf("  tm_mday = %d 日\n", local_time->tm_mday);
    printf("  tm_hour = %d 时\n", local_time->tm_hour);
    printf("  tm_min  = %d 分\n", local_time->tm_min);
    printf("  tm_sec  = %d 秒\n", local_time->tm_sec);
    printf("  tm_wday = %d (0=周日, 1=周一, ..., 6=周六)\n", 
           local_time->tm_wday);
    printf("  tm_yday = %d (一年中的第%d天)\n", 
           local_time->tm_yday, local_time->tm_yday + 1);
    printf("\n");
    
    printf("关键记忆点：\n");
    printf("  ⚠ tm_year: 从1900年开始，2024年存为124\n");
    printf("  ⚠ tm_mon:  从0开始，1月是0，12月是11\n");
    printf("  ⚠ tm_mday: 从1开始，1-31\n");
    printf("\n");
}

// 示例7：localtime() vs gmtime()
void example_localtime_vs_gmtime() {
    printf("=== 示例7：localtime() vs gmtime() ===\n");
    
    time_t now = time(NULL);
    
    struct tm *local = localtime(&now);
    struct tm *utc = gmtime(&now);
    
    printf("本地时间: %04d-%02d-%02d %02d:%02d:%02d\n",
           local->tm_year + 1900, local->tm_mon + 1, local->tm_mday,
           local->tm_hour, local->tm_min, local->tm_sec);
    
    printf("UTC时间:  %04d-%02d-%02d %02d:%02d:%02d\n",
           utc->tm_year + 1900, utc->tm_mon + 1, utc->tm_mday,
           utc->tm_hour, utc->tm_min, utc->tm_sec);
    
    int offset = local->tm_hour - utc->tm_hour;
    if (offset < -12) offset += 24;
    if (offset > 12) offset -= 24;
    printf("时区偏移: UTC%+d\n", offset);
    printf("\n");
}

// 示例8：mktime()创建时间戳
void example_mktime() {
    printf("=== 示例8：mktime()创建特定时间 ===\n");
    
    // 创建2024年10月31日 16:30:00的时间戳
    struct tm target_time = {0};
    target_time.tm_year = 2024 - 1900;  // 124
    target_time.tm_mon = 10 - 1;        // 9 (10月)
    target_time.tm_mday = 31;
    target_time.tm_hour = 16;
    target_time.tm_min = 30;
    target_time.tm_sec = 0;
    target_time.tm_isdst = -1;  // 自动判断夏令时
    
    time_t timestamp = mktime(&target_time);
    
    printf("设定时间: 2024-10-31 16:30:00\n");
    printf("生成时间戳: %ld\n", (long)timestamp);
    printf("验证: %s", ctime(&timestamp));
    printf("\n");
}

// 示例9：clock()性能测试
void example_clock_performance() {
    printf("=== 示例9：clock()性能测试 ===\n");
    
    clock_t start = clock();
    
    // 执行一些计算密集操作
    double result = 0.0;
    for (int i = 0; i < 10000000; i++) {
        result += i * 0.5;
    }
    
    clock_t end = clock();
    double cpu_time = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("执行1000万次浮点运算\n");
    printf("CPU时间: %.6f 秒\n", cpu_time);
    printf("CLOCKS_PER_SEC = %ld\n", (long)CLOCKS_PER_SEC);
    printf("result = %.0f (防止优化)\n", result);
    printf("\n");
}

// 示例10：时间计算示例
void example_time_calculation() {
    printf("=== 示例10：时间计算 ===\n");
    
    time_t now = time(NULL);
    
    // 计算1小时后
    time_t one_hour_later = now + 3600;
    printf("现在:    %s", ctime(&now));
    printf("1小时后: %s", ctime(&one_hour_later));
    
    // 计算1天后
    time_t one_day_later = now + 86400;
    printf("1天后:   %s", ctime(&one_day_later));
    
    // 计算1周后
    time_t one_week_later = now + 7 * 86400;
    printf("1周后:   %s", ctime(&one_week_later));
    
    printf("时间计算常用秒数：\n");
    printf("  1分钟 = 60秒\n");
    printf("  1小时 = 3600秒\n");
    printf("  1天   = 86400秒\n");
    printf("  1周   = 604800秒\n");
    printf("\n");
}

int main() {
    printf("╔═══════════════════════════════════════╗\n");
    printf("║   第11章：时间函数和相关库            ║\n");
    printf("║   11.1 时间基础概念与实战示例         ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
    
    example_unix_timestamp();
    example_time_t_size();
    example_ctime();
    example_time_comparison();
    example_difftime();
    example_struct_tm();
    example_localtime_vs_gmtime();
    example_mktime();
    example_clock_performance();
    example_time_calculation();
    
    printf("═════════════════════════════════════════\n");
    printf("核心知识点总结：\n");
    printf("═════════════════════════════════════════\n");
    printf("1. time()      - 获取Unix时间戳（秒）\n");
    printf("2. ctime()     - 时间戳转为字符串\n");
    printf("3. localtime() - 时间戳转struct tm（本地）\n");
    printf("4. gmtime()    - 时间戳转struct tm（UTC）\n");
    printf("5. mktime()    - struct tm转时间戳\n");
    printf("6. difftime()  - 计算两个时间的差值\n");
    printf("7. clock()     - CPU时间（用于性能测试）\n");
    printf("\n");
    printf("⚠ 关键注意事项：\n");
    printf("  • tm_year从1900开始，显示时要+1900\n");
    printf("  • tm_mon从0开始，1月是0，要+1显示\n");
    printf("  • tm_mday从1开始，正常使用\n");
    printf("  • ctime()返回的字符串包含换行符\n");
    printf("  • localtime()返回静态指针，多次调用会覆盖\n");
    printf("═════════════════════════════════════════\n");
    
    return 0;
}

/*
 * 编译和运行：
 *   gcc 11.1_time_basics.c -o 11.1
 *   ./11.1
 * 
 * 学习建议：
 *   1. 先运行程序，观察输出
 *   2. 修改示例代码中的参数，观察变化
 *   3. 尝试组合不同的时间函数
 *   4. 注意tm_year和tm_mon的偏移量
 */
