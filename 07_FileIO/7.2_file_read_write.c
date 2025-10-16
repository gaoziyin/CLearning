/*
 * 第七章：文件操作
 * 7.2 文件读写详解
 * 
 * 学习目标：
 * 1. 掌握各种文件读写方法
 * 2. 学习格式化输入输出
 * 3. 理解文件读写的细节
 * 4. 掌握文件数据的处理技巧
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 学生结构体
typedef struct {
    int id;
    char name[50];
    float score;
} Student;

// 函数声明
void writeStudents(const char *filename);
void readStudents(const char *filename);
void copyFile(const char *source, const char *dest);

int main() {
    printf("=== 文件读写详解 ===\n\n");
    
    // 1. 字符读写 - fgetc/fputc
    printf("1. 字符级读写:\n");
    FILE *fp1 = fopen("char_test.txt", "w");
    if (fp1 != NULL) {
        char text[] = "Hello";
        for (int i = 0; text[i] != '\0'; i++) {
            fputc(text[i], fp1);  // 逐字符写入
        }
        fputc('\n', fp1);
        fclose(fp1);
        printf("字符写入完成\n");
    }
    
    // 读取字符
    FILE *fp2 = fopen("char_test.txt", "r");
    if (fp2 != NULL) {
        printf("读取内容: ");
        int ch;
        while ((ch = fgetc(fp2)) != EOF) {  // 逐字符读取
            putchar(ch);
        }
        fclose(fp2);
    }
    printf("\n");
    
    // 2. 字符串读写 - fgets/fputs
    printf("2. 字符串读写:\n");
    FILE *fp3 = fopen("string_test.txt", "w");
    if (fp3 != NULL) {
        fputs("第一行文本\n", fp3);
        fputs("第二行文本\n", fp3);
        fputs("第三行文本\n", fp3);
        fclose(fp3);
        printf("字符串写入完成\n");
    }
    
    FILE *fp4 = fopen("string_test.txt", "r");
    if (fp4 != NULL) {
        char line[100];
        int lineNum = 1;
        printf("读取内容:\n");
        while (fgets(line, sizeof(line), fp4) != NULL) {
            printf("  行%d: %s", lineNum++, line);
        }
        fclose(fp4);
    }
    printf("\n");
    
    // 3. 格式化读写 - fprintf/fscanf
    printf("3. 格式化读写:\n");
    FILE *fp5 = fopen("formatted.txt", "w");
    if (fp5 != NULL) {
        fprintf(fp5, "%s %d %.2f\n", "张三", 20, 85.5);
        fprintf(fp5, "%s %d %.2f\n", "李四", 22, 90.0);
        fprintf(fp5, "%s %d %.2f\n", "王五", 21, 88.5);
        fclose(fp5);
        printf("格式化数据写入完成\n");
    }
    
    FILE *fp6 = fopen("formatted.txt", "r");
    if (fp6 != NULL) {
        char name[50];
        int age;
        float score;
        
        printf("读取格式化数据:\n");
        while (fscanf(fp6, "%s %d %f", name, &age, &score) == 3) {
            printf("  姓名: %s, 年龄: %d, 成绩: %.1f\n", name, age, score);
        }
        fclose(fp6);
    }
    printf("\n");
    
    // 4. 写入多条记录
    printf("4. 写入学生记录:\n");
    writeStudents("students.txt");
    printf("学生记录写入完成\n\n");
    
    // 5. 读取多条记录
    printf("5. 读取学生记录:\n");
    readStudents("students.txt");
    printf("\n");
    
    // 6. 追加数据
    printf("6. 追加新学生:\n");
    FILE *fp7 = fopen("students.txt", "a");
    if (fp7 != NULL) {
        Student newStudent = {1004, "赵六", 92.0};
        fprintf(fp7, "%d %s %.1f\n", 
                newStudent.id, newStudent.name, newStudent.score);
        fclose(fp7);
        printf("新学生已追加\n\n");
    }
    
    // 验证追加
    printf("7. 验证追加后的数据:\n");
    readStudents("students.txt");
    printf("\n");
    
    // 8. 逐行处理
    printf("8. 逐行处理文件:\n");
    FILE *fp8 = fopen("students.txt", "r");
    if (fp8 != NULL) {
        char line[100];
        int lineCount = 0;
        int totalScore = 0;
        
        while (fgets(line, sizeof(line), fp8) != NULL) {
            lineCount++;
            Student s;
            if (sscanf(line, "%d %s %f", &s.id, s.name, &s.score) == 3) {
                totalScore += s.score;
            }
        }
        
        printf("总行数: %d\n", lineCount);
        printf("平均分: %.1f\n", (float)totalScore / lineCount);
        fclose(fp8);
    }
    printf("\n");
    
    // 9. 读写混合操作
    printf("9. 读写混合 (r+ 模式):\n");
    FILE *fp9 = fopen("mixed.txt", "w+");  // w+: 可读可写
    if (fp9 != NULL) {
        // 先写入
        fprintf(fp9, "Line 1\n");
        fprintf(fp9, "Line 2\n");
        fprintf(fp9, "Line 3\n");
        
        // 移动到开头
        rewind(fp9);
        
        // 读取
        char line[100];
        printf("写入后立即读取:\n");
        while (fgets(line, sizeof(line), fp9) != NULL) {
            printf("  %s", line);
        }
        
        fclose(fp9);
    }
    printf("\n");
    
    // 10. 条件读取
    printf("10. 条件读取（成绩>85）:\n");
    FILE *fp10 = fopen("students.txt", "r");
    if (fp10 != NULL) {
        Student s;
        printf("优秀学生:\n");
        while (fscanf(fp10, "%d %s %f", &s.id, s.name, &s.score) == 3) {
            if (s.score > 85) {
                printf("  %d %s %.1f\n", s.id, s.name, s.score);
            }
        }
        fclose(fp10);
    }
    printf("\n");
    
    // 11. 文件复制
    printf("11. 文件复制:\n");
    copyFile("students.txt", "students_backup.txt");
    printf("文件复制完成: students.txt -> students_backup.txt\n\n");
    
    // 12. 统计文件信息
    printf("12. 文件统计信息:\n");
    FILE *fp11 = fopen("students.txt", "r");
    if (fp11 != NULL) {
        int charCount = 0;
        int wordCount = 0;
        int lineCount = 0;
        int ch;
        int inWord = 0;
        
        while ((ch = fgetc(fp11)) != EOF) {
            charCount++;
            
            if (ch == '\n') {
                lineCount++;
            }
            
            if (ch == ' ' || ch == '\n' || ch == '\t') {
                inWord = 0;
            } else if (!inWord) {
                inWord = 1;
                wordCount++;
            }
        }
        
        printf("字符数: %d\n", charCount);
        printf("单词数: %d\n", wordCount);
        printf("行数: %d\n", lineCount);
        fclose(fp11);
    }
    printf("\n");
    
    // 13. 查找特定内容
    printf("13. 查找特定学生 (ID=1002):\n");
    FILE *fp12 = fopen("students.txt", "r");
    if (fp12 != NULL) {
        Student s;
        int found = 0;
        
        while (fscanf(fp12, "%d %s %f", &s.id, s.name, &s.score) == 3) {
            if (s.id == 1002) {
                printf("找到学生: %d %s %.1f\n", s.id, s.name, s.score);
                found = 1;
                break;
            }
        }
        
        if (!found) {
            printf("未找到该学生\n");
        }
        
        fclose(fp12);
    }
    printf("\n");
    
    // 14. 更新文件内容（读取->修改->重写）
    printf("14. 更新学生成绩:\n");
    FILE *fp13 = fopen("students.txt", "r");
    FILE *fp14 = fopen("students_temp.txt", "w");
    
    if (fp13 != NULL && fp14 != NULL) {
        Student s;
        while (fscanf(fp13, "%d %s %f", &s.id, s.name, &s.score) == 3) {
            if (s.id == 1001) {
                s.score = 95.0;  // 更新成绩
                printf("更新学生 %d 的成绩为 %.1f\n", s.id, s.score);
            }
            fprintf(fp14, "%d %s %.1f\n", s.id, s.name, s.score);
        }
        
        fclose(fp13);
        fclose(fp14);
        
        // 删除原文件，重命名临时文件
        remove("students.txt");
        rename("students_temp.txt", "students.txt");
        printf("文件更新完成\n");
    }
    printf("\n");
    
    // 15. 验证更新
    printf("15. 验证更新后的数据:\n");
    readStudents("students.txt");
    printf("\n");
    
    // 16. 写入CSV格式
    printf("16. 写入CSV格式:\n");
    FILE *fp15 = fopen("students.csv", "w");
    if (fp15 != NULL) {
        fprintf(fp15, "ID,Name,Score\n");  // 表头
        fprintf(fp15, "1001,张三,95.0\n");
        fprintf(fp15, "1002,李四,87.5\n");
        fprintf(fp15, "1003,王五,90.0\n");
        fclose(fp15);
        printf("CSV文件创建完成\n");
    }
    
    // 读取CSV
    FILE *fp16 = fopen("students.csv", "r");
    if (fp16 != NULL) {
        char line[100];
        printf("CSV内容:\n");
        while (fgets(line, sizeof(line), fp16) != NULL) {
            printf("  %s", line);
        }
        fclose(fp16);
    }
    printf("\n");
    
    // 17. 错误处理示例
    printf("17. 文件读取错误处理:\n");
    FILE *fp17 = fopen("nonexistent.txt", "r");
    if (fp17 == NULL) {
        perror("错误");  // 打印系统错误信息
        printf("文件打开失败，继续执行其他操作\n");
    } else {
        fclose(fp17);
    }
    printf("\n");
    
    // 18. 检测文件结束
    printf("18. 文件结束检测:\n");
    FILE *fp18 = fopen("students.txt", "r");
    if (fp18 != NULL) {
        char ch;
        int count = 0;
        
        while (!feof(fp18)) {
            ch = fgetc(fp18);
            if (ch != EOF) {
                count++;
            }
        }
        
        printf("读取了 %d 个字符\n", count);
        printf("已到达文件末尾: %s\n", feof(fp18) ? "是" : "否");
        fclose(fp18);
    }
    printf("\n");
    
    // 19. 批量写入
    printf("19. 批量写入数据:\n");
    FILE *fp19 = fopen("numbers.txt", "w");
    if (fp19 != NULL) {
        for (int i = 1; i <= 10; i++) {
            fprintf(fp19, "%d ", i * i);
            if (i % 5 == 0) {
                fprintf(fp19, "\n");
            }
        }
        fclose(fp19);
        printf("批量数据写入完成\n");
    }
    
    // 读取并显示
    FILE *fp20 = fopen("numbers.txt", "r");
    if (fp20 != NULL) {
        int num;
        printf("数据内容: ");
        while (fscanf(fp20, "%d", &num) == 1) {
            printf("%d ", num);
        }
        printf("\n");
        fclose(fp20);
    }
    printf("\n");
    
    // 20. 创建的文件列表
    printf("20. 本程序创建的文件:\n");
    printf("  - char_test.txt\n");
    printf("  - string_test.txt\n");
    printf("  - formatted.txt\n");
    printf("  - students.txt\n");
    printf("  - students_backup.txt\n");
    printf("  - students.csv\n");
    printf("  - mixed.txt\n");
    printf("  - numbers.txt\n");
    
    return 0;
}

// 写入学生数据
void writeStudents(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("无法创建文件\n");
        return;
    }
    
    Student students[] = {
        {1001, "张三", 85.5},
        {1002, "李四", 87.5},
        {1003, "王五", 90.0}
    };
    
    int count = sizeof(students) / sizeof(students[0]);
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d %s %.1f\n", 
                students[i].id, 
                students[i].name, 
                students[i].score);
    }
    
    fclose(fp);
}

// 读取学生数据
void readStudents(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("无法打开文件\n");
        return;
    }
    
    Student s;
    printf("学生列表:\n");
    printf("  ID   姓名   成绩\n");
    printf("  --------------------\n");
    
    while (fscanf(fp, "%d %s %f", &s.id, s.name, &s.score) == 3) {
        printf("  %-4d %-6s %.1f\n", s.id, s.name, s.score);
    }
    
    fclose(fp);
}

// 文件复制
void copyFile(const char *source, const char *dest) {
    FILE *src = fopen(source, "r");
    FILE *dst = fopen(dest, "w");
    
    if (src == NULL || dst == NULL) {
        printf("文件操作失败\n");
        if (src) fclose(src);
        if (dst) fclose(dst);
        return;
    }
    
    int ch;
    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, dst);
    }
    
    fclose(src);
    fclose(dst);
}

/*
 * 知识点总结：
 * 
 * 字符读写函数：
 * 
 * fgetc():
 * int fgetc(FILE *fp);
 * - 从文件读取一个字符
 * - 返回读取的字符（int类型）
 * - 到达末尾返回EOF
 * - EOF是一个宏，值为-1
 * 
 * fputc():
 * int fputc(int ch, FILE *fp);
 * - 向文件写入一个字符
 * - 成功返回写入的字符
 * - 失败返回EOF
 * 
 * 用法：
 * while ((ch = fgetc(fp)) != EOF) {
 *     // 处理字符
 * }
 * 
 * 字符串读写函数：
 * 
 * fgets():
 * char *fgets(char *str, int n, FILE *fp);
 * - 读取一行（最多n-1个字符）
 * - 包含换行符'\n'
 * - 自动添加'\0'
 * - 成功返回str，失败或EOF返回NULL
 * 
 * 示例：
 * char line[100];
 * while (fgets(line, sizeof(line), fp) != NULL) {
 *     printf("%s", line);
 * }
 * 
 * fputs():
 * int fputs(const char *str, FILE *fp);
 * - 写入字符串
 * - 不自动添加换行符
 * - 需要手动添加'\n'
 * - 成功返回非负数，失败返回EOF
 * 
 * 格式化读写函数：
 * 
 * fprintf():
 * int fprintf(FILE *fp, const char *format, ...);
 * - 类似printf()，但输出到文件
 * - 返回写入的字符数
 * - 失败返回负数
 * 
 * 示例：
 * fprintf(fp, "姓名: %s, 年龄: %d\n", name, age);
 * 
 * fscanf():
 * int fscanf(FILE *fp, const char *format, ...);
 * - 类似scanf()，但从文件读取
 * - 返回成功读取的项数
 * - 到达EOF返回EOF
 * 
 * 示例：
 * while (fscanf(fp, "%d %s %f", &id, name, &score) == 3) {
 *     // 处理数据
 * }
 * 
 * 读写模式对比：
 * 
 * 字符级 (fgetc/fputc):
 * - 逐字符处理
 * - 最灵活但最慢
 * - 适合字符统计、加密等
 * 
 * 行级 (fgets/fputs):
 * - 逐行处理
 * - 效率较高
 * - 适合文本文件处理
 * 
 * 格式化 (fprintf/fscanf):
 * - 格式化数据
 * - 类型安全
 * - 适合结构化数据
 * 
 * EOF (End Of File):
 * 
 * - 文件结束标记
 * - 值为-1
 * - 定义在stdio.h
 * 
 * 检测EOF:
 * if (ch == EOF) { ... }
 * if (fgets(...) == NULL) { ... }
 * if (fscanf(...) == EOF) { ... }
 * 
 * feof()函数:
 * int feof(FILE *fp);
 * - 检测是否到达文件末尾
 * - 到达返回非0，否则返回0
 * 
 * 注意：
 * feof()在读取操作后才会设置
 * 所以循环中先读取再检查
 * 
 * 正确方式：
 * while ((ch = fgetc(fp)) != EOF) { ... }
 * 
 * 错误方式：
 * while (!feof(fp)) {
 *     ch = fgetc(fp);  // 可能多读一次
 * }
 * 
 * ferror()函数:
 * int ferror(FILE *fp);
 * - 检测文件操作是否出错
 * - 出错返回非0，否则返回0
 * 
 * 使用：
 * if (ferror(fp)) {
 *     printf("文件读写出错\n");
 * }
 * 
 * clearerr()函数:
 * void clearerr(FILE *fp);
 * - 清除错误标志和EOF标志
 * - 用于错误恢复
 * 
 * 文件追加：
 * 
 * "a" 模式：
 * FILE *fp = fopen("file.txt", "a");
 * - 在文件末尾追加
 * - 不删除原有内容
 * - 文件不存在则创建
 * 
 * 应用场景：
 * - 日志文件
 * - 累积数据
 * - 持续记录
 * 
 * 文件更新：
 * 
 * 方法1：读取->修改->重写全部
 * 1. 读取所有数据到内存
 * 2. 修改数据
 * 3. 重新写入整个文件
 * 
 * 方法2：使用临时文件
 * 1. 创建临时文件
 * 2. 边读边写，修改需要的部分
 * 3. 删除原文件
 * 4. 重命名临时文件
 * 
 * rewind()函数:
 * void rewind(FILE *fp);
 * - 将文件指针移到开头
 * - 等价于fseek(fp, 0, SEEK_SET)
 * - 清除错误标志
 * 
 * 用途：
 * - 重新读取文件
 * - 读写混合操作
 * 
 * remove()函数:
 * int remove(const char *filename);
 * - 删除文件
 * - 成功返回0，失败返回非0
 * 
 * 注意：
 * - 文件必须关闭后才能删除
 * - 删除后无法恢复
 * 
 * rename()函数:
 * int rename(const char *old, const char *new);
 * - 重命名文件
 * - 可用于移动文件
 * - 成功返回0，失败返回非0
 * 
 * 示例：
 * rename("old.txt", "new.txt");
 * rename("temp.txt", "data.txt");
 * 
 * perror()函数:
 * void perror(const char *str);
 * - 打印系统错误信息
 * - str是自定义前缀
 * 
 * 示例：
 * if (fp == NULL) {
 *     perror("文件打开失败");
 *     // 输出: 文件打开失败: No such file or directory
 * }
 * 
 * 文件格式：
 * 
 * 纯文本：
 * - 简单易读
 * - 占用空间大
 * - 跨平台性好
 * 
 * CSV格式：
 * - 逗号分隔值
 * - 易于导入Excel
 * - 适合表格数据
 * 
 * 格式：
 * ID,Name,Score
 * 1001,张三,85.5
 * 1002,李四,90.0
 * 
 * 批量操作：
 * 
 * 写入多条数据：
 * for (int i = 0; i < count; i++) {
 *     fprintf(fp, format, data[i]...);
 * }
 * 
 * 读取多条数据：
 * while (fscanf(fp, format, &data) != EOF) {
 *     // 处理数据
 * }
 * 
 * 最佳实践：
 * 
 * 1. 总是检查返回值
 * 2. 使用while循环读取直到EOF
 * 3. fscanf检查返回的项数
 * 4. 及时关闭文件
 * 5. 使用函数封装文件操作
 * 
 * 常见错误：
 * 
 * 1. 忘记检查NULL：
 *    FILE *fp = fopen(...);
 *    fprintf(fp, ...);  // fp可能是NULL
 * 
 * 2. 无限循环：
 *    while (!feof(fp)) {
 *        fgetc(fp);  // 最后一次会读取两次
 *    }
 * 
 * 3. 格式不匹配：
 *    fprintf(fp, "%d", floatValue);  // 类型错误
 * 
 * 4. 缓冲区溢出：
 *    char buf[10];
 *    fgets(buf, 100, fp);  // 缓冲区只有10
 * 
 * 5. 文件未关闭：
 *    数据可能没有写入磁盘
 * 
 * 性能优化：
 * 
 * 1. 减少fopen/fclose调用
 * 2. 使用大缓冲区
 * 3. 批量读写
 * 4. 避免频繁seek操作
 * 5. 考虑使用二进制模式
 */
