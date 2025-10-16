/*
 * 第一章：基础语法
 * 1.6 输入输出
 * 
 * 学习目标：
 * 1. 掌握printf函数的各种用法
 * 2. 学会使用scanf函数获取用户输入
 * 3. 了解其他输入输出函数
 */

#include <stdio.h>

int main() {
    printf("=== C语言输入输出详解 ===\n\n");
    
    // 1. printf 基本用法
    printf("1. printf 基本输出:\n");
    printf("这是一个简单的字符串\n");
    printf("可以输出多行\n");
    printf("使用 \\n 换行\n\n");
    
    // 2. printf 格式化输出
    printf("2. printf 格式化输出:\n");
    
    int age = 25;
    float height = 1.75;
    char grade = 'A';
    char name[] = "张三";
    
    printf("姓名: %s\n", name);
    printf("年龄: %d 岁\n", age);
    printf("身高: %.2f 米\n", height);
    printf("等级: %c\n\n", grade);
    
    // 3. 格式说明符详解
    printf("3. 各种格式说明符:\n");
    
    int num = 42;
    printf("%%d (十进制整数):     %d\n", num);
    printf("%%i (十进制整数):     %i\n", num);
    printf("%%o (八进制):         %o\n", num);
    printf("%%x (十六进制小写):   %x\n", num);
    printf("%%X (十六进制大写):   %X\n\n", num);
    
    unsigned int unum = 42;
    printf("%%u (无符号整数):     %u\n\n", unum);
    
    // 4. 浮点数格式化
    printf("4. 浮点数格式化:\n");
    
    double pi = 3.141592653589793;
    printf("%%f (默认6位小数):    %f\n", pi);
    printf("%%.2f (2位小数):      %.2f\n", pi);
    printf("%%.10f (10位小数):    %.10f\n", pi);
    printf("%%e (科学计数法):     %e\n", pi);
    printf("%%g (自动选择):       %g\n\n", pi);
    
    // 5. 字符和字符串
    printf("5. 字符和字符串输出:\n");
    
    char ch = 'H';
    char str[] = "Hello, World!";
    printf("%%c (字符):           %c\n", ch);
    printf("%%s (字符串):         %s\n\n", str);
    
    // 6. 宽度和对齐
    printf("6. 输出宽度和对齐:\n");
    
    int value = 123;
    printf("无宽度:       %d\n", value);
    printf("宽度10右对齐: %10d\n", value);
    printf("宽度10左对齐: %-10d|\n", value);
    printf("宽度10补零:   %010d\n\n", value);
    
    // 浮点数宽度控制
    float price = 19.99;
    printf("价格:         %8.2f 元\n", price);
    printf("价格(左对齐): %-8.2f 元\n\n", price);
    
    // 7. scanf 基本用法
    printf("7. scanf 输入示例:\n");
    printf("请输入一个整数: ");
    int input_num;
    scanf("%d", &input_num);  // 注意：必须使用&取地址
    printf("你输入的整数是: %d\n\n", input_num);
    
    // 清除输入缓冲区
    while (getchar() != '\n');
    
    // 8. 多个输入
    printf("8. 输入多个值:\n");
    printf("请输入年龄和身高(用空格分隔): ");
    int user_age;
    float user_height;
    scanf("%d %f", &user_age, &user_height);
    printf("年龄: %d 岁, 身高: %.2f 米\n\n", user_age, user_height);
    
    // 清除输入缓冲区
    while (getchar() != '\n');
    
    // 9. 字符输入
    printf("9. 字符输入:\n");
    printf("请输入一个字符: ");
    char input_char;
    scanf(" %c", &input_char);  // 空格跳过前面的空白字符
    printf("你输入的字符是: %c (ASCII: %d)\n\n", input_char, input_char);
    
    // 清除输入缓冲区
    while (getchar() != '\n');
    
    // 10. 字符串输入（注意空格问题）
    printf("10. 字符串输入:\n");
    printf("请输入你的名字(不含空格): ");
    char username[50];
    scanf("%s", username);  // 字符串数组名本身就是地址，不需要&
    printf("你好, %s!\n\n", username);
    
    // 清除输入缓冲区
    while (getchar() != '\n');
    
    // 11. 使用 fgets 输入带空格的字符串
    printf("11. 输入带空格的字符串:\n");
    printf("请输入一句话: ");
    char sentence[100];
    fgets(sentence, sizeof(sentence), stdin);
    printf("你说: %s\n", sentence);
    
    // 12. 单字符输入输出函数
    printf("12. getchar 和 putchar:\n");
    printf("请输入一个字符: ");
    char c = getchar();
    printf("你输入的字符是: ");
    putchar(c);
    putchar('\n');
    printf("\n");
    
    // 清除输入缓冲区
    while (getchar() != '\n');
    
    // 13. 实际应用：简单计算器
    printf("13. 实际应用 - 简单计算器:\n");
    float num1, num2, result;
    char operator;
    
    printf("请输入表达式 (如: 5 + 3): ");
    scanf("%f %c %f", &num1, &operator, &num2);
    
    switch (operator) {
        case '+':
            result = num1 + num2;
            printf("%.2f + %.2f = %.2f\n", num1, num2, result);
            break;
        case '-':
            result = num1 - num2;
            printf("%.2f - %.2f = %.2f\n", num1, num2, result);
            break;
        case '*':
            result = num1 * num2;
            printf("%.2f * %.2f = %.2f\n", num1, num2, result);
            break;
        case '/':
            if (num2 != 0) {
                result = num1 / num2;
                printf("%.2f / %.2f = %.2f\n", num1, num2, result);
            } else {
                printf("错误: 除数不能为0\n");
            }
            break;
        default:
            printf("错误: 不支持的运算符\n");
    }
    
    return 0;
}

