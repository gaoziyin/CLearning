/*
 * 第六章：结构体与联合体
 * 6.2 结构体操作
 * 
 * 学习目标：
 * 1. 掌握结构体作为函数参数
 * 2. 学会结构体作为返回值
 * 3. 理解结构体的比较和复制
 * 4. 学习结构体的实用操作技巧
 */

#include <stdio.h>
#include <string.h>
#include <math.h>

// 定义结构体类型

// 学生结构体
struct Student {
    int id;
    char name[50];
    int age;
    float score;
};

// 坐标点结构体
struct Point {
    double x;
    double y;
};

// 矩形结构体
struct Rectangle {
    struct Point topLeft;
    struct Point bottomRight;
};

// 时间结构体
struct Time {
    int hour;
    int minute;
    int second;
};

// 函数声明

// 传值方式传递结构体
void printStudent(struct Student s);

// 传址方式传递结构体（推荐）
void printStudentByPointer(const struct Student *s);

// 修改结构体
void updateScore(struct Student *s, float newScore);

// 返回结构体
struct Student createStudent(int id, const char *name, int age, float score);

// 比较两个点
int comparePoints(struct Point p1, struct Point p2);

// 计算两点距离
double calculateDistance(struct Point p1, struct Point p2);

// 时间操作
struct Time addTime(struct Time t1, struct Time t2);
int compareTime(struct Time t1, struct Time t2);

// 结构体数组操作
void sortStudentsByScore(struct Student arr[], int size);
struct Student* findStudentById(struct Student arr[], int size, int id);

