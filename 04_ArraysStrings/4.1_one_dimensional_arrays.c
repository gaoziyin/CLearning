/*
 * 第四章：数组与字符串
 * 4.1 一维数组
 * 
 * 学习目标：
 * 1. 理解数组的概念
 * 2. 掌握一维数组的声明和初始化
 * 3. 学会数组的遍历和操作
 */

#include <stdio.h>

int main() {
    printf("=== 一维数组详解 ===\n\n");
    
    // 1. 数组的声明和初始化
    printf("1. 数组的声明和初始化:\n");
    
    // 方式1：声明后逐个赋值
    int arr1[5];
    arr1[0] = 10;
    arr1[1] = 20;
    arr1[2] = 30;
    arr1[3] = 40;
    arr1[4] = 50;
    
    printf("arr1: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr1[i]);
    }
    printf("\n");
    
    // 方式2：声明时初始化
    int arr2[5] = {1, 2, 3, 4, 5};
    printf("arr2: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr2[i]);
    }
    printf("\n");
    
    // 方式3：部分初始化（其余为0）
    int arr3[5] = {1, 2, 3};  // arr3[3]和arr3[4]自动为0
    printf("arr3: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr3[i]);
    }
    printf("\n");
    
    // 方式4：全部初始化为0
    int arr4[5] = {0};
    printf("arr4: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr4[i]);
    }
    printf("\n");
    
    // 方式5：省略大小（编译器自动计算）
    int arr5[] = {10, 20, 30, 40, 50};
    int size5 = sizeof(arr5) / sizeof(arr5[0]);
    printf("arr5 大小: %d, 元素: ", size5);
    for (int i = 0; i < size5; i++) {
        printf("%d ", arr5[i]);
    }
    printf("\n\n");
    
    // 2. 数组的访问
    printf("2. 数组元素的访问:\n");
    int numbers[5] = {100, 200, 300, 400, 500};
    printf("第1个元素 numbers[0] = %d\n", numbers[0]);
    printf("第3个元素 numbers[2] = %d\n", numbers[2]);
    printf("最后一个元素 numbers[4] = %d\n\n", numbers[4]);
    
    // 3. 修改数组元素
    printf("3. 修改数组元素:\n");
    printf("修改前: numbers[2] = %d\n", numbers[2]);
    numbers[2] = 999;
    printf("修改后: numbers[2] = %d\n\n", numbers[2]);
    
    // 4. 计算数组大小
    printf("4. 计算数组大小:\n");
    int data[] = {5, 10, 15, 20, 25, 30};
    int array_size = sizeof(data) / sizeof(data[0]);
    printf("数组占用字节: %zu\n", sizeof(data));
    printf("单个元素字节: %zu\n", sizeof(data[0]));
    printf("数组元素个数: %d\n\n", array_size);
    
    // 5. 遍历数组
    printf("5. 遍历数组:\n");
    int scores[] = {85, 92, 78, 88, 95};
    int count = sizeof(scores) / sizeof(scores[0]);
    
    printf("所有分数: ");
    for (int i = 0; i < count; i++) {
        printf("%d ", scores[i]);
    }
    printf("\n\n");
    
    // 6. 计算数组元素的和
    printf("6. 计算数组元素的和:\n");
    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += scores[i];
    }
    printf("总分: %d\n", sum);
    printf("平均分: %.2f\n\n", (float)sum / count);
    
    // 7. 查找最大值和最小值
    printf("7. 查找最大值和最小值:\n");
    int values[] = {45, 23, 67, 12, 89, 34, 56};
    int size = sizeof(values) / sizeof(values[0]);
    
    int max = values[0];
    int min = values[0];
    
    for (int i = 1; i < size; i++) {
        if (values[i] > max) {
            max = values[i];
        }
        if (values[i] < min) {
            min = values[i];
        }
    }
    
    printf("数组: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", values[i]);
    }
    printf("\n");
    printf("最大值: %d\n", max);
    printf("最小值: %d\n\n", min);
    
    // 8. 数组反转
    printf("8. 数组反转:\n");
    int original[] = {1, 2, 3, 4, 5};
    int len = sizeof(original) / sizeof(original[0]);
    
    printf("原数组: ");
    for (int i = 0; i < len; i++) {
        printf("%d ", original[i]);
    }
    printf("\n");
    
    // 反转
    for (int i = 0; i < len / 2; i++) {
        int temp = original[i];
        original[i] = original[len - 1 - i];
        original[len - 1 - i] = temp;
    }
    
    printf("反转后: ");
    for (int i = 0; i < len; i++) {
        printf("%d ", original[i]);
    }
    printf("\n\n");
    
    // 9. 查找元素
    printf("9. 在数组中查找元素:\n");
    int search_arr[] = {10, 25, 30, 45, 50, 65, 70};
    int search_size = sizeof(search_arr) / sizeof(search_arr[0]);
    int target = 45;
    int found = -1;
    
    for (int i = 0; i < search_size; i++) {
        if (search_arr[i] == target) {
            found = i;
            break;
        }
    }
    
    if (found != -1) {
        printf("在索引 %d 处找到 %d\n", found, target);
    } else {
        printf("未找到 %d\n", target);
    }
    printf("\n");
    
    // 10. 复制数组
    printf("10. 复制数组:\n");
    int source[] = {1, 2, 3, 4, 5};
    int source_size = sizeof(source) / sizeof(source[0]);
    int destination[5];
    
    // 复制
    for (int i = 0; i < source_size; i++) {
        destination[i] = source[i];
    }
    
    printf("源数组: ");
    for (int i = 0; i < source_size; i++) {
        printf("%d ", source[i]);
    }
    printf("\n");
    
    printf("目标数组: ");
    for (int i = 0; i < source_size; i++) {
        printf("%d ", destination[i]);
    }
    printf("\n\n");
    
    // 11. 统计元素出现次数
    printf("11. 统计元素出现次数:\n");
    int nums[] = {1, 2, 3, 2, 4, 2, 5, 2};
    int nums_size = sizeof(nums) / sizeof(nums[0]);
    int search_num = 2;
    int occurrence = 0;
    
    for (int i = 0; i < nums_size; i++) {
        if (nums[i] == search_num) {
            occurrence++;
        }
    }
    
    printf("数组中 %d 出现了 %d 次\n\n", search_num, occurrence);
    
    // 12. 实际应用：成绩统计
    printf("12. 实际应用 - 成绩统计:\n");
    int student_scores[] = {85, 92, 78, 65, 88, 95, 72, 90};
    int total_students = sizeof(student_scores) / sizeof(student_scores[0]);
    
    int total_score = 0;
    int excellent = 0;  // 90分以上
    int good = 0;       // 80-89分
    int pass = 0;       // 60-79分
    int fail = 0;       // 60分以下
    
    for (int i = 0; i < total_students; i++) {
        total_score += student_scores[i];
        
        if (student_scores[i] >= 90) {
            excellent++;
        } else if (student_scores[i] >= 80) {
            good++;
        } else if (student_scores[i] >= 60) {
            pass++;
        } else {
            fail++;
        }
    }
    
    printf("总人数: %d\n", total_students);
    printf("平均分: %.2f\n", (float)total_score / total_students);
    printf("优秀(90+): %d人\n", excellent);
    printf("良好(80-89): %d人\n", good);
    printf("及格(60-79): %d人\n", pass);
    printf("不及格(<60): %d人\n", fail);
    
    return 0;
}

