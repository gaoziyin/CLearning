/*
 * 第五章：指针
 * 5.5 指针进阶主题
 * 
 * 学习目标：
 * 1. 理解多级指针（指向指针的指针）
 * 2. 掌握复杂的指针表达式
 * 3. 了解指针的常见陷阱和最佳实践
 * 4. 学习指针的实际应用案例
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 函数声明
void modifyPointer(int **ptr, int *newValue);
void allocateMemory(int **ptr, int value);
void printMatrix(int **matrix, int rows, int cols);
char** createStringArray(int size);

int main() {
    printf("=== 指针进阶主题 ===\n\n");
    
    // 1. 二级指针（指向指针的指针）
    printf("1. 二级指针基础:\n");
    int value = 100;
    int *ptr = &value;
    int **pptr = &ptr;  // 指向指针的指针
    
    printf("value = %d\n", value);
    printf("*ptr = %d\n", *ptr);
    printf("**pptr = %d\n", **pptr);
    
    printf("\n地址关系:\n");
    printf("&value = %p\n", (void*)&value);
    printf("ptr = %p\n", (void*)ptr);
    printf("*pptr = %p\n", (void*)*pptr);
    printf("&ptr = %p\n", (void*)&ptr);
    printf("pptr = %p\n\n", (void*)pptr);
    
    // 2. 通过二级指针修改指针
    printf("2. 通过二级指针修改指针:\n");
    int a = 10, b = 20;
    int *p = &a;
    
    printf("修改前: *p = %d\n", *p);
    
    int **pp = &p;
    *pp = &b;  // 修改p的值，使其指向b
    
    printf("修改后: *p = %d\n\n", *p);
    
    // 3. 通过二级指针修改值
    printf("3. 通过二级指针修改值:\n");
    int num = 50;
    int *pnum = &num;
    int **ppnum = &pnum;
    
    printf("修改前: num = %d\n", num);
    **ppnum = 999;
    printf("修改后: num = %d\n\n", num);
    
    // 4. 二级指针作为函数参数
    printf("4. 二级指针作为函数参数:\n");
    int val1 = 100, val2 = 200;
    int *ptr1 = &val1;
    
    printf("函数调用前: *ptr1 = %d\n", *ptr1);
    modifyPointer(&ptr1, &val2);
    printf("函数调用后: *ptr1 = %d\n\n", *ptr1);
    
    // 5. 指针数组与二级指针
    printf("5. 指针数组与二级指针:\n");
    char *names[] = {"Alice", "Bob", "Charlie", "David"};
    char **pnames = names;  // 指针数组可以赋值给二级指针
    
    printf("使用指针数组:\n");
    for (int i = 0; i < 4; i++) {
        printf("%s ", names[i]);
    }
    printf("\n");
    
    printf("使用二级指针:\n");
    for (int i = 0; i < 4; i++) {
        printf("%s ", *(pnames + i));
    }
    printf("\n\n");
    
    // 6. 动态二维数组（指针数组）
    printf("6. 动态二维数组（指针数组方式）:\n");
    int rows = 3, cols = 4;
    
    // 分配指针数组
    int **matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }
    
    // 初始化
    int count = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = count++;
        }
    }
    
    // 打印
    printf("矩阵:\n");
    printMatrix(matrix, rows, cols);
    
    // 释放内存
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    printf("\n");
    
    // 7. 三级指针
    printf("7. 三级指针:\n");
    int x = 42;
    int *px = &x;
    int **ppx = &px;
    int ***pppx = &ppx;
    
    printf("x = %d\n", x);
    printf("*px = %d\n", *px);
    printf("**ppx = %d\n", **ppx);
    printf("***pppx = %d\n\n", ***pppx);
    
    // 8. 指针常量 vs 常量指针
    printf("8. 指针常量 vs 常量指针:\n");
    int m = 10, n = 20;
    
    // const int *p1: 指向常量的指针
    const int *p1 = &m;
    printf("const int *p1 = &m;\n");
    printf("*p1 = %d\n", *p1);
    // *p1 = 30;  // 错误！不能修改指向的值
    p1 = &n;      // 可以修改指针
    printf("p1 = &n; (可以修改指针)\n");
    printf("*p1 = %d\n", *p1);
    
    // int * const p2: 指针常量
    int * const p2 = &m;
    printf("\nint * const p2 = &m;\n");
    printf("*p2 = %d\n", *p2);
    *p2 = 30;     // 可以修改指向的值
    printf("*p2 = 30; (可以修改值)\n");
    printf("*p2 = %d\n", *p2);
    // p2 = &n;   // 错误！不能修改指针
    
    // const int * const p3: 常量指针指向常量
    const int * const p3 = &n;
    printf("\nconst int * const p3 = &n;\n");
    printf("*p3 = %d\n", *p3);
    // *p3 = 40;  // 错误！
    // p3 = &m;   // 错误！
    printf("都不能修改\n\n");
    
    // 9. void 指针的高级用法
    printf("9. void 指针（通用指针）:\n");
    void *vptr;
    int vi = 100;
    float vf = 3.14;
    char vc = 'A';
    
    vptr = &vi;
    printf("指向int: %d\n", *(int*)vptr);
    
    vptr = &vf;
    printf("指向float: %.2f\n", *(float*)vptr);
    
    vptr = &vc;
    printf("指向char: %c\n\n", *(char*)vptr);
    
    // 10. 指针类型转换
    printf("10. 指针类型转换:\n");
    int arr[] = {0x12345678, 0xABCDEF00};
    char *byte_ptr = (char*)arr;
    
    printf("整数值: 0x%X\n", arr[0]);
    printf("按字节访问:\n");
    for (int i = 0; i < 4; i++) {
        printf("字节[%d]: 0x%02X\n", i, (unsigned char)byte_ptr[i]);
    }
    printf("\n");
    
    // 11. 复杂的指针表达式
    printf("11. 复杂的指针表达式:\n");
    int data[] = {10, 20, 30, 40, 50};
    int *pd = data;
    
    printf("数组: ");
    for (int i = 0; i < 5; i++) printf("%d ", data[i]);
    printf("\n");
    
    printf("*pd++ = %d (后置++，先取值再移动)\n", *pd++);
    printf("现在 *pd = %d\n", *pd);
    
    pd = data;  // 重置
    printf("*++pd = %d (前置++，先移动再取值)\n", *++pd);
    printf("现在 *pd = %d\n", *pd);
    
    pd = data;  // 重置
    printf("(*pd)++ = %d (值递增)\n", (*pd)++);
    printf("现在 *pd = %d\n\n", *pd);
    
    // 12. 指针数组排序
    printf("12. 实际应用 - 字符串排序（指针数组）:\n");
    char *languages[] = {"Python", "C", "Java", "JavaScript", "Go"};
    int lang_count = 5;
    
    printf("排序前: ");
    for (int i = 0; i < lang_count; i++) {
        printf("%s ", languages[i]);
    }
    printf("\n");
    
    // 冒泡排序（只交换指针）
    for (int i = 0; i < lang_count - 1; i++) {
        for (int j = 0; j < lang_count - i - 1; j++) {
            if (strcmp(languages[j], languages[j + 1]) > 0) {
                char *temp = languages[j];
                languages[j] = languages[j + 1];
                languages[j + 1] = temp;
            }
        }
    }
    
    printf("排序后: ");
    for (int i = 0; i < lang_count; i++) {
        printf("%s ", languages[i]);
    }
    printf("\n\n");
    
    // 13. 函数指针高级应用
    printf("13. 实际应用 - 回调函数模式:\n");
    
    // 定义函数指针类型
    typedef int (*Operation)(int, int);
    
    // 操作函数
    int add_op(int a, int b) { return a + b; }
    int sub_op(int a, int b) { return a - b; }
    int mul_op(int a, int b) { return a * b; }
    
    // 执行操作的函数
    void execute(Operation op, int x, int y, const char *name) {
        printf("%s: %d\n", name, op(x, y));
    }
    
    int num1 = 15, num2 = 5;
    execute(add_op, num1, num2, "加法");
    execute(sub_op, num1, num2, "减法");
    execute(mul_op, num1, num2, "乘法");
    printf("\n");
    
    // 14. 指针的常见陷阱
    printf("14. 指针常见陷阱示例:\n");
    
    printf("陷阱1: 野指针\n");
    int *wild;  // 未初始化
    printf("野指针包含随机地址: %p\n", (void*)wild);
    printf("解决：int *wild = NULL;\n\n");
    
    printf("陷阱2: 悬空指针\n");
    int *dangling = (int*)malloc(sizeof(int));
    *dangling = 100;
    printf("分配内存: *dangling = %d\n", *dangling);
    free(dangling);
    printf("释放后dangling仍指向已释放的内存\n");
    printf("解决：free后设置为NULL\n");
    dangling = NULL;
    printf("dangling = NULL; (安全)\n\n");
    
    printf("陷阱3: 内存泄漏\n");
    int *leak = (int*)malloc(sizeof(int));
    printf("分配内存但忘记释放会导致内存泄漏\n");
    printf("解决：使用完后 free(leak);\n");
    free(leak);
    printf("已释放\n\n");
    
    // 15. 指针使用的最佳实践
    printf("15. 指针最佳实践:\n");
    printf("✓ 总是初始化指针（NULL或有效地址）\n");
    printf("✓ 使用前检查是否为NULL\n");
    printf("✓ free后将指针设为NULL\n");
    printf("✓ 不返回局部变量地址\n");
    printf("✓ 使用const保护不应修改的数据\n");
    printf("✓ 避免多次释放同一指针\n");
    printf("✓ 配对使用malloc和free\n");
    printf("✓ 注意指针运算的边界\n");
    printf("✓ 使用有意义的变量名\n");
    printf("✓ 添加注释说明指针用途\n\n");
    
    // 16. 指针调试技巧
    printf("16. 指针调试技巧:\n");
    int debug_val = 42;
    int *debug_ptr = &debug_val;
    
    printf("打印指针信息:\n");
    printf("  指针地址: %p\n", (void*)&debug_ptr);
    printf("  指针值（指向的地址）: %p\n", (void*)debug_ptr);
    printf("  指针指向的值: %d\n", *debug_ptr);
    printf("  指针是否为NULL: %s\n", debug_ptr == NULL ? "是" : "否");
    printf("  变量地址: %p\n", (void*)&debug_val);
    
    return 0;
}

// 函数实现

// 通过二级指针修改指针
void modifyPointer(int **ptr, int *newValue) {
    *ptr = newValue;  // 修改指针指向的地址
}

// 分配内存并赋值
void allocateMemory(int **ptr, int value) {
    *ptr = (int*)malloc(sizeof(int));
    if (*ptr != NULL) {
        **ptr = value;
    }
}

// 打印矩阵
void printMatrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// 创建字符串数组
char** createStringArray(int size) {
    char **arr = (char**)malloc(size * sizeof(char*));
    for (int i = 0; i < size; i++) {
        arr[i] = (char*)malloc(50 * sizeof(char));
    }
    return arr;
}

/*
 * 知识点总结：
 * 
 * 多级指针：
 * 
 * 1. 二级指针（指向指针的指针）
 *    int **pp;
 *    - pp 是指针
 *    - *pp 是指针（int*）
 *    - **pp 是整数（int）
 * 
 * 2. 三级指针
 *    int ***ppp;
 *    - ppp 是指针
 *    - *ppp 是二级指针（int**）
 *    - **ppp 是指针（int*）
 *    - ***ppp 是整数（int）
 * 
 * 二级指针的应用：
 * 
 * 1. 修改指针的值：
 *    void changePtr(int **pp, int *newAddr) {
 *        *pp = newAddr;
 *    }
 * 
 * 2. 函数中分配内存：
 *    void allocate(int **pp) {
 *        *pp = malloc(sizeof(int));
 *    }
 * 
 * 3. 指针数组：
 *    char *strs[] = {"a", "b", "c"};
 *    char **p = strs;
 * 
 * 4. 动态二维数组：
 *    int **matrix = malloc(rows * sizeof(int*));
 *    for (int i = 0; i < rows; i++)
 *        matrix[i] = malloc(cols * sizeof(int));
 * 
 * const 与指针：
 * 
 * 1. 指向常量的指针：
 *    const int *p;
 *    - 不能修改 *p
 *    - 可以修改 p
 *    - 读作："p是指向const int的指针"
 * 
 * 2. 常量指针：
 *    int * const p;
 *    - 可以修改 *p
 *    - 不能修改 p
 *    - 读作："p是const指针，指向int"
 * 
 * 3. 指向常量的常量指针：
 *    const int * const p;
 *    - 不能修改 *p
 *    - 不能修改 p
 * 
 * 记忆技巧：
 * - const在*左边：数据是const
 * - const在*右边：指针是const
 * 
 * void 指针：
 * - 可以指向任何类型
 * - 不能直接解引用
 * - 使用前需要类型转换
 * - 常用于通用接口
 * 
 * 例如：
 * void *p = &x;
 * int val = *(int*)p;
 * 
 * 复杂指针表达式：
 * 
 * 优先级（高到低）：
 * 1. () []
 * 2. * &（右到左）
 * 3. ++ --（后置）
 * 4. ++ --（前置）* &（右到左）
 * 
 * 常见表达式：
 * - *p++     先取*p，后p++
 * - *++p     先++p，后取*p
 * - ++*p     先取*p，后值++
 * - (*p)++   明确：值++
 * - *p + 1   *p的值加1
 * - *(p+1)   p[1]
 * 
 * 指针陷阱：
 * 
 * 1. 野指针（Wild Pointer）
 *    int *p;  // 未初始化
 *    *p = 10; // 危险！
 *    
 *    解决：int *p = NULL;
 * 
 * 2. 悬空指针（Dangling Pointer）
 *    int *p = malloc(...);
 *    free(p);
 *    *p = 10;  // 危险！p指向已释放内存
 *    
 *    解决：free后设置 p = NULL;
 * 
 * 3. 内存泄漏
 *    int *p = malloc(...);
 *    p = NULL;  // 丢失引用，无法释放
 *    
 *    解决：free(p); p = NULL;
 * 
 * 4. 返回局部变量地址
 *    int* func() {
 *        int x = 10;
 *        return &x;  // 错误
 *    }
 * 
 * 5. 重复释放
 *    free(p);
 *    free(p);  // 错误
 * 
 * 6. 未配对的malloc/free
 *    int *p = malloc(...);
 *    // 忘记free(p);
 * 
 * 动态内存管理：
 * 
 * 分配：
 * - malloc(size)     分配size字节
 * - calloc(n, size)  分配n个size字节并清零
 * - realloc(p, size) 重新分配
 * 
 * 释放：
 * - free(p)          释放内存
 * 
 * 最佳实践：
 * 
 * 1. 初始化：
 *    int *p = NULL;
 * 
 * 2. 检查：
 *    if (p != NULL) {
 *        *p = 10;
 *    }
 * 
 * 3. 释放：
 *    free(p);
 *    p = NULL;
 * 
 * 4. 分配检查：
 *    int *p = malloc(sizeof(int));
 *    if (p == NULL) {
 *        // 处理错误
 *    }
 * 
 * 5. 配对：
 *    每个malloc对应一个free
 * 
 * 调试技巧：
 * 
 * 1. 打印指针信息：
 *    printf("p = %p\n", (void*)p);
 *    printf("*p = %d\n", *p);
 * 
 * 2. 检查NULL：
 *    if (p == NULL) {
 *        printf("指针为空\n");
 *    }
 * 
 * 3. 使用调试工具：
 *    - gdb（Linux）
 *    - Visual Studio调试器（Windows）
 *    - valgrind（内存检查）
 * 
 * 4. 添加断言：
 *    assert(p != NULL);
 * 
 * 高级技巧：
 * 
 * 1. typedef简化声明：
 *    typedef int* IntPtr;
 *    IntPtr p, q;  // 都是int*
 * 
 * 2. 函数指针typedef：
 *    typedef int (*Operation)(int, int);
 *    Operation op = add;
 * 
 * 3. 使用宏：
 *    #define SAFE_FREE(p) do { free(p); p = NULL; } while(0)
 * 
 * 4. 封装内存管理：
 *    void* safe_malloc(size_t size) {
 *        void *p = malloc(size);
 *        if (p == NULL) {
 *            fprintf(stderr, "内存分配失败\n");
 *            exit(1);
 *        }
 *        return p;
 *    }
 * 
 * 性能考虑：
 * - 指针操作通常很快
 * - 过度使用指针可能降低可读性
 * - 多级指针增加复杂度
 * - 现代编译器优化很好
 * 
 * 可移植性：
 * - 指针大小依赖平台（32位/64位）
 * - 不要假设指针大小
 * - 使用sizeof(void*)获取指针大小
 * - 使用intptr_t存储指针值
 * 
 * 安全编程：
 * - 永远初始化指针
 * - 检查NULL
 * - 边界检查
 * - 使用const保护
 * - 避免类型转换
 * - 使用静态分析工具
 * - 代码审查
 * - 单元测试
 */
