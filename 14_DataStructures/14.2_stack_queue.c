/*
 * 第十四章：数据结构
 * 14.2 栈和队列实现
 * 
 * 学习目标：
 * 1. 理解栈的LIFO（后进先出）特性
 * 2. 掌握栈的数组和链表实现
 * 3. 理解队列的FIFO（先进先出）特性
 * 4. 掌握队列的数组和链表实现
 * 5. 学习循环队列的实现
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// ==================== 数组实现的栈 ====================

// 数组栈结构
typedef struct {
    int data[MAX_SIZE];      // 数据数组
    int top;                 // 栈顶指针
} ArrayStack;

// 创建数组栈
ArrayStack* createArrayStack() {
    ArrayStack *stack = (ArrayStack*)malloc(sizeof(ArrayStack));
    stack->top = -1;  // 初始栈顶为-1，表示空栈
    return stack;
}

// 判断栈是否为空
int isStackEmpty(ArrayStack *stack) {
    return stack->top == -1;
}

// 判断栈是否已满
int isStackFull(ArrayStack *stack) {
    return stack->top == MAX_SIZE - 1;
}

// 入栈
int push(ArrayStack *stack, int value) {
    if (isStackFull(stack)) {
        printf("栈已满，无法入栈！\n");
        return 0;
    }
    stack->data[++stack->top] = value;
    return 1;
}

// 出栈
int pop(ArrayStack *stack, int *value) {
    if (isStackEmpty(stack)) {
        printf("栈为空，无法出栈！\n");
        return 0;
    }
    *value = stack->data[stack->top--];
    return 1;
}

// 查看栈顶元素
int peek(ArrayStack *stack, int *value) {
    if (isStackEmpty(stack)) {
        printf("栈为空！\n");
        return 0;
    }
    *value = stack->data[stack->top];
    return 1;
}

// 获取栈的大小
int getStackSize(ArrayStack *stack) {
    return stack->top + 1;
}

// 打印栈内容
void printStack(ArrayStack *stack) {
    if (isStackEmpty(stack)) {
        printf("栈为空\n");
        return;
    }
    printf("栈内容（栈顶->栈底）: [");
    for (int i = stack->top; i >= 0; i--) {
        printf("%d", stack->data[i]);
        if (i > 0) printf(", ");
    }
    printf("]\n");
}

// ==================== 链表实现的栈 ====================

// 链表节点
typedef struct StackNode {
    int data;
    struct StackNode *next;
} StackNode;

// 链表栈结构
typedef struct {
    StackNode *top;          // 栈顶指针
    int size;                // 栈大小
} LinkedStack;

// 创建链表栈
LinkedStack* createLinkedStack() {
    LinkedStack *stack = (LinkedStack*)malloc(sizeof(LinkedStack));
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

// 判断链表栈是否为空
int isLinkedStackEmpty(LinkedStack *stack) {
    return stack->top == NULL;
}

// 链表栈入栈
void linkedStackPush(LinkedStack *stack, int value) {
    StackNode *newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->data = value;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
}

// 链表栈出栈
int linkedStackPop(LinkedStack *stack, int *value) {
    if (isLinkedStackEmpty(stack)) {
        printf("栈为空，无法出栈！\n");
        return 0;
    }
    StackNode *temp = stack->top;
    *value = temp->data;
    stack->top = stack->top->next;
    free(temp);
    stack->size--;
    return 1;
}

// 打印链表栈
void printLinkedStack(LinkedStack *stack) {
    if (isLinkedStackEmpty(stack)) {
        printf("栈为空\n");
        return;
    }
    printf("栈内容（栈顶->栈底）: [");
    StackNode *current = stack->top;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) printf(", ");
        current = current->next;
    }
    printf("]\n");
}

// 释放链表栈
void freeLinkedStack(LinkedStack *stack) {
    while (!isLinkedStackEmpty(stack)) {
        int temp;
        linkedStackPop(stack, &temp);
    }
    free(stack);
}

// ==================== 数组实现的队列 ====================

// 数组队列结构（简单队列）
typedef struct {
    int data[MAX_SIZE];      // 数据数组
    int front;               // 队头指针
    int rear;                // 队尾指针
} ArrayQueue;

// 创建数组队列
ArrayQueue* createArrayQueue() {
    ArrayQueue *queue = (ArrayQueue*)malloc(sizeof(ArrayQueue));
    queue->front = 0;
    queue->rear = 0;
    return queue;
}

// 判断队列是否为空
int isQueueEmpty(ArrayQueue *queue) {
    return queue->front == queue->rear;
}

// 判断队列是否已满
int isQueueFull(ArrayQueue *queue) {
    return queue->rear == MAX_SIZE;
}

// 入队
int enqueue(ArrayQueue *queue, int value) {
    if (isQueueFull(queue)) {
        printf("队列已满，无法入队！\n");
        return 0;
    }
    queue->data[queue->rear++] = value;
    return 1;
}

// 出队
int dequeue(ArrayQueue *queue, int *value) {
    if (isQueueEmpty(queue)) {
        printf("队列为空，无法出队！\n");
        return 0;
    }
    *value = queue->data[queue->front++];
    return 1;
}

// 打印队列
void printQueue(ArrayQueue *queue) {
    if (isQueueEmpty(queue)) {
        printf("队列为空\n");
        return;
    }
    printf("队列内容（队头->队尾）: [");
    for (int i = queue->front; i < queue->rear; i++) {
        printf("%d", queue->data[i]);
        if (i < queue->rear - 1) printf(", ");
    }
    printf("]\n");
}

// ==================== 循环队列 ====================

// 循环队列结构
typedef struct {
    int data[MAX_SIZE];      // 数据数组
    int front;               // 队头指针
    int rear;                // 队尾指针
    int size;                // 当前元素个数
} CircularQueue;

// 创建循环队列
CircularQueue* createCircularQueue() {
    CircularQueue *queue = (CircularQueue*)malloc(sizeof(CircularQueue));
    queue->front = 0;
    queue->rear = 0;
    queue->size = 0;
    return queue;
}

// 判断循环队列是否为空
int isCircularQueueEmpty(CircularQueue *queue) {
    return queue->size == 0;
}

// 判断循环队列是否已满
int isCircularQueueFull(CircularQueue *queue) {
    return queue->size == MAX_SIZE;
}

// 循环队列入队
int circularEnqueue(CircularQueue *queue, int value) {
    if (isCircularQueueFull(queue)) {
        printf("循环队列已满，无法入队！\n");
        return 0;
    }
    queue->data[queue->rear] = value;
    queue->rear = (queue->rear + 1) % MAX_SIZE;  // 循环
    queue->size++;
    return 1;
}

// 循环队列出队
int circularDequeue(CircularQueue *queue, int *value) {
    if (isCircularQueueEmpty(queue)) {
        printf("循环队列为空，无法出队！\n");
        return 0;
    }
    *value = queue->data[queue->front];
    queue->front = (queue->front + 1) % MAX_SIZE;  // 循环
    queue->size--;
    return 1;
}

// 打印循环队列
void printCircularQueue(CircularQueue *queue) {
    if (isCircularQueueEmpty(queue)) {
        printf("循环队列为空\n");
        return;
    }
    printf("循环队列内容（队头->队尾）: [");
    int count = 0;
    int index = queue->front;
    while (count < queue->size) {
        printf("%d", queue->data[index]);
        if (count < queue->size - 1) printf(", ");
        index = (index + 1) % MAX_SIZE;
        count++;
    }
    printf("]\n");
}

// ==================== 链表实现的队列 ====================

// 队列节点
typedef struct QueueNode {
    int data;
    struct QueueNode *next;
} QueueNode;

// 链表队列结构
typedef struct {
    QueueNode *front;        // 队头指针
    QueueNode *rear;         // 队尾指针
    int size;                // 队列大小
} LinkedQueue;

// 创建链表队列
LinkedQueue* createLinkedQueue() {
    LinkedQueue *queue = (LinkedQueue*)malloc(sizeof(LinkedQueue));
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    return queue;
}

// 判断链表队列是否为空
int isLinkedQueueEmpty(LinkedQueue *queue) {
    return queue->front == NULL;
}

// 链表队列入队
void linkedEnqueue(LinkedQueue *queue, int value) {
    QueueNode *newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->data = value;
    newNode->next = NULL;
    
    if (isLinkedQueueEmpty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    queue->size++;
}

// 链表队列出队
int linkedDequeue(LinkedQueue *queue, int *value) {
    if (isLinkedQueueEmpty(queue)) {
        printf("链表队列为空，无法出队！\n");
        return 0;
    }
    
    QueueNode *temp = queue->front;
    *value = temp->data;
    queue->front = queue->front->next;
    
    if (queue->front == NULL) {
        queue->rear = NULL;  // 队列变为空
    }
    
    free(temp);
    queue->size--;
    return 1;
}

// 打印链表队列
void printLinkedQueue(LinkedQueue *queue) {
    if (isLinkedQueueEmpty(queue)) {
        printf("链表队列为空\n");
        return;
    }
    printf("链表队列内容（队头->队尾）: [");
    QueueNode *current = queue->front;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) printf(", ");
        current = current->next;
    }
    printf("]\n");
}

// 释放链表队列
void freeLinkedQueue(LinkedQueue *queue) {
    while (!isLinkedQueueEmpty(queue)) {
        int temp;
        linkedDequeue(queue, &temp);
    }
    free(queue);
}

// ==================== 栈的应用示例 ====================

// 应用1：检查括号匹配
int checkParentheses(const char *expression) {
    ArrayStack *stack = createArrayStack();
    int len = strlen(expression);
    int isValid = 1;
    
    for (int i = 0; i < len; i++) {
        char ch = expression[i];
        
        if (ch == '(' || ch == '[' || ch == '{') {
            // 左括号入栈
            push(stack, ch);
        } else if (ch == ')' || ch == ']' || ch == '}') {
            // 右括号，检查匹配
            if (isStackEmpty(stack)) {
                isValid = 0;
                break;
            }
            
            int top;
            pop(stack, &top);
            
            if ((ch == ')' && top != '(') ||
                (ch == ']' && top != '[') ||
                (ch == '}' && top != '{')) {
                isValid = 0;
                break;
            }
        }
    }
    
    if (!isStackEmpty(stack)) {
        isValid = 0;  // 还有未匹配的左括号
    }
    
    free(stack);
    return isValid;
}

// 应用2：十进制转换为其他进制
void convertBase(int number, int base) {
    ArrayStack *stack = createArrayStack();
    
    if (number == 0) {
        printf("0");
        free(stack);
        return;
    }
    
    // 转换过程
    while (number > 0) {
        push(stack, number % base);
        number /= base;
    }
    
    // 输出结果
    while (!isStackEmpty(stack)) {
        int digit;
        pop(stack, &digit);
        if (digit < 10) {
            printf("%d", digit);
        } else {
            printf("%c", 'A' + digit - 10);  // 16进制用A-F表示10-15
        }
    }
    
    free(stack);
}

// 应用3：逆波兰表达式计算（后缀表达式）
int evaluatePostfix(const char *expression) {
    LinkedStack *stack = createLinkedStack();
    int len = strlen(expression);
    
    for (int i = 0; i < len; i++) {
        char ch = expression[i];
        
        if (ch == ' ') continue;  // 跳过空格
        
        if (ch >= '0' && ch <= '9') {
            // 数字入栈
            linkedStackPush(stack, ch - '0');
        } else {
            // 操作符，弹出两个操作数
            int operand2, operand1;
            linkedStackPop(stack, &operand2);
            linkedStackPop(stack, &operand1);
            
            int result;
            switch (ch) {
                case '+': result = operand1 + operand2; break;
                case '-': result = operand1 - operand2; break;
                case '*': result = operand1 * operand2; break;
                case '/': result = operand1 / operand2; break;
            }
            
            linkedStackPush(stack, result);
        }
    }
    
    int finalResult;
    linkedStackPop(stack, &finalResult);
    freeLinkedStack(stack);
    
    return finalResult;
}

// ==================== 队列的应用示例 ====================

// 应用：模拟银行排队系统
void simulateBankQueue() {
    LinkedQueue *queue = createLinkedQueue();
    int customerNum = 1;
    
    printf("\n模拟银行排队系统：\n");
    
    // 顾客1-5依次到达
    for (int i = 1; i <= 5; i++) {
        linkedEnqueue(queue, i);
        printf("顾客%d进入队列\n", i);
    }
    
    printLinkedQueue(queue);
    
    // 服务前3个顾客
    printf("\n开始服务：\n");
    for (int i = 0; i < 3; i++) {
        int customer;
        if (linkedDequeue(queue, &customer)) {
            printf("正在服务顾客%d\n", customer);
        }
    }
    
    printLinkedQueue(queue);
    
    // 新顾客加入
    printf("\n顾客6、7加入队列\n");
    linkedEnqueue(queue, 6);
    linkedEnqueue(queue, 7);
    
    printLinkedQueue(queue);
    
    freeLinkedQueue(queue);
}

// ==================== 主函数 ====================

int main() {
    printf("=== 栈和队列数据结构 ===\n\n");
    
    // 1. 数组栈演示
    printf("1. 数组栈操作:\n");
    ArrayStack *arrayStack = createArrayStack();
    
    printf("入栈: 10, 20, 30, 40, 50\n");
    for (int i = 1; i <= 5; i++) {
        push(arrayStack, i * 10);
    }
    printStack(arrayStack);
    printf("栈大小: %d\n", getStackSize(arrayStack));
    
    int value;
    printf("\n出栈两次:\n");
    for (int i = 0; i < 2; i++) {
        if (pop(arrayStack, &value)) {
            printf("出栈元素: %d\n", value);
        }
    }
    printStack(arrayStack);
    
    if (peek(arrayStack, &value)) {
        printf("栈顶元素: %d\n", value);
    }
    
    // 2. 链表栈演示
    printf("\n\n2. 链表栈操作:\n");
    LinkedStack *linkedStack = createLinkedStack();
    
    printf("入栈: 5, 4, 3, 2, 1\n");
    for (int i = 5; i >= 1; i--) {
        linkedStackPush(linkedStack, i);
    }
    printLinkedStack(linkedStack);
    printf("栈大小: %d\n", linkedStack->size);
    
    // 3. 数组队列演示
    printf("\n\n3. 数组队列操作:\n");
    ArrayQueue *arrayQueue = createArrayQueue();
    
    printf("入队: 1, 2, 3, 4, 5\n");
    for (int i = 1; i <= 5; i++) {
        enqueue(arrayQueue, i);
    }
    printQueue(arrayQueue);
    
    printf("\n出队两次:\n");
    for (int i = 0; i < 2; i++) {
        if (dequeue(arrayQueue, &value)) {
            printf("出队元素: %d\n", value);
        }
    }
    printQueue(arrayQueue);
    
    // 4. 循环队列演示
    printf("\n\n4. 循环队列操作:\n");
    CircularQueue *circularQueue = createCircularQueue();
    
    printf("入队: 10, 20, 30, 40, 50\n");
    for (int i = 1; i <= 5; i++) {
        circularEnqueue(circularQueue, i * 10);
    }
    printCircularQueue(circularQueue);
    printf("队列大小: %d\n", circularQueue->size);
    
    printf("\n出队三次:\n");
    for (int i = 0; i < 3; i++) {
        if (circularDequeue(circularQueue, &value)) {
            printf("出队元素: %d\n", value);
        }
    }
    printCircularQueue(circularQueue);
    
    printf("\n继续入队: 60, 70, 80\n");
    for (int i = 6; i <= 8; i++) {
        circularEnqueue(circularQueue, i * 10);
    }
    printCircularQueue(circularQueue);
    
    // 5. 链表队列演示
    printf("\n\n5. 链表队列操作:\n");
    LinkedQueue *linkedQueue = createLinkedQueue();
    
    printf("入队: 100, 200, 300, 400\n");
    for (int i = 1; i <= 4; i++) {
        linkedEnqueue(linkedQueue, i * 100);
    }
    printLinkedQueue(linkedQueue);
    
    // 6. 栈的应用：括号匹配
    printf("\n\n6. 栈的应用 - 括号匹配:\n");
    const char *expr1 = "((a+b)*c)";
    const char *expr2 = "{[a+(b-c)]*d}";
    const char *expr3 = "((a+b)";
    
    printf("表达式: %s -> %s\n", expr1, 
           checkParentheses(expr1) ? "括号匹配" : "括号不匹配");
    printf("表达式: %s -> %s\n", expr2, 
           checkParentheses(expr2) ? "括号匹配" : "括号不匹配");
    printf("表达式: %s -> %s\n", expr3, 
           checkParentheses(expr3) ? "括号匹配" : "括号不匹配");
    
    // 7. 栈的应用：进制转换
    printf("\n\n7. 栈的应用 - 进制转换:\n");
    printf("十进制 255 转二进制: ");
    convertBase(255, 2);
    printf("\n");
    
    printf("十进制 255 转八进制: ");
    convertBase(255, 8);
    printf("\n");
    
    printf("十进制 255 转十六进制: ");
    convertBase(255, 16);
    printf("\n");
    
    // 8. 栈的应用：后缀表达式计算
    printf("\n\n8. 栈的应用 - 后缀表达式计算:\n");
    const char *postfix = "53+82-*";  // 对应中缀: (5+3)*(8-2) = 48
    printf("后缀表达式: %s\n", postfix);
    printf("计算结果: %d\n", evaluatePostfix(postfix));
    
    // 9. 队列的应用：银行排队
    printf("\n\n9. 队列的应用 - 银行排队系统:\n");
    simulateBankQueue();
    
    // 释放内存
    free(arrayStack);
    freeLinkedStack(linkedStack);
    free(arrayQueue);
    free(circularQueue);
    freeLinkedQueue(linkedQueue);
    
    printf("\n\n=== 程序结束 ===\n");
    
    return 0;
}
