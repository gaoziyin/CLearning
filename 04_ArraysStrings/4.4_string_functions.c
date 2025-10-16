/*
 * 第四章：数组与字符串
 * 4.4 字符串处理函数 (string.h)
 * 
 * 学习目标：
 * 1. 掌握标准字符串库函数
 * 2. 学会使用string.h中的常用函数
 * 3. 了解字符串处理的最佳实践
 */

#include <stdio.h>
#include <string.h>  // 字符串处理函数库
#include <ctype.h>   // 字符处理函数库

int main() {
    printf("=== 字符串处理函数详解 ===\n\n");
    
    // 1. strlen() - 计算字符串长度
    printf("1. strlen() - 字符串长度:\n");
    char str1[] = "Hello World";
    char str2[] = "C Programming";
    
    printf("字符串: \"%s\"\n", str1);
    printf("长度: %zu\n", strlen(str1));
    printf("字符串: \"%s\"\n", str2);
    printf("长度: %zu\n\n", strlen(str2));
    
    // 2. strcpy() - 字符串复制
    printf("2. strcpy() - 字符串复制:\n");
    char source[] = "Copy me!";
    char dest[50];
    
    strcpy(dest, source);  // 复制source到dest
    
    printf("源字符串: %s\n", source);
    printf("目标字符串: %s\n\n", dest);
    
    // 3. strncpy() - 安全的字符串复制
    printf("3. strncpy() - 限制长度的复制:\n");
    char src[] = "Hello World";
    char dst[20];
    
    strncpy(dst, src, 5);  // 只复制前5个字符
    dst[5] = '\0';  // 手动添加结束符
    
    printf("源字符串: %s\n", src);
    printf("复制前5个字符: %s\n\n", dst);
    
    // 4. strcat() - 字符串拼接
    printf("4. strcat() - 字符串拼接:\n");
    char first[50] = "Hello ";
    char second[] = "World!";
    
    strcat(first, second);  // 将second追加到first后面
    
    printf("拼接结果: %s\n\n", first);
    
    // 5. strncat() - 安全的字符串拼接
    printf("5. strncat() - 限制长度的拼接:\n");
    char base[50] = "Hello ";
    char append[] = "Beautiful World";
    
    strncat(base, append, 9);  // 只追加9个字符
    
    printf("拼接结果: %s\n\n", base);
    
    // 6. strcmp() - 字符串比较
    printf("6. strcmp() - 字符串比较:\n");
    char str_a[] = "Apple";
    char str_b[] = "Apple";
    char str_c[] = "Banana";
    
    printf("比较 \"%s\" 和 \"%s\": %d\n", str_a, str_b, strcmp(str_a, str_b));
    printf("(0表示相等)\n");
    
    int result = strcmp(str_a, str_c);
    printf("比较 \"%s\" 和 \"%s\": %d\n", str_a, str_c, result);
    printf("(负数表示第一个小于第二个)\n\n");
    
    // 7. strncmp() - 比较前n个字符
    printf("7. strncmp() - 比较前n个字符:\n");
    char word1[] = "Hello";
    char word2[] = "Help";
    
    printf("比较 \"%s\" 和 \"%s\" 的前3个字符: %d\n", 
           word1, word2, strncmp(word1, word2, 3));
    printf("比较 \"%s\" 和 \"%s\" 的前4个字符: %d\n\n", 
           word1, word2, strncmp(word1, word2, 4));
    
    // 8. strchr() - 查找字符
    printf("8. strchr() - 查找字符:\n");
    char text[] = "Hello World";
    char search_char = 'W';
    char *position = strchr(text, search_char);
    
    if (position != NULL) {
        printf("在字符串 \"%s\" 中找到 '%c'\n", text, search_char);
        printf("位置: %ld\n", position - text);
        printf("从该位置开始: %s\n", position);
    } else {
        printf("未找到字符 '%c'\n", search_char);
    }
    printf("\n");
    
    // 9. strrchr() - 从右边查找字符
    printf("9. strrchr() - 从右边查找字符:\n");
    char filename[] = "document.backup.txt";
    char *dot = strrchr(filename, '.');
    
    if (dot != NULL) {
        printf("文件名: %s\n", filename);
        printf("扩展名: %s\n\n", dot);
    }
    
    // 10. strstr() - 查找子串
    printf("10. strstr() - 查找子串:\n");
    char haystack[] = "The quick brown fox jumps over the lazy dog";
    char needle[] = "fox";
    char *found = strstr(haystack, needle);
    
    if (found != NULL) {
        printf("在 \"%s\" 中\n", haystack);
        printf("找到子串 \"%s\"\n", needle);
        printf("位置: %ld\n", found - haystack);
        printf("从该位置开始: %s\n", found);
    }
    printf("\n");
    
    // 11. strtok() - 字符串分割
    printf("11. strtok() - 字符串分割:\n");
    char sentence[] = "Hello,World,C,Programming";
    char *token;
    
    printf("原字符串: %s\n", sentence);
    printf("分割后:\n");
    
    token = strtok(sentence, ",");  // 第一次调用
    while (token != NULL) {
        printf("  %s\n", token);
        token = strtok(NULL, ",");  // 后续调用传NULL
    }
    printf("\n");
    
    // 12. sprintf() - 格式化字符串
    printf("12. sprintf() - 格式化字符串:\n");
    char buffer[100];
    int age = 25;
    float height = 1.75;
    
    sprintf(buffer, "年龄: %d, 身高: %.2f米", age, height);
    printf("格式化结果: %s\n\n", buffer);
    
    // 13. sscanf() - 从字符串读取格式化数据
    printf("13. sscanf() - 解析字符串:\n");
    char data[] = "25 1.75";
    int parsed_age;
    float parsed_height;
    
    sscanf(data, "%d %f", &parsed_age, &parsed_height);
    printf("原字符串: %s\n", data);
    printf("解析出的年龄: %d\n", parsed_age);
    printf("解析出的身高: %.2f\n\n", parsed_height);
    
    // 14. ctype.h 字符处理函数
    printf("14. ctype.h 字符处理函数:\n");
    char ch = 'a';
    
    printf("字符: %c\n", ch);
    printf("是否为字母: %s\n", isalpha(ch) ? "是" : "否");
    printf("是否为数字: %s\n", isdigit(ch) ? "是" : "否");
    printf("是否为小写: %s\n", islower(ch) ? "是" : "否");
    printf("是否为大写: %s\n", isupper(ch) ? "是" : "否");
    printf("转大写: %c\n", toupper(ch));
    printf("转小写: %c\n\n", tolower(ch));
    
    // 15. 实际应用：URL解析
    printf("15. 实际应用 - URL解析:\n");
    char url[] = "https://www.example.com/path/to/page.html";
    char url_copy[100];
    strcpy(url_copy, url);
    
    // 查找协议
    char *protocol_end = strstr(url_copy, "://");
    if (protocol_end != NULL) {
        *protocol_end = '\0';
        printf("协议: %s\n", url_copy);
        
        // 查找域名
        char *domain = protocol_end + 3;
        char *path_start = strchr(domain, '/');
        if (path_start != NULL) {
            *path_start = '\0';
            printf("域名: %s\n", domain);
            printf("路径: %s\n", path_start + 1);
        }
    }
    printf("\n");
    
    // 16. 实际应用：邮箱验证
    printf("16. 实际应用 - 邮箱格式检查:\n");
    char email[] = "user@example.com";
    
    char *at = strchr(email, '@');
    char *dot = strrchr(email, '.');
    
    printf("邮箱: %s\n", email);
    if (at != NULL && dot != NULL && at < dot) {
        printf("格式: 有效\n");
        printf("用户名长度: %ld\n", at - email);
        printf("域名: %s\n", at + 1);
    } else {
        printf("格式: 无效\n");
    }
    printf("\n");
    
    // 17. 实际应用：字符串清理
    printf("17. 实际应用 - 删除空格:\n");
    char messy[] = "  Hello   World  ";
    char clean[100];
    int j = 0;
    
    printf("原字符串: \"%s\"\n", messy);
    
    // 删除首尾空格
    int start = 0;
    int end = strlen(messy) - 1;
    
    while (messy[start] == ' ') start++;
    while (end >= 0 && messy[end] == ' ') end--;
    
    for (int i = start; i <= end; i++) {
        clean[j++] = messy[i];
    }
    clean[j] = '\0';
    
    printf("清理后: \"%s\"\n\n", clean);
    
    // 18. 实际应用：密码强度检查
    printf("18. 实际应用 - 密码强度:\n");
    char password[] = "SecurePass123!";
    
    int len = strlen(password);
    int has_upper = 0, has_lower = 0, has_digit = 0, has_special = 0;
    
    for (int i = 0; i < len; i++) {
        if (isupper(password[i])) has_upper = 1;
        if (islower(password[i])) has_lower = 1;
        if (isdigit(password[i])) has_digit = 1;
        if (!isalnum(password[i])) has_special = 1;
    }
    
    printf("密码: %s\n", password);
    printf("长度: %d\n", len);
    printf("包含大写: %s\n", has_upper ? "✓" : "✗");
    printf("包含小写: %s\n", has_lower ? "✓" : "✗");
    printf("包含数字: %s\n", has_digit ? "✓" : "✗");
    printf("包含特殊字符: %s\n", has_special ? "✓" : "✗");
    
    int strength = has_upper + has_lower + has_digit + has_special;
    if (len >= 8 && strength >= 3) {
        printf("强度: 强\n");
    } else if (len >= 6 && strength >= 2) {
        printf("强度: 中\n");
    } else {
        printf("强度: 弱\n");
    }
    
    return 0;
}

