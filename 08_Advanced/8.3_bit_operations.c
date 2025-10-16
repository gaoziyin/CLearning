/*
 * 第八章：高级主题
 * 8.3 位操作
 * 
 * 学习目标：
 * 1. 理解位运算的概念
 * 2. 掌握位运算符的使用
 * 3. 学习位操作的应用技巧
 * 4. 了解位域和位掩码
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 打印二进制表示
void printBinary(unsigned int num) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i % 8 == 0 && i != 0) printf(" ");
    }
    printf("\n");
}

// 打印字节的二进制
void printByte(unsigned char byte) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (byte >> i) & 1);
    }
}

// 权限标志
#define READ    0x01   // 0001
#define WRITE   0x02   // 0010
#define EXECUTE 0x04   // 0100
#define DELETE  0x08   // 1000

// 状态标志
typedef enum {
    FLAG_A = 1 << 0,   // 0001
    FLAG_B = 1 << 1,   // 0010
    FLAG_C = 1 << 2,   // 0100
    FLAG_D = 1 << 3    // 1000
} Flags;

// 位域结构体
typedef struct {
    unsigned int flag1 : 1;
    unsigned int flag2 : 1;
    unsigned int value : 6;
    unsigned int reserved : 24;
} BitField;

// 日期位域（节省空间）
typedef struct {
    unsigned int day : 5;    // 1-31
    unsigned int month : 4;  // 1-12
    unsigned int year : 12;  // 0-4095
} CompactDate;

int main() {
    printf("=== 位操作 ===\n\n");
    
    // 1. 位运算符概览
    printf("1. 位运算符:\n");
    printf("&  按位与\n");
    printf("|  按位或\n");
    printf("^  按位异或\n");
    printf("~  按位取反\n");
    printf("<< 左移\n");
    printf(">> 右移\n\n");
    
    // 2. 按位与 &
    printf("2. 按位与 & (都为1才为1):\n");
    unsigned char a = 0b11001100;  // 204
    unsigned char b = 0b10101010;  // 170
    
    printf("a = ");
    printByte(a);
    printf(" (%u)\n", a);
    
    printf("b = ");
    printByte(b);
    printf(" (%u)\n", b);
    
    printf("a & b = ");
    printByte(a & b);
    printf(" (%u)\n\n", a & b);
    
    // 3. 按位或 |
    printf("3. 按位或 | (有1就为1):\n");
    printf("a | b = ");
    printByte(a | b);
    printf(" (%u)\n\n", a | b);
    
    // 4. 按位异或 ^
    printf("4. 按位异或 ^ (不同为1):\n");
    printf("a ^ b = ");
    printByte(a ^ b);
    printf(" (%u)\n\n", a ^ b);
    
    // 5. 按位取反 ~
    printf("5. 按位取反 ~ (0变1, 1变0):\n");
    unsigned char c = 0b00001111;  // 15
    printf("c = ");
    printByte(c);
    printf(" (%u)\n", c);
    
    printf("~c = ");
    printByte(~c);
    printf(" (%u)\n\n", (unsigned char)~c);
    
    // 6. 左移 <<
    printf("6. 左移 << (左移n位，右边补0):\n");
    unsigned char d = 0b00000101;  // 5
    printf("d = ");
    printByte(d);
    printf(" (%u)\n", d);
    
    printf("d << 1 = ");
    printByte(d << 1);
    printf(" (%u)\n", d << 1);
    
    printf("d << 2 = ");
    printByte(d << 2);
    printf(" (%u)\n", d << 2);
    
    printf("左移1位相当于乘以2\n\n");
    
    // 7. 右移 >>
    printf("7. 右移 >> (右移n位，左边补0或补符号位):\n");
    unsigned char e = 0b10100000;  // 160
    printf("e = ");
    printByte(e);
    printf(" (%u)\n", e);
    
    printf("e >> 1 = ");
    printByte(e >> 1);
    printf(" (%u)\n", e >> 1);
    
    printf("e >> 2 = ");
    printByte(e >> 2);
    printf(" (%u)\n", e >> 2);
    
    printf("右移1位相当于除以2\n\n");
    
    // 8. 设置位（置1）
    printf("8. 设置位（置1）:\n");
    unsigned char flags = 0b00000000;
    int pos = 3;
    
    printf("原始: ");
    printByte(flags);
    printf("\n");
    
    flags |= (1 << pos);  // 设置第3位
    printf("设置第%d位后: ", pos);
    printByte(flags);
    printf("\n\n");
    
    // 9. 清除位（置0）
    printf("9. 清除位（置0）:\n");
    flags = 0b11111111;
    printf("原始: ");
    printByte(flags);
    printf("\n");
    
    flags &= ~(1 << pos);  // 清除第3位
    printf("清除第%d位后: ", pos);
    printByte(flags);
    printf("\n\n");
    
    // 10. 切换位（反转）
    printf("10. 切换位（反转）:\n");
    flags = 0b01010101;
    printf("原始: ");
    printByte(flags);
    printf("\n");
    
    flags ^= (1 << pos);  // 切换第3位
    printf("切换第%d位后: ", pos);
    printByte(flags);
    printf("\n\n");
    
    // 11. 检查位
    printf("11. 检查位:\n");
    flags = 0b00101100;
    printf("flags = ");
    printByte(flags);
    printf("\n");
    
    for (int i = 0; i < 8; i++) {
        int bit = (flags >> i) & 1;
        printf("第%d位: %d\n", i, bit);
    }
    printf("\n");
    
    // 12. 权限管理
    printf("12. 权限管理示例:\n");
    unsigned char permissions = 0;
    
    // 设置权限
    permissions |= READ;
    permissions |= WRITE;
    
    printf("当前权限: ");
    printByte(permissions);
    printf("\n");
    
    // 检查权限
    if (permissions & READ) {
        printf("有读权限\n");
    }
    if (permissions & WRITE) {
        printf("有写权限\n");
    }
    if (permissions & EXECUTE) {
        printf("有执行权限\n");
    } else {
        printf("无执行权限\n");
    }
    
    // 移除权限
    permissions &= ~WRITE;
    printf("\n移除写权限后: ");
    printByte(permissions);
    printf("\n\n");
    
    // 13. 多标志管理
    printf("13. 多标志管理:\n");
    unsigned int state = 0;
    
    // 设置多个标志
    state |= FLAG_A | FLAG_C;
    
    printf("state = 0x%02X\n", state);
    printf("FLAG_A: %s\n", (state & FLAG_A) ? "开" : "关");
    printf("FLAG_B: %s\n", (state & FLAG_B) ? "开" : "关");
    printf("FLAG_C: %s\n", (state & FLAG_C) ? "开" : "关");
    printf("FLAG_D: %s\n", (state & FLAG_D) ? "开" : "关");
    printf("\n");
    
    // 14. 交换两数（无需临时变量）
    printf("14. 异或交换技巧:\n");
    int x = 10, y = 20;
    printf("交换前: x=%d, y=%d\n", x, y);
    
    x ^= y;
    y ^= x;
    x ^= y;
    
    printf("交换后: x=%d, y=%d\n\n", x, y);
    
    // 15. 判断奇偶
    printf("15. 判断奇偶:\n");
    for (int i = 0; i < 5; i++) {
        if (i & 1) {
            printf("%d 是奇数\n", i);
        } else {
            printf("%d 是偶数\n", i);
        }
    }
    printf("\n");
    
    // 16. 乘除2的幂
    printf("16. 快速乘除2的幂:\n");
    int num = 5;
    printf("原始值: %d\n", num);
    printf("乘以2 (左移1): %d\n", num << 1);
    printf("乘以4 (左移2): %d\n", num << 2);
    printf("乘以8 (左移3): %d\n", num << 3);
    
    num = 40;
    printf("\n原始值: %d\n", num);
    printf("除以2 (右移1): %d\n", num >> 1);
    printf("除以4 (右移2): %d\n", num >> 2);
    printf("除以8 (右移3): %d\n", num >> 3);
    printf("\n");
    
    // 17. 统计1的个数
    printf("17. 统计1的个数:\n");
    unsigned int value = 0b11010101;
    int count = 0;
    unsigned int temp = value;
    
    while (temp) {
        count += temp & 1;
        temp >>= 1;
    }
    
    printf("数值: ");
    printByte(value);
    printf("\n1的个数: %d\n\n", count);
    
    // 18. 判断2的幂
    printf("18. 判断是否为2的幂:\n");
    int numbers[] = {1, 2, 3, 4, 5, 8, 15, 16, 32};
    
    for (int i = 0; i < 9; i++) {
        int n = numbers[i];
        // 2的幂只有一个1，n & (n-1) == 0
        if (n > 0 && (n & (n - 1)) == 0) {
            printf("%d 是2的幂\n", n);
        } else {
            printf("%d 不是2的幂\n", n);
        }
    }
    printf("\n");
    
    // 19. 位域结构体
    printf("19. 位域结构体:\n");
    BitField bf;
    bf.flag1 = 1;
    bf.flag2 = 0;
    bf.value = 42;
    bf.reserved = 0;
    
    printf("sizeof(BitField) = %zu 字节\n", sizeof(BitField));
    printf("flag1 = %u\n", bf.flag1);
    printf("flag2 = %u\n", bf.flag2);
    printf("value = %u\n", bf.value);
    printf("\n");
    
    // 20. 压缩日期
    printf("20. 压缩日期存储:\n");
    CompactDate date;
    date.year = 2024;
    date.month = 10;
    date.day = 15;
    
    printf("sizeof(CompactDate) = %zu 字节\n", sizeof(CompactDate));
    printf("日期: %04u-%02u-%02u\n", date.year, date.month, date.day);
    printf("\n对比普通结构体（12字节）节省空间\n\n");
    
    // 21. 提取字节
    printf("21. 提取和组合字节:\n");
    unsigned int color = 0x12345678;
    
    printf("颜色值: 0x%08X\n", color);
    printf("字节0: 0x%02X\n", (color >> 0) & 0xFF);
    printf("字节1: 0x%02X\n", (color >> 8) & 0xFF);
    printf("字节2: 0x%02X\n", (color >> 16) & 0xFF);
    printf("字节3: 0x%02X\n", (color >> 24) & 0xFF);
    printf("\n");
    
    // 22. 组合字节
    printf("22. 组合字节为整数:\n");
    unsigned char b1 = 0x12, b2 = 0x34, b3 = 0x56, b4 = 0x78;
    unsigned int combined = (b4 << 24) | (b3 << 16) | (b2 << 8) | b1;
    printf("组合结果: 0x%08X\n\n", combined);
    
    // 23. 位掩码
    printf("23. 位掩码技巧:\n");
    unsigned int status = 0xABCD;
    unsigned int mask = 0x00FF;
    
    printf("状态: 0x%04X\n", status);
    printf("掩码: 0x%04X\n", mask);
    printf("提取低8位: 0x%02X\n", status & mask);
    
    mask = 0xFF00;
    printf("提取高8位: 0x%02X\n", (status & mask) >> 8);
    printf("\n");
    
    // 24. 循环移位
    printf("24. 循环左移:\n");
    unsigned char val = 0b10110001;
    printf("原始: ");
    printByte(val);
    printf("\n");
    
    // 循环左移1位
    unsigned char rotated = (val << 1) | (val >> 7);
    printf("循环左移1位: ");
    printByte(rotated);
    printf("\n\n");
    
    // 25. 位操作应用总结
    printf("25. 位操作应用总结:\n");
    printf("常见应用:\n");
    printf("1. 权限管理\n");
    printf("2. 标志位控制\n");
    printf("3. 数据压缩\n");
    printf("4. 快速计算\n");
    printf("5. 硬件编程\n");
    printf("6. 图形处理\n");
    printf("7. 网络协议\n");
    printf("8. 加密算法\n");
    printf("9. 位图操作\n");
    printf("10. 状态机\n");
    
    return 0;
}

/*
 * 知识点总结：
 * 
 * 位运算符：
 * 
 * & (按位与)：
 * - 两位都为1，结果为1
 * - 否则为0
 * - 用途：清零、提取、掩码
 * 
 * | (按位或)：
 * - 两位有一个为1，结果为1
 * - 都为0时为0
 * - 用途：置位、合并
 * 
 * ^ (按位异或)：
 * - 两位相同为0，不同为1
 * - 用途：切换、交换、加密
 * 
 * ~ (按位取反)：
 * - 0变1，1变0
 * - 用途：取反、生成掩码
 * 
 * << (左移)：
 * - 左移n位，右边补0
 * - 相当于乘以2^n
 * - 用途：快速乘法、置位
 * 
 * >> (右移)：
 * - 右移n位
 * - 无符号数：左边补0
 * - 有符号数：左边补符号位
 * - 相当于除以2^n
 * - 用途：快速除法、提取位
 * 
 * 基本位操作：
 * 
 * 设置位（置1）：
 * value |= (1 << n)
 * 
 * 清除位（置0）：
 * value &= ~(1 << n)
 * 
 * 切换位（反转）：
 * value ^= (1 << n)
 * 
 * 检查位：
 * if (value & (1 << n))
 * 
 * 提取位：
 * bit = (value >> n) & 1
 * 
 * 位掩码：
 * 
 * 概念：
 * - 用于提取或屏蔽特定位
 * - 通常用十六进制表示
 * 
 * 示例：
 * 0xFF (11111111) - 低8位掩码
 * 0x0F (00001111) - 低4位掩码
 * 0xF0 (11110000) - 高4位掩码
 * 
 * 用法：
 * low_byte = value & 0xFF
 * high_byte = (value >> 8) & 0xFF
 * 
 * 标志位管理：
 * 
 * 定义标志：
 * #define FLAG_A 0x01  // 00000001
 * #define FLAG_B 0x02  // 00000010
 * #define FLAG_C 0x04  // 00000100
 * 
 * 或使用枚举：
 * enum {
 *     FLAG_A = 1 << 0,
 *     FLAG_B = 1 << 1,
 *     FLAG_C = 1 << 2
 * };
 * 
 * 设置多个标志：
 * flags |= FLAG_A | FLAG_B;
 * 
 * 清除标志：
 * flags &= ~FLAG_A;
 * 
 * 检查标志：
 * if (flags & FLAG_A)
 * 
 * 位域：
 * 
 * 定义：
 * struct BitField {
 *     unsigned int flag1 : 1;  // 1位
 *     unsigned int flag2 : 1;  // 1位
 *     unsigned int value : 6;  // 6位
 * };
 * 
 * 优点：
 * - 节省空间
 * - 语法清晰
 * - 自动位操作
 * 
 * 缺点：
 * - 不可移植（位序）
 * - 不能取地址
 * - 访问可能较慢
 * 
 * 快速运算技巧：
 * 
 * 乘以2的幂：
 * x * 2 = x << 1
 * x * 4 = x << 2
 * x * 8 = x << 3
 * 
 * 除以2的幂：
 * x / 2 = x >> 1
 * x / 4 = x >> 2
 * x / 8 = x >> 3
 * 
 * 判断奇偶：
 * if (x & 1) // 奇数
 * 
 * 判断2的幂：
 * if ((x & (x-1)) == 0) // 2的幂
 * 
 * 交换变量：
 * a ^= b;
 * b ^= a;
 * a ^= b;
 * 
 * 常见技巧：
 * 
 * 统计1的个数：
 * while (n) {
 *     count += n & 1;
 *     n >>= 1;
 * }
 * 
 * 反转位：
 * while (n) {
 *     reversed = (reversed << 1) | (n & 1);
 *     n >>= 1;
 * }
 * 
 * 获取最低位1：
 * lowest = n & (-n)
 * 
 * 清除最低位1：
 * n &= (n - 1)
 * 
 * 提取和组合字节：
 * 
 * 提取：
 * byte0 = (value >> 0) & 0xFF
 * byte1 = (value >> 8) & 0xFF
 * byte2 = (value >> 16) & 0xFF
 * byte3 = (value >> 24) & 0xFF
 * 
 * 组合：
 * value = (b3 << 24) | (b2 << 16) | (b1 << 8) | b0
 * 
 * 应用场景：
 * 
 * 1. 权限系统：
 *    - 读、写、执行权限
 *    - Unix文件权限
 * 
 * 2. 配置选项：
 *    - 功能开关
 *    - 状态标志
 * 
 * 3. 图形编程：
 *    - RGB颜色值
 *    - 像素操作
 * 
 * 4. 网络编程：
 *    - 协议标志
 *    - 数据打包
 * 
 * 5. 硬件编程：
 *    - 寄存器操作
 *    - 端口控制
 * 
 * 6. 数据压缩：
 *    - 位打包
 *    - 紧凑存储
 * 
 * 7. 加密算法：
 *    - 位运算加密
 *    - 散列函数
 * 
 * 注意事项：
 * 
 * 1. 有符号数右移：
 *    - 可能填充符号位
 *    - 结果取决于编译器
 *    - 使用unsigned避免
 * 
 * 2. 移位溢出：
 *    - 移位数不能大于类型位数
 *    - 未定义行为
 * 
 * 3. 优先级：
 *    - 位运算优先级较低
 *    - 需要括号
 *    - (x & mask) == 0
 * 
 * 4. 可读性：
 *    - 添加注释
 *    - 使用宏
 *    - 避免过度优化
 * 
 * 最佳实践：
 * 
 * 1. 使用unsigned进行位操作
 * 2. 定义有意义的宏
 * 3. 添加注释说明
 * 4. 使用枚举定义标志
 * 5. 检查移位范围
 * 6. 考虑可移植性
 * 7. 性能优化时才用
 * 8. 保持代码可读
 * 
 * 调试技巧：
 * 
 * 1. 打印二进制
 * 2. 使用十六进制
 * 3. 单步测试
 * 4. 验证每一步
 * 5. 使用位可视化工具
 * 
 * 性能考虑：
 * 
 * - 位运算非常快
 * - 适合性能关键代码
 * - 但要权衡可读性
 * - 现代编译器会优化
 */