/*
 * 知识点总结：
 * 
 * printf 函数：
 * - 功能：格式化输出到标准输出（屏幕）
 * - 语法：printf("格式字符串", 参数列表);
 * 
 * 常用格式说明符：
 * %d, %i  - int (十进制整数)
 * %u      - unsigned int (无符号整数)
 * %ld     - long int
 * %lld    - long long int
 * %f      - float/double (浮点数)
 * %lf     - double (在scanf中使用)
 * %e, %E  - 科学计数法
 * %c      - char (字符)
 * %s      - 字符串
 * %p      - 指针地址
 * %x, %X  - 十六进制
 * %o      - 八进制
 * %%      - 输出%符号
 * 
 * 格式控制：
 * %10d    - 宽度为10，右对齐
 * %-10d   - 宽度为10，左对齐
 * %010d   - 宽度为10，前面补0
 * %.2f    - 保留2位小数
 * %8.2f   - 总宽度8，保留2位小数
 * 
 * scanf 函数：
 * - 功能：从标准输入（键盘）读取格式化数据
 * - 语法：scanf("格式字符串", 地址列表);
 * - 注意：变量前必须加 & (取地址符)，数组名除外
 * 
 * 其他输入输出函数：
 * getchar()  - 读取单个字符
 * putchar()  - 输出单个字符
 * gets()     - 读取一行字符串（不安全，已弃用）
 * fgets()    - 读取一行字符串（安全）
 * puts()     - 输出字符串并换行
 * 
 * 注意事项：
 * 1. scanf 读取数据时会留下换行符，需要清除缓冲区
 * 2. 字符串输入时，数组名不需要 &
 * 3. scanf 的 %s 遇到空格会停止，使用 fgets 可以读取包含空格的字符串
 * 4. printf 的 %f 可以用于 float 和 double
 * 5. scanf 读取 double 时要用 %lf，读取 float 时用 %f
 * 
 * 最佳实践：
 * - 使用 fgets 代替 gets
 * - 使用 scanf 后及时清除缓冲区
 * - 检查 scanf 的返回值以确保输入成功
 * - 为字符串数组分配足够的空间
 */
