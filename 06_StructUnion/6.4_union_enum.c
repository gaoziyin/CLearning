/*
 * 第六章：结构体与联合体
 * 6.4 联合体与枚举
 * 
 * 学习目标：
 * 1. 理解联合体的概念和用途
 * 2. 掌握联合体与结构体的区别
 * 3. 学会枚举类型的使用
 * 4. 了解位字段的基本用法
 */

#include <stdio.h>
#include <string.h>

// 1. 联合体定义
union Data {
    int intVal;
    float floatVal;
    char str[20];
};

// 2. 联合体应用 - 数据转换
union Converter {
    int integer;
    float floatingPoint;
    char bytes[4];
};

// 3. 结构体与联合体结合
struct Packet {
    int type;  // 数据类型标识
    union {
        int intData;
        float floatData;
        char strData[50];
    } data;
};

// 4. 枚举类型 - 星期
enum Weekday {
    MONDAY,     // 0
    TUESDAY,    // 1
    WEDNESDAY,  // 2
    THURSDAY,   // 3
    FRIDAY,     // 4
    SATURDAY,   // 5
    SUNDAY      // 6
};

// 5. 枚举 - 指定值
enum ErrorCode {
    SUCCESS = 0,
    ERROR_FILE_NOT_FOUND = 100,
    ERROR_PERMISSION_DENIED = 101,
    ERROR_OUT_OF_MEMORY = 102,
    ERROR_INVALID_INPUT = 103
};

// 6. 枚举 - 颜色
enum Color {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    BLACK,
    WHITE
};

// 7. 结构体中使用枚举
enum Status {
    ACTIVE,
    INACTIVE,
    PENDING,
    SUSPENDED
};

struct Account {
    int id;
    char username[50];
    enum Status status;
};

// 8. 位字段（节省内存）
struct Flags {
    unsigned int isActive : 1;    // 1位
    unsigned int isAdmin : 1;     // 1位
    unsigned int hasEmail : 1;    // 1位
    unsigned int reserved : 5;    // 5位保留
};

// 9. 复杂的位字段应用
struct Date {
    unsigned int day : 5;      // 1-31 (5位足够)
    unsigned int month : 4;    // 1-12 (4位足够)
    unsigned int year : 12;    // 0-4095 (12位)
};

