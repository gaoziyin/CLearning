/*
 * 第十一章：时间函数和相关库
 * 11.3 strftime和日期时间格式化
 * 
 * 本文件展示strftime()函数的详细用法和格式化技巧
 * 编译命令：gcc 11.3_time_format.c -o 11.3
 */

#include <stdio.h>
#include <time.h>
#include <string.h>

// 示例1：strftime基本用法
void example_strftime_basic() {
    printf("=== 示例1：strftime基本用法 ===\n");
    
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    char buffer[100];
    
    // 基本格式化
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", local);
    printf("标准格式: %s\n", buffer);
    
    strftime(buffer, sizeof(buffer), "%Y年%m月%d日 %H时%M分%S秒", local);
    printf("中文格式: %s\n", buffer);
    
    printf("\nstrftime原型：\n");
    printf("  size_t strftime(char *s, size_t max, \n");
    printf("                  const char *format, \n");
    printf("                  const struct tm *tm);\n");
    printf("返回值：写入的字符数（不含\\0），失败返回0\n\n");
}

// 示例2：日期格式符
void example_date_specifiers() {
    printf("=== 示例2：日期格式符 ===\n");
    
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    char buffer[100];
    
    printf("年份格式：\n");
    strftime(buffer, sizeof(buffer), "%%Y = %Y (4位年份)", local);
    printf("  %s\n", buffer);
    strftime(buffer, sizeof(buffer), "%%y = %y (2位年份)", local);
    printf("  %s\n", buffer);
    
    printf("\n月份格式：\n");
    strftime(buffer, sizeof(buffer), "%%m = %m (数字月份 01-12)", local);
    printf("  %s\n", buffer);
    strftime(buffer, sizeof(buffer), "%%b = %b (月份缩写)", local);
    printf("  %s\n", buffer);
    strftime(buffer, sizeof(buffer), "%%B = %B (月份全称)", local);
    printf("  %s\n", buffer);
    
    printf("\n日期格式：\n");
    strftime(buffer, sizeof(buffer), "%%d = %d (月中日期 01-31)", local);
    printf("  %s\n", buffer);
    strftime(buffer, sizeof(buffer), "%%e = %e (月中日期  1-31，有空格)", local);
    printf("  %s\n", buffer);
    strftime(buffer, sizeof(buffer), "%%j = %j (年中日期 001-366)", local);
    printf("  %s\n", buffer);
    
    printf("\n");
}

// 示例3：时间格式符
void example_time_specifiers() {
    printf("=== 示例3：时间格式符 ===\n");
    
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    char buffer[100];
    
    printf("小时格式：\n");
    strftime(buffer, sizeof(buffer), "%%H = %H (24小时制 00-23)", local);
    printf("  %s\n", buffer);
    strftime(buffer, sizeof(buffer), "%%I = %I (12小时制 01-12)", local);
    printf("  %s\n", buffer);
    strftime(buffer, sizeof(buffer), "%%p = %p (AM/PM)", local);
    printf("  %s\n", buffer);
    
    printf("\n分钟和秒：\n");
    strftime(buffer, sizeof(buffer), "%%M = %M (分钟 00-59)", local);
    printf("  %s\n", buffer);
    strftime(buffer, sizeof(buffer), "%%S = %S (秒 00-60)", local);
    printf("  %s\n", buffer);
    
    printf("\n组合格式：\n");
    strftime(buffer, sizeof(buffer), "%%T = %T (等同于 %%H:%%M:%%S)", local);
    printf("  %s\n", buffer);
    strftime(buffer, sizeof(buffer), "%%R = %R (等同于 %%H:%%M)", local);
    printf("  %s\n", buffer);
    
    printf("\n");
}

// 示例4：星期格式符
void example_weekday_specifiers() {
    printf("=== 示例4：星期格式符 ===\n");
    
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    char buffer[100];
    
    strftime(buffer, sizeof(buffer), "%%w = %w (星期几 0-6，0是周日)", local);
    printf("%s\n", buffer);
    
    strftime(buffer, sizeof(buffer), "%%u = %u (星期几 1-7，1是周一)", local);
    printf("%s\n", buffer);
    
    strftime(buffer, sizeof(buffer), "%%a = %a (星期缩写)", local);
    printf("%s\n", buffer);
    
    strftime(buffer, sizeof(buffer), "%%A = %A (星期全称)", local);
    printf("%s\n", buffer);
    
    printf("\n周数格式：\n");
    strftime(buffer, sizeof(buffer), "%%U = %U (年中周数，周日为首日)", local);
    printf("%s\n", buffer);
    
    strftime(buffer, sizeof(buffer), "%%W = %W (年中周数，周一为首日)", local);
    printf("%s\n", buffer);
    
    printf("\n");
}

