/*
 * 第三章：函数
 * 3.2 函数参数 - 值传递
 * 
 * 学习目标：
 * 1. 理解值传递的机制
 * 2. 掌握形参和实参的区别
 * 3. 了解参数传递的注意事项
 */

#include <stdio.h>

// 函数声明
void modifyValue(int x);
void swap(int a, int b);
void swapCorrect(int *a, int *b);
int calculateSum(int n);
void printArray(int arr[], int size);
double average(int arr[], int size);
void printInfo(char name[], int age, float height);

int main() {
    printf("=== 函数参数详解 ===\n\n");
    
    // 1. 值传递的基本概念
    printf("1. 值传递机制:\n");
    int num = 10;
    printf("调用前: num = %d\n", num);
    modifyValue(num);  // 传递num的值（拷贝）
    printf("调用后: num = %d (未改变)\n", num);
    printf("说明: 函数内修改的是参数的副本，不影响原变量\n\n");
    
    // 2. 形参与实参
    printf("2. 形参与实参:\n");
    int x = 5, y = 8;
    printf("实参: x = %d, y = %d\n", x, y);
    int sum = add(x, y);  // x, y 是实参
    printf("和: %d\n", sum);
    printf("实参: 调用函数时传递的实际值\n");
    printf("形参: 函数定义中的参数（接收实参的副本）\n\n");
    
    // 3. 交换变量（错误示范）
    printf("3. 交换变量 - 错误示范（值传递）:\n");
    int a = 10, b = 20;
    printf("交换前: a = %d, b = %d\n", a, b);
    swap(a, b);
    printf("交换后: a = %d, b = %d (未交换)\n", a, b);
    printf("原因: 函数内交换的是副本，不影响原变量\n\n");
    
    // 4. 交换变量（正确方法 - 使用指针）
    printf("4. 交换变量 - 正确方法（使用指针）:\n");
    int m = 10, n = 20;
    printf("交换前: m = %d, n = %d\n", m, n);
    swapCorrect(&m, &n);  // 传递地址
    printf("交换后: m = %d, n = %d (成功交换)\n", m, n);
    printf("原因: 传递地址，函数可以修改原变量\n\n");
    
    // 5. 多个参数的函数
    printf("5. 多参数函数:\n");
    int result1 = multiply(3, 4);
    printf("3 × 4 = %d\n", result1);
    
    int result2 = multiplyThree(2, 3, 4);
    printf("2 × 3 × 4 = %d\n\n", result2);
    
    // 6. 数组作为参数
    printf("6. 数组作为函数参数:\n");
    int numbers[] = {10, 20, 30, 40, 50};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    printf("数组元素: ");
    printArray(numbers, size);
    
    double avg = average(numbers, size);
    printf("平均值: %.2f\n\n", avg);
    
    // 7. 字符串（字符数组）作为参数
    printf("7. 字符串作为参数:\n");
    char name[] = "张三";
    int age = 25;
    float height = 1.75;
    
    printInfo(name, age, height);
    printf("\n");
    
    // 8. 实际应用：计算阶乘
    printf("8. 实际应用 - 计算阶乘:\n");
    for (int i = 1; i <= 5; i++) {
        printf("%d! = %d\n", i, factorial(i));
    }
    printf("\n");
    
    // 9. 实际应用：判断质数
    printf("9. 实际应用 - 判断质数:\n");
    int test_nums[] = {2, 15, 17, 20, 23, 25, 29};
    for (int i = 0; i < 7; i++) {
        if (isPrime(test_nums[i])) {
            printf("%d 是质数\n", test_nums[i]);
        } else {
            printf("%d 不是质数\n", test_nums[i]);
        }
    }
    printf("\n");
    
    // 10. 实际应用：计算幂
    printf("10. 实际应用 - 计算幂:\n");
    printf("2³ = %d\n", power(2, 3));
    printf("5² = %d\n", power(5, 2));
    printf("10⁴ = %d\n", power(10, 4));
    
    return 0;
}

// ========== 函数定义 ==========

/*
 * 演示值传递：修改参数不影响原变量
 */
void modifyValue(int x) {
    printf("函数内修改前: x = %d\n", x);
    x = 100;
    printf("函数内修改后: x = %d\n", x);
}

