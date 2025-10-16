/*
 * 第八章：高级主题
 * 8.2 预处理器
 * 
 * 学习目标：
 * 1. 理解预处理器的作用
 * 2. 掌握宏定义和条件编译
 * 3. 学习文件包含和预定义宏
 * 4. 了解预处理器的高级应用
 */

#include <stdio.h>
#include <stdlib.h>

// 1. 简单宏定义
#define PI 3.14159
#define MAX_SIZE 100
#define BUFFER_SIZE 1024

// 2. 带参数的宏
#define SQUARE(x) ((x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(x) ((x) < 0 ? -(x) : (x))

// 3. 多行宏（使用反斜杠）
#define PRINT_ARRAY(arr, size) \
    do { \
        printf("["); \
        for (int i = 0; i < (size); i++) { \
            printf("%d", (arr)[i]); \
            if (i < (size) - 1) printf(", "); \
        } \
        printf("]\n"); \
    } while(0)

// 4. 字符串化运算符 #
#define TO_STRING(x) #x
#define PRINT_VAR(var) printf(#var " = %d\n", var)

// 5. 连接运算符 ##
#define CONCAT(a, b) a##b
#define VAR_NAME(prefix, num) prefix##num

// 6. 条件编译
#define DEBUG 1
#define VERSION 2

#if VERSION == 1
    #define FEATURE_A
#elif VERSION == 2
    #define FEATURE_B
#else
    #define FEATURE_C
#endif

// 7. 编译器检测
#ifdef _WIN32
    #define OS_NAME "Windows"
#elif defined(__linux__)
    #define OS_NAME "Linux"
#elif defined(__APPLE__)
    #define OS_NAME "macOS"
#else
    #define OS_NAME "Unknown"
#endif

// 8. 防止头文件重复包含
#ifndef MYHEADER_H
#define MYHEADER_H
// 头文件内容
#endif

// 9. 函数式宏
#define IS_EVEN(n) (((n) % 2) == 0)
#define IS_ODD(n) (((n) % 2) != 0)
#define SWAP(a, b, type) \
    do { \
        type temp = (a); \
        (a) = (b); \
        (b) = temp; \
    } while(0)

// 10. 调试宏
#if DEBUG
    #define DEBUG_PRINT(fmt, ...) \
        printf("DEBUG %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
    #define DEBUG_PRINT(fmt, ...)
#endif

// 11. 断言宏
#define ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "Assertion failed: %s\n", message); \
            fprintf(stderr, "File: %s, Line: %d\n", __FILE__, __LINE__); \
            exit(1); \
        } \
    } while(0)

