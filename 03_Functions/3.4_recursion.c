/*
 * 第三章：函数
 * 3.4 递归函数
 * 
 * 学习目标：
 * 1. 理解递归的概念
 * 2. 掌握递归函数的编写
 * 3. 了解递归的应用场景和注意事项
 */

#include <stdio.h>

// 函数声明
int factorial(int n);
int fibonacci(int n);
int sumOfDigits(int n);
int power(int base, int exp);
void printNumbers(int n);
void printReverse(int n);
int gcd(int a, int b);
void towerOfHanoi(int n, char from, char to, char aux);

int main() {
    printf("=== 递归函数详解 ===\n\n");
    
    // 1. 递归基础：阶乘
    printf("1. 递归计算阶乘:\n");
    for (int i = 0; i <= 6; i++) {
        printf("%d! = %d\n", i, factorial(i));
    }
    printf("\n");
    
    // 2. 斐波那契数列
    printf("2. 斐波那契数列（前10项）:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", fibonacci(i));
    }
    printf("\n");
    printf("F(0)=0, F(1)=1, F(n)=F(n-1)+F(n-2)\n\n");
    
    // 3. 递归求和
    printf("3. 递归计算1到n的和:\n");
    int n = 10;
    printf("1 + 2 + 3 + ... + %d = %d\n\n", n, sum(n));
    
    // 4. 数字各位之和
    printf("4. 递归计算数字各位之和:\n");
    int num = 12345;
    printf("%d 的各位之和: %d\n", num, sumOfDigits(num));
    printf("(1 + 2 + 3 + 4 + 5 = %d)\n\n", sumOfDigits(num));
    
    // 5. 幂运算
    printf("5. 递归计算幂:\n");
    printf("2³ = %d\n", power(2, 3));
    printf("5² = %d\n", power(5, 2));
    printf("3⁴ = %d\n\n", power(3, 4));
    
    // 6. 递归打印
    printf("6. 递归打印数字:\n");
    printf("正序: ");
    printNumbers(5);
    printf("\n");
    
    printf("倒序: ");
    printReverse(5);
    printf("\n\n");
    
    // 7. 最大公约数（欧几里得算法）
    printf("7. 递归求最大公约数:\n");
    int a = 48, b = 18;
    printf("GCD(%d, %d) = %d\n", a, b, gcd(a, b));
    printf("GCD(100, 35) = %d\n\n", gcd(100, 35));
    
    // 8. 二分查找（递归）
    printf("8. 递归二分查找:\n");
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 45, 56, 67, 78};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 23;
    
    int index = binarySearch(arr, 0, size - 1, target);
    if (index != -1) {
        printf("在索引 %d 处找到 %d\n", index, target);
    } else {
        printf("未找到 %d\n", target);
    }
    printf("\n");
    
    // 9. 字符串反转（递归）
    printf("9. 递归反转字符串:\n");
    char str[] = "Hello";
    printf("原字符串: %s\n", str);
    printf("反转后: ");
    reverseString(str, 0, 4);
    printf("\n\n");
    
    // 10. 汉诺塔问题
    printf("10. 汉诺塔问题（3个盘子）:\n");
    towerOfHanoi(3, 'A', 'C', 'B');
    printf("\n");
    
    // 11. 递归 vs 循环对比
    printf("11. 递归 vs 循环（计算阶乘）:\n");
    int num_fact = 5;
    printf("递归方式: %d! = %d\n", num_fact, factorial(num_fact));
    printf("循环方式: %d! = %d\n", num_fact, factorialIterative(num_fact));
    printf("\n");
    
    // 12. 递归深度示例
    printf("12. 递归深度计算:\n");
    printf("计算 5! 的递归深度: %d\n", getRecursionDepth(5));
    printf("(每次调用深度加1，直到基准情况)\n");
    
    return 0;
}

// ========== 函数定义 ==========

/*
 * 递归计算阶乘
 * n! = n × (n-1)!
 * 基准情况: 0! = 1, 1! = 1
 */
int factorial(int n) {
    // 基准情况（终止条件）
    if (n == 0 || n == 1) {
        return 1;
    }
    
    // 递归情况
    return n * factorial(n - 1);
}

/*
 * 递归计算斐波那契数列
 * F(0) = 0, F(1) = 1
 * F(n) = F(n-1) + F(n-2)
 */
int fibonacci(int n) {
    // 基准情况
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    
    // 递归情况
    return fibonacci(n - 1) + fibonacci(n - 2);
}

/*
 * 递归计算1到n的和
 * sum(n) = n + sum(n-1)
 */
int sum(int n) {
    if (n == 0) {
        return 0;
    }
    return n + sum(n - 1);
}

/*
 * 递归计算数字各位之和
 * sumOfDigits(1234) = 4 + sumOfDigits(123)
 */
int sumOfDigits(int n) {
    if (n == 0) {
        return 0;
    }
    return (n % 10) + sumOfDigits(n / 10);
}

/*
 * 递归计算幂
 * power(base, exp) = base × power(base, exp-1)
 */
int power(int base, int exp) {
    if (exp == 0) {
        return 1;
    }
    return base * power(base, exp - 1);
}

/*
 * 递归正序打印1到n
 */
void printNumbers(int n) {
    if (n == 0) {
        return;
    }
    printNumbers(n - 1);  // 先递归
    printf("%d ", n);      // 后打印
}

/*
 * 递归倒序打印n到1
 */
void printReverse(int n) {
    if (n == 0) {
        return;
    }
    printf("%d ", n);      // 先打印
    printReverse(n - 1);   // 后递归
}