// 示例5：其他常用格式符
void example_other_specifiers() {
    printf("=== 示例5：其他常用格式符 ===\n");
    
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    char buffer[200];
    
    printf("日期时间组合：\n");
    strftime(buffer, sizeof(buffer), "%%c = %c (完整日期时间)", local);
    printf("%s\n", buffer);
    
    strftime(buffer, sizeof(buffer), "%%x = %x (日期表示)", local);
    printf("%s\n", buffer);
    
    strftime(buffer, sizeof(buffer), "%%X = %X (时间表示)", local);
    printf("%s\n", buffer);
    
    strftime(buffer, sizeof(buffer), "%%D = %D (等同于 %%m/%%d/%%y)", local);
    printf("%s\n", buffer);
    
    strftime(buffer, sizeof(buffer), "%%F = %F (等同于 %%Y-%%m-%%d)", local);
    printf("%s\n", buffer);
    
    printf("\n时区相关：\n");
    strftime(buffer, sizeof(buffer), "%%z = %z (UTC偏移)", local);
    printf("%s\n", buffer);
    
    strftime(buffer, sizeof(buffer), "%%Z = %Z (时区名称)", local);
    printf("%s\n", buffer);
    
    printf("\n特殊：\n");
    strftime(buffer, sizeof(buffer), "%%%% = %% (百分号本身)", local);
    printf("%s\n", buffer);
    
    strftime(buffer, sizeof(buffer), "%%n = %n (换行符)", local);
    printf("换行符示例: 第一行%s第二行\n", buffer);
    
    strftime(buffer, sizeof(buffer), "%%t = %t (制表符)", local);
    printf("制表符示例: 项1%s项2\n", buffer);
    
    printf("\n");
}

// 示例6：实用格式化模板
void example_practical_formats() {
    printf("=== 示例6：实用格式化模板 ===\n");
    
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    char buffer[100];
    
    printf("常用日期格式：\n");
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", local);
    printf("  ISO日期:     %s\n", buffer);
    
    strftime(buffer, sizeof(buffer), "%Y/%m/%d", local);
    printf("  斜杠分隔:    %s\n", buffer);
    
    strftime(buffer, sizeof(buffer), "%Y年%m月%d日", local);
    printf("  中文格式:    %s\n", buffer);
    
    strftime(buffer, sizeof(buffer), "%m/%d/%Y", local);
    printf("  美式格式:    %s\n", buffer);
    
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", local);
    printf("  欧式格式:    %s\n", buffer);
    
    printf("\n常用时间格式：\n");
    strftime(buffer, sizeof(buffer), "%H:%M:%S", local);
    printf("  24小时制:    %s\n", buffer);
    
    strftime(buffer, sizeof(buffer), "%I:%M:%S %p", local);
    printf("  12小时制:    %s\n", buffer);
    
    strftime(buffer, sizeof(buffer), "%H时%M分%S秒", local);
    printf("  中文格式:    %s\n", buffer);
    
    printf("\n完整格式：\n");
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", local);
    printf("  数据库格式:  %s\n", buffer);
    
    strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%S%z", local);
    printf("  ISO 8601:    %s\n", buffer);
    
    strftime(buffer, sizeof(buffer), "%A, %B %d, %Y %I:%M %p", local);
    printf("  英文格式:    %s\n", buffer);
    
    printf("\n文件名友好格式：\n");
    strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", local);
    printf("  时间戳:      %s\n", buffer);
    
    strftime(buffer, sizeof(buffer), "backup_%Y%m%d.tar.gz", local);
    printf("  备份文件名:  %s\n", buffer);
    
    printf("\n");
}

// 示例7：日志时间格式
void example_log_formats() {
    printf("=== 示例7：日志时间格式 ===\n");
    
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    char buffer[200];
    
    // Apache日志格式
    strftime(buffer, sizeof(buffer), "[%d/%b/%Y:%H:%M:%S %z]", local);
    printf("Apache格式:  %s\n", buffer);
    
    // syslog格式
    strftime(buffer, sizeof(buffer), "%b %d %H:%M:%S", local);
    printf("syslog格式:  %s\n", buffer);
    
    // 自定义应用日志
    strftime(buffer, sizeof(buffer), "[%Y-%m-%d %H:%M:%S]", local);
    printf("应用日志:    %s [INFO] Application started\n", buffer);
    
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", local);
    printf("简单日志:    %s | User login successful\n", buffer);
    
    printf("\n");
}

// 示例8：不同语言环境下的格式化
void example_locale_formats() {
    printf("=== 示例8：不同语言环境格式 ===\n");
    
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    char buffer[100];
    
    printf("当前系统locale下的格式：\n");
    
    strftime(buffer, sizeof(buffer), "%c", local);
    printf("%%c (本地完整): %s\n", buffer);
    
    strftime(buffer, sizeof(buffer), "%x", local);
    printf("%%x (本地日期): %s\n", buffer);
    
    strftime(buffer, sizeof(buffer), "%X", local);
    printf("%%X (本地时间): %s\n", buffer);
    
    strftime(buffer, sizeof(buffer), "%A", local);
    printf("%%A (星期全称): %s\n", buffer);
    
    strftime(buffer, sizeof(buffer), "%B", local);
    printf("%%B (月份全称): %s\n", buffer);
    
    printf("\n注意：%%a/%%A/%%b/%%B的输出依赖系统locale设置\n");
    printf("中文Windows可能显示为中文，Linux可能为英文\n\n");
}

