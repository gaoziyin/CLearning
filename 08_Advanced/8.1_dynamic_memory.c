/*
 * 第八章：高级主题
 * 8.1 动态内存分配
 * 
 * 学习目标：
 * 1. 理解动态内存分配的概念
 * 2. 掌握malloc、calloc、realloc、free函数
 * 3. 学习动态数组和动态结构体
 * 4. 了解内存泄漏和悬空指针问题
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 学生结构体
typedef struct {
    int id;
    char name[50];
    float score;
} Student;

// 链表节点
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// 函数声明
void printArray(int *arr, int size);
Student* createStudent(int id, const char *name, float score);
Node* createNode(int data);
void printList(Node *head);
void freeList(Node *head);

int main() {
    printf("=== 动态内存分配 ===\n\n");
    
    // 1. 静态内存 vs 动态内存
    printf("1. 静态内存 vs 动态内存:\n");
    printf("静态内存（栈）:\n");
    printf("  - 编译时确定大小\n");
    printf("  - 自动管理\n");
    printf("  - 生命周期固定\n");
    printf("  - 大小有限\n\n");
    
    printf("动态内存（堆）:\n");
    printf("  - 运行时分配\n");
    printf("  - 手动管理\n");
    printf("  - 灵活的生命周期\n");
    printf("  - 大小更大\n\n");
    
    // 2. malloc() - 分配内存
    printf("2. malloc() - 分配内存:\n");
    
    // 分配5个int的空间
    int *arr1 = (int *)malloc(5 * sizeof(int));
    
    if (arr1 == NULL) {
        printf("内存分配失败！\n");
        return 1;
    }
    
    printf("成功分配 %zu 字节\n", 5 * sizeof(int));
    
    // 使用分配的内存
    for (int i = 0; i < 5; i++) {
        arr1[i] = i * 10;
    }
    
    printf("数组内容: ");
    printArray(arr1, 5);
    
    // 释放内存
    free(arr1);
    printf("内存已释放\n\n");
    
    // 3. calloc() - 分配并初始化为0
    printf("3. calloc() - 分配并清零:\n");
    
    int *arr2 = (int *)calloc(5, sizeof(int));
    
    if (arr2 != NULL) {
        printf("calloc分配的内存（自动初始化为0）: ");
        printArray(arr2, 5);
        
        free(arr2);
    }
    printf("\n");
    
    // 4. malloc vs calloc
    printf("4. malloc vs calloc 对比:\n");
    
    int *arr3 = (int *)malloc(3 * sizeof(int));
    int *arr4 = (int *)calloc(3, sizeof(int));
    
    if (arr3 != NULL && arr4 != NULL) {
        printf("malloc分配（未初始化，值不确定）: ");
        for (int i = 0; i < 3; i++) {
            arr3[i] = 0;  // 手动初始化
            printf("%d ", arr3[i]);
        }
        printf("\n");
        
        printf("calloc分配（自动初始化为0）: ");
        printArray(arr4, 3);
        
        free(arr3);
        free(arr4);
    }
    printf("\n");
    
    // 5. realloc() - 重新分配内存
    printf("5. realloc() - 调整内存大小:\n");
    
    int *arr5 = (int *)malloc(3 * sizeof(int));
    if (arr5 != NULL) {
        arr5[0] = 10;
        arr5[1] = 20;
        arr5[2] = 30;
        
        printf("原始数组（3个元素）: ");
        printArray(arr5, 3);
        
        // 扩大到5个元素
        int *temp = (int *)realloc(arr5, 5 * sizeof(int));
        if (temp != NULL) {
            arr5 = temp;
            arr5[3] = 40;
            arr5[4] = 50;
            
            printf("扩大后数组（5个元素）: ");
            printArray(arr5, 5);
        }
        
        free(arr5);
    }
    printf("\n");
    
    // 6. 动态分配字符串
    printf("6. 动态字符串:\n");
    
    char *str = (char *)malloc(20 * sizeof(char));
    if (str != NULL) {
        strcpy(str, "Hello, Dynamic!");
        printf("字符串: %s\n", str);
        
        // 扩大字符串空间
        str = (char *)realloc(str, 50 * sizeof(char));
        strcat(str, " Memory!");
        printf("扩展后: %s\n", str);
        
        free(str);
    }
    printf("\n");
    
    // 7. 动态分配结构体
    printf("7. 动态结构体:\n");
    
    Student *s1 = createStudent(1001, "张三", 85.5);
    if (s1 != NULL) {
        printf("学生: %d %s %.1f\n", s1->id, s1->name, s1->score);
        free(s1);
    }
    printf("\n");
    
    // 8. 动态分配结构体数组
    printf("8. 动态结构体数组:\n");
    
    int studentCount = 3;
    Student *students = (Student *)malloc(studentCount * sizeof(Student));
    
    if (students != NULL) {
        students[0] = (Student){1001, "张三", 85.5};
        students[1] = (Student){1002, "李四", 90.0};
        students[2] = (Student){1003, "王五", 87.5};
        
        printf("学生列表:\n");
        for (int i = 0; i < studentCount; i++) {
            printf("  %d %s %.1f\n", 
                   students[i].id, 
                   students[i].name, 
                   students[i].score);
        }
        
        free(students);
    }
    printf("\n");
    
    // 9. 动态二维数组
    printf("9. 动态二维数组:\n");
    
    int rows = 3, cols = 4;
    
    // 方法1：一次分配
    int *matrix = (int *)malloc(rows * cols * sizeof(int));
    if (matrix != NULL) {
        // 填充数据
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i * cols + j] = i * cols + j;
            }
        }
        
        // 打印
        printf("矩阵:\n");
        for (int i = 0; i < rows; i++) {
            printf("  ");
            for (int j = 0; j < cols; j++) {
                printf("%2d ", matrix[i * cols + j]);
            }
            printf("\n");
        }
        
        free(matrix);
    }
    printf("\n");
    
    // 10. 动态二维数组（指针数组方式）
    printf("10. 动态二维数组（指针数组）:\n");
    
    int **matrix2 = (int **)malloc(rows * sizeof(int *));
    if (matrix2 != NULL) {
        for (int i = 0; i < rows; i++) {
            matrix2[i] = (int *)malloc(cols * sizeof(int));
        }
        
        // 填充数据
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix2[i][j] = (i + 1) * (j + 1);
            }
        }
        
        // 打印
        printf("乘法表:\n");
        for (int i = 0; i < rows; i++) {
            printf("  ");
            for (int j = 0; j < cols; j++) {
                printf("%2d ", matrix2[i][j]);
            }
            printf("\n");
        }
        
        // 释放内存
        for (int i = 0; i < rows; i++) {
            free(matrix2[i]);
        }
        free(matrix2);
    }
    printf("\n");
    
    // 11. 动态链表
    printf("11. 动态链表:\n");
    
    Node *head = createNode(10);
    head->next = createNode(20);
    head->next->next = createNode(30);
    head->next->next->next = createNode(40);
    
    printf("链表: ");
    printList(head);
    
    freeList(head);
    printf("链表已释放\n\n");
    
    // 12. 内存泄漏示例（错误）
    printf("12. 内存泄漏警告:\n");
    printf("错误示例：\n");
    printf("  int *p = malloc(100);\n");
    printf("  p = malloc(200);  // 泄漏！第一次分配的内存丢失\n");
    printf("\n正确做法：\n");
    printf("  int *p = malloc(100);\n");
    printf("  free(p);  // 先释放\n");
    printf("  p = malloc(200);  // 再分配\n\n");
    
    // 13. 悬空指针示例
    printf("13. 悬空指针警告:\n");
    printf("错误示例：\n");
    printf("  int *p = malloc(100);\n");
    printf("  free(p);\n");
    printf("  *p = 10;  // 危险！p已被释放\n");
    printf("\n正确做法：\n");
    printf("  int *p = malloc(100);\n");
    printf("  free(p);\n");
    printf("  p = NULL;  // 设置为NULL，避免误用\n\n");
    
    // 14. 安全的内存分配模式
    printf("14. 安全的内存管理:\n");
    
    int *safe_ptr = (int *)malloc(10 * sizeof(int));
    if (safe_ptr == NULL) {
        printf("分配失败！\n");
    } else {
        printf("分配成功\n");
        
        // 使用内存
        for (int i = 0; i < 10; i++) {
            safe_ptr[i] = i;
        }
        
        // 释放并设置为NULL
        free(safe_ptr);
        safe_ptr = NULL;
        
        printf("内存已安全释放\n");
    }
    printf("\n");
    
    // 15. 内存分配失败处理
    printf("15. 处理内存分配失败:\n");
    
    // 尝试分配非常大的内存（可能失败）
    size_t huge_size = (size_t)1024 * 1024 * 1024 * 10;  // 10GB
    int *huge = (int *)malloc(huge_size);
    
    if (huge == NULL) {
        printf("无法分配 %zu 字节\n", huge_size);
        printf("可能原因：内存不足\n");
    } else {
        printf("分配成功（不太可能）\n");
        free(huge);
    }
    printf("\n");
    
    // 16. 动态字符串数组
    printf("16. 动态字符串数组:\n");
    
    int nameCount = 3;
    char **names = (char **)malloc(nameCount * sizeof(char *));
    
    if (names != NULL) {
        names[0] = (char *)malloc(20 * sizeof(char));
        names[1] = (char *)malloc(20 * sizeof(char));
        names[2] = (char *)malloc(20 * sizeof(char));
        
        strcpy(names[0], "张三");
        strcpy(names[1], "李四");
        strcpy(names[2], "王五");
        
        printf("姓名列表:\n");
        for (int i = 0; i < nameCount; i++) {
            printf("  %d. %s\n", i + 1, names[i]);
        }
        
        // 释放
        for (int i = 0; i < nameCount; i++) {
            free(names[i]);
        }
        free(names);
    }
    printf("\n");
    
    // 17. realloc缩小内存
    printf("17. realloc缩小内存:\n");
    
    int *arr6 = (int *)malloc(10 * sizeof(int));
    if (arr6 != NULL) {
        for (int i = 0; i < 10; i++) {
            arr6[i] = i;
        }
        
        printf("原始大小: 10个元素\n");
        
        // 缩小到5个
        arr6 = (int *)realloc(arr6, 5 * sizeof(int));
        printf("缩小后: 5个元素\n");
        printf("内容: ");
        printArray(arr6, 5);
        
        free(arr6);
    }
    printf("\n");
    
    // 18. 零大小的malloc
    printf("18. 特殊情况处理:\n");
    
    int *zero = (int *)malloc(0);
    if (zero != NULL) {
        printf("malloc(0) 返回了非NULL指针\n");
        free(zero);  // 仍需要释放
    } else {
        printf("malloc(0) 返回NULL\n");
    }
    printf("\n");
    
    // 19. 多次free的危险
    printf("19. 不要多次释放:\n");
    printf("错误示例：\n");
    printf("  int *p = malloc(100);\n");
    printf("  free(p);\n");
    printf("  free(p);  // 危险！双重释放\n");
    printf("\n正确做法：\n");
    printf("  int *p = malloc(100);\n");
    printf("  free(p);\n");
    printf("  p = NULL;  // 防止再次释放\n\n");
    
    // 20. 内存管理最佳实践
    printf("20. 内存管理最佳实践:\n");
    printf("1. 总是检查malloc/calloc/realloc返回值\n");
    printf("2. 每次malloc都要对应一个free\n");
    printf("3. free后将指针设为NULL\n");
    printf("4. 不要访问已释放的内存\n");
    printf("5. 不要多次释放同一块内存\n");
    printf("6. 注意realloc可能改变指针地址\n");
    printf("7. 使用valgrind等工具检测内存泄漏\n");
    printf("8. 在函数返回前释放局部分配的内存\n");
    printf("9. 复杂结构递归释放\n");
    printf("10. 考虑使用内存池优化性能\n");
    
    return 0;
}

// 打印数组
void printArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 创建学生
Student* createStudent(int id, const char *name, float score) {
    Student *s = (Student *)malloc(sizeof(Student));
    if (s != NULL) {
        s->id = id;
        strncpy(s->name, name, sizeof(s->name) - 1);
        s->name[sizeof(s->name) - 1] = '\0';
        s->score = score;
    }
    return s;
}

// 创建链表节点
Node* createNode(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node != NULL) {
        node->data = data;
        node->next = NULL;
    }
    return node;
}

// 打印链表
void printList(Node *head) {
    Node *current = head;
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
void freeList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

/*
 * 知识点总结：
 * 
 * 动态内存分配概念：
 * 
 * 静态分配（栈）：
 * - 编译时确定大小
 * - 自动管理（自动释放）
 * - 生命周期：函数执行期间
 * - 大小限制：通常几MB
 * - 速度快
 * 
 * 动态分配（堆）：
 * - 运行时分配大小
 * - 手动管理（需要free）
 * - 生命周期：手动控制
 * - 大小限制：系统内存
 * - 速度较慢
 * 
 * malloc() 函数：
 * 
 * void* malloc(size_t size);
 * 
 * - 分配size字节的内存
 * - 返回void*指针（需要类型转换）
 * - 成功返回指针，失败返回NULL
 * - 内存内容未初始化（值不确定）
 * 
 * 使用模式：
 * int *p = (int *)malloc(n * sizeof(int));
 * if (p == NULL) {
 *     // 处理错误
 * }
 * // 使用p
 * free(p);
 * 
 * calloc() 函数：
 * 
 * void* calloc(size_t nmemb, size_t size);
 * 
 * - 分配nmemb个size字节的内存
 * - 自动初始化为0
 * - 返回void*指针
 * - 成功返回指针，失败返回NULL
 * 
 * malloc vs calloc：
 * - malloc: 不初始化，稍快
 * - calloc: 初始化为0，稍慢但安全
 * 
 * 选择：
 * - 需要初始化为0：用calloc
 * - 立即赋值：用malloc
 * 
 * realloc() 函数：
 * 
 * void* realloc(void *ptr, size_t size);
 * 
 * - 调整已分配内存的大小
 * - ptr为NULL时等同于malloc
 * - size为0时等同于free
 * - 可能改变内存地址
 * - 原内容保留（在新大小范围内）
 * 
 * 重要：
 * int *new_ptr = realloc(old_ptr, new_size);
 * if (new_ptr != NULL) {
 *     old_ptr = new_ptr;  // 更新指针
 * } else {
 *     // 处理失败，old_ptr仍有效
 * }
 * 
 * free() 函数：
 * 
 * void free(void *ptr);
 * 
 * - 释放malloc/calloc/realloc分配的内存
 * - ptr必须是这些函数返回的指针
 * - 释放后不应再访问
 * - 可以free(NULL)（安全，无操作）
 * 
 * 注意：
 * - 每次malloc对应一次free
 * - 不要free栈上的内存
 * - 不要多次free
 * - free后建议设置为NULL
 * 
 * 内存泄漏：
 * 
 * 定义：
 * 分配的内存未释放，导致内存无法回收
 * 
 * 常见原因：
 * 1. 忘记free
 * 2. 指针丢失（重新赋值前未free）
 * 3. 函数返回前未释放
 * 4. 异常退出时未清理
 * 
 * 示例：
 * int *p = malloc(100);
 * p = malloc(200);  // 泄漏！第一次的内存丢失
 * 
 * 正确：
 * int *p = malloc(100);
 * free(p);
 * p = malloc(200);
 * 
 * 悬空指针：
 * 
 * 定义：
 * 指向已释放内存的指针
 * 
 * 危险：
 * int *p = malloc(100);
 * free(p);
 * *p = 10;  // 危险！访问已释放的内存
 * 
 * 预防：
 * free(p);
 * p = NULL;  // 防止误用
 * 
 * 双重释放：
 * 
 * 危险：
 * int *p = malloc(100);
 * free(p);
 * free(p);  // 错误！双重释放
 * 
 * 预防：
 * free(p);
 * p = NULL;
 * 
 * 动态数组：
 * 
 * 一维：
 * int *arr = malloc(n * sizeof(int));
 * 
 * 二维（连续内存）：
 * int *matrix = malloc(rows * cols * sizeof(int));
 * matrix[i * cols + j] = value;
 * 
 * 二维（指针数组）：
 * int **matrix = malloc(rows * sizeof(int*));
 * for (int i = 0; i < rows; i++) {
 *     matrix[i] = malloc(cols * sizeof(int));
 * }
 * 
 * 动态结构体：
 * 
 * 单个：
 * Student *s = malloc(sizeof(Student));
 * 
 * 数组：
 * Student *arr = malloc(n * sizeof(Student));
 * 
 * 链表：
 * typedef struct Node {
 *     int data;
 *     struct Node *next;
 * } Node;
 * 
 * Node *node = malloc(sizeof(Node));
 * 
 * 动态字符串：
 * 
 * 分配：
 * char *str = malloc(len * sizeof(char));
 * strcpy(str, "Hello");
 * 
 * 扩展：
 * str = realloc(str, new_len);
 * strcat(str, " World");
 * 
 * 释放：
 * free(str);
 * 
 * 复杂数据结构释放：
 * 
 * 链表：
 * void freeList(Node *head) {
 *     while (head != NULL) {
 *         Node *next = head->next;
 *         free(head);
 *         head = next;
 *     }
 * }
 * 
 * 二维数组（指针数组）：
 * for (int i = 0; i < rows; i++) {
 *     free(matrix[i]);
 * }
 * free(matrix);
 * 
 * 树：递归释放
 * 
 * 内存分配失败：
 * 
 * 原因：
 * - 内存不足
 * - 碎片化
 * - 达到进程限制
 * 
 * 处理：
 * int *p = malloc(size);
 * if (p == NULL) {
 *     fprintf(stderr, "内存分配失败\n");
 *     // 清理已分配的资源
 *     // 返回错误
 *     return -1;
 * }
 * 
 * sizeof运算符：
 * 
 * 正确使用：
 * malloc(n * sizeof(int))
 * malloc(sizeof(struct Student))
 * 
 * 避免：
 * malloc(n * 4)  // 不可移植
 * 
 * 类型转换：
 * 
 * C++需要：
 * int *p = (int *)malloc(...);
 * 
 * C语言可选：
 * int *p = malloc(...);
 * 
 * 建议：加上类型转换，更清晰
 * 
 * 内存对齐：
 * 
 * malloc返回的内存适合任何类型
 * 自动满足对齐要求
 * 
 * 最佳实践：
 * 
 * 1. 检查返回值
 * 2. 配对malloc/free
 * 3. free后设NULL
 * 4. 使用sizeof
 * 5. 避免内存泄漏
 * 6. 避免悬空指针
 * 7. 不要double free
 * 8. 函数返回前清理
 * 9. 异常处理
 * 10. 使用工具检测
 * 
 * 调试工具：
 * 
 * - valgrind（Linux）
 * - AddressSanitizer
 * - Visual Studio内存检测
 * - 自定义内存跟踪
 * 
 * 性能考虑：
 * 
 * - malloc/free有开销
 * - 频繁分配影响性能
 * - 考虑内存池
 * - 批量分配
 * - 减少碎片化
 * 
 * 常见错误：
 * 
 * 1. 不检查NULL
 * 2. 忘记free
 * 3. 访问已释放内存
 * 4. 数组越界
 * 5. 大小计算错误
 * 6. 类型不匹配
 */
