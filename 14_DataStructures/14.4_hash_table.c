/*
 * 第十四章：数据结构
 * 14.4 哈希表实现
 * 
 * 学习目标：
 * 1. 理解哈希表的基本原理
 * 2. 掌握哈希函数的设计
 * 3. 学习冲突解决方法（链地址法、开放地址法）
 * 4. 实现哈希表的插入、查找、删除操作
 * 5. 了解哈希表的负载因子和动态扩容
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10
#define LOAD_FACTOR_THRESHOLD 0.7

// ==================== 链地址法实现哈希表 ====================

// 哈希表节点（链表节点）
typedef struct HashNode {
    int key;                     // 键
    int value;                   // 值
    struct HashNode *next;       // 指向下一个节点
} HashNode;

// 哈希表结构（链地址法）
typedef struct {
    HashNode **buckets;          // 桶数组（指针数组）
    int size;                    // 哈希表大小
    int count;                   // 当前元素个数
} HashTable;

// 哈希函数（除留余数法）
int hashFunction(int key, int tableSize) {
    return abs(key) % tableSize;
}

// 创建哈希表
HashTable* createHashTable(int size) {
    HashTable *table = (HashTable*)malloc(sizeof(HashTable));
    table->size = size;
    table->count = 0;
    
    // 分配桶数组
    table->buckets = (HashNode**)malloc(sizeof(HashNode*) * size);
    
    // 初始化每个桶为NULL
    for (int i = 0; i < size; i++) {
        table->buckets[i] = NULL;
    }
    
    return table;
}

// 插入或更新键值对
void hashTableInsert(HashTable *table, int key, int value) {
    int index = hashFunction(key, table->size);
    
    // 检查键是否已存在
    HashNode *current = table->buckets[index];
    while (current != NULL) {
        if (current->key == key) {
            current->value = value;  // 更新值
            return;
        }
        current = current->next;
    }
    
    // 键不存在，创建新节点并插入到链表头部
    HashNode *newNode = (HashNode*)malloc(sizeof(HashNode));
    newNode->key = key;
    newNode->value = value;
    newNode->next = table->buckets[index];
    table->buckets[index] = newNode;
    table->count++;
}

// 查找键对应的值
int hashTableSearch(HashTable *table, int key, int *value) {
    int index = hashFunction(key, table->size);
    
    HashNode *current = table->buckets[index];
    while (current != NULL) {
        if (current->key == key) {
            *value = current->value;
            return 1;  // 找到
        }
        current = current->next;
    }
    
    return 0;  // 未找到
}

// 删除键值对
int hashTableDelete(HashTable *table, int key) {
    int index = hashFunction(key, table->size);
    
    HashNode *current = table->buckets[index];
    HashNode *prev = NULL;
    
    while (current != NULL) {
        if (current->key == key) {
            if (prev == NULL) {
                // 删除的是第一个节点
                table->buckets[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            table->count--;
            return 1;  // 删除成功
        }
        prev = current;
        current = current->next;
    }
    
    return 0;  // 未找到
}

// 计算负载因子
float getLoadFactor(HashTable *table) {
    return (float)table->count / table->size;
}

// 打印哈希表
void printHashTable(HashTable *table) {
    printf("哈希表内容（大小: %d, 元素数: %d, 负载因子: %.2f）:\n", 
           table->size, table->count, getLoadFactor(table));
    
    for (int i = 0; i < table->size; i++) {
        printf("桶[%d]: ", i);
        
        HashNode *current = table->buckets[i];
        if (current == NULL) {
            printf("空\n");
        } else {
            while (current != NULL) {
                printf("(%d:%d)", current->key, current->value);
                if (current->next != NULL) {
                    printf(" -> ");
                }
                current = current->next;
            }
            printf("\n");
        }
    }
}

// 释放哈希表
void freeHashTable(HashTable *table) {
    for (int i = 0; i < table->size; i++) {
        HashNode *current = table->buckets[i];
        while (current != NULL) {
            HashNode *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(table->buckets);
    free(table);
}

// ==================== 开放地址法（线性探测）实现哈希表 ====================

// 哈希表项状态
typedef enum {
    EMPTY,      // 空
    OCCUPIED,   // 已占用
    DELETED     // 已删除
} Status;

// 哈希表项
typedef struct {
    int key;
    int value;
    Status status;
} HashItem;

// 开放地址法哈希表
typedef struct {
    HashItem *items;             // 哈希表项数组
    int size;                    // 哈希表大小
    int count;                   // 当前元素个数
} OpenHashTable;

// 创建开放地址法哈希表
OpenHashTable* createOpenHashTable(int size) {
    OpenHashTable *table = (OpenHashTable*)malloc(sizeof(OpenHashTable));
    table->size = size;
    table->count = 0;
    
    table->items = (HashItem*)malloc(sizeof(HashItem) * size);
    
    // 初始化所有项为空
    for (int i = 0; i < size; i++) {
        table->items[i].status = EMPTY;
    }
    
    return table;
}

// 线性探测法插入
int openHashInsert(OpenHashTable *table, int key, int value) {
    if (table->count >= table->size) {
        printf("哈希表已满！\n");
        return 0;
    }
    
    int index = hashFunction(key, table->size);
    int originalIndex = index;
    
    // 线性探测
    while (table->items[index].status == OCCUPIED) {
        if (table->items[index].key == key) {
            // 键已存在，更新值
            table->items[index].value = value;
            return 1;
        }
        
        index = (index + 1) % table->size;  // 线性探测下一个位置
        
        if (index == originalIndex) {
            printf("哈希表已满！\n");
            return 0;
        }
    }
    
    // 找到空位置或已删除位置，插入
    table->items[index].key = key;
    table->items[index].value = value;
    table->items[index].status = OCCUPIED;
    table->count++;
    
    return 1;
}

// 线性探测法查找
int openHashSearch(OpenHashTable *table, int key, int *value) {
    int index = hashFunction(key, table->size);
    int originalIndex = index;
    
    while (table->items[index].status != EMPTY) {
        if (table->items[index].status == OCCUPIED && 
            table->items[index].key == key) {
            *value = table->items[index].value;
            return 1;  // 找到
        }
        
        index = (index + 1) % table->size;
        
        if (index == originalIndex) {
            break;  // 已经遍历完整个表
        }
    }
    
    return 0;  // 未找到
}

// 线性探测法删除
int openHashDelete(OpenHashTable *table, int key) {
    int index = hashFunction(key, table->size);
    int originalIndex = index;
    
    while (table->items[index].status != EMPTY) {
        if (table->items[index].status == OCCUPIED && 
            table->items[index].key == key) {
            table->items[index].status = DELETED;
            table->count--;
            return 1;  // 删除成功
        }
        
        index = (index + 1) % table->size;
        
        if (index == originalIndex) {
            break;
        }
    }
    
    return 0;  // 未找到
}

// 打印开放地址法哈希表
void printOpenHashTable(OpenHashTable *table) {
    printf("开放地址法哈希表（大小: %d, 元素数: %d, 负载因子: %.2f）:\n", 
           table->size, table->count, (float)table->count / table->size);
    
    for (int i = 0; i < table->size; i++) {
        printf("位置[%d]: ", i);
        
        if (table->items[i].status == EMPTY) {
            printf("空\n");
        } else if (table->items[i].status == DELETED) {
            printf("已删除\n");
        } else {
            printf("(%d:%d)\n", table->items[i].key, table->items[i].value);
        }
    }
}

// 释放开放地址法哈希表
void freeOpenHashTable(OpenHashTable *table) {
    free(table->items);
    free(table);
}

// ==================== 字符串哈希表 ====================

// 字符串哈希节点
typedef struct StringHashNode {
    char *key;                   // 字符串键
    int value;                   // 值
    struct StringHashNode *next;
} StringHashNode;

// 字符串哈希表
typedef struct {
    StringHashNode **buckets;
    int size;
    int count;
} StringHashTable;

// 字符串哈希函数（DJB2算法）
unsigned int stringHashFunction(const char *str, int tableSize) {
    unsigned long hash = 5381;
    int c;
    
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }
    
    return hash % tableSize;
}

// 创建字符串哈希表
StringHashTable* createStringHashTable(int size) {
    StringHashTable *table = (StringHashTable*)malloc(sizeof(StringHashTable));
    table->size = size;
    table->count = 0;
    
    table->buckets = (StringHashNode**)malloc(sizeof(StringHashNode*) * size);
    
    for (int i = 0; i < size; i++) {
        table->buckets[i] = NULL;
    }
    
    return table;
}

// 字符串哈希表插入
void stringHashInsert(StringHashTable *table, const char *key, int value) {
    int index = stringHashFunction(key, table->size);
    
    // 检查键是否已存在
    StringHashNode *current = table->buckets[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;  // 更新值
            return;
        }
        current = current->next;
    }
    
    // 创建新节点
    StringHashNode *newNode = (StringHashNode*)malloc(sizeof(StringHashNode));
    newNode->key = (char*)malloc(strlen(key) + 1);
    strcpy(newNode->key, key);
    newNode->value = value;
    newNode->next = table->buckets[index];
    table->buckets[index] = newNode;
    table->count++;
}

// 字符串哈希表查找
int stringHashSearch(StringHashTable *table, const char *key, int *value) {
    int index = stringHashFunction(key, table->size);
    
    StringHashNode *current = table->buckets[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            *value = current->value;
            return 1;
        }
        current = current->next;
    }
    
    return 0;
}

// 打印字符串哈希表
void printStringHashTable(StringHashTable *table) {
    printf("字符串哈希表内容:\n");
    
    for (int i = 0; i < table->size; i++) {
        printf("桶[%d]: ", i);
        
        StringHashNode *current = table->buckets[i];
        if (current == NULL) {
            printf("空\n");
        } else {
            while (current != NULL) {
                printf("(\"%s\":%d)", current->key, current->value);
                if (current->next != NULL) {
                    printf(" -> ");
                }
                current = current->next;
            }
            printf("\n");
        }
    }
}

// 释放字符串哈希表
void freeStringHashTable(StringHashTable *table) {
    for (int i = 0; i < table->size; i++) {
        StringHashNode *current = table->buckets[i];
        while (current != NULL) {
            StringHashNode *temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
    free(table->buckets);
    free(table);
}

// ==================== 哈希表应用示例 ====================

// 应用1：统计数组中元素出现的频率
void countFrequency(int arr[], int n) {
    HashTable *table = createHashTable(TABLE_SIZE);
    
    printf("统计数组元素频率:\n");
    printf("数组: [");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n\n");
    
    // 统计频率
    for (int i = 0; i < n; i++) {
        int count;
        if (hashTableSearch(table, arr[i], &count)) {
            hashTableInsert(table, arr[i], count + 1);
        } else {
            hashTableInsert(table, arr[i], 1);
        }
    }
    
    // 输出频率
    printf("元素频率:\n");
    for (int i = 0; i < table->size; i++) {
        HashNode *current = table->buckets[i];
        while (current != NULL) {
            printf("元素 %d 出现 %d 次\n", current->key, current->value);
            current = current->next;
        }
    }
    
    freeHashTable(table);
}

// 应用2：查找数组中的第一个重复元素
int findFirstDuplicate(int arr[], int n) {
    HashTable *table = createHashTable(TABLE_SIZE);
    
    for (int i = 0; i < n; i++) {
        int value;
        if (hashTableSearch(table, arr[i], &value)) {
            freeHashTable(table);
            return arr[i];  // 找到第一个重复元素
        }
        hashTableInsert(table, arr[i], 1);
    }
    
    freeHashTable(table);
    return -1;  // 没有重复元素
}

// ==================== 主函数 ====================

int main() {
    printf("=== 哈希表数据结构 ===\n\n");
    
    // 1. 链地址法哈希表演示
    printf("1. 链地址法哈希表:\n");
    HashTable *chainTable = createHashTable(TABLE_SIZE);
    
    printf("插入键值对: (5,50), (15,150), (25,250), (35,350), (45,450)\n");
    hashTableInsert(chainTable, 5, 50);
    hashTableInsert(chainTable, 15, 150);
    hashTableInsert(chainTable, 25, 250);
    hashTableInsert(chainTable, 35, 350);
    hashTableInsert(chainTable, 45, 450);
    
    printf("\n");
    printHashTable(chainTable);
    
    printf("\n查找键15: ");
    int value;
    if (hashTableSearch(chainTable, 15, &value)) {
        printf("找到，值为 %d\n", value);
    } else {
        printf("未找到\n");
    }
    
    printf("\n删除键25\n");
    hashTableDelete(chainTable, 25);
    printHashTable(chainTable);
    
    // 2. 开放地址法哈希表演示
    printf("\n\n2. 开放地址法（线性探测）哈希表:\n");
    OpenHashTable *openTable = createOpenHashTable(TABLE_SIZE);
    
    printf("插入键值对: (12,120), (22,220), (32,320), (42,420)\n");
    openHashInsert(openTable, 12, 120);
    openHashInsert(openTable, 22, 220);
    openHashInsert(openTable, 32, 320);
    openHashInsert(openTable, 42, 420);
    
    printf("\n");
    printOpenHashTable(openTable);
    
    printf("\n查找键22: ");
    if (openHashSearch(openTable, 22, &value)) {
        printf("找到，值为 %d\n", value);
    } else {
        printf("未找到\n");
    }
    
    printf("\n删除键22\n");
    openHashDelete(openTable, 22);
    printOpenHashTable(openTable);
    
    // 3. 字符串哈希表演示
    printf("\n\n3. 字符串哈希表:\n");
    StringHashTable *strTable = createStringHashTable(TABLE_SIZE);
    
    printf("插入学生成绩:\n");
    stringHashInsert(strTable, "张三", 85);
    stringHashInsert(strTable, "李四", 92);
    stringHashInsert(strTable, "王五", 78);
    stringHashInsert(strTable, "赵六", 88);
    
    printf("\n");
    printStringHashTable(strTable);
    
    printf("\n查找学生'李四'的成绩: ");
    if (stringHashSearch(strTable, "李四", &value)) {
        printf("%d分\n", value);
    } else {
        printf("未找到\n");
    }
    
    // 4. 应用：统计元素频率
    printf("\n\n4. 应用示例 - 统计元素频率:\n");
    int arr1[] = {1, 2, 3, 2, 4, 1, 5, 2, 6, 1};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    countFrequency(arr1, n1);
    
    // 5. 应用：查找第一个重复元素
    printf("\n\n5. 应用示例 - 查找第一个重复元素:\n");
    int arr2[] = {10, 20, 30, 40, 20, 50};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("数组: [");
    for (int i = 0; i < n2; i++) {
        printf("%d", arr2[i]);
        if (i < n2 - 1) printf(", ");
    }
    printf("]\n");
    
    int duplicate = findFirstDuplicate(arr2, n2);
    if (duplicate != -1) {
        printf("第一个重复元素: %d\n", duplicate);
    } else {
        printf("没有重复元素\n");
    }
    
    // 6. 哈希冲突演示
    printf("\n\n6. 哈希冲突演示:\n");
    printf("插入键 5, 15, 25 (都映射到同一个桶)\n");
    HashTable *collisionTable = createHashTable(TABLE_SIZE);
    hashTableInsert(collisionTable, 5, 50);
    hashTableInsert(collisionTable, 15, 150);
    hashTableInsert(collisionTable, 25, 250);
    
    printf("\n");
    printHashTable(collisionTable);
    printf("\n注意：所有元素都在桶[5]中形成链表\n");
    
    // 释放内存
    freeHashTable(chainTable);
    freeOpenHashTable(openTable);
    freeStringHashTable(strTable);
    freeHashTable(collisionTable);
    
    printf("\n=== 程序结束 ===\n");
    
    return 0;
}
