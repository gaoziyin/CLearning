/*
 * 第五章：指针
 * 5.1 指针基础
 * 
 * 学习目标：
 * 1. 理解指针的概念和作用
 * 2. 掌握指针的声明和初始化
 * 3. 学会使用指针访问和修改变量
 * 4. 理解指针和地址的关系
 */

#include <stdio.h>

int main() {
    printf("=== 指针基础 ===\n\n");
    
    // 1. 理解内存地址
    printf("1. 内存地址:\n");
    int num = 42;
    
    printf("变量 num 的值: %d\n", num);
    printf("变量 num 的地址: %p\n", (void*)&num);
    printf("地址占用字节: %zu\n\n", sizeof(&num));
    
    // 2. 指针的声明
    printf("2. 指针的声明:\n");
    int *ptr;  // 声明一个指向int的指针
    
    printf("指针 ptr 的大小: %zu 字节\n\n", sizeof(ptr));
    
    // 3. 指针的初始化
    printf("3. 指针的初始化:\n");
    int value = 100;
    int *p = &value;  // p指向value的地址
    
    printf("value 的值: %d\n", value);
    printf("value 的地址: %p\n", (void*)&value);
    printf("指针 p 的值（存储的地址）: %p\n", (void*)p);
    printf("指针 p 指向的值: %d\n\n", *p);
    
    // 4. 取地址运算符 &
    printf("4. 取地址运算符 &:\n");
    int a = 10;
    int b = 20;
    
    printf("a = %d, 地址 = %p\n", a, (void*)&a);
    printf("b = %d, 地址 = %p\n\n", b, (void*)&b);
    
    // 5. 解引用运算符 *
    printf("5. 解引用运算符 * (间接访问):\n");
    int x = 50;
    int *px = &x;
    
    printf("直接访问: x = %d\n", x);
    printf("通过指针访问: *px = %d\n", *px);
    printf("两者相等: %s\n\n", x == *px ? "是" : "否");
    
    // 6. 通过指针修改变量
    printf("6. 通过指针修改变量:\n");
    int number = 5;
    int *pnum = &number;
    
    printf("修改前: number = %d\n", number);
    *pnum = 99;  // 通过指针修改
    printf("修改后: number = %d\n", number);
    printf("*pnum = %d\n\n", *pnum);
    
    // 7. 多个指针指向同一个变量
    printf("7. 多个指针指向同一个变量:\n");
    int shared = 777;
    int *p1 = &shared;
    int *p2 = &shared;
    
    printf("shared = %d\n", shared);
    printf("*p1 = %d\n", *p1);
    printf("*p2 = %d\n", *p2);
    
    *p1 = 888;
    printf("通过p1修改后:\n");
    printf("shared = %d\n", shared);
    printf("*p2 = %d\n\n", *p2);
    
    // 8. 指针的类型
    printf("8. 不同类型的指针:\n");
    int i = 10;
    float f = 3.14;
    char c = 'A';
    double d = 2.718;
    
    int *pi = &i;
    float *pf = &f;
    char *pc = &c;
    double *pd = &d;
    
    printf("int: %d, 地址: %p\n", *pi, (void*)pi);
    printf("float: %.2f, 地址: %p\n", *pf, (void*)pf);
    printf("char: %c, 地址: %p\n", *pc, (void*)pc);
    printf("double: %.3f, 地址: %p\n\n", *pd, (void*)pd);
    
    // 9. 空指针 NULL
    printf("9. 空指针 NULL:\n");
    int *null_ptr = NULL;  // 初始化为空
    
    printf("null_ptr 的值: %p\n", (void*)null_ptr);
    
    if (null_ptr == NULL) {
        printf("指针为空，不能解引用\n");
    }
    
    // 安全使用指针
    null_ptr = &value;
    if (null_ptr != NULL) {
        printf("指针已初始化，值为: %d\n\n", *null_ptr);
    }
    
    // 10. 野指针（未初始化的指针）
    printf("10. 指针初始化的重要性:\n");
    int *wild_ptr;  // 未初始化，指向随机地址
    
    printf("未初始化的指针包含随机地址: %p\n", (void*)wild_ptr);
    printf("这是危险的！应该初始化为NULL或有效地址\n\n");
    
    // 11. void 指针（通用指针）
    printf("11. void 指针:\n");
    void *vptr;
    int val1 = 100;
    float val2 = 3.14;
    
    vptr = &val1;
    printf("指向int: %d\n", *(int*)vptr);  // 需要类型转换
    
    vptr = &val2;
    printf("指向float: %.2f\n\n", *(float*)vptr);
    
    // 12. 指针与const
    printf("12. 指针与const:\n");
    
    // const数据，非const指针
    const int const_val = 100;
    const int *ptr_to_const = &const_val;
    printf("const数据: %d\n", *ptr_to_const);
    // *ptr_to_const = 200;  // 错误！不能修改
    
    // 非const数据，const指针
    int normal_val = 50;
    int * const const_ptr = &normal_val;
    printf("const指针: %d\n", *const_ptr);
    *const_ptr = 60;  // 可以修改数据
    printf("修改后: %d\n", *const_ptr);
    // const_ptr = &a;  // 错误！不能修改指针
    
    printf("\n");
    
    // 13. 指针的大小
    printf("13. 指针的大小:\n");
    printf("所有指针的大小都相同（在同一架构上）:\n");
    printf("int*    : %zu 字节\n", sizeof(int*));
    printf("float*  : %zu 字节\n", sizeof(float*));
    printf("char*   : %zu 字节\n", sizeof(char*));
    printf("double* : %zu 字节\n", sizeof(double*));
    printf("void*   : %zu 字节\n\n", sizeof(void*));
    
    // 14. 指针赋值
    printf("14. 指针赋值:\n");
    int m = 10, n = 20;
    int *pm = &m;
    int *pn = &n;
    
    printf("pm 指向 m(%d), pn 指向 n(%d)\n", *pm, *pn);
    
    pm = pn;  // pm现在指向n
    printf("pm = pn 后:\n");
    printf("pm 指向: %d\n", *pm);
    printf("pn 指向: %d\n\n", *pn);
    
    // 15. 指针比较
    printf("15. 指针比较:\n");
    int arr[5] = {1, 2, 3, 4, 5};
    int *p_start = &arr[0];
    int *p_end = &arr[4];
    
    printf("p_start 地址: %p\n", (void*)p_start);
    printf("p_end 地址: %p\n", (void*)p_end);
    
    if (p_start < p_end) {
        printf("p_start 在 p_end 之前\n");
    }
    
    if (p_start == &arr[0]) {
        printf("p_start 指向数组首元素\n");
    }
    
    printf("\n");
    
    // 16. 实际应用：交换两个变量
    printf("16. 实际应用 - 通过指针交换变量:\n");
    int var1 = 100, var2 = 200;
    int *pvar1 = &var1, *pvar2 = &var2;
    
    printf("交换前: var1 = %d, var2 = %d\n", var1, var2);
    
    // 交换指针指向的值
    int temp = *pvar1;
    *pvar1 = *pvar2;
    *pvar2 = temp;
    
    printf("交换后: var1 = %d, var2 = %d\n\n", var1, var2);
    
    // 17. 实际应用：查找最大值
    printf("17. 实际应用 - 指针查找最大值:\n");
    int nums[] = {45, 78, 23, 89, 56, 12, 34};
    int size = sizeof(nums) / sizeof(nums[0]);
    
    int *pmax = &nums[0];  // 假设第一个是最大
    
    for (int i = 1; i < size; i++) {
        if (nums[i] > *pmax) {
            pmax = &nums[i];
        }
    }
    
    printf("数组中的最大值: %d\n", *pmax);
    printf("最大值的索引: %ld\n\n", pmax - nums);
    
    // 18. 实际应用：指针作为函数参数预览
    printf("18. 指针的用途:\n");
    printf("✓ 动态内存分配\n");
    printf("✓ 函数返回多个值\n");
    printf("✓ 高效传递大数据\n");
    printf("✓ 实现数据结构（链表、树等）\n");
    printf("✓ 操作数组和字符串\n");
    
    return 0;
}

