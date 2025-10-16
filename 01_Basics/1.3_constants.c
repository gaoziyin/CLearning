/*
 * 第一章：基础语法
 * 1.3 常量
 * 
 * 学习目标：
 * 1. 理解常量的概念
 * 2. 掌握定义常量的两种方法
 * 3. 学会使用const和#define
 */

#include <stdio.h>

// 使用 #define 定义符号常量（预处理器指令）
#define PI 3.14159          // 圆周率
#define MAX_SIZE 100        // 最大尺寸
#define COMPANY "ABC科技"   // 公司名称
#define YEAR 2025          // 年份

int main() {
    printf("=== 常量的使用 ===\n\n");
    
    // 1. 字面常量 - 直接在代码中写出的固定值
    printf("1. 字面常量示例：\n");
    printf("整数字面量: %d\n", 100);
    printf("浮点字面量: %f\n", 3.14);
    printf("字符字面量: %c\n", 'A');
    printf("字符串字面量: %s\n\n", "Hello");
    
    // 2. 符号常量 - 使用 #define 定义
    printf("2. 符号常量 (#define)：\n");
    printf("圆周率 PI = %.5f\n", PI);
    printf("最大尺寸 MAX_SIZE = %d\n", MAX_SIZE);
    printf("公司名称: %s\n", COMPANY);
    printf("年份: %d\n\n", YEAR);
    
    // 计算圆的面积和周长
    float radius = 5.0;
    float area = PI * radius * radius;
    float circumference = 2 * PI * radius;
    printf("半径为 %.1f 的圆：\n", radius);
    printf("面积 = %.2f\n", area);
    printf("周长 = %.2f\n\n", circumference);
    
    // 3. const 关键字定义常量
    printf("3. const 常量：\n");
    const int DAYS_IN_WEEK = 7;        // 一周的天数
    const float GRAVITY = 9.8f;         // 重力加速度
    const char GRADE_A = 'A';           // 等级A
    
    printf("一周有 %d 天\n", DAYS_IN_WEEK);
    printf("重力加速度: %.1f m/s²\n", GRAVITY);
    printf("优秀等级: %c\n\n", GRADE_A);
    
    // const 常量不能被修改
    // DAYS_IN_WEEK = 8;  // 错误！这行代码会导致编译错误
    
    // 4. 不同类型的常量
    printf("4. 不同进制的整数常量：\n");
    const int decimal = 100;      // 十进制
    const int octal = 0144;       // 八进制 (以0开头)
    const int hexadecimal = 0x64; // 十六进制 (以0x开头)
    
    printf("十进制: %d\n", decimal);
    printf("八进制 0144 = %d (十进制)\n", octal);
    printf("十六进制 0x64 = %d (十进制)\n\n", hexadecimal);
    
    // 5. 字符常量的转义序列
    printf("5. 转义字符常量：\n");
    printf("换行符: 第一行\\n第二行\n");
    printf("制表符: 列1\\t列2\\t列3\n");
    printf("反斜杠: 路径 C:\\\\Windows\\\\System32\n");
    printf("单引号: \\' 双引号: \\\"\n");
    printf("响铃符: \\a (会发出声音)\n\n");
    
    // 6. 实际应用示例：计算税后价格
    const float TAX_RATE = 0.13;  // 税率 13%
    float original_price = 100.0;
    float tax = original_price * TAX_RATE;
    float final_price = original_price + tax;
    
    printf("6. 实际应用 - 价格计算：\n");
    printf("原价: %.2f 元\n", original_price);
    printf("税率: %.0f%%\n", TAX_RATE * 100);
    printf("税额: %.2f 元\n", tax);
    printf("含税价格: %.2f 元\n", final_price);
    
    return 0;
}

/*
 * 知识点总结：
 * 
 * 常量的定义方法：
 * 1. 字面常量：直接写在代码中的值
 *    - 整数: 123
 *    - 浮点: 3.14
 *    - 字符: 'A'
 *    - 字符串: "Hello"
 * 
 * 2. #define 符号常量：
 *    - 语法: #define 名称 值
 *    - 预处理阶段替换
 *    - 不占用内存
 *    - 没有类型检查
 * 
 * 3. const 关键字：
 *    - 语法: const 类型 名称 = 值;
 *    - 有类型检查
 *    - 占用内存
 *    - 不能修改
 * 
 * #define vs const：
 * - #define: 简单文本替换，无类型，不占内存
 * - const: 有类型的只读变量，占内存，更安全
 * 
 * 转义字符：
 * \n  - 换行
 * \t  - 制表符
 * \\  - 反斜杠
 * \'  - 单引号
 * \"  - 双引号
 * \0  - 空字符
 * \a  - 响铃
 * 
 * 命名规范：
 * - 常量名通常使用大写字母
 * - 多个单词用下划线分隔
 * - 例如: MAX_SIZE, PI, TAX_RATE
 */
