/*
 * 第二章：控制流程
 * 2.1 if语句 - 条件判断
 * 
 * 学习目标：
 * 1. 掌握if语句的基本语法
 * 2. 学会使用if-else和if-else if-else
 * 3. 理解嵌套if语句
 */

#include <stdio.h>

int main() {
    printf("=== if条件语句详解 ===\n\n");
    
    // 1. 简单if语句
    printf("1. 简单if语句:\n");
    int age = 18;
    
    if (age >= 18) {
        printf("你已经成年了\n");
    }
    
    if (age < 18) {
        printf("你还未成年\n");
    }
    printf("\n");
    
    // 2. if-else语句
    printf("2. if-else语句:\n");
    int score = 75;
    
    if (score >= 60) {
        printf("分数 %d: 及格\n", score);
    } else {
        printf("分数 %d: 不及格\n", score);
    }
    printf("\n");
    
    // 3. if-else if-else多分支语句
    printf("3. if-else if-else多分支:\n");
    int grade = 85;
    
    if (grade >= 90) {
        printf("成绩 %d: 优秀 (A)\n", grade);
    } else if (grade >= 80) {
        printf("成绩 %d: 良好 (B)\n", grade);
    } else if (grade >= 70) {
        printf("成绩 %d: 中等 (C)\n", grade);
    } else if (grade >= 60) {
        printf("成绩 %d: 及格 (D)\n", grade);
    } else {
        printf("成绩 %d: 不及格 (F)\n", grade);
    }
    printf("\n");
    
    // 4. 嵌套if语句
    printf("4. 嵌套if语句:\n");
    int user_age = 20;
    int has_license = 1;  // 1表示有驾照
    
    if (user_age >= 18) {
        printf("年龄符合要求\n");
        if (has_license) {
            printf("有驾照，可以驾驶\n");
        } else {
            printf("没有驾照，不能驾驶\n");
        }
    } else {
        printf("年龄不足18岁，不能考驾照\n");
    }
    printf("\n");
    
    // 5. 逻辑运算符与if语句
    printf("5. 使用逻辑运算符:\n");
    int temperature = 25;
    int is_sunny = 1;
    
    // 逻辑与 &&
    if (temperature > 20 && is_sunny) {
        printf("温度 %d°C，天气晴朗，适合出游\n", temperature);
    }
    
    // 逻辑或 ||
    int is_weekend = 0;
    int is_holiday = 1;
    
    if (is_weekend || is_holiday) {
        printf("今天是休息日\n");
    }
    
    // 逻辑非 !
    int is_raining = 0;
    
    if (!is_raining) {
        printf("没有下雨，可以出门\n");
    }
    printf("\n");
    
    // 6. 条件表达式的值
    printf("6. 条件表达式的真假:\n");
    int a = 10, b = 20;
    
    printf("a = %d, b = %d\n", a, b);
    printf("a == b 的值: %d\n", a == b);  // 0 (假)
    printf("a != b 的值: %d\n", a != b);  // 1 (真)
    printf("a < b 的值: %d\n", a < b);    // 1 (真)
    
    // 在C语言中，0为假，非0为真
    if (5) {
        printf("非零值 5 被视为真\n");
    }
    
    if (0) {
        printf("这句不会执行\n");
    } else {
        printf("0 被视为假\n");
    }
    printf("\n");
    
    // 7. 实际应用：判断闰年
    printf("7. 实际应用 - 判断闰年:\n");
    int year = 2024;
    
    // 闰年条件：能被4整除但不能被100整除，或者能被400整除
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        printf("%d 年是闰年\n", year);
    } else {
        printf("%d 年不是闰年\n", year);
    }
    printf("\n");
    
    // 8. 实际应用：判断三角形类型
    printf("8. 实际应用 - 判断三角形类型:\n");
    int side1 = 3, side2 = 4, side3 = 5;
    
    // 首先判断能否构成三角形
    if (side1 + side2 > side3 && side1 + side3 > side2 && side2 + side3 > side1) {
        printf("边长 %d, %d, %d 可以构成三角形\n", side1, side2, side3);
        
        // 判断三角形类型
        if (side1 == side2 && side2 == side3) {
            printf("这是等边三角形\n");
        } else if (side1 == side2 || side2 == side3 || side1 == side3) {
            printf("这是等腰三角形\n");
        } else {
            printf("这是不等边三角形\n");
        }
        
        // 判断是否为直角三角形
        if (side1*side1 + side2*side2 == side3*side3 ||
            side1*side1 + side3*side3 == side2*side2 ||
            side2*side2 + side3*side3 == side1*side1) {
            printf("这是直角三角形\n");
        }
    } else {
        printf("边长 %d, %d, %d 不能构成三角形\n", side1, side2, side3);
    }
    printf("\n");
    
    // 9. 实际应用：计算个人所得税
    printf("9. 实际应用 - 简化版个人所得税计算:\n");
    float income = 15000;  // 月收入
    float tax = 0;
    float taxable_income = income - 5000;  // 扣除起征点
    
    if (taxable_income <= 0) {
        tax = 0;
    } else if (taxable_income <= 3000) {
        tax = taxable_income * 0.03;
    } else if (taxable_income <= 12000) {
        tax = 3000 * 0.03 + (taxable_income - 3000) * 0.10;
    } else if (taxable_income <= 25000) {
        tax = 3000 * 0.03 + 9000 * 0.10 + (taxable_income - 12000) * 0.20;
    } else {
        tax = 3000 * 0.03 + 9000 * 0.10 + 13000 * 0.20 + (taxable_income - 25000) * 0.25;
    }
    
    printf("月收入: %.2f 元\n", income);
    printf("应纳税所得额: %.2f 元\n", taxable_income);
    printf("应缴个税: %.2f 元\n", tax);
    printf("税后收入: %.2f 元\n", income - tax);
    
    return 0;
}

/*
 * 知识点总结：
 * 
 * if语句的语法：
 * 
 * 1. 简单if语句：
 *    if (条件) {
 *        语句块;
 *    }
 * 
 * 2. if-else语句：
 *    if (条件) {
 *        语句块1;
 *    } else {
 *        语句块2;
 *    }
 * 
 * 3. if-else if-else语句：
 *    if (条件1) {
 *        语句块1;
 *    } else if (条件2) {
 *        语句块2;
 *    } else if (条件3) {
 *        语句块3;
 *    } else {
 *        语句块4;
 *    }
 * 
 * 4. 嵌套if语句：
 *    if (条件1) {
 *        if (条件2) {
 *            语句块;
 *        }
 *    }
 * 
 * 条件表达式：
 * - 关系运算符: ==, !=, >, <, >=, <=
 * - 逻辑运算符: && (与), || (或), ! (非)
 * - 值: 0为假，非0为真
 * 
 * 注意事项：
 * 1. 条件必须用括号括起来
 * 2. 使用 == 比较相等，不是 =
 * 3. 多个条件可以用 && 或 || 连接
 * 4. 代码块建议使用花括号，即使只有一条语句
 * 5. else if 和 else 是可选的
 * 
 * 最佳实践：
 * - 始终使用花括号，增强可读性
 * - 避免过深的嵌套，可以用 else if 代替
 * - 复杂条件可以先用变量存储
 * - 注意运算符优先级，必要时使用括号
 */
