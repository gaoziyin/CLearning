/*
 * 第十二章：预处理器与宏编程
 * 12.2 条件编译
 * 
 * 本文件详细讲解C语言条件编译指令
 * 编译命令：
 *   基本: gcc 12.2_conditional_compilation.c -o 12.2
 *   调试: gcc -DDEBUG 12.2_conditional_compilation.c -o 12.2
 *   Windows: gcc -DWINDOWS 12.2_conditional_compilation.c -o 12.2
 */

#include <stdio.h>
#include <string.h>

// 示例1：#ifdef / #ifndef / #endif
#define FEATURE_A_ENABLED

void example_ifdef_ifndef() {
    printf("=== 示例1：#ifdef / #ifndef ===\n\n");
    
    #ifdef FEATURE_A_ENABLED
    printf("✓ 功能A已启用\n");
    #endif
    
    #ifndef FEATURE_B_ENABLED
    printf("✗ 功能B未启用\n");
    #endif
    
    printf("\n#ifdef 语法：\n");
    printf("  #ifdef MACRO_NAME\n");
    printf("    // 如果已定义则编译这部分\n");
    printf("  #endif\n");
    
    printf("\n#ifndef 语法：\n");
    printf("  #ifndef MACRO_NAME\n");
    printf("    // 如果未定义则编译这部分\n");
    printf("  #endif\n\n");
}

// 示例2：#if defined / #if !defined
#define VERSION_MAJOR 2
#define VERSION_MINOR 5

void example_if_defined() {
    printf("=== 示例2：#if defined ===\n\n");
    
    #if defined(VERSION_MAJOR) && defined(VERSION_MINOR)
    printf("版本号: %d.%d\n", VERSION_MAJOR, VERSION_MINOR);
    #else
    printf("版本号未定义\n");
    #endif
    
    #if !defined(BETA_VERSION)
    printf("这是正式版本\n");
    #endif
    
    printf("\n#if defined 的优势：\n");
    printf("  • 可以使用逻辑运算符 &&、||、!\n");
    printf("  • 可以组合多个条件\n");
    printf("  • 更灵活的条件判断\n\n");
}

// 示例3：#if / #elif / #else
#define BUILD_TYPE 2  // 1=Debug, 2=Release, 3=Test

void example_if_elif_else() {
    printf("=== 示例3：#if / #elif / #else ===\n\n");
    
    #if BUILD_TYPE == 1
    printf("编译模式: Debug\n");
    printf("  • 包含调试信息\n");
    printf("  • 未优化\n");
    printf("  • 额外检查\n");
    #elif BUILD_TYPE == 2
    printf("编译模式: Release\n");
    printf("  • 无调试信息\n");
    printf("  • 完全优化\n");
    printf("  • 最佳性能\n");
    #elif BUILD_TYPE == 3
    printf("编译模式: Test\n");
    printf("  • 测试代码\n");
    printf("  • 覆盖率分析\n");
    printf("  • 性能分析\n");
    #else
    printf("编译模式: 未知\n");
    #endif
    
    printf("\n");
}

// 示例4：跨平台编译
void example_platform_specific() {
    printf("=== 示例4：跨平台编译 ===\n\n");
    
    printf("当前平台检测：\n");
    
    #ifdef _WIN32
        printf("  操作系统: Windows (32位或64位)\n");
        #ifdef _WIN64
            printf("  架构: 64位\n");
        #else
            printf("  架构: 32位\n");
        #endif
    #elif defined(__linux__)
        printf("  操作系统: Linux\n");
        #ifdef __x86_64__
            printf("  架构: x86_64\n");
        #elif defined(__i386__)
            printf("  架构: x86\n");
        #elif defined(__arm__)
            printf("  架构: ARM\n");
        #endif
    #elif defined(__APPLE__)
        printf("  操作系统: macOS\n");
        #ifdef __x86_64__
            printf("  架构: Intel\n");
        #elif defined(__aarch64__)
            printf("  架构: Apple Silicon (M1/M2)\n");
        #endif
    #else
        printf("  操作系统: 未知\n");
    #endif
    
    printf("\n常用平台宏：\n");
    printf("  Windows:  _WIN32, _WIN64, _MSC_VER\n");
    printf("  Linux:    __linux__, __unix__\n");
    printf("  macOS:    __APPLE__, __MACH__\n");
    printf("  Android:  __ANDROID__\n");
    printf("  iOS:      TARGET_OS_IPHONE\n\n");
}

