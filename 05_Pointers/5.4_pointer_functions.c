/*
 * 第五章：指针
 * 5.4 指针与函数
 * 
 * 学习目标：
 * 1. 掌握指针作为函数参数
 * 2. 理解传值与传址的区别
 * 3. 学会函数返回指针
 * 4. 了解函数指针的基本用法
 */

#include <stdio.h>
#include <string.h>

// 函数声明

// 1. 传值调用
void swapByValue(int a, int b);

// 2. 传址调用（指针参数）
void swapByPointer(int *a, int *b);

// 3. 数组参数（本质是指针）
int sumArray(int *arr, int size);
void printArray(int arr[], int size);

// 4. 修改数组元素
void doubleValues(int *arr, int size);

// 5. 字符串参数
int stringLength(const char *str);
void toUpperCase(char *str);
void stringCopy(char *dest, const char *src);

// 6. 多个返回值（通过指针）
void getDimensions(int *width, int *height);
void divMod(int a, int b, int *quotient, int *remainder);

// 7. 返回指针
int* findMax(int *arr, int size);
char* findChar(char *str, char ch);

// 8. 返回静态变量指针
int* getStaticArray(void);

// 9. const 指针参数
void displayValue(const int *ptr);
int sumNumbers(const int *arr, int size);

// 10. 函数指针基础
int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);

int main() {
    printf("=== 指针与函数 ===\n\n");
    
    // 1. 传值 vs 传址
    printf("1. 传值调用 vs 传址调用:\n");
    int x = 10, y = 20;
    
    printf("交换前: x = %d, y = %d\n", x, y);
    swapByValue(x, y);
    printf("传值调用后: x = %d, y = %d (未改变)\n", x, y);
    
    swapByPointer(&x, &y);
    printf("传址调用后: x = %d, y = %d (已交换)\n\n", x, y);
    
    // 2. 数组作为参数
    printf("2. 数组参数:\n");
    int numbers[] = {5, 10, 15, 20, 25};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    printf("数组: ");
    printArray(numbers, size);
    
    int sum = sumArray(numbers, size);
    printf("数组和: %d\n\n", sum);
    
    // 3. 修改数组
    printf("3. 通过指针修改数组:\n");
    int data[] = {1, 2, 3, 4, 5};
    int len = sizeof(data) / sizeof(data[0]);
    
    printf("修改前: ");
    printArray(data, len);
    
    doubleValues(data, len);
    printf("每个值翻倍后: ");
    printArray(data, len);
    printf("\n");
    
    // 4. 字符串参数
    printf("4. 字符串参数:\n");
    char message[] = "hello world";
    
    printf("原字符串: %s\n", message);
    printf("长度: %d\n", stringLength(message));
    
    toUpperCase(message);
    printf("转大写后: %s\n\n", message);
    
    // 5. 字符串复制
    printf("5. 字符串复制函数:\n");
    char source[] = "Copy me!";
    char destination[50];
    
    stringCopy(destination, source);
    printf("源: %s\n", source);
    printf("目标: %s\n\n", destination);
    
    // 6. 多个返回值
    printf("6. 通过指针返回多个值:\n");
    int width, height;
    getDimensions(&width, &height);
    printf("宽度: %d, 高度: %d\n", width, height);
    
    int quot, rem;
    divMod(17, 5, &quot, &rem);
    printf("17 ÷ 5 = %d 余 %d\n\n", quot, rem);
    
    // 7. 返回指针
    printf("7. 函数返回指针:\n");
    int scores[] = {85, 92, 78, 95, 88};
    int score_size = sizeof(scores) / sizeof(scores[0]);
    
    int *max_ptr = findMax(scores, score_size);
    if (max_ptr != NULL) {
        printf("最大值: %d\n", *max_ptr);
        printf("位置: %ld\n\n", max_ptr - scores);
    }
    
    // 8. 在字符串中查找字符
    printf("8. 查找字符返回指针:\n");
    char text[] = "Hello World";
    char search_ch = 'W';
    
    char *found = findChar(text, search_ch);
    if (found != NULL) {
        printf("在 '%s' 中找到 '%c'\n", text, search_ch);
        printf("从该位置开始: %s\n\n", found);
    }
    
    // 9. 返回静态数组
    printf("9. 返回静态变量指针:\n");
    int *static_arr = getStaticArray();
    printf("静态数组: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", static_arr[i]);
    }
    printf("\n\n");
    
    // 10. const 保护参数
    printf("10. const 保护指针参数:\n");
    int value = 100;
    displayValue(&value);
    
    int nums[] = {10, 20, 30, 40};
    int nums_size = sizeof(nums) / sizeof(nums[0]);
    printf("数组和: %d\n\n", sumNumbers(nums, nums_size));
    
    // 11. 函数指针
    printf("11. 函数指针:\n");
    int a = 10, b = 5;
    
    // 声明函数指针
    int (*operation)(int, int);
    
    // 指向加法函数
    operation = add;
    printf("%d + %d = %d\n", a, b, operation(a, b));
    
    // 指向减法函数
    operation = subtract;
    printf("%d - %d = %d\n", a, b, operation(a, b));
    
    // 指向乘法函数
    operation = multiply;
    printf("%d × %d = %d\n\n", a, b, operation(a, b));
    
    // 12. 函数指针数组
    printf("12. 函数指针数组（计算器）:\n");
    int (*calc[3])(int, int) = {add, subtract, multiply};
    char *ops[] = {"+", "-", "×"};
    
    int num1 = 20, num2 = 4;
    for (int i = 0; i < 3; i++) {
        printf("%d %s %d = %d\n", 
               num1, ops[i], num2, calc[i](num1, num2));
    }
    printf("\n");
    
    // 13. 实际应用：排序函数
    printf("13. 实际应用 - 冒泡排序:\n");
    int unsorted[] = {64, 34, 25, 12, 22, 11, 90};
    int unsorted_size = sizeof(unsorted) / sizeof(unsorted[0]);
    
    printf("排序前: ");
    printArray(unsorted, unsorted_size);
    
    // 冒泡排序（使用指针）
    for (int i = 0; i < unsorted_size - 1; i++) {
        for (int j = 0; j < unsorted_size - i - 1; j++) {
            if (*(unsorted + j) > *(unsorted + j + 1)) {
                swapByPointer(unsorted + j, unsorted + j + 1);
            }
        }
    }
    
    printf("排序后: ");
    printArray(unsorted, unsorted_size);
    printf("\n");
    
    // 14. 实际应用：统计函数
    printf("14. 实际应用 - 统计最大最小值:\n");
    int test[] = {45, 23, 78, 12, 89, 34, 56};
    int test_size = sizeof(test) / sizeof(test[0]);
    int min, max;
    
    // 获取最大最小值
    min = max = test[0];
    for (int i = 1; i < test_size; i++) {
        if (test[i] < min) min = test[i];
        if (test[i] > max) max = test[i];
    }
    
    printf("数组: ");
    printArray(test, test_size);
    printf("最小值: %d, 最大值: %d\n", min, max);
    
    return 0;
}

