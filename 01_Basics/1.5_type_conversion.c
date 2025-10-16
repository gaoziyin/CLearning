/*
 * 第一章：基础语法
 * 1.5 类型转换
 * 
 * 学习目标：
 * 1. 理解隐式类型转换
 * 2. 掌握显式类型转换（强制类型转换）
 * 3. 了解类型转换的注意事项
 */

#include <stdio.h>

int main() {
    printf("=== C语言类型转换 ===\n\n");
    
    // 1. 隐式类型转换（自动转换）
    printf("1. 隐式类型转换（自动转换）:\n");
    
    // 整型提升
    char c = 'A';  // ASCII码为65
    int i = c;     // char自动转换为int
    printf("字符 '%c' 转换为整数: %d\n", c, i);
    
    // 算术运算中的自动转换
    int a = 5;
    float b = 2.5;
    float result = a + b;  // int自动转换为float
    printf("整数 %d + 浮点数 %.1f = %.1f\n\n", a, b, result);
    
    // 2. 类型转换的规则
    printf("2. 算术运算中的类型提升规则:\n");
    
    char ch = 10;
    short sh = 20;
    int n = 30;
    long ln = 40L;
    float f = 5.5f;
    double d = 6.6;
    
    // 表达式中向高级类型转换
    printf("char + short = int: %zu 字节\n", sizeof(ch + sh));
    printf("int + long = long: %zu 字节\n", sizeof(n + ln));
    printf("int + float = float: %zu 字节\n", sizeof(n + f));
    printf("float + double = double: %zu 字节\n\n", sizeof(f + d));
    
    // 3. 显式类型转换（强制类型转换）
    printf("3. 显式类型转换（强制类型转换）:\n");
    
    // 浮点数转整数
    double pi = 3.14159;
    int pi_int = (int)pi;  // 强制转换为int，小数部分被截断
    printf("double %.5f 强制转换为 int: %d\n", pi, pi_int);
    
    // 整数转浮点数
    int x = 7, y = 2;
    float division1 = x / y;           // 整数除法，结果为3
    float division2 = (float)x / y;    // 强制转换后为浮点除法
    printf("整数除法: %d / %d = %.1f\n", x, y, division1);
    printf("浮点除法: (float)%d / %d = %.2f\n\n", x, y, division2);
    
    // 4. 赋值运算中的类型转换
    printf("4. 赋值运算中的类型转换:\n");
    
    int num1 = 3.9;  // 浮点数赋值给整数，小数部分丢失
    printf("3.9 赋值给 int: %d\n", num1);
    
    float num2 = 100;  // 整数赋值给浮点数
    printf("100 赋值给 float: %.1f\n", num2);
    
    // 大类型赋值给小类型（可能溢出）
    int big = 300;
    char small = big;  // 可能发生溢出
    printf("int 300 赋值给 char: %d (可能溢出)\n\n", small);
    
    // 5. 字符和整数的转换
    printf("5. 字符和整数的转换:\n");
    
    char letter = 'A';
    printf("字符 '%c' 的ASCII码: %d\n", letter, letter);
    
    int ascii = 66;
    printf("ASCII码 %d 对应的字符: '%c'\n", ascii, (char)ascii);
    
    // 大小写转换
    char lowercase = 'a';
    char uppercase = lowercase - 32;  // 利用ASCII码差值
    printf("小写 '%c' 转大写: '%c'\n\n", lowercase, uppercase);
    
    // 6. 精度损失示例
    printf("6. 类型转换中的精度损失:\n");
    
    double precise = 123.456789;
    float less_precise = (float)precise;
    int no_decimal = (int)precise;
    
    printf("原始值 (double):  %.6f\n", precise);
    printf("转为 float:       %.6f (精度降低)\n", less_precise);
    printf("转为 int:         %d (丢失小数)\n\n", no_decimal);
    
    // 7. 常见的陷阱
    printf("7. 类型转换的常见陷阱:\n");
    
    // 陷阱1: 整数除法
    printf("陷阱1 - 整数除法:\n");
    int p = 5, q = 2;
    printf("错误: %d / %d = %.2f\n", p, q, (float)(p / q));  // 先除后转换，结果为2.00
    printf("正确: %d / %d = %.2f\n\n", p, q, (float)p / q);  // 先转换后除，结果为2.50
    
    // 陷阱2: 有符号和无符号比较
    printf("陷阱2 - 有符号和无符号比较:\n");
    int signed_num = -1;
    unsigned int unsigned_num = 1;
    if (signed_num < unsigned_num) {
        printf("-1 < 1 (正常比较)\n");
    } else {
        printf("-1 不小于 1 (错误！有符号数被转换为无符号数)\n");
    }
    printf("signed_num = %d, 转为 unsigned: %u\n\n", signed_num, (unsigned)signed_num);
    
    // 8. 实际应用示例
    printf("8. 实际应用 - 成绩百分比计算:\n");
    
    int total_score = 450;    // 总分
    int max_score = 500;      // 满分
    
    // 错误的做法
    float percentage1 = total_score / max_score * 100;
    printf("错误计算: %.1f%%\n", percentage1);  // 结果为0.0
    
    // 正确的做法
    float percentage2 = (float)total_score / max_score * 100;
    printf("正确计算: %.1f%%\n", percentage2);  // 结果为90.0
    
    return 0;
}

/*
 * 知识点总结：
 * 
 * 类型转换的两种方式：
 * 
 * 1. 隐式类型转换（自动转换）：
 *    - 编译器自动执行
 *    - 从低级类型向高级类型转换
 *    - 类型等级: char < short < int < long < float < double
 *    - 发生时机：
 *      a) 不同类型混合运算
 *      b) 赋值运算
 *      c) 函数参数传递
 * 
 * 2. 显式类型转换（强制转换）：
 *    - 语法: (目标类型)表达式
 *    - 程序员主动控制
 *    - 可能导致精度损失或数据溢出
 * 
 * 转换规则：
 * 1. 算术运算：
 *    - 操作数自动转换为最高级类型
 *    - char和short自动提升为int
 * 
 * 2. 赋值运算：
 *    - 右边表达式转换为左边变量类型
 *    - 可能发生截断或溢出
 * 
 * 3. 整数除法：
 *    - 两个整数相除，结果为整数
 *    - 需要浮点结果时，至少一个操作数要转换为浮点型
 * 
 * 注意事项：
 * 1. 大类型转小类型可能溢出
 * 2. 浮点转整数会丢失小数部分
 * 3. 有符号和无符号混合运算要小心
 * 4. 整数除法前要先转换类型
 * 5. double转float会损失精度
 * 
 * 最佳实践：
 * - 尽量避免隐式转换
 * - 明确使用强制类型转换
 * - 注意精度和范围
 * - 小心有符号和无符号混合
 */