// 示例5：编译器检测
void example_compiler_detection() {
    printf("=== 示例5：编译器检测 ===\n\n");
    
    printf("编译器信息：\n");
    
    #ifdef __GNUC__
        printf("  编译器: GCC/G++\n");
        printf("  版本: %d.%d.%d\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
    #elif defined(_MSC_VER)
        printf("  编译器: Microsoft Visual C++\n");
        printf("  版本: %d\n", _MSC_VER);
    #elif defined(__clang__)
        printf("  编译器: Clang\n");
        printf("  版本: %d.%d.%d\n", __clang_major__, __clang_minor__, __clang_patchlevel__);
    #else
        printf("  编译器: 未知\n");
    #endif
    
    printf("\nC标准版本：\n");
    #if __STDC_VERSION__ >= 201710L
        printf("  C17 或更高\n");
    #elif __STDC_VERSION__ >= 201112L
        printf("  C11\n");
    #elif __STDC_VERSION__ >= 199901L
        printf("  C99\n");
    #else
        printf("  C89/C90\n");
    #endif
    
    printf("\n");
}

// 示例6：调试开关
// 通过 gcc -DDEBUG 启用调试代码
#ifdef DEBUG
    #define DEBUG_PRINT(fmt, ...) \
        fprintf(stderr, "[DEBUG] %s:%d:%s(): " fmt "\n", \
                __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#else
    #define DEBUG_PRINT(fmt, ...) // 不输出
#endif

void example_debug_switches() {
    printf("=== 示例6：调试开关 ===\n\n");
    
    int x = 10, y = 20;
    DEBUG_PRINT("变量初始化完成");
    
    int sum = x + y;
    DEBUG_PRINT("计算结果: %d + %d = %d", x, y, sum);
    
    #ifdef DEBUG
    printf("调试模式已启用\n");
    printf("  • 额外日志输出\n");
    printf("  • 断言检查\n");
    printf("  • 性能可能降低\n");
    #else
    printf("调试模式未启用\n");
    printf("  • 无调试输出\n");
    printf("  • 最佳性能\n");
    #endif
    
    printf("\n编译方式：\n");
    printf("  启用调试: gcc -DDEBUG 12.2_conditional_compilation.c -o 12.2\n");
    printf("  禁用调试: gcc 12.2_conditional_compilation.c -o 12.2\n\n");
}

// 示例7：功能特性开关
// #define ENABLE_LOGGING
// #define ENABLE_PROFILING
#define ENABLE_ENCRYPTION

void example_feature_flags() {
    printf("=== 示例7：功能特性开关 ===\n\n");
    
    printf("已启用的功能：\n");
    
    #ifdef ENABLE_LOGGING
    printf("  ✓ 日志记录\n");
    #else
    printf("  ✗ 日志记录\n");
    #endif
    
    #ifdef ENABLE_PROFILING
    printf("  ✓ 性能分析\n");
    #else
    printf("  ✗ 性能分析\n");
    #endif
    
    #ifdef ENABLE_ENCRYPTION
    printf("  ✓ 数据加密\n");
    #else
    printf("  ✗ 数据加密\n");
    #endif
    
    printf("\n使用场景：\n");
    printf("  • 开发版 vs 生产版\n");
    printf("  • 免费版 vs 专业版\n");
    printf("  • 实验性功能控制\n");
    printf("  • 平台特定功能\n\n");
}

// 示例8：版本控制
#define API_VERSION 3

void example_version_control() {
    printf("=== 示例8：版本控制 ===\n\n");
    
    printf("API版本: %d\n", API_VERSION);
    
    #if API_VERSION >= 3
    printf("  ✓ 支持新特性\n");
    printf("  ✓ 使用高级API\n");
    void* result = NULL;  // 使用新接口
    printf("  使用新版API\n");
    #elif API_VERSION >= 2
    printf("  ⚠ 使用兼容模式\n");
    int result = 0;  // 使用旧接口
    printf("  使用旧版API\n");
    #else
    printf("  ✗ 版本过低\n");
    printf("  需要升级到版本2或更高\n");
    #endif
    
    printf("\n");
}

// 示例9：#error 和 #warning
void example_error_warning() {
    printf("=== 示例9：编译时错误和警告 ===\n\n");
    
    // 检查必要的宏是否定义
    #ifndef VERSION_MAJOR
        // #error "VERSION_MAJOR must be defined!"
        printf("⚠ 示例：如果取消注释#error，编译将失败\n");
    #endif
    
    // 检查配置冲突
    #if defined(DEBUG) && defined(OPTIMIZE)
        // #warning "Debug and Optimize are both enabled!"
        printf("⚠ 示例：#warning会产生编译警告\n");
    #endif
    
    printf("编译时检查：\n");
    printf("  #error: 强制编译失败\n");
    printf("    用途: 检测必需的配置\n");
    printf("  #warning: 产生编译警告\n");
    printf("    用途: 提醒潜在问题\n");
    
    printf("\n示例：\n");
    printf("  #ifndef REQUIRED_MACRO\n");
    printf("    #error \"REQUIRED_MACRO必须定义！\"\n");
    printf("  #endif\n\n");
}

// 示例10：复杂条件组合
#define SYSTEM_TYPE 1    // 1=Desktop, 2=Mobile, 3=Embedded
#define HAS_GUI 1
#define MEMORY_SIZE 8    // GB

void example_complex_conditions() {
    printf("=== 示例10：复杂条件组合 ===\n\n");
    
    printf("系统配置分析：\n");
    
    #if (SYSTEM_TYPE == 1) && (MEMORY_SIZE >= 8)
    printf("  系统类型: 高端桌面系统\n");
    printf("  推荐设置: 最高画质\n");
    #elif (SYSTEM_TYPE == 1) && (MEMORY_SIZE >= 4)
    printf("  系统类型: 普通桌面系统\n");
    printf("  推荐设置: 中等画质\n");
    #elif SYSTEM_TYPE == 2
    printf("  系统类型: 移动设备\n");
    printf("  推荐设置: 省电模式\n");
    #elif SYSTEM_TYPE == 3
    printf("  系统类型: 嵌入式系统\n");
    printf("  推荐设置: 最小资源占用\n");
    #endif
    
    #if defined(HAS_GUI) && (MEMORY_SIZE < 2)
        // #warning "GUI enabled but low memory!"
    printf("  ⚠ 内存可能不足\n");
    #endif
    
    printf("\n条件表达式支持：\n");
    printf("  • 算术运算: +, -, *, /, %%\n");
    printf("  • 比较运算: <, >, <=, >=, ==, !=\n");
    printf("  • 逻辑运算: &&, ||, !\n");
    printf("  • 括号分组: ( )\n\n");
}

// 示例11：条件编译的实际应用
#define USE_FAST_MATH 1

double calculate_distance(double x, double y) {
    #if USE_FAST_MATH
        // 快速但不够精确的算法
        double ax = x < 0 ? -x : x;
        double ay = y < 0 ? -y : y;
        return ax + ay;  // 曼哈顿距离
    #else
        // 精确但较慢的算法
        return sqrt(x * x + y * y);  // 欧几里得距离
    #endif
}

void example_practical_usage() {
    printf("=== 示例11：实际应用 ===\n\n");
    
    double dist = calculate_distance(3.0, 4.0);
    printf("距离计算结果: %.2f\n", dist);
    
    #if USE_FAST_MATH
    printf("  算法: 快速近似\n");
    printf("  精度: 较低\n");
    printf("  速度: 快\n");
    #else
    printf("  算法: 精确计算\n");
    printf("  精度: 高\n");
    printf("  速度: 较慢\n");
    #endif
    
    printf("\n实际应用场景：\n");
    printf("  • 游戏开发: 快速数学 vs 精确计算\n");
    printf("  • 嵌入式: 完整功能 vs 精简版本\n");
    printf("  • 跨平台: 不同OS的API选择\n");
    printf("  • 优化: Debug vs Release构建\n\n");
}

int main() {
    printf("╔═══════════════════════════════════════╗\n");
    printf("║   第12章：预处理器与宏编程            ║\n");
    printf("║   12.2 条件编译                       ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
    
    example_ifdef_ifndef();
    example_if_defined();
    example_if_elif_else();
    example_platform_specific();
    example_compiler_detection();
    example_debug_switches();
    example_feature_flags();
    example_version_control();
    example_error_warning();
    example_complex_conditions();
    example_practical_usage();
    
    printf("═════════════════════════════════════════\n");
    printf("条件编译总结：\n");
    printf("═════════════════════════════════════════\n");
    printf("基本指令：\n");
    printf("  #ifdef  MACRO     - 如果已定义\n");
    printf("  #ifndef MACRO     - 如果未定义\n");
    printf("  #if expression    - 条件为真\n");
    printf("  #elif expression  - 否则如果\n");
    printf("  #else             - 否则\n");
    printf("  #endif            - 结束条件块\n");
    printf("\n");
    printf("高级用法：\n");
    printf("  #if defined(A) && defined(B)\n");
    printf("  #if VERSION >= 2\n");
    printf("  #error \"错误信息\"\n");
    printf("  #warning \"警告信息\"\n");
    printf("\n");
    printf("应用场景：\n");
    printf("  ✓ 跨平台代码\n");
    printf("  ✓ Debug/Release切换\n");
    printf("  ✓ 功能特性开关\n");
    printf("  ✓ 版本兼容性\n");
    printf("  ✓ 编译器适配\n");
    printf("\n");
    printf("最佳实践：\n");
    printf("  • 使用有意义的宏名\n");
    printf("  • 添加清晰的注释\n");
    printf("  • 避免过度嵌套\n");
    printf("  • 保持代码可读性\n");
    printf("═════════════════════════════════════════\n");
    
    return 0;
}

/*
 * 编译和运行：
 *   基本编译:
 *     gcc 12.2_conditional_compilation.c -o 12.2
 *   启用调试:
 *     gcc -DDEBUG 12.2_conditional_compilation.c -o 12.2
 *   定义多个宏:
 *     gcc -DDEBUG -DENABLE_LOGGING 12.2_conditional_compilation.c -o 12.2
 *   定义带值的宏:
 *     gcc -DVERSION_MAJOR=3 12.2_conditional_compilation.c -o 12.2
 * 
 * 学习要点：
 *   1. 掌握条件编译的基本语法
 *   2. 了解跨平台编译技巧
 *   3. 学会使用编译开关
 *   4. 理解条件编译的应用场景
 *   5. 掌握调试和发布版本切换
 * 
 * 下一步：
 *   学习12.3 头文件保护
 */
