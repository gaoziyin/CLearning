/*
 * 第十二章：预处理器与宏编程
 * 12.1 宏定义基础
 * 
 * 本文件详细讲解C语言宏定义的基础知识
 * 编译命令：gcc 12.1_define_basics.c -o 12.1
 */

#include <stdio.h>
#include <string.h>

// 示例1：对象式宏（Object-like Macros）- 常量定义
#define PI 3.14159265359
#define MAX_SIZE 1024
#define BUFFER_SIZE 256
#define VERSION "1.0.0"
#define AUTHOR "C Learner"

void example_object_macros() {
    printf("=== 示例1：对象式宏（常量定义）===\n\n");
    
    printf("数学常量：\n");
    printf("  PI = %.10f\n", PI);
    printf("  圆面积 (r=5): %.2f\n", PI * 5 * 5);
    
    printf("\n配置常量：\n");
    printf("  MAX_SIZE = %d\n", MAX_SIZE);
    printf("  BUFFER_SIZE = %d\n", BUFFER_SIZE);
    
    printf("\n字符串常量：\n");
    printf("  VERSION = %s\n", VERSION);
    printf("  AUTHOR = %s\n", AUTHOR);
    
    printf("\n⚠ 注意：宏定义末尾不要加分号！\n");
    printf("  正确: #define PI 3.14\n");
    printf("  错误: #define PI 3.14;\n\n");
}

// 示例2：函数式宏（Function-like Macros）
#define SQUARE(x) ((x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(x) ((x) < 0 ? -(x) : (x))
#define IS_EVEN(n) (((n) % 2) == 0)

void example_function_macros() {
    printf("=== 示例2：函数式宏 ===\n\n");
    
    printf("SQUARE宏测试：\n");
    printf("  SQUARE(5) = %d\n", SQUARE(5));
    printf("  SQUARE(3 + 2) = %d\n", SQUARE(3 + 2));
    
    printf("\nMAX/MIN宏测试：\n");
    printf("  MAX(10, 20) = %d\n", MAX(10, 20));
    printf("  MIN(10, 20) = %d\n", MIN(10, 20));
    printf("  MAX(5.5, 3.2) = %.1f\n", MAX(5.5, 3.2));
    
    printf("\nABS宏测试：\n");
    printf("  ABS(-10) = %d\n", ABS(-10));
    printf("  ABS(15) = %d\n", ABS(15));
    
    printf("\nIS_EVEN宏测试：\n");
    printf("  IS_EVEN(4) = %d (1=偶数)\n", IS_EVEN(4));
    printf("  IS_EVEN(7) = %d (0=奇数)\n", IS_EVEN(7));
    
    printf("\n✓ 函数式宏的括号很重要！\n");
    printf("  防止运算符优先级问题\n\n");
}

// 示例3：宏的副作用问题
#define WRONG_SQUARE(x) (x * x)           // 错误：缺少括号
#define CORRECT_SQUARE(x) ((x) * (x))     // 正确：完整括号

void example_macro_side_effects() {
    printf("=== 示例3：宏的副作用 ===\n\n");
    
    // 问题1：运算符优先级
    printf("运算符优先级问题：\n");
    int a = 3 + 2;
    printf("  WRONG_SQUARE(3 + 2) = %d (错误！)\n", WRONG_SQUARE(3 + 2));
    printf("    展开为: 3 + 2 * 3 + 2 = %d\n", 3 + 2 * 3 + 2);
    printf("  CORRECT_SQUARE(3 + 2) = %d (正确)\n", CORRECT_SQUARE(3 + 2));
    printf("    展开为: ((3 + 2) * (3 + 2)) = %d\n", ((3 + 2) * (3 + 2)));
    
    // 问题2：多次求值
    printf("\n多次求值问题：\n");
    int x = 5;
    printf("  x = %d\n", x);
    printf("  SQUARE(x++) = %d\n", SQUARE(x++));
    printf("  x现在 = %d (警告：x被递增了两次！)\n", x);
    printf("    展开为: ((x++) * (x++))\n");
    
    printf("\n⚠ 宏参数的副作用：\n");
    printf("  • 宏会多次展开参数\n");
    printf("  • 避免在宏参数中使用++、--等\n");
    printf("  • 这是宏函数的主要缺点\n\n");
}

// 示例4：宏与函数对比
// 函数版本
int func_square(int x) {
    return x * x;
}

// 宏版本
#define MACRO_SQUARE(x) ((x) * (x))