int main() {
    printf("=== 联合体与枚举 ===\n\n");
    
    // 1. 联合体基础
    printf("1. 联合体基础:\n");
    union Data data;
    
    printf("联合体大小: %zu 字节\n", sizeof(union Data));
    printf("（等于最大成员的大小）\n\n");
    
    // 2. 联合体使用 - 同一时间只能使用一个成员
    printf("2. 联合体的使用:\n");
    
    data.intVal = 42;
    printf("存储整数: %d\n", data.intVal);
    
    data.floatVal = 3.14;
    printf("存储浮点数: %.2f\n", data.floatVal);
    printf("此时整数值被覆盖: %d (垃圾值)\n", data.intVal);
    
    strcpy(data.str, "Hello");
    printf("存储字符串: %s\n", data.str);
    printf("此时浮点数被覆盖: %.2f (垃圾值)\n\n", data.floatVal);
    
    // 3. 联合体的内存共享
    printf("3. 联合体内存共享演示:\n");
    union Data d;
    
    d.intVal = 0x12345678;
    printf("整数值: 0x%X\n", d.intVal);
    printf("字符串（前4字节）: ");
    for (int i = 0; i < 4; i++) {
        printf("%02X ", (unsigned char)d.str[i]);
    }
    printf("\n\n");
    
    // 4. 类型转换器
    printf("4. 联合体应用 - 数据转换:\n");
    union Converter conv;
    
    conv.floatingPoint = 3.14159;
    printf("浮点数: %.5f\n", conv.floatingPoint);
    printf("内部表示（字节）: ");
    for (int i = 0; i < 4; i++) {
        printf("%02X ", (unsigned char)conv.bytes[i]);
    }
    printf("\n\n");
    
    // 5. 带标识的联合体
    printf("5. 带类型标识的联合体:\n");
    
    struct Packet packet1;
    packet1.type = 1;  // 整数类型
    packet1.data.intData = 100;
    
    struct Packet packet2;
    packet2.type = 2;  // 浮点类型
    packet2.data.floatData = 3.14;
    
    struct Packet packet3;
    packet3.type = 3;  // 字符串类型
    strcpy(packet3.data.strData, "Hello World");
    
    // 根据类型读取数据
    printf("数据包1 (类型%d): %d\n", packet1.type, packet1.data.intData);
    printf("数据包2 (类型%d): %.2f\n", packet2.type, packet2.data.floatData);
    printf("数据包3 (类型%d): %s\n\n", packet3.type, packet3.data.strData);
    
    // 6. 枚举类型基础
    printf("6. 枚举类型基础:\n");
    enum Weekday today = FRIDAY;
    
    printf("今天是: ");
    switch (today) {
        case MONDAY: printf("星期一"); break;
        case TUESDAY: printf("星期二"); break;
        case WEDNESDAY: printf("星期三"); break;
        case THURSDAY: printf("星期四"); break;
        case FRIDAY: printf("星期五"); break;
        case SATURDAY: printf("星期六"); break;
        case SUNDAY: printf("星期日"); break;
    }
    printf(" (值=%d)\n\n", today);
    
    // 7. 枚举值
    printf("7. 枚举的默认值:\n");
    printf("MONDAY = %d\n", MONDAY);
    printf("TUESDAY = %d\n", TUESDAY);
    printf("FRIDAY = %d\n", FRIDAY);
    printf("SUNDAY = %d\n\n", SUNDAY);
    
    // 8. 指定枚举值
    printf("8. 自定义枚举值 - 错误码:\n");
    enum ErrorCode err = ERROR_FILE_NOT_FOUND;
    
    printf("错误码值:\n");
    printf("SUCCESS = %d\n", SUCCESS);
    printf("ERROR_FILE_NOT_FOUND = %d\n", ERROR_FILE_NOT_FOUND);
    printf("ERROR_PERMISSION_DENIED = %d\n", ERROR_PERMISSION_DENIED);
    
    if (err == ERROR_FILE_NOT_FOUND) {
        printf("\n当前错误: 文件未找到\n\n");
    }
    
    // 9. 枚举在switch中使用
    printf("9. 枚举在switch中的应用:\n");
    enum Color color = RED;
    
    printf("颜色: ");
    switch (color) {
        case RED:
            printf("红色 (RGB: 255, 0, 0)\n");
            break;
        case GREEN:
            printf("绿色 (RGB: 0, 255, 0)\n");
            break;
        case BLUE:
            printf("蓝色 (RGB: 0, 0, 255)\n");
            break;
        default:
            printf("其他颜色\n");
    }
    printf("\n");
    
    // 10. 结构体中使用枚举
    printf("10. 结构体与枚举结合:\n");
    struct Account accounts[3] = {
        {1001, "alice", ACTIVE},
        {1002, "bob", INACTIVE},
        {1003, "charlie", PENDING}
    };
    
    printf("账户列表:\n");
    for (int i = 0; i < 3; i++) {
        printf("%d. %s - ", accounts[i].id, accounts[i].username);
        switch (accounts[i].status) {
            case ACTIVE: printf("激活"); break;
            case INACTIVE: printf("未激活"); break;
            case PENDING: printf("待审核"); break;
            case SUSPENDED: printf("已暂停"); break;
        }
        printf("\n");
    }
    printf("\n");
    
    // 11. 位字段基础
    printf("11. 位字段 - 节省内存:\n");
    struct Flags flags = {0};
    
    printf("Flags结构体大小: %zu 字节\n", sizeof(struct Flags));
    
    flags.isActive = 1;
    flags.isAdmin = 0;
    flags.hasEmail = 1;
    
    printf("是否激活: %d\n", flags.isActive);
    printf("是否管理员: %d\n", flags.isAdmin);
    printf("是否有邮箱: %d\n\n", flags.hasEmail);
    
    // 12. 位字段应用 - 日期
    printf("12. 位字段应用 - 压缩日期:\n");
    struct Date birthdate;
    
    birthdate.year = 2000;
    birthdate.month = 5;
    birthdate.day = 20;
    
    printf("普通结构体(3个int): %zu 字节\n", sizeof(int) * 3);
    printf("位字段结构体: %zu 字节\n", sizeof(struct Date));
    printf("日期: %d年%d月%d日\n\n", 
           birthdate.year, birthdate.month, birthdate.day);
    
    // 13. 实际应用：配置标志
    printf("13. 实际应用 - 配置标志:\n");
    
    struct Config {
        unsigned int verbose : 1;
        unsigned int debug : 1;
        unsigned int logging : 1;
        unsigned int compression : 1;
        unsigned int encryption : 1;
        unsigned int unused : 3;
    };
    
    struct Config config = {0};
    config.verbose = 1;
    config.debug = 0;
    config.logging = 1;
    config.compression = 1;
    config.encryption = 0;
    
    printf("配置:\n");
    printf("详细模式: %s\n", config.verbose ? "开" : "关");
    printf("调试模式: %s\n", config.debug ? "开" : "关");
    printf("日志记录: %s\n", config.logging ? "开" : "关");
    printf("压缩: %s\n", config.compression ? "开" : "关");
    printf("加密: %s\n\n", config.encryption ? "开" : "关");
    
    // 14. 实际应用：状态机
    printf("14. 实际应用 - 状态机:\n");
    
    enum State {
        STATE_IDLE,
        STATE_RUNNING,
        STATE_PAUSED,
        STATE_STOPPED,
        STATE_ERROR
    };
    
    enum State currentState = STATE_IDLE;
    
    printf("初始状态: ");
    switch (currentState) {
        case STATE_IDLE: printf("空闲\n"); break;
        case STATE_RUNNING: printf("运行中\n"); break;
        case STATE_PAUSED: printf("暂停\n"); break;
        case STATE_STOPPED: printf("停止\n"); break;
        case STATE_ERROR: printf("错误\n"); break;
    }
    
    // 状态转换
    currentState = STATE_RUNNING;
    printf("转换后: 运行中\n\n");
    
    // 15. 联合体与结构体的大小比较
    printf("15. 大小比较:\n");
    
    struct Combined {
        int intVal;
        float floatVal;
        char str[20];
    };
    
    printf("结构体 Combined: %zu 字节 (所有成员)\n", 
           sizeof(struct Combined));
    printf("联合体 Data: %zu 字节 (最大成员)\n", 
           sizeof(union Data));
    printf("节省内存: %zu 字节\n", 
           sizeof(struct Combined) - sizeof(union Data));
    
    return 0;
}

