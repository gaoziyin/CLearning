/*
 * 第六章：结构体与联合体
 * 6.5 typedef与类型定义
 * 
 * 学习目标：
 * 1. 掌握typedef的使用方法
 * 2. 学会为结构体、联合体定义别名
 * 3. 理解typedef的优势和应用场景
 * 4. 学习复杂类型定义的技巧
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 1. 基本类型typedef
typedef int Integer;
typedef float Real;
typedef char Character;

// 2. 指针类型typedef
typedef int* IntPtr;
typedef char* String;

// 3. 数组类型typedef
typedef int IntArray[10];
typedef char Name[50];

// 4. 结构体typedef（方式1：分开定义）
struct Point {
    double x;
    double y;
};
typedef struct Point Point;  // 定义别名

// 5. 结构体typedef（方式2：同时定义）
typedef struct {
    double width;
    double height;
} Rectangle;

// 6. 结构体typedef（方式3：命名+别名）
typedef struct Student {
    int id;
    char name[50];
    float score;
} Student;

// 7. 联合体typedef
typedef union {
    int intVal;
    float floatVal;
    char strVal[20];
} Data;

// 8. 枚举typedef
typedef enum {
    RED,
    GREEN,
    BLUE,
    YELLOW
} Color;

// 9. 函数指针typedef
typedef int (*CompareFunc)(int, int);
typedef void (*CallbackFunc)(void);

// 10. 复杂类型typedef
typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef Node* NodePtr;

// 11. 数组指针typedef
typedef int (*ArrayPtr)[10];

// 12. 结构体指针typedef
typedef struct Employee {
    int id;
    Name name;  // 使用之前定义的typedef
    float salary;
} Employee, *EmployeePtr;

// 13. 嵌套的typedef
typedef struct {
    int hour;
    int minute;
    int second;
} Time;

typedef struct {
    Name eventName;
    Time startTime;
    Time endTime;
} Event;

// 函数声明
int compare(int a, int b);
void greet(void);
void printStudent(Student s);
void printEmployee(EmployeePtr emp);

int main() {
    printf("=== typedef与类型定义 ===\n\n");
    
    // 1. 基本类型typedef
    printf("1. 基本类型typedef:\n");
    Integer num = 100;
    Real pi = 3.14159;
    Character ch = 'A';
    
    printf("Integer: %d\n", num);
    printf("Real: %.5f\n", pi);
    printf("Character: %c\n\n", ch);
    
    // 2. 指针类型typedef
    printf("2. 指针类型typedef:\n");
    Integer value = 42;
    IntPtr ptr = &value;
    
    printf("值: %d\n", value);
    printf("通过指针: %d\n", *ptr);
    
    String message = "Hello, typedef!";
    printf("字符串: %s\n\n", message);
    
    // 3. 数组类型typedef
    printf("3. 数组类型typedef:\n");
    IntArray numbers = {1, 2, 3, 4, 5};
    Name userName = "张三";
    
    printf("数组: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n姓名: %s\n\n", userName);
    
    // 4. 结构体typedef - 方式1
    printf("4. 结构体typedef (方式1):\n");
    Point p1;
    p1.x = 10.0;
    p1.y = 20.0;
    printf("点: (%.1f, %.1f)\n\n", p1.x, p1.y);
    
    // 5. 结构体typedef - 方式2（匿名结构体）
    printf("5. 结构体typedef (方式2 - 匿名):\n");
    Rectangle rect = {100.0, 50.0};
    printf("矩形: 宽%.1f, 高%.1f\n", rect.width, rect.height);
    printf("面积: %.1f\n\n", rect.width * rect.height);
    
    // 6. 结构体typedef - 方式3（推荐）
    printf("6. 结构体typedef (方式3 - 推荐):\n");
    Student student = {1001, "李四", 85.5};
    printStudent(student);
    printf("\n");
    
    // 7. 联合体typedef
    printf("7. 联合体typedef:\n");
    Data data;
    
    data.intVal = 100;
    printf("整数: %d\n", data.intVal);
    
    data.floatVal = 3.14;
    printf("浮点: %.2f\n\n", data.floatVal);
    
    // 8. 枚举typedef
    printf("8. 枚举typedef:\n");
    Color favoriteColor = BLUE;
    Color backgroundColor = RED;
    
    printf("最喜欢的颜色: ");
    switch (favoriteColor) {
        case RED: printf("红色"); break;
        case GREEN: printf("绿色"); break;
        case BLUE: printf("蓝色"); break;
        case YELLOW: printf("黄色"); break;
    }
    printf("\n\n");
    
    // 9. 函数指针typedef
    printf("9. 函数指针typedef:\n");
    CompareFunc cmpFunc = compare;
    CallbackFunc callback = greet;
    
    int result = cmpFunc(10, 20);
    printf("比较结果: %d\n", result);
    
    printf("调用回调函数: ");
    callback();
    printf("\n\n");
    
    // 10. 链表节点typedef
    printf("10. 链表节点typedef:\n");
    Node node1 = {10, NULL};
    Node node2 = {20, NULL};
    Node node3 = {30, NULL};
    
    node1.next = &node2;
    node2.next = &node3;
    
    printf("链表: ");
    Node *current = &node1;
    while (current != NULL) {
        printf("%d ", current->data);
        if (current->next != NULL) printf("-> ");
        current = current->next;
    }
    printf("\n\n");
    
    // 11. 指针typedef
    printf("11. 节点指针typedef:\n");
    NodePtr head = (NodePtr)malloc(sizeof(Node));
    head->data = 100;
    head->next = NULL;
    
    printf("头节点数据: %d\n", head->data);
    free(head);
    printf("\n");
    
    // 12. 结构体指针typedef
    printf("12. 结构体指针typedef:\n");
    Employee emp = {2001, "王五", 12000.0};
    EmployeePtr empPtr = &emp;
    
    printEmployee(empPtr);
    printf("\n");
    
    // 13. 嵌套typedef
    printf("13. 嵌套的typedef结构:\n");
    Event meeting = {
        "技术会议",
        {14, 30, 0},
        {16, 30, 0}
    };
    
    printf("事件: %s\n", meeting.eventName);
    printf("开始: %02d:%02d:%02d\n", 
           meeting.startTime.hour,
           meeting.startTime.minute,
           meeting.startTime.second);
    printf("结束: %02d:%02d:%02d\n\n",
           meeting.endTime.hour,
           meeting.endTime.minute,
           meeting.endTime.second);
    
    // 14. 实际应用：数据结构
    printf("14. 实际应用 - 栈结构:\n");
    
    typedef struct {
        int items[100];
        int top;
    } Stack;
    
    Stack stack = {{0}, -1};
    
    // 压栈
    stack.items[++stack.top] = 10;
    stack.items[++stack.top] = 20;
    stack.items[++stack.top] = 30;
    
    printf("栈内容: ");
    for (int i = 0; i <= stack.top; i++) {
        printf("%d ", stack.items[i]);
    }
    printf("\n");
    
    // 弹栈
    int popped = stack.items[stack.top--];
    printf("弹出: %d\n", popped);
    printf("栈顶: %d\n\n", stack.items[stack.top]);
    
    // 15. 实际应用：二维点和线
    printf("15. 实际应用 - 几何图形:\n");
    
    typedef struct {
        Point start;
        Point end;
    } Line;
    
    Line line = {{0.0, 0.0}, {10.0, 10.0}};
    
    printf("直线:\n");
    printf("起点: (%.1f, %.1f)\n", line.start.x, line.start.y);
    printf("终点: (%.1f, %.1f)\n\n", line.end.x, line.end.y);
    
    // 16. 实际应用：通用链表
    printf("16. 实际应用 - 通用数据结构:\n");
    
    typedef struct ListNode {
        void *data;
        struct ListNode *next;
    } ListNode;
    
    typedef struct {
        ListNode *head;
        int size;
    } LinkedList;
    
    LinkedList list = {NULL, 0};
    printf("创建空链表，大小: %d\n\n", list.size);
    
    // 17. typedef的优势展示
    printf("17. typedef的优势:\n");
    printf("不使用typedef:\n");
    printf("  struct Student s1;\n");
    printf("  struct Student *ptr;\n");
    printf("\n使用typedef:\n");
    printf("  Student s1;\n");
    printf("  Student *ptr;\n");
    printf("\n更简洁、易读！\n\n");
    
    // 18. 多个typedef
    printf("18. 多个相关的typedef:\n");
    
    typedef unsigned char Byte;
    typedef unsigned short Word;
    typedef unsigned int DWord;
    typedef unsigned long long QWord;
    
    Byte b = 255;
    Word w = 65535;
    DWord dw = 4294967295U;
    
    printf("Byte (8位): %u\n", b);
    printf("Word (16位): %u\n", w);
    printf("DWord (32位): %u\n\n", dw);
    
    // 19. 类型安全
    printf("19. 使用typedef提高类型安全:\n");
    
    typedef int StudentID;
    typedef int CourseID;
    
    StudentID sid = 1001;
    CourseID cid = 2001;
    
    printf("学生ID: %d\n", sid);
    printf("课程ID: %d\n", cid);
    printf("虽然都是int，但语义更清晰\n\n");
    
    // 20. 条件编译中的typedef
    printf("20. 平台相关的typedef:\n");
    
    #ifdef _WIN32
        typedef long long int64_t;
        printf("Windows平台\n");
    #else
        typedef long int64_t;
        printf("Unix/Linux平台\n");
    #endif
    
    printf("int64_t大小: %zu字节\n", sizeof(int64_t));
    
    return 0;
}

// 函数实现

int compare(int a, int b) {
    return a - b;
}

void greet(void) {
    printf("Hello from callback!");
}

void printStudent(Student s) {
    printf("学生信息:\n");
    printf("  学号: %d\n", s.id);
    printf("  姓名: %s\n", s.name);
    printf("  成绩: %.1f\n", s.score);
}

void printEmployee(EmployeePtr emp) {
    printf("员工信息:\n");
    printf("  ID: %d\n", emp->id);
    printf("  姓名: %s\n", emp->name);
    printf("  工资: ¥%.2f\n", emp->salary);
}

/*
 * 知识点总结：
 * 
 * typedef 关键字：
 * 
 * 作用：
 * - 为现有类型定义新名称（别名）
 * - 提高代码可读性
 * - 简化复杂类型声明
 * - 增强代码可维护性
 * 
 * 基本语法：
 * typedef 原类型 新名称;
 * 
 * 例如：
 * typedef int Integer;
 * typedef float Real;
 * 
 * 基本类型typedef：
 * 
 * 1. 整数类型：
 *    typedef int Int32;
 *    typedef long long Int64;
 *    typedef unsigned int UInt;
 * 
 * 2. 浮点类型：
 *    typedef float Float32;
 *    typedef double Float64;
 * 
 * 3. 字符类型：
 *    typedef char Char;
 *    typedef unsigned char Byte;
 * 
 * 指针类型typedef：
 * 
 * typedef int* IntPtr;
 * typedef char* String;
 * typedef void* VoidPtr;
 * 
 * 使用：
 * IntPtr p1, p2;  // 两个都是指针
 * 
 * 注意：
 * int *p1, *p2;   // 显式写*
 * IntPtr p1, p2;  // 隐式包含*
 * 
 * 数组类型typedef：
 * 
 * typedef int IntArray[10];
 * typedef char String[100];
 * 
 * 使用：
 * IntArray arr1, arr2;  // 两个数组
 * 
 * 结构体typedef：
 * 
 * 方式1：分开定义
 * struct Point {
 *     int x, y;
 * };
 * typedef struct Point Point;
 * 
 * 方式2：同时定义（匿名）
 * typedef struct {
 *     int x, y;
 * } Point;
 * 
 * 方式3：命名+别名（推荐）
 * typedef struct Point {
 *     int x, y;
 * } Point;
 * 
 * 优势：
 * - 不用写 struct 关键字
 * - 代码更简洁
 * 
 * 对比：
 * struct Point p1;  // 不用typedef
 * Point p1;         // 使用typedef
 * 
 * 联合体typedef：
 * 
 * typedef union {
 *     int intVal;
 *     float floatVal;
 * } Data;
 * 
 * 使用：
 * Data d;
 * d.intVal = 10;
 * 
 * 枚举typedef：
 * 
 * typedef enum {
 *     RED,
 *     GREEN,
 *     BLUE
 * } Color;
 * 
 * 使用：
 * Color c = RED;
 * 
 * 函数指针typedef：
 * 
 * 不使用typedef：
 * int (*func)(int, int);
 * 
 * 使用typedef：
 * typedef int (*FuncPtr)(int, int);
 * FuncPtr func;
 * 
 * 更清晰：
 * typedef int (*CompareFunc)(int, int);
 * typedef void (*CallbackFunc)(void);
 * 
 * 复杂类型typedef：
 * 
 * 1. 数组指针：
 *    typedef int (*ArrayPtr)[10];
 * 
 * 2. 指针数组：
 *    typedef int* PtrArray[10];
 * 
 * 3. 函数指针数组：
 *    typedef int (*FuncArray[10])(int);
 * 
 * typedef的优势：
 * 
 * 1. 简化声明：
 *    struct Student s;  vs  Student s;
 * 
 * 2. 提高可读性：
 *    typedef int StudentID;
 *    StudentID id;  // 语义清晰
 * 
 * 3. 易于维护：
 *    typedef float Real;
 *    // 以后改成double只需改一处
 * 
 * 4. 隐藏实现：
 *    typedef struct Node* NodePtr;
 *    // 用户不需要知道内部结构
 * 
 * 5. 平台兼容：
 *    #ifdef _WIN32
 *        typedef long long int64_t;
 *    #else
 *        typedef long int64_t;
 *    #endif
 * 
 * 6. 函数指针：
 *    typedef简化复杂的函数指针声明
 * 
 * typedef vs #define：
 * 
 * typedef：
 * - 由编译器处理
 * - 类型安全
 * - 作用域规则
 * - 只能用于类型
 * 
 * #define：
 * - 预处理器文本替换
 * - 无类型检查
 * - 全局作用
 * - 可用于任何文本
 * 
 * 例如：
 * typedef int* IntPtr;
 * IntPtr p1, p2;  // 都是指针
 * 
 * #define IntPtr int*
 * IntPtr p1, p2;  // p1是指针，p2是int！
 * 
 * 常用typedef模式：
 * 
 * 1. 基本类型别名：
 *    typedef unsigned int uint;
 *    typedef unsigned char byte;
 * 
 * 2. 结构体简化：
 *    typedef struct Student Student;
 * 
 * 3. 函数指针：
 *    typedef void (*Handler)(int);
 * 
 * 4. 数据结构：
 *    typedef struct Node Node;
 *    typedef Node* NodePtr;
 * 
 * 5. 回调函数：
 *    typedef void (*Callback)(void*);
 * 
 * 实际应用：
 * 
 * 1. 数据结构：
 *    typedef struct Stack Stack;
 *    typedef struct Queue Queue;
 *    typedef struct Tree Tree;
 * 
 * 2. 句柄类型：
 *    typedef void* HANDLE;
 *    typedef struct File* FileHandle;
 * 
 * 3. 回调系统：
 *    typedef void (*EventHandler)(Event*);
 * 
 * 4. 跨平台：
 *    typedef platform_specific_type portable_type;
 * 
 * 最佳实践：
 * 
 * 1. 命名：
 *    - 有意义的名称
 *    - 首字母大写（约定）
 *    - 避免与标准类型冲突
 * 
 * 2. 使用场景：
 *    - 简化复杂类型
 *    - 提高可读性时
 *    - 需要抽象时
 * 
 * 3. 结构体：
 *    - 使用方式3（命名+别名）
 *    - 保留结构体名（用于前向声明）
 * 
 * 4. 指针：
 *    - 谨慎使用指针typedef
 *    - 可能隐藏指针性质
 * 
 * 5. 函数指针：
 *    - 强烈推荐使用typedef
 *    - 大大提高可读性
 * 
 * 注意事项：
 * 
 * 1. 不是新类型：
 *    - 只是别名
 *    - 本质还是原类型
 * 
 * 2. 作用域：
 *    - 遵循C的作用域规则
 *    - 可以在函数内定义
 * 
 * 3. 指针陷阱：
 *    typedef int* IntPtr;
 *    IntPtr p, q;  // 都是指针
 *    但可能误导
 * 
 * 4. 过度使用：
 *    - 不要为每个类型都typedef
 *    - 保持简单明了
 * 
 * 常见错误：
 * 
 * 1. typedef顺序：
 *    int typedef Integer;  // 错误
 *    typedef int Integer;  // 正确
 * 
 * 2. 忘记分号：
 *    typedef struct Point {
 *        int x, y;
 *    } Point  // 错误：缺少分号
 * 
 * 3. 重复定义：
 *    typedef int MyInt;
 *    typedef float MyInt;  // 错误
 * 
 * 4. 与变量混淆：
 *    typedef int MyInt;
 *    int MyInt;  // 错误：名称冲突
 * 
 * 调试技巧：
 * 
 * 1. 使用原类型：
 *    如果typedef有问题，换回原类型
 * 
 * 2. 查看定义：
 *    IDE通常可以跳转到typedef定义
 * 
 * 3. 编译器输出：
 *    查看编译器如何解释typedef
 */
