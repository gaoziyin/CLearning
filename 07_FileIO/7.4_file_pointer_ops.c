/*
 * 第七章：文件操作
 * 7.4 文件指针操作
 * 
 * 学习目标：
 * 1. 掌握文件指针定位函数
 * 2. 学习文件位置的获取和设置
 * 3. 理解文件的随机访问
 * 4. 掌握文件操作的高级技巧
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 记录结构体
typedef struct {
    int id;
    char name[30];
    float salary;
} Employee;

// 函数声明
void createEmployeeFile(void);
void displayEmployeeAtPosition(int position);
void updateEmployeeSalary(int position, float newSalary);

int main() {
    printf("=== 文件指针操作 ===\n\n");
    
    // 1. fseek() - 文件定位
    printf("1. fseek() - 文件指针定位:\n");
    FILE *fp1 = fopen("test.txt", "w+");
    if (fp1 != NULL) {
        fprintf(fp1, "0123456789");
        
        // SEEK_SET - 从文件开头
        fseek(fp1, 5, SEEK_SET);
        printf("fseek(fp, 5, SEEK_SET) - 从开头移动5字节\n");
        printf("当前位置: %ld\n", ftell(fp1));
        
        // SEEK_CUR - 从当前位置
        fseek(fp1, 2, SEEK_CUR);
        printf("fseek(fp, 2, SEEK_CUR) - 从当前位置移动2字节\n");
        printf("当前位置: %ld\n", ftell(fp1));
        
        // SEEK_END - 从文件末尾
        fseek(fp1, -3, SEEK_END);
        printf("fseek(fp, -3, SEEK_END) - 从末尾向前3字节\n");
        printf("当前位置: %ld\n", ftell(fp1));
        
        fclose(fp1);
    }
    printf("\n");
    
    // 2. ftell() - 获取当前位置
    printf("2. ftell() - 获取文件指针位置:\n");
    FILE *fp2 = fopen("test.txt", "r");
    if (fp2 != NULL) {
        printf("初始位置: %ld\n", ftell(fp2));
        
        fgetc(fp2);
        printf("读取1字符后: %ld\n", ftell(fp2));
        
        fseek(fp2, 5, SEEK_SET);
        printf("移动到位置5: %ld\n", ftell(fp2));
        
        fclose(fp2);
    }
    printf("\n");
    
    // 3. rewind() - 回到文件开头
    printf("3. rewind() - 回到文件开头:\n");
    FILE *fp3 = fopen("test.txt", "r");
    if (fp3 != NULL) {
        // 读取一些数据
        char ch;
        for (int i = 0; i < 5; i++) {
            ch = fgetc(fp3);
        }
        printf("读取5个字符后位置: %ld\n", ftell(fp3));
        
        // 回到开头
        rewind(fp3);
        printf("rewind()后位置: %ld\n", ftell(fp3));
        
        // 再次读取
        ch = fgetc(fp3);
        printf("读取的字符: %c\n", ch);
        
        fclose(fp3);
    }
    printf("\n");
    
    // 4. 获取文件大小
    printf("4. 获取文件大小:\n");
    FILE *fp4 = fopen("test.txt", "r");
    if (fp4 != NULL) {
        // 移到末尾
        fseek(fp4, 0, SEEK_END);
        
        // 获取位置（即文件大小）
        long fileSize = ftell(fp4);
        printf("文件大小: %ld 字节\n", fileSize);
        
        fclose(fp4);
    }
    printf("\n");
    
    // 5. 创建员工记录文件
    printf("5. 创建员工记录文件:\n");
    createEmployeeFile();
    printf("员工记录已创建\n\n");
    
    // 6. 随机访问 - 读取特定记录
    printf("6. 随机访问 - 读取第2条记录:\n");
    displayEmployeeAtPosition(1);  // 索引从0开始
    printf("\n");
    
    // 7. 读取所有记录
    printf("7. 读取所有员工记录:\n");
    FILE *fp5 = fopen("employees.bin", "rb");
    if (fp5 != NULL) {
        Employee emp;
        int index = 0;
        
        printf("ID   姓名           工资\n");
        printf("--------------------------------\n");
        
        while (fread(&emp, sizeof(Employee), 1, fp5) == 1) {
            printf("%-4d %-14s ¥%.2f\n", 
                   emp.id, emp.name, emp.salary);
            index++;
        }
        
        fclose(fp5);
    }
    printf("\n");
    
    // 8. 更新特定记录
    printf("8. 更新第1条记录的工资:\n");
    updateEmployeeSalary(0, 9000.0);
    printf("工资已更新\n\n");
    
    // 9. 验证更新
    printf("9. 验证更新后的记录:\n");
    displayEmployeeAtPosition(0);
    printf("\n");
    
    // 10. 在文件中间插入数据（覆盖方式）
    printf("10. 在文件中间修改数据:\n");
    FILE *fp6 = fopen("test.txt", "r+");
    if (fp6 != NULL) {
        // 移到位置3
        fseek(fp6, 3, SEEK_SET);
        
        // 写入新数据（会覆盖）
        fprintf(fp6, "XYZ");
        
        fclose(fp6);
        printf("数据已修改\n");
    }
    
    // 读取验证
    FILE *fp7 = fopen("test.txt", "r");
    if (fp7 != NULL) {
        char content[100];
        fgets(content, sizeof(content), fp7);
        printf("修改后内容: %s\n", content);
        fclose(fp7);
    }
    printf("\n");
    
    // 11. 逆序读取文件
    printf("11. 逆序读取文件:\n");
    FILE *fp8 = fopen("test.txt", "r");
    if (fp8 != NULL) {
        // 获取文件大小
        fseek(fp8, 0, SEEK_END);
        long size = ftell(fp8);
        
        printf("逆序内容: ");
        for (long i = size - 1; i >= 0; i--) {
            fseek(fp8, i, SEEK_SET);
            char ch = fgetc(fp8);
            if (ch != '\n') {
                putchar(ch);
            }
        }
        printf("\n");
        
        fclose(fp8);
    }
    printf("\n");
    
    // 12. 查找特定内容的位置
    printf("12. 查找ID为1003的员工位置:\n");
    FILE *fp9 = fopen("employees.bin", "rb");
    if (fp9 != NULL) {
        Employee emp;
        long position;
        int found = 0;
        
        while (fread(&emp, sizeof(Employee), 1, fp9) == 1) {
            if (emp.id == 1003) {
                position = ftell(fp9) - sizeof(Employee);
                printf("找到员工，文件位置: %ld 字节\n", position);
                printf("记录索引: %ld\n", position / sizeof(Employee));
                found = 1;
                break;
            }
        }
        
        if (!found) {
            printf("未找到该员工\n");
        }
        
        fclose(fp9);
    }
    printf("\n");
    
    // 13. 计算文件中的记录数
    printf("13. 计算记录数:\n");
    FILE *fp10 = fopen("employees.bin", "rb");
    if (fp10 != NULL) {
        fseek(fp10, 0, SEEK_END);
        long fileSize = ftell(fp10);
        int recordCount = fileSize / sizeof(Employee);
        
        printf("文件大小: %ld 字节\n", fileSize);
        printf("每条记录: %zu 字节\n", sizeof(Employee));
        printf("总记录数: %d 条\n", recordCount);
        
        fclose(fp10);
    }
    printf("\n");
    
    // 14. 读取文件的中间部分
    printf("14. 读取第2到第4条记录:\n");
    FILE *fp11 = fopen("employees.bin", "rb");
    if (fp11 != NULL) {
        Employee emp;
        
        // 跳到第2条记录（索引1）
        fseek(fp11, 1 * sizeof(Employee), SEEK_SET);
        
        printf("ID   姓名           工资\n");
        printf("--------------------------------\n");
        
        // 读取3条记录
        for (int i = 0; i < 3; i++) {
            if (fread(&emp, sizeof(Employee), 1, fp11) == 1) {
                printf("%-4d %-14s ¥%.2f\n", 
                       emp.id, emp.name, emp.salary);
            }
        }
        
        fclose(fp11);
    }
    printf("\n");
    
    // 15. 在文件末尾添加记录
    printf("15. 追加新员工记录:\n");
    FILE *fp12 = fopen("employees.bin", "ab");
    if (fp12 != NULL) {
        Employee newEmp = {1006, "赵六", 7500.0};
        fwrite(&newEmp, sizeof(Employee), 1, fp12);
        printf("新员工已添加: %d %s\n", newEmp.id, newEmp.name);
        fclose(fp12);
    }
    printf("\n");
    
    // 16. fgetpos() 和 fsetpos()
    printf("16. fgetpos() 和 fsetpos():\n");
    FILE *fp13 = fopen("test.txt", "r");
    if (fp13 != NULL) {
        fpos_t position;
        
        // 读取一些字符
        for (int i = 0; i < 5; i++) {
            fgetc(fp13);
        }
        
        // 保存当前位置
        fgetpos(fp13, &position);
        printf("保存位置: %lld\n", (long long)position);
        
        // 继续读取
        for (int i = 0; i < 3; i++) {
            fgetc(fp13);
        }
        printf("当前位置: %ld\n", ftell(fp13));
        
        // 恢复到保存的位置
        fsetpos(fp13, &position);
        printf("恢复到保存的位置: %ld\n", ftell(fp13));
        
        fclose(fp13);
    }
    printf("\n");
    
    // 17. 删除特定记录（通过重写）
    printf("17. 删除ID为1002的记录:\n");
    FILE *src = fopen("employees.bin", "rb");
    FILE *dst = fopen("employees_temp.bin", "wb");
    
    if (src != NULL && dst != NULL) {
        Employee emp;
        int deleted = 0;
        
        while (fread(&emp, sizeof(Employee), 1, src) == 1) {
            if (emp.id != 1002) {
                fwrite(&emp, sizeof(Employee), 1, dst);
            } else {
                deleted = 1;
                printf("删除记录: %d %s\n", emp.id, emp.name);
            }
        }
        
        fclose(src);
        fclose(dst);
        
        if (deleted) {
            remove("employees.bin");
            rename("employees_temp.bin", "employees.bin");
            printf("文件已更新\n");
        }
    }
    printf("\n");
    
    // 18. 验证删除
    printf("18. 验证删除后的记录:\n");
    FILE *fp14 = fopen("employees.bin", "rb");
    if (fp14 != NULL) {
        Employee emp;
        
        printf("ID   姓名           工资\n");
        printf("--------------------------------\n");
        
        while (fread(&emp, sizeof(Employee), 1, fp14) == 1) {
            printf("%-4d %-14s ¥%.2f\n", 
                   emp.id, emp.name, emp.salary);
        }
        
        fclose(fp14);
    }
    printf("\n");
    
    // 19. 文件指针的相对移动
    printf("19. 文件指针的相对移动:\n");
    FILE *fp15 = fopen("employees.bin", "rb");
    if (fp15 != NULL) {
        Employee emp;
        
        // 读取第1条
        fread(&emp, sizeof(Employee), 1, fp15);
        printf("第1条: %d %s\n", emp.id, emp.name);
        
        // 向后跳过1条
        fseek(fp15, sizeof(Employee), SEEK_CUR);
        
        // 读取第3条
        fread(&emp, sizeof(Employee), 1, fp15);
        printf("第3条: %d %s\n", emp.id, emp.name);
        
        // 向前移动2条
        fseek(fp15, -2 * sizeof(Employee), SEEK_CUR);
        
        // 再次读取第2条
        fread(&emp, sizeof(Employee), 1, fp15);
        printf("回到第2条: %d %s\n", emp.id, emp.name);
        
        fclose(fp15);
    }
    printf("\n");
    
    // 20. 总结
    printf("20. 文件指针操作总结:\n");
    printf("fseek()  - 移动文件指针\n");
    printf("ftell()  - 获取当前位置\n");
    printf("rewind() - 回到文件开头\n");
    printf("fgetpos()/fsetpos() - 保存/恢复位置\n");
    printf("\n这些函数使得随机访问文件成为可能！\n");
    
    return 0;
}

// 创建员工文件
void createEmployeeFile(void) {
    FILE *fp = fopen("employees.bin", "wb");
    if (fp == NULL) {
        printf("无法创建文件\n");
        return;
    }
    
    Employee employees[] = {
        {1001, "张三", 8000.0},
        {1002, "李四", 7500.0},
        {1003, "王五", 9000.0},
        {1004, "赵六", 6500.0},
        {1005, "钱七", 8500.0}
    };
    
    int count = sizeof(employees) / sizeof(employees[0]);
    fwrite(employees, sizeof(Employee), count, fp);
    
    fclose(fp);
}

// 显示指定位置的员工
void displayEmployeeAtPosition(int position) {
    FILE *fp = fopen("employees.bin", "rb");
    if (fp == NULL) {
        printf("无法打开文件\n");
        return;
    }
    
    Employee emp;
    
    // 移动到指定记录
    fseek(fp, position * sizeof(Employee), SEEK_SET);
    
    // 读取记录
    if (fread(&emp, sizeof(Employee), 1, fp) == 1) {
        printf("记录 %d: ID=%d, 姓名=%s, 工资=¥%.2f\n",
               position, emp.id, emp.name, emp.salary);
    } else {
        printf("读取失败\n");
    }
    
    fclose(fp);
}

// 更新员工工资
void updateEmployeeSalary(int position, float newSalary) {
    FILE *fp = fopen("employees.bin", "rb+");
    if (fp == NULL) {
        printf("无法打开文件\n");
        return;
    }
    
    Employee emp;
    
    // 定位到指定记录
    fseek(fp, position * sizeof(Employee), SEEK_SET);
    
    // 读取记录
    if (fread(&emp, sizeof(Employee), 1, fp) == 1) {
        // 修改工资
        emp.salary = newSalary;
        
        // 回到记录起始位置
        fseek(fp, position * sizeof(Employee), SEEK_SET);
        
        // 写回修改后的记录
        fwrite(&emp, sizeof(Employee), 1, fp);
    }
    
    fclose(fp);
}

/*
 * 知识点总结：
 * 
 * 文件指针定位函数：
 * 
 * fseek():
 * int fseek(FILE *fp, long offset, int origin);
 * 
 * 参数：
 * - fp: 文件指针
 * - offset: 偏移量（字节数）
 * - origin: 起始位置
 * 
 * origin的值：
 * SEEK_SET (0) - 文件开头
 * SEEK_CUR (1) - 当前位置
 * SEEK_END (2) - 文件末尾
 * 
 * 返回值：
 * - 成功: 0
 * - 失败: 非0
 * 
 * 示例：
 * fseek(fp, 0, SEEK_SET);      // 移到开头
 * fseek(fp, 100, SEEK_SET);    // 移到第100字节
 * fseek(fp, 10, SEEK_CUR);     // 向后10字节
 * fseek(fp, -10, SEEK_CUR);    // 向前10字节
 * fseek(fp, 0, SEEK_END);      // 移到末尾
 * fseek(fp, -20, SEEK_END);    // 从末尾向前20字节
 * 
 * ftell():
 * long ftell(FILE *fp);
 * 
 * - 返回当前文件指针位置
 * - 以字节为单位
 * - 从文件开头算起
 * - 失败返回-1L
 * 
 * 用途：
 * 1. 获取当前位置
 * 2. 获取文件大小
 * 3. 记录位置以便恢复
 * 
 * 示例：
 * long pos = ftell(fp);
 * printf("当前位置: %ld\n", pos);
 * 
 * rewind():
 * void rewind(FILE *fp);
 * 
 * - 将文件指针移到开头
 * - 清除错误标志
 * - 等价于 fseek(fp, 0, SEEK_SET)
 * 
 * 用途：
 * - 重新读取文件
 * - 从头开始处理
 * 
 * fgetpos() 和 fsetpos():
 * 
 * int fgetpos(FILE *fp, fpos_t *pos);
 * - 获取当前位置到pos
 * - 成功返回0
 * 
 * int fsetpos(FILE *fp, const fpos_t *pos);
 * - 设置位置为pos
 * - 成功返回0
 * 
 * 优点：
 * - 可处理大文件（>2GB）
 * - 更精确
 * - 可移植性好
 * 
 * 示例：
 * fpos_t position;
 * fgetpos(fp, &position);  // 保存位置
 * // ... 做其他操作
 * fsetpos(fp, &position);  // 恢复位置
 * 
 * 获取文件大小：
 * 
 * 方法1：
 * fseek(fp, 0, SEEK_END);
 * long size = ftell(fp);
 * rewind(fp);
 * 
 * 方法2：
 * fseek(fp, 0, SEEK_END);
 * long size = ftell(fp);
 * fseek(fp, 0, SEEK_SET);
 * 
 * 注意：
 * - 只能用于二进制文件
 * - 文本文件可能不准确
 * 
 * 随机访问记录：
 * 
 * 读取第n条记录：
 * fseek(fp, n * sizeof(Record), SEEK_SET);
 * fread(&record, sizeof(Record), 1, fp);
 * 
 * 更新第n条记录：
 * fseek(fp, n * sizeof(Record), SEEK_SET);
 * fread(&record, sizeof(Record), 1, fp);
 * // 修改record
 * fseek(fp, n * sizeof(Record), SEEK_SET);
 * fwrite(&record, sizeof(Record), 1, fp);
 * 
 * 计算记录数：
 * fseek(fp, 0, SEEK_END);
 * long fileSize = ftell(fp);
 * int count = fileSize / sizeof(Record);
 * 
 * 相对移动：
 * 
 * 向后跳过n条记录：
 * fseek(fp, n * sizeof(Record), SEEK_CUR);
 * 
 * 向前移动n条记录：
 * fseek(fp, -n * sizeof(Record), SEEK_CUR);
 * 
 * 移到倒数第n条：
 * fseek(fp, -n * sizeof(Record), SEEK_END);
 * 
 * 文件操作模式：
 * 
 * "r+"  - 读写，文件必须存在
 * "w+"  - 读写，文件不存在创建，存在清空
 * "a+"  - 读写，追加模式
 * "rb+" - 二进制读写，文件必须存在
 * "wb+" - 二进制读写，文件不存在创建
 * "ab+" - 二进制读写追加
 * 
 * 更新记录的步骤：
 * 
 * 1. 以"rb+"模式打开
 * 2. fseek到记录位置
 * 3. fread读取记录
 * 4. 修改记录
 * 5. fseek回到记录位置
 * 6. fwrite写入记录
 * 7. 关闭文件
 * 
 * 删除记录：
 * 
 * 方法1：标记删除
 * - 在记录中添加deleted字段
 * - 设置为1表示删除
 * - 读取时跳过deleted记录
 * 
 * 方法2：物理删除
 * - 创建临时文件
 * - 复制非删除记录
 * - 删除原文件
 * - 重命名临时文件
 * 
 * 插入记录：
 * 
 * 方法1：追加到末尾
 * - 最简单
 * - 使用"ab"模式
 * 
 * 方法2：插入到中间
 * - 读取后半部分到内存
 * - 写入新记录
 * - 写回后半部分
 * - 较复杂
 * 
 * 逆序读取：
 * 
 * fseek(fp, 0, SEEK_END);
 * long size = ftell(fp);
 * for (long i = size - 1; i >= 0; i--) {
 *     fseek(fp, i, SEEK_SET);
 *     char ch = fgetc(fp);
 *     // 处理字符
 * }
 * 
 * 查找记录：
 * 
 * 顺序查找：
 * while (fread(&record, sizeof(Record), 1, fp) == 1) {
 *     if (符合条件) {
 *         long pos = ftell(fp) - sizeof(Record);
 *         // 处理
 *         break;
 *     }
 * }
 * 
 * 二分查找（记录已排序）：
 * - 计算中间记录位置
 * - fseek到该位置
 * - 比较决定继续在哪半部分查找
 * 
 * 文件指针注意事项：
 * 
 * 1. 文本文件：
 *    - fseek可能不准确
 *    - 换行符转换问题
 *    - 建议只用SEEK_SET和0偏移
 * 
 * 2. 二进制文件：
 *    - fseek完全可靠
 *    - 字节精确定位
 * 
 * 3. 读写切换：
 *    - 读写之间要fseek或rewind
 *    - 或者fflush
 * 
 * 4. 末尾追加：
 *    - "a"模式每次写入都在末尾
 *    - 即使fseek也无效
 * 
 * 常见错误：
 * 
 * 1. 不检查返回值：
 *    fseek(fp, 100, SEEK_SET);  // 应检查返回值
 * 
 * 2. 位置计算错误：
 *    fseek(fp, n, SEEK_SET);  // 应该是n * sizeof(Record)
 * 
 * 3. 读写不同步：
 *    fread后直接fwrite  // 应该先fseek
 * 
 * 4. 文本模式定位：
 *    fseek在文本模式下可能不准
 * 
 * 5. 超出文件范围：
 *    fseek(fp, 10000, SEEK_SET);  // 可能超出文件大小
 * 
 * 最佳实践：
 * 
 * 1. 二进制文件用随机访问
 * 2. 总是检查fseek返回值
 * 3. 使用ftell获取位置
 * 4. 更新前先读取
 * 5. 记录大小固定更好
 * 6. 添加文件头记录元信息
 * 7. 考虑使用数据库
 * 
 * 性能考虑：
 * 
 * 1. 减少fseek调用
 * 2. 批量操作
 * 3. 使用缓冲
 * 4. 顺序访问比随机访问快
 * 5. 考虑内存映射文件
 * 
 * 应用场景：
 * 
 * - 数据库文件
 * - 索引文件
 * - 大文件部分读取
 * - 日志文件
 * - 配置文件
 * - 多媒体文件
 */