int main() {
    printf("=== 结构体操作 ===\n\n");
    
    // 1. 结构体作为函数参数（传值）
    printf("1. 传值方式传递结构体:\n");
    struct Student s1 = {1001, "张三", 20, 85.5};
    
    printf("调用函数:\n");
    printStudent(s1);
    
    printf("\n注意：传值会复制整个结构体\n");
    printf("结构体大小: %zu 字节\n\n", sizeof(struct Student));
    
    // 2. 结构体作为函数参数（传址）
    printf("2. 传址方式传递结构体（推荐）:\n");
    printf("调用函数:\n");
    printStudentByPointer(&s1);
    
    printf("\n传址只传递指针（%zu 字节）\n", sizeof(struct Student*));
    printf("更高效，尤其是大结构体\n\n");
    
    // 3. 通过指针修改结构体
    printf("3. 通过指针修改结构体:\n");
    printf("修改前: %s, 成绩 %.1f\n", s1.name, s1.score);
    
    updateScore(&s1, 95.0);
    printf("修改后: %s, 成绩 %.1f\n\n", s1.name, s1.score);
    
    // 4. 函数返回结构体
    printf("4. 函数返回结构体:\n");
    struct Student s2 = createStudent(1002, "李四", 21, 90.0);
    
    printf("创建的学生: %d, %s, %d岁, %.1f分\n\n", 
           s2.id, s2.name, s2.age, s2.score);
    
    // 5. 结构体比较
    printf("5. 结构体比较:\n");
    struct Point p1 = {10.0, 20.0};
    struct Point p2 = {10.0, 20.0};
    struct Point p3 = {15.0, 25.0};
    
    printf("p1: (%.1f, %.1f)\n", p1.x, p1.y);
    printf("p2: (%.1f, %.1f)\n", p2.x, p2.y);
    printf("p3: (%.1f, %.1f)\n", p3.x, p3.y);
    
    // 不能直接用 == 比较结构体
    // if (p1 == p2) { }  // 错误！
    
    if (comparePoints(p1, p2)) {
        printf("p1 和 p2 相同\n");
    }
    
    if (!comparePoints(p1, p3)) {
        printf("p1 和 p3 不同\n");
    }
    printf("\n");
    
    // 6. 结构体复制
    printf("6. 结构体复制:\n");
    struct Student original = {2001, "原始", 20, 80.0};
    struct Student copy;
    
    // 方式1：直接赋值（推荐）
    copy = original;
    
    printf("原始: %s, %.1f\n", original.name, original.score);
    printf("复制: %s, %.1f\n", copy.name, copy.score);
    
    // 修改复制不影响原始
    copy.score = 95.0;
    strcpy(copy.name, "复制");
    
    printf("\n修改复制后:\n");
    printf("原始: %s, %.1f\n", original.name, original.score);
    printf("复制: %s, %.1f\n\n", copy.name, copy.score);
    
    // 7. 使用 memcpy 复制（不推荐）
    printf("7. 使用 memcpy 复制结构体:\n");
    struct Student s3, s4;
    s3.id = 3001;
    strcpy(s3.name, "测试");
    s3.age = 22;
    s3.score = 88.0;
    
    memcpy(&s4, &s3, sizeof(struct Student));
    
    printf("复制结果: %d, %s, %d岁, %.1f分\n\n", 
           s4.id, s4.name, s4.age, s4.score);
    
    // 8. 计算两点距离
    printf("8. 实际应用 - 计算距离:\n");
    struct Point pa = {0.0, 0.0};
    struct Point pb = {3.0, 4.0};
    
    double dist = calculateDistance(pa, pb);
    
    printf("点A: (%.1f, %.1f)\n", pa.x, pa.y);
    printf("点B: (%.1f, %.1f)\n", pb.x, pb.y);
    printf("距离: %.2f\n\n", dist);
    
    // 9. 时间操作
    printf("9. 实际应用 - 时间运算:\n");
    struct Time t1 = {2, 30, 45};
    struct Time t2 = {1, 45, 30};
    
    printf("时间1: %02d:%02d:%02d\n", t1.hour, t1.minute, t1.second);
    printf("时间2: %02d:%02d:%02d\n", t2.hour, t2.minute, t2.second);
    
    struct Time sum = addTime(t1, t2);
    printf("相加: %02d:%02d:%02d\n\n", sum.hour, sum.minute, sum.second);
    
    // 10. 时间比较
    printf("10. 时间比较:\n");
    struct Time morning = {8, 30, 0};
    struct Time afternoon = {14, 30, 0};
    
    int cmp = compareTime(morning, afternoon);
    printf("早上 %02d:%02d ", morning.hour, morning.minute);
    if (cmp < 0) {
        printf("< ");
    } else if (cmp > 0) {
        printf("> ");
    } else {
        printf("= ");
    }
    printf("下午 %02d:%02d\n\n", afternoon.hour, afternoon.minute);
    
    // 11. 结构体数组操作
    printf("11. 结构体数组排序:\n");
    struct Student class[] = {
        {1001, "张三", 20, 75.5},
        {1002, "李四", 21, 92.0},
        {1003, "王五", 19, 88.5},
        {1004, "赵六", 20, 95.0},
        {1005, "钱七", 22, 82.0}
    };
    int size = sizeof(class) / sizeof(class[0]);
    
    printf("排序前:\n");
    for (int i = 0; i < size; i++) {
        printf("%s: %.1f分\n", class[i].name, class[i].score);
    }
    
    sortStudentsByScore(class, size);
    
    printf("\n按成绩排序后:\n");
    for (int i = 0; i < size; i++) {
        printf("%s: %.1f分\n", class[i].name, class[i].score);
    }
    printf("\n");
    
    // 12. 查找结构体
    printf("12. 在数组中查找结构体:\n");
    int searchId = 1003;
    struct Student *found = findStudentById(class, size, searchId);
    
    if (found != NULL) {
        printf("找到学号 %d: %s, %.1f分\n\n", 
               searchId, found->name, found->score);
    } else {
        printf("未找到学号 %d\n\n", searchId);
    }
    
    // 13. 嵌套结构体操作
    printf("13. 嵌套结构体操作:\n");
    struct Rectangle rect = {
        {0.0, 10.0},   // 左上角
        {10.0, 0.0}    // 右下角
    };
    
    printf("矩形信息:\n");
    printf("左上角: (%.1f, %.1f)\n", 
           rect.topLeft.x, rect.topLeft.y);
    printf("右下角: (%.1f, %.1f)\n", 
           rect.bottomRight.x, rect.bottomRight.y);
    
    double width = rect.bottomRight.x - rect.topLeft.x;
    double height = rect.topLeft.y - rect.bottomRight.y;
    double area = width * height;
    
    printf("宽度: %.1f\n", width);
    printf("高度: %.1f\n", height);
    printf("面积: %.1f\n\n", area);
    
    // 14. 结构体数组统计
    printf("14. 统计信息:\n");
    float total = 0, max_score = class[0].score, min_score = class[0].score;
    struct Student *top_student = &class[0];
    
    for (int i = 0; i < size; i++) {
        total += class[i].score;
        if (class[i].score > max_score) {
            max_score = class[i].score;
            top_student = &class[i];
        }
        if (class[i].score < min_score) {
            min_score = class[i].score;
        }
    }
    
    printf("总人数: %d\n", size);
    printf("总分: %.1f\n", total);
    printf("平均分: %.2f\n", total / size);
    printf("最高分: %.1f (%s)\n", max_score, top_student->name);
    printf("最低分: %.1f\n", min_score);
    
    return 0;
}

