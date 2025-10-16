/*
 * 第六章：结构体与联合体
 * 6.3 嵌套结构体与复杂数据结构
 * 
 * 学习目标：
 * 1. 掌握嵌套结构体的定义和使用
 * 2. 学会结构体指针的使用
 * 3. 理解自引用结构体
 * 4. 实现简单的链表等数据结构
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 1. 嵌套结构体 - 地址信息
struct Address {
    char street[100];
    char city[50];
    char province[50];
    int zipCode;
};

// 2. 包含嵌套结构体的员工信息
struct Employee {
    int id;
    char name[50];
    struct Address address;  // 嵌套的结构体
    float salary;
};

// 3. 日期结构体
struct Date {
    int year;
    int month;
    int day;
};

// 4. 包含多个嵌套结构体
struct Event {
    char title[100];
    struct Date startDate;
    struct Date endDate;
    char location[100];
};

// 5. 自引用结构体 - 链表节点
struct ListNode {
    int data;
    struct ListNode *next;  // 指向下一个节点
};

// 6. 二叉树节点
struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
};

// 7. 学生课程信息（复杂嵌套）
struct Course {
    int courseId;
    char courseName[50];
    int credits;
};

struct StudentRecord {
    int studentId;
    char studentName[50];
    struct Course courses[5];  // 课程数组
    int courseCount;
};

// 函数声明
void printEmployee(const struct Employee *emp);
void printEvent(const struct Event *event);
struct ListNode* createNode(int data);
void printList(struct ListNode *head);
void freeList(struct ListNode *head);
int dateDifference(struct Date d1, struct Date d2);

int main() {
    printf("=== 嵌套结构体与复杂数据结构 ===\n\n");
    
    // 1. 简单嵌套结构体
    printf("1. 嵌套结构体基础:\n");
    struct Employee emp1;
    
    emp1.id = 1001;
    strcpy(emp1.name, "张三");
    strcpy(emp1.address.street, "中关村大街1号");
    strcpy(emp1.address.city, "北京");
    strcpy(emp1.address.province, "北京市");
    emp1.address.zipCode = 100080;
    emp1.salary = 12000.0;
    
    printEmployee(&emp1);
    printf("\n");
    
    // 2. 嵌套结构体初始化
    printf("2. 嵌套结构体初始化:\n");
    struct Employee emp2 = {
        1002,
        "李四",
        {
            "人民路88号",
            "上海",
            "上海市",
            200000
        },
        15000.0
    };
    
    printEmployee(&emp2);
    printf("\n");
    
    // 3. 指定成员初始化
    printf("3. 指定成员初始化:\n");
    struct Employee emp3 = {
        .id = 1003,
        .name = "王五",
        .address = {
            .city = "广州",
            .province = "广东省",
            .zipCode = 510000
        },
        .salary = 13000.0
    };
    
    printf("员工: %s, 城市: %s\n\n", emp3.name, emp3.address.city);
    
    // 4. 通过指针访问嵌套结构体
    printf("4. 通过指针访问嵌套结构体:\n");
    struct Employee *pEmp = &emp1;
    
    printf("方式1: pEmp->address.city = %s\n", pEmp->address.city);
    printf("方式2: (*pEmp).address.city = %s\n\n", (*pEmp).address.city);
    
    // 5. 包含多个嵌套结构体的事件
    printf("5. 复杂嵌套结构体 - 事件:\n");
    struct Event meeting = {
        "技术会议",
        {2025, 10, 20},
        {2025, 10, 22},
        "北京国际会议中心"
    };
    
    printEvent(&meeting);
    printf("\n");
    
    // 6. 日期计算
    printf("6. 日期差计算:\n");
    struct Date birthday = {2000, 5, 20};
    struct Date today = {2025, 10, 16};
    
    int days = dateDifference(birthday, today);
    printf("从 %d-%02d-%02d 到 %d-%02d-%02d\n",
           birthday.year, birthday.month, birthday.day,
           today.year, today.month, today.day);
    printf("大约 %d 天\n\n", days);
    
    // 7. 结构体数组嵌套
    printf("7. 结构体数组中的嵌套:\n");
    struct Employee team[3] = {
        {2001, "张三", {"街道1", "北京", "北京市", 100000}, 10000},
        {2002, "李四", {"街道2", "上海", "上海市", 200000}, 12000},
        {2003, "王五", {"街道3", "深圳", "广东省", 518000}, 15000}
    };
    
    printf("团队成员:\n");
    for (int i = 0; i < 3; i++) {
        printf("%d. %s - %s, 工资:¥%.2f\n", 
               i+1, team[i].name, team[i].address.city, team[i].salary);
    }
    printf("\n");
    
    // 8. 自引用结构体 - 链表
    printf("8. 自引用结构体 - 单链表:\n");
    
    // 创建链表节点
    struct ListNode *head = createNode(10);
    head->next = createNode(20);
    head->next->next = createNode(30);
    head->next->next->next = createNode(40);
    
    printf("链表内容: ");
    printList(head);
    printf("\n");
    
    // 释放链表内存
    freeList(head);
    printf("链表已释放\n\n");
    
    // 9. 动态创建链表
    printf("9. 动态创建链表:\n");
    struct ListNode *list = NULL;
    struct ListNode *tail = NULL;
    
    // 添加节点
    for (int i = 1; i <= 5; i++) {
        struct ListNode *newNode = createNode(i * 10);
        if (list == NULL) {
            list = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    
    printf("动态链表: ");
    printList(list);
    printf("\n");
    
    // 遍历并计算总和
    int sum = 0;
    struct ListNode *current = list;
    while (current != NULL) {
        sum += current->data;
        current = current->next;
    }
    printf("链表元素总和: %d\n\n", sum);
    
    // 释放
    freeList(list);
    
    // 10. 二叉树节点
    printf("10. 自引用结构体 - 二叉树:\n");
    
    // 手动创建简单二叉树
    struct TreeNode *root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->value = 50;
    
    root->left = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->left->value = 30;
    root->left->left = NULL;
    root->left->right = NULL;
    
    root->right = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->right->value = 70;
    root->right->left = NULL;
    root->right->right = NULL;
    
    printf("二叉树结构:\n");
    printf("       %d\n", root->value);
    printf("      / \\\n");
    printf("     %d   %d\n", root->left->value, root->right->value);
    printf("\n");
    
    // 释放树节点
    free(root->left);
    free(root->right);
    free(root);
    
    // 11. 学生课程记录（复杂嵌套）
    printf("11. 复杂数据结构 - 学生课程:\n");
    struct StudentRecord student;
    
    student.studentId = 20250001;
    strcpy(student.studentName, "张三");
    student.courseCount = 3;
    
    // 添加课程
    student.courses[0] = (struct Course){101, "高等数学", 4};
    student.courses[1] = (struct Course){102, "C语言程序设计", 3};
    student.courses[2] = (struct Course){103, "数据结构", 4};
    
    printf("学生: %s (学号: %d)\n", 
           student.studentName, student.studentId);
    printf("选修课程:\n");
    
    int totalCredits = 0;
    for (int i = 0; i < student.courseCount; i++) {
        printf("  %d. %s (学分: %d)\n",
               i+1, 
               student.courses[i].courseName,
               student.courses[i].credits);
        totalCredits += student.courses[i].credits;
    }
    printf("总学分: %d\n\n", totalCredits);
    
    // 12. 实际应用：组织结构
    printf("12. 实际应用 - 公司部门结构:\n");
    
    struct Department {
        char name[50];
        struct Employee manager;
        int employeeCount;
    };
    
    struct Department dept = {
        "技术部",
        {3001, "李经理", {"科技园", "深圳", "广东省", 518000}, 25000.0},
        15
    };
    
    printf("部门: %s\n", dept.name);
    printf("经理: %s\n", dept.manager.name);
    printf("地址: %s, %s\n", 
           dept.manager.address.city, 
           dept.manager.address.province);
    printf("员工数: %d\n\n", dept.employeeCount);
    
    // 13. 实际应用：订单系统
    printf("13. 实际应用 - 订单系统:\n");
    
    struct OrderItem {
        int productId;
        char productName[50];
        int quantity;
        float price;
    };
    
    struct Order {
        int orderId;
        struct Date orderDate;
        struct OrderItem items[5];
        int itemCount;
        float totalAmount;
    };
    
    struct Order order = {
        10001,
        {2025, 10, 16},
        {
            {1001, "键盘", 2, 299.0},
            {1002, "鼠标", 3, 99.0},
            {1003, "显示器", 1, 1999.0}
        },
        3,
        0.0
    };
    
    // 计算总金额
    for (int i = 0; i < order.itemCount; i++) {
        order.totalAmount += order.items[i].quantity * order.items[i].price;
    }
    
    printf("订单号: %d\n", order.orderId);
    printf("日期: %d-%02d-%02d\n", 
           order.orderDate.year, 
           order.orderDate.month, 
           order.orderDate.day);
    printf("订单明细:\n");
    
    for (int i = 0; i < order.itemCount; i++) {
        printf("  %s x%d @ ¥%.2f = ¥%.2f\n",
               order.items[i].productName,
               order.items[i].quantity,
               order.items[i].price,
               order.items[i].quantity * order.items[i].price);
    }
    printf("总金额: ¥%.2f\n", order.totalAmount);
    
    return 0;
}

// 函数实现

// 打印员工信息
void printEmployee(const struct Employee *emp) {
    printf("员工信息:\n");
    printf("  ID: %d\n", emp->id);
    printf("  姓名: %s\n", emp->name);
    printf("  地址: %s, %s, %s %d\n",
           emp->address.street,
           emp->address.city,
           emp->address.province,
           emp->address.zipCode);
    printf("  工资: ¥%.2f\n", emp->salary);
}

// 打印事件信息
void printEvent(const struct Event *event) {
    printf("事件: %s\n", event->title);
    printf("开始: %d-%02d-%02d\n", 
           event->startDate.year,
           event->startDate.month,
           event->startDate.day);
    printf("结束: %d-%02d-%02d\n", 
           event->endDate.year,
           event->endDate.month,
           event->endDate.day);
    printf("地点: %s\n", event->location);
}

// 创建链表节点
struct ListNode* createNode(int data) {
    struct ListNode *node = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (node != NULL) {
        node->data = data;
        node->next = NULL;
    }
    return node;
}

// 打印链表
void printList(struct ListNode *head) {
    struct ListNode *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        if (current->next != NULL) {
            printf("-> ");
        }
        current = current->next;
    }
    printf("\n");
}

// 释放链表
void freeList(struct ListNode *head) {
    struct ListNode *current = head;
    while (current != NULL) {
        struct ListNode *next = current->next;
        free(current);
        current = next;
    }
}

// 简单日期差计算（近似）
int dateDifference(struct Date d1, struct Date d2) {
    // 简化计算：不考虑闰年等复杂情况
    int days1 = d1.year * 365 + d1.month * 30 + d1.day;
    int days2 = d2.year * 365 + d2.month * 30 + d2.day;
    return days2 - days1;
}

/*
 * 知识点总结：
 * 
 * 嵌套结构体：
 * 
 * 定义：
 * struct Address {
 *     char city[50];
 *     int zipCode;
 * };
 * 
 * struct Person {
 *     char name[50];
 *     struct Address address;  // 嵌套
 * };
 * 
 * 访问嵌套成员：
 * 
 * 1. 直接访问：
 *    person.address.city
 *    person.address.zipCode
 * 
 * 2. 通过指针：
 *    ptr->address.city
 *    ptr->address.zipCode
 * 
 * 初始化嵌套结构体：
 * 
 * 1. 逐个初始化：
 *    struct Person p;
 *    strcpy(p.name, "张三");
 *    strcpy(p.address.city, "北京");
 * 
 * 2. 整体初始化：
 *    struct Person p = {
 *        "张三",
 *        {"北京", 100000}
 *    };
 * 
 * 3. 指定成员初始化：
 *    struct Person p = {
 *        .name = "张三",
 *        .address = {
 *            .city = "北京",
 *            .zipCode = 100000
 *        }
 *    };
 * 
 * 多层嵌套：
 * 
 * struct City {
 *     char name[50];
 * };
 * 
 * struct Address {
 *     struct City city;
 *     int zipCode;
 * };
 * 
 * struct Person {
 *     struct Address address;
 * };
 * 
 * 访问：
 * person.address.city.name
 * 
 * 自引用结构体：
 * 
 * 定义：
 * struct Node {
 *     int data;
 *     struct Node *next;  // 指向同类型的指针
 * };
 * 
 * 注意：
 * - 不能包含自身（无限递归）
 * - 可以包含指向自身的指针
 * - 用于链表、树等数据结构
 * 
 * 链表基本操作：
 * 
 * 1. 创建节点：
 *    struct Node* createNode(int data) {
 *        struct Node *node = malloc(sizeof(struct Node));
 *        node->data = data;
 *        node->next = NULL;
 *        return node;
 *    }
 * 
 * 2. 遍历链表：
 *    struct Node *current = head;
 *    while (current != NULL) {
 *        // 处理 current->data
 *        current = current->next;
 *    }
 * 
 * 3. 释放链表：
 *    while (head != NULL) {
 *        struct Node *temp = head;
 *        head = head->next;
 *        free(temp);
 *    }
 * 
 * 二叉树节点：
 * 
 * struct TreeNode {
 *     int value;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 * 
 * 创建：
 * struct TreeNode *root = malloc(sizeof(struct TreeNode));
 * root->value = 10;
 * root->left = NULL;
 * root->right = NULL;
 * 
 * 结构体数组嵌套：
 * 
 * struct Course {
 *     char name[50];
 *     int credits;
 * };
 * 
 * struct Student {
 *     char name[50];
 *     struct Course courses[5];  // 数组
 *     int courseCount;
 * };
 * 
 * 访问：
 * student.courses[0].name
 * student.courses[i].credits
 * 
 * 复杂数据结构设计：
 * 
 * 1. 分层设计：
 *    - 从简单到复杂
 *    - 模块化
 * 
 * 2. 合理抽象：
 *    - 提取公共部分
 *    - 封装相关数据
 * 
 * 3. 考虑扩展：
 *    - 预留空间
 *    - 使用指针（灵活性）
 * 
 * 内存管理：
 * 
 * 1. 静态分配：
 *    struct Node node;
 *    - 栈上分配
 *    - 自动管理
 * 
 * 2. 动态分配：
 *    struct Node *node = malloc(sizeof(struct Node));
 *    - 堆上分配
 *    - 需要手动释放
 * 
 * 3. 释放原则：
 *    - 谁分配谁释放
 *    - 释放后置NULL
 *    - 避免重复释放
 * 
 * 实际应用场景：
 * 
 * 1. 用户信息系统：
 *    - 个人信息 + 地址
 *    - 联系方式
 * 
 * 2. 订单管理：
 *    - 订单头 + 订单项数组
 *    - 客户信息
 * 
 * 3. 组织结构：
 *    - 部门 + 员工
 *    - 层级关系
 * 
 * 4. 数据结构：
 *    - 链表
 *    - 树
 *    - 图
 * 
 * 5. 事件系统：
 *    - 事件信息 + 时间
 *    - 参与者列表
 * 
 * 最佳实践：
 * 
 * 1. 设计：
 *    - 清晰的层次结构
 *    - 合理的抽象级别
 *    - 避免过度嵌套
 * 
 * 2. 命名：
 *    - 有意义的结构体名
 *    - 清晰的成员名
 *    - 一致的命名风格
 * 
 * 3. 初始化：
 *    - 总是初始化
 *    - 使用指定初始化
 *    - 检查动态分配
 * 
 * 4. 访问：
 *    - 使用合适的运算符
 *    - 检查NULL指针
 *    - 注意访问顺序
 * 
 * 5. 内存：
 *    - 配对 malloc/free
 *    - 避免内存泄漏
 *    - 释放后置NULL
 * 
 * 常见错误：
 * 
 * 1. 自包含：
 *    struct Node {
 *        struct Node node;  // 错误！
 *    };
 * 
 * 2. 忘记malloc检查：
 *    struct Node *n = malloc(...);
 *    n->data = 10;  // n可能为NULL
 * 
 * 3. 内存泄漏：
 *    struct Node *n = malloc(...);
 *    n = NULL;  // 泄漏！
 * 
 * 4. 悬空指针：
 *    free(node);
 *    node->data = 10;  // 错误！
 * 
 * 5. 访问顺序错误：
 *    ptr.member  // 错误（ptr是指针）
 *    ptr->member  // 正确
 * 
 * 调试技巧：
 * 
 * 1. 打印结构：
 *    - 编写打印函数
 *    - 显示所有层次
 * 
 * 2. 检查指针：
 *    - 验证非NULL
 *    - 打印地址
 * 
 * 3. 跟踪链表：
 *    - 遍历打印
 *    - 检查循环
 * 
 * 4. 内存工具：
 *    - valgrind（Linux）
 *    - Visual Studio调试器
 * 
 * 性能优化：
 * 
 * 1. 减少嵌套层次
 * 2. 使用指针代替大结构体
 * 3. 考虑缓存友好性
 * 4. 合理使用内存池
 */
