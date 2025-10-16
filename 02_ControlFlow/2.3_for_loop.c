/*
 * 第二章：控制流程
 * 2.3 for循环 - 计数循环
 * 
 * 学习目标：
 * 1. 掌握for循环的语法结构
 * 2. 学会使用for循环解决实际问题
 * 3. 理解嵌套for循环
 */

#include <stdio.h>

int main() {
    printf("=== for循环详解 ===\n\n");
    
    // 1. 基本for循环
    printf("1. 基本for循环:\n");
    printf("输出1到5: ");
    for (int i = 1; i <= 5; i++) {
        printf("%d ", i);
    }
    printf("\n\n");
    
    // 2. for循环的各个部分
    printf("2. for循环结构说明:\n");
    printf("for (初始化; 条件; 更新) { 循环体 }\n");
    printf("倒数5到1: ");
    for (int i = 5; i >= 1; i--) {
        printf("%d ", i);
    }
    printf("\n\n");
    
    // 3. 不同的步长
    printf("3. 不同步长的循环:\n");
    printf("每次加2: ");
    for (int i = 0; i <= 10; i += 2) {
        printf("%d ", i);
    }
    printf("\n");
    
    printf("每次乘2: ");
    for (int i = 1; i <= 32; i *= 2) {
        printf("%d ", i);
    }
    printf("\n\n");
    
    // 4. 使用for循环计算累加和
    printf("4. 计算1到100的和:\n");
    int sum = 0;
    for (int i = 1; i <= 100; i++) {
        sum += i;
    }
    printf("1 + 2 + 3 + ... + 100 = %d\n\n", sum);
    
    // 5. 计算阶乘
    printf("5. 计算阶乘:\n");
    int n = 5;
    long factorial = 1;
    for (int i = 1; i <= n; i++) {
        factorial *= i;
    }
    printf("%d! = %ld\n\n", n, factorial);
    
    // 6. 遍历数组
    printf("6. 遍历数组:\n");
    int numbers[] = {10, 20, 30, 40, 50};
    int array_size = sizeof(numbers) / sizeof(numbers[0]);
    
    printf("数组元素: ");
    for (int i = 0; i < array_size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n\n");
    
    // 7. 嵌套for循环 - 打印乘法表
    printf("7. 嵌套循环 - 九九乘法表:\n");
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= i; j++) {
            printf("%d×%d=%2d  ", j, i, i*j);
        }
        printf("\n");
    }
    printf("\n");
    
    // 8. 嵌套循环 - 打印图案
    printf("8. 打印星号图案:\n");
    printf("直角三角形:\n");
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= i; j++) {
            printf("* ");
        }
        printf("\n");
    }
    printf("\n");
    
    printf("倒直角三角形:\n");
    for (int i = 5; i >= 1; i--) {
        for (int j = 1; j <= i; j++) {
            printf("* ");
        }
        printf("\n");
    }
    printf("\n");
    
    printf("正三角形:\n");
    for (int i = 1; i <= 5; i++) {
        // 打印空格
        for (int j = 1; j <= 5-i; j++) {
            printf(" ");
        }
        // 打印星号
        for (int j = 1; j <= 2*i-1; j++) {
            printf("*");
        }
        printf("\n");
    }
    printf("\n");
    
    // 9. 实际应用：寻找质数
    printf("9. 寻找2到50之间的质数:\n");
    for (int num = 2; num <= 50; num++) {
        int is_prime = 1;  // 假设是质数
        
        // 检查是否能被2到num-1之间的数整除
        for (int i = 2; i < num; i++) {
            if (num % i == 0) {
                is_prime = 0;  // 不是质数
                break;  // 找到因子就退出
            }
        }
        
        if (is_prime) {
            printf("%d ", num);
        }
    }
    printf("\n\n");
    
    // 10. 实际应用：斐波那契数列
    printf("10. 斐波那契数列前10项:\n");
    int fib1 = 0, fib2 = 1, fib_next;
    printf("%d %d ", fib1, fib2);
    
    for (int i = 2; i < 10; i++) {
        fib_next = fib1 + fib2;
        printf("%d ", fib_next);
        fib1 = fib2;
        fib2 = fib_next;
    }
    printf("\n\n");
    
    // 11. 空语句和无限循环
    printf("11. for循环的特殊形式:\n");
    
    // 初始化在循环外
    int k = 0;
    for (; k < 3; k++) {
        printf("k = %d ", k);
    }
    printf("\n");
    
    // 更新在循环体内
    int m = 0;
    for (; m < 3;) {
        printf("m = %d ", m);
        m++;
    }
    printf("\n");
    
    // 无限循环（需要break跳出）
    printf("无限循环示例（只执行3次）: ");
    int count = 0;
    for (;;) {
        printf("%d ", count);
        count++;
        if (count >= 3) {
            break;  // 跳出循环
        }
    }
    printf("\n\n");
    
    // 12. 实际应用：数字倒序输出
    printf("12. 数字倒序输出:\n");
    int number = 12345;
    printf("原数字: %d\n", number);
    printf("倒序输出: ");
    
    for (; number > 0; number /= 10) {
        printf("%d", number % 10);
    }
    printf("\n");
    
    return 0;
}

/*
 * 知识点总结：
 * 
 * for循环语法：
 * for (初始化; 条件判断; 更新表达式) {
 *     循环体语句;
 * }
 * 
 * 执行流程：
 * 1. 执行初始化表达式（只执行一次）
 * 2. 判断条件是否为真
 * 3. 如果为真，执行循环体
 * 4. 执行更新表达式
 * 5. 返回步骤2
 * 
 * for循环的组成部分：
 * - 初始化：设置循环变量的初始值（可选）
 * - 条件：循环继续的条件（可选）
 * - 更新：每次循环后的操作（可选）
 * - 循环体：需要重复执行的代码
 * 
 * 常见用途：
 * 1. 计数循环：执行固定次数
 * 2. 遍历数组：访问数组的每个元素
 * 3. 数学计算：累加、累乘、阶乘
 * 4. 图案绘制：使用嵌套循环
 * 
 * 嵌套for循环：
 * - 外层循环每执行一次，内层循环执行完整一轮
 * - 常用于二维数组、矩阵、图案绘制
 * - 注意避免过深的嵌套，影响性能
 * 
 * 循环控制：
 * - break：立即退出循环
 * - continue：跳过本次循环，继续下一次
 * 
 * 特殊情况：
 * 1. 空初始化：for (; i < 10; i++)
 * 2. 空条件：for (int i = 0; ; i++) - 无限循环
 * 3. 空更新：for (int i = 0; i < 10; )
 * 4. 全空：for (;;) - 无限循环
 * 
 * 注意事项：
 * 1. 循环变量作用域在for语句内（C99标准）
 * 2. 避免在循环体内修改循环变量导致的逻辑错误
 * 3. 注意循环条件，避免死循环
 * 4. 嵌套循环要注意时间复杂度
 * 
 * 最佳实践：
 * - 循环变量名要有意义（i, j, k 用于简单计数）
 * - 避免在循环内进行不必要的计算
 * - 能用for就不用while（当循环次数明确时）
 * - 注意数组越界问题
 */