/*
 * 递归求最大公约数（欧几里得算法）
 * gcd(a, b) = gcd(b, a % b)
 */
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

/*
 * 递归二分查找
 */
int binarySearch(int arr[], int left, int right, int target) {
    // 基准情况：未找到
    if (left > right) {
        return -1;
    }
    
    int mid = left + (right - left) / 2;
    
    // 基准情况：找到
    if (arr[mid] == target) {
        return mid;
    }
    
    // 递归情况
    if (arr[mid] > target) {
        return binarySearch(arr, left, mid - 1, target);  // 左半部分
    } else {
        return binarySearch(arr, mid + 1, right, target);  // 右半部分
    }
}

/*
 * 递归反转字符串
 */
void reverseString(char str[], int start, int end) {
    if (start >= end) {
        printf("%s", str);
        return;
    }
    
    // 交换首尾字符
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    
    // 递归处理中间部分
    reverseString(str, start + 1, end - 1);
}

/*
 * 汉诺塔问题
 * from: 起始柱
 * to: 目标柱
 * aux: 辅助柱
 */
void towerOfHanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        printf("移动盘子 1 从 %c 到 %c\n", from, to);
        return;
    }
    
    // 将n-1个盘子从from移到aux（借助to）
    towerOfHanoi(n - 1, from, aux, to);
    
    // 将第n个盘子从from移到to
    printf("移动盘子 %d 从 %c 到 %c\n", n, from, to);
    
    // 将n-1个盘子从aux移到to（借助from）
    towerOfHanoi(n - 1, aux, to, from);
}

/*
 * 循环方式计算阶乘（对比）
 */
int factorialIterative(int n) {
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

/*
 * 计算递归深度
 */
int getRecursionDepth(int n) {
    if (n <= 1) {
        return 1;
    }
    return 1 + getRecursionDepth(n - 1);
}

/*
 * 知识点总结：
 * 
 * 递归的概念：
 * - 函数调用自身的编程技术
 * - 将大问题分解为相似的小问题
 * - 必须有终止条件（基准情况）
 * 
 * 递归的组成要素：
 * 1. 基准情况（Base Case）：
 *    - 递归的终止条件
 *    - 不再调用自身
 *    - 直接返回结果
 * 
 * 2. 递归情况（Recursive Case）：
 *    - 函数调用自身
 *    - 问题规模缩小
 *    - 逐步接近基准情况
 * 
 * 递归的执行过程：
 * 1. 递推阶段：函数不断调用自身，问题规模减小
 * 2. 回归阶段：达到基准情况后，逐层返回结果
 * 
 * 递归 vs 循环：
 * 
 * 递归的优点：
 * - 代码简洁优雅
 * - 更符合数学定义
 * - 某些问题更直观（树、图遍历）
 * 
 * 递归的缺点：
 * - 性能开销大（函数调用）
 * - 可能栈溢出
 * - 可能重复计算（如斐波那契）
 * 
 * 循环的优点：
 * - 执行效率高
 * - 不占用栈空间
 * - 不会栈溢出
 * 
 * 循环的缺点：
 * - 某些问题不直观
 * - 代码可能复杂
 * 
 * 递归的经典应用：
 * 1. 数学计算：
 *    - 阶乘、幂运算
 *    - 斐波那契数列
 *    - 最大公约数
 * 
 * 2. 数据结构：
 *    - 树的遍历
 *    - 图的遍历
 *    - 链表操作
 * 
 * 3. 算法：
 *    - 二分查找
 *    - 快速排序
 *    - 归并排序
 *    - 回溯算法
 * 
 * 4. 经典问题：
 *    - 汉诺塔
 *    - N皇后问题
 *    - 迷宫求解
 * 
 * 递归优化：
 * 
 * 1. 尾递归优化：
 *    - 递归调用是函数最后一个操作
 *    - 编译器可以优化为循环
 * 
 * 2. 记忆化（Memoization）：
 *    - 缓存已计算的结果
 *    - 避免重复计算
 *    - 典型应用：斐波那契数列
 * 
 * 3. 转换为循环：
 *    - 某些递归可以改写为循环
 *    - 提高性能，避免栈溢出
 * 
 * 递归的注意事项：
 * 1. 必须有明确的终止条件
 * 2. 每次递归要向终止条件靠近
 * 3. 注意栈空间限制
 * 4. 避免无限递归
 * 5. 考虑性能影响
 * 
 * 常见错误：
 * 1. 没有基准情况（无限递归）
 * 2. 基准情况永远达不到
 * 3. 递归深度过大导致栈溢出
 * 4. 重复计算导致性能问题
 * 5. 参数传递错误
 * 
 * 递归深度：
 * - 递归调用的层数
 * - 每次调用占用栈空间
 * - 深度过大会导致栈溢出
 * - 典型栈大小：1-8MB
 * 
 * 何时使用递归：
 * 适合：
 * - 问题本质是递归的（树、分治）
 * - 递归定义更清晰
 * - 递归深度可控
 * 
 * 不适合：
 * - 循环更简单直观
 * - 递归深度很大
 * - 性能要求高
 * - 有大量重复计算
 * 
 * 最佳实践：
 * - 始终定义清晰的基准情况
 * - 确保每次递归都向基准情况前进
 * - 为递归函数添加详细注释
 * - 考虑递归深度限制
 * - 测试边界情况
 * - 权衡递归和循环
 * - 必要时进行优化（尾递归、记忆化）
 * - 大数据量时优先考虑循环
 */
