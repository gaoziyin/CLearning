/*
 * 第一章：基础语法
 * 1.2 变量与数据类型
 * 
 * 学习目标：
 * 1. 掌握C语言的基本数据类型
 * 2. 学会声明和初始化变量
 * 3. 理解不同数据类型的取值范围
 */

#include <stdio.h>
#include <limits.h>  // 包含各种数据类型的限制值

int main() {
    printf("=== C语言基本数据类型 ===\n\n");
    
    // 1. 整型 (int) - 用于存储整数
    int age = 25;
    int year = 2025;
    printf("整型 (int):\n");
    printf("年龄: %d\n", age);
    printf("年份: %d\n", year);
    printf("int 范围: %d 到 %d\n\n", INT_MIN, INT_MAX);
    
    // 2. 短整型 (short) - 较小的整数
    short temperature = -15;
    printf("短整型 (short):\n");
    printf("温度: %d°C\n", temperature);
    printf("short 范围: %d 到 %d\n\n", SHRT_MIN, SHRT_MAX);
    
    // 3. 长整型 (long) - 较大的整数
    long population = 1400000000L;  // L后缀表示长整型
    printf("长整型 (long):\n");
    printf("人口数量: %ld\n", population);
    printf("long 范围: %ld 到 %ld\n\n", LONG_MIN, LONG_MAX);
    
    // 4. 无符号整型 (unsigned) - 只存储非负数
    unsigned int score = 95;
    printf("无符号整型 (unsigned int):\n");
    printf("分数: %u\n", score);
    printf("unsigned int 范围: 0 到 %u\n\n", UINT_MAX);
    
    // 5. 字符型 (char) - 存储单个字符
    char grade = 'A';
    char symbol = '$';
    printf("字符型 (char):\n");
    printf("等级: %c\n", grade);
    printf("符号: %c\n", symbol);
    printf("字符的ASCII码: %d\n\n", grade);  // 显示字符的数值
    
    // 6. 单精度浮点型 (float) - 存储小数
    float pi = 3.14159f;  // f后缀表示float
    float price = 19.99f;
    printf("单精度浮点型 (float):\n");
    printf("圆周率: %.5f\n", pi);  // .5f表示保留5位小数
    printf("价格: %.2f元\n\n", price);
    
    // 7. 双精度浮点型 (double) - 更精确的小数
    double pi_precise = 3.141592653589793;
    double distance = 384400.0;  // 地球到月球的距离(km)
    printf("双精度浮点型 (double):\n");
    printf("精确圆周率: %.15f\n", pi_precise);
    printf("地月距离: %.1f 公里\n\n", distance);
    
    // 8. 布尔型 (需要 stdbool.h，这里用int模拟)
    int is_student = 1;  // 1表示真(true)，0表示假(false)
    int is_working = 0;
    printf("布尔值 (用int表示):\n");
    printf("是学生: %d\n", is_student);
    printf("是否工作: %d\n\n", is_working);
    
    // 9. sizeof运算符 - 查看数据类型占用的字节数
    printf("=== 各数据类型占用的字节数 ===\n");
    printf("char:   %zu 字节\n", sizeof(char));
    printf("short:  %zu 字节\n", sizeof(short));
    printf("int:    %zu 字节\n", sizeof(int));
    printf("long:   %zu 字节\n", sizeof(long));
    printf("float:  %zu 字节\n", sizeof(float));
    printf("double: %zu 字节\n", sizeof(double));
    
    return 0;
}

/*
 * 知识点总结：
 * 
 * 基本数据类型：
 * - int:      整数，通常4字节
 * - short:    短整数，通常2字节
 * - long:     长整数，通常4或8字节
 * - char:     字符，1字节
 * - float:    单精度浮点数，4字节
 * - double:   双精度浮点数，8字节
 * - unsigned: 无符号修饰符，只存储非负数
 * 
 * 格式说明符：
 * %d  - int
 * %ld - long
 * %u  - unsigned int
 * %c  - char
 * %f  - float/double
 * %lf - double (scanf中使用)
 * %zu - size_t
 * 
 * 练习建议：
 * 1. 尝试声明不同类型的变量
 * 2. 使用printf输出变量的值
 * 3. 观察不同格式说明符的输出效果
 */
