/*
 * 第七章：文件操作
 * 7.3 二进制文件操作
 * 
 * 学习目标：
 * 1. 理解二进制文件与文本文件的区别
 * 2. 掌握fread和fwrite函数
 * 3. 学习二进制文件的读写技巧
 * 4. 了解二进制文件的应用场景
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 学生结构体
typedef struct {
    int id;
    char name[50];
    float score;
    int age;
} Student;

// 图像数据结构（简化）
typedef struct {
    int width;
    int height;
    unsigned char data[100];  // 简化的图像数据
} Image;

// 函数声明
void writeBinaryStudents(const char *filename);
void readBinaryStudents(const char *filename);
void compareTextAndBinary(void);

int main() {
    printf("=== 二进制文件操作 ===\n\n");
    
    // 1. 文本文件 vs 二进制文件
    printf("1. 文本文件 vs 二进制文件:\n");
    printf("文本文件:\n");
    printf("  - 以字符形式存储\n");
    printf("  - 人类可读\n");
    printf("  - 占用空间大\n");
    printf("  - 例如：.txt, .c, .csv\n\n");
    
    printf("二进制文件:\n");
    printf("  - 以二进制形式存储\n");
    printf("  - 需要程序解析\n");
    printf("  - 占用空间小\n");
    printf("  - 读写速度快\n");
    printf("  - 例如：.exe, .jpg, .dat\n\n");
    
    // 2. fwrite - 写入二进制数据
    printf("2. 写入二进制数据 (fwrite):\n");
    FILE *fp1 = fopen("data.bin", "wb");  // "wb" - 二进制写模式
    if (fp1 != NULL) {
        int numbers[] = {10, 20, 30, 40, 50};
        int count = sizeof(numbers) / sizeof(numbers[0]);
        
        // fwrite(数据指针, 每项大小, 项数, 文件指针)
        size_t written = fwrite(numbers, sizeof(int), count, fp1);
        
        printf("写入 %zu 个整数\n", written);
        fclose(fp1);
    }
    printf("\n");
    
    // 3. fread - 读取二进制数据
    printf("3. 读取二进制数据 (fread):\n");
    FILE *fp2 = fopen("data.bin", "rb");  // "rb" - 二进制读模式
    if (fp2 != NULL) {
        int numbers[5];
        
        // fread(数据指针, 每项大小, 项数, 文件指针)
        size_t read = fread(numbers, sizeof(int), 5, fp2);
        
        printf("读取 %zu 个整数: ", read);
        for (int i = 0; i < read; i++) {
            printf("%d ", numbers[i]);
        }
        printf("\n");
        fclose(fp2);
    }
    printf("\n");
    
    // 4. 写入结构体
    printf("4. 写入结构体到二进制文件:\n");
    writeBinaryStudents("students.bin");
    printf("学生数据已写入二进制文件\n\n");
    
    // 5. 读取结构体
    printf("5. 从二进制文件读取结构体:\n");
    readBinaryStudents("students.bin");
    printf("\n");
    
    // 6. 单个结构体读写
    printf("6. 单个结构体操作:\n");
    Student s1 = {1004, "赵六", 88.5, 22};
    
    // 写入
    FILE *fp3 = fopen("student.bin", "wb");
    if (fp3 != NULL) {
        fwrite(&s1, sizeof(Student), 1, fp3);
        printf("写入学生: %d %s\n", s1.id, s1.name);
        fclose(fp3);
    }
    
    // 读取
    FILE *fp4 = fopen("student.bin", "rb");
    if (fp4 != NULL) {
        Student s2;
        fread(&s2, sizeof(Student), 1, fp4);
        printf("读取学生: %d %s %.1f %d岁\n", 
               s2.id, s2.name, s2.score, s2.age);
        fclose(fp4);
    }
    printf("\n");
    
    // 7. 追加二进制数据
    printf("7. 追加二进制数据:\n");
    FILE *fp5 = fopen("students.bin", "ab");  // "ab" - 二进制追加
    if (fp5 != NULL) {
        Student newStudent = {1005, "钱七", 91.0, 21};
        fwrite(&newStudent, sizeof(Student), 1, fp5);
        printf("追加学生: %d %s\n", newStudent.id, newStudent.name);
        fclose(fp5);
    }
    printf("\n");
    
    // 8. 验证追加
    printf("8. 验证追加后的数据:\n");
    readBinaryStudents("students.bin");
    printf("\n");
    
    // 9. 计算文件中的记录数
    printf("9. 计算记录数:\n");
    FILE *fp6 = fopen("students.bin", "rb");
    if (fp6 != NULL) {
        // 移动到文件末尾
        fseek(fp6, 0, SEEK_END);
        // 获取文件大小
        long fileSize = ftell(fp6);
        // 计算记录数
        int recordCount = fileSize / sizeof(Student);
        
        printf("文件大小: %ld 字节\n", fileSize);
        printf("记录大小: %zu 字节\n", sizeof(Student));
        printf("记录数量: %d\n", recordCount);
        
        fclose(fp6);
    }
    printf("\n");
    
    // 10. 随机访问 - 读取特定记录
    printf("10. 随机访问 - 读取第2条记录:\n");
    FILE *fp7 = fopen("students.bin", "rb");
    if (fp7 != NULL) {
        Student s;
        // 跳到第2条记录（索引1）
        fseek(fp7, 1 * sizeof(Student), SEEK_SET);
        fread(&s, sizeof(Student), 1, fp7);
        
        printf("第2条记录: %d %s %.1f\n", s.id, s.name, s.score);
        fclose(fp7);
    }
    printf("\n");
    
    // 11. 更新特定记录
    printf("11. 更新第1条记录的成绩:\n");
    FILE *fp8 = fopen("students.bin", "rb+");  // "rb+" - 二进制读写
    if (fp8 != NULL) {
        Student s;
        
        // 读取第1条记录
        fseek(fp8, 0, SEEK_SET);
        fread(&s, sizeof(Student), 1, fp8);
        printf("原成绩: %.1f\n", s.score);
        
        // 修改成绩
        s.score = 98.0;
        
        // 回到第1条记录位置
        fseek(fp8, 0, SEEK_SET);
        // 写入修改后的数据
        fwrite(&s, sizeof(Student), 1, fp8);
        printf("新成绩: %.1f\n", s.score);
        
        fclose(fp8);
    }
    printf("\n");
    
    // 12. 验证更新
    printf("12. 验证更新:\n");
    readBinaryStudents("students.bin");
    printf("\n");
    
    // 13. 文本文件与二进制文件对比
    printf("13. 存储空间对比:\n");
    compareTextAndBinary();
    printf("\n");
    
    // 14. 写入混合数据
    printf("14. 写入混合数据类型:\n");
    FILE *fp9 = fopen("mixed.bin", "wb");
    if (fp9 != NULL) {
        int id = 100;
        float score = 95.5;
        char name[] = "测试";
        
        fwrite(&id, sizeof(int), 1, fp9);
        fwrite(&score, sizeof(float), 1, fp9);
        fwrite(name, sizeof(char), strlen(name) + 1, fp9);
        
        printf("混合数据已写入\n");
        fclose(fp9);
    }
    
    // 读取混合数据
    FILE *fp10 = fopen("mixed.bin", "rb");
    if (fp10 != NULL) {
        int id;
        float score;
        char name[50];
        
        fread(&id, sizeof(int), 1, fp10);
        fread(&score, sizeof(float), 1, fp10);
        fread(name, sizeof(char), 5, fp10);
        
        printf("读取数据: ID=%d, Score=%.1f, Name=%s\n", 
               id, score, name);
        fclose(fp10);
    }
    printf("\n");
    
    // 15. 二进制文件复制
    printf("15. 二进制文件复制:\n");
    FILE *src = fopen("students.bin", "rb");
    FILE *dst = fopen("students_backup.bin", "wb");
    
    if (src != NULL && dst != NULL) {
        unsigned char buffer[1024];
        size_t bytes;
        
        while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
            fwrite(buffer, 1, bytes, dst);
        }
        
        printf("文件复制完成\n");
    }
    
    if (src) fclose(src);
    if (dst) fclose(dst);
    printf("\n");
    
    // 16. 图像数据示例
    printf("16. 图像数据操作:\n");
    Image img;
    img.width = 10;
    img.height = 10;
    
    // 填充简单的图像数据
    for (int i = 0; i < 100; i++) {
        img.data[i] = i;
    }
    
    // 保存图像
    FILE *fp11 = fopen("image.bin", "wb");
    if (fp11 != NULL) {
        fwrite(&img, sizeof(Image), 1, fp11);
        printf("图像数据已保存: %dx%d\n", img.width, img.height);
        fclose(fp11);
    }
    
    // 加载图像
    FILE *fp12 = fopen("image.bin", "rb");
    if (fp12 != NULL) {
        Image loadedImg;
        fread(&loadedImg, sizeof(Image), 1, fp12);
        printf("图像数据已加载: %dx%d\n", 
               loadedImg.width, loadedImg.height);
        printf("前5个像素: ");
        for (int i = 0; i < 5; i++) {
            printf("%d ", loadedImg.data[i]);
        }
        printf("\n");
        fclose(fp12);
    }
    printf("\n");
    
    // 17. 数组的二进制存储
    printf("17. 大数组的二进制存储:\n");
    FILE *fp13 = fopen("array.bin", "wb");
    if (fp13 != NULL) {
        double data[1000];
        for (int i = 0; i < 1000; i++) {
            data[i] = i * 0.1;
        }
        
        fwrite(data, sizeof(double), 1000, fp13);
        printf("1000个double值已写入\n");
        fclose(fp13);
    }
    
    FILE *fp14 = fopen("array.bin", "rb");
    if (fp14 != NULL) {
        double data[1000];
        size_t count = fread(data, sizeof(double), 1000, fp14);
        printf("读取 %zu 个值\n", count);
        printf("前5个值: %.1f %.1f %.1f %.1f %.1f\n",
               data[0], data[1], data[2], data[3], data[4]);
        fclose(fp14);
    }
    printf("\n");
    
    // 18. 查找特定记录
    printf("18. 查找ID为1003的学生:\n");
    FILE *fp15 = fopen("students.bin", "rb");
    if (fp15 != NULL) {
        Student s;
        int found = 0;
        
        while (fread(&s, sizeof(Student), 1, fp15) == 1) {
            if (s.id == 1003) {
                printf("找到: %d %s %.1f\n", s.id, s.name, s.score);
                found = 1;
                break;
            }
        }
        
        if (!found) {
            printf("未找到该学生\n");
        }
        
        fclose(fp15);
    }
    printf("\n");
    
    // 19. 统计信息
    printf("19. 统计二进制文件信息:\n");
    FILE *fp16 = fopen("students.bin", "rb");
    if (fp16 != NULL) {
        Student s;
        int count = 0;
        float totalScore = 0;
        int totalAge = 0;
        
        while (fread(&s, sizeof(Student), 1, fp16) == 1) {
            count++;
            totalScore += s.score;
            totalAge += s.age;
        }
        
        printf("学生总数: %d\n", count);
        printf("平均成绩: %.1f\n", totalScore / count);
        printf("平均年龄: %.1f\n", (float)totalAge / count);
        
        fclose(fp16);
    }
    printf("\n");
    
    // 20. 创建的文件列表
    printf("20. 本程序创建的二进制文件:\n");
    printf("  - data.bin\n");
    printf("  - students.bin\n");
    printf("  - student.bin\n");
    printf("  - students_backup.bin\n");
    printf("  - mixed.bin\n");
    printf("  - image.bin\n");
    printf("  - array.bin\n");
    
    return 0;
}

// 写入学生数据到二进制文件
void writeBinaryStudents(const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("无法创建文件\n");
        return;
    }
    
    Student students[] = {
        {1001, "张三", 85.5, 20},
        {1002, "李四", 90.0, 21},
        {1003, "王五", 87.5, 22}
    };
    
    int count = sizeof(students) / sizeof(students[0]);
    fwrite(students, sizeof(Student), count, fp);
    
    fclose(fp);
}

// 从二进制文件读取学生数据
void readBinaryStudents(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("无法打开文件\n");
        return;
    }
    
    Student s;
    printf("学生列表:\n");
    printf("  ID   姓名   成绩   年龄\n");
    printf("  ---------------------------\n");
    
    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        printf("  %-4d %-6s %-5.1f %d\n", 
               s.id, s.name, s.score, s.age);
    }
    
    fclose(fp);
}

// 对比文本文件和二进制文件
void compareTextAndBinary(void) {
    Student students[] = {
        {1001, "张三", 85.5, 20},
        {1002, "李四", 90.0, 21},
        {1003, "王五", 87.5, 22}
    };
    int count = sizeof(students) / sizeof(students[0]);
    
    // 写入文本文件
    FILE *fp1 = fopen("compare_text.txt", "w");
    if (fp1 != NULL) {
        for (int i = 0; i < count; i++) {
            fprintf(fp1, "%d %s %.1f %d\n",
                    students[i].id, students[i].name, 
                    students[i].score, students[i].age);
        }
        fclose(fp1);
    }
    
    // 写入二进制文件
    FILE *fp2 = fopen("compare_binary.bin", "wb");
    if (fp2 != NULL) {
        fwrite(students, sizeof(Student), count, fp2);
        fclose(fp2);
    }
    
    // 获取文件大小
    FILE *fp3 = fopen("compare_text.txt", "rb");
    if (fp3 != NULL) {
        fseek(fp3, 0, SEEK_END);
        long textSize = ftell(fp3);
        printf("文本文件大小: %ld 字节\n", textSize);
        fclose(fp3);
    }
    
    FILE *fp4 = fopen("compare_binary.bin", "rb");
    if (fp4 != NULL) {
        fseek(fp4, 0, SEEK_END);
        long binarySize = ftell(fp4);
        printf("二进制文件大小: %ld 字节\n", binarySize);
        fclose(fp4);
    }
    
    printf("结论: 二进制文件通常更小、读写更快\n");
}

/*
 * 知识点总结：
 * 
 * 二进制文件打开模式：
 * 
 * "rb"  - 二进制只读
 * "wb"  - 二进制只写（覆盖）
 * "ab"  - 二进制追加
 * "rb+" - 二进制读写
 * "wb+" - 二进制读写（覆盖）
 * "ab+" - 二进制读写（追加）
 * 
 * 注意：
 * - Windows系统必须使用'b'
 * - Unix/Linux中'b'可选但建议使用
 * 
 * fwrite() 函数：
 * 
 * size_t fwrite(const void *ptr, size_t size, 
 *               size_t nmemb, FILE *fp);
 * 
 * 参数：
 * - ptr: 数据指针
 * - size: 每项的字节数
 * - nmemb: 项数
 * - fp: 文件指针
 * 
 * 返回值：
 * - 成功写入的项数
 * 
 * 示例：
 * int arr[5] = {1,2,3,4,5};
 * fwrite(arr, sizeof(int), 5, fp);
 * 
 * fread() 函数：
 * 
 * size_t fread(void *ptr, size_t size, 
 *              size_t nmemb, FILE *fp);
 * 
 * 参数：
 * - ptr: 存储数据的指针
 * - size: 每项的字节数
 * - nmemb: 要读取的项数
 * - fp: 文件指针
 * 
 * 返回值：
 * - 实际读取的项数
 * 
 * 示例：
 * int arr[5];
 * size_t n = fread(arr, sizeof(int), 5, fp);
 * 
 * 结构体的二进制读写：
 * 
 * 写入：
 * Student s = {1001, "张三", 85.5, 20};
 * fwrite(&s, sizeof(Student), 1, fp);
 * 
 * 读取：
 * Student s;
 * fread(&s, sizeof(Student), 1, fp);
 * 
 * 数组的二进制读写：
 * 
 * 写入：
 * int arr[100] = {...};
 * fwrite(arr, sizeof(int), 100, fp);
 * 
 * 读取：
 * int arr[100];
 * fread(arr, sizeof(int), 100, fp);
 * 
 * 优点：
 * - 一次操作多个数据
 * - 效率高
 * 
 * 二进制文件的优势：
 * 
 * 1. 空间效率：
 *    - 直接存储二进制形式
 *    - 不需要转换为字符
 *    - 占用空间小
 * 
 * 2. 速度快：
 *    - 无需格式化转换
 *    - 直接内存拷贝
 *    - 读写速度快
 * 
 * 3. 精度保持：
 *    - 浮点数不损失精度
 *    - 完全按原值存储
 * 
 * 4. 数据保护：
 *    - 不易被文本编辑器修改
 *    - 一定程度的保密性
 * 
 * 二进制文件的劣势：
 * 
 * 1. 不可读：
 *    - 人类无法直接阅读
 *    - 需要专门程序解析
 * 
 * 2. 平台相关：
 *    - 字节序可能不同
 *    - 结构体填充可能不同
 *    - 跨平台需要注意
 * 
 * 3. 版本兼容：
 *    - 结构体改变后不兼容
 *    - 需要版本管理
 * 
 * 随机访问：
 * 
 * fseek() - 移动文件指针：
 * int fseek(FILE *fp, long offset, int origin);
 * 
 * origin参数：
 * SEEK_SET - 文件开头
 * SEEK_CUR - 当前位置
 * SEEK_END - 文件末尾
 * 
 * 示例：
 * fseek(fp, 0, SEEK_SET);        // 移到开头
 * fseek(fp, 100, SEEK_SET);      // 移到第100字节
 * fseek(fp, 10, SEEK_CUR);       // 向后移10字节
 * fseek(fp, -10, SEEK_CUR);      // 向前移10字节
 * fseek(fp, 0, SEEK_END);        // 移到末尾
 * fseek(fp, -100, SEEK_END);     // 从末尾向前100字节
 * 
 * ftell() - 获取当前位置：
 * long ftell(FILE *fp);
 * - 返回当前文件指针位置
 * - 从文件开头算起的字节数
 * 
 * 用途：
 * - 获取文件大小
 * - 记录位置
 * 
 * 示例：
 * fseek(fp, 0, SEEK_END);
 * long size = ftell(fp);  // 文件大小
 * 
 * rewind() - 回到开头：
 * void rewind(FILE *fp);
 * 等价于 fseek(fp, 0, SEEK_SET);
 * 
 * 记录的随机访问：
 * 
 * 读取第n条记录（从0开始）：
 * fseek(fp, n * sizeof(Record), SEEK_SET);
 * fread(&record, sizeof(Record), 1, fp);
 * 
 * 更新第n条记录：
 * fseek(fp, n * sizeof(Record), SEEK_SET);
 * fwrite(&record, sizeof(Record), 1, fp);
 * 
 * 计算记录数：
 * fseek(fp, 0, SEEK_END);
 * long fileSize = ftell(fp);
 * int count = fileSize / sizeof(Record);
 * 
 * 文件复制（二进制）：
 * 
 * 使用缓冲区：
 * unsigned char buffer[1024];
 * size_t bytes;
 * while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
 *     fwrite(buffer, 1, bytes, dst);
 * }
 * 
 * 优点：
 * - 不关心文件内容
 * - 适用于所有文件类型
 * - 效率高
 * 
 * 混合数据类型：
 * 
 * 写入：
 * int id = 100;
 * float score = 95.5;
 * char name[] = "张三";
 * 
 * fwrite(&id, sizeof(int), 1, fp);
 * fwrite(&score, sizeof(float), 1, fp);
 * fwrite(name, sizeof(char), strlen(name)+1, fp);
 * 
 * 读取时必须知道顺序和类型
 * 
 * 字节序问题：
 * 
 * 大端序（Big-Endian）：
 * - 高位字节存储在低地址
 * - 网络字节序
 * 
 * 小端序（Little-Endian）：
 * - 低位字节存储在低地址
 * - Intel x86架构
 * 
 * 跨平台解决方案：
 * - 统一使用网络字节序
 * - 或者自定义格式
 * 
 * 结构体对齐问题：
 * 
 * 编译器可能对结构体进行填充：
 * struct Data {
 *     char a;    // 1字节
 *     // 可能有3字节填充
 *     int b;     // 4字节
 * };
 * 
 * 解决方案：
 * 1. 使用#pragma pack(1)
 * 2. 手动控制读写每个字段
 * 3. 使用固定大小的类型
 * 
 * 应用场景：
 * 
 * 二进制文件适合：
 * - 大量数据存储
 * - 数值计算结果
 * - 图像、音频数据
 * - 数据库文件
 * - 配置文件（内部使用）
 * 
 * 文本文件适合：
 * - 配置文件（用户可编辑）
 * - 日志文件
 * - CSV数据导出
 * - 跨平台数据交换
 * 
 * 最佳实践：
 * 
 * 1. 使用'b'模式
 * 2. 检查fread/fwrite返回值
 * 3. 注意字节序和对齐
 * 4. 添加文件头（版本信息）
 * 5. 考虑跨平台兼容性
 * 
 * 常见错误：
 * 
 * 1. 忘记'b'模式：
 *    fopen("file", "r");  // 应该是"rb"
 * 
 * 2. sizeof错误：
 *    fwrite(arr, sizeof(arr), 1, fp);  // 错误
 *    fwrite(arr, sizeof(int), n, fp);  // 正确
 * 
 * 3. 不检查返回值：
 *    fread(&s, sizeof(s), 1, fp);  // 应检查返回值
 * 
 * 4. 指针错误：
 *    int *p;
 *    fread(p, sizeof(int), 1, fp);  // p未初始化
 * 
 * 5. 跨平台问题：
 *    忽略字节序和对齐
 * 
 * 性能优化：
 * 
 * 1. 使用大缓冲区
 * 2. 批量读写
 * 3. 减少fseek调用
 * 4. 合理的记录大小
 * 5. 预分配空间
 */