// 函数实现

// 传值方式打印学生（会复制整个结构体）
void printStudent(struct Student s) {
    printf("学号: %d\n", s.id);
    printf("姓名: %s\n", s.name);
    printf("年龄: %d\n", s.age);
    printf("成绩: %.1f\n", s.score);
}

// 传址方式打印学生（只传递指针，更高效）
void printStudentByPointer(const struct Student *s) {
    printf("学号: %d\n", s->id);
    printf("姓名: %s\n", s->name);
    printf("年龄: %d\n", s->age);
    printf("成绩: %.1f\n", s->score);
}

// 更新成绩
void updateScore(struct Student *s, float newScore) {
    s->score = newScore;
}

// 创建学生
struct Student createStudent(int id, const char *name, int age, float score) {
    struct Student s;
    s.id = id;
    strcpy(s.name, name);
    s.age = age;
    s.score = score;
    return s;
}

// 比较两个点
int comparePoints(struct Point p1, struct Point p2) {
    return (p1.x == p2.x && p1.y == p2.y);
}

// 计算两点距离
double calculateDistance(struct Point p1, struct Point p2) {
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    return sqrt(dx * dx + dy * dy);
}

// 时间相加
struct Time addTime(struct Time t1, struct Time t2) {
    struct Time result;
    
    result.second = t1.second + t2.second;
    result.minute = t1.minute + t2.minute;
    result.hour = t1.hour + t2.hour;
    
    // 处理进位
    if (result.second >= 60) {
        result.minute += result.second / 60;
        result.second %= 60;
    }
    
    if (result.minute >= 60) {
        result.hour += result.minute / 60;
        result.minute %= 60;
    }
    
    return result;
}

// 比较时间
int compareTime(struct Time t1, struct Time t2) {
    if (t1.hour != t2.hour) {
        return t1.hour - t2.hour;
    }
    if (t1.minute != t2.minute) {
        return t1.minute - t2.minute;
    }
    return t1.second - t2.second;
}

