/*
 * 第二章：控制流程
 * 2.2 switch语句 - 多分支选择
 * 
 * 学习目标：
 * 1. 掌握switch语句的语法
 * 2. 理解break的作用
 * 3. 学会default的使用
 */

#include <stdio.h>

int main() {
    printf("=== switch多分支语句详解 ===\n\n");
    
    // 1. 基本switch语句
    printf("1. 基本switch语句:\n");
    int day = 3;
    
    switch (day) {
        case 1:
            printf("星期一\n");
            break;
        case 2:
            printf("星期二\n");
            break;
        case 3:
            printf("星期三\n");
            break;
        case 4:
            printf("星期四\n");
            break;
        case 5:
            printf("星期五\n");
            break;
        case 6:
            printf("星期六\n");
            break;
        case 7:
            printf("星期日\n");
            break;
        default:
            printf("无效的日期\n");
            break;
    }
    printf("\n");
    
    // 2. 使用字符作为case标签
    printf("2. 字符类型的switch:\n");
    char grade = 'B';
    
    switch (grade) {
        case 'A':
            printf("优秀！成绩90-100分\n");
            break;
        case 'B':
            printf("良好！成绩80-89分\n");
            break;
        case 'C':
            printf("中等！成绩70-79分\n");
            break;
        case 'D':
            printf("及格！成绩60-69分\n");
            break;
        case 'F':
            printf("不及格！成绩60分以下\n");
            break;
        default:
            printf("无效的等级\n");
            break;
    }
    printf("\n");
    
    // 3. 没有break的情况（fall through）
    printf("3. 没有break的情况:\n");
    int month = 3;
    
    switch (month) {
        case 12:
        case 1:
        case 2:
            printf("月份 %d: 冬季\n", month);
            break;
        case 3:
        case 4:
        case 5:
            printf("月份 %d: 春季\n", month);
            break;
        case 6:
        case 7:
        case 8:
            printf("月份 %d: 夏季\n", month);
            break;
        case 9:
        case 10:
        case 11:
            printf("月份 %d: 秋季\n", month);
            break;
        default:
            printf("无效的月份\n");
            break;
    }
    printf("\n");
    
    // 4. 嵌套switch语句
    printf("4. 嵌套switch语句:\n");
    char category = 'A';
    int level = 2;
    
    switch (category) {
        case 'A':
            printf("类别: A\n");
            switch (level) {
                case 1:
                    printf("等级: A1\n");
                    break;
                case 2:
                    printf("等级: A2\n");
                    break;
                case 3:
                    printf("等级: A3\n");
                    break;
                default:
                    printf("无效的等级\n");
            }
            break;
        case 'B':
            printf("类别: B\n");
            break;
        default:
            printf("无效的类别\n");
    }
    printf("\n");
    
    // 5. switch与if-else的对比
    printf("5. switch vs if-else:\n");
    int number = 2;
    
    // 使用switch
    printf("使用switch: ");
    switch (number) {
        case 1:
            printf("一\n");
            break;
        case 2:
            printf("二\n");
            break;
        case 3:
            printf("三\n");
            break;
        default:
            printf("其他\n");
    }
    
    // 使用if-else (等价)
    printf("使用if-else: ");
    if (number == 1) {
        printf("一\n");
    } else if (number == 2) {
        printf("二\n");
    } else if (number == 3) {
        printf("三\n");
    } else {
        printf("其他\n");
    }
    printf("\n");
    
    // 6. 实际应用：计算器
    printf("6. 实际应用 - 简单计算器:\n");
    float num1 = 10, num2 = 5;
    char operator = '*';
    float result;
    
    printf("计算: %.1f %c %.1f\n", num1, operator, num2);
    
    switch (operator) {
        case '+':
            result = num1 + num2;
            printf("结果: %.2f\n", result);
            break;
        case '-':
            result = num1 - num2;
            printf("结果: %.2f\n", result);
            break;
        case '*':
            result = num1 * num2;
            printf("结果: %.2f\n", result);
            break;
        case '/':
            if (num2 != 0) {
                result = num1 / num2;
                printf("结果: %.2f\n", result);
            } else {
                printf("错误: 除数不能为0\n");
            }
            break;
        case '%':
            printf("结果: %d\n", (int)num1 % (int)num2);
            break;
        default:
            printf("错误: 不支持的运算符\n");
    }
    printf("\n");
    
    // 7. 实际应用：菜单系统
    printf("7. 实际应用 - 菜单系统:\n");
    int choice = 2;
    
    printf("=== 主菜单 ===\n");
    printf("1. 新建文件\n");
    printf("2. 打开文件\n");
    printf("3. 保存文件\n");
    printf("4. 退出\n");
    printf("请选择: %d\n", choice);
    
    switch (choice) {
        case 1:
            printf("执行: 新建文件\n");
            // 这里可以调用新建文件的函数
            break;
        case 2:
            printf("执行: 打开文件\n");
            // 这里可以调用打开文件的函数
            break;
        case 3:
            printf("执行: 保存文件\n");
            // 这里可以调用保存文件的函数
            break;
        case 4:
            printf("退出程序\n");
            // return 0; // 退出程序
            break;
        default:
            printf("无效的选择，请重新选择\n");
    }
    printf("\n");
    
    // 8. 实际应用：月份天数
    printf("8. 实际应用 - 计算月份天数:\n");
    int year = 2024;
    int mon = 2;
    int days;
    
    switch (mon) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            days = 31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            days = 30;
            break;
        case 2:
            // 判断闰年
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
                days = 29;
            } else {
                days = 28;
            }
            break;
        default:
            days = 0;
            printf("无效的月份\n");
    }
    
    if (days > 0) {
        printf("%d年%d月有%d天\n", year, mon, days);
    }
    
    return 0;
}

/*
 * 知识点总结：
 * 
 * switch语句语法：
 * switch (表达式) {
 *     case 常量1:
 *         语句块1;
 *         break;
 *     case 常量2:
 *         语句块2;
 *         break;
 *     ...
 *     default:
 *         默认语句块;
 *         break;
 * }
 * 
 * 关键要点：
 * 1. 表达式必须是整型或字符型
 * 2. case标签必须是常量表达式
 * 3. case标签的值必须唯一
 * 4. break语句用于跳出switch
 * 5. default子句是可选的，用于处理所有其他情况
 * 6. 没有break会继续执行下一个case（fall through）
 * 
 * switch vs if-else：
 * 
 * 使用switch的情况：
 * - 判断一个变量等于多个常量值中的某一个
 * - case标签值是固定的常量
 * - 代码更清晰，执行效率可能更高
 * 
 * 使用if-else的情况：
 * - 需要判断范围（如 x > 10）
 * - 需要复杂的条件表达式
 * - 需要判断浮点数
 * - 条件表达式不是简单的相等比较
 * 
 * fall through特性：
 * - 当case没有break时，会继续执行下一个case
 * - 可以用于多个case共享同一段代码
 * - 要谨慎使用，避免意外错误
 * 
 * 注意事项：
 * 1. 不要忘记break语句
 * 2. default放在最后（虽然位置任意）
 * 3. 每个case只能是单个常量值
 * 4. 不能用变量作为case标签
 * 5. 可以在case中声明变量，但要用花括号
 * 
 * 最佳实践：
 * - 总是包含default子句
 * - 每个case都要有break（除非有意fall through）
 * - 合理利用fall through特性处理多个相同的情况
 * - 复杂判断优先考虑if-else
 */
