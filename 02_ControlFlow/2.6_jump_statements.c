/*
 * 第二章：控制流程
 * 2.6 跳转语句 - break, continue, goto
 * 
 * 学习目标：
 * 1. 掌握break语句的使用
 * 2. 理解continue语句的作用
 * 3. 了解goto语句（谨慎使用）
 */

#include <stdio.h>

int main() {
    printf("=== 跳转语句详解 ===\n\n");
    
    // 1. break - 退出循环
    printf("1. break语句 - 退出循环:\n");
    printf("找到第一个能被7整除的数: ");
    
    for (int i = 1; i <= 100; i++) {
        if (i % 7 == 0) {
            printf("%d\n", i);
            break;  // 找到后立即退出循环
        }
    }
    printf("\n");
    
    // 2. break在while循环中
    printf("2. break在while循环中:\n");
    int count = 1;
    
    while (1) {  // 无限循环
        printf("%d ", count);
        if (count >= 5) {
            break;  // 条件满足时退出
        }
        count++;
    }
    printf("\n循环已终止\n\n");
    
    // 3. break在switch中
    printf("3. break在switch语句中:\n");
    char grade = 'B';
    
    switch (grade) {
        case 'A':
            printf("优秀\n");
            break;  // 防止继续执行下一个case
        case 'B':
            printf("良好\n");
            break;
        case 'C':
            printf("中等\n");
            break;
        default:
            printf("其他\n");
            break;
    }
    printf("\n");
    
    // 4. continue - 跳过本次循环
    printf("4. continue语句 - 跳过本次循环:\n");
    printf("输出1-10之间的奇数: ");
    
    for (int i = 1; i <= 10; i++) {
        if (i % 2 == 0) {
            continue;  // 跳过偶数
        }
        printf("%d ", i);
    }
    printf("\n\n");
    
    // 5. continue在while循环中
    printf("5. continue在while循环中:\n");
    printf("输出1-10，跳过5: ");
    
    int num = 0;
    while (num < 10) {
        num++;
        if (num == 5) {
            continue;  // 跳过5
        }
        printf("%d ", num);
    }
    printf("\n\n");
    
    // 6. break vs continue
    printf("6. break vs continue对比:\n");
    
    printf("使用break（遇到5停止）: ");
    for (int i = 1; i <= 10; i++) {
        if (i == 5) {
            break;  // 退出循环
        }
        printf("%d ", i);
    }
    printf("\n");
    
    printf("使用continue（跳过5）: ");
    for (int i = 1; i <= 10; i++) {
        if (i == 5) {
            continue;  // 跳过本次，继续下一次
        }
        printf("%d ", i);
    }
    printf("\n\n");
    
    // 7. 嵌套循环中的break
    printf("7. 嵌套循环中的break:\n");
    printf("break只退出内层循环:\n");
    
    for (int i = 1; i <= 3; i++) {
        printf("外层循环 %d: ", i);
        for (int j = 1; j <= 5; j++) {
            if (j == 4) {
                break;  // 只退出内层循环
            }
            printf("%d ", j);
        }
        printf("\n");
    }
    printf("\n");
    
    // 8. 使用标志变量退出多层循环
    printf("8. 使用标志变量退出多层循环:\n");
    int found = 0;
    
    for (int i = 1; i <= 5 && !found; i++) {
        for (int j = 1; j <= 5; j++) {
            printf("(%d,%d) ", i, j);
            if (i == 3 && j == 3) {
                found = 1;
                break;
            }
        }
        printf("\n");
    }
    printf("找到目标位置(3,3)，退出所有循环\n\n");
    
    // 9. 实际应用：查找数组中的元素
    printf("9. 实际应用 - 在数组中查找元素:\n");
    int array[] = {10, 25, 37, 42, 55, 68, 73, 89, 91};
    int size = sizeof(array) / sizeof(array[0]);
    int target = 42;
    int index = -1;
    
    for (int i = 0; i < size; i++) {
        if (array[i] == target) {
            index = i;
            break;  // 找到后立即退出
        }
    }
    
    if (index != -1) {
        printf("在索引 %d 处找到 %d\n", index, target);
    } else {
        printf("未找到 %d\n", target);
    }
    printf("\n");
    
    // 10. 实际应用：输入验证
    printf("10. 实际应用 - 输入验证:\n");
    // 模拟用户输入
    int inputs[] = {-1, 0, 5, 15, 8};
    int input_idx = 0;
    int valid_input;
    
    printf("请输入1-10之间的数字:\n");
    for (int attempt = 1; attempt <= 5; attempt++) {
        int input = inputs[input_idx++];
        printf("输入: %d\n", input);
        
        if (input >= 1 && input <= 10) {
            valid_input = input;
            printf("输入有效！\n");
            break;  // 输入有效，退出循环
        }
        printf("输入无效！\n");
    }
    printf("\n");
    
    // 11. 实际应用：跳过特定值
    printf("11. 实际应用 - 计算平均分（跳过0分）:\n");
    int scores[] = {85, 0, 90, 0, 78, 92, 88, 0, 95};
    int score_count = sizeof(scores) / sizeof(scores[0]);
    int total = 0;
    int valid_count = 0;
    
    for (int i = 0; i < score_count; i++) {
        if (scores[i] == 0) {
            continue;  // 跳过0分
        }
        total += scores[i];
        valid_count++;
    }
    
    if (valid_count > 0) {
        float average = (float)total / valid_count;
        printf("有效分数个数: %d\n", valid_count);
        printf("平均分: %.2f\n", average);
    }
    printf("\n");
    
    // 12. goto语句（不推荐，但要了解）
    printf("12. goto语句示例（谨慎使用）:\n");
    int value = 0;
    
    start:  // 标签
    if (value < 3) {
        printf("value = %d\n", value);
        value++;
        goto start;  // 跳转到标签处
    }
    
    printf("循环结束\n\n");
    
    // 13. goto用于错误处理（较合理的用法）
    printf("13. goto用于错误处理:\n");
    int step = 1;
    int error = 0;
    
    printf("执行步骤 1\n");
    if (step == 1) {
        step++;
    } else {
        error = 1;
        goto cleanup;  // 跳转到清理代码
    }
    
    printf("执行步骤 2\n");
    if (step == 2) {
        step++;
    } else {
        error = 2;
        goto cleanup;
    }
    
    printf("执行步骤 3\n");
    printf("所有步骤完成\n");
    
cleanup:  // 清理代码标签
    if (error) {
        printf("发生错误，错误码: %d\n", error);
    }
    printf("清理资源\n\n");
    
    // 14. 实际应用：质数判断（使用break优化）
    printf("14. 实际应用 - 优化的质数判断:\n");
    int numbers[] = {2, 15, 17, 24, 29, 35, 37};
    int num_count = sizeof(numbers) / sizeof(numbers[0]);
    
    for (int i = 0; i < num_count; i++) {
        int n = numbers[i];
        int is_prime = 1;
        
        if (n < 2) {
            is_prime = 0;
        } else {
            for (int j = 2; j * j <= n; j++) {
                if (n % j == 0) {
                    is_prime = 0;
                    break;  // 找到因子，不是质数，立即退出
                }
            }
        }
        
        if (is_prime) {
            printf("%d 是质数\n", n);
        } else {
            printf("%d 不是质数\n", n);
        }
    }
    
    return 0;
}

