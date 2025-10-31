/*
 * 第十二章：预处理器与宏编程
 * 12.4 高级宏编程技巧
 * 
 * 本文件详细讲解C语言高级宏编程技术
 * 编译命令：gcc 12.4_macro_techniques.c -o 12.4
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 示例1：# 运算符（字符串化 Stringification）
#define TO_STRING(x) #x
#define PRINT_VALUE(var) printf(#var " = %d\n", (var))
#define PRINT_EXPR(expr) printf(#expr " = %d\n", (expr))

void example_stringification() {
    printf("=== 示例1：# 字符串化运算符 ===\n\n");
    
    int age = 25;
    int count = 100;
    
    printf("基本使用：\n");
    printf("  TO_STRING(Hello) = \"%s\"\n", TO_STRING(Hello));
    printf("  TO_STRING(123) = \"%s\"\n", TO_STRING(123));
    printf("  TO_STRING(x + y) = \"%s\"\n", TO_STRING(x + y));
    
    printf("\n实用示例：\n");
    PRINT_VALUE(age);
    PRINT_VALUE(count);
    PRINT_EXPR(age + 10);
    PRINT_EXPR(count * 2);
    
    printf("\n# 运算符的作用：\n");
    printf("  • 将宏参数转换为字符串\n");
    printf("  • 保留参数的原始文本\n");
    printf("  • 常用于调试输出\n\n");
}

// 示例2：## 运算符（标记连接 Token Pasting）
#define CONCAT(a, b) a##b
#define VAR_NAME(prefix, num) prefix##num
#define MAKE_FUNCTION(type, name) type get_##name() { return name; }

void example_token_pasting() {
    printf("=== 示例2：## 标记连接运算符 ===\n\n");
    
    int var1 = 10;
    int var2 = 20;
    int var3 = 30;
    
    printf("基本使用：\n");
    printf("  CONCAT(var, 1) = %d\n", CONCAT(var, 1));
    printf("  CONCAT(var, 2) = %d\n", CONCAT(var, 2));
    printf("  CONCAT(var, 3) = %d\n", CONCAT(var, 3));
    
    // 动态创建变量名
    int VAR_NAME(value_, 1) = 100;
    int VAR_NAME(value_, 2) = 200;
    printf("\n动态变量名：\n");
    printf("  value_1 = %d\n", value_1);
    printf("  value_2 = %d\n", value_2);
    
    printf("\n## 运算符的作用：\n");
    printf("  • 连接两个标记\n");
    printf("  • 生成新的标识符\n");
    printf("  • 用于元编程\n\n");
}

// 示例3：可变参数宏 __VA_ARGS__
#define LOG(format, ...) \
    printf("[LOG] " format "\n", ##__VA_ARGS__)

#define DEBUG(format, ...) \
    printf("[DEBUG] %s:%d: " format "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define ERROR(format, ...) \
    fprintf(stderr, "[ERROR] %s:%d: " format "\n", __FILE__, __LINE__, ##__VA_ARGS__)

void example_variadic_macros() {
    printf("=== 示例3：可变参数宏 ===\n\n");
    
    printf("不同数量的参数：\n");
    LOG("程序启动");
    LOG("用户ID: %d", 12345);
    LOG("用户 %s 登录成功", "Alice");
    LOG("坐标: (%d, %d)", 10, 20);
    
    printf("\n调试输出：\n");
    int x = 42;
    DEBUG("变量值: %d", x);
    DEBUG("计算结果: %d + %d = %d", x, 10, x + 10);
    
    printf("\n错误输出：\n");
    ERROR("文件未找到: %s", "config.txt");
    
    printf("\n可变参数宏的特点：\n");
    printf("  • __VA_ARGS__ 代表所有可变参数\n");
    printf("  • ##__VA_ARGS__ 处理空参数情况\n");
    printf("  • C99标准引入\n\n");
}

// 示例4：宏递归和展开
#define REPEAT_1(x) x
#define REPEAT_2(x) REPEAT_1(x), REPEAT_1(x)
#define REPEAT_4(x) REPEAT_2(x), REPEAT_2(x)
#define REPEAT_8(x) REPEAT_4(x), REPEAT_4(x)

#define ARRAY_INIT(value, count) {REPEAT_##count(value)}

void example_macro_recursion() {
    printf("=== 示例4：宏展开技巧 ===\n\n");
    
    // 使用宏生成数组初始化
    int arr1[] = ARRAY_INIT(0, 4);  // {0, 0, 0, 0}
    int arr2[] = ARRAY_INIT(1, 8);  // {1, 1, 1, 1, 1, 1, 1, 1}
    
    printf("数组1 (4个0): ");
    for (int i = 0; i < 4; i++) {
        printf("%d ", arr1[i]);
    }
    printf("\n");
    
    printf("数组2 (8个1): ");
    for (int i = 0; i < 8; i++) {
        printf("%d ", arr2[i]);
    }
    printf("\n");
    
    printf("\n宏展开过程：\n");
    printf("  ARRAY_INIT(0, 4)\n");
    printf("  → {REPEAT_4(0)}\n");
    printf("  → {REPEAT_2(0), REPEAT_2(0)}\n");
    printf("  → {0, 0, 0, 0}\n\n");
}

// 示例5：X-Macros技术
#define COLOR_LIST \
    X(RED, 0xFF0000) \
    X(GREEN, 0x00FF00) \
    X(BLUE, 0x0000FF) \
    X(YELLOW, 0xFFFF00) \
    X(CYAN, 0x00FFFF) \
    X(MAGENTA, 0xFF00FF)

// 生成枚举
#define X(name, value) COLOR_##name = value,
typedef enum {
    COLOR_LIST
} Color;
#undef X

// 生成字符串数组
#define X(name, value) #name,
const char* color_names[] = {
    COLOR_LIST
};
#undef X

// 生成值数组
#define X(name, value) value,
int color_values[] = {
    COLOR_LIST
};
#undef X

void example_x_macros() {
    printf("=== 示例5：X-Macros技术 ===\n\n");
    
    printf("颜色列表（自动生成）：\n");
    int num_colors = sizeof(color_names) / sizeof(color_names[0]);
    
    for (int i = 0; i < num_colors; i++) {
        printf("  %-10s = 0x%06X\n", color_names[i], color_values[i]);
    }
    
    printf("\nX-Macros的优势：\n");
    printf("  ✓ 单一数据源\n");
    printf("  ✓ 自动同步\n");
    printf("  ✓ 减少重复代码\n");
    printf("  ✓ 易于维护\n");
    
    printf("\n应用场景：\n");
    printf("  • 枚举和字符串映射\n");
    printf("  • 配置表\n");
    printf("  • 消息类型定义\n");
    printf("  • 状态机\n\n");
}

// 示例6：类型安全的宏
#define TYPE_SAFE_MAX(type, a, b) \
    ({ \
        type _a = (a); \
        type _b = (b); \
        _a > _b ? _a : _b; \
    })

// 注意：这是GCC扩展（Statement Expression）
void example_type_safe_macros() {
    printf("=== 示例6：类型安全的宏（GCC扩展）===\n\n");
    
    #ifdef __GNUC__
    printf("使用语句表达式：\n");
    int x = 5, y = 3;
    printf("  MAX(5, 3) = %d\n", TYPE_SAFE_MAX(int, x++, y++));
    printf("  x = %d, y = %d (只递增一次)\n", x, y);
    
    printf("\n语句表达式的优势：\n");
    printf("  ✓ 避免参数多次求值\n");
    printf("  ✓ 可以声明局部变量\n");
    printf("  ✓ 更安全的宏\n");
    printf("  ✗ 非标准C（GCC/Clang扩展）\n");
    #else
    printf("语句表达式需要GCC或Clang编译器\n");
    #endif
    
    printf("\n");
}

// 示例7：宏的条件展开
#define VERSION 2

#if VERSION == 1
    #define API_CALL(x) api_v1_##x
#elif VERSION == 2
    #define API_CALL(x) api_v2_##x
#else
    #define API_CALL(x) api_default_##x
#endif

void api_v1_init() { printf("API v1 初始化\n"); }
void api_v2_init() { printf("API v2 初始化\n"); }

void example_conditional_macros() {
    printf("=== 示例7：条件宏展开 ===\n\n");
    
    printf("当前版本: %d\n", VERSION);
    API_CALL(init)();
    
    printf("\n根据版本选择不同实现：\n");
    printf("  VERSION=1 → api_v1_init()\n");
    printf("  VERSION=2 → api_v2_init()\n");
    printf("  其他     → api_default_init()\n");
    
    printf("\n应用场景：\n");
    printf("  • API版本兼容\n");
    printf("  • 平台适配\n");
    printf("  • 功能开关\n\n");
}

// 示例8：宏生成函数
#define DEFINE_GETTER_SETTER(type, name) \
    static type _##name; \
    type get_##name() { return _##name; } \
    void set_##name(type value) { _##name = value; }

DEFINE_GETTER_SETTER(int, width)
DEFINE_GETTER_SETTER(int, height)
DEFINE_GETTER_SETTER(float, scale)

void example_code_generation() {
    printf("=== 示例8：宏生成代码 ===\n\n");
    
    set_width(1920);
    set_height(1080);
    set_scale(1.5f);
    
    printf("生成的getter/setter：\n");
    printf("  宽度: %d\n", get_width());
    printf("  高度: %d\n", get_height());
    printf("  缩放: %.1f\n", get_scale());
    
    printf("\n自动生成的代码：\n");
    printf("  • 私有变量: _width, _height, _scale\n");
    printf("  • Getter: get_width(), get_height()...\n");
    printf("  • Setter: set_width(), set_height()...\n");
    
    printf("\n优势：\n");
    printf("  • 减少样板代码\n");
    printf("  • 统一接口风格\n");
    printf("  • 易于维护\n\n");
}

// 示例9：断言宏
#ifdef NDEBUG
    #define ASSERT(condition, message) ((void)0)
#else
    #define ASSERT(condition, message) \
        do { \
            if (!(condition)) { \
                fprintf(stderr, "断言失败: %s\n", message); \
                fprintf(stderr, "  文件: %s\n", __FILE__); \
                fprintf(stderr, "  行号: %d\n", __LINE__); \
                fprintf(stderr, "  函数: %s\n", __func__); \
                fprintf(stderr, "  条件: %s\n", #condition); \
                abort(); \
            } \
        } while(0)
#endif

void example_assert_macro() {
    printf("=== 示例9：自定义断言宏 ===\n\n");
    
    int value = 10;
    
    ASSERT(value > 0, "值必须为正数");
    printf("断言通过: value = %d\n", value);
    
    ASSERT(value < 100, "值不能超过100");
    printf("断言通过: value < 100\n");
    
    printf("\n断言宏的特点：\n");
    printf("  • 调试版本：检查条件\n");
    printf("  • 发布版本：编译为空操作\n");
    printf("  • 提供详细错误信息\n");
    printf("  • 包含文件名、行号、函数名\n");
    
    // 下面这行会触发断言（已注释）
    // ASSERT(value > 100, "这会失败！");
    
    printf("\n");
}

// 示例10：宏库示例 - 容器操作
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define ARRAY_FOREACH(arr, size, i) \
    for (size_t i = 0; i < (size); i++)

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define CLAMP(x, min, max) (MIN(MAX(x, min), max))
#define SWAP(a, b, type) \
    do { type _tmp = (a); (a) = (b); (b) = _tmp; } while(0)

void example_macro_library() {
    printf("=== 示例10：实用宏库 ===\n\n");
    
    int numbers[] = {5, 2, 8, 1, 9, 3};
    size_t size = ARRAY_SIZE(numbers);
    
    printf("原始数组: ");
    ARRAY_FOREACH(numbers, size, i) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    // 使用宏进行操作
    printf("\n宏操作演示：\n");
    printf("  MIN(5, 3) = %d\n", MIN(5, 3));
    printf("  MAX(5, 3) = %d\n", MAX(5, 3));
    printf("  CLAMP(15, 0, 10) = %d\n", CLAMP(15, 0, 10));
    printf("  CLAMP(-5, 0, 10) = %d\n", CLAMP(-5, 0, 10));
    
    int a = 10, b = 20;
    printf("\n交换前: a = %d, b = %d\n", a, b);
    SWAP(a, b, int);
    printf("交换后: a = %d, b = %d\n", a, b);
    
    printf("\n常用宏库分类：\n");
    printf("  1. 数值运算: MIN, MAX, ABS, CLAMP\n");
    printf("  2. 数组操作: SIZE, FOREACH, SORT\n");
    printf("  3. 调试工具: ASSERT, LOG, DEBUG\n");
    printf("  4. 类型检查: IS_POINTER, IS_ARRAY\n");
    printf("  5. 位操作: BIT_SET, BIT_CLEAR\n\n");
}

// 示例11：宏编程最佳实践
void example_best_practices() {
    printf("=== 示例11：宏编程最佳实践 ===\n\n");
    
    printf("1. 命名规范\n");
    printf("   ✓ 全大写字母\n");
    printf("   ✓ 下划线分隔\n");
    printf("   ✓ 有意义的名称\n");
    printf("   示例: MAX_SIZE, IS_VALID, ARRAY_FOREACH\n");
    
    printf("\n2. 括号使用\n");
    printf("   ✓ 参数加括号\n");
    printf("   ✓ 整个表达式加括号\n");
    printf("   错误: #define SQR(x) x*x\n");
    printf("   正确: #define SQR(x) ((x)*(x))\n");
    
    printf("\n3. 副作用避免\n");
    printf("   ✗ 不要用++、--\n");
    printf("   ✗ 不要有隐藏的副作用\n");
    printf("   ✓ 使用语句表达式（GCC）\n");
    printf("   ✓ 或者改用inline函数\n");
    
    printf("\n4. 多行宏格式\n");
    printf("   ✓ 使用do-while(0)\n");
    printf("   ✓ 反斜杠对齐\n");
    printf("   ✓ 缩进清晰\n");
    
    printf("\n5. 文档注释\n");
    printf("   • 说明宏的用途\n");
    printf("   • 参数含义\n");
    printf("   • 注意事项\n");
    printf("   • 使用示例\n");
    
    printf("\n6. 何时不用宏\n");
    printf("   ✗ 复杂逻辑 → 用函数\n");
    printf("   ✗ 类型相关 → 用函数重载（C++）\n");
    printf("   ✗ 需要调试 → 用函数\n");
    printf("   ✗ 简单常量 → 用const/enum\n\n");
}

int main() {
    printf("╔═══════════════════════════════════════╗\n");
    printf("║   第12章：预处理器与宏编程            ║\n");
    printf("║   12.4 高级宏编程技巧                 ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
    
    example_stringification();
    example_token_pasting();
    example_variadic_macros();
    example_macro_recursion();
    example_x_macros();
    example_type_safe_macros();
    example_conditional_macros();
    example_code_generation();
    example_assert_macro();
    example_macro_library();
    example_best_practices();
    
    printf("═════════════════════════════════════════\n");
    printf("高级宏技巧总结：\n");
    printf("═════════════════════════════════════════\n");
    printf("核心运算符：\n");
    printf("  #           字符串化\n");
    printf("  ##          标记连接\n");
    printf("  __VA_ARGS__ 可变参数\n");
    printf("\n");
    printf("高级技术：\n");
    printf("  • X-Macros      统一数据源\n");
    printf("  • 代码生成      减少重复\n");
    printf("  • 条件展开      版本适配\n");
    printf("  • 语句表达式    避免副作用（GCC）\n");
    printf("\n");
    printf("应用场景：\n");
    printf("  ✓ 调试日志\n");
    printf("  ✓ 断言检查\n");
    printf("  ✓ 代码生成\n");
    printf("  ✓ 枚举映射\n");
    printf("  ✓ 通用容器\n");
    printf("\n");
    printf("注意事项：\n");
    printf("  • 复杂宏难以调试\n");
    printf("  • 注意副作用\n");
    printf("  • 保持简单\n");
    printf("  • 优先考虑函数\n");
    printf("═════════════════════════════════════════\n");
    
    return 0;
}

/*
 * 编译和运行：
 *   gcc 12.4_macro_techniques.c -o 12.4
 *   ./12.4
 * 
 * GCC扩展特性：
 *   gcc -std=gnu99 12.4_macro_techniques.c -o 12.4
 * 
 * 学习要点：
 *   1. 掌握#和##运算符
 *   2. 理解可变参数宏
 *   3. 学习X-Macros技术
 *   4. 了解宏的高级应用
 *   5. 知道何时用宏、何时用函数
 * 
 * 实践建议：
 *   • 尝试实现自己的调试宏
 *   • 使用X-Macros管理枚举
 *   • 创建实用的宏库
 * 
 * 下一步：
 *   学习12.5 预定义宏
 */