// 按成绩排序（冒泡排序）
void sortStudentsByScore(struct Student arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j].score < arr[j + 1].score) {
                // 交换整个结构体
                struct Student temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// 按学号查找学生
struct Student* findStudentById(struct Student arr[], int size, int id) {
    for (int i = 0; i < size; i++) {
        if (arr[i].id == id) {
            return &arr[i];
        }
    }
    return NULL;
}

/*
 * 知识点总结：
 * 
 * 结构体作为函数参数：
 * 
 * 1. 传值（Pass by Value）
 *    void func(struct Student s);
 *    - 复制整个结构体
 *    - 函数内修改不影响原结构体
 *    - 低效（大结构体）
 * 
 * 2. 传址（Pass by Pointer）
 *    void func(struct Student *s);
 *    - 只传递指针
 *    - 函数内可以修改原结构体
 *    - 高效（推荐）
 * 
 * 3. const保护
 *    void func(const struct Student *s);
 *    - 传指针但不允许修改
 *    - 兼顾效率和安全
 * 
 * 选择建议：
 * - 小结构体（<16字节）：传值
 * - 大结构体：传指针
 * - 不修改：加const
 * - 需要修改：传指针
 * 
 * 返回结构体：
 * 
 * 1. 直接返回：
 *    struct Student func() {
 *        struct Student s;
 *        // 初始化s
 *        return s;
 *    }
 * 
 * 2. 返回指针：
 *    struct Student* func() {
 *        static struct Student s;
 *        // 或动态分配
 *        return &s;
 *    }
 * 
 * 注意：
 * - 不要返回局部变量地址
 * - 可以返回static变量地址
 * - 可以返回动态分配的内存
 * 
 * 结构体比较：
 * 
 * 不能直接比较：
 * if (s1 == s2) { }  // 错误！
 * 
 * 需要逐个成员比较：
 * int equal = (s1.id == s2.id && 
 *              strcmp(s1.name, s2.name) == 0 &&
 *              s1.age == s2.age &&
 *              s1.score == s2.score);
 * 
 * 或编写比较函数：
 * int compareStudent(struct Student s1, struct Student s2) {
 *     // 实现比较逻辑
 * }
 * 
 * 结构体复制：
 * 
 * 1. 直接赋值（推荐）：
 *    struct Student s2 = s1;
 *    s2 = s1;
 * 
 * 2. 使用 memcpy：
 *    memcpy(&s2, &s1, sizeof(struct Student));
 * 
 * 3. 逐个成员复制：
 *    s2.id = s1.id;
 *    strcpy(s2.name, s1.name);
 *    ...
 * 
 * 注意：
 * - 直接赋值是深拷贝
 * - 指针成员需要特殊处理
 * - 包含指针的结构体要小心
 * 
 * 结构体数组操作：
 * 
 * 1. 遍历：
 *    for (int i = 0; i < size; i++) {
 *        printf("%s", arr[i].name);
 *    }
 * 
 * 2. 排序：
 *    - 可以交换整个结构体
 *    - 或使用指针数组
 *    - qsort() 标准库函数
 * 
 * 3. 查找：
 *    - 线性查找
 *    - 二分查找（已排序）
 *    - 返回指针或索引
 * 
 * 4. 统计：
 *    - 求和、平均、最大、最小
 *    - 计数、过滤
 * 
 * 嵌套结构体：
 * 
 * 访问：
 * struct Rectangle rect;
 * rect.topLeft.x = 10.0;
 * rect.topLeft.y = 20.0;
 * 
 * 指针访问：
 * struct Rectangle *p = &rect;
 * p->topLeft.x = 10.0;
 * p->topLeft.y = 20.0;
 * 
 * 实用技巧：
 * 
 * 1. 初始化辅助函数：
 *    struct Student createStudent(...) {
 *        struct Student s = {0};
 *        // 初始化
 *        return s;
 *    }
 * 
 * 2. 打印函数：
 *    void printStudent(const struct Student *s) {
 *        printf("%d: %s\n", s->id, s->name);
 *    }
 * 
 * 3. 比较函数：
 *    int compareStudent(const void *a, const void *b) {
 *        // 用于qsort
 *    }
 * 
 * 4. 复制函数：
 *    void copyStudent(struct Student *dest, 
 *                     const struct Student *src) {
 *        *dest = *src;
 *    }
 * 
 * 常见模式：
 * 
 * 1. 查找模式：
 *    struct Student* findById(struct Student arr[], 
 *                             int size, int id) {
 *        for (int i = 0; i < size; i++) {
 *            if (arr[i].id == id) 
 *                return &arr[i];
 *        }
 *        return NULL;
 *    }
 * 
 * 2. 排序模式：
 *    void sort(struct Student arr[], int size) {
 *        // 冒泡/选择/快速排序
 *    }
 * 
 * 3. 映射模式：
 *    void updateAll(struct Student arr[], int size,
 *                   void (*func)(struct Student*)) {
 *        for (int i = 0; i < size; i++) {
 *            func(&arr[i]);
 *        }
 *    }
 * 
 * 性能考虑：
 * 
 * 1. 传参：
 *    - 小结构体：传值
 *    - 大结构体：传指针
 * 
 * 2. 返回：
 *    - 现代编译器优化返回值
 *    - 避免不必要的复制
 * 
 * 3. 对齐：
 *    - 注意内存对齐
 *    - 合理排列成员顺序
 * 
 * 4. 缓存：
 *    - 相关数据放一起
 *    - 减少缓存未命中
 * 
 * 最佳实践：
 * 
 * 1. 参数传递：
 *    - 大结构体用指针
 *    - 加const保护不修改的参数
 *    - 命名清晰
 * 
 * 2. 返回值：
 *    - 小结构体直接返回
 *    - 大结构体通过参数返回
 *    - 不返回局部变量地址
 * 
 * 3. 比较：
 *    - 编写专门的比较函数
 *    - 明确比较规则
 * 
 * 4. 初始化：
 *    - 总是初始化
 *    - 提供创建函数
 * 
 * 5. 错误处理：
 *    - 检查NULL指针
 *    - 验证输入
 *    - 返回错误码或NULL
 * 
 * 常见错误：
 * 
 * 1. 直接比较：
 *    if (s1 == s2) { }  // 错误
 * 
 * 2. 返回局部变量地址：
 *    struct Student* func() {
 *        struct Student s;
 *        return &s;  // 错误
 *    }
 * 
 * 3. 忘记初始化：
 *    struct Student s;
 *    printf("%s", s.name);  // 未定义
 * 
 * 4. 空指针解引用：
 *    struct Student *p = NULL;
 *    p->id = 1001;  // 崩溃
 */