void example_macro_vs_function() {
    printf("=== 示例4：宏 vs 函数 ===\n\n");
    
    printf("┌─────────────┬──────────────┬──────────────┐\n");
    printf("│   特性      │     宏       │    函数      │\n");
    printf("├─────────────┼──────────────┼──────────────┤\n");
    printf("│ 类型检查    │ 无           │ 有           │\n");
    printf("│ 调用开销    │ 无（内联）   │ 有           │\n");
    printf("│ 代码大小    │ 可能增大     │ 不增大       │\n");
    printf("│ 调试        │ 困难         │ 容易         │\n");
    printf("│ 副作用      │ 可能有       │ 无           │\n");
    printf("│ 类型安全    │ 否           │ 是           │\n");
    printf("└─────────────┴──────────────┴──────────────┘\n");
    
    printf("\n性能对比：\n");
    
    // 函数调用
    int result1 = func_square(5);
    printf("  函数: func_square(5) = %d\n", result1);
    
    // 宏展开
    int result2 = MACRO_SQUARE(5);
    printf("  宏:   MACRO_SQUARE(5) = %d\n", result2);
    
    printf("\n使用建议：\n");
    printf("  ✓ 简单常量 → 使用宏\n");
    printf("  ✓ 简单计算且性能关键 → 使用宏\n");
    printf("  ✓ 需要类型通用性 → 使用宏\n");
    printf("  ✓ 复杂逻辑 → 使用函数\n");
    printf("  ✓ 需要调试 → 使用函数\n");
    printf("  ✓ 现代C → 使用inline函数\n\n");
}

// 示例5：多行宏定义
#define SWAP(a, b, type) \
    do { \
        type temp = (a); \
        (a) = (b); \
        (b) = temp; \
    } while(0)

#define PRINT_ARRAY(arr, size) \
    do { \
        printf("["); \
        for (int i = 0; i < (size); i++) { \
            printf("%d", (arr)[i]); \
            if (i < (size) - 1) printf(", "); \
        } \
        printf("]\n"); \
    } while(0)

void example_multiline_macros() {
    printf("=== 示例5：多行宏定义 ===\n\n");
    
    printf("SWAP宏测试：\n");
    int x = 10, y = 20;
    printf("  交换前: x = %d, y = %d\n", x, y);
    SWAP(x, y, int);
    printf("  交换后: x = %d, y = %d\n", x, y);
    
    printf("\nPRINT_ARRAY宏测试：\n");
    int arr[] = {1, 2, 3, 4, 5};
    printf("  数组内容: ");
    PRINT_ARRAY(arr, 5);
    
    printf("\n多行宏的要点：\n");
    printf("  • 使用反斜杠 \\ 连接多行\n");
    printf("  • 反斜杠后不能有空格\n");
    printf("  • 最后一行不需要反斜杠\n");
    printf("  • 使用 do-while(0) 确保安全\n\n");
}

// 示例6：条件运算符宏
#define CLAMP(x, min, max) \
    ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))

#define IN_RANGE(x, min, max) \
    ((x) >= (min) && (x) <= (max))

#define SIGN(x) \
    ((x) > 0 ? 1 : ((x) < 0 ? -1 : 0))

void example_conditional_macros() {
    printf("=== 示例6：条件运算符宏 ===\n\n");
    
    printf("CLAMP宏（限制范围）：\n");
    printf("  CLAMP(15, 0, 10) = %d\n", CLAMP(15, 0, 10));
    printf("  CLAMP(-5, 0, 10) = %d\n", CLAMP(-5, 0, 10));
    printf("  CLAMP(5, 0, 10) = %d\n", CLAMP(5, 0, 10));
    
    printf("\nIN_RANGE宏（范围检查）：\n");
    printf("  IN_RANGE(5, 0, 10) = %d\n", IN_RANGE(5, 0, 10));
    printf("  IN_RANGE(15, 0, 10) = %d\n", IN_RANGE(15, 0, 10));
    
    printf("\nSIGN宏（符号判断）：\n");
    printf("  SIGN(10) = %d\n", SIGN(10));
    printf("  SIGN(-5) = %d\n", SIGN(-5));
    printf("  SIGN(0) = %d\n", SIGN(0));
    
    printf("\n");
}

// 示例7：类型转换宏
#define TO_INT(x) ((int)(x))
#define TO_FLOAT(x) ((float)(x))
#define PTR_TO_INT(ptr) ((long)(ptr))
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

void example_conversion_macros() {
    printf("=== 示例7：类型转换宏 ===\n\n");
    
    printf("数值转换：\n");
    double d = 3.14159;
    printf("  TO_INT(3.14159) = %d\n", TO_INT(d));
    printf("  TO_FLOAT(5) = %.1f\n", TO_FLOAT(5));
    
    printf("\n数组大小宏：\n");
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printf("  数组元素个数: %zu\n", ARRAY_SIZE(numbers));
    
    char str[] = "Hello";
    printf("  字符数组大小: %zu (包含\\0)\n", ARRAY_SIZE(str));
    
    printf("\n⚠ ARRAY_SIZE只能用于数组，不能用于指针！\n\n");
}

// 示例8：宏的作用域
#define TEMP_VALUE 100

