/*
 * 第五章：指针
 * 5.2 指针运算
 * 
 * 学习目标：
 * 1. 理解指针的算术运算
 * 2. 掌握指针的递增和递减
 * 3. 学会指针的加减运算
 * 4. 理解指针与数组的关系
 */

#include <stdio.h>

int main() {
    printf("=== 指针运算 ===\n\n");
    
    // 1. 指针递增
    printf("1. 指针递增 (++):\n");
    int arr1[] = {10, 20, 30, 40, 50};
    int *p1 = arr1;  // 指向第一个元素
    
    printf("初始位置: *p1 = %d, 地址 = %p\n", *p1, (void*)p1);
    p1++;  // 移动到下一个int
    printf("p1++后:   *p1 = %d, 地址 = %p\n", *p1, (void*)p1);
    p1++;
    printf("再p1++:   *p1 = %d, 地址 = %p\n\n", *p1, (void*)p1);
    
    // 2. 指针递减
    printf("2. 指针递减 (--):\n");
    int arr2[] = {100, 200, 300, 400};
    int *p2 = &arr2[3];  // 指向最后一个元素
    
    printf("初始位置: *p2 = %d, 地址 = %p\n", *p2, (void*)p2);
    p2--;
    printf("p2--后:   *p2 = %d, 地址 = %p\n", *p2, (void*)p2);
    p2--;
    printf("再p2--:   *p2 = %d, 地址 = %p\n\n", *p2, (void*)p2);
    
    // 3. 指针加法
    printf("3. 指针加法 (p + n):\n");
    int numbers[] = {5, 10, 15, 20, 25, 30};
    int *pn = numbers;
    
    printf("pn:     *pn = %d\n", *pn);
    printf("pn+1:   *(pn+1) = %d\n", *(pn+1));
    printf("pn+2:   *(pn+2) = %d\n", *(pn+2));
    printf("pn+5:   *(pn+5) = %d\n\n", *(pn+5));
    
    // 4. 指针减法
    printf("4. 指针减法 (p - n):\n");
    int *p_end = &numbers[5];
    
    printf("p_end:   *p_end = %d\n", *p_end);
    printf("p_end-1: *(p_end-1) = %d\n", *(p_end-1));
    printf("p_end-3: *(p_end-3) = %d\n\n", *(p_end-3));
    
    // 5. 指针相减（计算距离）
    printf("5. 两个指针相减:\n");
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int *p_first = &data[1];
    int *p_last = &data[6];
    
    printf("p_first 指向: %d\n", *p_first);
    printf("p_last 指向: %d\n", *p_last);
    printf("p_last - p_first = %ld (相距%ld个元素)\n\n", 
           p_last - p_first, p_last - p_first);
    
    // 6. 不同类型指针的步长
    printf("6. 不同类型指针的步长:\n");
    char carr[] = "Hello";
    int iarr[] = {1, 2, 3};
    float farr[] = {1.1, 2.2, 3.3};
    double darr[] = {1.11, 2.22, 3.33};
    
    char *pc = carr;
    int *pi = iarr;
    float *pf = farr;
    double *pd = darr;
    
    printf("char*:   %p -> %p (移动%ld字节)\n", 
           (void*)pc, (void*)(pc+1), (char*)(pc+1) - pc);
    printf("int*:    %p -> %p (移动%ld字节)\n", 
           (void*)pi, (void*)(pi+1), (char*)(pi+1) - (char*)pi);
    printf("float*:  %p -> %p (移动%ld字节)\n", 
           (void*)pf, (void*)(pf+1), (char*)(pf+1) - (char*)pf);
    printf("double*: %p -> %p (移动%ld字节)\n\n", 
           (void*)pd, (void*)(pd+1), (char*)(pd+1) - (char*)pd);
    
    // 7. 指针与数组下标的关系
    printf("7. 指针与数组下标:\n");
    int vals[] = {11, 22, 33, 44, 55};
    int *pv = vals;
    
    printf("数组下标方式:\n");
    for (int i = 0; i < 5; i++) {
        printf("vals[%d] = %d\n", i, vals[i]);
    }
    
    printf("\n指针方式:\n");
    for (int i = 0; i < 5; i++) {
        printf("*(pv+%d) = %d\n", i, *(pv+i));
    }
    printf("\n");
    
    // 8. 遍历数组的不同方式
    printf("8. 遍历数组的三种方式:\n");
    int items[] = {100, 200, 300, 400, 500};
    int size = sizeof(items) / sizeof(items[0]);
    
    // 方式1：数组下标
    printf("方式1 - 数组下标: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", items[i]);
    }
    printf("\n");
    
    // 方式2：指针算术
    printf("方式2 - 指针算术: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", *(items + i));
    }
    printf("\n");
    
    // 方式3：指针递增
    printf("方式3 - 指针递增: ");
    int *ptr = items;
    for (int i = 0; i < size; i++) {
        printf("%d ", *ptr);
        ptr++;
    }
    printf("\n\n");
    
    // 9. 指针比较
    printf("9. 指针比较:\n");
    int array[] = {1, 2, 3, 4, 5};
    int *pa = &array[0];
    int *pb = &array[4];
    
    printf("pa 指向 array[0]: %d\n", *pa);
    printf("pb 指向 array[4]: %d\n", *pb);
    
    if (pa < pb) {
        printf("pa 在 pb 之前（地址更小）\n");
    }
    
    if (pa != pb) {
        printf("pa 和 pb 指向不同位置\n");
    }
    printf("\n");
    
    // 10. 反向遍历数组
    printf("10. 反向遍历数组:\n");
    int seq[] = {10, 20, 30, 40, 50};
    int *p_start = &seq[4];  // 从最后开始
    
    printf("反向输出: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", *(p_start - i));
    }
    printf("\n\n");
    
    // 11. 字符串遍历
    printf("11. 字符串遍历（指针方式）:\n");
    char str[] = "Hello";
    char *ps = str;
    
    printf("逐字符输出: ");
    while (*ps != '\0') {
        printf("%c ", *ps);
        ps++;
    }
    printf("\n\n");
    
    // 12. 指针运算的实际应用：查找元素
    printf("12. 实际应用 - 查找元素:\n");
    int search_arr[] = {15, 23, 8, 42, 16, 31, 9};
    int search_size = sizeof(search_arr) / sizeof(search_arr[0]);
    int target = 42;
    int *found = NULL;
    
    for (int *p = search_arr; p < search_arr + search_size; p++) {
        if (*p == target) {
            found = p;
            break;
        }
    }
    
    if (found != NULL) {
        printf("找到 %d，位置: %ld\n\n", target, found - search_arr);
    }
    
    // 13. 实际应用：复制数组
    printf("13. 实际应用 - 复制数组（指针方式）:\n");
    int source[] = {1, 2, 3, 4, 5};
    int dest[5];
    int copy_size = sizeof(source) / sizeof(source[0]);
    
    int *psrc = source;
    int *pdst = dest;
    
    for (int i = 0; i < copy_size; i++) {
        *pdst = *psrc;
        psrc++;
        pdst++;
    }
    
    printf("源数组: ");
    for (int i = 0; i < copy_size; i++) printf("%d ", source[i]);
    printf("\n目标数组: ");
    for (int i = 0; i < copy_size; i++) printf("%d ", dest[i]);
    printf("\n\n");
    
    // 14. 实际应用：字符串长度
    printf("14. 实际应用 - 计算字符串长度:\n");
    char message[] = "Programming";
    char *pm = message;
    int length = 0;
    
    while (*pm != '\0') {
        length++;
        pm++;
    }
    
    printf("字符串: %s\n", message);
    printf("长度: %d\n\n", length);
    
    // 15. 实际应用：反转数组
    printf("15. 实际应用 - 反转数组:\n");
    int reverse[] = {1, 2, 3, 4, 5, 6};
    int rev_size = sizeof(reverse) / sizeof(reverse[0]);
    
    printf("原数组: ");
    for (int i = 0; i < rev_size; i++) printf("%d ", reverse[i]);
    printf("\n");
    
    int *left = reverse;
    int *right = reverse + rev_size - 1;
    
    while (left < right) {
        int temp = *left;
        *left = *right;
        *right = temp;
        left++;
        right--;
    }
    
    printf("反转后: ");
    for (int i = 0; i < rev_size; i++) printf("%d ", reverse[i]);
    printf("\n\n");
    
    // 16. 前缀和后缀递增的区别
    printf("16. ++p 与 p++ 的区别:\n");
    int test[] = {10, 20, 30};
    int *pt = test;
    
    printf("初始: *pt = %d\n", *pt);
    printf("*pt++ = %d (先取值，后移动)\n", *pt++);
    printf("现在: *pt = %d\n", *pt);
    
    pt = test;  // 重置
    printf("\n初始: *pt = %d\n", *pt);
    printf("*++pt = %d (先移动，后取值)\n", *++pt);
    printf("现在: *pt = %d\n\n", *pt);
    
    // 17. 复杂的指针表达式
    printf("17. 复杂的指针表达式:\n");
    int complex[] = {5, 10, 15, 20, 25};
    int *pc_ptr = complex;
    
    printf("*pc_ptr = %d\n", *pc_ptr);
    printf("*(pc_ptr + 2) = %d\n", *(pc_ptr + 2));
    printf("*pc_ptr + 2 = %d (注意：先解引用，再加2)\n", *pc_ptr + 2);
    printf("(*pc_ptr)++ = %d (解引用后值加1)\n", (*pc_ptr)++);
    printf("现在 *pc_ptr = %d\n\n", *pc_ptr);
    
    // 18. 指针运算的边界
    printf("18. 指针运算注意事项:\n");
    int bounds[] = {1, 2, 3, 4, 5};
    int *pb = bounds;
    
    printf("✓ 合法：pb + 5 (指向末尾后一个位置)\n");
    printf("✓ 合法：pb < bounds + 5 (比较)\n");
    printf("✗ 非法：pb + 10 (越界)\n");
    printf("✗ 非法：pb - 10 (越界)\n");
    printf("✗ 危险：*(pb + 10) (访问越界内存)\n");
    
    return 0;
}

