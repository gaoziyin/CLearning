/*
 * 第十一章：时间函数和相关库
 * 11.2 time.h 标准库函数详解
 * 
 * 本文件详细展示time.h库中所有常用函数的用法
 * 编译命令：gcc 11.2_time_library.c -o 11.2
 */

#include <stdio.h>
#include <time.h>
#include <string.h>

// 示例1：time() - 获取当前时间戳
void example_time_function() {
    printf("=== 示例1：time()函数 ===\n");
    
    // 方法1：传递NULL
    time_t t1 = time(NULL);
    printf("方法1 time(NULL): %ld\n", (long)t1);
    
    // 方法2：传递指针
    time_t t2;
    time(&t2);
    printf("方法2 time(&t):   %ld\n", (long)t2);
    
    printf("两种方法结果相同\n");
    printf("返回值：成功返回时间戳，失败返回-1\n\n");
}

// 示例2：ctime() - 时间戳转字符串
void example_ctime_function() {
    printf("=== 示例2：ctime()函数 ===\n");
    
    time_t now = time(NULL);
    char *str = ctime(&now);
    
    printf("时间戳: %ld\n", (long)now);
    printf("转换结果: %s", str);  // 自带换行
    printf("字符串长度: %zu (包含换行符)\n", strlen(str));
    
    printf("\n格式说明：\n");
    printf("  Www Mmm dd hh:mm:ss yyyy\\n\n");
    printf("  Www - 星期几（3字母）\n");
    printf("  Mmm - 月份（3字母）\n");
    printf("  dd  - 日期（2位数字）\n");
    printf("  hh:mm:ss - 时分秒\n");
    printf("  yyyy - 年份（4位数字）\n\n");
    
    printf("⚠ 注意：ctime()返回静态缓冲区，多次调用会覆盖\n\n");
}

// 示例3：localtime() - 转本地时间
void example_localtime_function() {
    printf("=== 示例3：localtime()函数 ===\n");
    
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    
    printf("时间戳: %ld\n", (long)now);
    printf("\n分解后的时间结构：\n");
    printf("  年份: %d (原始值%d + 1900)\n", 
           local->tm_year + 1900, local->tm_year);
    printf("  月份: %d (原始值%d + 1)\n", 
           local->tm_mon + 1, local->tm_mon);
    printf("  日期: %d\n", local->tm_mday);
    printf("  时:   %d\n", local->tm_hour);
    printf("  分:   %d\n", local->tm_min);
    printf("  秒:   %d\n", local->tm_sec);
    printf("  星期: %d (0=周日)\n", local->tm_wday);
    printf("  年日: %d (一年中的第%d天)\n", 
           local->tm_yday, local->tm_yday + 1);
    printf("  夏令时: %d (>0:是, 0:否, <0:未知)\n", local->tm_isdst);
    
    printf("\n⚠ 返回静态指针，下次调用会覆盖内容\n\n");
}

// 示例4：gmtime() - 转UTC时间
void example_gmtime_function() {
    printf("=== 示例4：gmtime()函数 ===\n");
    
    time_t now = time(NULL);
    struct tm *utc = gmtime(&now);
    struct tm *local = localtime(&now);
    
    printf("UTC时间:  %04d-%02d-%02d %02d:%02d:%02d\n",
           utc->tm_year + 1900, utc->tm_mon + 1, utc->tm_mday,
           utc->tm_hour, utc->tm_min, utc->tm_sec);
    
    printf("本地时间: %04d-%02d-%02d %02d:%02d:%02d\n",
           local->tm_year + 1900, local->tm_mon + 1, local->tm_mday,
           local->tm_hour, local->tm_min, local->tm_sec);
    
    printf("\n用途：\n");
    printf("  • 存储时间时统一用UTC，避免时区混乱\n");
    printf("  • 显示时再转为本地时间\n");
    printf("  • 国际化应用必须使用UTC\n\n");
}

