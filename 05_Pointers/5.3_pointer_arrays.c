/*
 * 第五章：指针
 * 5.3 指针与数组
 * 
 * 学习目标：
 * 1. 深入理解指针和数组的关系
 * 2. 掌握数组名作为指针的使用
 * 3. 学会指针数组和数组指针
 * 4. 理解多维数组与指针
 */

#include <stdio.h>
#include <string.h>

int main() {
    printf("=== 指针与数组 ===\n\n");
    
    // 1. 数组名是指针常量
    printf("1. 数组名的本质:\n");
    int arr[] = {10, 20, 30, 40, 50};
    
    printf("数组名 arr: %p\n", (void*)arr);
    printf("首元素地址 &arr[0]: %p\n", (void*)&arr[0]);
    printf("arr == &arr[0]: %s\n\n", arr == &arr[0] ? "是" : "否");
    
    // 2. 数组名与指针的区别
    printf("2. 数组名与指针的区别:\n");
    int nums[] = {1, 2, 3};
    int *ptr = nums;
    
    printf("sizeof(nums) = %zu (整个数组)\n", sizeof(nums));
    printf("sizeof(ptr) = %zu (指针大小)\n", sizeof(ptr));
    
    // arr = ptr;  // 错误！数组名不能被赋值
    ptr = nums;    // 正确！指针可以被赋值
    printf("ptr 可以重新赋值\n\n");
    
    // 3. 通过指针访问数组
    printf("3. 通过指针访问数组:\n");
    int data[] = {100, 200, 300, 400, 500};
    int *p = data;
    
    printf("方式1 - 数组下标: data[2] = %d\n", data[2]);
    printf("方式2 - 指针下标: p[2] = %d\n", p[2]);
    printf("方式3 - 指针运算: *(p+2) = %d\n", *(p+2));
    printf("方式4 - 数组指针运算: *(data+2) = %d\n\n", *(data+2));
    
    // 4. 指针遍历数组
    printf("4. 使用指针遍历数组:\n");
    int values[] = {5, 10, 15, 20, 25};
    int size = sizeof(values) / sizeof(values[0]);
    
    printf("方式1 - 指针递增:\n");
    int *pv = values;
    for (int i = 0; i < size; i++) {
        printf("%d ", *pv);
        pv++;
    }
    printf("\n");
    
    printf("方式2 - 指针加法:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", *(values + i));
    }
    printf("\n\n");
    
    // 5. 字符串与指针
    printf("5. 字符串与指针:\n");
    char str1[] = "Hello";      // 字符数组
    char *str2 = "World";       // 字符串字面量
    
    printf("str1 (数组): %s\n", str1);
    printf("str2 (指针): %s\n", str2);
    
    str1[0] = 'h';  // 可以修改
    printf("修改后的 str1: %s\n", str1);
    
    // str2[0] = 'w';  // 错误！不能修改字符串字面量
    printf("str2 指向只读内存，不能修改\n\n");
    
    // 6. 指针数组
    printf("6. 指针数组（数组的每个元素是指针）:\n");
    char *fruits[] = {
        "Apple",
        "Banana",
        "Orange",
        "Grape",
        "Mango"
    };
    
    int fruit_count = sizeof(fruits) / sizeof(fruits[0]);
    printf("水果列表:\n");
    for (int i = 0; i < fruit_count; i++) {
        printf("%d. %s\n", i + 1, fruits[i]);
    }
    printf("\n");
    
    // 7. 数组指针（指向数组的指针）
    printf("7. 数组指针（指向整个数组的指针）:\n");
    int matrix[3] = {10, 20, 30};
    int (*arr_ptr)[3] = &matrix;  // 指向包含3个int的数组
    
    printf("通过数组指针访问:\n");
    for (int i = 0; i < 3; i++) {
        printf("(*arr_ptr)[%d] = %d\n", i, (*arr_ptr)[i]);
    }
    printf("\n");
    
    // 8. 指针数组 vs 数组指针
    printf("8. 指针数组 vs 数组指针:\n");
    int a = 1, b = 2, c = 3;
    
    // 指针数组：数组中的元素是指针
    int *ptr_array[3] = {&a, &b, &c};
    printf("指针数组 int *ptr_array[3]:\n");
    for (int i = 0; i < 3; i++) {
        printf("*ptr_array[%d] = %d\n", i, *ptr_array[i]);
    }
    
    // 数组指针：指向数组的指针
    int array[3] = {10, 20, 30};
    int (*array_ptr)[3] = &array;
    printf("\n数组指针 int (*array_ptr)[3]:\n");
    for (int i = 0; i < 3; i++) {
        printf("(*array_ptr)[%d] = %d\n", i, (*array_ptr)[i]);
    }
    printf("\n");
    
    // 9. 二维数组与指针
    printf("9. 二维数组与指针:\n");
    int table[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    printf("二维数组:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%2d ", table[i][j]);
        }
        printf("\n");
    }
    
    printf("\ntable[0] 是指向第一行的指针: %p\n", (void*)table[0]);
    printf("table[1] 是指向第二行的指针: %p\n", (void*)table[1]);
    printf("*table[0] = %d (第一行第一个元素)\n\n", *table[0]);
    
    // 10. 用指针访问二维数组
    printf("10. 用指针访问二维数组:\n");
    int grid[2][3] = {{1, 2, 3}, {4, 5, 6}};
    
    printf("grid[1][2] = %d\n", grid[1][2]);
    printf("*(grid[1] + 2) = %d\n", *(grid[1] + 2));
    printf("*(*(grid + 1) + 2) = %d\n\n", *(*(grid + 1) + 2));
    
    // 11. 指向二维数组的指针
    printf("11. 指向二维数组的指针:\n");
    int mat[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int (*pmat)[3] = mat;  // 指向包含3个int的数组
    
    printf("通过指针访问二维数组:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", pmat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    // 12. 字符串数组
    printf("12. 字符串数组（指针数组）:\n");
    char *days[] = {
        "Monday", "Tuesday", "Wednesday",
        "Thursday", "Friday", "Saturday", "Sunday"
    };
    
    printf("一周的日期:\n");
    for (int i = 0; i < 7; i++) {
        printf("%s ", days[i]);
    }
    printf("\n\n");
    
    // 13. 实际应用：命令行参数模拟
    printf("13. 实际应用 - 命令行参数风格:\n");
    char *argv[] = {"program", "-o", "output.txt", "-v"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    
    printf("程序名: %s\n", argv[0]);
    printf("参数:\n");
    for (int i = 1; i < argc; i++) {
        printf("  argv[%d] = %s\n", i, argv[i]);
    }
    printf("\n");
    
    // 14. 实际应用：查找表
    printf("14. 实际应用 - 查找表:\n");
    char *months[] = {
        "January", "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December"
    };
    
    int month_num = 7;
    if (month_num >= 1 && month_num <= 12) {
        printf("第%d个月是: %s\n\n", month_num, months[month_num - 1]);
    }
    
    // 15. 实际应用：矩阵操作
    printf("15. 实际应用 - 矩阵求和:\n");
    int scores[3][4] = {
        {85, 90, 78, 92},
        {88, 76, 95, 89},
        {91, 84, 88, 93}
    };
    
    printf("学生成绩表:\n");
    for (int i = 0; i < 3; i++) {
        printf("学生%d: ", i + 1);
        int sum = 0;
        for (int j = 0; j < 4; j++) {
            printf("%d ", scores[i][j]);
            sum += scores[i][j];
        }
        printf("| 总分: %d, 平均: %.2f\n", sum, sum / 4.0);
    }
    printf("\n");
    
    // 16. 实际应用：字符串搜索
    printf("16. 实际应用 - 在字符串数组中搜索:\n");
    char *names[] = {"Alice", "Bob", "Charlie", "David", "Eve"};
    int name_count = sizeof(names) / sizeof(names[0]);
    char *search = "Charlie";
    
    int found = -1;
    for (int i = 0; i < name_count; i++) {
        if (strcmp(names[i], search) == 0) {
            found = i;
            break;
        }
    }
    
    if (found != -1) {
        printf("找到 '%s'，索引: %d\n\n", search, found);
    }
    
    // 17. 数组作为指针传递
    printf("17. 数组和指针的内存布局:\n");
    int seq[] = {1, 2, 3, 4};
    int *pseq = seq;
    
    printf("数组元素地址:\n");
    for (int i = 0; i < 4; i++) {
        printf("&seq[%d] = %p\n", i, (void*)&seq[i]);
    }
    
    printf("\n通过指针访问相同地址:\n");
    for (int i = 0; i < 4; i++) {
        printf("(pseq + %d) = %p, 值: %d\n", 
               i, (void*)(pseq + i), *(pseq + i));
    }
    printf("\n");
    
    // 18. const 与数组指针
    printf("18. const 与数组:\n");
    const int const_arr[] = {10, 20, 30};
    const int *pc = const_arr;
    
    printf("const 数组: ");
    for (int i = 0; i < 3; i++) {
        printf("%d ", pc[i]);
    }
    printf("\n");
    // pc[0] = 99;  // 错误！不能修改
    printf("const 保护数组不被修改\n");
    
    return 0;
}

/*
 * 知识点总结：
 * 
 * 数组名与指针：
 * 
 * 相同点：
 * - 数组名可以当作指针使用
 * - arr 等价于 &arr[0]
 * - 都可以用下标访问：arr[i] 和 ptr[i]
 * - 都可以进行指针运算：arr+i 和 ptr+i
 * 
 * 不同点：
 * - sizeof(arr) = 整个数组大小
 * - sizeof(ptr) = 指针大小
 * - arr 是常量，不能被赋值
 * - ptr 是变量，可以被赋值
 * - &arr 是指向整个数组的指针
 * - &ptr 是指向指针的指针
 * 
 * 访问数组元素的等价方式：
 * 
 * 假设：int arr[5]; int *p = arr;
 * 
 * 访问第i个元素：
 * - arr[i]
 * - *(arr + i)
 * - p[i]
 * - *(p + i)
 * 
 * 获取第i个元素地址：
 * - &arr[i]
 * - arr + i
 * - &p[i]
 * - p + i
 * 
 * 字符串与指针：
 * 
 * 1. 字符数组：
 *    char str[] = "Hello";
 *    - 存储在栈上
 *    - 可以修改
 *    - 自动管理内存
 * 
 * 2. 字符串指针：
 *    char *str = "Hello";
 *    - 指向字符串字面量
 *    - 存储在只读内存
 *    - 不能修改内容
 * 
 * 指针数组：
 * - 定义：类型 *数组名[大小]
 * - 例如：int *arr[5]
 * - 含义：数组中每个元素都是指针
 * - 用途：字符串数组、动态数组集合
 * 
 * 示例：
 * char *names[] = {"Alice", "Bob", "Charlie"};
 * 
 * 数组指针：
 * - 定义：类型 (*指针名)[大小]
 * - 例如：int (*ptr)[5]
 * - 含义：指向包含5个int的数组的指针
 * - 用途：二维数组、矩阵操作
 * 
 * 示例：
 * int arr[5] = {1, 2, 3, 4, 5};
 * int (*ptr)[5] = &arr;
 * 
 * 记忆技巧：
 * - int *arr[5];  // []优先级高，先是数组
 * - int (*ptr)[5]; // ()强制，先是指针
 * 
 * 二维数组与指针：
 * 
 * 二维数组：int arr[3][4];
 * 
 * 理解：
 * - arr 是包含3个元素的数组
 * - 每个元素是包含4个int的数组
 * - arr[0], arr[1], arr[2] 是指向行的指针
 * 
 * 访问：
 * - arr[i][j]          // 标准方式
 * - *(arr[i] + j)      // 指针方式1
 * - *(*(arr + i) + j)  // 指针方式2
 * - (*(arr + i))[j]    // 指针方式3
 * 
 * 指向二维数组的指针：
 * int (*p)[4] = arr;  // 指向包含4个int的数组
 * 
 * 访问：
 * - p[i][j]
 * - (p+i)[0][j]
 * - *(*(p+i)+j)
 * 
 * 字符串数组：
 * 
 * 方式1：二维字符数组
 * char strs[3][10] = {"Hello", "World", "C"};
 * - 固定大小
 * - 浪费空间
 * - 可以修改
 * 
 * 方式2：指针数组
 * char *strs[] = {"Hello", "World", "C"};
 * - 灵活大小
 * - 节省空间
 * - 指向字符串字面量（不可修改）
 * 
 * 常用模式：
 * 
 * 1. 字符串数组（命令行参数）：
 *    char *argv[] = {"prog", "-a", "-b"};
 *    int argc = sizeof(argv) / sizeof(argv[0]);
 * 
 * 2. 查找表：
 *    char *months[] = {"Jan", "Feb", ...};
 *    printf("%s", months[month-1]);
 * 
 * 3. 菜单系统：
 *    char *menu[] = {
 *        "1. Option 1",
 *        "2. Option 2",
 *        ...
 *    };
 * 
 * const 与数组：
 * 
 * 1. const 数组：
 *    const int arr[] = {1, 2, 3};
 *    - 数组元素不能修改
 * 
 * 2. 指向 const 数据的指针：
 *    const int *p = arr;
 *    - 不能通过 p 修改数据
 * 
 * 3. const 指针：
 *    int * const p = arr;
 *    - p 不能指向其他地址
 * 
 * 内存布局：
 * 
 * 数组：
 * int arr[4] = {1, 2, 3, 4};
 * [1][2][3][4]  <- 连续内存
 * 
 * 指针数组：
 * char *strs[3] = {"Hi", "OK", "Bye"};
 * [ptr1][ptr2][ptr3]  <- 指针数组
 *   ↓     ↓      ↓
 *  "Hi"  "OK"   "Bye"  <- 字符串在其他位置
 * 
 * 性能考虑：
 * - 数组访问和指针访问性能相当
 * - 编译器会优化
 * - 指针可能稍快（少一次计算）
 * - 可读性更重要
 * 
 * 常见错误：
 * 
 * 1. 混淆指针数组和数组指针：
 *    int *arr[5];   // 指针数组
 *    int (*ptr)[5]; // 数组指针
 * 
 * 2. 修改字符串字面量：
 *    char *s = "Hello";
 *    s[0] = 'h';  // 错误！段错误
 * 
 * 3. sizeof 理解错误：
 *    void func(int arr[]) {
 *        int n = sizeof(arr) / sizeof(arr[0]);  // 错误
 *    }
 * 
 * 4. 返回局部数组：
 *    int* func() {
 *        int arr[5];
 *        return arr;  // 错误
 *    }
 * 
 * 最佳实践：
 * - 使用指针数组处理字符串集合
 * - 传递数组时同时传递大小
 * - 使用 const 保护只读数组
 * - 注意字符串字面量的只读性
 * - 为二维数组使用适当的指针类型
 * - 清晰命名指针和数组变量
 * - 优先使用数组表示法（可读性）
 */
