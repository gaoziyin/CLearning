/*
 * 第二章：控制流程
 * 2.5 do-while循环 - 后测试循环
 * 
 * 学习目标：
 * 1. 掌握do-while循环的语法
 * 2. 理解do-while与while的区别
 * 3. 学会在合适场景使用do-while
 */

#include <stdio.h>

int main() {
    printf("=== do-while循环详解 ===\n\n");
    
    // 1. 基本do-while循环
    printf("1. 基本do-while循环:\n");
    int count = 1;
    
    do {
        printf("%d ", count);
        count++;
    } while (count <= 5);
    printf("\n\n");
    
    // 2. while vs do-while 对比
    printf("2. while vs do-while对比:\n");
    
    // while循环：条件不满足，一次都不执行
    printf("while循环（条件：i < 0）: ");
    int i = 5;
    while (i < 0) {
        printf("%d ", i);  // 不会执行
    }
    printf("未执行\n");
    
    // do-while循环：至少执行一次
    printf("do-while循环（条件：i < 0）: ");
    int j = 5;
    do {
        printf("%d ", j);  // 会执行一次
    } while (j < 0);
    printf("\n\n");
    
    // 3. 使用do-while计算累加和
    printf("3. 计算1到10的和:\n");
    int num = 1;
    int sum = 0;
    
    do {
        sum += num;
        num++;
    } while (num <= 10);
    
    printf("1 + 2 + 3 + ... + 10 = %d\n\n", sum);
    
    // 4. 输入验证（do-while的经典应用）
    printf("4. 输入验证示例:\n");
    int input;
    
    // 模拟用户输入
    int inputs[] = {-5, 0, 15, 8};
    int input_idx = 0;
    
    printf("请输入一个1-10之间的数字:\n");
    do {
        input = inputs[input_idx++];
        printf("输入: %d\n", input);
        
        if (input < 1 || input > 10) {
            printf("输入无效！请输入1-10之间的数字\n");
        }
    } while (input < 1 || input > 10);
    
    printf("有效输入: %d\n\n", input);
    
    // 5. 菜单驱动程序
    printf("5. 菜单驱动程序示例:\n");
    int choice;
    
    // 模拟用户选择
    int menu_choices[] = {1, 2, 3};
    int menu_idx = 0;
    
    do {
        printf("\n=== 计算器菜单 ===\n");
        printf("1. 加法\n");
        printf("2. 减法\n");
        printf("3. 退出\n");
        
        choice = menu_choices[menu_idx++];
        printf("请选择: %d\n", choice);
        
        if (choice == 1) {
            printf("执行加法: 5 + 3 = 8\n");
        } else if (choice == 2) {
            printf("执行减法: 5 - 3 = 2\n");
        } else if (choice == 3) {
            printf("退出程序\n");
        } else {
            printf("无效选择\n");
        }
    } while (choice != 3 && menu_idx < 3);
    printf("\n");
    
    // 6. 数字游戏
    printf("6. 求和游戏:\n");
    int number = 0;
    int total = 0;
    
    // 模拟输入序列
    int numbers[] = {5, 10, 15, 0};
    int num_idx = 0;
    
    printf("输入数字相加，输入0结束:\n");
    do {
        number = numbers[num_idx++];
        printf("输入: %d\n", number);
        total += number;
    } while (number != 0 && num_idx < 4);
    
    printf("总和: %d\n\n", total);
    
    // 7. 密码验证
    printf("7. 密码验证（至少尝试一次）:\n");
    char password[20];
    int attempts = 0;
    int max_tries = 3;
    int authenticated = 0;
    const char* correct_pwd = "abc123";
    
    // 模拟密码输入
    const char* pwd_attempts[] = {"wrong", "bad", "abc123"};
    int pwd_idx = 0;
    
    do {
        attempts++;
        const char* pwd = pwd_attempts[pwd_idx++];
        printf("第 %d 次尝试，输入密码: %s\n", attempts, pwd);
        
        // 简化的字符串比较（实际应该用strcmp）
        int match = 1;
        for (int i = 0; pwd[i] != '\0' || correct_pwd[i] != '\0'; i++) {
            if (pwd[i] != correct_pwd[i]) {
                match = 0;
                break;
            }
        }
        
        if (match) {
            printf("密码正确！\n");
            authenticated = 1;
        } else {
            printf("密码错误！\n");
        }
    } while (!authenticated && attempts < max_tries && pwd_idx < 3);
    
    if (!authenticated) {
        printf("超过最大尝试次数\n");
    }
    printf("\n");
    
    // 8. 计算阶乘
    printf("8. 计算阶乘:\n");
    int n = 5;
    long factorial = 1;
    int factor = 1;
    
    do {
        factorial *= factor;
        factor++;
    } while (factor <= n);
    
    printf("%d! = %ld\n\n", n, factorial);
    
    // 9. 倒序输出
    printf("9. 倒序输出数字:\n");
    int original = 12345;
    printf("原数字: %d\n", original);
    printf("倒序输出: ");
    
    do {
        printf("%d", original % 10);
        original /= 10;
    } while (original > 0);
    printf("\n\n");
    
    // 10. 生成随机数直到满足条件（模拟）
    printf("10. 模拟随机数生成:\n");
    int random_nums[] = {3, 7, 2, 9, 5};
    int rand_idx = 0;
    int target = 5;
    int random;
    
    printf("生成随机数直到得到 %d:\n", target);
    do {
        random = random_nums[rand_idx++];
        printf("生成: %d\n", random);
    } while (random != target && rand_idx < 5);
    
    if (random == target) {
        printf("找到目标数字 %d!\n", target);
    }
    printf("\n");
    
    // 11. 字符处理
    printf("11. 字符处理示例:\n");
    char chars[] = {'A', 'B', 'C', 'D', '\0'};
    int char_idx = 0;
    char ch;
    
    printf("输出字符直到遇到空字符:\n");
    do {
        ch = chars[char_idx++];
        if (ch != '\0') {
            printf("%c ", ch);
        }
    } while (ch != '\0');
    printf("\n\n");
    
    // 12. 实际应用：ATM机界面
    printf("12. ATM机界面模拟:\n");
    float balance = 1000.0;
    int atm_choice;
    int atm_active = 1;
    
    // 模拟ATM操作
    int atm_operations[] = {1, 2, 3, 4};
    int atm_idx = 0;
    
    do {
        printf("\n=== ATM机 ===\n");
        printf("1. 查询余额\n");
        printf("2. 存款\n");
        printf("3. 取款\n");
        printf("4. 退出\n");
        printf("当前余额: %.2f 元\n", balance);
        
        atm_choice = atm_operations[atm_idx++];
        printf("选择操作: %d\n", atm_choice);
        
        switch (atm_choice) {
            case 1:
                printf("余额: %.2f 元\n", balance);
                break;
            case 2:
                printf("存入 500 元\n");
                balance += 500;
                printf("新余额: %.2f 元\n", balance);
                break;
            case 3:
                printf("取出 200 元\n");
                if (balance >= 200) {
                    balance -= 200;
                    printf("新余额: %.2f 元\n", balance);
                } else {
                    printf("余额不足\n");
                }
                break;
            case 4:
                printf("感谢使用，再见！\n");
                atm_active = 0;
                break;
            default:
                printf("无效选择\n");
        }
    } while (atm_active && atm_idx < 4);
    
    return 0;
}

