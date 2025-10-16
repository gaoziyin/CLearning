/*
 * 第八章：高级主题
 * 8.4 命令行参数
 * 
 * 学习目标：
 * 1. 理解命令行参数的概念
 * 2. 掌握argc和argv的使用
 * 3. 学习参数解析技巧
 * 4. 了解命令行程序设计模式
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 显示帮助信息
void showHelp(const char *programName) {
    printf("用法: %s [选项] [参数]\n\n", programName);
    printf("选项:\n");
    printf("  -h, --help      显示帮助信息\n");
    printf("  -v, --version   显示版本信息\n");
    printf("  -f <file>       指定输入文件\n");
    printf("  -o <file>       指定输出文件\n");
    printf("  -n <number>     指定数值\n");
    printf("  -d, --debug     启用调试模式\n");
    printf("\n示例:\n");
    printf("  %s -f input.txt -o output.txt\n", programName);
    printf("  %s --debug -n 100\n", programName);
}

// 显示版本信息
void showVersion(void) {
    printf("程序版本 1.0.0\n");
    printf("作者: C语言学习\n");
    printf("日期: 2024\n");
}

// 处理文件
void processFile(const char *inputFile, const char *outputFile) {
    printf("处理文件:\n");
    printf("  输入: %s\n", inputFile);
    printf("  输出: %s\n", outputFile ? outputFile : "标准输出");
}

int main(int argc, char *argv[]) {
    printf("=== 命令行参数 ===\n\n");
    
    // 1. 基本概念
    printf("1. 命令行参数基础:\n");
    printf("argc = %d (参数个数)\n", argc);
    printf("argv[0] = %s (程序名)\n\n", argv[0]);
    
    // 2. 显示所有参数
    printf("2. 所有命令行参数:\n");
    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = \"%s\"\n", i, argv[i]);
    }
    printf("\n");
    
    // 3. 无参数情况
    if (argc == 1) {
        printf("3. 未提供参数\n");
        printf("提示: 使用 -h 或 --help 查看帮助\n\n");
    }
    
    // 4. 解析参数
    printf("4. 参数解析:\n");
    
    char *inputFile = NULL;
    char *outputFile = NULL;
    int number = 0;
    int debugMode = 0;
    
    // 遍历参数
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            showHelp(argv[0]);
            return 0;
        }
        else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
            showVersion();
            return 0;
        }
        else if (strcmp(argv[i], "-f") == 0) {
            if (i + 1 < argc) {
                inputFile = argv[++i];
                printf("输入文件: %s\n", inputFile);
            } else {
                fprintf(stderr, "错误: -f 需要文件名参数\n");
                return 1;
            }
        }
        else if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                outputFile = argv[++i];
                printf("输出文件: %s\n", outputFile);
            } else {
                fprintf(stderr, "错误: -o 需要文件名参数\n");
                return 1;
            }
        }
        else if (strcmp(argv[i], "-n") == 0) {
            if (i + 1 < argc) {
                number = atoi(argv[++i]);
                printf("数值: %d\n", number);
            } else {
                fprintf(stderr, "错误: -n 需要数值参数\n");
                return 1;
            }
        }
        else if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--debug") == 0) {
            debugMode = 1;
            printf("调试模式: 启用\n");
        }
        else {
            printf("未知参数: %s\n", argv[i]);
        }
    }
    printf("\n");
    
    // 5. 参数验证
    printf("5. 参数验证:\n");
    if (inputFile && outputFile) {
        printf("配置完整，可以执行\n");
        processFile(inputFile, outputFile);
    } else if (inputFile) {
        printf("只有输入文件，使用默认输出\n");
        processFile(inputFile, NULL);
    } else if (argc > 1) {
        printf("配置不完整\n");
    }
    printf("\n");
    
    // 6. 数值参数处理
    if (number > 0) {
        printf("6. 数值参数处理:\n");
        printf("处理数值: %d\n", number);
        printf("计算结果: %d\n", number * 2);
        printf("\n");
    }
    
    // 7. 调试模式
    if (debugMode) {
        printf("7. 调试信息:\n");
        printf("程序名: %s\n", argv[0]);
        printf("参数数: %d\n", argc);
        printf("输入文件: %s\n", inputFile ? inputFile : "未指定");
        printf("输出文件: %s\n", outputFile ? outputFile : "未指定");
        printf("数值: %d\n", number);
        printf("\n");
    }
    
    // 8. 示例：简单计算器
    printf("8. 简单计算器示例:\n");
    printf("用法示例: program 10 + 20\n");
    
    if (argc == 4) {
        int a = atoi(argv[1]);
        char op = argv[2][0];
        int b = atoi(argv[3]);
        int result = 0;
        
        switch (op) {
            case '+':
                result = a + b;
                printf("%d + %d = %d\n", a, b, result);
                break;
            case '-':
                result = a - b;
                printf("%d - %d = %d\n", a, b, result);
                break;
            case '*':
            case 'x':
                result = a * b;
                printf("%d * %d = %d\n", a, b, result);
                break;
            case '/':
                if (b != 0) {
                    result = a / b;
                    printf("%d / %d = %d\n", a, b, result);
                } else {
                    printf("错误: 除数不能为0\n");
                }
                break;
            default:
                printf("未知运算符: %c\n", op);
        }
    }
    printf("\n");
    
    // 9. 环境变量（扩展知识）
    printf("9. 环境变量:\n");
    printf("PATH环境变量的一部分:\n");
    
    // 注意：main可以有第三个参数envp
    // int main(int argc, char *argv[], char *envp[])
    
    char *path = getenv("PATH");
    if (path) {
        // 只显示前100个字符
        printf("  %.100s...\n", path);
    }
    
    char *home = getenv("HOME");
    if (home) {
        printf("HOME = %s\n", home);
    }
    
    char *user = getenv("USER");
    if (user) {
        printf("USER = %s\n", user);
    }
    printf("\n");
    
    // 10. 参数解析最佳实践
    printf("10. 命令行程序设计模式:\n");
    printf("1. 提供 -h 或 --help 选项\n");
    printf("2. 提供 -v 或 --version 选项\n");
    printf("3. 使用短选项 (-f) 和长选项 (--file)\n");
    printf("4. 验证参数完整性\n");
    printf("5. 提供友好的错误信息\n");
    printf("6. 使用返回码表示状态\n");
    printf("7. 支持标准输入/输出\n");
    printf("8. 文档化所有选项\n\n");
    
    // 11. 返回码
    printf("11. 程序返回码:\n");
    printf("0  - 成功\n");
    printf("1  - 一般错误\n");
    printf("2  - 参数错误\n");
    printf("非0 - 表示错误\n\n");
    
    // 12. 实际示例：文件处理程序
    printf("12. 典型命令行程序框架:\n");
    printf("\n");
    printf("/* 文件处理程序示例 */\n");
    printf("int main(int argc, char *argv[]) {\n");
    printf("    // 1. 检查参数数量\n");
    printf("    if (argc < 2) {\n");
    printf("        showUsage(argv[0]);\n");
    printf("        return 1;\n");
    printf("    }\n");
    printf("    \n");
    printf("    // 2. 解析参数\n");
    printf("    Config config = parseArgs(argc, argv);\n");
    printf("    \n");
    printf("    // 3. 验证参数\n");
    printf("    if (!validateConfig(&config)) {\n");
    printf("        return 2;\n");
    printf("    }\n");
    printf("    \n");
    printf("    // 4. 执行操作\n");
    printf("    int result = process(&config);\n");
    printf("    \n");
    printf("    // 5. 返回状态码\n");
    printf("    return result;\n");
    printf("}\n\n");
    
    // 13. getopt函数（标准库）
    printf("13. getopt函数（高级）:\n");
    printf("标准库提供getopt用于解析参数\n");
    printf("\n");
    printf("#include <unistd.h>\n");
    printf("int opt;\n");
    printf("while ((opt = getopt(argc, argv, \"hf:o:\")) != -1) {\n");
    printf("    switch (opt) {\n");
    printf("        case 'h': showHelp(); break;\n");
    printf("        case 'f': inputFile = optarg; break;\n");
    printf("        case 'o': outputFile = optarg; break;\n");
    printf("    }\n");
    printf("}\n\n");
    
    // 14. 常见使用场景
    printf("14. 命令行程序常见场景:\n");
    printf("- 文件处理工具\n");
    printf("- 数据转换程序\n");
    printf("- 批处理脚本\n");
    printf("- 系统管理工具\n");
    printf("- 构建工具\n");
    printf("- 测试工具\n");
    printf("- 命令行界面\n\n");
    
    // 15. 参数类型
    printf("15. 参数类型:\n");
    printf("位置参数: command file1 file2\n");
    printf("选项参数: command -f file\n");
    printf("标志参数: command --verbose\n");
    printf("键值参数: command --key=value\n\n");
    
    // 16. 错误处理
    printf("16. 错误处理示例:\n");
    if (argc > 1 && argv[1][0] == '-' && strlen(argv[1]) == 2) {
        char option = argv[1][1];
        if (option != 'h' && option != 'v' && option != 'f' && 
            option != 'o' && option != 'n' && option != 'd') {
            fprintf(stderr, "错误: 未知选项 '-%c'\n", option);
            fprintf(stderr, "使用 -h 查看帮助\n");
        }
    }
    printf("\n");
    
    // 17. 程序使用示例
    printf("17. 本程序使用示例:\n");
    printf("基本用法:\n");
    printf("  %s\n", argv[0]);
    printf("\n显示帮助:\n");
    printf("  %s -h\n", argv[0]);
    printf("\n显示版本:\n");
    printf("  %s -v\n", argv[0]);
    printf("\n处理文件:\n");
    printf("  %s -f input.txt -o output.txt\n", argv[0]);
    printf("\n启用调试:\n");
    printf("  %s --debug -n 100\n", argv[0]);
    printf("\n组合使用:\n");
    printf("  %s -f data.txt -o result.txt -n 50 -d\n", argv[0]);
    printf("\n");
    
    // 18. Windows vs Unix
    printf("18. 平台差异:\n");
    printf("Windows: 使用 / 或 - 作为选项前缀\n");
    printf("  例如: program /h 或 program -h\n");
    printf("\nUnix/Linux: 使用 - 或 -- 作为选项前缀\n");
    printf("  例如: program -h 或 program --help\n\n");
    
    // 19. 参数传递注意事项
    printf("19. 参数传递注意事项:\n");
    printf("1. argv[0] 是程序名（可能是路径）\n");
    printf("2. argv[argc] 是 NULL\n");
    printf("3. 参数都是字符串类型\n");
    printf("4. 需要转换为其他类型\n");
    printf("5. 空格分隔参数\n");
    printf("6. 引号包含空格的参数\n");
    printf("7. 特殊字符需要转义\n\n");
    
    // 20. 总结
    printf("20. 命令行参数总结:\n");
    printf("main函数原型:\n");
    printf("  int main(int argc, char *argv[])\n");
    printf("  int main(int argc, char **argv)\n");
    printf("\nargc: 参数个数（包含程序名）\n");
    printf("argv: 参数数组（字符串指针数组）\n");
    printf("\n关键技能:\n");
    printf("1. 遍历argv数组\n");
    printf("2. 使用strcmp比较参数\n");
    printf("3. 使用atoi/atof转换类型\n");
    printf("4. 验证参数完整性\n");
    printf("5. 提供友好的用户界面\n");
    printf("6. 处理错误情况\n");
    printf("7. 返回适当的状态码\n");
    
    return 0;
}

