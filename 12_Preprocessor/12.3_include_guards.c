/*
 * 第十二章：预处理器与宏编程
 * 12.3 头文件保护与包含
 * 
 * 本文件详细讲解C语言头文件保护和文件包含技巧
 * 编译命令：gcc 12.3_include_guards.c -o 12.3
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 示例1：头文件保护的必要性
/*
 * 问题演示：没有头文件保护会导致重复定义
 * 
 * 假设有以下文件结构：
 * 
 * types.h:
 *   typedef struct { int x, y; } Point;
 * 
 * graphics.h:
 *   #include "types.h"
 *   void draw_point(Point p);
 * 
 * main.c:
 *   #include "types.h"
 *   #include "graphics.h"  // 错误！Point被定义两次
 */

void example_why_guards() {
    printf("=== 示例1：为什么需要头文件保护 ===\n\n");
    
    printf("问题场景：\n");
    printf("  main.c 包含 types.h\n");
    printf("  main.c 包含 graphics.h\n");
    printf("  graphics.h 也包含 types.h\n");
    printf("  ↓\n");
    printf("  结果：types.h的内容被包含两次！\n");
    printf("  错误：重复定义\n");
    
    printf("\n没有保护的后果：\n");
    printf("  ✗ 编译错误（重复定义）\n");
    printf("  ✗ 编译时间增加\n");
    printf("  ✗ 宏定义冲突\n");
    printf("  ✗ 类型定义冲突\n\n");
}

// 示例2：传统的头文件保护（Include Guards）
void example_traditional_guards() {
    printf("=== 示例2：传统头文件保护 ===\n\n");
    
    printf("标准模式：\n");
    printf("  #ifndef MYHEADER_H\n");
    printf("  #define MYHEADER_H\n");
    printf("  \n");
    printf("  // 头文件内容\n");
    printf("  \n");
    printf("  #endif // MYHEADER_H\n");
    
    printf("\n工作原理：\n");
    printf("  1. 第一次包含：\n");
    printf("     MYHEADER_H未定义 → 定义它 → 处理内容\n");
    printf("  2. 第二次包含：\n");
    printf("     MYHEADER_H已定义 → 跳过内容\n");
    
    printf("\n命名规范：\n");
    printf("  • 使用全大写\n");
    printf("  • 基于文件名\n");
    printf("  • 添加_H后缀\n");
    printf("  • 避免冲突（可加项目前缀）\n");
    printf("  示例：\n");
    printf("    utils.h    → UTILS_H\n");
    printf("    config.h   → CONFIG_H\n");
    printf("    my_types.h → MY_TYPES_H\n\n");
}

// 示例3：#pragma once（现代方法）
void example_pragma_once() {
    printf("=== 示例3：#pragma once ===\n\n");
    
    printf("使用方法：\n");
    printf("  #pragma once\n");
    printf("  \n");
    printf("  // 头文件内容\n");
    
    printf("\n优点：\n");
    printf("  ✓ 简洁（只需一行）\n");
    printf("  ✓ 不会命名冲突\n");
    printf("  ✓ 编译速度更快\n");
    printf("  ✓ 不易出错\n");
    
    printf("\n缺点：\n");
    printf("  ✗ 非标准C（虽然广泛支持）\n");
    printf("  ✗ 某些老编译器不支持\n");
    printf("  ✗ 符号链接可能有问题\n");
    
    printf("\n编译器支持：\n");
    printf("  ✓ GCC/G++\n");
    printf("  ✓ Clang\n");
    printf("  ✓ MSVC\n");
    printf("  ✓ Intel C++\n");
    printf("  ? 嵌入式编译器（需检查）\n\n");
}

// 示例4：两种方法的比较
void example_comparison() {
    printf("=== 示例4：Include Guards vs #pragma once ===\n\n");
    
    printf("┌──────────────────┬──────────────┬──────────────┐\n");
    printf("│     特性         │ Include Guard│ #pragma once │\n");
    printf("├──────────────────┼──────────────┼──────────────┤\n");
    printf("│ 标准兼容性       │ 标准C        │ 非标准       │\n");
    printf("│ 编译器支持       │ 所有         │ 大部分现代   │\n");
    printf("│ 代码量           │ 3行          │ 1行          │\n");
    printf("│ 命名冲突风险     │ 存在         │ 无           │\n");
    printf("│ 编译速度         │ 较慢         │ 较快         │\n");
    printf("│ 可移植性         │ 完美         │ 很好         │\n");
    printf("│ 维护难度         │ 需要命名     │ 简单         │\n");
    printf("└──────────────────┴──────────────┴──────────────┘\n");
    
    printf("\n推荐做法：\n");
    printf("  • 新项目: 优先使用 #pragma once\n");
    printf("  • 库项目: 使用 Include Guards（兼容性）\n");
    printf("  • 折中方案: 两者都用\n");
    printf("    #ifndef MYHEADER_H\n");
    printf("    #define MYHEADER_H\n");
    printf("    #pragma once\n");
    printf("    // ...\n");
    printf("    #endif\n\n");
}

