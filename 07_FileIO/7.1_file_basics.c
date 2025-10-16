/*
 * 第七章：文件操作
 * 7.1 文件基础
 * 
 * 学习目标：
 * 1. 理解文件的概念和分类
 * 2. 掌握文件的打开和关闭
 * 3. 学习文件指针的使用
 * 4. 了解文件打开模式
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    printf("=== 文件基础 ===\n\n");
    
    // 1. 文件指针
    printf("1. 文件指针概念:\n");
    printf("FILE *fp;  // 文件指针类型\n");
    printf("用于标识和访问文件\n\n");
    
    // 2. 文件打开 - 写模式
    printf("2. 创建并写入文件:\n");
    FILE *fp1 = fopen("test1.txt", "w");  // 打开文件（写模式）
    
    if (fp1 == NULL) {
        printf("错误：无法创建文件！\n");
        return 1;
    }
    
    printf("文件 test1.txt 创建成功\n");
    fprintf(fp1, "Hello, File!\n");  // 写入文本
    fprintf(fp1, "这是第二行\n");
    fprintf(fp1, "文件操作很简单\n");
    
    fclose(fp1);  // 关闭文件（重要！）
    printf("文件已写入并关闭\n\n");
    
    // 3. 文件打开 - 读模式
    printf("3. 读取文件内容:\n");
    FILE *fp2 = fopen("test1.txt", "r");  // 打开文件（读模式）
    
    if (fp2 == NULL) {
        printf("错误：无法打开文件！\n");
        return 1;
    }
    
    char buffer[100];
    printf("文件内容：\n");
    while (fgets(buffer, sizeof(buffer), fp2) != NULL) {
        printf("  %s", buffer);  // 读取每一行
    }
    
    fclose(fp2);
    printf("文件已读取并关闭\n\n");
    
    // 4. 文件打开模式详解
    printf("4. 文件打开模式:\n");
    printf("\"r\"  - 只读（文件必须存在）\n");
    printf("\"w\"  - 只写（文件不存在则创建，存在则清空）\n");
    printf("\"a\"  - 追加（文件不存在则创建，存在则在末尾追加）\n");
    printf("\"r+\" - 读写（文件必须存在）\n");
    printf("\"w+\" - 读写（文件不存在则创建，存在则清空）\n");
    printf("\"a+\" - 读写追加（文件不存在则创建）\n\n");
    
    // 5. 追加模式
    printf("5. 追加内容到文件:\n");
    FILE *fp3 = fopen("test1.txt", "a");  // 追加模式
    
    if (fp3 != NULL) {
        fprintf(fp3, "这是追加的内容\n");
        fprintf(fp3, "不会删除原有内容\n");
        fclose(fp3);
        printf("内容已追加\n\n");
    }
    
    // 6. 验证追加结果
    printf("6. 验证追加后的文件:\n");
    fp2 = fopen("test1.txt", "r");
    if (fp2 != NULL) {
        printf("完整文件内容：\n");
        while (fgets(buffer, sizeof(buffer), fp2) != NULL) {
            printf("  %s", buffer);
        }
        fclose(fp2);
        printf("\n");
    }
    
    // 7. 文件是否存在检查
    printf("7. 检查文件是否存在:\n");
    FILE *check = fopen("nonexistent.txt", "r");
    if (check == NULL) {
        printf("文件 nonexistent.txt 不存在\n");
    } else {
        printf("文件 nonexistent.txt 存在\n");
        fclose(check);
    }
    
    check = fopen("test1.txt", "r");
    if (check == NULL) {
        printf("文件 test1.txt 不存在\n");
    } else {
        printf("文件 test1.txt 存在\n");
        fclose(check);
    }
    printf("\n");
    
    // 8. 写入多种数据类型
    printf("8. 写入不同类型数据:\n");
    FILE *fp4 = fopen("data.txt", "w");
    if (fp4 != NULL) {
        int age = 25;
        float score = 95.5;
        char name[] = "张三";
        
        fprintf(fp4, "姓名: %s\n", name);
        fprintf(fp4, "年龄: %d\n", age);
        fprintf(fp4, "成绩: %.1f\n", score);
        
        fclose(fp4);
        printf("数据已写入 data.txt\n\n");
    }
    
    // 9. 读取多种数据类型
    printf("9. 读取不同类型数据:\n");
    FILE *fp5 = fopen("data.txt", "r");
    if (fp5 != NULL) {
        char name[50];
        int age;
        float score;
        
        fscanf(fp5, "姓名: %s\n", name);
        fscanf(fp5, "年龄: %d\n", &age);
        fscanf(fp5, "成绩: %f\n", &score);
        
        printf("读取的数据:\n");
        printf("  姓名: %s\n", name);
        printf("  年龄: %d\n", age);
        printf("  成绩: %.1f\n", score);
        
        fclose(fp5);
        printf("\n");
    }
    
    // 10. 字符级读写
    printf("10. 字符级文件操作:\n");
    FILE *fp6 = fopen("chars.txt", "w");
    if (fp6 != NULL) {
        // 写入字符
        fputc('A', fp6);
        fputc('B', fp6);
        fputc('C', fp6);
        fputc('\n', fp6);
        
        fclose(fp6);
        printf("字符已写入\n");
    }
    
    // 读取字符
    FILE *fp7 = fopen("chars.txt", "r");
    if (fp7 != NULL) {
        printf("读取字符: ");
        int ch;
        while ((ch = fgetc(fp7)) != EOF) {
            printf("%c", ch);
        }
        fclose(fp7);
        printf("\n");
    }
    printf("\n");
    
    // 11. 行级读写
    printf("11. 行级文件操作:\n");
    FILE *fp8 = fopen("lines.txt", "w");
    if (fp8 != NULL) {
        fputs("第一行文本\n", fp8);
        fputs("第二行文本\n", fp8);
        fputs("第三行文本\n", fp8);
        fclose(fp8);
        printf("多行文本已写入\n");
    }
    
    FILE *fp9 = fopen("lines.txt", "r");
    if (fp9 != NULL) {
        printf("读取的行:\n");
        char line[100];
        while (fgets(line, sizeof(line), fp9) != NULL) {
            printf("  %s", line);
        }
        fclose(fp9);
        printf("\n");
    }
    
    // 12. 文件打开失败处理
    printf("12. 文件错误处理:\n");
    FILE *fp10 = fopen("/invalid/path/file.txt", "r");
    if (fp10 == NULL) {
        printf("文件打开失败！\n");
        printf("可能原因：\n");
        printf("  - 文件不存在\n");
        printf("  - 路径错误\n");
        printf("  - 权限不足\n");
        printf("  - 磁盘已满\n");
    } else {
        fclose(fp10);
    }
    printf("\n");
    
    // 13. 读写模式 r+
    printf("13. 读写模式 (r+):\n");
    FILE *fp11 = fopen("test1.txt", "r+");
    if (fp11 != NULL) {
        // 读取第一行
        char firstLine[100];
        fgets(firstLine, sizeof(firstLine), fp11);
        printf("第一行: %s", firstLine);
        
        // 在当前位置写入
        fprintf(fp11, "插入的内容\n");
        
        fclose(fp11);
        printf("r+ 模式操作完成\n\n");
    }
    
    // 14. 统计文件行数
    printf("14. 统计文件行数:\n");
    FILE *fp12 = fopen("test1.txt", "r");
    if (fp12 != NULL) {
        int lineCount = 0;
        char ch;
        
        while ((ch = fgetc(fp12)) != EOF) {
            if (ch == '\n') {
                lineCount++;
            }
        }
        
        printf("test1.txt 共有 %d 行\n", lineCount);
        fclose(fp12);
        printf("\n");
    }
    
    // 15. 文件复制
    printf("15. 文件复制:\n");
    FILE *source = fopen("test1.txt", "r");
    FILE *dest = fopen("test1_copy.txt", "w");
    
    if (source != NULL && dest != NULL) {
        char ch;
        while ((ch = fgetc(source)) != EOF) {
            fputc(ch, dest);
        }
        printf("文件复制完成: test1.txt -> test1_copy.txt\n");
    }
    
    if (source != NULL) fclose(source);
    if (dest != NULL) fclose(dest);
    printf("\n");
    
    // 16. 标准流
    printf("16. 标准输入输出流:\n");
    printf("stdin  - 标准输入（键盘）\n");
    printf("stdout - 标准输出（屏幕）\n");
    printf("stderr - 标准错误（屏幕）\n");
    
    fprintf(stdout, "这是标准输出\n");
    fprintf(stderr, "这是标准错误\n");
    printf("\n");
    
    // 17. 刷新缓冲区
    printf("17. 缓冲区操作:\n");
    FILE *fp13 = fopen("buffer.txt", "w");
    if (fp13 != NULL) {
        fprintf(fp13, "写入但未刷新");
        fflush(fp13);  // 强制刷新缓冲区
        printf("缓冲区已刷新\n");
        
        fprintf(fp13, "继续写入\n");
        fclose(fp13);  // 关闭时自动刷新
    }
    printf("\n");
    
    // 18. 临时文件
    printf("18. 临时文件:\n");
    FILE *temp = tmpfile();  // 创建临时文件
    if (temp != NULL) {
        fprintf(temp, "这是临时数据\n");
        printf("临时文件创建成功\n");
        printf("关闭后自动删除\n");
        fclose(temp);  // 自动删除
    }
    printf("\n");
    
    // 19. 文件操作完整流程
    printf("19. 完整的文件操作流程:\n");
    printf("步骤1: 声明文件指针\n");
    printf("步骤2: 打开文件（检查是否成功）\n");
    printf("步骤3: 读写操作\n");
    printf("步骤4: 关闭文件\n\n");
    
    FILE *demo = fopen("demo.txt", "w");
    if (demo == NULL) {
        printf("步骤2失败：无法打开文件\n");
        return 1;
    }
    printf("步骤2成功：文件已打开\n");
    
    fprintf(demo, "演示内容\n");
    printf("步骤3成功：数据已写入\n");
    
    fclose(demo);
    printf("步骤4成功：文件已关闭\n\n");
    
    // 20. 清理测试文件
    printf("20. 程序执行完成\n");
    printf("创建的测试文件:\n");
    printf("  - test1.txt\n");
    printf("  - data.txt\n");
    printf("  - chars.txt\n");
    printf("  - lines.txt\n");
    printf("  - test1_copy.txt\n");
    printf("  - buffer.txt\n");
    printf("  - demo.txt\n");
    printf("\n可以手动查看和删除这些文件\n");
    
    return 0;
}

/*
 * 知识点总结：
 * 
 * 文件概念：
 * 
 * 文件是存储在外部存储设备上的数据集合
 * - 程序运行时数据在内存中
 * - 程序结束后数据消失
 * - 文件可以永久保存数据
 * 
 * 文件分类：
 * 
 * 1. 文本文件：
 *    - 以ASCII/UTF-8编码存储
 *    - 可用文本编辑器打开
 *    - 人类可读
 *    - 例如：.txt, .c, .h
 * 
 * 2. 二进制文件：
 *    - 以二进制形式存储
 *    - 需要特定程序打开
 *    - 存储效率高
 *    - 例如：.exe, .jpg, .mp3
 * 
 * 文件指针：
 * 
 * FILE *fp;
 * 
 * - FILE是结构体类型（定义在stdio.h）
 * - 文件指针指向文件信息
 * - 包含文件位置、缓冲区等信息
 * 
 * 文件操作基本步骤：
 * 
 * 1. 打开文件：
 *    FILE *fp = fopen(filename, mode);
 * 
 * 2. 检查是否成功：
 *    if (fp == NULL) { 处理错误 }
 * 
 * 3. 读写操作：
 *    fprintf, fscanf, fgets, fputs等
 * 
 * 4. 关闭文件：
 *    fclose(fp);
 * 
 * fopen() 函数：
 * 
 * 语法：
 * FILE *fopen(const char *filename, const char *mode);
 * 
 * 参数：
 * - filename: 文件名（可含路径）
 * - mode: 打开模式
 * 
 * 返回值：
 * - 成功：返回文件指针
 * - 失败：返回NULL
 * 
 * 文件打开模式：
 * 
 * 文本文件模式：
 * "r"  - 只读，文件必须存在
 * "w"  - 只写，文件不存在则创建，存在则清空
 * "a"  - 追加，文件不存在则创建，写入在末尾
 * "r+" - 读写，文件必须存在
 * "w+" - 读写，文件不存在则创建，存在则清空
 * "a+" - 读写，文件不存在则创建，读从头，写在尾
 * 
 * 二进制文件模式（后面学习）：
 * "rb", "wb", "ab", "rb+", "wb+", "ab+"
 * 
 * 模式详解：
 * 
 * "r" (read):
 * - 文件必须存在
 * - 只能读取
 * - 文件指针在开头
 * 
 * "w" (write):
 * - 文件不存在则创建
 * - 文件存在则清空内容
 * - 只能写入
 * - 文件指针在开头
 * 
 * "a" (append):
 * - 文件不存在则创建
 * - 文件存在保留内容
 * - 只能写入
 * - 文件指针在末尾
 * 
 * "r+" (read+):
 * - 文件必须存在
 * - 可读可写
 * - 不清空内容
 * - 文件指针在开头
 * 
 * "w+" (write+):
 * - 文件不存在则创建
 * - 文件存在则清空
 * - 可读可写
 * - 文件指针在开头
 * 
 * "a+" (append+):
 * - 文件不存在则创建
 * - 文件存在保留内容
 * - 可读可写
 * - 读从任意位置，写在末尾
 * 
 * fclose() 函数：
 * 
 * 语法：
 * int fclose(FILE *fp);
 * 
 * 作用：
 * - 关闭文件
 * - 刷新缓冲区
 * - 释放资源
 * 
 * 返回值：
 * - 成功：0
 * - 失败：EOF
 * 
 * 重要性：
 * - 必须关闭打开的文件
 * - 不关闭可能丢失数据
 * - 不关闭会占用系统资源
 * 
 * 基本文件读写函数：
 * 
 * 1. 字符级：
 *    int fgetc(FILE *fp);     // 读一个字符
 *    int fputc(int ch, FILE *fp);  // 写一个字符
 * 
 * 2. 行级：
 *    char *fgets(char *str, int n, FILE *fp);  // 读一行
 *    int fputs(const char *str, FILE *fp);     // 写一行
 * 
 * 3. 格式化：
 *    int fprintf(FILE *fp, format, ...);  // 格式化写入
 *    int fscanf(FILE *fp, format, ...);   // 格式化读取
 * 
 * fgets() 详解：
 * 
 * char *fgets(char *str, int n, FILE *fp);
 * 
 * - 读取一行（包含换行符）
 * - 最多读n-1个字符
 * - 自动添加'\0'
 * - 遇到EOF或换行符停止
 * - 成功返回str，失败返回NULL
 * 
 * fputs() 详解：
 * 
 * int fputs(const char *str, FILE *fp);
 * 
 * - 写入字符串
 * - 不自动添加换行符
 * - 成功返回非负数，失败返回EOF
 * 
 * fprintf() 和 fscanf()：
 * 
 * 类似printf()和scanf()
 * 但是操作文件而不是控制台
 * 
 * fprintf(fp, "姓名: %s, 年龄: %d\n", name, age);
 * fscanf(fp, "姓名: %s, 年龄: %d", name, &age);
 * 
 * 错误处理：
 * 
 * 1. 检查fopen()返回值：
 *    if (fp == NULL) { 处理错误 }
 * 
 * 2. 检查读取是否成功：
 *    if (fgets(...) == NULL) { 到达文件末尾或错误 }
 * 
 * 3. 使用feof()和ferror()：
 *    feof(fp)   - 是否到达文件末尾
 *    ferror(fp) - 是否发生错误
 * 
 * 文件路径：
 * 
 * 1. 相对路径：
 *    "file.txt"           - 当前目录
 *    "data/file.txt"      - 子目录
 *    "../file.txt"        - 上级目录
 * 
 * 2. 绝对路径：
 *    Windows: "C:\\data\\file.txt"
 *    Linux:   "/home/user/file.txt"
 * 
 * 注意：Windows路径使用\\（转义）
 * 
 * 标准流：
 * 
 * stdin  - 标准输入（键盘）
 * stdout - 标准输出（屏幕）
 * stderr - 标准错误（屏幕）
 * 
 * 这些是预定义的FILE指针
 * 不需要打开和关闭
 * 
 * 缓冲区：
 * 
 * - 文件操作使用缓冲区
 * - 提高效率
 * - fflush(fp) - 强制刷新缓冲区
 * - fclose()自动刷新
 * 
 * 最佳实践：
 * 
 * 1. 总是检查fopen()返回值
 * 2. 使用完毕立即关闭文件
 * 3. 使用const修饰模式字符串
 * 4. 路径使用宏或配置文件
 * 5. 处理异常情况
 * 
 * 常见错误：
 * 
 * 1. 忘记关闭文件：
 *    FILE *fp = fopen(...);
 *    // 使用文件
 *    // 忘记fclose(fp);
 * 
 * 2. 不检查返回值：
 *    FILE *fp = fopen(...);
 *    fprintf(fp, ...);  // 如果fp是NULL会崩溃
 * 
 * 3. 路径错误：
 *    Windows: "C:\data\file.txt"  // 错误，\d等是转义字符
 *    正确: "C:\\data\\file.txt"
 * 
 * 4. 模式错误：
 *    fopen("file.txt", "r");  // 文件不存在会失败
 * 
 * 5. 重复打开：
 *    打开文件后没关闭又打开
 * 
 * 调试技巧：
 * 
 * 1. 检查文件是否创建：
 *    在文件系统中查看
 * 
 * 2. 打印错误信息：
 *    if (fp == NULL) {
 *        perror("文件打开失败");
 *    }
 * 
 * 3. 使用调试器：
 *    查看文件指针是否为NULL
 * 
 * 4. 逐步测试：
 *    先测试打开，再测试读写
 */