/*
 * 两数相加
 */
int add(int a, int b) {  // a, b 是形参
    return a + b;
}

/*
 * 交换两个数（错误方法 - 值传递）
 */
void swap(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
    printf("函数内交换后: a = %d, b = %d\n", a, b);
}

/*
 * 交换两个数（正确方法 - 指针）
 */
void swapCorrect(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/*
 * 两数相乘
 */
int multiply(int x, int y) {
    return x * y;
}

/*
 * 三数相乘
 */
int multiplyThree(int x, int y, int z) {
    return x * y * z;
}

/*
 * 打印数组元素
 * 注意：数组名作为参数时，传递的是地址
 */
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/*
 * 计算数组平均值
 */
double average(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return (double)sum / size;
}

/*
 * 打印个人信息
 */
void printInfo(char name[], int age, float height) {
    printf("姓名: %s\n", name);
    printf("年龄: %d 岁\n", age);
    printf("身高: %.2f 米\n", height);
}

/*
 * 计算阶乘
 */
int factorial(int n) {
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

/*
 * 判断是否为质数
 */
int isPrime(int n) {
    if (n < 2) {
        return 0;  // 不是质数
    }
    
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return 0;  // 不是质数
        }
    }
    
    return 1;  // 是质数
}

/*
 * 计算幂：base^exponent
 */
int power(int base, int exponent) {
    int result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

/*
 * 知识点总结：
 * 
 * 值传递机制：
 * - C语言中，所有参数都是按值传递
 * - 函数接收的是参数值的副本
 * - 修改形参不会影响实参
 * 
 * 形参 vs 实参：
 * 
 * 形参（形式参数）：
 * - 函数定义中的参数
 * - 在函数内部作为局部变量
 * - 接收实参的值（副本）
 * - 作用域仅限于函数内部
 * 
 * 实参（实际参数）：
 * - 函数调用时传递的实际值
 * - 可以是常量、变量或表达式
 * - 必须与形参类型匹配
 * 
 * 参数传递的类型：
 * 
 * 1. 传值（值传递）：
 *    void func(int x) { ... }
 *    - 传递值的副本
 *    - 不能修改原变量
 *    - 适合：不需要修改原变量时
 * 
 * 2. 传地址（通过指针）：
 *    void func(int *x) { ... }
 *    - 传递变量的地址
 *    - 可以修改原变量
 *    - 适合：需要修改原变量或传递大型数据
 * 
 * 3. 传数组：
 *    void func(int arr[], int size) { ... }
 *    - 数组名本身就是地址
 *    - 可以修改数组元素
 *    - 必须同时传递数组大小
 * 
 * 数组参数的特殊性：
 * - int arr[] 等价于 int *arr
 * - 数组名传递的是首元素地址
 * - 函数内可以修改数组元素
 * - sizeof(arr)在函数内得到的是指针大小，不是数组大小
 * - 因此需要单独传递数组大小
 * 
 * 多参数函数：
 * - 参数用逗号分隔
 * - 参数从左到右传递
 * - 每个参数都需要指定类型
 * - 建议参数不超过5个
 * 
 * 参数类型转换：
 * - 实参类型与形参类型不同时会自动转换
 * - 可能导致精度损失
 * - 建议显式转换以提高可读性
 * 
 * 注意事项：
 * 1. 实参和形参的个数、类型、顺序必须匹配
 * 2. 值传递不能修改原变量
 * 3. 数组传递时，数组大小信息会丢失
 * 4. 字符串就是字符数组
 * 5. 传递大型结构体时建议使用指针
 * 
 * 常见错误：
 * 1. 期望通过值传递修改原变量（应该用指针）
 * 2. 忘记传递数组大小
 * 3. 参数个数或类型不匹配
 * 4. 在函数内使用sizeof获取数组大小
 * 
 * 最佳实践：
 * - 只读参数使用值传递
 * - 需要修改的参数使用指针
 * - 大型数据结构使用指针或引用
 * - 数组参数总是传递大小
 * - 使用const保护不需要修改的指针参数
 * - 参数名要有意义
 * - 为参数添加注释说明
 */