int main() {
    printf("=== 预处理器 ===\n\n");
    
    // 1. 简单宏定义
    printf("1. 简单宏定义:\n");
    printf("PI = %.5f\n", PI);
    printf("MAX_SIZE = %d\n", MAX_SIZE);
    
    double radius = 5.0;
    double area = PI * radius * radius;
    printf("半径%.1f的圆面积: %.2f\n\n", radius, area);
    
    // 2. 带参数的宏
    printf("2. 带参数的宏:\n");
    int a = 5, b = 3;
    
    printf("SQUARE(%d) = %d\n", a, SQUARE(a));
    printf("MAX(%d, %d) = %d\n", a, b, MAX(a, b));
    printf("MIN(%d, %d) = %d\n", a, b, MIN(a, b));
    printf("ABS(%d) = %d\n", -10, ABS(-10));
    printf("\n");
    
    // 3. 宏的陷阱
    printf("3. 宏使用注意事项:\n");
    
    // 错误：没有括号
    // #define BAD_SQUARE(x) x * x
    // BAD_SQUARE(1 + 2) 展开为 1 + 2 * 1 + 2 = 5（错误）
    
    // 正确：有括号
    // SQUARE(1 + 2) 展开为 ((1 + 2) * (1 + 2)) = 9（正确）
    
    printf("SQUARE(1 + 2) = %d (正确结果9)\n", SQUARE(1 + 2));
    printf("总是在宏参数外加括号！\n\n");
    
    // 4. 多行宏
    printf("4. 多行宏:\n");
    int arr[] = {1, 2, 3, 4, 5};
    printf("数组: ");
    PRINT_ARRAY(arr, 5);
    printf("\n");
    
    // 5. 字符串化 #
    printf("5. 字符串化运算符 #:\n");
    int value = 42;
    
    printf("TO_STRING(Hello) = %s\n", TO_STRING(Hello));
    printf("TO_STRING(123) = %s\n", TO_STRING(123));
    
    PRINT_VAR(value);
    printf("\n");
    
    // 6. 连接运算符 ##
    printf("6. 连接运算符 ##:\n");
    int CONCAT(var, 1) = 10;
    int CONCAT(var, 2) = 20;
    int CONCAT(var, 3) = 30;
    
    printf("var1 = %d\n", var1);
    printf("var2 = %d\n", var2);
    printf("var3 = %d\n", var3);
    printf("\n");
    
    // 7. 条件编译
    printf("7. 条件编译:\n");
    
    #ifdef DEBUG
        printf("调试模式已启用\n");
    #endif
    
    #ifdef FEATURE_B
        printf("功能B已启用（VERSION=2）\n");
    #endif
    
    printf("操作系统: %s\n\n", OS_NAME);
    
    // 8. 预定义宏
    printf("8. 预定义宏:\n");
    printf("文件名: %s\n", __FILE__);
    printf("行号: %d\n", __LINE__);
    printf("日期: %s\n", __DATE__);
    printf("时间: %s\n", __TIME__);
    
    #ifdef __STDC__
        printf("符合标准C\n");
    #endif
    
    printf("\n");
    
    // 9. 函数式宏
    printf("9. 函数式宏:\n");
    
    for (int i = 1; i <= 5; i++) {
        if (IS_EVEN(i)) {
            printf("%d 是偶数\n", i);
        } else {
            printf("%d 是奇数\n", i);
        }
    }
    printf("\n");
    
    // 10. SWAP宏
    printf("10. SWAP宏:\n");
    int x = 10, y = 20;
    printf("交换前: x=%d, y=%d\n", x, y);
    
    SWAP(x, y, int);
    printf("交换后: x=%d, y=%d\n\n", x, y);
    
    // 11. 调试宏
    printf("11. 调试宏:\n");
    DEBUG_PRINT("程序启动");
    DEBUG_PRINT("变量值: %d", value);
    printf("\n");
    
    // 12. 断言
    printf("12. 断言宏:\n");
    int num = 5;
    ASSERT(num > 0, "num必须大于0");
    printf("断言通过: num = %d\n\n", num);
    
    // 如果取消注释，程序会退出
    // ASSERT(num < 0, "num必须小于0");
    
    // 13. #undef取消定义
    printf("13. #undef取消宏定义:\n");
    #define TEMP 100
    printf("TEMP = %d\n", TEMP);
    
    #undef TEMP
    #define TEMP 200
    printf("重定义后 TEMP = %d\n\n", TEMP);
    
    // 14. #ifdef vs #if defined
    printf("14. 条件编译语法:\n");
    
    #ifdef DEBUG
        printf("#ifdef DEBUG: 真\n");
    #endif
    
    #if defined(DEBUG)
        printf("#if defined(DEBUG): 真\n");
    #endif
    
    #if defined(DEBUG) && DEBUG == 1
        printf("#if defined(DEBUG) && DEBUG == 1: 真\n");
    #endif
    
    printf("\n");
    
    // 15. #error指令
    printf("15. #error预处理指令:\n");
    printf("用于编译时错误检查\n");
    
    #if MAX_SIZE < 10
        #error "MAX_SIZE太小，必须至少为10"
    #endif
    
    printf("MAX_SIZE检查通过\n\n");
    
    // 16. #pragma指令
    printf("16. #pragma指令:\n");
    printf("#pragma once - 防止重复包含\n");
    printf("#pragma pack - 结构体对齐\n");
    printf("#pragma warning - 警告控制\n\n");
    
    // 17. 可变参数宏
    printf("17. 可变参数宏:\n");
    #define LOG(format, ...) \
        printf("[LOG] " format "\n", ##__VA_ARGS__)
    
    LOG("程序启动");
    LOG("用户ID: %d", 1001);
    LOG("用户: %s, 年龄: %d", "张三", 25);
    printf("\n");
    
    // 18. 宏 vs 函数
    printf("18. 宏 vs 函数对比:\n");
    printf("宏的优点:\n");
    printf("  - 无函数调用开销\n");
    printf("  - 类型无关\n");
    printf("  - 编译时计算\n");
    printf("\n宏的缺点:\n");
    printf("  - 无类型检查\n");
    printf("  - 代码膨胀\n");
    printf("  - 调试困难\n");
    printf("  - 可能有副作用\n\n");
    
    // 19. 宏的副作用
    printf("19. 宏的副作用示例:\n");
    int count = 5;
    
    // 危险：SQUARE(count++)会展开为((count++) * (count++))
    // count会被增加两次！
    printf("正确用法: 先计算，再传入宏\n");
    int temp = count;
    printf("SQUARE(%d) = %d\n\n", temp, SQUARE(temp));
    
    // 20. 编译配置
    printf("20. 使用宏进行编译配置:\n");
    
    #ifdef FEATURE_B
        printf("启用功能B\n");
        printf("这是VERSION 2的特性\n");
    #endif
    
    printf("\n编译时配置选项:\n");
    printf("  -DDEBUG=1     启用调试\n");
    printf("  -DVERSION=2   设置版本\n");
    printf("  -DMAX_SIZE=100 定义常量\n");
    
    return 0;
}

/*
 * 知识点总结：
 * 
 * 预处理器概念：
 * 
 * 预处理：
 * - 编译前的文本替换
 * - 由预处理器执行
 * - 处理#开头的指令
 * - 生成处理后的代码给编译器
 * 
 * 编译过程：
 * 源代码 -> 预处理 -> 编译 -> 汇编 -> 链接 -> 可执行文件
 * 
 * #define宏定义：
 * 
 * 简单宏：
 * #define PI 3.14159
 * #define MAX_SIZE 100
 * 
 * 特点：
 * - 简单文本替换
 * - 无类型
 * - 编译时替换
 * 
 * 命名约定：
 * - 全大写
 * - 下划线分隔
 * 
 * 带参数的宏：
 * 
 * 语法：
 * #define SQUARE(x) ((x) * (x))
 * 
 * 重要：
 * - 参数和整个表达式都要加括号
 * - 避免优先级问题
 * 
 * 错误示例：
 * #define BAD(x) x * x
 * BAD(1 + 2) -> 1 + 2 * 1 + 2 = 5 （错！）
 * 
 * 正确示例：
 * #define GOOD(x) ((x) * (x))
 * GOOD(1 + 2) -> ((1 + 2) * (1 + 2)) = 9 （对！）
 * 
 * 多行宏：
 * 
 * 语法：
 * #define MACRO \
 *     statement1; \
 *     statement2; \
 *     statement3
 * 
 * do-while(0)技巧：
 * #define SAFE_MACRO \
 *     do { \
 *         statement1; \
 *         statement2; \
 *     } while(0)
 * 
 * 好处：
 * - 可以在任何地方使用分号
 * - 避免if-else问题
 * 
 * 字符串化 #：
 * 
 * #define TO_STRING(x) #x
 * 
 * 用法：
 * TO_STRING(Hello) -> "Hello"
 * TO_STRING(123) -> "123"
 * 
 * 应用：
 * #define PRINT_VAR(v) printf(#v " = %d\n", v)
 * 
 * 连接运算符 ##：
 * 
 * #define CONCAT(a, b) a##b
 * 
 * 用法：
 * CONCAT(var, 1) -> var1
 * CONCAT(temp, _value) -> temp_value
 * 
 * 应用：
 * 动态生成变量名
 * 
 * 条件编译：
 * 
 * #ifdef指令：
 * #ifdef MACRO
 *     // 如果MACRO已定义
 * #endif
 * 
 * #ifndef指令：
 * #ifndef MACRO
 *     // 如果MACRO未定义
 * #endif
 * 
 * #if指令：
 * #if expression
 *     // 如果表达式为真
 * #elif expression2
 *     // 否则如果
 * #else
 *     // 否则
 * #endif
 * 
 * #if defined()：
 * #if defined(MACRO)
 *     // 等同于#ifdef
 * #endif
 * 
 * #if defined(A) && defined(B)
 *     // 两个都定义
 * #endif
 * 
 * 头文件保护：
 * 
 * 传统方法：
 * #ifndef HEADER_H
 * #define HEADER_H
 * // 头文件内容
 * #endif
 * 
 * 现代方法（非标准）：
 * #pragma once
 * 
 * 作用：
 * - 防止重复包含
 * - 避免重定义错误
 * 
 * 预定义宏：
 * 
 * __FILE__    当前文件名
 * __LINE__    当前行号
 * __DATE__    编译日期
 * __TIME__    编译时间
 * __STDC__    是否符合标准C
 * __STDC_VERSION__  C标准版本
 * __cplusplus    C++编译器
 * 
 * 平台宏：
 * _WIN32      Windows
 * __linux__   Linux
 * __APPLE__   macOS
 * __unix__    Unix
 * 
 * 编译器宏：
 * __GNUC__    GCC
 * _MSC_VER    MSVC
 * __clang__   Clang
 * 
 * #undef指令：
 * 
 * #undef MACRO
 * 
 * 作用：
 * - 取消宏定义
 * - 允许重定义
 * 
 * 用法：
 * #define MAX 100
 * #undef MAX
 * #define MAX 200
 * 
 * #error指令：
 * 
 * #error "错误信息"
 * 
 * 用途：
 * - 编译时检查
 * - 阻止编译
 * 
 * 示例：
 * #if VERSION < 2
 *     #error "需要版本2或更高"
 * #endif
 * 
 * #pragma指令：
 * 
 * 编译器特定指令
 * 
 * 常见：
 * #pragma once           防止重复包含
 * #pragma pack(1)        结构体对齐
 * #pragma warning(...)   警告控制
 * #pragma comment(...)   链接库
 * 
 * 可变参数宏：
 * 
 * #define LOG(fmt, ...) \
 *     printf(fmt, ##__VA_ARGS__)
 * 
 * __VA_ARGS__：
 * - 可变参数
 * - ...表示可变参数
 * - ##用于处理空参数
 * 
 * 用法：
 * LOG("Hello");
 * LOG("Value: %d", 10);
 * LOG("X=%d, Y=%d", x, y);
 * 
 * 宏 vs 函数：
 * 
 * 宏优点：
 * - 无函数调用开销
 * - 类型无关（泛型）
 * - 编译时计算
 * - 可以操作代码
 * 
 * 宏缺点：
 * - 无类型检查
 * - 代码膨胀
 * - 调试困难
 * - 可能有副作用
 * - 不能递归
 * 
 * 函数优点：
 * - 类型安全
 * - 易于调试
 * - 代码复用
 * - 可以递归
 * 
 * 函数缺点：
 * - 函数调用开销
 * - 类型固定
 * 
 * 选择：
 * - 简单常量：宏
 * - 简单计算：内联函数
 * - 复杂逻辑：函数
 * - 类型无关：宏或模板（C++）
 * 
 * 宏的副作用：
 * 
 * 问题：
 * #define SQUARE(x) ((x) * (x))
 * SQUARE(i++) -> ((i++) * (i++))
 * // i增加两次！
 * 
 * 避免：
 * - 不在宏参数中使用++/--
 * - 先计算再传入
 * - 使用函数
 * 
 * 条件编译应用：
 * 
 * 调试代码：
 * #ifdef DEBUG
 *     printf("Debug: x=%d\n", x);
 * #endif
 * 
 * 平台相关：
 * #ifdef _WIN32
 *     // Windows代码
 * #else
 *     // Unix代码
 * #endif
 * 
 * 功能开关：
 * #ifdef FEATURE_X
 *     // 功能X代码
 * #endif
 * 
 * 版本控制：
 * #if VERSION >= 2
 *     // 新版本功能
 * #endif
 * 
 * 最佳实践：
 * 
 * 1. 宏名全大写
 * 2. 参数加括号
 * 3. 整体表达式加括号
 * 4. 多行宏用do-while(0)
 * 5. 避免副作用
 * 6. 优先考虑函数
 * 7. 复杂逻辑用函数
 * 8. 使用头文件保护
 * 9. 条件编译保持简单
 * 10. 文档化宏的行为
 * 
 * 常见错误：
 * 
 * 1. 忘记括号
 * 2. 分号问题
 * 3. 副作用
 * 4. 宏名冲突
 * 5. 过度使用宏
 * 6. 宏太复杂
 * 
 * 调试技巧：
 * 
 * 1. 查看预处理输出：
 *    gcc -E file.c
 * 
 * 2. 展开宏查看
 * 3. 使用#error测试
 * 4. 逐步替换为函数
 * 
 * 编译选项：
 * 
 * 定义宏：
 * gcc -DDEBUG file.c
 * gcc -DVERSION=2 file.c
 * 
 * 查看预定义宏：
 * gcc -dM -E - < /dev/null
 */
