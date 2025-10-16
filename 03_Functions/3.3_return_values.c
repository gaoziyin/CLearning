/*
 * 第三章：函数
 * 3.3 函数返回值
 * 
 * 学习目标：
 * 1. 掌握return语句的使用
 * 2. 理解不同类型的返回值
 * 3. 学会处理多返回值的情况
 */

#include <stdio.h>

// 函数声明
int getMax(int a, int b);
double divide(int a, int b, int *success);
void getMinMax(int arr[], int size, int *min, int *max);
char getGrade(int score);
int* findElement(int arr[], int size, int target);
void calculateCircle(double radius, double *area, double *circumference);

int main() {
    printf("=== 函数返回值详解 ===\n\n");
    
    // 1. 基本返回值
    printf("1. 基本返回值:\n");
    int max = getMax(10, 25);
    printf("10 和 25 的最大值: %d\n\n", max);
    
    // 2. void函数（无返回值）
    printf("2. void函数（无返回值）:\n");
    printMessage("这是一条消息");
    printf("void函数不返回值，用于执行操作\n\n");
    
    // 3. 返回不同类型的值
    printf("3. 不同类型的返回值:\n");
    int int_result = getIntValue();
    double double_result = getDoubleValue();
    char char_result = getCharValue();
    
    printf("整数返回值: %d\n", int_result);
    printf("浮点返回值: %.2f\n", double_result);
    printf("字符返回值: %c\n\n", char_result);
    
    // 4. 返回值用于条件判断
    printf("4. 返回值用于条件判断:\n");
    int num = 17;
    if (isPrime(num)) {
        printf("%d 是质数\n", num);
    } else {
        printf("%d 不是质数\n", num);
    }
    printf("\n");
    
    // 5. 多个return语句
    printf("5. 多个return语句:\n");
    printf("5的绝对值: %d\n", absoluteValue(5));
    printf("-5的绝对值: %d\n", absoluteValue(-5));
    printf("0的绝对值: %d\n\n", absoluteValue(0));
    
    // 6. 返回值表示成功/失败
    printf("6. 返回值表示操作状态:\n");
    int success;
    double result = divide(10, 2, &success);
    if (success) {
        printf("10 / 2 = %.2f\n", result);
    } else {
        printf("除法失败\n");
    }
    
    result = divide(10, 0, &success);
    if (success) {
        printf("10 / 0 = %.2f\n", result);
    } else {
        printf("除法失败（除数为0）\n");
    }
    printf("\n");
    
    // 7. 通过指针参数返回多个值
    printf("7. 通过指针返回多个值:\n");
    int numbers[] = {15, 3, 42, 8, 27, 19, 5};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int min, max;
    
    getMinMax(numbers, size, &min, &max);
    printf("数组: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    printf("最小值: %d\n", min);
    printf("最大值: %d\n\n", max);
    
    // 8. 返回字符
    printf("8. 返回字符类型:\n");
    int scores[] = {95, 82, 76, 58, 91};
    printf("分数转等级:\n");
    for (int i = 0; i < 5; i++) {
        printf("分数 %d -> 等级 %c\n", scores[i], getGrade(scores[i]));
    }
    printf("\n");
    
    // 9. 提前返回（优化代码结构）
    printf("9. 提前返回优化代码:\n");
    printf("计算1到10的和（偶数）: %d\n", sumEvenNumbers(10));
    printf("计算1到10的和（奇数）: %d\n\n", sumOddNumbers(10));
    
    // 10. 实际应用：计算圆的属性
    printf("10. 实际应用 - 通过指针返回多个值:\n");
    double radius = 5.0;
    double area, circumference;
    
    calculateCircle(radius, &area, &circumference);
    printf("半径: %.1f\n", radius);
    printf("面积: %.2f\n", area);
    printf("周长: %.2f\n\n", circumference);
    
    // 11. 返回值的链式调用
    printf("11. 返回值的链式使用:\n");
    int a = 5, b = 10, c = 15;
    int max_of_three = getMax(getMax(a, b), c);
    printf("%d, %d, %d 的最大值: %d\n\n", a, b, c, max_of_three);
    
    // 12. 实际应用：字符串长度
    printf("12. 实际应用 - 计算字符串长度:\n");
    char str1[] = "Hello";
    char str2[] = "C Programming";
    printf("\"%s\" 的长度: %d\n", str1, stringLength(str1));
    printf("\"%s\" 的长度: %d\n", str2, stringLength(str2));
    
    return 0;
}

// ========== 函数定义 ==========

/*
 * 返回两个数中的最大值
 */
int getMax(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

/*
 * 打印消息（无返回值）
 */
void printMessage(char message[]) {
    printf("消息: %s\n", message);
}

/*
 * 返回整数值
 */
int getIntValue(void) {
    return 42;
}

/*
 * 返回浮点值
 */
double getDoubleValue(void) {
    return 3.14159;
}

/*
 * 返回字符值
 */
char getCharValue(void) {
    return 'A';
}

/*
 * 判断质数（返回布尔值：1为真，0为假）
 */
int isPrime(int n) {
    if (n < 2) {
        return 0;
    }
    
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    
    return 1;
}

/*
 * 计算绝对值（多个return语句）
 */
int absoluteValue(int x) {
    if (x < 0) {
        return -x;  // 负数返回其相反数
    }
    return x;  // 非负数直接返回
}

/*
 * 除法运算，通过指针返回成功状态
 */
double divide(int a, int b, int *success) {
    if (b == 0) {
        *success = 0;  // 失败
        return 0.0;
    }
    
    *success = 1;  // 成功
    return (double)a / b;
}

/*
 * 通过指针返回数组的最小值和最大值
 */
void getMinMax(int arr[], int size, int *min, int *max) {
    *min = arr[0];
    *max = arr[0];
    
    for (int i = 1; i < size; i++) {
        if (arr[i] < *min) {
            *min = arr[i];
        }
        if (arr[i] > *max) {
            *max = arr[i];
        }
    }
}

/*
 * 根据分数返回等级
 */
char getGrade(int score) {
    if (score >= 90) {
        return 'A';
    } else if (score >= 80) {
        return 'B';
    } else if (score >= 70) {
        return 'C';
    } else if (score >= 60) {
        return 'D';
    } else {
        return 'F';
    }
}

/*
 * 计算1到n之间偶数的和
 */
int sumEvenNumbers(int n) {
    int sum = 0;
    for (int i = 2; i <= n; i += 2) {
        sum += i;
    }
    return sum;
}

/*
 * 计算1到n之间奇数的和
 */
int sumOddNumbers(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i += 2) {
        sum += i;
    }
    return sum;
}

/*
 * 计算圆的面积和周长（通过指针返回两个值）
 */
void calculateCircle(double radius, double *area, double *circumference) {
    const double PI = 3.14159265359;
    *area = PI * radius * radius;
    *circumference = 2 * PI * radius;
}

/*
 * 计算字符串长度
 */
int stringLength(char str[]) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

/*
 * 知识点总结：
 * 
 * return语句的作用：
 * 1. 返回一个值给调用者
 * 2. 立即终止函数执行
 * 3. 将控制权返回给调用者
 * 
 * return语句的语法：
 * - return;          // void函数，不返回值
 * - return 表达式;   // 返回表达式的值
 * 
 * 返回值类型：
 * - 必须与函数声明的返回类型匹配
 * - 可以是任何基本数据类型
 * - 可以是指针类型
 * - 不能直接返回数组（但可以返回指针）
 * 
 * void函数：
 * - 不返回任何值
 * - 用于执行操作（如打印、修改全局变量）
 * - 可以使用 return; 提前退出
 * - 调用时不需要接收返回值
 * 
 * 多个return语句：
 * - 函数可以有多个return语句
 * - 但只有一个会被执行
 * - 常用于不同条件下返回不同值
 * - 提前返回可以简化代码结构
 * 
 * 返回值的使用：
 * 1. 赋值给变量：int x = func();
 * 2. 直接使用：printf("%d", func());
 * 3. 用于表达式：int sum = func1() + func2();
 * 4. 用于条件判断：if (func()) { ... }
 * 5. 链式调用：func1(func2());
 * 
 * 返回值表示状态：
 * - 常见约定：
 *   0 表示成功
 *   非0 表示错误码
 * - 或：
 *   1 表示真/成功
 *   0 表示假/失败
 * 
 * 多返回值的处理：
 * 
 * C语言不直接支持多返回值，但有以下方法：
 * 
 * 1. 使用指针参数：
 *    void func(int *result1, int *result2) {
 *        *result1 = value1;
 *        *result2 = value2;
 *    }
 * 
 * 2. 使用结构体：
 *    struct Result {
 *        int value1;
 *        int value2;
 *    };
 *    struct Result func() { ... }
 * 
 * 3. 使用全局变量（不推荐）
 * 
 * 返回指针的注意事项：
 * - 不要返回局部变量的地址
 * - 可以返回动态分配的内存地址
 * - 可以返回传入的指针参数
 * - 可以返回全局变量地址
 * - 可以返回静态局部变量地址
 * 
 * 注意事项：
 * 1. 返回类型必须匹配
 * 2. 非void函数必须有return语句
 * 3. return后的代码不会执行
 * 4. 不要返回局部变量的地址
 * 5. 返回值可能被忽略
 * 
 * 常见错误：
 * 1. 返回类型与声明不匹配
 * 2. 忘记return语句
 * 3. 返回局部变量的地址
 * 4. void函数返回值
 * 5. 没有处理所有路径的返回
 * 
 * 最佳实践：
 * - 函数应该只有一个职责
 * - 返回值要有明确含义
 * - 使用有意义的返回值
 * - 为返回值添加注释
 * - 错误情况要有明确的返回值
 * - 考虑使用枚举表示状态码
 * - 保持返回值类型一致性
 * - 函数开头检查参数有效性，无效时提前返回
 */