// 示例5：正确的头文件结构
void example_header_structure() {
    printf("=== 示例5：正确的头文件结构 ===\n\n");
    
    printf("完整的头文件模板：\n");
    printf("\n");
    printf("  /*\n");
    printf("   * mylib.h - 简短描述\n");
    printf("   * 作者、日期、版权等信息\n");
    printf("   */\n");
    printf("  \n");
    printf("  #ifndef MYLIB_H\n");
    printf("  #define MYLIB_H\n");
    printf("  \n");
    printf("  // 1. 系统头文件\n");
    printf("  #include <stdio.h>\n");
    printf("  #include <stdlib.h>\n");
    printf("  \n");
    printf("  // 2. 第三方库头文件\n");
    printf("  // #include <external_lib.h>\n");
    printf("  \n");
    printf("  // 3. 项目内部头文件\n");
    printf("  // #include \"project_header.h\"\n");
    printf("  \n");
    printf("  // 4. C++兼容性\n");
    printf("  #ifdef __cplusplus\n");
    printf("  extern \"C\" {\n");
    printf("  #endif\n");
    printf("  \n");
    printf("  // 5. 宏定义\n");
    printf("  #define MYLIB_VERSION 1\n");
    printf("  \n");
    printf("  // 6. 类型定义\n");
    printf("  typedef struct MyStruct MyStruct;\n");
    printf("  \n");
    printf("  // 7. 函数声明\n");
    printf("  void my_function(void);\n");
    printf("  \n");
    printf("  // 8. 内联函数（如果有）\n");
    printf("  static inline int my_inline(int x) {\n");
    printf("      return x * 2;\n");
    printf("  }\n");
    printf("  \n");
    printf("  // 9. C++兼容性结束\n");
    printf("  #ifdef __cplusplus\n");
    printf("  }\n");
    printf("  #endif\n");
    printf("  \n");
    printf("  #endif // MYLIB_H\n");
    printf("\n");
}

// 示例6：#include的两种形式
void example_include_forms() {
    printf("=== 示例6：#include的形式 ===\n\n");
    
    printf("< > 形式（系统头文件）：\n");
    printf("  #include <stdio.h>\n");
    printf("  #include <stdlib.h>\n");
    printf("  搜索路径：编译器的系统目录\n");
    printf("  用途：标准库、系统头文件\n");
    
    printf("\n\" \" 形式（用户头文件）：\n");
    printf("  #include \"myheader.h\"\n");
    printf("  #include \"../common/utils.h\"\n");
    printf("  搜索路径：\n");
    printf("    1. 当前文件目录\n");
    printf("    2. -I 指定的目录\n");
    printf("    3. 系统目录（备选）\n");
    printf("  用途：项目自己的头文件\n");
    
    printf("\n路径示例：\n");
    printf("  相对路径:\n");
    printf("    #include \"header.h\"        // 同目录\n");
    printf("    #include \"../header.h\"     // 上级目录\n");
    printf("    #include \"subdir/header.h\" // 子目录\n");
    printf("  \n");
    printf("  编译时指定:\n");
    printf("    gcc -I/path/to/headers main.c\n");
    printf("    gcc -I../include -I./lib main.c\n\n");
}