/*
 * 知识点总结：
 * 
 * 联合体（Union）：
 * 
 * 定义：
 * union 联合体名 {
 *     类型1 成员1;
 *     类型2 成员2;
 *     ...
 * };
 * 
 * 特点：
 * - 所有成员共享同一块内存
 * - 大小等于最大成员的大小
 * - 同一时间只能使用一个成员
 * - 修改一个成员会影响其他成员
 * 
 * 联合体 vs 结构体：
 * 
 * 结构体：
 * - 每个成员有独立内存
 * - 大小 = 所有成员之和（加对齐）
 * - 可以同时使用所有成员
 * 
 * 联合体：
 * - 所有成员共享内存
 * - 大小 = 最大成员
 * - 同一时间只能用一个成员
 * 
 * 联合体的应用：
 * 
 * 1. 节省内存：
 *    当多个变量不会同时使用时
 * 
 * 2. 类型转换：
 *    union Converter {
 *        float f;
 *        int i;
 *        char bytes[4];
 *    };
 * 
 * 3. 变体数据：
 *    struct Variant {
 *        int type;
 *        union {
 *            int intVal;
 *            float floatVal;
 *            char *strVal;
 *        } data;
 *    };
 * 
 * 4. 网络协议：
 *    不同类型的数据包
 * 
 * 使用联合体的注意事项：
 * 
 * 1. 需要记住最后写入的成员
 * 2. 通常配合类型标识使用
 * 3. 读取错误的成员会得到垃圾值
 * 4. 不能同时使用多个成员
 * 
 * 枚举（Enum）：
 * 
 * 定义：
 * enum 枚举名 {
 *     枚举值1,
 *     枚举值2,
 *     ...
 * };
 * 
 * 特点：
 * - 定义一组命名的整数常量
 * - 默认从0开始，依次递增
 * - 可以指定特定值
 * - 提高代码可读性
 * 
 * 枚举的使用：
 * 
 * 1. 默认值：
 *    enum Color {
 *        RED,     // 0
 *        GREEN,   // 1
 *        BLUE     // 2
 *    };
 * 
 * 2. 指定值：
 *    enum ErrorCode {
 *        SUCCESS = 0,
 *        ERROR_FILE = 100,
 *        ERROR_MEMORY = 200
 *    };
 * 
 * 3. 部分指定：
 *    enum Values {
 *        A,       // 0
 *        B = 10,  // 10
 *        C,       // 11
 *        D        // 12
 *    };
 * 
 * 枚举的优势：
 * 
 * 1. 可读性：
 *    if (status == ACTIVE)  // 清晰
 *    vs
 *    if (status == 1)       // 不清晰
 * 
 * 2. 类型安全：
 *    enum Color c = RED;
 * 
 * 3. 易于维护：
 *    集中定义，便于修改
 * 
 * 4. IDE支持：
 *    自动完成、类型检查
 * 
 * 枚举的应用场景：
 * 
 * 1. 状态机：
 *    enum State { IDLE, RUNNING, STOPPED };
 * 
 * 2. 错误码：
 *    enum Error { OK, ERROR_FILE, ERROR_MEM };
 * 
 * 3. 选项标志：
 *    enum Options { VERBOSE, DEBUG, QUIET };
 * 
 * 4. 方向：
 *    enum Direction { UP, DOWN, LEFT, RIGHT };
 * 
 * 5. 星期/月份：
 *    enum Weekday { MON, TUE, WED, ... };
 * 
 * 位字段（Bit Fields）：
 * 
 * 定义：
 * struct Flags {
 *     unsigned int flag1 : 1;  // 1位
 *     unsigned int flag2 : 1;  // 1位
 *     unsigned int value : 5;  // 5位
 * };
 * 
 * 特点：
 * - 指定成员占用的位数
 * - 节省内存
 * - 只能用于整数类型
 * - 不能取地址
 * 
 * 位字段的应用：
 * 
 * 1. 标志位：
 *    struct {
 *        unsigned int isActive : 1;
 *        unsigned int isAdmin : 1;
 *    };
 * 
 * 2. 压缩数据：
 *    struct Date {
 *        unsigned int day : 5;    // 1-31
 *        unsigned int month : 4;  // 1-12
 *        unsigned int year : 12;  // 0-4095
 *    };
 * 
 * 3. 硬件寄存器：
 *    模拟硬件寄存器的位
 * 
 * 位字段注意事项：
 * 
 * 1. 不可移植：
 *    - 位序依赖编译器
 *    - 对齐方式不同
 * 
 * 2. 不能取地址：
 *    unsigned int *p = &flags.flag1;  // 错误
 * 
 * 3. 只能用整数：
 *    不能用float、double等
 * 
 * 4. 性能：
 *    访问位字段可能比普通字段慢
 * 
 * 组合使用：
 * 
 * 结构体 + 联合体 + 枚举：
 * 
 * enum Type { INT, FLOAT, STRING };
 * 
 * struct Variant {
 *     enum Type type;
 *     union {
 *         int intVal;
 *         float floatVal;
 *         char strVal[100];
 *     } value;
 * };
 * 
 * 最佳实践：
 * 
 * 1. 联合体：
 *    - 总是配合类型标识
 *    - 记录当前使用的成员
 *    - 文档说明用途
 * 
 * 2. 枚举：
 *    - 使用有意义的名称
 *    - 全大写（约定）
 *    - 避免魔数
 * 
 * 3. 位字段：
 *    - 用于节省内存的场合
 *    - 注意可移植性
 *    - 文档说明位的含义
 * 
 * 常见错误：
 * 
 * 1. 联合体误用：
 *    union Data d;
 *    d.intVal = 10;
 *    printf("%f", d.floatVal);  // 错误！
 * 
 * 2. 枚举当作字符串：
 *    enum Color c = RED;
 *    printf("%s", c);  // 错误！
 * 
 * 3. 位字段取地址：
 *    struct Flags f;
 *    int *p = &f.flag;  // 错误！
 * 
 * 4. 超出位字段范围：
 *    unsigned int value : 3;  // 最大7
 *    value = 10;  // 溢出
 * 
 * 调试技巧：
 * 
 * 1. 打印联合体：
 *    - 打印所有成员（谨慎）
 *    - 使用类型标识
 * 
 * 2. 枚举值：
 *    - 可以直接打印整数值
 *    - 编写转字符串函数
 * 
 * 3. 位字段：
 *    - 打印每个位
 *    - 使用调试器查看
 */
