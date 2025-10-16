/*
 * 第八章：高级主题
 * 8.5 标准库函数
 * 
 * 学习目标：
 * 1. 了解C标准库的组成
 * 2. 掌握常用标准库函数
 * 3. 学习数学、时间、字符串等库
 * 4. 理解标准库的最佳使用方式
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#include <assert.h>

// 比较函数（用于qsort）
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// 比较函数（降序）
int compareDesc(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    printf("=== C标准库函数 ===\n\n");
    
    // 1. 标准库概览
    printf("1. C标准库头文件:\n");
    printf("<stdio.h>   - 输入输出\n");
    printf("<stdlib.h>  - 实用工具\n");
    printf("<string.h>  - 字符串处理\n");
    printf("<math.h>    - 数学函数\n");
    printf("<time.h>    - 时间日期\n");
    printf("<ctype.h>   - 字符处理\n");
    printf("<limits.h>  - 类型限制\n");
    printf("<float.h>   - 浮点限制\n");
    printf("<assert.h>  - 断言\n");
    printf("<errno.h>   - 错误处理\n\n");
    
    // 2. 数学函数 <math.h>
    printf("2. 数学函数 (math.h):\n");
    double x = 2.0, y = 3.0;
    
    printf("pow(%.1f, %.1f) = %.2f\n", x, y, pow(x, y));
    printf("sqrt(16) = %.2f\n", sqrt(16.0));
    printf("ceil(3.2) = %.1f\n", ceil(3.2));
    printf("floor(3.8) = %.1f\n", floor(3.8));
    printf("fabs(-5.5) = %.1f\n", fabs(-5.5));
    printf("sin(π/2) = %.2f\n", sin(M_PI / 2));
    printf("cos(π) = %.2f\n", cos(M_PI));
    printf("log(2.718) = %.2f\n", log(2.718));
    printf("log10(100) = %.1f\n", log10(100.0));
    printf("exp(1) = %.2f\n", exp(1.0));
    printf("\n");
    
    // 3. 随机数 <stdlib.h>
    printf("3. 随机数函数:\n");
    
    // 设置随机数种子
    srand((unsigned int)time(NULL));
    
    printf("5个随机数 [0-%d]: ", RAND_MAX);
    for (int i = 0; i < 5; i++) {
        printf("%d ", rand());
    }
    printf("\n");
    
    printf("5个随机数 [1-100]: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", rand() % 100 + 1);
    }
    printf("\n\n");
    
    // 4. 类型转换 <stdlib.h>
    printf("4. 字符串转换函数:\n");
    char str1[] = "123";
    char str2[] = "45.67";
    char str3[] = "  89  ";
    
    int num1 = atoi(str1);
    double num2 = atof(str2);
    long num3 = atol(str3);
    
    printf("atoi(\"%s\") = %d\n", str1, num1);
    printf("atof(\"%s\") = %.2f\n", str2, num2);
    printf("atol(\"%s\") = %ld\n", str3, num3);
    
    // strtol - 更安全的转换
    char *endptr;
    long num4 = strtol("123abc", &endptr, 10);
    printf("strtol(\"123abc\") = %ld, 剩余: \"%s\"\n", num4, endptr);
    printf("\n");
    
    // 5. 内存管理 <stdlib.h>
    printf("5. 内存分配函数:\n");
    int *arr = (int *)malloc(5 * sizeof(int));
    if (arr != NULL) {
        printf("malloc分配成功\n");
        for (int i = 0; i < 5; i++) {
            arr[i] = i * 10;
        }
        printf("数组: ");
        for (int i = 0; i < 5; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        free(arr);
        printf("内存已释放\n");
    }
    printf("\n");
    
    // 6. 排序和搜索 <stdlib.h>
    printf("6. qsort排序:\n");
    int numbers[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(numbers) / sizeof(numbers[0]);
    
    printf("排序前: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    qsort(numbers, n, sizeof(int), compare);
    
    printf("排序后: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n\n");
    
    // 7. 二分查找 <stdlib.h>
    printf("7. bsearch二分查找:\n");
    int key = 25;
    int *result = (int *)bsearch(&key, numbers, n, sizeof(int), compare);
    
    if (result != NULL) {
        printf("找到 %d，位置: %ld\n", key, result - numbers);
    } else {
        printf("未找到 %d\n", key);
    }
    printf("\n");
    
    // 8. 字符串函数 <string.h>
    printf("8. 字符串函数:\n");
    char dest[50] = "Hello";
    char src[] = " World";
    
    printf("原始: \"%s\"\n", dest);
    
    strcat(dest, src);
    printf("strcat后: \"%s\"\n", dest);
    
    printf("strlen: %zu\n", strlen(dest));
    printf("strcmp(\"abc\", \"abd\"): %d\n", strcmp("abc", "abd"));
    
    char copy[50];
    strcpy(copy, dest);
    printf("strcpy后: \"%s\"\n", copy);
    
    char *pos = strchr(dest, 'W');
    if (pos) {
        printf("strchr找到'W'的位置: %ld\n", pos - dest);
    }
    printf("\n");
    
    // 9. 字符分类 <ctype.h>
    printf("9. 字符处理函数:\n");
    char ch = 'A';
    
    printf("字符: '%c'\n", ch);
    printf("isalpha: %d\n", isalpha(ch));
    printf("isdigit: %d\n", isdigit(ch));
    printf("isupper: %d\n", isupper(ch));
    printf("islower: %d\n", islower(ch));
    printf("tolower: '%c'\n", tolower(ch));
    printf("toupper: '%c'\n", toupper('a'));
    printf("\n");
    
    // 10. 时间函数 <time.h>
    printf("10. 时间日期函数:\n");
    
    // 获取当前时间
    time_t now = time(NULL);
    printf("Unix时间戳: %ld\n", (long)now);
    
    // 转换为字符串
    char *timeStr = ctime(&now);
    printf("当前时间: %s", timeStr);
    
    // 结构化时间
    struct tm *localTime = localtime(&now);
    printf("年: %d\n", localTime->tm_year + 1900);
    printf("月: %d\n", localTime->tm_mon + 1);
    printf("日: %d\n", localTime->tm_mday);
    printf("时: %d\n", localTime->tm_hour);
    printf("分: %d\n", localTime->tm_min);
    printf("秒: %d\n", localTime->tm_sec);
    
    // 格式化时间
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);
    printf("格式化: %s\n", buffer);
    printf("\n");
    
    // 11. 时间测量
    printf("11. 性能测量:\n");
    clock_t start = clock();
    
    // 执行一些操作
    int sum = 0;
    for (int i = 0; i < 1000000; i++) {
        sum += i;
    }
    
    clock_t end = clock();
    double cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("执行时间: %.6f 秒\n", cpu_time);
    printf("结果: %d\n", sum);
    printf("\n");
    
    // 12. 类型限制 <limits.h>
    printf("12. 整数类型限制:\n");
    printf("CHAR_BIT (位数): %d\n", CHAR_BIT);
    printf("CHAR_MIN: %d\n", CHAR_MIN);
    printf("CHAR_MAX: %d\n", CHAR_MAX);
    printf("INT_MIN: %d\n", INT_MIN);
    printf("INT_MAX: %d\n", INT_MAX);
    printf("LONG_MIN: %ld\n", LONG_MIN);
    printf("LONG_MAX: %ld\n", LONG_MAX);
    printf("\n");
    
    // 13. 浮点限制 <float.h>
    printf("13. 浮点类型限制:\n");
    printf("FLT_MIN: %e\n", FLT_MIN);
    printf("FLT_MAX: %e\n", FLT_MAX);
    printf("DBL_MIN: %e\n", DBL_MIN);
    printf("DBL_MAX: %e\n", DBL_MAX);
    printf("FLT_DIG (有效位数): %d\n", FLT_DIG);
    printf("DBL_DIG (有效位数): %d\n", DBL_DIG);
    printf("\n");
    
    // 14. 断言 <assert.h>
    printf("14. 断言:\n");
    int value = 10;
    assert(value > 0);  // 通过
    printf("断言通过: value = %d > 0\n", value);
    
    // assert(value < 0);  // 会失败并终止程序
    printf("\n");
    
    // 15. 程序终止 <stdlib.h>
    printf("15. 程序控制:\n");
    printf("exit(0)  - 正常退出\n");
    printf("exit(1)  - 错误退出\n");
    printf("abort()  - 异常终止\n");
    printf("atexit() - 注册退出函数\n");
    printf("\n");
    
    // 16. 环境变量 <stdlib.h>
    printf("16. 环境变量:\n");
    char *path = getenv("PATH");
    if (path) {
        printf("PATH前50字符: %.50s...\n", path);
    }
    
    char *home = getenv("HOME");
    if (home) {
        printf("HOME: %s\n", home);
    }
    printf("\n");
    
    // 17. 绝对值函数 <stdlib.h>
    printf("17. 绝对值函数:\n");
    printf("abs(-10) = %d\n", abs(-10));
    printf("labs(-1000000L) = %ld\n", labs(-1000000L));
    printf("fabs(-3.14) = %.2f\n", fabs(-3.14));
    printf("\n");
    
    // 18. 字符串查找 <string.h>
    printf("18. 字符串查找:\n");
    char text[] = "Hello World Program";
    
    char *found = strstr(text, "World");
    if (found) {
        printf("找到\"World\"，位置: %ld\n", found - text);
    }
    
    char *lastSpace = strrchr(text, ' ');
    if (lastSpace) {
        printf("最后一个空格位置: %ld\n", lastSpace - text);
    }
    printf("\n");
    
    // 19. 内存操作 <string.h>
    printf("19. 内存操作函数:\n");
    char buffer1[20] = "Hello";
    char buffer2[20];
    
    // 复制内存
    memcpy(buffer2, buffer1, strlen(buffer1) + 1);
    printf("memcpy: %s\n", buffer2);
    
    // 移动内存（可重叠）
    memmove(buffer1 + 2, buffer1, 3);
    printf("memmove: %s\n", buffer1);
    
    // 设置内存
    char buffer3[10];
    memset(buffer3, 'A', 9);
    buffer3[9] = '\0';
    printf("memset: %s\n", buffer3);
    
    // 比较内存
    int cmp = memcmp("abc", "abd", 3);
    printf("memcmp: %d\n", cmp);
    printf("\n");
    
    // 20. 实用函数总结
    printf("20. 常用标准库函数分类:\n\n");
    
    printf("输入输出 (stdio.h):\n");
    printf("  printf, scanf, fprintf, fscanf\n");
    printf("  fopen, fclose, fread, fwrite\n");
    printf("  fgets, fputs, fgetc, fputc\n\n");
    
    printf("字符串 (string.h):\n");
    printf("  strlen, strcpy, strcat, strcmp\n");
    printf("  strchr, strstr, strtok\n");
    printf("  memcpy, memmove, memset, memcmp\n\n");
    
    printf("数学 (math.h):\n");
    printf("  pow, sqrt, sin, cos, tan\n");
    printf("  log, exp, ceil, floor, fabs\n\n");
    
    printf("工具 (stdlib.h):\n");
    printf("  malloc, calloc, realloc, free\n");
    printf("  atoi, atof, strtol, strtod\n");
    printf("  rand, srand, qsort, bsearch\n");
    printf("  exit, abort, system, getenv\n\n");
    
    printf("时间 (time.h):\n");
    printf("  time, clock, localtime\n");
    printf("  strftime, difftime\n\n");
    
    printf("字符 (ctype.h):\n");
    printf("  isalpha, isdigit, isupper, islower\n");
    printf("  toupper, tolower, isspace\n\n");
    
    printf("断言 (assert.h):\n");
    printf("  assert\n\n");
    
    printf("编译时使用 -lm 链接数学库（Unix/Linux）\n");
    
    return 0;
}

/*
 * 知识点总结：
 * 
 * C标准库概述：
 * 
 * 标准库：
 * - ISO C标准定义
 * - 所有C编译器必须提供
 * - 跨平台可移植
 * - 高质量实现
 * 
 * 主要头文件：
 * 
 * <stdio.h> - 标准输入输出：
 * - printf, scanf
 * - fprintf, fscanf
 * - fopen, fclose
 * - fread, fwrite
 * - fgets, fputs, fgetc, fputc
 * - fseek, ftell, rewind
 * - perror
 * 
 * <stdlib.h> - 通用工具：
 * - malloc, calloc, realloc, free
 * - atoi, atof, atol
 * - strtol, strtod
 * - rand, srand
 * - qsort, bsearch
 * - abs, labs
 * - exit, abort, atexit
 * - system, getenv
 * 
 * <string.h> - 字符串处理：
 * - strlen, strcpy, strncpy
 * - strcat, strncat
 * - strcmp, strncmp
 * - strchr, strrchr, strstr
 * - strtok
 * - memcpy, memmove
 * - memset, memcmp
 * 
 * <math.h> - 数学函数：
 * - pow, sqrt
 * - sin, cos, tan, asin, acos, atan
 * - log, log10, exp
 * - ceil, floor, round
 * - fabs, fmod
 * 
 * <time.h> - 时间日期：
 * - time, clock
 * - localtime, gmtime
 * - strftime, mktime
 * - difftime
 * 
 * <ctype.h> - 字符处理：
 * - isalpha, isdigit, isalnum
 * - isupper, islower, isspace
 * - toupper, tolower
 * 
 * <limits.h> - 类型限制：
 * - CHAR_MIN, CHAR_MAX
 * - INT_MIN, INT_MAX
 * - LONG_MIN, LONG_MAX
 * 
 * <float.h> - 浮点限制：
 * - FLT_MIN, FLT_MAX
 * - DBL_MIN, DBL_MAX
 * - FLT_DIG, DBL_DIG
 * 
 * <assert.h> - 断言：
 * - assert(expression)
 * 
 * <errno.h> - 错误处理：
 * - errno全局变量
 * - 错误码宏
 * 
 * 数学函数详解：
 * 
 * 基本运算：
 * pow(x, y)     x的y次方
 * sqrt(x)       平方根
 * fabs(x)       绝对值
 * 
 * 三角函数：
 * sin(x)        正弦
 * cos(x)        余弦
 * tan(x)        正切
 * asin(x)       反正弦
 * acos(x)       反余弦
 * atan(x)       反正切
 * atan2(y, x)   反正切（两参数）
 * 
 * 指数对数：
 * exp(x)        e^x
 * log(x)        自然对数
 * log10(x)      常用对数
 * 
 * 取整：
 * ceil(x)       向上取整
 * floor(x)      向下取整
 * round(x)      四舍五入
 * trunc(x)      截断
 * 
 * 其他：
 * fmod(x, y)    浮点取模
 * hypot(x, y)   斜边长度
 * 
 * 随机数：
 * 
 * 生成随机数：
 * srand(seed);           设置种子
 * int r = rand();        生成随机数
 * 
 * 范围随机数：
 * rand() % n             [0, n-1]
 * rand() % n + 1         [1, n]
 * rand() % (max-min+1) + min  [min, max]
 * 
 * 随机种子：
 * srand(time(NULL));     使用当前时间
 * 
 * 注意：
 * - rand()质量一般
 * - 不适合安全相关
 * - C11提供更好的方案
 * 
 * 字符串转换：
 * 
 * 简单转换：
 * atoi(str)     字符串转int
 * atof(str)     字符串转double
 * atol(str)     字符串转long
 * 
 * 特点：
 * - 简单易用
 * - 不检查错误
 * - 不知道转换到哪里
 * 
 * 安全转换：
 * char *endptr;
 * long num = strtol(str, &endptr, 10);
 * if (*endptr != '\0') {
 *     // 有非数字字符
 * }
 * 
 * 类似函数：
 * strtol   字符串转long
 * strtoul  字符串转unsigned long
 * strtod   字符串转double
 * 
 * 排序和查找：
 * 
 * qsort():
 * void qsort(void *base, size_t nmemb, 
 *            size_t size, int (*compar)(const void *, const void *));
 * 
 * 用法：
 * int compare(const void *a, const void *b) {
 *     return (*(int*)a - *(int*)b);
 * }
 * qsort(arr, n, sizeof(int), compare);
 * 
 * bsearch():
 * void *bsearch(const void *key, const void *base, 
 *               size_t nmemb, size_t size,
 *               int (*compar)(const void *, const void *));
 * 
 * 注意：
 * - 数组必须已排序
 * - 使用相同的比较函数
 * 
 * 时间处理：
 * 
 * 获取时间：
 * time_t now = time(NULL);
 * 
 * 转换为字符串：
 * char *str = ctime(&now);
 * 
 * 结构化时间：
 * struct tm *t = localtime(&now);
 * t->tm_year + 1900  年
 * t->tm_mon + 1      月
 * t->tm_mday         日
 * t->tm_hour         时
 * t->tm_min          分
 * t->tm_sec          秒
 * 
 * 格式化：
 * char buf[80];
 * strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", t);
 * 
 * 性能测量：
 * clock_t start = clock();
 * // 代码
 * clock_t end = clock();
 * double time = (double)(end - start) / CLOCKS_PER_SEC;
 * 
 * 字符分类：
 * 
 * isalpha(c)   字母
 * isdigit(c)   数字
 * isalnum(c)   字母或数字
 * isspace(c)   空白字符
 * isupper(c)   大写字母
 * islower(c)   小写字母
 * ispunct(c)   标点符号
 * 
 * 转换：
 * toupper(c)   转大写
 * tolower(c)   转小写
 * 
 * 内存操作：
 * 
 * memcpy():
 * - 复制内存
 * - 不能重叠
 * - 快速
 * 
 * memmove():
 * - 复制内存
 * - 可以重叠
 * - 稍慢
 * 
 * memset():
 * - 设置内存
 * - 通常用于初始化
 * 
 * memcmp():
 * - 比较内存
 * - 字节级比较
 * 
 * 程序控制：
 * 
 * exit(code):
 * - 正常退出
 * - 调用atexit注册的函数
 * - 关闭文件
 * - 返回状态码
 * 
 * abort():
 * - 异常终止
 * - 不调用atexit
 * - 生成core dump
 * 
 * atexit(func):
 * - 注册退出函数
 * - exit时调用
 * - 后注册先调用
 * 
 * 最佳实践：
 * 
 * 1. 优先使用标准库
 * 2. 检查返回值
 * 3. 处理错误
 * 4. 注意边界情况
 * 5. 使用安全版本
 * 6. 理解函数行为
 * 7. 阅读文档
 * 8. 考虑性能
 * 
 * 常见错误：
 * 
 * 1. 不检查返回值
 * 2. 缓冲区溢出
 * 3. 字符串未终止
 * 4. 忘记初始化
 * 5. 类型不匹配
 * 6. 精度问题
 * 
 * 注意事项：
 * 
 * 1. 数学库链接：
 *    gcc -lm file.c
 * 
 * 2. 线程安全：
 *    某些函数不是线程安全的
 * 
 * 3. 缓冲区大小：
 *    总是检查边界
 * 
 * 4. 平台差异：
 *    某些函数可能有差异
 * 
 * 扩展库：
 * 
 * POSIX：
 * - 更多函数
 * - Unix/Linux特定
 * 
 * Windows：
 * - Windows API
 * - 特定于Windows
 * 
 * 第三方库：
 * - 更专业功能
 * - 需要额外安装
 */