// 函数实现

// 1. 传值调用（不能修改原变量）
void swapByValue(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
    // a和b是副本，不影响原变量
}

// 2. 传址调用（可以修改原变量）
void swapByPointer(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 3. 计算数组和
int sumArray(int *arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += *(arr + i);  // 或 arr[i]
    }
    return sum;
}

// 4. 打印数组
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 5. 数组元素翻倍
void doubleValues(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        *(arr + i) *= 2;
    }
}

// 6. 计算字符串长度
int stringLength(const char *str) {
    int len = 0;
    while (*str != '\0') {
        len++;
        str++;
    }
    return len;
}

// 7. 转大写
void toUpperCase(char *str) {
    while (*str != '\0') {
        if (*str >= 'a' && *str <= 'z') {
            *str = *str - 32;
        }
        str++;
    }
}

// 8. 字符串复制
void stringCopy(char *dest, const char *src) {
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

// 9. 获取尺寸（多个返回值）
void getDimensions(int *width, int *height) {
    *width = 1920;
    *height = 1080;
}

// 10. 除法和取模
void divMod(int a, int b, int *quotient, int *remainder) {
    *quotient = a / b;
    *remainder = a % b;
}

// 11. 查找最大值并返回指针
int* findMax(int *arr, int size) {
    if (size <= 0) return NULL;
    
    int *max_ptr = arr;
    for (int i = 1; i < size; i++) {
        if (*(arr + i) > *max_ptr) {
            max_ptr = arr + i;
        }
    }
    return max_ptr;
}

// 12. 查找字符
char* findChar(char *str, char ch) {
    while (*str != '\0') {
        if (*str == ch) {
            return str;
        }
        str++;
    }
    return NULL;
}

// 13. 返回静态数组
int* getStaticArray(void) {
    static int arr[5] = {10, 20, 30, 40, 50};
    return arr;  // 静态变量，函数结束后仍然存在
}

// 14. 显示值（const保护）
void displayValue(const int *ptr) {
    printf("值: %d\n", *ptr);
    // *ptr = 200;  // 错误！不能修改const指针指向的值
}

// 15. 计算和（const保护）
int sumNumbers(const int *arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

// 16-18. 简单的数学运算函数
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

/*
 * 知识点总结：
 * 
 * 函数参数传递方式：
 * 
 * 1. 传值（Pass by Value）
 *    void func(int x);
 *    - 传递变量的副本
 *    - 函数内修改不影响原变量
 *    - 适合小数据类型
 * 
 * 2. 传址（Pass by Pointer）
 *    void func(int *x);
 *    - 传递变量的地址
 *    - 函数内可以修改原变量
 *    - 高效（不复制数据）
 * 
 * 指针参数的用途：
 * 
 * 1. 修改原变量：
 *    void swap(int *a, int *b);
 * 
 * 2. 返回多个值：
 *    void getXY(int *x, int *y);
 * 
 * 3. 高效传递大数据：
 *    void process(int *largeArray, int size);
 * 
 * 4. 传递数组：
 *    void printArray(int arr[], int size);
 * 
 * 数组作为参数：
 * 
 * 声明方式：
 * - void func(int arr[], int size);
 * - void func(int *arr, int size);
 * - void func(int arr[10]);  // 10会被忽略
 * 
 * 注意：
 * - 数组退化为指针
 * - sizeof(arr) 得到的是指针大小
 * - 必须单独传递数组大小
 * - 可以修改数组元素
 * 
 * const 指针参数：
 * 
 * 1. 指向const数据：
 *    void func(const int *ptr);
 *    - 不能修改 *ptr
 *    - 可以修改 ptr
 *    - 保护数据不被修改
 * 
 * 2. const指针：
 *    void func(int * const ptr);
 *    - 可以修改 *ptr
 *    - 不能修改 ptr
 * 
 * 3. 两者结合：
 *    void func(const int * const ptr);
 *    - 都不能修改
 * 
 * 返回指针：
 * 
 * 安全的方式：
 * 1. 返回参数中的指针：
 *    int* find(int *arr, int size);
 * 
 * 2. 返回静态变量：
 *    int* getStatic() {
 *        static int x = 10;
 *        return &x;
 *    }
 * 
 * 3. 返回动态分配的内存（后续章节）：
 *    int* create() {
 *        int *p = malloc(sizeof(int));
 *        return p;
 *    }
 * 
 * 危险的方式：
 * ✗ 返回局部变量地址：
 *    int* bad() {
 *        int x = 10;
 *        return &x;  // 错误！x在函数结束后销毁
 *    }
 * 
 * 函数指针：
 * 
 * 声明：
 * 返回类型 (*指针名)(参数类型列表);
 * 
 * 例如：
 * int (*func_ptr)(int, int);
 * 
 * 使用：
 * func_ptr = add;          // 赋值
 * int result = func_ptr(5, 3);  // 调用
 * 
 * 函数指针数组：
 * int (*arr[5])(int, int);
 * - 数组中每个元素是函数指针
 * 
 * 典型应用：
 * 
 * 1. 交换函数：
 *    void swap(int *a, int *b) {
 *        int temp = *a;
 *        *a = *b;
 *        *b = temp;
 *    }
 * 
 * 2. 查找函数：
 *    int* find(int *arr, int size, int target) {
 *        for (int i = 0; i < size; i++) {
 *            if (arr[i] == target) return &arr[i];
 *        }
 *        return NULL;
 *    }
 * 
 * 3. 字符串处理：
 *    void toUpper(char *str) {
 *        while (*str) {
 *            *str = toupper(*str);
 *            str++;
 *        }
 *    }
 * 
 * 4. 统计函数：
 *    void stats(int *arr, int size, int *min, int *max) {
 *        *min = *max = arr[0];
 *        for (int i = 1; i < size; i++) {
 *            if (arr[i] < *min) *min = arr[i];
 *            if (arr[i] > *max) *max = arr[i];
 *        }
 *    }
 * 
 * 最佳实践：
 * 
 * 1. 参数设计：
 *    - 小数据用传值
 *    - 大数据用指针
 *    - 需要修改用指针
 *    - 只读数据用const指针
 * 
 * 2. 数组参数：
 *    - 总是传递大小
 *    - 考虑使用const保护
 *    - 检查NULL指针
 * 
 * 3. 返回指针：
 *    - 不返回局部变量地址
 *    - 返回NULL表示失败
 *    - 使用static或动态内存
 *    - 文档说明内存管理责任
 * 
 * 4. 函数指针：
 *    - 使用typedef简化声明
 *    - 检查NULL再调用
 *    - 清晰命名
 * 
 * 常见错误：
 * 
 * 1. 忘记传递大小：
 *    void process(int *arr) {
 *        // 无法知道数组大小
 *    }
 * 
 * 2. 返回局部变量地址：
 *    int* func() {
 *        int x = 10;
 *        return &x;  // 错误
 *    }
 * 
 * 3. 修改const数据：
 *    void func(const int *p) {
 *        *p = 10;  // 错误
 *    }
 * 
 * 4. 忘记检查NULL：
 *    int* p = find(...);
 *    *p = 10;  // 如果p是NULL会崩溃
 * 
 * 5. 指针未初始化：
 *    int *p;
 *    func(p);  // p指向未知位置
 * 
 * 调试技巧：
 * - 在函数入口检查指针是否为NULL
 * - 打印指针地址和值
 * - 使用assert验证前提条件
 * - 检查数组边界
 */
