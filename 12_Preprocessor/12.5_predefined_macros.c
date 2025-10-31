/*
 * 第十二章：预处理器与宏编程
 * 12.5 预定义宏和实用技巧
 * 
 * 本文件详细讲解C语言预定义宏及实用编程技巧
 * 编译命令：gcc 12.5_predefined_macros.c -o 12.5
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 示例1：标准预定义宏
void example_standard_macros() {
    printf("=== 示例1：标准预定义宏 ===\n\n");
    
    printf("文件和位置信息：\n");
    printf("  __FILE__  : %s\n", __FILE__);
    printf("  __LINE__  : %d\n", __LINE__);
    
    #ifdef __func__
    printf("  __func__  : %s\n", __func__);
    #endif
    
    printf("\n日期和时间：\n");
    printf("  __DATE__  : %s\n", __DATE__);
    printf("  __TIME__  : %s\n", __TIME__);
    
    printf("\nC标准版本：\n");
    printf("  __STDC__        : ");
    #ifdef __STDC__
    printf("1 (符合标准C)\n");
    #else
    printf("未定义\n");
    #endif
    
    printf("  __STDC_VERSION__: ");
    #ifdef __STDC_VERSION__
        #if __STDC_VERSION__ == 199901L
            printf("199901L (C99)\n");
        #elif __STDC_VERSION__ == 201112L
            printf("201112L (C11)\n");
        #elif __STDC_VERSION__ == 201710L
            printf("201710L (C17)\n");
        #elif __STDC_VERSION__ >= 202000L
            printf("%ld (C23或更高)\n", __STDC_VERSION__);
        #else
            printf("%ld\n", __STDC_VERSION__);
        #endif
    #else
    printf("未定义 (C89/C90)\n");
    #endif
    
    printf("\n");
}

// 示例2：编译器识别宏
void example_compiler_macros() {
    printf("=== 示例2：编译器识别宏 ===\n\n");
    
    printf("编译器信息：\n");
    
    #ifdef __GNUC__
        printf("  编译器: GCC/G++\n");
        printf("  主版本: %d\n", __GNUC__);
        printf("  次版本: %d\n", __GNUC_MINOR__);
        printf("  补丁版本: %d\n", __GNUC_PATCHLEVEL__);
        printf("  完整版本: %d.%d.%d\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
    #endif
    
    #ifdef __clang__
        printf("  编译器: Clang\n");
        printf("  版本: %d.%d.%d\n", __clang_major__, __clang_minor__, __clang_patchlevel__);
    #endif
    
    #ifdef _MSC_VER
        printf("  编译器: Microsoft Visual C++\n");
        printf("  版本号: %d\n", _MSC_VER);
        printf("  完整版本: %d\n", _MSC_FULL_VER);
    #endif
    
    printf("\n常用编译器宏：\n");
    printf("  GCC/G++: __GNUC__\n");
    printf("  Clang:   __clang__\n");
    printf("  MSVC:    _MSC_VER\n");
    printf("  Intel:   __INTEL_COMPILER\n");
    printf("  MinGW:   __MINGW32__ / __MINGW64__\n");
    printf("\n");
}

// 示例3：平台识别宏
void example_platform_macros() {
    printf("=== 示例3：平台识别宏 ===\n\n");
    
    printf("操作系统：\n");
    
    #ifdef _WIN32
        printf("  平台: Windows\n");
        #ifdef _WIN64
            printf("  架构: 64位\n");
        #else
            printf("  架构: 32位\n");
        #endif
    #endif
    
    #ifdef __linux__
        printf("  平台: Linux\n");
        #ifdef __x86_64__
            printf("  架构: x86_64\n");
        #elif defined(__i386__)
            printf("  架构: i386\n");
        #elif defined(__arm__)
            printf("  架构: ARM\n");
        #elif defined(__aarch64__)
            printf("  架构: ARM64\n");
        #endif
    #endif
    
    #ifdef __APPLE__
        printf("  平台: Apple\n");
        #include <TargetConditionals.h>
        #if TARGET_OS_IPHONE
            printf("  系统: iOS\n");
        #elif TARGET_OS_MAC
            printf("  系统: macOS\n");
        #endif
    #endif
    
    #ifdef __unix__
        printf("  类型: Unix-like系统\n");
    #endif
    
    #ifdef __ANDROID__
        printf("  平台: Android\n");
    #endif
    
    printf("\n字节序：\n");
    #ifdef __BYTE_ORDER__
        #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
            printf("  小端序 (Little Endian)\n");
        #elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
            printf("  大端序 (Big Endian)\n");
        #endif
    #else
        // 运行时检测
        int n = 1;
        if (*(char*)&n == 1) {
            printf("  小端序 (Little Endian)\n");
        } else {
            printf("  大端序 (Big Endian)\n");
        }
    #endif
    
    printf("\n");
}

// 示例4：架构相关宏
void example_architecture_macros() {
    printf("=== 示例4：架构相关宏 ===\n\n");
    
    printf("处理器架构：\n");
    
    #if defined(__x86_64__) || defined(_M_X64)
        printf("  架构: x86-64 (AMD64)\n");
        printf("  位数: 64位\n");
    #elif defined(__i386__) || defined(_M_IX86)
        printf("  架构: x86 (IA-32)\n");
        printf("  位数: 32位\n");
    #elif defined(__arm__)
        printf("  架构: ARM 32位\n");
    #elif defined(__aarch64__)
        printf("  架构: ARM 64位\n");
    #elif defined(__mips__)
        printf("  架构: MIPS\n");
    #elif defined(__powerpc__) || defined(__ppc__)
        printf("  架构: PowerPC\n");
    #endif
    
    printf("\n指针大小：\n");
    #if defined(__LP64__) || defined(_LP64)
        printf("  LP64 模型 (long和指针是64位)\n");
    #elif defined(__ILP32__) || defined(_ILP32)
        printf("  ILP32 模型 (int、long和指针是32位)\n");
    #endif
    
    printf("  实际大小: %zu 字节\n", sizeof(void*));
    
    printf("\n");
}

// 示例5：实用的日志宏
#define LOG_LEVEL_DEBUG 0
#define LOG_LEVEL_INFO  1
#define LOG_LEVEL_WARN  2
#define LOG_LEVEL_ERROR 3

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_INFO
#endif

#define LOG(level, format, ...) \
    do { \
        if (level >= LOG_LEVEL) { \
            const char* level_str[] = {"DEBUG", "INFO", "WARN", "ERROR"}; \
            printf("[%s] %s:%d %s() - " format "\n", \
                   level_str[level], __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
        } \
    } while(0)

#define LOG_DEBUG(format, ...) LOG(LOG_LEVEL_DEBUG, format, ##__VA_ARGS__)
#define LOG_INFO(format, ...)  LOG(LOG_LEVEL_INFO, format, ##__VA_ARGS__)
#define LOG_WARN(format, ...)  LOG(LOG_LEVEL_WARN, format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) LOG(LOG_LEVEL_ERROR, format, ##__VA_ARGS__)

void example_logging_macros() {
    printf("=== 示例5：实用日志宏 ===\n\n");
    
    LOG_DEBUG("这是调试信息");
    LOG_INFO("程序启动成功");
    LOG_WARN("配置文件使用默认值");
    LOG_ERROR("无法打开文件: %s", "config.txt");
    
    printf("\n日志级别控制：\n");
    printf("  • DEBUG: 详细调试信息\n");
    printf("  • INFO:  一般信息\n");
    printf("  • WARN:  警告信息\n");
    printf("  • ERROR: 错误信息\n");
    
    printf("\n编译时控制：\n");
    printf("  gcc -DLOG_LEVEL=0 源文件.c  # 显示所有\n");
    printf("  gcc -DLOG_LEVEL=2 源文件.c  # 只显示警告和错误\n");
    printf("\n");
}

// 示例6：性能测量宏
#define BENCHMARK_START() \
    clock_t _bench_start = clock()

#define BENCHMARK_END(name) \
    do { \
        clock_t _bench_end = clock(); \
        double _bench_time = (double)(_bench_end - _bench_start) / CLOCKS_PER_SEC; \
        printf("[BENCHMARK] %s: %.6f 秒\n", name, _bench_time); \
    } while(0)

void example_benchmark_macros() {
    printf("=== 示例6：性能测量宏 ===\n\n");
    
    BENCHMARK_START();
    
    // 模拟一些工作
    long sum = 0;
    for (int i = 0; i < 10000000; i++) {
        sum += i;
    }
    
    BENCHMARK_END("计算1000万次累加");
    
    printf("结果: %ld\n", sum);
    
    printf("\n使用方法：\n");
    printf("  BENCHMARK_START();\n");
    printf("  // 要测量的代码\n");
    printf("  BENCHMARK_END(\"描述\");\n");
    printf("\n");
}

// 示例7：编译时断言（C11）
#if __STDC_VERSION__ >= 201112L
    #define STATIC_ASSERT(expr, msg) _Static_assert(expr, msg)
#else
    #define STATIC_ASSERT(expr, msg) \
        typedef char static_assertion_##msg[(expr) ? 1 : -1]
#endif

void example_static_assert() {
    printf("=== 示例7：编译时断言 ===\n\n");
    
    // 编译时检查
    STATIC_ASSERT(sizeof(int) == 4, int_must_be_4_bytes);
    STATIC_ASSERT(sizeof(void*) >= 4, pointer_must_be_at_least_4_bytes);
    
    printf("编译时断言通过：\n");
    printf("  ✓ sizeof(int) == 4\n");
    printf("  ✓ sizeof(void*) >= 4\n");
    
    printf("\n编译时断言的优势：\n");
    printf("  • 在编译期发现错误\n");
    printf("  • 无运行时开销\n");
    printf("  • 确保假设成立\n");
    printf("  • C11提供 _Static_assert\n");
    
    printf("\n使用场景：\n");
    printf("  • 检查类型大小\n");
    printf("  • 验证对齐要求\n");
    printf("  • 确保数组大小\n");
    printf("  • 平台兼容性检查\n");
    printf("\n");
}

// 示例8：内存对齐宏
#define ALIGN_UP(x, align) (((x) + (align) - 1) & ~((align) - 1))
#define ALIGN_DOWN(x, align) ((x) & ~((align) - 1))
#define IS_ALIGNED(x, align) (((x) & ((align) - 1)) == 0)

void example_alignment_macros() {
    printf("=== 示例8：内存对齐宏 ===\n\n");
    
    printf("对齐到4字节：\n");
    for (int i = 1; i <= 10; i++) {
        printf("  %2d → 向上对齐: %2d, 向下对齐: %2d, 已对齐: %s\n",
               i,
               ALIGN_UP(i, 4),
               ALIGN_DOWN(i, 4),
               IS_ALIGNED(i, 4) ? "是" : "否");
    }
    
    printf("\n对齐到8字节：\n");
    int values[] = {7, 8, 9, 15, 16, 17};
    for (int i = 0; i < 6; i++) {
        int v = values[i];
        printf("  %2d → 向上对齐: %2d, 已对齐: %s\n",
               v, ALIGN_UP(v, 8), IS_ALIGNED(v, 8) ? "是" : "否");
    }
    
    printf("\n应用场景：\n");
    printf("  • 内存分配器\n");
    printf("  • DMA传输\n");
    printf("  • 性能优化\n");
    printf("  • 硬件接口\n");
    printf("\n");
}

// 示例9：位操作宏
#define BIT(n) (1U << (n))
#define BIT_SET(value, bit) ((value) | BIT(bit))
#define BIT_CLEAR(value, bit) ((value) & ~BIT(bit))
#define BIT_TOGGLE(value, bit) ((value) ^ BIT(bit))
#define BIT_CHECK(value, bit) (((value) & BIT(bit)) != 0)

void example_bit_macros() {
    printf("=== 示例9：位操作宏 ===\n\n");
    
    unsigned int flags = 0;
    
    printf("初始值: 0x%08X (%u)\n", flags, flags);
    
    flags = BIT_SET(flags, 0);
    printf("设置bit 0: 0x%08X\n", flags);
    
    flags = BIT_SET(flags, 3);
    printf("设置bit 3: 0x%08X\n", flags);
    
    flags = BIT_SET(flags, 7);
    printf("设置bit 7: 0x%08X\n", flags);
    
    printf("\n检查位状态：\n");
    for (int i = 0; i < 8; i++) {
        printf("  bit %d: %s\n", i, BIT_CHECK(flags, i) ? "1" : "0");
    }
    
    flags = BIT_CLEAR(flags, 3);
    printf("\n清除bit 3: 0x%08X\n", flags);
    
    flags = BIT_TOGGLE(flags, 0);
    printf("切换bit 0: 0x%08X\n", flags);
    
    printf("\n应用场景：\n");
    printf("  • 标志位管理\n");
    printf("  • 寄存器操作\n");
    printf("  • 权限控制\n");
    printf("  • 状态机\n");
    printf("\n");
}

// 示例10：容器宏
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define OFFSETOF(type, member) ((size_t)&(((type*)0)->member))
#define CONTAINER_OF(ptr, type, member) \
    ((type*)((char*)(ptr) - OFFSETOF(type, member)))

struct MyStruct {
    int id;
    char name[32];
    double value;
};

void example_container_macros() {
    printf("=== 示例10：容器宏 ===\n\n");
    
    int numbers[] = {1, 2, 3, 4, 5};
    printf("数组大小: %zu\n", ARRAY_SIZE(numbers));
    
    printf("\n结构体成员偏移：\n");
    printf("  id的偏移: %zu\n", OFFSETOF(struct MyStruct, id));
    printf("  name的偏移: %zu\n", OFFSETOF(struct MyStruct, name));
    printf("  value的偏移: %zu\n", OFFSETOF(struct MyStruct, value));
    
    struct MyStruct obj = {42, "Test", 3.14};
    char* name_ptr = obj.name;
    struct MyStruct* obj_ptr = CONTAINER_OF(name_ptr, struct MyStruct, name);
    
    printf("\n通过成员指针获取容器：\n");
    printf("  对象地址: %p\n", (void*)&obj);
    printf("  推导地址: %p\n", (void*)obj_ptr);
    printf("  匹配: %s\n", (obj_ptr == &obj) ? "是" : "否");
    
    printf("\n应用场景：\n");
    printf("  • Linux内核链表\n");
    printf("  • 侵入式容器\n");
    printf("  • 通用数据结构\n");
    printf("\n");
}

// 示例11：预定义宏的实用技巧
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define VERSION_MAJOR 1
#define VERSION_MINOR 2
#define VERSION_PATCH 3
#define VERSION_STRING \
    TOSTRING(VERSION_MAJOR) "." \
    TOSTRING(VERSION_MINOR) "." \
    TOSTRING(VERSION_PATCH)

void example_practical_tips() {
    printf("=== 示例11：实用技巧总结 ===\n\n");
    
    printf("版本信息：\n");
    printf("  版本号: %s\n", VERSION_STRING);
    printf("  编译日期: %s\n", __DATE__);
    printf("  编译时间: %s\n", __TIME__);
    
    printf("\n调试信息宏：\n");
    printf("  #define TRACE() printf(\"%%s:%%d\\n\", __FILE__, __LINE__)\n");
    printf("  #define FUNC_TRACE() printf(\"Enter %%s()\\n\", __func__)\n");
    
    printf("\n平台适配宏：\n");
    printf("  #ifdef _WIN32\n");
    printf("    #define PATH_SEP '\\\\'\n");
    printf("  #else\n");
    printf("    #define PATH_SEP '/'\n");
    printf("  #endif\n");
    
    printf("\n类型安全宏：\n");
    printf("  #define NEW(type) ((type*)malloc(sizeof(type)))\n");
    printf("  #define NEW_ARRAY(type, n) ((type*)calloc(n, sizeof(type)))\n");
    
    printf("\n错误处理宏：\n");
    printf("  #define CHECK(expr) \\\n");
    printf("    if (!(expr)) { \\\n");
    printf("      fprintf(stderr, \"Check failed: %%s\\n\", #expr); \\\n");
    printf("      return -1; \\\n");
    printf("    }\n");
    
    printf("\n");
}

int main() {
    printf("╔═══════════════════════════════════════╗\n");
    printf("║   第12章：预处理器与宏编程            ║\n");
    printf("║   12.5 预定义宏和实用技巧             ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
    
    example_standard_macros();
    example_compiler_macros();
    example_platform_macros();
    example_architecture_macros();
    example_logging_macros();
    example_benchmark_macros();
    example_static_assert();
    example_alignment_macros();
    example_bit_macros();
    example_container_macros();
    example_practical_tips();
    
    printf("═════════════════════════════════════════\n");
    printf("预定义宏总结：\n");
    printf("═════════════════════════════════════════\n");
    printf("标准预定义宏：\n");
    printf("  __FILE__        当前文件名\n");
    printf("  __LINE__        当前行号\n");
    printf("  __func__        当前函数名\n");
    printf("  __DATE__        编译日期\n");
    printf("  __TIME__        编译时间\n");
    printf("  __STDC_VERSION__C标准版本\n");
    printf("\n");
    printf("编译器宏：\n");
    printf("  __GNUC__        GCC编译器\n");
    printf("  __clang__       Clang编译器\n");
    printf("  _MSC_VER        MSVC编译器\n");
    printf("\n");
    printf("平台宏：\n");
    printf("  _WIN32          Windows\n");
    printf("  __linux__       Linux\n");
    printf("  __APPLE__       macOS/iOS\n");
    printf("  __ANDROID__     Android\n");
    printf("\n");
    printf("实用技巧：\n");
    printf("  ✓ 日志系统\n");
    printf("  ✓ 性能测量\n");
    printf("  ✓ 编译时断言\n");
    printf("  ✓ 位操作\n");
    printf("  ✓ 内存对齐\n");
    printf("  ✓ 容器操作\n");
    printf("\n");
    printf("最佳实践：\n");
    printf("  • 合理使用预定义宏\n");
    printf("  • 构建实用宏库\n");
    printf("  • 注意跨平台兼容性\n");
    printf("  • 适当使用内联函数替代宏\n");
    printf("═════════════════════════════════════════\n");
    
    return 0;
}

/*
 * 编译和运行：
 *   gcc 12.5_predefined_macros.c -o 12.5
 *   ./12.5
 * 
 * C11特性编译：
 *   gcc -std=c11 12.5_predefined_macros.c -o 12.5
 * 
 * 学习要点：
 *   1. 掌握常用预定义宏
 *   2. 了解编译器和平台识别
 *   3. 学习实用宏的设计模式
 *   4. 理解宏在实际项目中的应用
 *   5. 知道何时使用宏、何时使用函数
 * 
 * 实践建议：
 *   • 构建自己的日志宏库
 *   • 实现跨平台代码
 *   • 创建性能测量工具
 *   • 设计类型安全的宏
 * 
 * 第12章完成！
 * 下一步：学习第13章 - 高级内存管理
 */
