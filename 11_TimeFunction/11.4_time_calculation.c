/*
 * 第十一章：时间函数和相关库
 * 11.4 时间计算和实用技巧
 * 
 * 本文件展示时间计算、日期操作等实用技巧
 * 编译命令：gcc 11.4_time_calculation.c -o 11.4
 */

#include <stdio.h>
#include <time.h>
#include <string.h>

// 示例1：计算N天后的日期
void example_days_later() {
    printf("=== 示例1：计算N天后的日期 ===\n");
    
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    char buffer[100];
    
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", local);
    printf("今天:    %s\n", buffer);
    
    // 方法1：直接加秒数
    time_t tomorrow = now + 86400;
    struct tm *tm_tomorrow = localtime(&tomorrow);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", tm_tomorrow);
    printf("明天:    %s (now + 86400秒)\n", buffer);
    
    // 方法2：使用mktime自动修正
    struct tm future = *local;
    future.tm_mday += 7;  // 加7天
    future.tm_isdst = -1;
    mktime(&future);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &future);
    printf("7天后:   %s (tm_mday + 7)\n", buffer);
    
    // 30天后（跨月）
    future = *local;
    future.tm_mday += 30;
    future.tm_isdst = -1;
    mktime(&future);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &future);
    printf("30天后:  %s\n", buffer);
    
    printf("\n");
}

// 示例2：计算N个月后的日期
void example_months_later() {
    printf("=== 示例2：计算N个月后的日期 ===\n");
    
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    char buffer[100];
    
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", local);
    printf("今天:    %s\n", buffer);
    
    // 1个月后
    struct tm future = *local;
    future.tm_mon += 1;
    future.tm_isdst = -1;
    mktime(&future);  // 自动处理跨年
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &future);
    printf("1个月后: %s\n", buffer);
    
    // 6个月后
    future = *local;
    future.tm_mon += 6;
    future.tm_isdst = -1;
    mktime(&future);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &future);
    printf("6个月后: %s\n", buffer);
    
    // 13个月后（跨年）
    future = *local;
    future.tm_mon += 13;
    future.tm_isdst = -1;
    mktime(&future);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &future);
    printf("13个月后: %s\n", buffer);
    
    printf("\n");
}

// 示例3：计算两个日期之间的天数
void example_days_between() {
    printf("=== 示例3：计算两个日期之间的天数 ===\n");
    
    // 日期1：2024-01-01
    struct tm date1 = {0};
    date1.tm_year = 2024 - 1900;
    date1.tm_mon = 1 - 1;
    date1.tm_mday = 1;
    date1.tm_isdst = -1;
    
    // 日期2：2024-12-31
    struct tm date2 = {0};
    date2.tm_year = 2024 - 1900;
    date2.tm_mon = 12 - 1;
    date2.tm_mday = 31;
    date2.tm_isdst = -1;
    
    time_t time1 = mktime(&date1);
    time_t time2 = mktime(&date2);
    
    double seconds = difftime(time2, time1);
    int days = (int)(seconds / 86400);
    
    printf("日期1: 2024-01-01\n");
    printf("日期2: 2024-12-31\n");
    printf("相差: %d 天\n", days);
    printf("(2024年共%d天，是%s)\n", 
           days + 1, (days + 1 == 366) ? "闰年" : "平年");
    
    printf("\n");
}

// 示例4：判断闰年
void example_leap_year() {
    printf("=== 示例4：判断闰年 ===\n");
    
    // 方法1：手动计算
    int years[] = {2000, 2020, 2024, 2023, 1900, 2100};
    
    for (int i = 0; i < 6; i++) {
        int year = years[i];
        int is_leap;
        
        if (year % 400 == 0) {
            is_leap = 1;
        } else if (year % 100 == 0) {
            is_leap = 0;
        } else if (year % 4 == 0) {
            is_leap = 1;
        } else {
            is_leap = 0;
        }
        
        printf("%d年: %s\n", year, is_leap ? "闰年" : "平年");
    }
    
    printf("\n闰年判断规则：\n");
    printf("  1. 能被400整除 → 闰年 (2000年)\n");
    printf("  2. 能被100整除 → 平年 (1900年)\n");
    printf("  3. 能被4整除   → 闰年 (2024年)\n");
    printf("  4. 否则        → 平年 (2023年)\n");
    
    printf("\n");
}