void example_macro_scope() {
    printf("=== 示例8：宏的作用域 ===\n\n");
    
    printf("全局宏：\n");
    printf("  TEMP_VALUE = %d\n", TEMP_VALUE);
    
    // 宏可以在代码中重新定义
    #undef TEMP_VALUE
    #define TEMP_VALUE 200
    
    printf("  重新定义后: TEMP_VALUE = %d\n", TEMP_VALUE);
    
    printf("\n宏的作用域特点：\n");
    printf("  • 从定义处到文件结束\n");
    printf("  • 或直到#undef\n");
    printf("  • 不受函数或代码块限制\n");
    printf("  • 可以在代码中间定义\n\n");
    
    #undef TEMP_VALUE
}

// 示例9：#undef 取消宏定义
#define DEBUG_MODE 1

void example_undef() {
    printf("=== 示例9：#undef 取消定义 ===\n\n");
    
    #ifdef DEBUG_MODE
    printf("DEBUG_MODE 已定义，值为: %d\n", DEBUG_MODE);
    #endif
    
    // 取消定义
    #undef DEBUG_MODE
    
    #ifdef DEBUG_MODE
    printf("DEBUG_MODE 仍然定义\n");
    #else
    printf("DEBUG_MODE 已被取消定义\n");
    #endif
    
    printf("\n#undef 的用途：\n");
    printf("  • 在不同代码段使用不同定义\n");
    printf("  • 避免宏名冲突\n");
    printf("  • 临时禁用某个宏\n");
    printf("  • 重新定义宏之前\n\n");
}

// 示例10：常见错误与最佳实践
#define WRONG_MAX(a, b) a > b ? a : b          // 错误：缺少括号
#define RIGHT_MAX(a, b) ((a) > (b) ? (a) : (b)) // 正确

#define WRONG_INC(x) x++                       // 错误：副作用
// 正确做法：不要用宏做这种操作，用函数

void example_best_practices() {
    printf("=== 示例10：常见错误与最佳实践 ===\n\n");
    
    printf("错误1：缺少括号\n");
    printf("  int x = WRONG_MAX(1, 2) + 3;\n");
    printf("  展开: 1 > 2 ? 1 : 2 + 3 = %d (错误！)\n", WRONG_MAX(1, 2) + 3);
    printf("  应该: ((1) > (2) ? (1) : (2)) + 3 = %d\n", RIGHT_MAX(1, 2) + 3);
    
    printf("\n最佳实践：\n");
    printf("  1. 宏名全大写（与变量区分）\n");
    printf("  2. 参数和表达式都加括号\n");
    printf("  3. 避免在宏中使用++、--\n");
    printf("  4. 多行宏使用 do-while(0)\n");
    printf("  5. 复杂逻辑用函数代替宏\n");
    printf("  6. 用#undef避免宏污染\n");
    printf("  7. 宏末尾不加分号\n");
    printf("  8. 注释宏的用途和注意事项\n");
    
    printf("\n");
}

int main() {
    printf("╔═══════════════════════════════════════╗\n");
    printf("║   第12章：预处理器与宏编程            ║\n");
    printf("║   12.1 宏定义基础                     ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
    
    example_object_macros();
    example_function_macros();
    example_macro_side_effects();
    example_macro_vs_function();
    example_multiline_macros();
    example_conditional_macros();
    example_conversion_macros();
    example_macro_scope();
    example_undef();
    example_best_practices();
    
    printf("═════════════════════════════════════════\n");
    printf("宏定义基础总结：\n");
    printf("═════════════════════════════════════════\n");
    printf("对象式宏：\n");
    printf("  #define NAME value\n");
    printf("  用于定义常量\n");
    printf("\n");
    printf("函数式宏：\n");
    printf("  #define MACRO(params) expression\n");
    printf("  用于简单的代码替换\n");
    printf("\n");
    printf("优点：\n");
    printf("  ✓ 无函数调用开销\n");
    printf("  ✓ 类型通用\n");
    printf("  ✓ 编译时计算\n");
    printf("\n");
    printf("缺点：\n");
    printf("  ✗ 无类型检查\n");
    printf("  ✗ 可能有副作用\n");
    printf("  ✗ 调试困难\n");
    printf("  ✗ 可能增大代码\n");
    printf("\n");
    printf("关键要点：\n");
    printf("  • 参数加括号防止优先级问题\n");
    printf("  • 避免参数副作用\n");
    printf("  • 宏名使用大写\n");
    printf("  • 复杂逻辑用函数\n");
    printf("═════════════════════════════════════════\n");
    
    return 0;
}

/*
 * 编译和运行：
 *   gcc 12.1_define_basics.c -o 12.1
 *   ./12.1
 * 
 * 学习要点：
 *   1. 理解宏的本质是文本替换
 *   2. 掌握宏定义的语法规则
 *   3. 了解宏的优缺点
 *   4. 避免宏的常见陷阱
 *   5. 学会何时用宏、何时用函数
 * 
 * 下一步：
 *   学习12.2 条件编译
 */