/*
 * 知识点总结：
 * 
 * do-while循环语法：
 * do {
 *     循环体;
 * } while (条件表达式);
 * 
 * 执行流程：
 * 1. 先执行循环体
 * 2. 再判断条件
 * 3. 如果条件为真，返回步骤1
 * 4. 如果条件为假，退出循环
 * 
 * 关键特点：
 * - 至少执行一次循环体
 * - 后测试循环（先执行后判断）
 * - 循环体在条件检查之前执行
 * 
 * while vs do-while：
 * 
 * while循环：
 * - 先判断条件，再执行
 * - 可能一次都不执行
 * - 适合：循环次数可能为0的情况
 * 
 * do-while循环：
 * - 先执行，再判断条件
 * - 至少执行一次
 * - 适合：需要至少执行一次的情况
 * 
 * 适用场景：
 * 1. 菜单驱动程序
 *    - 至少显示一次菜单
 *    - 用户选择退出才结束
 * 
 * 2. 输入验证
 *    - 至少尝试输入一次
 *    - 输入无效时重复要求输入
 * 
 * 3. 游戏循环
 *    - 游戏至少运行一次
 *    - 直到游戏结束
 * 
 * 4. 用户交互
 *    - 必须至少执行一次的操作
 *    - ATM、点餐系统等
 * 
 * 语法要点：
 * 1. 循环体后的 while(条件); 不要忘记分号
 * 2. 条件表达式的括号必须有
 * 3. 循环体用花括号括起来（推荐）
 * 
 * 循环控制：
 * - break：立即退出循环
 * - continue：跳过剩余语句，进入条件判断
 * 
 * 注意事项：
 * 1. 不要忘记while后的分号
 * 2. 确保循环体内有改变条件的代码
 * 3. 避免死循环，确保条件最终为假
 * 4. 循环变量的初始化在do之前
 * 
 * 常见错误：
 * 1. 忘记while后的分号：
 *    do { ... } while (条件)  // 错误
 *    do { ... } while (条件); // 正确
 * 
 * 2. 条件永远为真导致死循环
 * 3. 循环变量未初始化
 * 
 * 最佳实践：
 * - 当需要"至少执行一次"时使用do-while
 * - 菜单程序优先考虑do-while
 * - 输入验证场景使用do-while
 * - 条件表达式要清晰
 * - 为循环添加注释说明用途
 */