// 示例7：循环包含问题
void example_circular_inclusion() {
    printf("=== 示例7：循环包含问题 ===\n\n");
    
    printf("问题场景：\n");
    printf("  a.h 包含 b.h\n");
    printf("  b.h 包含 a.h\n");
    printf("  ↓\n");
    printf("  无限循环！\n");
    
    printf("\n即使有头文件保护也会有问题：\n");
    printf("  1. 编译器处理 a.h\n");
    printf("  2. a.h 需要 b.h，开始处理 b.h\n");
    printf("  3. b.h 需要 a.h，但a.h保护符已定义\n");
    printf("  4. b.h 中无法使用 a.h 的内容\n");
    printf("  5. 导致未定义标识符错误\n");
    
    printf("\n解决方案：\n");
    printf("  方法1：前向声明\n");
    printf("    // 在b.h中\n");
    printf("    struct TypeFromA;  // 前向声明\n");
    printf("    // 使用指针: struct TypeFromA* ptr;\n");
    printf("  \n");
    printf("  方法2：重新设计\n");
    printf("    • 分离接口和实现\n");
    printf("    • 减少头文件依赖\n");
    printf("    • 使用中间头文件\n");
    printf("  \n");
    printf("  方法3：合并头文件\n");
    printf("    • 将相互依赖的放在一起\n\n");
}

// 示例8：前向声明技巧
void example_forward_declaration() {
    printf("=== 示例8：前向声明 ===\n\n");
    
    printf("前向声明的使用：\n");
    printf("\n");
    printf("  // types.h\n");
    printf("  #ifndef TYPES_H\n");
    printf("  #define TYPES_H\n");
    printf("  \n");
    printf("  // 前向声明\n");
    printf("  struct Node;\n");
    printf("  struct Tree;\n");
    printf("  \n");
    printf("  // 现在可以使用指针\n");
    printf("  struct Node {\n");
    printf("      int data;\n");
    printf("      struct Node* next;  // OK\n");
    printf("      struct Tree* tree;  // OK\n");
    printf("  };\n");
    printf("  \n");
    printf("  #endif\n");
    
    printf("\n限制：\n");
    printf("  ✓ 可以：声明指针\n");
    printf("  ✓ 可以：作为函数参数类型\n");
    printf("  ✗ 不可以：定义变量（需要完整定义）\n");
    printf("  ✗ 不可以：访问成员（需要完整定义）\n");
    printf("  ✗ 不可以：使用sizeof（需要完整定义）\n\n");
}

// 示例9：条件包含
void example_conditional_include() {
    printf("=== 示例9：条件包含 ===\n\n");
    
    printf("根据平台包含不同头文件：\n");
    printf("\n");
    printf("  #ifdef _WIN32\n");
    printf("      #include <windows.h>\n");
    printf("      #include <winsock2.h>\n");
    printf("  #elif defined(__linux__)\n");
    printf("      #include <unistd.h>\n");
    printf("      #include <sys/socket.h>\n");
    printf("  #elif defined(__APPLE__)\n");
    printf("      #include <sys/types.h>\n");
    printf("      #include <sys/socket.h>\n");
    printf("  #endif\n");
    
    printf("\n功能性条件包含：\n");
    printf("  #ifdef USE_OPENSSL\n");
    printf("      #include <openssl/ssl.h>\n");
    printf("  #endif\n");
    printf("  \n");
    printf("  #ifdef ENABLE_GUI\n");
    printf("      #include <gtk/gtk.h>\n");
    printf("  #endif\n");
    
    printf("\n版本兼容性：\n");
    printf("  #if __STDC_VERSION__ >= 201112L\n");
    printf("      #include <stdatomic.h>\n");
    printf("      #include <threads.h>\n");
    printf("  #endif\n\n");
}

// 示例10：预编译头文件（PCH）
void example_precompiled_headers() {
    printf("=== 示例10：预编译头文件 ===\n\n");
    
    printf("什么是预编译头文件？\n");
    printf("  • 编译器预先处理常用头文件\n");
    printf("  • 保存编译结果供后续使用\n");
    printf("  • 显著加快编译速度\n");
    
    printf("\n适合预编译的头文件：\n");
    printf("  ✓ 标准库头文件（stdio.h, stdlib.h等）\n");
    printf("  ✓ 第三方库头文件（很少修改）\n");
    printf("  ✓ 项目公共头文件（稳定的）\n");
    printf("  ✗ 经常修改的头文件\n");
    
    printf("\nGCC/Clang使用方法：\n");
    printf("  1. 创建 stdafx.h:\n");
    printf("       #include <stdio.h>\n");
    printf("       #include <stdlib.h>\n");
    printf("       #include <string.h>\n");
    printf("  \n");
    printf("  2. 预编译:\n");
    printf("       gcc -c stdafx.h -o stdafx.h.gch\n");
    printf("  \n");
    printf("  3. 使用:\n");
    printf("       gcc main.c  // 自动使用stdafx.h.gch\n");
    
    printf("\nMSVC使用方法：\n");
    printf("  1. 项目属性 → C/C++ → 预编译头\n");
    printf("  2. 选择"使用预编译头"\n");
    printf("  3. 指定 stdafx.h\n");
    
    printf("\n优势：\n");
    printf("  • 大型项目编译加速50%%以上\n");
    printf("  • 减少重复编译工作\n");
    printf("  • 特别适合Windows项目\n\n");
}

