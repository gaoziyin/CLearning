/*
 * 第四章：数组与字符串
 * 4.3 字符数组与字符串基础
 * 
 * 学习目标：
 * 1. 理解字符串的概念
 * 2. 掌握字符数组和字符串的关系
 * 3. 学会字符串的基本操作
 */

#include <stdio.h>

int main() {
    printf("=== 字符数组与字符串基础 ===\n\n");
    
    // 1. 字符数组的声明和初始化
    printf("1. 字符数组:\n");
    char ch1 = 'A';  // 单个字符
    char ch_arr[5] = {'H', 'e', 'l', 'l', 'o'};  // 字符数组
    
    printf("单个字符: %c\n", ch1);
    printf("字符数组: ");
    for (int i = 0; i < 5; i++) {
        printf("%c", ch_arr[i]);
    }
    printf("\n\n");
    
    // 2. 字符串的表示
    printf("2. 字符串（以\\0结尾的字符数组）:\n");
    char str1[6] = {'H', 'e', 'l', 'l', 'o', '\0'};  // 手动添加\0
    char str2[] = "Hello";  // 自动添加\0
    
    printf("str1: %s\n", str1);
    printf("str2: %s\n", str2);
    printf("str2的长度: %zu (不包括\\0)\n", sizeof(str2) - 1);
    printf("str2占用字节: %zu (包括\\0)\n\n", sizeof(str2));
    
    // 3. 字符串的声明方式
    printf("3. 字符串的不同声明方式:\n");
    
    char string1[] = "Hello";           // 自动计算大小
    char string2[10] = "Hello";         // 指定大小
    char string3[10] = {'H', 'i', '\0'}; // 字符数组形式
    
    printf("string1: %s\n", string1);
    printf("string2: %s\n", string2);
    printf("string3: %s\n\n", string3);
    
    // 4. 访问字符串中的字符
    printf("4. 访问字符串中的字符:\n");
    char word[] = "Programming";
    printf("完整字符串: %s\n", word);
    printf("第1个字符: %c\n", word[0]);
    printf("第5个字符: %c\n", word[4]);
    printf("最后一个字符: %c\n", word[10]);  // 'g'
    printf("字符串结束符: %d (ASCII码)\n\n", word[11]);  // '\0' = 0
    
    // 5. 遍历字符串
    printf("5. 遍历字符串:\n");
    char text[] = "Hello World";
    
    printf("逐字符输出: ");
    for (int i = 0; text[i] != '\0'; i++) {
        printf("%c ", text[i]);
    }
    printf("\n\n");
    
    // 6. 计算字符串长度
    printf("6. 计算字符串长度:\n");
    char message[] = "C Programming";
    int length = 0;
    
    while (message[length] != '\0') {
        length++;
    }
    
    printf("字符串: %s\n", message);
    printf("长度: %d\n\n", length);
    
    // 7. 字符串输入
    printf("7. 字符串输入输出:\n");
    char name[50];
    printf("请输入你的名字: ");
    scanf("%s", name);  // 遇到空格停止
    printf("你好, %s!\n\n", name);
    
    // 清除输入缓冲
    while (getchar() != '\n');
    
    // 8. 输入带空格的字符串
    printf("8. 输入带空格的字符串:\n");
    char sentence[100];
    printf("请输入一句话: ");
    fgets(sentence, sizeof(sentence), stdin);
    printf("你说: %s", sentence);  // fgets会保留换行符
    printf("\n");
    
    // 9. 字符串复制（手动实现）
    printf("9. 字符串复制:\n");
    char source[] = "Copy me!";
    char destination[50];
    int i = 0;
    
    while (source[i] != '\0') {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0';  // 别忘了结束符
    
    printf("源字符串: %s\n", source);
    printf("目标字符串: %s\n\n", destination);
    
    // 10. 字符串比较（手动实现）
    printf("10. 字符串比较:\n");
    char str_a[] = "Hello";
    char str_b[] = "Hello";
    char str_c[] = "World";
    
    // 比较str_a和str_b
    int same = 1;
    for (int i = 0; str_a[i] != '\0' || str_b[i] != '\0'; i++) {
        if (str_a[i] != str_b[i]) {
            same = 0;
            break;
        }
    }
    
    printf("\"%s\" 和 \"%s\" %s\n", str_a, str_b, same ? "相同" : "不同");
    
    // 比较str_a和str_c
    same = 1;
    for (int i = 0; str_a[i] != '\0' || str_c[i] != '\0'; i++) {
        if (str_a[i] != str_c[i]) {
            same = 0;
            break;
        }
    }
    
    printf("\"%s\" 和 \"%s\" %s\n\n", str_a, str_c, same ? "相同" : "不同");
    
    // 11. 字符串拼接（手动实现）
    printf("11. 字符串拼接:\n");
    char first[] = "Hello ";
    char second[] = "World!";
    char combined[50];
    
    int idx = 0;
    // 复制第一个字符串
    for (int j = 0; first[j] != '\0'; j++) {
        combined[idx++] = first[j];
    }
    // 复制第二个字符串
    for (int j = 0; second[j] != '\0'; j++) {
        combined[idx++] = second[j];
    }
    combined[idx] = '\0';
    
    printf("第一个: %s\n", first);
    printf("第二个: %s\n", second);
    printf("拼接后: %s\n\n", combined);
    
    // 12. 统计字符出现次数
    printf("12. 统计字符出现次数:\n");
    char sample[] = "programming";
    char target_ch = 'g';
    int count = 0;
    
    for (int i = 0; sample[i] != '\0'; i++) {
        if (sample[i] == target_ch) {
            count++;
        }
    }
    
    printf("字符串: %s\n", sample);
    printf("字符 '%c' 出现了 %d 次\n\n", target_ch, count);
    
    // 13. 大小写转换
    printf("13. 大小写转换:\n");
    char lower[] = "hello world";
    char upper[50];
    
    for (int i = 0; lower[i] != '\0'; i++) {
        if (lower[i] >= 'a' && lower[i] <= 'z') {
            upper[i] = lower[i] - 32;  // 转大写
        } else {
            upper[i] = lower[i];
        }
    }
    upper[sizeof(lower) - 1] = '\0';
    
    printf("小写: %s\n", lower);
    printf("大写: %s\n\n", upper);
    
    // 14. 反转字符串
    printf("14. 反转字符串:\n");
    char original[] = "Hello";
    int len = 0;
    
    // 计算长度
    while (original[len] != '\0') {
        len++;
    }
    
    printf("原字符串: %s\n", original);
    
    // 反转
    for (int i = 0; i < len / 2; i++) {
        char temp = original[i];
        original[i] = original[len - 1 - i];
        original[len - 1 - i] = temp;
    }
    
    printf("反转后: %s\n\n", original);
    
    // 15. 字符串数组
    printf("15. 字符串数组（二维字符数组）:\n");
    char fruits[5][20] = {
        "Apple",
        "Banana",
        "Orange",
        "Grape",
        "Mango"
    };
    
    printf("水果列表:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d. %s\n", i + 1, fruits[i]);
    }
    printf("\n");
    
    // 16. 实际应用：密码验证
    printf("16. 实际应用 - 密码强度检查:\n");
    char password[] = "Pass123!";
    
    int has_upper = 0, has_lower = 0, has_digit = 0, has_special = 0;
    int pwd_len = 0;
    
    for (int i = 0; password[i] != '\0'; i++) {
        pwd_len++;
        if (password[i] >= 'A' && password[i] <= 'Z') has_upper = 1;
        if (password[i] >= 'a' && password[i] <= 'z') has_lower = 1;
        if (password[i] >= '0' && password[i] <= '9') has_digit = 1;
        if (!((password[i] >= 'A' && password[i] <= 'Z') ||
              (password[i] >= 'a' && password[i] <= 'z') ||
              (password[i] >= '0' && password[i] <= '9'))) {
            has_special = 1;
        }
    }
    
    printf("密码: %s\n", password);
    printf("长度: %d\n", pwd_len);
    printf("包含大写字母: %s\n", has_upper ? "是" : "否");
    printf("包含小写字母: %s\n", has_lower ? "是" : "否");
    printf("包含数字: %s\n", has_digit ? "是" : "否");
    printf("包含特殊字符: %s\n", has_special ? "是" : "否");
    
    int strength = has_upper + has_lower + has_digit + has_special;
    if (pwd_len >= 8 && strength >= 3) {
        printf("密码强度: 强\n");
    } else if (pwd_len >= 6 && strength >= 2) {
        printf("密码强度: 中\n");
    } else {
        printf("密码强度: 弱\n");
    }
    
    return 0;
}

