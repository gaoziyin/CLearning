/*
 * 第一章：基础语法
 * 1.4 运算符
 * 
 * 学习目标：
 * 1. 掌握算术运算符的使用
 * 2. 理解关系运算符和逻辑运算符
 * 3. 学会使用赋值运算符和自增自减运算符
 */

#include <stdio.h>

int main() {
    printf("=== C语言运算符详解 ===\n\n");
    
    // 1. 算术运算符
    printf("1. 算术运算符 (+, -, *, /, %%):\n");
    int a = 10, b = 3;
    printf("a = %d, b = %d\n", a, b);
    printf("加法: %d + %d = %d\n", a, b, a + b);
    printf("减法: %d - %d = %d\n", a, b, a - b);
    printf("乘法: %d * %d = %d\n", a, b, a * b);
    printf("除法: %d / %d = %d\n", a, b, a / b);  // 整数除法，结果为3
    printf("取模: %d %% %d = %d\n\n", a, b, a % b);  // 余数为1
    
    // 浮点数除法
    float x = 10.0, y = 3.0;
    printf("浮点除法: %.1f / %.1f = %.2f\n\n", x, y, x / y);
    
    // 2. 关系运算符（比较运算符）
    printf("2. 关系运算符 (==, !=, >, <, >=, <=):\n");
    int m = 5, n = 8;
    printf("m = %d, n = %d\n", m, n);
    printf("m == n : %d (相等)\n", m == n);      // 0 (假)
    printf("m != n : %d (不等)\n", m != n);      // 1 (真)
    printf("m > n  : %d (大于)\n", m > n);       // 0 (假)
    printf("m < n  : %d (小于)\n", m < n);       // 1 (真)
    printf("m >= n : %d (大于等于)\n", m >= n);  // 0 (假)
    printf("m <= n : %d (小于等于)\n\n", m <= n);// 1 (真)
    
    // 3. 逻辑运算符
    printf("3. 逻辑运算符 (&&, ||, !):\n");
    int p = 1;  // 真
    int q = 0;  // 假
    printf("p = %d (真), q = %d (假)\n", p, q);
    printf("p && q : %d (逻辑与 AND)\n", p && q);  // 0 (两个都为真时才为真)
    printf("p || q : %d (逻辑或 OR)\n", p || q);   // 1 (有一个为真就为真)
    printf("!p     : %d (逻辑非 NOT)\n", !p);      // 0 (取反)
    printf("!q     : %d (逻辑非 NOT)\n\n", !q);    // 1 (取反)
    
    // 4. 赋值运算符
    printf("4. 赋值运算符 (=, +=, -=, *=, /=, %%):\n");
    int num = 10;
    printf("初始值 num = %d\n", num);
    
    num += 5;  // 等价于 num = num + 5
    printf("num += 5  -> num = %d\n", num);
    
    num -= 3;  // 等价于 num = num - 3
    printf("num -= 3  -> num = %d\n", num);
    
    num *= 2;  // 等价于 num = num * 2
    printf("num *= 2  -> num = %d\n", num);
    
    num /= 4;  // 等价于 num = num / 4
    printf("num /= 4  -> num = %d\n", num);
    
    num %= 3;  // 等价于 num = num % 3
    printf("num %%= 3  -> num = %d\n\n", num);
    
    // 5. 自增和自减运算符
    printf("5. 自增/自减运算符 (++, --):\n");
    int count = 5;
    printf("初始值 count = %d\n", count);
    
    printf("count++ (后缀): 返回 %d, ", count++);  // 先使用，后加1
    printf("count现在是 %d\n", count);
    
    printf("++count (前缀): 返回 %d, ", ++count);  // 先加1，后使用
    printf("count现在是 %d\n", count);
    
    printf("count-- (后缀): 返回 %d, ", count--);  // 先使用，后减1
    printf("count现在是 %d\n", count);
    
    printf("--count (前缀): 返回 %d, ", --count);  // 先减1，后使用
    printf("count现在是 %d\n\n", count);
    
    // 6. 条件运算符（三元运算符）
    printf("6. 条件运算符 (? :):\n");
    int score = 85;
    char *result = (score >= 60) ? "及格" : "不及格";
    printf("分数: %d, 结果: %s\n", score, result);
    
    int max = (a > b) ? a : b;  // 找出较大值
    printf("%d 和 %d 中的较大值是: %d\n\n", a, b, max);
    
    // 7. sizeof 运算符
    printf("7. sizeof 运算符:\n");
    int var = 100;
    printf("int类型的大小: %zu 字节\n", sizeof(int));
    printf("变量var的大小: %zu 字节\n", sizeof(var));
    printf("表达式的大小: %zu 字节\n\n", sizeof(a + b));
    
    // 8. 逗号运算符
    printf("8. 逗号运算符:\n");
    int i, j, k;
    k = (i = 3, j = 5, i + j);  // 从左到右执行，返回最后一个表达式的值
    printf("i = %d, j = %d, k = %d\n\n", i, j, k);
    
    // 9. 运算符优先级示例
    printf("9. 运算符优先级:\n");
    int result1 = 2 + 3 * 4;        // 乘法优先于加法
    int result2 = (2 + 3) * 4;      // 括号优先级最高
    printf("2 + 3 * 4 = %d\n", result1);
    printf("(2 + 3) * 4 = %d\n", result2);
    
    // 复杂表达式
    int result3 = 10 > 5 && 20 < 30;  // 关系运算优先于逻辑运算
    printf("10 > 5 && 20 < 30 = %d\n\n", result3);
    
    // 10. 实际应用：计算器示例
    printf("10. 实际应用 - 简单计算器:\n");
    float num1 = 15.5, num2 = 4.2;
    printf("数字1: %.1f\n", num1);
    printf("数字2: %.1f\n", num2);
    printf("相加: %.1f + %.1f = %.2f\n", num1, num2, num1 + num2);
    printf("相减: %.1f - %.1f = %.2f\n", num1, num2, num1 - num2);
    printf("相乘: %.1f * %.1f = %.2f\n", num1, num2, num1 * num2);
    printf("相除: %.1f / %.1f = %.2f\n", num1, num2, num1 / num2);
    
    return 0;
}

