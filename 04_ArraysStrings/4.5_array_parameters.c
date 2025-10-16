/*
 * 第四章：数组与字符串
 * 4.5 数组作为函数参数
 * 
 * 学习目标：
 * 1. 理解数组传递给函数的机制
 * 2. 掌握数组参数的声明方式
 * 3. 学会在函数中操作数组
 * 4. 了解数组和指针的关系
 */

#include <stdio.h>
#include <string.h>

// 函数声明

// 1. 一维数组作为参数
void printArray(int arr[], int size);
int sumArray(int arr[], int size);
int findMax(int arr[], int size);

// 2. 数组参数的不同声明方式
void modifyArray1(int arr[], int size);
void modifyArray2(int *arr, int size);
void modifyArray3(int arr[10]);  // 大小会被忽略

// 3. const 数组参数
void displayArray(const int arr[], int size);
int calculateSum(const int arr[], int size);

// 4. 二维数组作为参数
void print2DArray(int rows, int cols, int arr[rows][cols]);
void printMatrix(int arr[][3], int rows);  // 列数必须指定

// 5. 字符串作为参数
void printString(char str[]);
int stringLength(const char str[]);
void toUpperCase(char str[]);

// 6. 数组排序函数
void bubbleSort(int arr[], int size);
void selectionSort(int arr[], int size);

// 7. 数组搜索函数
int linearSearch(int arr[], int size, int target);
int binarySearch(int arr[], int size, int target);

// 8. 数组操作函数
void reverseArray(int arr[], int size);
void copyArray(int dest[], const int src[], int size);

// 9. 返回数组（通过参数）
void createArray(int arr[], int size, int value);
void inputArray(int arr[], int size);

// 10. 统计函数
int countOccurrences(int arr[], int size, int value);
float calculateAverage(int arr[], int size);

int main() {
    printf("=== 数组作为函数参数 ===\n\n");
    
    // 1. 一维数组传递
    printf("1. 一维数组传递:\n");
    int numbers[] = {10, 20, 30, 40, 50};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    printf("数组内容: ");
    printArray(numbers, size);
    
    int sum = sumArray(numbers, size);
    printf("数组和: %d\n", sum);
    
    int max = findMax(numbers, size);
    printf("最大值: %d\n\n", max);
    
    // 2. 修改数组
    printf("2. 在函数中修改数组:\n");
    int data[] = {1, 2, 3, 4, 5};
    int len = sizeof(data) / sizeof(data[0]);
    
    printf("修改前: ");
    printArray(data, len);
    
    modifyArray1(data, len);
    printf("修改后: ");
    printArray(data, len);
    printf("\n");
    
    // 3. const保护数组
    printf("3. const保护只读数组:\n");
    int scores[] = {85, 92, 78, 95, 88};
    int n = sizeof(scores) / sizeof(scores[0]);
    
    displayArray(scores, n);
    int total = calculateSum(scores, n);
    printf("总分: %d\n\n", total);
    
    // 4. 二维数组传递
    printf("4. 二维数组传递:\n");
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    printMatrix(matrix, 3);
    printf("\n");
    
    // 5. 字符串传递
    printf("5. 字符串作为参数:\n");
    char message[] = "Hello World";
    
    printString(message);
    printf("字符串长度: %d\n", stringLength(message));
    
    toUpperCase(message);
    printf("转大写后: ");
    printString(message);
    printf("\n");
    
    // 6. 数组排序
    printf("6. 数组排序:\n");
    int arr1[] = {64, 34, 25, 12, 22, 11, 90};
    int arr2[] = {64, 34, 25, 12, 22, 11, 90};
    int arr_size = sizeof(arr1) / sizeof(arr1[0]);
    
    printf("原数组: ");
    printArray(arr1, arr_size);
    
    bubbleSort(arr1, arr_size);
    printf("冒泡排序后: ");
    printArray(arr1, arr_size);
    
    selectionSort(arr2, arr_size);
    printf("选择排序后: ");
    printArray(arr2, arr_size);
    printf("\n");
    
    // 7. 数组搜索
    printf("7. 数组搜索:\n");
    int search_arr[] = {10, 23, 35, 47, 52, 68, 79, 85, 91};
    int search_size = sizeof(search_arr) / sizeof(search_arr[0]);
    int target = 47;
    
    printf("数组: ");
    printArray(search_arr, search_size);
    
    int index = linearSearch(search_arr, search_size, target);
    printf("线性搜索 %d: 索引 %d\n", target, index);
    
    index = binarySearch(search_arr, search_size, target);
    printf("二分搜索 %d: 索引 %d\n\n", target, index);
    
    // 8. 数组反转
    printf("8. 数组反转:\n");
    int rev[] = {1, 2, 3, 4, 5};
    int rev_size = sizeof(rev) / sizeof(rev[0]);
    
    printf("原数组: ");
    printArray(rev, rev_size);
    
    reverseArray(rev, rev_size);
    printf("反转后: ");
    printArray(rev, rev_size);
    printf("\n");
    
    // 9. 数组复制
    printf("9. 数组复制:\n");
    int source[] = {10, 20, 30, 40, 50};
    int destination[5];
    int copy_size = sizeof(source) / sizeof(source[0]);
    
    copyArray(destination, source, copy_size);
    printf("源数组: ");
    printArray(source, copy_size);
    printf("目标数组: ");
    printArray(destination, copy_size);
    printf("\n");
    
    // 10. 创建数组
    printf("10. 创建和初始化数组:\n");
    int new_arr[8];
    createArray(new_arr, 8, 99);
    printf("创建的数组: ");
    printArray(new_arr, 8);
    printf("\n");
    
    // 11. 统计函数
    printf("11. 数组统计:\n");
    int stats[] = {5, 3, 8, 3, 9, 3, 1};
    int stats_size = sizeof(stats) / sizeof(stats[0]);
    
    printf("数组: ");
    printArray(stats, stats_size);
    
    int count = countOccurrences(stats, stats_size, 3);
    printf("数字3出现次数: %d\n", count);
    
    float avg = calculateAverage(stats, stats_size);
    printf("平均值: %.2f\n\n", avg);
    
    // 12. 实际应用：学生成绩管理
    printf("12. 实际应用 - 学生成绩管理:\n");
    int grades[] = {85, 92, 78, 95, 88, 76, 91};
    int num_students = sizeof(grades) / sizeof(grades[0]);
    
    printf("学生成绩: ");
    printArray(grades, num_students);
    
    printf("总分: %d\n", sumArray(grades, num_students));
    printf("平均分: %.2f\n", calculateAverage(grades, num_students));
    printf("最高分: %d\n", findMax(grades, num_students));
    
    // 排序成绩
    int sorted_grades[7];
    copyArray(sorted_grades, grades, num_students);
    bubbleSort(sorted_grades, num_students);
    printf("排序后: ");
    printArray(sorted_grades, num_students);
    
    return 0;
}

