/*
 * 第七章：文件操作
 * 7.5 文件错误处理与高级应用
 * 
 * 学习目标：
 * 1. 掌握文件错误处理方法
 * 2. 学习文件状态检测
 * 3. 了解文件操作的高级应用
 * 4. 掌握实际项目中的文件处理技巧
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

// 学生结构体
typedef struct {
    int id;
    char name[50];
    float score;
} Student;

// 日志级别
typedef enum {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
} LogLevel;

// 函数声明
void writeLog(const char *message, LogLevel level);
int safeFileOpen(const char *filename, const char *mode, FILE **fp);
void processStudentFile(const char *filename);
void createBackup(const char *filename);

int main() {
    printf("=== 文件错误处理与高级应用 ===\n\n");
    
    // 1. 基本错误检测
    printf("1. 基本文件错误检测:\n");
    FILE *fp1 = fopen("nonexistent.txt", "r");
    if (fp1 == NULL) {
        printf("文件打开失败\n");
        printf("错误代码: %d\n", errno);
        perror("详细错误");  // 打印系统错误信息
    } else {
        fclose(fp1);
    }
    printf("\n");
    
    // 2. ferror() - 检测文件错误
    printf("2. ferror() - 文件错误检测:\n");
    FILE *fp2 = fopen("test_error.txt", "w+");
    if (fp2 != NULL) {
        fprintf(fp2, "测试数据\n");
        
        if (ferror(fp2)) {
            printf("写入时发生错误\n");
        } else {
            printf("写入成功，无错误\n");
        }
        
        fclose(fp2);
    }
    printf("\n");
    
    // 3. feof() - 检测文件结束
    printf("3. feof() - 文件结束检测:\n");
    FILE *fp3 = fopen("test_error.txt", "r");
    if (fp3 != NULL) {
        char ch;
        int charCount = 0;
        
        while ((ch = fgetc(fp3)) != EOF) {
            charCount++;
        }
        
        if (feof(fp3)) {
            printf("已到达文件末尾\n");
            printf("读取了 %d 个字符\n", charCount);
        }
        
        if (ferror(fp3)) {
            printf("读取过程中发生错误\n");
        }
        
        fclose(fp3);
    }
    printf("\n");
    
    // 4. clearerr() - 清除错误标志
    printf("4. clearerr() - 清除错误标志:\n");
    FILE *fp4 = fopen("test_error.txt", "r");
    if (fp4 != NULL) {
        // 读到文件末尾
        while (fgetc(fp4) != EOF);
        
        printf("EOF标志: %s\n", feof(fp4) ? "是" : "否");
        
        clearerr(fp4);  // 清除错误和EOF标志
        printf("clearerr后EOF标志: %s\n", feof(fp4) ? "是" : "否");
        
        fclose(fp4);
    }
    printf("\n");
    
    // 5. 安全的文件打开封装
    printf("5. 安全的文件打开:\n");
    FILE *fp5 = NULL;
    if (safeFileOpen("test.txt", "w", &fp5) == 0) {
        fprintf(fp5, "安全写入的数据\n");
        fclose(fp5);
        printf("文件操作成功\n");
    }
    printf("\n");
    
    // 6. tmpfile() - 临时文件
    printf("6. 临时文件创建:\n");
    FILE *temp = tmpfile();
    if (temp != NULL) {
        fprintf(temp, "这是临时数据\n");
        fprintf(temp, "文件关闭后自动删除\n");
        
        rewind(temp);
        
        char buffer[100];
        printf("临时文件内容:\n");
        while (fgets(buffer, sizeof(buffer), temp) != NULL) {
            printf("  %s", buffer);
        }
        
        fclose(temp);  // 自动删除
        printf("临时文件已关闭并删除\n");
    }
    printf("\n");
    
    // 7. tmpnam() - 生成临时文件名
    printf("7. 生成临时文件名:\n");
    char tempname[L_tmpnam];
    if (tmpnam(tempname) != NULL) {
        printf("临时文件名: %s\n", tempname);
        
        FILE *fp6 = fopen(tempname, "w");
        if (fp6 != NULL) {
            fprintf(fp6, "临时数据\n");
            fclose(fp6);
            printf("临时文件已创建\n");
            
            // 手动删除
            if (remove(tempname) == 0) {
                printf("临时文件已删除\n");
            }
        }
    }
    printf("\n");
    
    // 8. rename() - 文件重命名
    printf("8. 文件重命名:\n");
    FILE *fp7 = fopen("oldname.txt", "w");
    if (fp7 != NULL) {
        fprintf(fp7, "原文件内容\n");
        fclose(fp7);
        
        if (rename("oldname.txt", "newname.txt") == 0) {
            printf("文件重命名成功: oldname.txt -> newname.txt\n");
        } else {
            perror("重命名失败");
        }
    }
    printf("\n");
    
    // 9. remove() - 删除文件
    printf("9. 删除文件:\n");
    FILE *fp8 = fopen("todelete.txt", "w");
    if (fp8 != NULL) {
        fprintf(fp8, "待删除文件\n");
        fclose(fp8);
        
        printf("文件已创建: todelete.txt\n");
        
        if (remove("todelete.txt") == 0) {
            printf("文件已删除\n");
        } else {
            perror("删除失败");
        }
    }
    printf("\n");
    
    // 10. 日志系统
    printf("10. 简单日志系统:\n");
    writeLog("程序启动", LOG_INFO);
    writeLog("发现潜在问题", LOG_WARNING);
    writeLog("发生严重错误", LOG_ERROR);
    printf("日志已写入 app.log\n\n");
    
    // 11. 读取日志
    printf("11. 读取日志文件:\n");
    FILE *fp9 = fopen("app.log", "r");
    if (fp9 != NULL) {
        char line[200];
        while (fgets(line, sizeof(line), fp9) != NULL) {
            printf("  %s", line);
        }
        fclose(fp9);
    }
    printf("\n");
    
    // 12. 文件存在性检查
    printf("12. 检查文件是否存在:\n");
    const char *files[] = {"newname.txt", "notexist.txt", "app.log"};
    
    for (int i = 0; i < 3; i++) {
        FILE *check = fopen(files[i], "r");
        if (check != NULL) {
            printf("  %s - 存在\n", files[i]);
            fclose(check);
        } else {
            printf("  %s - 不存在\n", files[i]);
        }
    }
    printf("\n");
    
    // 13. 文件备份
    printf("13. 创建文件备份:\n");
    createBackup("newname.txt");
    printf("备份完成: newname.txt -> newname.txt.bak\n\n");
    
    // 14. 批量处理文件
    printf("14. 批量文件处理:\n");
    
    // 创建测试文件
    FILE *fp10 = fopen("students.txt", "w");
    if (fp10 != NULL) {
        fprintf(fp10, "1001 张三 85.5\n");
        fprintf(fp10, "1002 李四 90.0\n");
        fprintf(fp10, "1003 王五 87.5\n");
        fclose(fp10);
    }
    
    processStudentFile("students.txt");
    printf("\n");
    
    // 15. 文件锁定概念（简化演示）
    printf("15. 文件访问控制:\n");
    FILE *fp11 = fopen("locked.txt", "w");
    if (fp11 != NULL) {
        fprintf(fp11, "这个文件正在使用\n");
        printf("文件已打开，其他进程可能无法写入\n");
        
        // 模拟长时间操作
        printf("正在处理...\n");
        
        fclose(fp11);
        printf("文件已关闭，其他进程可以访问\n");
    }
    printf("\n");
    
    // 16. 文件大小限制检查
    printf("16. 文件大小检查:\n");
    FILE *fp12 = fopen("students.txt", "rb");
    if (fp12 != NULL) {
        fseek(fp12, 0, SEEK_END);
        long size = ftell(fp12);
        
        printf("文件大小: %ld 字节\n", size);
        
        if (size > 1024 * 1024) {  // 大于1MB
            printf("警告: 文件较大\n");
        } else if (size > 0) {
            printf("文件大小正常\n");
        } else {
            printf("警告: 文件为空\n");
        }
        
        fclose(fp12);
    }
    printf("\n");
    
    // 17. 配置文件读写
    printf("17. 配置文件操作:\n");
    
    // 写入配置
    FILE *config = fopen("config.ini", "w");
    if (config != NULL) {
        fprintf(config, "[Settings]\n");
        fprintf(config, "MaxUsers=100\n");
        fprintf(config, "Timeout=30\n");
        fprintf(config, "EnableLog=true\n");
        fclose(config);
        printf("配置文件已创建\n");
    }
    
    // 读取配置
    FILE *configRead = fopen("config.ini", "r");
    if (configRead != NULL) {
        char line[100];
        printf("配置内容:\n");
        while (fgets(line, sizeof(line), configRead) != NULL) {
            printf("  %s", line);
        }
        fclose(configRead);
    }
    printf("\n");
    
    // 18. CSV文件处理
    printf("18. CSV文件处理:\n");
    
    // 写入CSV
    FILE *csv = fopen("data.csv", "w");
    if (csv != NULL) {
        fprintf(csv, "ID,Name,Score\n");
        fprintf(csv, "1001,张三,85.5\n");
        fprintf(csv, "1002,李四,90.0\n");
        fprintf(csv, "1003,王五,87.5\n");
        fclose(csv);
        printf("CSV文件已创建\n");
    }
    
    // 读取CSV
    FILE *csvRead = fopen("data.csv", "r");
    if (csvRead != NULL) {
        char line[100];
        printf("CSV内容:\n");
        
        // 跳过表头
        fgets(line, sizeof(line), csvRead);
        printf("  %s", line);
        
        // 读取数据
        while (fgets(line, sizeof(line), csvRead) != NULL) {
            printf("  %s", line);
        }
        
        fclose(csvRead);
    }
    printf("\n");
    
    // 19. 文件完整性检查
    printf("19. 文件完整性验证:\n");
    FILE *fp13 = fopen("students.txt", "r");
    if (fp13 != NULL) {
        Student s;
        int validRecords = 0;
        int invalidRecords = 0;
        
        while (fscanf(fp13, "%d %s %f", &s.id, s.name, &s.score) == 3) {
            if (s.id > 0 && s.score >= 0 && s.score <= 100) {
                validRecords++;
            } else {
                invalidRecords++;
            }
        }
        
        printf("有效记录: %d\n", validRecords);
        printf("无效记录: %d\n", invalidRecords);
        
        fclose(fp13);
    }
    printf("\n");
    
    // 20. 错误处理总结
    printf("20. 文件操作错误处理总结:\n");
    printf("1. 始终检查fopen返回值\n");
    printf("2. 使用perror打印错误信息\n");
    printf("3. 使用ferror检测IO错误\n");
    printf("4. 使用feof检测文件结束\n");
    printf("5. 及时关闭文件\n");
    printf("6. 处理异常情况\n");
    printf("7. 验证文件内容\n");
    printf("8. 创建备份文件\n");
    printf("9. 记录日志\n");
    printf("10. 清理临时文件\n");
    
    return 0;
}

// 写入日志
void writeLog(const char *message, LogLevel level) {
    FILE *log = fopen("app.log", "a");
    if (log == NULL) {
        fprintf(stderr, "无法打开日志文件\n");
        return;
    }
    
    // 获取当前时间
    time_t now = time(NULL);
    char *timeStr = ctime(&now);
    timeStr[strlen(timeStr) - 1] = '\0';  // 移除换行符
    
    // 日志级别字符串
    const char *levelStr[] = {"INFO", "WARNING", "ERROR"};
    
    // 写入日志
    fprintf(log, "[%s] [%s] %s\n", timeStr, levelStr[level], message);
    
    fclose(log);
}

// 安全的文件打开
int safeFileOpen(const char *filename, const char *mode, FILE **fp) {
    *fp = fopen(filename, mode);
    
    if (*fp == NULL) {
        fprintf(stderr, "错误: 无法打开文件 %s\n", filename);
        perror("原因");
        return -1;
    }
    
    return 0;
}

// 处理学生文件
void processStudentFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "无法打开文件: %s\n", filename);
        return;
    }
    
    Student s;
    int count = 0;
    float totalScore = 0;
    
    printf("处理学生数据:\n");
    
    while (fscanf(fp, "%d %s %f", &s.id, s.name, &s.score) == 3) {
        printf("  学生: %d %s %.1f\n", s.id, s.name, s.score);
        count++;
        totalScore += s.score;
    }
    
    if (ferror(fp)) {
        fprintf(stderr, "读取文件时发生错误\n");
    } else if (feof(fp)) {
        printf("文件处理完成\n");
        printf("总学生数: %d\n", count);
        printf("平均成绩: %.2f\n", totalScore / count);
    }
    
    fclose(fp);
}

// 创建备份
void createBackup(const char *filename) {
    FILE *src = fopen(filename, "rb");
    if (src == NULL) {
        fprintf(stderr, "无法打开源文件: %s\n", filename);
        return;
    }
    
    // 生成备份文件名
    char backupName[256];
    snprintf(backupName, sizeof(backupName), "%s.bak", filename);
    
    FILE *dst = fopen(backupName, "wb");
    if (dst == NULL) {
        fprintf(stderr, "无法创建备份文件: %s\n", backupName);
        fclose(src);
        return;
    }
    
    // 复制文件内容
    unsigned char buffer[1024];
    size_t bytes;
    
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        if (fwrite(buffer, 1, bytes, dst) != bytes) {
            fprintf(stderr, "写入备份文件时出错\n");
            break;
        }
    }
    
    fclose(src);
    fclose(dst);
}

/*
 * 知识点总结：
 * 
 * 错误检测函数：
 * 
 * 1. ferror():
 *    int ferror(FILE *fp);
 *    - 检测文件流是否有错误
 *    - 有错误返回非0
 *    - 无错误返回0
 * 
 * 2. feof():
 *    int feof(FILE *fp);
 *    - 检测是否到达文件末尾
 *    - 到达返回非0
 *    - 未到达返回0
 * 
 * 3. clearerr():
 *    void clearerr(FILE *fp);
 *    - 清除错误和EOF标志
 *    - 允许继续操作
 * 
 * 注意：
 * - 这些标志在读写操作后设置
 * - 需要在检查前先尝试操作
 * 
 * errno和perror():
 * 
 * errno:
 * - 全局变量
 * - 存储最后一次错误代码
 * - 定义在errno.h
 * 
 * perror():
 * void perror(const char *str);
 * - 打印错误信息到stderr
 * - 格式: "str: 系统错误信息"
 * 
 * 示例：
 * if (fp == NULL) {
 *     printf("errno: %d\n", errno);
 *     perror("文件打开失败");
 * }
 * 
 * 输出示例:
 * errno: 2
 * 文件打开失败: No such file or directory
 * 
 * 文件操作返回值：
 * 
 * fopen():
 * - 成功: 返回FILE指针
 * - 失败: 返回NULL
 * 
 * fclose():
 * - 成功: 返回0
 * - 失败: 返回EOF
 * 
 * fread/fwrite():
 * - 返回实际读写的项数
 * - 小于请求数可能表示错误或EOF
 * 
 * fseek():
 * - 成功: 返回0
 * - 失败: 返回非0
 * 
 * remove():
 * - 成功: 返回0
 * - 失败: 返回非0
 * 
 * rename():
 * - 成功: 返回0
 * - 失败: 返回非0
 * 
 * 临时文件：
 * 
 * tmpfile():
 * FILE *tmpfile(void);
 * - 创建临时二进制文件
 * - "wb+"模式
 * - 关闭时自动删除
 * - 失败返回NULL
 * 
 * 优点：
 * - 自动管理
 * - 不需要命名
 * - 自动清理
 * 
 * tmpnam():
 * char *tmpnam(char *str);
 * - 生成唯一的临时文件名
 * - str为NULL时使用内部缓冲区
 * - 返回文件名指针
 * 
 * 注意：
 * - 只生成名字，不创建文件
 * - 需要手动创建和删除
 * - 可能有安全问题
 * 
 * 文件删除和重命名：
 * 
 * remove():
 * int remove(const char *filename);
 * - 删除文件
 * - 成功返回0
 * - 文件必须关闭
 * 
 * rename():
 * int rename(const char *old, const char *new);
 * - 重命名或移动文件
 * - 成功返回0
 * - 文件必须关闭
 * - 可用于移动文件
 * 
 * 注意：
 * - 文件必须先关闭
 * - 检查返回值
 * - 目标文件存在会被覆盖
 * 
 * 日志系统：
 * 
 * 基本要素：
 * - 时间戳
 * - 日志级别（INFO/WARNING/ERROR）
 * - 日志内容
 * - 追加模式
 * 
 * 实现：
 * void writeLog(const char *msg, LogLevel level) {
 *     FILE *log = fopen("app.log", "a");
 *     // 写入时间、级别、消息
 *     fclose(log);
 * }
 * 
 * 日志级别：
 * - DEBUG: 调试信息
 * - INFO: 一般信息
 * - WARNING: 警告
 * - ERROR: 错误
 * - FATAL: 致命错误
 * 
 * 文件备份：
 * 
 * 策略：
 * 1. 简单备份：
 *    原文件.bak
 * 
 * 2. 时间戳备份：
 *    原文件_20231015.bak
 * 
 * 3. 版本号备份：
 *    原文件.bak1, .bak2
 * 
 * 实现：
 * - 复制整个文件
 * - 使用缓冲区
 * - 检查错误
 * 
 * 配置文件：
 * 
 * INI格式：
 * [Section]
 * Key=Value
 * 
 * 简单格式：
 * Key=Value
 * # 注释
 * 
 * JSON格式：
 * {
 *   "key": "value"
 * }
 * 
 * 读取技巧：
 * - 逐行读取
 * - 解析键值对
 * - 跳过注释
 * - 处理空行
 * 
 * CSV文件：
 * 
 * 格式：
 * Header1,Header2,Header3
 * Value1,Value2,Value3
 * 
 * 读取：
 * - 读取表头
 * - 解析逗号分隔值
 * - 处理引号
 * - 处理换行
 * 
 * 写入：
 * - 写入表头
 * - 用逗号分隔
 * - 必要时加引号
 * 
 * 文件完整性：
 * 
 * 检查项：
 * - 文件是否存在
 * - 文件大小是否合理
 * - 数据格式是否正确
 * - 数值范围是否有效
 * - 必填字段是否存在
 * 
 * 校验方法：
 * - 记录数检查
 * - 字段验证
 * - 范围检查
 * - 格式验证
 * - 校验和（CRC）
 * 
 * 文件锁定：
 * 
 * Windows：
 * - 文件打开时自动锁定
 * - 其他进程无法写入
 * 
 * Linux：
 * - 需要显式锁定
 * - flock()或fcntl()
 * 
 * 应对策略：
 * - 及时关闭文件
 * - 使用临时文件
 * - 重试机制
 * 
 * 安全文件操作：
 * 
 * 1. 检查返回值
 * 2. 验证输入
 * 3. 限制文件大小
 * 4. 使用安全路径
 * 5. 权限控制
 * 6. 避免竞态条件
 * 7. 清理临时文件
 * 8. 加密敏感数据
 * 
 * 错误处理策略：
 * 
 * 1. 预防：
 *    - 检查文件是否存在
 *    - 检查权限
 *    - 验证参数
 * 
 * 2. 检测：
 *    - 检查返回值
 *    - 使用ferror/feof
 *    - 记录错误
 * 
 * 3. 恢复：
 *    - 重试操作
 *    - 使用备份
 *    - 回滚更改
 * 
 * 4. 报告：
 *    - 记录日志
 *    - 通知用户
 *    - 保存错误信息
 * 
 * 最佳实践：
 * 
 * 1. 文件操作：
 *    - 总是检查返回值
 *    - 使用合适的模式
 *    - 及时关闭文件
 *    - 处理所有错误
 * 
 * 2. 数据安全：
 *    - 定期备份
 *    - 验证数据
 *    - 使用事务
 *    - 原子操作
 * 
 * 3. 性能优化：
 *    - 使用缓冲区
 *    - 批量操作
 *    - 减少IO次数
 *    - 异步IO（高级）
 * 
 * 4. 维护性：
 *    - 清晰的命名
 *    - 详细的注释
 *    - 日志记录
 *    - 版本控制
 * 
 * 常见错误：
 * 
 * 1. 不检查返回值
 * 2. 文件未关闭
 * 3. 路径错误
 * 4. 权限不足
 * 5. 磁盘空间满
 * 6. 并发访问冲突
 * 7. 缓冲区溢出
 * 8. 资源泄漏
 * 
 * 调试技巧：
 * 
 * 1. 打印错误信息
 * 2. 检查文件系统
 * 3. 使用调试器
 * 4. 查看日志
 * 5. 单步执行
 * 6. 检查文件内容
 * 7. 验证路径
 * 8. 测试边界情况
 * 
 * 实际应用：
 * 
 * - 数据持久化
 * - 配置管理
 * - 日志记录
 * - 数据导入导出
 * - 文件处理工具
 * - 数据分析
 * - 批处理
 * - 系统集成
 */