/*
 * 知识点总结：
 * 
 * 指针的概念：
 * - 指针是一个变量，存储另一个变量的内存地址
 * - 指针本身也有地址
 * - 通过指针可以间接访问和修改其他变量
 * 
 * 指针的声明：
 * 类型 *指针名;
 * 
 * 例如：
 * int *p;      // 指向int的指针
 * float *pf;   // 指向float的指针
 * char *pc;    // 指向char的指针
 * 
 * 注意：* 是声明符号，不是运算符
 * 
 * 两个重要运算符：
 * 
 * 1. 取地址运算符 &
 *    - 获取变量的内存地址
 *    - &变量名
 *    例如：&x 返回x的地址
 * 
 * 2. 解引用运算符 *
 *    - 访问指针指向的值
 *    - *指针名
 *    例如：*p 访问p指向的值
 * 
 * 指针的初始化：
 * 
 * 1. 指向现有变量：
 *    int x = 10;
 *    int *p = &x;
 * 
 * 2. 初始化为NULL：
 *    int *p = NULL;
 * 
 * 3. 未初始化（危险）：
 *    int *p;  // 野指针
 * 
 * 指针的使用：
 * 
 * 1. 读取值：
 *    int x = 10;
 *    int *p = &x;
 *    printf("%d", *p);  // 输出10
 * 
 * 2. 修改值：
 *    *p = 20;  // x现在是20
 * 
 * 3. 修改指针：
 *    int y = 30;
 *    p = &y;  // p现在指向y
 * 
 * 空指针 NULL：
 * - 不指向任何有效内存
 * - 值为0或((void*)0)
 * - 解引用空指针会导致程序崩溃
 * - 使用前应检查：if (p != NULL)
 * 
 * 野指针：
 * - 未初始化的指针
 * - 指向随机内存地址
 * - 非常危险
 * - 应该初始化为NULL或有效地址
 * 
 * void 指针：
 * - 通用指针类型
 * - 可以指向任何类型
 * - 使用前需要类型转换
 * - 例如：*(int*)vptr
 * 
 * const 与指针：
 * 
 * 1. 指向常量的指针：
 *    const int *p;
 *    - 不能通过p修改数据
 *    - 可以修改p本身
 * 
 * 2. 常量指针：
 *    int * const p;
 *    - 可以修改数据
 *    - 不能修改p本身
 * 
 * 3. 指向常量的常量指针：
 *    const int * const p;
 *    - 不能修改数据
 *    - 不能修改p本身
 * 
 * 指针的大小：
 * - 在32位系统：4字节
 * - 在64位系统：8字节
 * - 与指向的类型无关
 * - 所有指针大小相同
 * 
 * 指针运算：
 * - 指针可以比较（==, !=, <, >, <=, >=）
 * - 指针可以赋值（p = q）
 * - 指针算术运算（下一节详细讲解）
 * 
 * 指针与数组：
 * - 数组名是指向首元素的常量指针
 * - arr[i] 等价于 *(arr + i)
 * - &arr[i] 等价于 arr + i
 * 
 * 指针的优势：
 * 1. 动态内存管理
 * 2. 高效的数据传递
 * 3. 实现复杂数据结构
 * 4. 直接操作内存
 * 5. 函数返回多个值
 * 
 * 常见错误：
 * 
 * 1. 使用未初始化的指针：
 *    int *p;
 *    *p = 10;  // 错误！p指向未知位置
 * 
 * 2. 解引用空指针：
 *    int *p = NULL;
 *    *p = 10;  // 错误！会导致崩溃
 * 
 * 3. 返回局部变量地址：
 *    int* func() {
 *        int x = 10;
 *        return &x;  // 错误！x是局部变量
 *    }
 * 
 * 4. 类型不匹配：
 *    float f = 3.14;
 *    int *p = &f;  // 警告！类型不匹配
 * 
 * 5. 忘记取地址：
 *    int x = 10;
 *    int *p = x;  // 错误！应该是&x
 * 
 * 最佳实践：
 * - 总是初始化指针
 * - 使用前检查NULL
 * - 不要返回局部变量地址
 * - 使用const保护不修改的数据
 * - 释放后将指针置为NULL
 * - 避免野指针
 * - 使用有意义的指针名
 * - 注意指针类型匹配
 * 
 * 调试技巧：
 * - 打印指针地址：printf("%p", (void*)p);
 * - 打印指针值：printf("%d", *p);
 * - 检查NULL：if (p == NULL)
 * - 使用调试器查看内存
 * 
 * 记忆口诀：
 * - & 取地址
 * - * 取内容
 * - 指针存地址
 * - 解引用得值
 */