// 示例9：缓冲区大小处理
void example_buffer_handling() {
    printf("=== 示例9：缓冲区大小处理 ===\n");
    
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    
    // 测试不同缓冲区大小
    char small_buf[10];
    char large_buf[100];
    
    size_t result1 = strftime(small_buf, sizeof(small_buf), 
                              "%Y-%m-%d %H:%M:%S", local);
    printf("小缓冲区(10字节): ");
    if (result1 == 0) {
        printf("失败（缓冲区太小）\n");
    } else {
        printf("成功，写入%zu字节: %s\n", result1, small_buf);
    }
    
    size_t result2 = strftime(large_buf, sizeof(large_buf), 
                              "%Y-%m-%d %H:%M:%S", local);
    printf("大缓冲区(100字节): ");
    if (result2 == 0) {
        printf("失败\n");
    } else {
        printf("成功，写入%zu字节: %s\n", result2, large_buf);
    }
    
    printf("\n⚠ 最佳实践：\n");
    printf("  • 缓冲区至少64字节\n");
    printf("  • 检查返回值，0表示失败\n");
    printf("  • 使用sizeof避免硬编码\n\n");
}

// 示例10：实际应用场景
void example_real_world_usage() {
    printf("=== 示例10：实际应用场景 ===\n");
    
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    char buffer[200];
    
    // 1. 生成唯一文件名
    strftime(buffer, sizeof(buffer), "report_%Y%m%d_%H%M%S.txt", local);
    printf("报表文件名: %s\n", buffer);
    
    // 2. 邮件头部时间
    strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S %z", local);
    printf("邮件Date:   %s\n", buffer);
    
    // 3. HTTP日期头
    struct tm *utc = gmtime(&now);
    strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S GMT", utc);
    printf("HTTP Date:  %s\n", buffer);
    
    // 4. 用户友好显示
    strftime(buffer, sizeof(buffer), 
             "%Y年%m月%d日 %A %H:%M", local);
    printf("用户显示:   %s\n", buffer);
    
    // 5. 数据库插入
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", local);
    printf("SQL INSERT: '%s'\n", buffer);
    
    printf("\n");
}

int main() {
    printf("╔═══════════════════════════════════════╗\n");
    printf("║   第11章：时间函数和相关库            ║\n");
    printf("║   11.3 strftime日期时间格式化         ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
    
    example_strftime_basic();
    example_date_specifiers();
    example_time_specifiers();
    example_weekday_specifiers();
    example_other_specifiers();
    example_practical_formats();
    example_log_formats();
    example_locale_formats();
    example_buffer_handling();
    example_real_world_usage();
    
    printf("═════════════════════════════════════════\n");
    printf("strftime格式符速查表：\n");
    printf("═════════════════════════════════════════\n");
    printf("日期：\n");
    printf("  %%Y - 4位年份 (2024)    %%y - 2位年份 (24)\n");
    printf("  %%m - 月份 (01-12)      %%b - 月份缩写 (Jan)\n");
    printf("  %%B - 月份全称 (January) %%d - 日期 (01-31)\n");
    printf("  %%j - 年中日期 (001-366)\n");
    printf("\n");
    printf("时间：\n");
    printf("  %%H - 24小时 (00-23)    %%I - 12小时 (01-12)\n");
    printf("  %%M - 分钟 (00-59)      %%S - 秒 (00-60)\n");
    printf("  %%p - AM/PM             %%T - HH:MM:SS\n");
    printf("\n");
    printf("星期：\n");
    printf("  %%w - 星期数字 (0-6)    %%u - 星期数字 (1-7)\n");
    printf("  %%a - 星期缩写 (Mon)    %%A - 星期全称 (Monday)\n");
    printf("\n");
    printf("组合格式：\n");
    printf("  %%c - 完整日期时间      %%x - 本地日期\n");
    printf("  %%X - 本地时间          %%F - YYYY-MM-DD\n");
    printf("  %%D - MM/DD/YY\n");
    printf("\n");
    printf("常用模板：\n");
    printf("  日志: [%%Y-%%m-%%d %%H:%%M:%%S]\n");
    printf("  文件: %%Y%%m%%d_%%H%%M%%S\n");
    printf("  ISO:  %%Y-%%m-%%dT%%H:%%M:%%S%%z\n");
    printf("═════════════════════════════════════════\n");
    
    return 0;
}

/*
 * 编译和运行：
 *   gcc 11.3_time_format.c -o 11.3
 *   ./11.3
 * 
 * 学习重点：
 *   1. 熟记常用格式符（%%Y %%m %%d %%H %%M %%S）
 *   2. 区分%%H(24小时)和%%I(12小时)
 *   3. 注意缓冲区大小，检查返回值
 *   4. 掌握实际场景的格式化模板
 */