/*
 * 知识点总结：
 * 
 * 数组的概念：
 * - 数组是相同类型元素的集合
 * - 元素在内存中连续存储
 * - 通过索引访问元素
 * - 索引从0开始
 * 
 * 数组的声明：
 * 类型 数组名[大小];
 * 
 * 例如：
 * int arr[10];      // 声明10个整数的数组
 * float prices[5];  // 声明5个浮点数的数组
 * 
 * 数组的初始化：
 * 1. 完全初始化：
 *    int arr[5] = {1, 2, 3, 4, 5};
 * 
 * 2. 部分初始化：
 *    int arr[5] = {1, 2};  // 其余为0
 * 
 * 3. 全部初始化为0：
 *    int arr[5] = {0};
 * 
 * 4. 省略大小：
 *    int arr[] = {1, 2, 3};  // 大小自动为3
 * 
 * 数组访问：
 * - 使用索引：arr[0], arr[1], arr[2]...
 * - 索引范围：0 到 size-1
 * - 访问越界会导致未定义行为
 * 
 * 计算数组大小：
 * int size = sizeof(arr) / sizeof(arr[0]);
 * 
 * - sizeof(arr)：数组总字节数
 * - sizeof(arr[0])：单个元素字节数
 * - 相除得到元素个数
 * 
 * 数组特点：
 * 1. 固定大小：
 *    - 声明时确定大小
 *    - 运行时不能改变
 * 
 * 2. 连续存储：
 *    - 元素在内存中连续
 *    - 便于遍历和访问
 * 
 * 3. 类型统一：
 *    - 所有元素类型相同
 *    - 不能混合类型
 * 
 * 4. 索引访问：
 *    - O(1)时间复杂度
 *    - 直接计算地址
 * 
 * 常见操作：
 * 1. 遍历：
 *    for (int i = 0; i < size; i++) {
 *        处理 arr[i];
 *    }
 * 
 * 2. 查找：
 *    线性查找每个元素
 * 
 * 3. 反转：
 *    交换首尾元素
 * 
 * 4. 复制：
 *    逐个复制元素
 * 
 * 5. 统计：
 *    遍历并计数
 * 
 * 注意事项：
 * 1. 数组下标从0开始
 * 2. 不要越界访问
 * 3. 数组大小必须是常量
 * 4. 数组名不能直接赋值
 * 5. 传递给函数时传的是地址
 * 
 * 常见错误：
 * 1. 数组越界：
 *    int arr[5];
 *    arr[5] = 10;  // 错误！最大索引是4
 * 
 * 2. 未初始化就使用：
 *    int arr[5];
 *    printf("%d", arr[0]);  // 值不确定
 * 
 * 3. 数组大小使用变量（C99之前）：
 *    int n = 5;
 *    int arr[n];  // C99支持，但不推荐
 * 
 * 4. 数组赋值：
 *    int a[5], b[5];
 *    a = b;  // 错误！不能直接赋值
 * 
 * 5. 返回局部数组：
 *    不能返回局部数组的地址
 * 
 * 最佳实践：
 * - 数组声明时就初始化
 * - 使用sizeof计算大小
 * - 遍历时检查边界
 * - 使用有意义的数组名
 * - 数组作为参数时同时传递大小
 * - 避免硬编码数组大小
 * - 使用宏或const定义数组大小
 * 
 * 数组与指针：
 * - 数组名是指向首元素的指针
 * - arr 等价于 &arr[0]
 * - arr[i] 等价于 *(arr + i)
 * - 后续章节详细讲解
 */