// 示例5：mktime() - struct tm转时间戳
void example_mktime_function() {
    printf("=== 示例5：mktime()函数 ===\n");
    
    // 创建特定时间：2025年1月1日 00:00:00
    struct tm target = {0};
    target.tm_year = 2025 - 1900;  // 125
    target.tm_mon = 1 - 1;          // 0
    target.tm_mday = 1;
    target.tm_hour = 0;
    target.tm_min = 0;
    target.tm_sec = 0;
    target.tm_isdst = -1;  // 让系统自动判断夏令时
    
    printf("输入时间: 2025-01-01 00:00:00\n");
    
    time_t timestamp = mktime(&target);
    
    if (timestamp == -1) {
        printf("错误：无效的时间\n");
    } else {
        printf("生成时间戳: %ld\n", (long)timestamp);
        printf("验证: %s", ctime(&timestamp));
        
        // mktime会自动修正不合法的值
        printf("\nmktime还会修正tm_wday和tm_yday：\n");
        printf("  星期: %d\n", target.tm_wday);
        printf("  年日: %d\n", target.tm_yday);
    }
    printf("\n");
}

// 示例6：mktime()自动修正功能
void example_mktime_normalization() {
    printf("=== 示例6：mktime()自动修正 ===\n");
    
    // 测试1：月份超出范围
    struct tm test1 = {0};
    test1.tm_year = 2024 - 1900;
    test1.tm_mon = 13;  // 14月 -> 2025年2月
    test1.tm_mday = 1;
    test1.tm_isdst = -1;
    
    printf("输入：2024-14-01（14月）\n");
    mktime(&test1);
    printf("修正：%04d-%02d-%02d\n\n",
           test1.tm_year + 1900, test1.tm_mon + 1, test1.tm_mday);
    
    // 测试2：日期超出范围
    struct tm test2 = {0};
    test2.tm_year = 2024 - 1900;
    test2.tm_mon = 1 - 1;
    test2.tm_mday = 32;  // 1月32日 -> 2月1日
    test2.tm_isdst = -1;
    
    printf("输入：2024-01-32（32日）\n");
    mktime(&test2);
    printf("修正：%04d-%02d-%02d\n\n",
           test2.tm_year + 1900, test2.tm_mon + 1, test2.tm_mday);
    
    printf("用途：可用于计算"30天后"等相对时间\n\n");
}

// 示例7：asctime() - struct tm转字符串
void example_asctime_function() {
    printf("=== 示例7：asctime()函数 ===\n");
    
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    
    // asctime直接从struct tm转字符串
    char *str = asctime(local);
    
    printf("asctime输出: %s", str);
    printf("格式与ctime相同\n");
    printf("区别：asctime输入是struct tm，ctime输入是time_t\n\n");
    
    printf("两者对比：\n");
    printf("  ctime(&t)    = %s", ctime(&now));
    printf("  asctime(tm)  = %s", asctime(local));
    printf("\n");
}

// 示例8：difftime() - 时间差计算
void example_difftime_function() {
    printf("=== 示例8：difftime()函数 ===\n");
    
    // 创建两个时间点
    time_t start = time(NULL);
    time_t end = start + 12345;  // 加上一些秒数
    
    double diff = difftime(end, start);
    
    printf("开始时间: %ld\n", (long)start);
    printf("结束时间: %ld\n", (long)end);
    printf("时间差: %.0f 秒\n", diff);
    
    // 转换为不同单位
    printf("\n换算：\n");
    printf("  %.0f 秒\n", diff);
    printf("  %.2f 分钟\n", diff / 60);
    printf("  %.2f 小时\n", diff / 3600);
    printf("  %.2f 天\n", diff / 86400);
    
    printf("\n为何使用difftime而不是直接相减？\n");
    printf("  • difftime返回double，更精确\n");
    printf("  • 可移植性更好（某些系统time_t不是整数）\n");
    printf("  • 明确表达意图\n\n");
}