/*
 * 知识点总结：
 * 
 * 指针算术运算基础：
 * 
 * 1. 指针递增 (++)
 *    p++;     // 指向下一个元素
 *    ++p;     // 指向下一个元素
 *    移动的字节数 = sizeof(数据类型)
 * 
 * 2. 指针递减 (--)
 *    p--;     // 指向前一个元素
 *    --p;     // 指向前一个元素
 * 
 * 3. 指针加整数
 *    p + n    // 向后移动n个元素
 *    p += n   // 移动并赋值
 * 
 * 4. 指针减整数
 *    p - n    // 向前移动n个元素
 *    p -= n   // 移动并赋值
 * 
 * 5. 两指针相减
 *    p2 - p1  // 返回两指针间的元素个数
 *    结果类型：ptrdiff_t
 * 
 * 指针步长：
 * - char*:   +1 移动 1 字节
 * - int*:    +1 移动 4 字节（通常）
 * - float*:  +1 移动 4 字节
 * - double*: +1 移动 8 字节
 * 
 * 公式：新地址 = 旧地址 + (n × sizeof(类型))
 * 
 * 指针与数组的等价关系：
 * 
 * 假设：int arr[5]; int *p = arr;
 * 
 * 等价表达式：
 * arr[i]  ≡  *(arr + i)  ≡  *(p + i)  ≡  p[i]
 * &arr[i] ≡  arr + i     ≡  p + i
 * 
 * 指针运算规则：
 * 
 * 合法操作：
 * ✓ 指针 + 整数
 * ✓ 指针 - 整数
 * ✓ 指针 - 指针（同类型）
 * ✓ 指针比较（<, >, ==, !=, <=, >=）
 * ✓ 指针赋值
 * 
 * 非法操作：
 * ✗ 指针 + 指针
 * ✗ 指针 * 指针
 * ✗ 指针 / 指针
 * ✗ 指针 % 指针
 * 
 * 指针递增/递减优先级：
 * 
 * 1. *p++
 *    等价于 *(p++)
 *    先取值，后移动指针
 * 
 * 2. *++p
 *    等价于 *(++p)
 *    先移动指针，后取值
 * 
 * 3. ++*p
 *    等价于 ++(*p)
 *    先取值，后值递增
 * 
 * 4. (*p)++
 *    明确先取值，后值递增
 * 
 * 遍历数组的方式：
 * 
 * 方式1：数组下标
 * for (int i = 0; i < n; i++) {
 *     使用 arr[i]
 * }
 * 
 * 方式2：指针算术
 * for (int i = 0; i < n; i++) {
 *     使用 *(arr + i)
 * }
 * 
 * 方式3：指针递增
 * int *p = arr;
 * for (int i = 0; i < n; i++) {
 *     使用 *p
 *     p++;
 * }
 * 
 * 方式4：指针比较
 * for (int *p = arr; p < arr + n; p++) {
 *     使用 *p
 * }
 * 
 * 指针比较：
 * - 只能比较指向同一数组的指针
 * - 可以使用 <, >, <=, >=, ==, !=
 * - 地址小的指针 < 地址大的指针
 * - 可以比较是否为NULL
 * 
 * 有效指针范围：
 * - 指向数组元素
 * - 指向数组末尾后一个位置（但不能解引用）
 * - NULL指针
 * 
 * 无效操作：
 * - 指向数组开始前的位置
 * - 指向数组末尾后多个位置
 * - 访问越界内存
 * 
 * 字符串遍历：
 * char *p = str;
 * while (*p != '\0') {
 *     // 处理 *p
 *     p++;
 * }
 * 
 * 常用指针技巧：
 * 
 * 1. 查找元素：
 *    for (int *p = arr; p < arr + size; p++) {
 *        if (*p == target) return p;
 *    }
 * 
 * 2. 复制数组：
 *    int *src = source, *dst = dest;
 *    while (src < source + size) {
 *        *dst++ = *src++;
 *    }
 * 
 * 3. 反转数组：
 *    int *left = arr, *right = arr + size - 1;
 *    while (left < right) {
 *        交换 *left 和 *right
 *        left++; right--;
 *    }
 * 
 * 性能考虑：
 * - 指针操作通常比数组索引快
 * - 现代编译器会优化两者
 * - 代码可读性也很重要
 * 
 * 常见错误：
 * 
 * 1. 越界访问：
 *    int arr[5];
 *    int *p = arr;
 *    *(p + 10);  // 错误！越界
 * 
 * 2. 指针未初始化：
 *    int *p;
 *    p++;  // 危险！p指向未知位置
 * 
 * 3. 比较不同数组的指针：
 *    int arr1[5], arr2[5];
 *    int *p1 = arr1, *p2 = arr2;
 *    if (p1 < p2) { }  // 未定义行为
 * 
 * 4. 解引用末尾后的指针：
 *    int arr[5];
 *    int *p = arr + 5;  // 合法
 *    int x = *p;        // 错误！不能解引用
 * 
 * 最佳实践：
 * - 总是检查指针边界
 * - 使用有意义的指针名
 * - 优先使用指针比较而非索引
 * - 注意指针运算的优先级
 * - 遍历时使用 p < end 而非 p <= end
 * - 保持代码可读性
 * - 添加注释说明指针用途
 * 
 * 调试技巧：
 * - 打印指针地址
 * - 打印指针间距离
 * - 检查指针是否在有效范围
 * - 使用断言验证指针
 */