// 示例11：头文件组织最佳实践
void example_best_practices() {
    printf("=== 示例11：最佳实践 ===\n\n");
    
    printf("1. 最小化头文件依赖\n");
    printf("   • 只包含必需的头文件\n");
    printf("   • 尽量在.c文件中包含\n");
    printf("   • 使用前向声明减少依赖\n");
    
    printf("\n2. 头文件中避免的内容\n");
    printf("   ✗ 函数实现（除inline/static）\n");
    printf("   ✗ 全局变量定义（只能声明）\n");
    printf("   ✗ using声明（C++）\n");
    printf("   ✗ 大量的宏定义\n");
    
    printf("\n3. 包含顺序规范\n");
    printf("   a) 对应的.h文件（如果是.c文件）\n");
    printf("   b) C系统头文件\n");
    printf("   c) C++系统头文件\n");
    printf("   d) 其他库的头文件\n");
    printf("   e) 本项目的头文件\n");
    printf("   各组之间空一行\n");
    
    printf("\n4. 头文件命名\n");
    printf("   • 小写字母，下划线分隔\n");
    printf("   • 有意义的名称\n");
    printf("   • 避免通用名（如utils.h）\n");
    printf("   • 可添加项目前缀\n");
    
    printf("\n5. 头文件注释\n");
    printf("   • 文件顶部：用途说明\n");
    printf("   • 每个函数：功能、参数、返回值\n");
    printf("   • 复杂宏：使用说明和示例\n");
    printf("   • 版本和作者信息\n\n");
}

int main() {
    printf("╔═══════════════════════════════════════╗\n");
    printf("║   第12章：预处理器与宏编程            ║\n");
    printf("║   12.3 头文件保护与包含               ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
    
    example_why_guards();
    example_traditional_guards();
    example_pragma_once();
    example_comparison();
    example_header_structure();
    example_include_forms();
    example_circular_inclusion();
    example_forward_declaration();
    example_conditional_include();
    example_precompiled_headers();
    example_best_practices();
    
    printf("═════════════════════════════════════════\n");
    printf("头文件保护总结：\n");
    printf("═════════════════════════════════════════\n");
    printf("Include Guards（传统方法）：\n");
    printf("  #ifndef HEADER_H\n");
    printf("  #define HEADER_H\n");
    printf("  // 内容\n");
    printf("  #endif\n");
    printf("\n");
    printf("#pragma once（现代方法）：\n");
    printf("  #pragma once\n");
    printf("  // 内容\n");
    printf("\n");
    printf("选择建议：\n");
    printf("  • 新项目 → #pragma once\n");
    printf("  • 库项目 → Include Guards\n");
    printf("  • 需要最大兼容性 → Include Guards\n");
    printf("\n");
    printf("关键原则：\n");
    printf("  1. 所有头文件必须有保护\n");
    printf("  2. 使用唯一的保护符名称\n");
    printf("  3. 最小化头文件依赖\n");
    printf("  4. 避免循环包含\n");
    printf("  5. 合理使用前向声明\n");
    printf("  6. 遵循包含顺序规范\n");
    printf("═════════════════════════════════════════\n");
    
    return 0;
}

/*
 * 编译和运行：
 *   gcc 12.3_include_guards.c -o 12.3
 *   ./12.3
 * 
 * 学习要点：
 *   1. 理解头文件保护的必要性
 *   2. 掌握Include Guards和#pragma once
 *   3. 了解循环包含问题及解决方案
 *   4. 学会合理组织头文件
 *   5. 遵循头文件编写最佳实践
 * 
 * 实践建议：
 *   • 创建一个小型项目，实践头文件组织
 *   • 尝试不同的包含方式
 *   • 理解前向声明的使用场景
 * 
 * 下一步：
 *   学习12.4 宏编程技巧
 */
