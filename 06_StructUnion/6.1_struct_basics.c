/*
 * 第六章：结构体与联合体
 * 6.1 结构体基础
 * 
 * 学习目标：
 * 1. 理解结构体的概念和作用
 * 2. 掌握结构体的定义和声明
 * 3. 学会创建和使用结构体变量
 * 4. 理解结构体成员的访问方式
 */

#include <stdio.h>
#include <string.h>

// 1. 基本结构体定义
struct Student {
    int id;              // 学号
    char name[50];       // 姓名
    int age;             // 年龄
    float score;         // 成绩
};

// 2. 定义时声明变量
struct Book {
    char title[100];
    char author[50];
    int year;
    float price;
} book1, book2;  // 同时声明两个变量

// 3. 匿名结构体（不常用）
struct {
    int x;
    int y;
} point1, point2;

// 4. 自引用结构体（为链表等数据结构准备）
struct Node {
    int data;
    struct Node *next;  // 指向同类型结构体的指针
};

int main() {
    printf("=== 结构体基础 ===\n\n");
    
    // 1. 创建结构体变量
    printf("1. 创建结构体变量:\n");
    struct Student student1;
    
    // 初始化成员
    student1.id = 1001;
    strcpy(student1.name, "张三");
    student1.age = 20;
    student1.score = 85.5;
    
    printf("学号: %d\n", student1.id);
    printf("姓名: %s\n", student1.name);
    printf("年龄: %d\n", student1.age);
    printf("成绩: %.1f\n\n", student1.score);
    
    // 2. 结构体初始化
    printf("2. 结构体初始化:\n");
    
    // 方式1：按顺序初始化
    struct Student student2 = {1002, "李四", 21, 90.0};
    
    // 方式2：指定成员初始化（C99）
    struct Student student3 = {
        .id = 1003,
        .name = "王五",
        .age = 22,
        .score = 88.5
    };
    
    printf("学生2: %d, %s, %d岁, %.1f分\n", 
           student2.id, student2.name, student2.age, student2.score);
    printf("学生3: %d, %s, %d岁, %.1f分\n\n", 
           student3.id, student3.name, student3.age, student3.score);
    
    // 3. 访问结构体成员
    printf("3. 访问和修改结构体成员:\n");
    struct Student student4 = {1004, "赵六", 19, 75.0};
    
    printf("修改前: %s, 成绩 %.1f\n", student4.name, student4.score);
    
    // 修改成员
    student4.score = 85.0;
    student4.age = 20;
    
    printf("修改后: %s, 成绩 %.1f, 年龄 %d\n\n", 
           student4.name, student4.score, student4.age);
    
    // 4. 结构体数组
    printf("4. 结构体数组:\n");
    struct Student class[3] = {
        {2001, "小明", 20, 85.5},
        {2002, "小红", 19, 92.0},
        {2003, "小刚", 21, 78.5}
    };
    
    printf("班级学生信息:\n");
    for (int i = 0; i < 3; i++) {
        printf("%d. %s (学号:%d) - %.1f分\n", 
               i+1, class[i].name, class[i].id, class[i].score);
    }
    printf("\n");
    
    // 5. 结构体赋值
    printf("5. 结构体赋值:\n");
    struct Student s1 = {3001, "原始", 20, 80.0};
    struct Student s2;
    
    // 结构体可以直接赋值（整体复制）
    s2 = s1;
    
    printf("s1: %d, %s, %.1f\n", s1.id, s1.name, s1.score);
    printf("s2: %d, %s, %.1f\n", s2.id, s2.name, s2.score);
    
    // 修改s2不影响s1
    s2.score = 95.0;
    strcpy(s2.name, "复制");
    
    printf("修改s2后:\n");
    printf("s1: %s, %.1f\n", s1.name, s1.score);
    printf("s2: %s, %.1f\n\n", s2.name, s2.score);
    
    // 6. 结构体的大小
    printf("6. 结构体的大小:\n");
    printf("sizeof(struct Student) = %zu 字节\n", sizeof(struct Student));
    printf("预期大小 = 4 + 50 + 4 + 4 = 62 字节\n");
    printf("实际可能更大（内存对齐）\n\n");
    
    // 7. 嵌套的结构体成员
    printf("7. 包含数组的结构体:\n");
    struct Course {
        char name[30];
        int credits;
        float grades[3];  // 三次成绩
    };
    
    struct Course math = {
        "高等数学",
        4,
        {85.0, 90.0, 88.5}
    };
    
    printf("课程: %s\n", math.name);
    printf("学分: %d\n", math.credits);
    printf("成绩: ");
    for (int i = 0; i < 3; i++) {
        printf("%.1f ", math.grades[i]);
    }
    printf("\n\n");
    
    // 8. 指向结构体的指针
    printf("8. 指向结构体的指针:\n");
    struct Student *ptr = &student1;
    
    // 方式1：通过指针访问成员
    printf("通过 (*ptr).member 访问:\n");
    printf("学号: %d\n", (*ptr).id);
    printf("姓名: %s\n", (*ptr).name);
    
    // 方式2：使用箭头运算符（更常用）
    printf("\n通过 ptr->member 访问:\n");
    printf("学号: %d\n", ptr->id);
    printf("姓名: %s\n", ptr->name);
    printf("成绩: %.1f\n\n", ptr->score);
    
    // 9. 通过指针修改结构体
    printf("9. 通过指针修改结构体:\n");
    printf("修改前: %s, %.1f分\n", ptr->name, ptr->score);
    
    ptr->score = 95.0;
    strcpy(ptr->name, "张三(优秀)");
    
    printf("修改后: %s, %.1f分\n\n", ptr->name, ptr->score);
    
    // 10. 结构体指针数组
    printf("10. 结构体指针数组:\n");
    struct Student *students[3];
    students[0] = &class[0];
    students[1] = &class[1];
    students[2] = &class[2];
    
    printf("通过指针数组访问:\n");
    for (int i = 0; i < 3; i++) {
        printf("%s: %.1f分\n", students[i]->name, students[i]->score);
    }
    printf("\n");
    
    // 11. 实际应用：图书管理
    printf("11. 实际应用 - 图书信息:\n");
    struct Book books[3] = {
        {"C程序设计", "谭浩强", 2015, 35.0},
        {"数据结构", "严蔚敏", 2018, 42.0},
        {"算法导论", "Thomas", 2020, 128.0}
    };
    
    printf("图书列表:\n");
    for (int i = 0; i < 3; i++) {
        printf("%d. 《%s》 - %s (%d年) ¥%.2f\n",
               i+1, books[i].title, books[i].author, 
               books[i].year, books[i].price);
    }
    printf("\n");
    
    // 12. 实际应用：坐标点
    printf("12. 实际应用 - 坐标系统:\n");
    struct Point {
        int x;
        int y;
    };
    
    struct Point p1 = {10, 20};
    struct Point p2 = {30, 40};
    
    printf("点1: (%d, %d)\n", p1.x, p1.y);
    printf("点2: (%d, %d)\n", p2.x, p2.y);
    
    // 计算距离（简化版，只算曼哈顿距离）
    int distance = abs(p2.x - p1.x) + abs(p2.y - p1.y);
    printf("曼哈顿距离: %d\n\n", distance);
    
    // 13. 实际应用：日期时间
    printf("13. 实际应用 - 日期结构:\n");
    struct Date {
        int year;
        int month;
        int day;
    };
    
    struct Date today = {2025, 10, 16};
    struct Date birthday = {2000, 5, 20};
    
    printf("今天: %d年%d月%d日\n", today.year, today.month, today.day);
    printf("生日: %d年%d月%d日\n", birthday.year, birthday.month, birthday.day);
    
    // 简单年龄计算
    int age = today.year - birthday.year;
    if (today.month < birthday.month || 
        (today.month == birthday.month && today.day < birthday.day)) {
        age--;
    }
    printf("年龄: %d岁\n\n", age);
    
    // 14. 空结构体变量
    printf("14. 未初始化的结构体:\n");
    struct Student empty;
    printf("未初始化的结构体包含垃圾值\n");
    printf("应该初始化: struct Student empty = {0};\n\n");
    
    // 正确的初始化
    struct Student initialized = {0};
    printf("初始化为0: id=%d, age=%d, score=%.1f\n", 
           initialized.id, initialized.age, initialized.score);
    
    return 0;
}