// 示例5：计算年龄
void example_calculate_age() {
    printf("=== 示例5：计算年龄 ===\n");
    
    time_t now = time(NULL);
    struct tm *today = localtime(&now);
    
    // 设定生日
    struct tm birthday = {0};
    birthday.tm_year = 1995 - 1900;
    birthday.tm_mon = 6 - 1;  // 6月
    birthday.tm_mday = 15;
    birthday.tm_isdst = -1;
    
    // 计算年龄
    int age = today->tm_year - birthday.tm_year;
    
    // 检查今年生日是否已过
    if (today->tm_mon < birthday.tm_mon ||
        (today->tm_mon == birthday.tm_mon && today->tm_mday < birthday.tm_mday)) {
        age--;
    }
    
    printf("生日: 1995-06-15\n");
    printf("今天: %04d-%02d-%02d\n",
           today->tm_year + 1900, today->tm_mon + 1, today->tm_mday);
    printf("年龄: %d岁\n", age);
    
    // 距离下个生日还有多少天
    struct tm next_birthday = birthday;
    next_birthday.tm_year = today->tm_year;
    if (today->tm_mon > birthday.tm_mon ||
        (today->tm_mon == birthday.tm_mon && today->tm_mday >= birthday.tm_mday)) {
        next_birthday.tm_year++;
    }
    
    time_t now_t = mktime(today);
    time_t next_t = mktime(&next_birthday);
    int days_to_birthday = (int)(difftime(next_t, now_t) / 86400);
    
    printf("距下个生日: %d天\n", days_to_birthday);
    
    printf("\n");
}

// 示例6：获取月份天数
void example_days_in_month() {
    printf("=== 示例6：获取月份天数 ===\n");
    
    // 测试2024年各月天数
    int year = 2024;
    
    for (int month = 1; month <= 12; month++) {
        struct tm date = {0};
        date.tm_year = year - 1900;
        date.tm_mon = month - 1;
        date.tm_mday = 1;  // 本月第1天
        date.tm_isdst = -1;
        
        mktime(&date);
        
        // 获取下个月第0天（即本月最后一天）
        date.tm_mon++;
        date.tm_mday = 0;
        mktime(&date);
        
        printf("%d年%2d月: %2d天\n", year, month, date.tm_mday);
    }
    
    printf("\n");
}

// 示例7：获取本周的开始和结束
void example_week_range() {
    printf("=== 示例7：获取本周的开始和结束 ===\n");
    
    time_t now = time(NULL);
    struct tm *today = localtime(&now);
    char buffer[100];
    
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %A", today);
    printf("今天: %s (星期%d)\n", buffer, today->tm_wday);
    
    // 本周周一（周日是0，周一是1）
    struct tm monday = *today;
    int days_since_monday = (today->tm_wday + 6) % 7;  // 距周一的天数
    monday.tm_mday -= days_since_monday;
    monday.tm_isdst = -1;
    mktime(&monday);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &monday);
    printf("本周周一: %s\n", buffer);
    
    // 本周周日
    struct tm sunday = monday;
    sunday.tm_mday += 6;
    sunday.tm_isdst = -1;
    mktime(&sunday);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &sunday);
    printf("本周周日: %s\n", buffer);
    
    printf("\n");
}

// 示例8：获取本月的开始和结束
void example_month_range() {
    printf("=== 示例8：获取本月的开始和结束 ===\n");
    
    time_t now = time(NULL);
    struct tm *today = localtime(&now);
    char buffer[100];
    
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", today);
    printf("今天: %s\n", buffer);
    
    // 本月第一天
    struct tm first_day = *today;
    first_day.tm_mday = 1;
    first_day.tm_isdst = -1;
    mktime(&first_day);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &first_day);
    printf("本月第一天: %s\n", buffer);
    
    // 本月最后一天
    struct tm last_day = first_day;
    last_day.tm_mon++;
    last_day.tm_mday = 0;  // 下月第0天 = 本月最后一天
    last_day.tm_isdst = -1;
    mktime(&last_day);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &last_day);
    printf("本月最后一天: %s\n", buffer);
    
    printf("\n");
}

