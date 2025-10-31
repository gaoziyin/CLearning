/*
 * 第十四章：数据结构
 * 14.5 图实现
 * 
 * 学习目标：
 * 1. 理解图的基本概念（顶点、边、有向图、无向图）
 * 2. 掌握图的两种存储方式（邻接矩阵、邻接表）
 * 3. 学习深度优先搜索（DFS）算法
 * 4. 学习广度优先搜索（BFS）算法
 * 5. 了解图的常见应用（最短路径、拓扑排序等）
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_VERTICES 10
#define INF INT_MAX

// ==================== 邻接矩阵实现图 ====================

// 邻接矩阵图结构
typedef struct {
    int vertices;                    // 顶点数
    int edges;                       // 边数
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];  // 邻接矩阵
} MatrixGraph;

// 创建邻接矩阵图
MatrixGraph* createMatrixGraph(int vertices) {
    MatrixGraph *graph = (MatrixGraph*)malloc(sizeof(MatrixGraph));
    graph->vertices = vertices;
    graph->edges = 0;
    
    // 初始化邻接矩阵
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }
    
    return graph;
}

// 添加边（无向图）
void addEdgeMatrix(MatrixGraph *graph, int src, int dest) {
    if (src >= 0 && src < graph->vertices && 
        dest >= 0 && dest < graph->vertices) {
        graph->adjMatrix[src][dest] = 1;
        graph->adjMatrix[dest][src] = 1;  // 无向图
        graph->edges++;
    }
}

// 添加有向边
void addDirectedEdgeMatrix(MatrixGraph *graph, int src, int dest) {
    if (src >= 0 && src < graph->vertices && 
        dest >= 0 && dest < graph->vertices) {
        graph->adjMatrix[src][dest] = 1;
        graph->edges++;
    }
}

// 添加带权重的边
void addWeightedEdgeMatrix(MatrixGraph *graph, int src, int dest, int weight) {
    if (src >= 0 && src < graph->vertices && 
        dest >= 0 && dest < graph->vertices) {
        graph->adjMatrix[src][dest] = weight;
        graph->adjMatrix[dest][src] = weight;  // 无向图
    }
}

// 打印邻接矩阵
void printMatrixGraph(MatrixGraph *graph) {
    printf("邻接矩阵表示（顶点数: %d, 边数: %d）:\n", graph->vertices, graph->edges);
    printf("   ");
    for (int i = 0; i < graph->vertices; i++) {
        printf("%d ", i);
    }
    printf("\n");
    
    for (int i = 0; i < graph->vertices; i++) {
        printf("%d: ", i);
        for (int j = 0; j < graph->vertices; j++) {
            printf("%d ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

// ==================== 邻接表实现图 ====================

// 邻接表节点
typedef struct AdjListNode {
    int vertex;                      // 顶点
    int weight;                      // 权重
    struct AdjListNode *next;        // 下一个节点
} AdjListNode;

// 邻接表
typedef struct {
    AdjListNode *head;               // 链表头
} AdjList;

// 邻接表图结构
typedef struct {
    int vertices;                    // 顶点数
    int edges;                       // 边数
    AdjList *array;                  // 邻接表数组
} ListGraph;

// 创建邻接表节点
AdjListNode* createAdjListNode(int vertex, int weight) {
    AdjListNode *newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// 创建邻接表图
ListGraph* createListGraph(int vertices) {
    ListGraph *graph = (ListGraph*)malloc(sizeof(ListGraph));
    graph->vertices = vertices;
    graph->edges = 0;
    
    graph->array = (AdjList*)malloc(vertices * sizeof(AdjList));
    
    // 初始化每个邻接表为空
    for (int i = 0; i < vertices; i++) {
        graph->array[i].head = NULL;
    }
    
    return graph;
}

// 添加边（无向图）
void addEdgeList(ListGraph *graph, int src, int dest, int weight) {
    // 从src到dest
    AdjListNode *newNode = createAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    
    // 从dest到src（无向图）
    newNode = createAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
    
    graph->edges++;
}

// 添加有向边
void addDirectedEdgeList(ListGraph *graph, int src, int dest, int weight) {
    AdjListNode *newNode = createAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    graph->edges++;
}

// 打印邻接表
void printListGraph(ListGraph *graph) {
    printf("邻接表表示（顶点数: %d, 边数: %d）:\n", graph->vertices, graph->edges);
    
    for (int i = 0; i < graph->vertices; i++) {
        printf("顶点 %d: ", i);
        AdjListNode *temp = graph->array[i].head;
        
        while (temp) {
            printf("-> %d(权重:%d) ", temp->vertex, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}

// ==================== 深度优先搜索（DFS） ====================

// DFS递归辅助函数
void dfsUtil(MatrixGraph *graph, int vertex, int visited[]) {
    // 标记当前节点为已访问
    visited[vertex] = 1;
    printf("%d ", vertex);
    
    // 遍历所有相邻节点
    for (int i = 0; i < graph->vertices; i++) {
        if (graph->adjMatrix[vertex][i] && !visited[i]) {
            dfsUtil(graph, i, visited);
        }
    }
}

// 深度优先搜索（从指定顶点开始）
void dfs(MatrixGraph *graph, int startVertex) {
    int visited[MAX_VERTICES] = {0};
    
    printf("DFS遍历（从顶点%d开始）: ", startVertex);
    dfsUtil(graph, startVertex, visited);
    printf("\n");
}

// DFS遍历邻接表图
void dfsListUtil(ListGraph *graph, int vertex, int visited[]) {
    visited[vertex] = 1;
    printf("%d ", vertex);
    
    AdjListNode *temp = graph->array[vertex].head;
    while (temp) {
        if (!visited[temp->vertex]) {
            dfsListUtil(graph, temp->vertex, visited);
        }
        temp = temp->next;
    }
}

void dfsList(ListGraph *graph, int startVertex) {
    int visited[MAX_VERTICES] = {0};
    
    printf("DFS遍历（从顶点%d开始）: ", startVertex);
    dfsListUtil(graph, startVertex, visited);
    printf("\n");
}

// ==================== 广度优先搜索（BFS） ====================

// 简单队列实现
typedef struct {
    int data[MAX_VERTICES];
    int front;
    int rear;
} Queue;

Queue* createQueue() {
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

int isQueueEmpty(Queue *queue) {
    return queue->front == -1;
}

void enqueue(Queue *queue, int value) {
    if (queue->front == -1) {
        queue->front = 0;
    }
    queue->data[++queue->rear] = value;
}

int dequeue(Queue *queue) {
    int value = queue->data[queue->front];
    if (queue->front == queue->rear) {
        queue->front = queue->rear = -1;
    } else {
        queue->front++;
    }
    return value;
}

// 广度优先搜索（邻接矩阵）
void bfs(MatrixGraph *graph, int startVertex) {
    int visited[MAX_VERTICES] = {0};
    Queue *queue = createQueue();
    
    printf("BFS遍历（从顶点%d开始）: ", startVertex);
    
    visited[startVertex] = 1;
    enqueue(queue, startVertex);
    
    while (!isQueueEmpty(queue)) {
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);
        
        // 遍历所有相邻节点
        for (int i = 0; i < graph->vertices; i++) {
            if (graph->adjMatrix[currentVertex][i] && !visited[i]) {
                visited[i] = 1;
                enqueue(queue, i);
            }
        }
    }
    
    printf("\n");
    free(queue);
}

// BFS遍历邻接表图
void bfsList(ListGraph *graph, int startVertex) {
    int visited[MAX_VERTICES] = {0};
    Queue *queue = createQueue();
    
    printf("BFS遍历（从顶点%d开始）: ", startVertex);
    
    visited[startVertex] = 1;
    enqueue(queue, startVertex);
    
    while (!isQueueEmpty(queue)) {
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);
        
        AdjListNode *temp = graph->array[currentVertex].head;
        while (temp) {
            if (!visited[temp->vertex]) {
                visited[temp->vertex] = 1;
                enqueue(queue, temp->vertex);
            }
            temp = temp->next;
        }
    }
    
    printf("\n");
    free(queue);
}

// ==================== 图的算法 ====================

// 检测图中是否有环（使用DFS）
int hasCycleUtil(MatrixGraph *graph, int vertex, int visited[], int recStack[]) {
    visited[vertex] = 1;
    recStack[vertex] = 1;
    
    for (int i = 0; i < graph->vertices; i++) {
        if (graph->adjMatrix[vertex][i]) {
            if (!visited[i]) {
                if (hasCycleUtil(graph, i, visited, recStack)) {
                    return 1;
                }
            } else if (recStack[i]) {
                return 1;  // 发现环
            }
        }
    }
    
    recStack[vertex] = 0;
    return 0;
}

int hasCycle(MatrixGraph *graph) {
    int visited[MAX_VERTICES] = {0};
    int recStack[MAX_VERTICES] = {0};
    
    for (int i = 0; i < graph->vertices; i++) {
        if (!visited[i]) {
            if (hasCycleUtil(graph, i, visited, recStack)) {
                return 1;
            }
        }
    }
    
    return 0;
}

// 拓扑排序（使用DFS）
void topologicalSortUtil(MatrixGraph *graph, int vertex, int visited[], int stack[], int *stackIndex) {
    visited[vertex] = 1;
    
    for (int i = 0; i < graph->vertices; i++) {
        if (graph->adjMatrix[vertex][i] && !visited[i]) {
            topologicalSortUtil(graph, i, visited, stack, stackIndex);
        }
    }
    
    stack[(*stackIndex)++] = vertex;
}

void topologicalSort(MatrixGraph *graph) {
    int visited[MAX_VERTICES] = {0};
    int stack[MAX_VERTICES];
    int stackIndex = 0;
    
    printf("拓扑排序: ");
    
    for (int i = 0; i < graph->vertices; i++) {
        if (!visited[i]) {
            topologicalSortUtil(graph, i, visited, stack, &stackIndex);
        }
    }
    
    // 反向输出栈
    for (int i = stackIndex - 1; i >= 0; i--) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

// Dijkstra最短路径算法
void dijkstra(MatrixGraph *graph, int startVertex) {
    int dist[MAX_VERTICES];
    int visited[MAX_VERTICES] = {0};
    
    // 初始化距离数组
    for (int i = 0; i < graph->vertices; i++) {
        dist[i] = INF;
    }
    dist[startVertex] = 0;
    
    for (int count = 0; count < graph->vertices - 1; count++) {
        // 找到未访问节点中距离最小的
        int minDist = INF;
        int minIndex = -1;
        
        for (int i = 0; i < graph->vertices; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                minIndex = i;
            }
        }
        
        if (minIndex == -1) break;
        
        visited[minIndex] = 1;
        
        // 更新相邻节点的距离
        for (int i = 0; i < graph->vertices; i++) {
            if (!visited[i] && graph->adjMatrix[minIndex][i] && 
                dist[minIndex] != INF &&
                dist[minIndex] + graph->adjMatrix[minIndex][i] < dist[i]) {
                dist[i] = dist[minIndex] + graph->adjMatrix[minIndex][i];
            }
        }
    }
    
    // 打印最短路径
    printf("从顶点%d到其他顶点的最短路径:\n", startVertex);
    for (int i = 0; i < graph->vertices; i++) {
        printf("顶点%d: ", i);
        if (dist[i] == INF) {
            printf("不可达\n");
        } else {
            printf("%d\n", dist[i]);
        }
    }
}

// ==================== 释放图内存 ====================

void freeMatrixGraph(MatrixGraph *graph) {
    free(graph);
}

void freeListGraph(ListGraph *graph) {
    for (int i = 0; i < graph->vertices; i++) {
        AdjListNode *temp = graph->array[i].head;
        while (temp) {
            AdjListNode *toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(graph->array);
    free(graph);
}

// ==================== 主函数 ====================

int main() {
    printf("=== 图数据结构 ===\n\n");
    
    // 1. 邻接矩阵图演示
    printf("1. 邻接矩阵表示的无向图:\n");
    printf("图的结构:\n");
    printf("    0 --- 1\n");
    printf("    |     |\n");
    printf("    2 --- 3\n\n");
    
    MatrixGraph *matrixGraph = createMatrixGraph(4);
    addEdgeMatrix(matrixGraph, 0, 1);
    addEdgeMatrix(matrixGraph, 0, 2);
    addEdgeMatrix(matrixGraph, 1, 3);
    addEdgeMatrix(matrixGraph, 2, 3);
    
    printMatrixGraph(matrixGraph);
    
    // 2. 邻接表图演示
    printf("\n\n2. 邻接表表示的无向图:\n");
    ListGraph *listGraph = createListGraph(4);
    addEdgeList(listGraph, 0, 1, 1);
    addEdgeList(listGraph, 0, 2, 1);
    addEdgeList(listGraph, 1, 3, 1);
    addEdgeList(listGraph, 2, 3, 1);
    
    printListGraph(listGraph);
    
    // 3. DFS遍历
    printf("\n\n3. 深度优先搜索（DFS）:\n");
    dfs(matrixGraph, 0);
    dfsList(listGraph, 0);
    
    // 4. BFS遍历
    printf("\n\n4. 广度优先搜索（BFS）:\n");
    bfs(matrixGraph, 0);
    bfsList(listGraph, 0);
    
    // 5. 有向图和环检测
    printf("\n\n5. 有向图和环检测:\n");
    printf("有向图结构:\n");
    printf("    0 → 1 → 2\n");
    printf("    ↓       ↓\n");
    printf("    3 ← ← ← 4\n\n");
    
    MatrixGraph *directedGraph = createMatrixGraph(5);
    addDirectedEdgeMatrix(directedGraph, 0, 1);
    addDirectedEdgeMatrix(directedGraph, 1, 2);
    addDirectedEdgeMatrix(directedGraph, 2, 4);
    addDirectedEdgeMatrix(directedGraph, 4, 3);
    addDirectedEdgeMatrix(directedGraph, 0, 3);
    
    printMatrixGraph(directedGraph);
    printf("\n是否有环: %s\n", hasCycle(directedGraph) ? "是" : "否");
    
    // 6. 拓扑排序
    printf("\n\n6. 拓扑排序（DAG - 有向无环图）:\n");
    printf("DAG结构:\n");
    printf("    0 → 1 → 3\n");
    printf("    ↓   ↓   ↓\n");
    printf("    2 → → → 4\n\n");
    
    MatrixGraph *dag = createMatrixGraph(5);
    addDirectedEdgeMatrix(dag, 0, 1);
    addDirectedEdgeMatrix(dag, 0, 2);
    addDirectedEdgeMatrix(dag, 1, 3);
    addDirectedEdgeMatrix(dag, 1, 4);
    addDirectedEdgeMatrix(dag, 2, 4);
    addDirectedEdgeMatrix(dag, 3, 4);
    
    topologicalSort(dag);
    
    // 7. Dijkstra最短路径
    printf("\n\n7. Dijkstra最短路径算法:\n");
    printf("带权图结构:\n");
    printf("        1\n");
    printf("    0 ---- 1\n");
    printf("    |      |\n");
    printf("   4|      |3\n");
    printf("    |      |\n");
    printf("    2 ---- 3\n");
    printf("        2\n\n");
    
    MatrixGraph *weightedGraph = createMatrixGraph(4);
    addWeightedEdgeMatrix(weightedGraph, 0, 1, 1);
    addWeightedEdgeMatrix(weightedGraph, 0, 2, 4);
    addWeightedEdgeMatrix(weightedGraph, 1, 3, 3);
    addWeightedEdgeMatrix(weightedGraph, 2, 3, 2);
    
    dijkstra(weightedGraph, 0);
    
    // 8. 更复杂的图示例
    printf("\n\n8. 复杂图示例（社交网络）:\n");
    ListGraph *socialGraph = createListGraph(6);
    
    // 添加"朋友"关系
    addEdgeList(socialGraph, 0, 1, 1);  // 用户0和1是朋友
    addEdgeList(socialGraph, 0, 2, 1);
    addEdgeList(socialGraph, 1, 3, 1);
    addEdgeList(socialGraph, 2, 3, 1);
    addEdgeList(socialGraph, 3, 4, 1);
    addEdgeList(socialGraph, 4, 5, 1);
    
    printListGraph(socialGraph);
    
    printf("\n从用户0开始的朋友网络遍历:\n");
    bfsList(socialGraph, 0);
    
    // 释放内存
    freeMatrixGraph(matrixGraph);
    freeListGraph(listGraph);
    freeMatrixGraph(directedGraph);
    freeMatrixGraph(dag);
    freeMatrixGraph(weightedGraph);
    freeListGraph(socialGraph);
    
    printf("\n=== 程序结束 ===\n");
    
    return 0;
}