/*
 * 知识点总结：
 * 
 * 结构体的概念：
 * - 结构体是用户自定义的复合数据类型
 * - 可以包含不同类型的成员
 * - 用于表示现实世界的实体
 * 
 * 结构体定义：
 * 
 * 语法：
 * struct 结构体名 {
 *     类型1 成员1;
 *     类型2 成员2;
 *     ...
 * };
 * 
 * 例如：
 * struct Student {
 *     int id;
 *     char name[50];
 *     float score;
 * };
 * 
 * 结构体变量声明：
 * 
 * 1. 定义后声明：
 *    struct Student s1;
 * 
 * 2. 定义时声明：
 *    struct Student {
 *        ...
 *    } s1, s2;
 * 
 * 3. 匿名结构体：
 *    struct {
 *        ...
 *    } s1;
 * 
 * 结构体初始化：
 * 
 * 1. 声明时初始化：
 *    struct Student s1 = {1001, "张三", 85.5};
 * 
 * 2. 指定成员初始化（C99）：
 *    struct Student s2 = {
 *        .id = 1002,
 *        .name = "李四",
 *        .score = 90.0
 *    };
 * 
 * 3. 部分初始化：
 *    struct Student s3 = {1003};  // 其他成员为0
 * 
 * 4. 全部清零：
 *    struct Student s4 = {0};
 * 
 * 访问结构体成员：
 * 
 * 1. 点运算符 .
 *    s1.id = 1001;
 *    printf("%s", s1.name);
 * 
 * 2. 箭头运算符 ->（指针）
 *    struct Student *ptr = &s1;
 *    ptr->id = 1002;
 *    printf("%s", ptr->name);
 * 
 * 注意：
 * ptr->member 等价于 (*ptr).member
 * 
 * 结构体赋值：
 * - 可以整体赋值
 * - 会复制所有成员
 * - 是深拷贝（值复制）
 * 
 * 例如：
 * struct Student s1 = {1001, "张三", 85.5};
 * struct Student s2 = s1;  // 整体复制
 * 
 * 结构体数组：
 * 
 * 声明：
 * struct Student class[30];
 * 
 * 初始化：
 * struct Student class[3] = {
 *     {1001, "张三", 85.5},
 *     {1002, "李四", 90.0},
 *     {1003, "王五", 88.0}
 * };
 * 
 * 访问：
 * class[0].id = 1001;
 * printf("%s", class[0].name);
 * 
 * 结构体指针：
 * 
 * 声明：
 * struct Student *ptr;
 * 
 * 赋值：
 * ptr = &s1;
 * 
 * 访问成员：
 * - (*ptr).member  // 需要括号
 * - ptr->member    // 推荐使用
 * 
 * 结构体大小：
 * - sizeof(struct) 返回结构体大小
 * - 可能大于成员大小之和（内存对齐）
 * - 编译器会添加填充字节
 * 
 * 内存对齐：
 * - 提高访问效率
 * - 通常按最大成员对齐
 * - 可以使用 #pragma pack 控制
 * 
 * 结构体成员类型：
 * - 基本类型：int, float, char等
 * - 数组：char name[50]
 * - 指针：int *ptr
 * - 其他结构体（嵌套）
 * - 不能包含自身，但可以包含指向自身的指针
 * 
 * 自引用结构体：
 * struct Node {
 *     int data;
 *     struct Node *next;  // 正确
 *     // struct Node node; // 错误！
 * };
 * 
 * 结构体的用途：
 * 1. 表示现实实体（学生、书籍等）
 * 2. 组织相关数据
 * 3. 实现数据结构（链表、树等）
 * 4. 函数返回多个值
 * 5. 提高代码可读性
 * 
 * 最佳实践：
 * 
 * 1. 命名：
 *    - 使用有意义的名称
 *    - 首字母大写（约定）
 *    - 成员名清晰明确
 * 
 * 2. 初始化：
 *    - 总是初始化结构体变量
 *    - 使用 = {0} 清零
 *    - 使用指定初始化提高可读性
 * 
 * 3. 访问：
 *    - 指针用 ->
 *    - 变量用 .
 * 
 * 4. 组织：
 *    - 相关数据放在一起
 *    - 合理排列成员顺序
 *    - 考虑内存对齐
 * 
 * 常见错误：
 * 
 * 1. 忘记 struct 关键字：
 *    Student s1;  // 错误（除非使用typedef）
 *    struct Student s1;  // 正确
 * 
 * 2. 直接比较结构体：
 *    if (s1 == s2) { }  // 错误！不能直接比较
 * 
 * 3. 未初始化就使用：
 *    struct Student s1;
 *    printf("%d", s1.id);  // 未定义行为
 * 
 * 4. 指针运算符优先级：
 *    *ptr.member  // 错误！. 优先级高
 *    (*ptr).member  // 正确
 *    ptr->member  // 推荐
 * 
 * 5. 自包含：
 *    struct Node {
 *        struct Node node;  // 错误！无限递归
 *    };
 * 
 * 调试技巧：
 * - 打印所有成员
 * - 检查指针是否为NULL
 * - 验证初始化
 * - 使用调试器查看结构体
 * 
 * 性能考虑：
 * - 结构体赋值会复制所有成员
 * - 大结构体使用指针传递
 * - 注意内存对齐的影响
 * - 考虑成员排列顺序
 */