// 示例9：时间戳和字符串互转
void example_timestamp_conversion() {
    printf("=== 示例9：时间戳和字符串互转 ===\n");
    
    // 时间戳 → 字符串
    time_t timestamp = 1735660800;  // 2025-01-01 00:00:00 UTC
    struct tm *utc_time = gmtime(&timestamp);
    char buffer[100];
    
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", utc_time);
    printf("时间戳 %ld → %s (UTC)\n", (long)timestamp, buffer);
    
    // 字符串 → 时间戳（手动解析）
    struct tm parsed = {0};
    parsed.tm_year = 2025 - 1900;
    parsed.tm_mon = 1 - 1;
    parsed.tm_mday = 1;
    parsed.tm_hour = 8;
    parsed.tm_min = 30;
    parsed.tm_sec = 0;
    parsed.tm_isdst = -1;
    
    time_t result = mktime(&parsed);
    printf("2025-01-01 08:30:00 → 时间戳 %ld\n", (long)result);
    
    printf("\n注意：C标准库没有strptime()（解析字符串）\n");
    printf("      Windows可用sscanf手动解析\n");
    printf("      Linux可用strptime()函数\n");
    
    printf("\n");
}

// 示例10：性能测试 - 不同时间操作的开销
void example_performance_test() {
    printf("=== 示例10：时间操作性能测试 ===\n");
    
    const int iterations = 1000000;
    clock_t start, end;
    double cpu_time;
    
    // 测试1：time()
    start = clock();
    for (int i = 0; i < iterations; i++) {
        volatile time_t t = time(NULL);
        (void)t;
    }
    end = clock();
    cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("time()      调用%d次: %.6f秒\n", iterations, cpu_time);
    
    // 测试2：localtime()
    time_t now = time(NULL);
    start = clock();
    for (int i = 0; i < iterations; i++) {
        volatile struct tm *t = localtime(&now);
        (void)t;
    }
    end = clock();
    cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("localtime() 调用%d次: %.6f秒\n", iterations, cpu_time);
    
    // 测试3：mktime()
    struct tm tm_test = {0};
    tm_test.tm_year = 2024 - 1900;
    tm_test.tm_mon = 0;
    tm_test.tm_mday = 1;
    tm_test.tm_isdst = -1;
    
    start = clock();
    for (int i = 0; i < iterations; i++) {
        volatile time_t t = mktime(&tm_test);
        (void)t;
    }
    end = clock();
    cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("mktime()    调用%d次: %.6f秒\n", iterations, cpu_time);
    
    printf("\n性能建议：\n");
    printf("  • time()速度最快，高频调用首选\n");
    printf("  • localtime/gmtime较慢，缓存结果\n");
    printf("  • mktime更慢，避免循环中频繁调用\n");
    
    printf("\n");
}

int main() {
    printf("╔═══════════════════════════════════════╗\n");
    printf("║   第11章：时间函数和相关库            ║\n");
    printf("║   11.4 时间计算和实用技巧             ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
    
    example_days_later();
    example_months_later();
    example_days_between();
    example_leap_year();
    example_calculate_age();
    example_days_in_month();
    example_week_range();
    example_month_range();
    example_timestamp_conversion();
    example_performance_test();
    
    printf("═════════════════════════════════════════\n");
    printf("时间计算技巧总结：\n");
    printf("═════════════════════════════════════════\n");
    printf("1. 日期加减：\n");
    printf("   • 简单情况：时间戳直接加减秒数\n");
    printf("   • 跨月/跨年：修改tm结构后调用mktime()\n");
    printf("\n");
    printf("2. 日期比较：\n");
    printf("   • 转为时间戳后直接比较\n");
    printf("   • 使用difftime()计算差值\n");
    printf("\n");
    printf("3. 常用计算：\n");
    printf("   • 年龄 = 当前年 - 出生年（考虑生日）\n");
    printf("   • 月天数：下月第0天 = 本月最后一天\n");
    printf("   • 闰年：能被400整除，或能被4但不能被100整除\n");
    printf("\n");
    printf("4. mktime()的神奇用法：\n");
    printf("   • tm_mday = 0  → 上月最后一天\n");
    printf("   • tm_mday = -1 → 上月倒数第二天\n");
    printf("   • tm_mday = 32 → 自动进位到下月\n");
    printf("   • tm_mon = -1  → 去年12月\n");
    printf("\n");
    printf("5. 性能优化：\n");
    printf("   • 缓存localtime()结果\n");
    printf("   • 批量计算用时间戳\n");
    printf("   • 避免循环中调用mktime()\n");
    printf("═════════════════════════════════════════\n");
    
    return 0;
}

/*
 * 编译和运行：
 *   gcc 11.4_time_calculation.c -o 11.4
 *   ./11.4
 * 
 * 学习要点：
 *   1. 掌握mktime()的自动修正功能
 *   2. 学会计算年龄、日期差等常用场景
 *   3. 理解时间计算的性能影响
 *   4. 实践中优先使用时间戳计算
 */