/*
 * 知识点总结：
 * 
 * 命令行参数概念：
 * 
 * 定义：
 * - 程序启动时传递的参数
 * - 在命令行输入
 * - 通过main函数接收
 * 
 * 格式：
 * program arg1 arg2 arg3 ...
 * 
 * main函数原型：
 * 
 * 标准形式：
 * int main(int argc, char *argv[])
 * 
 * 等价形式：
 * int main(int argc, char **argv)
 * 
 * 扩展形式（非标准）：
 * int main(int argc, char *argv[], char *envp[])
 * 
 * argc和argv：
 * 
 * argc (argument count):
 * - 参数个数
 * - 包括程序名
 * - 至少为1
 * - 类型：int
 * 
 * argv (argument vector):
 * - 参数数组
 * - argv[0]: 程序名
 * - argv[1]到argv[argc-1]: 实际参数
 * - argv[argc]: NULL
 * - 类型：char*数组
 * 
 * 示例：
 * 命令: program hello world
 * argc = 3
 * argv[0] = "program"
 * argv[1] = "hello"
 * argv[2] = "world"
 * argv[3] = NULL
 * 
 * 参数类型：
 * 
 * 1. 位置参数：
 *    command file1 file2
 *    - 顺序重要
 *    - 按位置解析
 * 
 * 2. 选项参数：
 *    command -f file
 *    - 带标志
 *    - 顺序灵活
 * 
 * 3. 标志参数：
 *    command --verbose
 *    - 布尔型
 *    - 有或无
 * 
 * 4. 键值参数：
 *    command --key=value
 *    - 带值的选项
 * 
 * 参数解析：
 * 
 * 基本模式：
 * for (int i = 1; i < argc; i++) {
 *     if (strcmp(argv[i], "-h") == 0) {
 *         // 处理-h选项
 *     } else if (strcmp(argv[i], "-f") == 0) {
 *         // 获取下一个参数
 *         if (i + 1 < argc) {
 *             filename = argv[++i];
 *         }
 *     }
 * }
 * 
 * 类型转换：
 * 
 * 字符串到整数：
 * int num = atoi(argv[i]);
 * 
 * 字符串到浮点：
 * double val = atof(argv[i]);
 * 
 * 字符串到长整数：
 * long num = atol(argv[i]);
 * long long num = atoll(argv[i]);
 * 
 * 更安全的转换：
 * char *endptr;
 * long num = strtol(argv[i], &endptr, 10);
 * if (*endptr != '\0') {
 *     // 转换失败
 * }
 * 
 * 选项风格：
 * 
 * Unix风格：
 * -h           短选项
 * --help       长选项
 * -f file      带参数选项
 * --file=name  长选项带值
 * 
 * Windows风格：
 * /h           选项
 * /f:file      选项带值
 * 
 * GNU风格：
 * -abc         组合短选项（-a -b -c）
 * --option     长选项
 * 
 * getopt函数：
 * 
 * 包含头文件：
 * #include <unistd.h>  // Unix
 * 
 * 用法：
 * int opt;
 * while ((opt = getopt(argc, argv, "hf:o:")) != -1) {
 *     switch (opt) {
 *         case 'h':
 *             showHelp();
 *             break;
 *         case 'f':
 *             inputFile = optarg;
 *             break;
 *         case 'o':
 *             outputFile = optarg;
 *             break;
 *         case '?':
 *             // 未知选项
 *             break;
 *     }
 * }
 * 
 * 选项字符串：
 * "hf:o:"
 * h - 无参数选项
 * f: - 带参数选项
 * o: - 带参数选项
 * 
 * getopt_long：
 * 
 * 支持长选项：
 * struct option long_options[] = {
 *     {"help",    no_argument,       0, 'h'},
 *     {"file",    required_argument, 0, 'f'},
 *     {"output",  required_argument, 0, 'o'},
 *     {0, 0, 0, 0}
 * };
 * 
 * 环境变量：
 * 
 * 获取环境变量：
 * char *value = getenv("VAR_NAME");
 * if (value != NULL) {
 *     // 使用value
 * }
 * 
 * 设置环境变量：
 * setenv("VAR_NAME", "value", 1);
 * 
 * 常见环境变量：
 * PATH, HOME, USER, SHELL, LANG等
 * 
 * 返回码：
 * 
 * 标准约定：
 * 0   - 成功
 * 1   - 一般错误
 * 2   - 参数错误
 * 非0 - 失败
 * 
 * 使用：
 * return 0;  // 成功
 * return 1;  // 失败
 * exit(0);   // 任何地方退出
 * 
 * Shell中检查：
 * $? (Unix)
 * %ERRORLEVEL% (Windows)
 * 
 * 最佳实践：
 * 
 * 1. 提供帮助：
 *    -h, --help
 * 
 * 2. 提供版本：
 *    -v, --version
 * 
 * 3. 验证参数：
 *    检查必需参数
 *    验证值范围
 * 
 * 4. 错误处理：
 *    友好的错误信息
 *    使用stderr
 *    返回适当错误码
 * 
 * 5. 文档化：
 *    清晰的用法说明
 *    示例命令
 *    选项说明
 * 
 * 6. 灵活性：
 *    支持标准输入/输出
 *    允许选项组合
 *    合理的默认值
 * 
 * 7. 一致性：
 *    遵循平台惯例
 *    使用标准选项名
 * 
 * 常见错误：
 * 
 * 1. 不检查argc：
 *    argv[1]可能不存在
 * 
 * 2. 数组越界：
 *    访问argv[i]前检查i < argc
 * 
 * 3. 不验证参数：
 *    假设参数总是有效
 * 
 * 4. 忘记类型转换：
 *    直接使用字符串作为数字
 * 
 * 5. 不处理空格：
 *    含空格的参数需要引号
 * 
 * 应用场景：
 * 
 * - 命令行工具
 * - 批处理程序
 * - 自动化脚本
 * - 系统管理
 * - 数据处理
 * - 文件转换
 * - 测试工具
 * - 构建系统
 * 
 * 调试技巧：
 * 
 * 1. 打印所有参数
 * 2. 逐个验证
 * 3. 测试边界情况
 * 4. 使用调试器
 * 5. 添加详细日志
 */