/*
 * 知识点总结：
 * 
 * string.h 常用函数：
 * 
 * 1. 长度计算：
 *    size_t strlen(const char *str);
 *    - 返回字符串长度（不含'\0'）
 * 
 * 2. 字符串复制：
 *    char *strcpy(char *dest, const char *src);
 *    - 复制src到dest（包括'\0'）
 *    - 不安全，可能越界
 * 
 *    char *strncpy(char *dest, const char *src, size_t n);
 *    - 复制最多n个字符
 *    - 更安全
 *    - 可能不添加'\0'
 * 
 * 3. 字符串拼接：
 *    char *strcat(char *dest, const char *src);
 *    - 将src追加到dest后
 *    - dest必须有足够空间
 * 
 *    char *strncat(char *dest, const char *src, size_t n);
 *    - 追加最多n个字符
 *    - 自动添加'\0'
 * 
 * 4. 字符串比较：
 *    int strcmp(const char *s1, const char *s2);
 *    - 返回0：相等
 *    - 返回负数：s1 < s2
 *    - 返回正数：s1 > s2
 * 
 *    int strncmp(const char *s1, const char *s2, size_t n);
 *    - 只比较前n个字符
 * 
 * 5. 查找字符：
 *    char *strchr(const char *str, int ch);
 *    - 从左查找字符ch
 *    - 返回指针或NULL
 * 
 *    char *strrchr(const char *str, int ch);
 *    - 从右查找字符ch
 * 
 * 6. 查找子串：
 *    char *strstr(const char *haystack, const char *needle);
 *    - 在haystack中查找needle
 *    - 返回首次出现的位置
 * 
 * 7. 字符串分割：
 *    char *strtok(char *str, const char *delim);
 *    - 用delim分割str
 *    - 第一次传str，后续传NULL
 *    - 会修改原字符串
 * 
 * 8. 格式化：
 *    int sprintf(char *str, const char *format, ...);
 *    - 格式化输出到字符串
 * 
 *    int sscanf(const char *str, const char *format, ...);
 *    - 从字符串读取格式化数据
 * 
 * ctype.h 字符处理函数：
 * 
 * 1. 字符检查：
 *    isalpha(ch)  - 是否为字母
 *    isdigit(ch)  - 是否为数字
 *    isalnum(ch)  - 是否为字母或数字
 *    islower(ch)  - 是否为小写
 *    isupper(ch)  - 是否为大写
 *    isspace(ch)  - 是否为空白字符
 * 
 * 2. 字符转换：
 *    toupper(ch)  - 转大写
 *    tolower(ch)  - 转小写
 * 
 * 安全性考虑：
 * 
 * 不安全的函数：
 * - strcpy：可能越界
 * - strcat：可能越界
 * - gets：已弃用
 * - sprintf：可能越界
 * 
 * 安全的替代：
 * - strncpy：限制长度
 * - strncat：限制长度
 * - fgets：替代gets
 * - snprintf：替代sprintf
 * 
 * 注意事项：
 * 1. strcpy和strcat要确保目标空间足够
 * 2. strncpy不一定添加'\0'
 * 3. strtok会修改原字符串
 * 4. strcmp返回值的含义
 * 5. 字符串函数不检查NULL指针
 * 
 * 常见错误：
 * 1. 目标缓冲区太小：
 *    char dest[5];
 *    strcpy(dest, "Hello World");  // 越界
 * 
 * 2. 忘记'\0'：
 *    char str[5];
 *    strncpy(str, "Hello", 5);  // 没有'\0'
 * 
 * 3. 比较字符串用==：
 *    if (str1 == str2) { }  // 错误
 * 
 * 4. strtok用法错误：
 *    char *t1 = strtok(str, ",");
 *    char *t2 = strtok(str, ",");  // 错误！应该用NULL
 * 
 * 最佳实践：
 * - 优先使用安全的n系列函数
 * - 总是检查返回值
 * - 确保缓冲区足够大
 * - 使用const保护只读参数
 * - 检查NULL指针
 * - 使用strlen计算实际长度
 * - 为'\0'预留空间
 * - 字符串操作前验证输入
 * 
 * 性能提示：
 * - strlen需要遍历，避免重复调用
 * - 大字符串操作考虑使用memcpy
 * - 频繁拼接考虑使用缓冲区
 */