/*
 * 知识点总结：
 * 
 * 运算符分类：
 * 
 * 1. 算术运算符：
 *    +    加法
 *    -    减法
 *    *    乘法
 *    /    除法
 *    %    取模（求余数）
 * 
 * 2. 关系运算符：
 *    ==   等于
 *    !=   不等于
 *    >    大于
 *    <    小于
 *    >=   大于等于
 *    <=   小于等于
 * 
 * 3. 逻辑运算符：
 *    &&   逻辑与（AND）
 *    ||   逻辑或（OR）
 *    !    逻辑非（NOT）
 * 
 * 4. 赋值运算符：
 *    =    简单赋值
 *    +=   加后赋值
 *    -=   减后赋值
 *    *=   乘后赋值
 *    /=   除后赋值
 *    %=   取模后赋值
 * 
 * 5. 自增/自减运算符：
 *    ++   自增（加1）
 *    --   自减（减1）
 *    前缀：先运算后使用
 *    后缀：先使用后运算
 * 
 * 6. 其他运算符：
 *    ?:   条件运算符（三元）
 *    sizeof  求字节数
 *    ,    逗号运算符
 * 
 * 运算符优先级（从高到低）：
 * 1. ()  括号
 * 2. ++ -- ! sizeof  一元运算符
 * 3. * / %  乘除模
 * 4. + -  加减
 * 5. < <= > >=  关系运算符
 * 6. == !=  相等运算符
 * 7. &&  逻辑与
 * 8. ||  逻辑或
 * 9. ?:  条件运算符
 * 10. = += -= *= /= %=  赋值运算符
 * 11. ,  逗号运算符
 */
