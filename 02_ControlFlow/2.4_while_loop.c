/*
 * 第二章：控制流程
 * 2.4 while循环 - 条件循环
 * 
 * 学习目标：
 * 1. 掌握while循环的语法和使用
 * 2. 理解while与for的区别
 * 3. 学会使用while处理未知次数的循环
 */

#include <stdio.h>

int main() {
    printf("=== while循环详解 ===\n\n");
    
    // 1. 基本while循环
    printf("1. 基本while循环:\n");
    int count = 1;
    while (count <= 5) {
        printf("%d ", count);
        count++;
    }
    printf("\n\n");
    
    // 2. while循环倒数
    printf("2. 倒数计数:\n");
    int num = 5;
    while (num > 0) {
        printf("%d ", num);
        num--;
    }
    printf("\n\n");
    
    // 3. 使用while计算累加和
    printf("3. 计算1到100的和:\n");
    int i = 1;
    int sum = 0;
    while (i <= 100) {
        sum += i;
        i++;
    }
    printf("1 + 2 + 3 + ... + 100 = %d\n\n", sum);
    
    // 4. while循环读取输入（模拟）
    printf("4. 输入验证示例:\n");
    int password = 0;
    int correct_password = 1234;
    int attempts = 0;
    int max_attempts = 3;
    
    printf("请输入密码（提示：密码是1234）: ");
    scanf("%d", &password);
    attempts++;
    
    while (password != correct_password && attempts < max_attempts) {
        printf("密码错误！还有 %d 次机会\n", max_attempts - attempts);
        printf("请重新输入密码: ");
        scanf("%d", &password);
        attempts++;
    }
    
    if (password == correct_password) {
        printf("密码正确！登录成功\n");
    } else {
        printf("密码错误次数过多，账户已锁定\n");
    }
    printf("\n");
    
    // 5. 数字反转
    printf("5. 数字反转:\n");
    int original = 12345;
    int reversed = 0;
    int temp = original;
    
    printf("原数字: %d\n", original);
    
    while (temp > 0) {
        reversed = reversed * 10 + temp % 10;
        temp /= 10;
    }
    
    printf("反转后: %d\n\n", reversed);
    
    // 6. 求最大公约数（辗转相除法）
    printf("6. 求最大公约数（GCD）:\n");
    int a = 48, b = 18;
    int gcd_a = a, gcd_b = b;
    
    printf("%d 和 %d 的最大公约数: ", a, b);
    
    while (gcd_b != 0) {
        int remainder = gcd_a % gcd_b;
        gcd_a = gcd_b;
        gcd_b = remainder;
    }
    
    printf("%d\n\n", gcd_a);
    
    // 7. 判断回文数
    printf("7. 判断回文数:\n");
    int number = 12321;
    int original_num = number;
    int reversed_num = 0;
    
    // 反转数字
    while (number > 0) {
        reversed_num = reversed_num * 10 + number % 10;
        number /= 10;
    }
    
    if (original_num == reversed_num) {
        printf("%d 是回文数\n", original_num);
    } else {
        printf("%d 不是回文数\n", original_num);
    }
    printf("\n");
    
    // 8. 计算数字位数
    printf("8. 计算数字的位数:\n");
    int value = 123456;
    int digits = 0;
    int temp_val = value;
    
    if (temp_val == 0) {
        digits = 1;
    } else {
        while (temp_val > 0) {
            digits++;
            temp_val /= 10;
        }
    }
    
    printf("数字 %d 有 %d 位\n\n", value, digits);
    
    // 9. 求数字各位之和
    printf("9. 求数字各位之和:\n");
    int n = 12345;
    int digit_sum = 0;
    int temp_n = n;
    
    while (temp_n > 0) {
        digit_sum += temp_n % 10;
        temp_n /= 10;
    }
    
    printf("数字 %d 的各位之和: %d\n", n, digit_sum);
    printf("(1 + 2 + 3 + 4 + 5 = %d)\n\n", digit_sum);
    
    // 10. 猜数字游戏（简化版）
    printf("10. 简化的猜数字游戏:\n");
    int secret_number = 42;
    int guess = 0;
    int guess_count = 0;
    int found = 0;
    
    printf("我想了一个1-100之间的数字（提示：是42）\n");
    
    // 模拟用户猜测
    int guesses[] = {50, 30, 40, 42};
    int guess_index = 0;
    
    while (!found && guess_index < 4) {
        guess = guesses[guess_index++];
        guess_count++;
        printf("第 %d 次猜测: %d\n", guess_count, guess);
        
        if (guess < secret_number) {
            printf("太小了！\n");
        } else if (guess > secret_number) {
            printf("太大了！\n");
        } else {
            printf("恭喜！猜对了！用了 %d 次\n", guess_count);
            found = 1;
        }
    }
    printf("\n");
    
    // 11. 无限循环（需要break跳出）
    printf("11. 无限循环示例:\n");
    int counter = 0;
    
    while (1) {  // 条件永远为真
        printf("循环 %d 次\n", counter + 1);
        counter++;
        
        if (counter >= 3) {
            printf("达到3次，退出循环\n");
            break;
        }
    }
    printf("\n");
    
    // 12. 实际应用：简单菜单系统
    printf("12. 菜单系统示例（模拟）:\n");
    int choice = 0;
    int menu_active = 1;
    
    // 模拟用户选择
    int choices[] = {1, 2, 3, 4};
    int choice_idx = 0;
    
    while (menu_active && choice_idx < 4) {
        printf("\n=== 主菜单 ===\n");
        printf("1. 查看余额\n");
        printf("2. 存款\n");
        printf("3. 取款\n");
        printf("4. 退出\n");
        
        choice = choices[choice_idx++];
        printf("请选择: %d\n", choice);
        
        if (choice == 1) {
            printf("当前余额: 1000.00 元\n");
        } else if (choice == 2) {
            printf("存款成功\n");
        } else if (choice == 3) {
            printf("取款成功\n");
        } else if (choice == 4) {
            printf("感谢使用，再见！\n");
            menu_active = 0;
        } else {
            printf("无效选择，请重试\n");
        }
    }
    
    return 0;
}