/*
 * 知识点总结：
 * 
 * 字符串的概念：
 * - 在C语言中，字符串是以'\0'结尾的字符数组
 * - '\0'是字符串结束标志（ASCII码为0）
 * - 字符串长度不包括'\0'
 * - 数组大小要包括'\0'
 * 
 * 字符 vs 字符串：
 * - 字符：单个字符，用单引号 'A'
 * - 字符串：字符序列，用双引号 "ABC"
 * 
 * 字符串的表示：
 * 1. 字符数组形式：
 *    char str[] = {'H', 'i', '\0'};
 * 
 * 2. 字符串字面量：
 *    char str[] = "Hi";  // 自动添加'\0'
 * 
 * 字符串的声明：
 * 1. 自动大小：
 *    char str[] = "Hello";  // 大小为6（包括'\0'）
 * 
 * 2. 指定大小：
 *    char str[10] = "Hello";  // 剩余空间填充0
 * 
 * 3. 未初始化：
 *    char str[10];  // 内容不确定
 * 
 * 字符串输入：
 * 1. scanf("%s", str);
 *    - 读取到空格或换行停止
 *    - 不读取空格
 *    - 容易越界
 * 
 * 2. gets(str);  (不安全，已弃用)
 *    - 读取整行
 *    - 包括空格
 *    - 没有边界检查
 * 
 * 3. fgets(str, size, stdin);  (推荐)
 *    - 读取整行
 *    - 有大小限制
 *    - 安全
 *    - 包含换行符
 * 
 * 字符串输出：
 * 1. printf("%s", str);
 *    - 输出到'\0'为止
 * 
 * 2. puts(str);
 *    - 自动换行
 * 
 * 字符串长度：
 * - 不包括'\0'
 * - 手动计算：
 *   int len = 0;
 *   while (str[len] != '\0') len++;
 * 
 * 字符串操作（手动实现）：
 * 
 * 1. 复制：
 *    while ((dest[i] = src[i]) != '\0') i++;
 * 
 * 2. 比较：
 *    逐字符比较直到'\0'
 * 
 * 3. 拼接：
 *    先复制第一个，再追加第二个
 * 
 * 4. 长度：
 *    计数到'\0'
 * 
 * 字符串数组：
 * char strs[行数][列数];
 * 
 * 例如：
 * char names[3][20] = {"Alice", "Bob", "Charlie"};
 * 
 * 字符串常量：
 * - "Hello" 是字符串常量
 * - 存储在只读内存区
 * - 不能修改
 * 
 * 字符串指针（后续章节）：
 * char *str = "Hello";
 * - str指向字符串常量
 * - 不能修改内容
 * 
 * 转义字符：
 * \n  - 换行
 * \t  - 制表符
 * \\  - 反斜杠
 * \"  - 双引号
 * \'  - 单引号
 * \0  - 空字符
 * 
 * ASCII码：
 * - 'A' - 'Z': 65-90
 * - 'a' - 'z': 97-122
 * - '0' - '9': 48-57
 * - 大小写差32
 * 
 * 注意事项：
 * 1. 必须有'\0'结束符
 * 2. 数组大小要足够（包括'\0'）
 * 3. scanf读取字符串容易越界
 * 4. 字符串比较不能用 ==
 * 5. 字符串赋值不能用 =
 * 
 * 常见错误：
 * 1. 忘记'\0'：
 *    char str[5] = {'H', 'e', 'l', 'l', 'o'};  // 缺少'\0'
 * 
 * 2. 数组太小：
 *    char str[5] = "Hello";  // 需要6个字节
 * 
 * 3. 直接比较：
 *    if (str1 == str2) { }  // 错误！比较的是地址
 * 
 * 4. 直接赋值：
 *    str1 = str2;  // 错误！数组名不能赋值
 * 
 * 5. 越界访问：
 *    char str[5];
 *    scanf("%s", str);  // 输入超过4个字符会越界
 * 
 * 最佳实践：
 * - 使用fgets代替gets和scanf
 * - 总是检查字符串长度
 * - 初始化字符串数组
 * - 预留足够空间（包括'\0'）
 * - 使用string.h的标准函数
 * - 避免硬编码字符串大小
 * - 检查输入的有效性
 */
