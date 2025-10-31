/*
 * 第十四章：数据结构
 * 14.1 链表实现
 * 
 * 学习目标：
 * 1. 理解链表的基本概念和特点
 * 2. 掌握单向链表的实现
 * 3. 学习双向链表的实现
 * 4. 了解循环链表的应用
 * 5. 掌握链表的常见操作（插入、删除、查找、反转等）
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==================== 单向链表 ====================

// 单向链表节点定义
typedef struct SNode {
    int data;                // 数据域
    struct SNode *next;      // 指针域：指向下一个节点
} SNode;

// 单向链表结构
typedef struct {
    SNode *head;             // 头指针
    int size;                // 链表大小
} SLinkedList;

// 创建单向链表
SLinkedList* createSLinkedList() {
    SLinkedList *list = (SLinkedList*)malloc(sizeof(SLinkedList));
    list->head = NULL;
    list->size = 0;
    return list;
}

// 在单向链表头部插入节点
void sListInsertHead(SLinkedList *list, int data) {
    SNode *newNode = (SNode*)malloc(sizeof(SNode));
    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;
    list->size++;
}

// 在单向链表尾部插入节点
void sListInsertTail(SLinkedList *list, int data) {
    SNode *newNode = (SNode*)malloc(sizeof(SNode));
    newNode->data = data;
    newNode->next = NULL;
    
    if (list->head == NULL) {
        // 链表为空
        list->head = newNode;
    } else {
        // 找到最后一个节点
        SNode *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    list->size++;
}

// 在指定位置插入节点
int sListInsertAt(SLinkedList *list, int index, int data) {
    if (index < 0 || index > list->size) {
        return 0;  // 索引无效
    }
    
    if (index == 0) {
        sListInsertHead(list, data);
        return 1;
    }
    
    SNode *newNode = (SNode*)malloc(sizeof(SNode));
    newNode->data = data;
    
    SNode *current = list->head;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }
    
    newNode->next = current->next;
    current->next = newNode;
    list->size++;
    return 1;
}

// 删除单向链表头部节点
int sListDeleteHead(SLinkedList *list) {
    if (list->head == NULL) {
        return 0;  // 链表为空
    }
    
    SNode *temp = list->head;
    list->head = list->head->next;
    free(temp);
    list->size--;
    return 1;
}

// 删除指定值的节点（删除第一个匹配的节点）
int sListDeleteValue(SLinkedList *list, int data) {
    if (list->head == NULL) {
        return 0;
    }
    
    // 如果要删除的是头节点
    if (list->head->data == data) {
        return sListDeleteHead(list);
    }
    
    // 查找要删除的节点
    SNode *current = list->head;
    while (current->next != NULL && current->next->data != data) {
        current = current->next;
    }
    
    if (current->next == NULL) {
        return 0;  // 未找到
    }
    
    SNode *temp = current->next;
    current->next = current->next->next;
    free(temp);
    list->size--;
    return 1;
}

// 查找节点
SNode* sListFind(SLinkedList *list, int data) {
    SNode *current = list->head;
    while (current != NULL) {
        if (current->data == data) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// 反转单向链表
void sListReverse(SLinkedList *list) {
    SNode *prev = NULL;
    SNode *current = list->head;
    SNode *next = NULL;
    
    while (current != NULL) {
        next = current->next;     // 保存下一个节点
        current->next = prev;     // 反转指针
        prev = current;           // 移动prev
        current = next;           // 移动current
    }
    
    list->head = prev;
}

// 打印单向链表
void printSLinkedList(SLinkedList *list) {
    SNode *current = list->head;
    printf("[");
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("]\n");
}

// 释放单向链表
void freeSLinkedList(SLinkedList *list) {
    SNode *current = list->head;
    while (current != NULL) {
        SNode *temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

// ==================== 双向链表 ====================

// 双向链表节点定义
typedef struct DNode {
    int data;                // 数据域
    struct DNode *prev;      // 前驱指针
    struct DNode *next;      // 后继指针
} DNode;

// 双向链表结构
typedef struct {
    DNode *head;             // 头指针
    DNode *tail;             // 尾指针
    int size;                // 链表大小
} DLinkedList;

// 创建双向链表
DLinkedList* createDLinkedList() {
    DLinkedList *list = (DLinkedList*)malloc(sizeof(DLinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

// 在双向链表头部插入节点
void dListInsertHead(DLinkedList *list, int data) {
    DNode *newNode = (DNode*)malloc(sizeof(DNode));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = list->head;
    
    if (list->head == NULL) {
        // 链表为空
        list->tail = newNode;
    } else {
        list->head->prev = newNode;
    }
    
    list->head = newNode;
    list->size++;
}

// 在双向链表尾部插入节点
void dListInsertTail(DLinkedList *list, int data) {
    DNode *newNode = (DNode*)malloc(sizeof(DNode));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = list->tail;
    
    if (list->tail == NULL) {
        // 链表为空
        list->head = newNode;
    } else {
        list->tail->next = newNode;
    }
    
    list->tail = newNode;
    list->size++;
}

// 删除双向链表头部节点
int dListDeleteHead(DLinkedList *list) {
    if (list->head == NULL) {
        return 0;
    }
    
    DNode *temp = list->head;
    list->head = list->head->next;
    
    if (list->head == NULL) {
        // 链表变为空
        list->tail = NULL;
    } else {
        list->head->prev = NULL;
    }
    
    free(temp);
    list->size--;
    return 1;
}

// 删除双向链表尾部节点
int dListDeleteTail(DLinkedList *list) {
    if (list->tail == NULL) {
        return 0;
    }
    
    DNode *temp = list->tail;
    list->tail = list->tail->prev;
    
    if (list->tail == NULL) {
        // 链表变为空
        list->head = NULL;
    } else {
        list->tail->next = NULL;
    }
    
    free(temp);
    list->size--;
    return 1;
}

// 打印双向链表（正向）
void printDLinkedList(DLinkedList *list) {
    DNode *current = list->head;
    printf("[");
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" <-> ");
        }
        current = current->next;
    }
    printf("]\n");
}

// 打印双向链表（反向）
void printDLinkedListReverse(DLinkedList *list) {
    DNode *current = list->tail;
    printf("[");
    while (current != NULL) {
        printf("%d", current->data);
        if (current->prev != NULL) {
            printf(" <-> ");
        }
        current = current->prev;
    }
    printf("]\n");
}

// 释放双向链表
void freeDLinkedList(DLinkedList *list) {
    DNode *current = list->head;
    while (current != NULL) {
        DNode *temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

// ==================== 循环链表 ====================

// 循环链表结构（使用单向链表节点）
typedef struct {
    SNode *head;             // 头指针
    int size;                // 链表大小
} CircularList;

// 创建循环链表
CircularList* createCircularList() {
    CircularList *list = (CircularList*)malloc(sizeof(CircularList));
    list->head = NULL;
    list->size = 0;
    return list;
}

// 在循环链表尾部插入节点
void cListInsert(CircularList *list, int data) {
    SNode *newNode = (SNode*)malloc(sizeof(SNode));
    newNode->data = data;
    
    if (list->head == NULL) {
        // 链表为空，新节点指向自己
        newNode->next = newNode;
        list->head = newNode;
    } else {
        // 找到最后一个节点
        SNode *current = list->head;
        while (current->next != list->head) {
            current = current->next;
        }
        current->next = newNode;
        newNode->next = list->head;
    }
    list->size++;
}

// 打印循环链表
void printCircularList(CircularList *list) {
    if (list->head == NULL) {
        printf("[]\n");
        return;
    }
    
    SNode *current = list->head;
    printf("[");
    do {
        printf("%d", current->data);
        current = current->next;
        if (current != list->head) {
            printf(" -> ");
        }
    } while (current != list->head);
    printf(" -> (循环)]\n");
}

// 释放循环链表
void freeCircularList(CircularList *list) {
    if (list->head == NULL) {
        free(list);
        return;
    }
    
    SNode *current = list->head;
    SNode *first = list->head;
    do {
        SNode *temp = current;
        current = current->next;
        free(temp);
    } while (current != first);
    
    free(list);
}

// ==================== 链表应用示例 ====================

// 示例1：约瑟夫环问题（使用循环链表）
void josephusProblem(int n, int m) {
    printf("\n约瑟夫环问题：n=%d, m=%d\n", n, m);
    
    // 创建循环链表
    CircularList *list = createCircularList();
    for (int i = 1; i <= n; i++) {
        cListInsert(list, i);
    }
    
    printf("初始序列：");
    printCircularList(list);
    
    // 报数淘汰
    SNode *current = list->head;
    SNode *prev = NULL;
    
    // 找到最后一个节点
    while (current->next != list->head) {
        current = current->next;
    }
    prev = current;
    current = list->head;
    
    printf("出列顺序：");
    while (list->size > 1) {
        // 报数m-1次
        for (int i = 1; i < m; i++) {
            prev = current;
            current = current->next;
        }
        
        // 淘汰当前节点
        printf("%d ", current->data);
        prev->next = current->next;
        
        if (current == list->head) {
            list->head = current->next;
        }
        
        SNode *temp = current;
        current = current->next;
        free(temp);
        list->size--;
    }
    
    printf("\n最后幸存者：%d\n", current->data);
    free(current);
    free(list);
}

// 示例2：检测链表是否有环
int hasCycle(SNode *head) {
    if (head == NULL || head->next == NULL) {
        return 0;
    }
    
    // 快慢指针法
    SNode *slow = head;
    SNode *fast = head;
    
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;           // 慢指针走一步
        fast = fast->next->next;     // 快指针走两步
        
        if (slow == fast) {
            return 1;  // 有环
        }
    }
    
    return 0;  // 无环
}

// 示例3：合并两个有序链表
SLinkedList* mergeSortedLists(SLinkedList *list1, SLinkedList *list2) {
    SLinkedList *result = createSLinkedList();
    SNode *p1 = list1->head;
    SNode *p2 = list2->head;
    
    SNode *tail = NULL;
    
    while (p1 != NULL && p2 != NULL) {
        SNode *newNode = (SNode*)malloc(sizeof(SNode));
        
        if (p1->data <= p2->data) {
            newNode->data = p1->data;
            p1 = p1->next;
        } else {
            newNode->data = p2->data;
            p2 = p2->next;
        }
        
        newNode->next = NULL;
        
        if (result->head == NULL) {
            result->head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        result->size++;
    }
    
    // 处理剩余节点
    SNode *remaining = (p1 != NULL) ? p1 : p2;
    while (remaining != NULL) {
        SNode *newNode = (SNode*)malloc(sizeof(SNode));
        newNode->data = remaining->data;
        newNode->next = NULL;
        
        tail->next = newNode;
        tail = newNode;
        remaining = remaining->next;
        result->size++;
    }
    
    return result;
}

// ==================== 主函数 ====================

int main() {
    printf("=== 链表数据结构 ===\n\n");
    
    // 1. 单向链表演示
    printf("1. 单向链表操作:\n");
    SLinkedList *sList = createSLinkedList();
    
    printf("在头部插入: 3, 2, 1\n");
    sListInsertHead(sList, 3);
    sListInsertHead(sList, 2);
    sListInsertHead(sList, 1);
    printf("链表内容: ");
    printSLinkedList(sList);
    
    printf("\n在尾部插入: 4, 5\n");
    sListInsertTail(sList, 4);
    sListInsertTail(sList, 5);
    printf("链表内容: ");
    printSLinkedList(sList);
    
    printf("\n在位置2插入: 10\n");
    sListInsertAt(sList, 2, 10);
    printf("链表内容: ");
    printSLinkedList(sList);
    
    printf("\n查找值为4的节点: ");
    SNode *found = sListFind(sList, 4);
    if (found) {
        printf("找到了，值为 %d\n", found->data);
    }
    
    printf("\n删除值为10的节点\n");
    sListDeleteValue(sList, 10);
    printf("链表内容: ");
    printSLinkedList(sList);
    
    printf("\n反转链表\n");
    sListReverse(sList);
    printf("链表内容: ");
    printSLinkedList(sList);
    
    printf("链表大小: %d\n", sList->size);
    
    // 2. 双向链表演示
    printf("\n\n2. 双向链表操作:\n");
    DLinkedList *dList = createDLinkedList();
    
    printf("在尾部插入: 1, 2, 3, 4, 5\n");
    for (int i = 1; i <= 5; i++) {
        dListInsertTail(dList, i);
    }
    printf("正向遍历: ");
    printDLinkedList(dList);
    printf("反向遍历: ");
    printDLinkedListReverse(dList);
    
    printf("\n在头部插入: 0\n");
    dListInsertHead(dList, 0);
    printf("正向遍历: ");
    printDLinkedList(dList);
    
    printf("\n删除头节点\n");
    dListDeleteHead(dList);
    printf("正向遍历: ");
    printDLinkedList(dList);
    
    printf("\n删除尾节点\n");
    dListDeleteTail(dList);
    printf("正向遍历: ");
    printDLinkedList(dList);
    
    printf("链表大小: %d\n", dList->size);
    
    // 3. 循环链表演示
    printf("\n\n3. 循环链表操作:\n");
    CircularList *cList = createCircularList();
    
    printf("插入: 1, 2, 3, 4, 5\n");
    for (int i = 1; i <= 5; i++) {
        cListInsert(cList, i);
    }
    printf("循环链表: ");
    printCircularList(cList);
    
    // 4. 约瑟夫环问题
    printf("\n\n4. 约瑟夫环问题演示:\n");
    josephusProblem(7, 3);
    
    // 5. 合并有序链表
    printf("\n\n5. 合并两个有序链表:\n");
    SLinkedList *list1 = createSLinkedList();
    SLinkedList *list2 = createSLinkedList();
    
    printf("链表1: ");
    sListInsertTail(list1, 1);
    sListInsertTail(list1, 3);
    sListInsertTail(list1, 5);
    printSLinkedList(list1);
    
    printf("链表2: ");
    sListInsertTail(list2, 2);
    sListInsertTail(list2, 4);
    sListInsertTail(list2, 6);
    printSLinkedList(list2);
    
    SLinkedList *merged = mergeSortedLists(list1, list2);
    printf("合并后: ");
    printSLinkedList(merged);
    
    // 释放内存
    freeSLinkedList(sList);
    freeDLinkedList(dList);
    freeCircularList(cList);
    freeSLinkedList(list1);
    freeSLinkedList(list2);
    freeSLinkedList(merged);
    
    printf("\n=== 程序结束 ===\n");
    
    return 0;
}