/*
 * 知识点总结：
 * 
 * while循环语法：
 * while (条件表达式) {
 *     循环体;
 * }
 * 
 * 执行流程：
 * 1. 判断条件是否为真
 * 2. 如果为真，执行循环体
 * 3. 返回步骤1
 * 4. 如果为假，退出循环
 * 
 * while vs for：
 * 
 * 使用while的情况：
 * - 不知道具体循环次数
 * - 根据某个条件判断是否继续
 * - 处理输入验证
 * - 游戏循环、菜单系统
 * 
 * 使用for的情况：
 * - 循环次数明确
 * - 需要计数器
 * - 遍历数组
 * 
 * 常见应用场景：
 * 1. 输入验证：重复要求用户输入直到正确
 * 2. 数学计算：GCD、反转数字、判断回文
 * 3. 菜单系统：显示菜单直到用户选择退出
 * 4. 游戏循环：游戏未结束就继续
 * 5. 读取数据：直到文件结束或遇到特定标记
 * 
 * 循环控制：
 * - break：立即退出循环
 * - continue：跳过本次循环，进入下一次判断
 * 
 * 注意事项：
 * 1. 确保循环条件最终会变为假，避免死循环
 * 2. 循环体内要有改变条件的语句
 * 3. 初始化循环变量在while之前
 * 4. 小心无限循环 while(1)，必须有break
 * 
 * 常见错误：
 * 1. 忘记更新循环变量，导致死循环
 * 2. 条件写错，导致循环不执行或无限执行
 * 3. 在循环体外访问循环变量（作用域问题）
 * 
 * while与do-while的区别：
 * - while：先判断后执行，可能一次都不执行
 * - do-while：先执行后判断，至少执行一次
 * 
 * 最佳实践：
 * - 循环条件要清晰明确
 * - 避免复杂的循环条件
 * - 循环体要有明确的退出机制
 * - 使用有意义的变量名
 * - 为无限循环添加注释说明
 */