// 函数实现

// 1. 打印数组
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 2. 计算数组和
int sumArray(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

// 3. 查找最大值
int findMax(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// 4. 修改数组（方式1）
void modifyArray1(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] *= 2;  // 每个元素乘以2
    }
}

// 5. 修改数组（方式2 - 指针形式）
void modifyArray2(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] += 10;
    }
}

// 6. 修改数组（方式3 - 指定大小，但会被忽略）
void modifyArray3(int arr[10]) {
    // 实际上和 int arr[] 一样
    arr[0] = 100;
}

// 7. 显示数组（const保护）
void displayArray(const int arr[], int size) {
    printf("数组内容: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    // arr[0] = 100;  // 错误！不能修改const数组
}

// 8. 计算和（const保护）
int calculateSum(const int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

// 9. 打印二维数组（变长数组）
void print2DArray(int rows, int cols, int arr[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

// 10. 打印矩阵（固定列数）
void printMatrix(int arr[][3], int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

// 11. 打印字符串
void printString(char str[]) {
    printf("%s\n", str);
}

// 12. 计算字符串长度
int stringLength(const char str[]) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

// 13. 转大写
void toUpperCase(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 32;
        }
    }
}

// 14. 冒泡排序
void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// 15. 选择排序
void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

// 16. 线性搜索
int linearSearch(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;  // 未找到
}

// 17. 二分搜索（需要有序数组）
int binarySearch(int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        }
        
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;  // 未找到
}

// 18. 反转数组
void reverseArray(int arr[], int size) {
    for (int i = 0; i < size / 2; i++) {
        int temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}

// 19. 复制数组
void copyArray(int dest[], const int src[], int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

// 20. 创建数组
void createArray(int arr[], int size, int value) {
    for (int i = 0; i < size; i++) {
        arr[i] = value;
    }
}

// 21. 输入数组
void inputArray(int arr[], int size) {
    printf("请输入%d个整数:\n", size);
    for (int i = 0; i < size; i++) {
        printf("元素[%d]: ", i);
        scanf("%d", &arr[i]);
    }
}

// 22. 统计出现次数
int countOccurrences(int arr[], int size, int value) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) {
            count++;
        }
    }
    return count;
}

// 23. 计算平均值
float calculateAverage(int arr[], int size) {
    int sum = sumArray(arr, size);
    return (float)sum / size;
}

/*
 * 知识点总结：
 * 
 * 数组作为参数的本质：
 * - C语言中，数组名是指向第一个元素的指针
 * - 传递数组实际上传递的是指针
 * - 函数内修改数组会影响原数组
 * - 不会复制整个数组
 * 
 * 数组参数的声明方式：
 * 
 * 1. 标准形式：
 *    void func(int arr[], int size);
 * 
 * 2. 指针形式：
 *    void func(int *arr, int size);
 * 
 * 3. 指定大小（会被忽略）：
 *    void func(int arr[10]);
 * 
 * 这三种形式完全等价！
 * 
 * 一维数组参数：
 * - 必须传递数组大小
 * - sizeof在函数内无法获取真实大小
 * - 可以修改数组内容
 * 
 * 例如：
 * void processArray(int arr[], int size) {
 *     // sizeof(arr) 返回的是指针大小，不是数组大小
 *     for (int i = 0; i < size; i++) {
 *         arr[i] *= 2;
 *     }
 * }
 * 
 * const 保护：
 * void readOnly(const int arr[], int size);
 * - 防止函数修改数组
 * - 表明函数只读数组
 * - 编译器会检查
 * 
 * 二维数组参数：
 * 
 * 方式1：指定列数
 * void func(int arr[][COLS], int rows);
 * - 列数必须指定
 * - 行数可选
 * 
 * 方式2：变长数组（C99）
 * void func(int rows, int cols, int arr[rows][cols]);
 * - 尺寸参数必须在数组前
 * 
 * 字符串参数：
 * void processString(char str[]);
 * void processString(char *str);
 * - 不需要传递大小（有'\0'）
 * - 可以修改内容
 * 
 * const字符串：
 * void displayString(const char str[]);
 * - 只读，不能修改
 * 
 * 传递数组的优点：
 * 1. 不复制数据，效率高
 * 2. 可以修改原数组
 * 3. 适合大数据量
 * 
 * 传递数组的缺点：
 * 1. 容易修改原数组
 * 2. 需要单独传递大小
 * 3. 没有边界检查
 * 
 * 数组与指针：
 * int arr[5];
 * int *ptr = arr;  // arr退化为指针
 * 
 * arr[i] 等价于 *(arr + i)
 * &arr[i] 等价于 arr + i
 * 
 * 返回数组：
 * - 不能直接返回数组
 * - 可以返回指针
 * - 可以通过参数修改数组
 * 
 * 错误示例：
 * int* func() {
 *     int arr[10];  // 局部数组
 *     return arr;   // 错误！返回局部变量地址
 * }
 * 
 * 正确方式：
 * void func(int result[], int size) {
 *     // 通过参数修改数组
 * }
 * 
 * 常见操作模式：
 * 
 * 1. 遍历：
 *    for (int i = 0; i < size; i++) {
 *        // 使用arr[i]
 *    }
 * 
 * 2. 查找：
 *    for (int i = 0; i < size; i++) {
 *        if (arr[i] == target) return i;
 *    }
 * 
 * 3. 统计：
 *    int count = 0;
 *    for (int i = 0; i < size; i++) {
 *        if (条件) count++;
 *    }
 * 
 * 4. 修改：
 *    for (int i = 0; i < size; i++) {
 *        arr[i] = 新值;
 *    }
 * 
 * 注意事项：
 * 1. 总是传递数组大小
 * 2. 检查边界
 * 3. 使用const保护只读数组
 * 4. 不返回局部数组
 * 5. 二维数组必须指定列数
 * 
 * 常见错误：
 * 1. 忘记传递大小：
 *    void func(int arr[]) {
 *        int size = sizeof(arr) / sizeof(arr[0]);  // 错误
 *    }
 * 
 * 2. 返回局部数组：
 *    int* func() {
 *        int arr[10];
 *        return arr;  // 错误
 *    }
 * 
 * 3. 越界访问：
 *    void func(int arr[], int size) {
 *        arr[size] = 0;  // 错误，越界
 *    }
 * 
 * 最佳实践：
 * - 使用const保护不修改的数组
 * - 总是传递并检查数组大小
 * - 避免越界访问
 * - 为函数命名清晰表明功能
 * - 使用有意义的参数名
 * - 添加参数验证
 * - 考虑使用指针操作优化性能
 * 
 * 性能优化：
 * - 避免不必要的数组复制
 * - 使用指针算术代替索引（小幅提升）
 * - 大数组考虑传递指针
 * - 使用inline函数（小函数）
 */