// 示例9：clock() - CPU时间
void example_clock_function() {
    printf("=== 示例9：clock()函数 ===\n");
    
    clock_t start = clock();
    
    // 执行一些计算
    long sum = 0;
    for (int i = 0; i < 5000000; i++) {
        sum += i;
    }
    
    clock_t end = clock();
    
    printf("开始时钟: %ld\n", (long)start);
    printf("结束时钟: %ld\n", (long)end);
    printf("时钟差:   %ld\n", (long)(end - start));
    printf("CLOCKS_PER_SEC: %ld\n", (long)CLOCKS_PER_SEC);
    
    double cpu_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("CPU时间: %.6f 秒\n", cpu_time);
    printf("sum = %ld (防止优化)\n", sum);
    
    printf("\nclock() vs time()：\n");
    printf("  clock() - 测量CPU时间（进程占用）\n");
    printf("  time()  - 测量墙上时钟时间（真实流逝）\n");
    printf("  CPU时间 ≤ 墙上时钟时间\n\n");
}

// 示例10：实用时间工具函数
void example_practical_tools() {
    printf("=== 示例10：实用工具函数 ===\n");
    
    time_t now = time(NULL);
    
    // 1. 判断是否是同一天
    struct tm *tm1 = localtime(&now);
    time_t tomorrow = now + 86400;
    struct tm *tm2 = localtime(&tomorrow);
    
    printf("今天: %04d-%02d-%02d\n",
           tm1->tm_year + 1900, tm1->tm_mon + 1, tm1->tm_mday);
    printf("明天: %04d-%02d-%02d\n",
           tm2->tm_year + 1900, tm2->tm_mon + 1, tm2->tm_mday);
    
    // 2. 计算年龄
    struct tm birth = {0};
    birth.tm_year = 2000 - 1900;
    birth.tm_mon = 6 - 1;
    birth.tm_mday = 15;
    birth.tm_isdst = -1;
    
    time_t birth_time = mktime(&birth);
    double age_seconds = difftime(now, birth_time);
    int age_years = (int)(age_seconds / (365.25 * 86400));
    
    printf("\n出生日期: 2000-06-15\n");
    printf("当前年龄: 约%d岁\n", age_years);
    
    // 3. 星期几的文字
    const char *weekdays[] = {
        "周日", "周一", "周二", "周三", "周四", "周五", "周六"
    };
    struct tm *today = localtime(&now);
    printf("今天是: %s\n", weekdays[today->tm_wday]);
    
    printf("\n");
}

int main() {
    printf("╔═══════════════════════════════════════╗\n");
    printf("║   第11章：时间函数和相关库            ║\n");
    printf("║   11.2 time.h标准库函数详解           ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
    
    example_time_function();
    example_ctime_function();
    example_localtime_function();
    example_gmtime_function();
    example_mktime_function();
    example_mktime_normalization();
    example_asctime_function();
    example_difftime_function();
    example_clock_function();
    example_practical_tools();
    
    printf("═════════════════════════════════════════\n");
    printf("time.h函数速查表：\n");
    printf("═════════════════════════════════════════\n");
    printf("获取时间：\n");
    printf("  time()      - 获取当前Unix时间戳\n");
    printf("  clock()     - 获取CPU时钟数\n");
    printf("\n");
    printf("转换函数：\n");
    printf("  localtime() - time_t → struct tm (本地)\n");
    printf("  gmtime()    - time_t → struct tm (UTC)\n");
    printf("  mktime()    - struct tm → time_t\n");
    printf("  ctime()     - time_t → 字符串\n");
    printf("  asctime()   - struct tm → 字符串\n");
    printf("\n");
    printf("计算函数：\n");
    printf("  difftime()  - 计算两个time_t的差值\n");
    printf("\n");
    printf("⚠ 关键注意：\n");
    printf("  • localtime/gmtime/asctime/ctime返回静态指针\n");
    printf("  • 多线程使用localtime_r/gmtime_r等线程安全版本\n");
    printf("  • mktime会自动修正不合法的时间值\n");
    printf("  • tm_isdst设为-1让系统自动判断夏令时\n");
    printf("═════════════════════════════════════════\n");
    
    return 0;
}

/*
 * 编译和运行：
 *   gcc 11.2_time_library.c -o 11.2
 *   ./11.2
 * 
 * 学习要点：
 *   1. 理解每个函数的用途和返回值
 *   2. 注意静态指针的问题
 *   3. 掌握时间转换的流程
 *   4. 实践中优先使用线程安全版本
 */
