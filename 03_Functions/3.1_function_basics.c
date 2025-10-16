/*
 * 第三章：函数
 * 3.1 函数定义与调用
 * 
 * 学习目标：
 * 1. 理解函数的概念和作用
 * 2. 掌握函数的定义和调用
 * 3. 学会函数的声明和原型
 */

#include <stdio.h>

// 函数声明（函数原型）
// 告诉编译器函数的存在，可以在main之前声明，在main之后定义
void greet(void);
int add(int a, int b);
void printLine(void);
int square(int num);
double calculateArea(double radius);

int main() {
    printf("=== 函数基础 ===\n\n");
    
    // 1. 调用无参数无返回值的函数
    printf("1. 调用无参数无返回值的函数:\n");
    greet();  // 调用函数
    printLine();
    printf("\n");
    
    // 2. 调用有参数有返回值的函数
    printf("2. 调用有参数有返回值的函数:\n");
    int x = 5, y = 3;
    int sum = add(x, y);  // 调用函数并接收返回值
    printf("%d + %d = %d\n", x, y, sum);
    printLine();
    printf("\n");
    
    // 3. 函数可以多次调用
    printf("3. 函数可以被多次调用:\n");
    printf("3的平方: %d\n", square(3));
    printf("5的平方: %d\n", square(5));
    printf("10的平方: %d\n", square(10));
    printLine();
    printf("\n");
    
    // 4. 函数调用可以嵌套
    printf("4. 函数调用的嵌套:\n");
    int result = add(square(2), square(3));  // 2² + 3² = 4 + 9 = 13
    printf("2² + 3² = %d\n", result);
    printLine();
    printf("\n");
    
    // 5. 函数返回值可以直接用于表达式
    printf("5. 返回值用于表达式:\n");
    int total = add(10, 20) + add(5, 15);
    printf("(10 + 20) + (5 + 15) = %d\n", total);
    printLine();
    printf("\n");
    
    // 6. 浮点数函数
    printf("6. 浮点数函数示例:\n");
    double radius = 5.0;
    double area = calculateArea(radius);
    printf("半径为 %.1f 的圆面积: %.2f\n", radius, area);
    printLine();
    printf("\n");
    
    // 7. 实际应用：计算多个数的最大值
    printf("7. 实际应用 - 找最大值:\n");
    int num1 = 25, num2 = 48, num3 = 36;
    int max = findMax(num1, num2, num3);
    printf("%d, %d, %d 中的最大值: %d\n", num1, num2, num3, max);
    printLine();
    printf("\n");
    
    // 8. 实际应用：温度转换
    printf("8. 实际应用 - 温度转换:\n");
    double celsius = 25.0;
    double fahrenheit = celsiusToFahrenheit(celsius);
    printf("%.1f°C = %.1f°F\n", celsius, fahrenheit);
    
    double f = 77.0;
    double c = fahrenheitToCelsius(f);
    printf("%.1f°F = %.1f°C\n", f, c);
    
    return 0;
}

// ========== 函数定义 ==========

/*
 * 函数名: greet
 * 功能: 打印问候语
 * 参数: 无
 * 返回值: 无
 */
void greet(void) {
    printf("你好！欢迎学习C语言函数！\n");
}

/*
 * 函数名: printLine
 * 功能: 打印分隔线
 * 参数: 无
 * 返回值: 无
 */
void printLine(void) {
    printf("--------------------------------\n");
}

/*
 * 函数名: add
 * 功能: 计算两个整数的和
 * 参数: a - 第一个整数, b - 第二个整数
 * 返回值: 两数之和
 */
int add(int a, int b) {
    int result = a + b;
    return result;  // 返回计算结果
}

/*
 * 函数名: square
 * 功能: 计算一个数的平方
 * 参数: num - 要计算平方的数
 * 返回值: num的平方
 */
int square(int num) {
    return num * num;
}

/*
 * 函数名: calculateArea
 * 功能: 计算圆的面积
 * 参数: radius - 圆的半径
 * 返回值: 圆的面积
 */
double calculateArea(double radius) {
    const double PI = 3.14159;
    return PI * radius * radius;
}

/*
 * 函数名: findMax
 * 功能: 找出三个数中的最大值
 * 参数: a, b, c - 三个整数
 * 返回值: 最大值
 */
int findMax(int a, int b, int c) {
    int max = a;
    
    if (b > max) {
        max = b;
    }
    
    if (c > max) {
        max = c;
    }
    
    return max;
}

/*
 * 函数名: celsiusToFahrenheit
 * 功能: 摄氏度转华氏度
 * 参数: celsius - 摄氏温度
 * 返回值: 华氏温度
 * 公式: F = C × 9/5 + 32
 */
double celsiusToFahrenheit(double celsius) {
    return celsius * 9.0 / 5.0 + 32.0;
}

/*
 * 函数名: fahrenheitToCelsius
 * 功能: 华氏度转摄氏度
 * 参数: fahrenheit - 华氏温度
 * 返回值: 摄氏温度
 * 公式: C = (F - 32) × 5/9
 */
double fahrenheitToCelsius(double fahrenheit) {
    return (fahrenheit - 32.0) * 5.0 / 9.0;
}

/*
 * 知识点总结：
 * 
 * 函数的概念：
 * - 函数是完成特定任务的代码块
 * - 可以重复调用，提高代码复用性
 * - 使程序结构更清晰，易于维护
 * 
 * 函数的组成部分：
 * 返回类型 函数名(参数列表) {
 *     函数体;
 *     return 返回值;  // 如果返回类型不是void
 * }
 * 
 * 函数的类型：
 * 1. 无参数无返回值：void func(void)
 * 2. 无参数有返回值：int func(void)
 * 3. 有参数无返回值：void func(int a)
 * 4. 有参数有返回值：int func(int a, int b)
 * 
 * 函数声明 vs 函数定义：
 * - 声明（原型）：告诉编译器函数的存在
 *   int add(int a, int b);  // 分号结尾
 * 
 * - 定义：函数的具体实现
 *   int add(int a, int b) {
 *       return a + b;
 *   }
 * 
 * 函数调用：
 * - 语法：函数名(实参列表);
 * - 实参：实际传递给函数的值
 * - 返回值可以赋值给变量或用于表达式
 * 
 * return语句：
 * - 作用：
 *   1. 返回一个值给调用者
 *   2. 终止函数执行
 * - void函数可以用 return; 提前退出
 * - 非void函数必须返回匹配类型的值
 * 
 * 函数的优点：
 * 1. 代码复用：避免重复编写相同代码
 * 2. 模块化：将大问题分解为小问题
 * 3. 易于测试：可以单独测试每个函数
 * 4. 易于维护：修改功能只需修改一个函数
 * 5. 提高可读性：函数名可以表达代码意图
 * 
 * 函数命名规范：
 * - 使用有意义的名称
 * - 动词开头：calculate, get, set, print, check
 * - 驼峰命名法：calculateArea, getUserName
 * - 或下划线分隔：calculate_area, get_user_name
 * 
 * 注意事项：
 * 1. 函数声明要在调用之前
 * 2. 返回类型和return的值类型要匹配
 * 3. 参数个数和类型要匹配
 * 4. void函数不能有返回值
 * 5. 函数不能嵌套定义（C语言不支持）
 * 
 * 最佳实践：
 * - 函数功能要单一，只做一件事
 * - 函数不要太长（建议不超过50行）
 * - 参数不要太多（建议不超过5个）
 * - 为函数添加注释说明功能、参数、返回值
 * - 使用有意义的参数名
 */