/*
 * 知识点总结：
 * 
 * 1. break语句：
 * - 功能：立即退出最近的循环或switch
 * - 语法：break;
 * - 使用场景：
 *   a) 在循环中提前退出
 *   b) 在switch中防止fall through
 *   c) 找到目标后不需要继续搜索
 * 
 * 2. continue语句：
 * - 功能：跳过本次循环剩余部分，进入下一次循环
 * - 语法：continue;
 * - 使用场景：
 *   a) 跳过特定值
 *   b) 过滤不符合条件的数据
 *   c) 简化嵌套的if语句
 * 
 * 3. goto语句：
 * - 功能：无条件跳转到指定标签
 * - 语法：goto 标签; ... 标签:
 * - 使用场景（极少使用）：
 *   a) 深层嵌套循环的退出
 *   b) 错误处理和资源清理
 *   c) 状态机实现
 * 
 * break vs continue：
 * 
 * break：
 * - 完全退出循环
 * - 执行循环后的代码
 * - 只影响最近的一层循环
 * 
 * continue：
 * - 跳过本次循环
 * - 继续下一次循环
 * - 返回循环开始处
 * 
 * 嵌套循环中的控制：
 * - break只退出当前层循环
 * - 要退出多层循环：
 *   a) 使用标志变量
 *   b) 使用goto（不推荐）
 *   c) 将循环封装在函数中，用return
 * 
 * goto语句的争议：
 * 
 * 不推荐使用的原因：
 * - 破坏程序结构
 * - 难以理解和维护
 * - 容易产生"意大利面条式代码"
 * 
 * 可接受的使用场景：
 * - 从深层嵌套中退出
 * - 统一的错误处理和资源清理
 * - 性能关键的代码（极少数情况）
 * 
 * 注意事项：
 * 1. break和continue只影响最近的循环
 * 2. switch中的break很重要，防止fall through
 * 3. continue在do-while中跳到条件判断
 * 4. goto向前跳转容易形成无限循环
 * 5. goto不能跳入代码块内部
 * 
 * 最佳实践：
 * 1. 优先使用break和continue
 * 2. 避免使用goto，除非有充分理由
 * 3. 使用有意义的标签名（如果使用goto）
 * 4. 为跳转语句添加注释说明原因
 * 5. 考虑用函数return代替复杂的跳转
 * 
 * 替代方案：
 * - 用函数封装，使用return退出
 * - 使用布尔标志变量控制循环
 * - 重新设计循环逻辑
 */
