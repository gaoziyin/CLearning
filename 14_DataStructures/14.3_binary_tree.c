/*
 * 第十四章：数据结构
 * 14.3 二叉树实现
 * 
 * 学习目标：
 * 1. 理解二叉树的基本概念
 * 2. 掌握二叉树的三种遍历方法（前序、中序、后序）
 * 3. 学习二叉搜索树（BST）的实现
 * 4. 掌握二叉树的插入、删除、查找操作
 * 5. 了解二叉树的层次遍历
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==================== 二叉树基本结构 ====================

// 二叉树节点定义
typedef struct TreeNode {
    int data;                    // 数据域
    struct TreeNode *left;       // 左子树指针
    struct TreeNode *right;      // 右子树指针
} TreeNode;

// ==================== 二叉树基本操作 ====================

// 创建新节点
TreeNode* createNode(int data) {
    TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 前序遍历（根-左-右）
void preorderTraversal(TreeNode *root) {
    if (root == NULL) return;
    
    printf("%d ", root->data);           // 访问根节点
    preorderTraversal(root->left);       // 遍历左子树
    preorderTraversal(root->right);      // 遍历右子树
}

// 中序遍历（左-根-右）
void inorderTraversal(TreeNode *root) {
    if (root == NULL) return;
    
    inorderTraversal(root->left);        // 遍历左子树
    printf("%d ", root->data);           // 访问根节点
    inorderTraversal(root->right);       // 遍历右子树
}

// 后序遍历（左-右-根）
void postorderTraversal(TreeNode *root) {
    if (root == NULL) return;
    
    postorderTraversal(root->left);      // 遍历左子树
    postorderTraversal(root->right);     // 遍历右子树
    printf("%d ", root->data);           // 访问根节点
}

// 计算二叉树的高度
int getHeight(TreeNode *root) {
    if (root == NULL) return 0;
    
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// 计算二叉树的节点数
int getNodeCount(TreeNode *root) {
    if (root == NULL) return 0;
    
    return 1 + getNodeCount(root->left) + getNodeCount(root->right);
}

// 计算二叉树的叶子节点数
int getLeafCount(TreeNode *root) {
    if (root == NULL) return 0;
    
    // 如果是叶子节点
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    
    return getLeafCount(root->left) + getLeafCount(root->right);
}

// ==================== 层次遍历（使用队列） ====================

// 简单队列节点
typedef struct QueueNode {
    TreeNode *treeNode;
    struct QueueNode *next;
} QueueNode;

// 简单队列
typedef struct {
    QueueNode *front;
    QueueNode *rear;
} Queue;

// 创建队列
Queue* createQueue() {
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// 判断队列是否为空
int isQueueEmpty(Queue *queue) {
    return queue->front == NULL;
}

// 入队
void enqueue(Queue *queue, TreeNode *node) {
    QueueNode *newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->treeNode = node;
    newNode->next = NULL;
    
    if (queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// 出队
TreeNode* dequeue(Queue *queue) {
    if (isQueueEmpty(queue)) return NULL;
    
    QueueNode *temp = queue->front;
    TreeNode *treeNode = temp->treeNode;
    queue->front = queue->front->next;
    
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    
    free(temp);
    return treeNode;
}

// 层次遍历（广度优先遍历）
void levelOrderTraversal(TreeNode *root) {
    if (root == NULL) return;
    
    Queue *queue = createQueue();
    enqueue(queue, root);
    
    while (!isQueueEmpty(queue)) {
        TreeNode *current = dequeue(queue);
        printf("%d ", current->data);
        
        if (current->left != NULL) {
            enqueue(queue, current->left);
        }
        if (current->right != NULL) {
            enqueue(queue, current->right);
        }
    }
    
    free(queue);
}

// ==================== 二叉搜索树（BST） ====================

// 向BST中插入节点
TreeNode* bstInsert(TreeNode *root, int data) {
    // 如果树为空，创建新节点作为根节点
    if (root == NULL) {
        return createNode(data);
    }
    
    // 递归插入
    if (data < root->data) {
        root->left = bstInsert(root->left, data);
    } else if (data > root->data) {
        root->right = bstInsert(root->right, data);
    }
    // 如果data等于root->data，不插入重复值
    
    return root;
}

// 在BST中查找节点
TreeNode* bstSearch(TreeNode *root, int data) {
    // 树为空或找到节点
    if (root == NULL || root->data == data) {
        return root;
    }
    
    // 在左子树中查找
    if (data < root->data) {
        return bstSearch(root->left, data);
    }
    
    // 在右子树中查找
    return bstSearch(root->right, data);
}

// 找到BST中的最小节点
TreeNode* findMin(TreeNode *root) {
    if (root == NULL) return NULL;
    
    while (root->left != NULL) {
        root = root->left;
    }
    
    return root;
}

// 找到BST中的最大节点
TreeNode* findMax(TreeNode *root) {
    if (root == NULL) return NULL;
    
    while (root->right != NULL) {
        root = root->right;
    }
    
    return root;
}

// 从BST中删除节点
TreeNode* bstDelete(TreeNode *root, int data) {
    if (root == NULL) return NULL;
    
    // 查找要删除的节点
    if (data < root->data) {
        root->left = bstDelete(root->left, data);
    } else if (data > root->data) {
        root->right = bstDelete(root->right, data);
    } else {
        // 找到要删除的节点
        
        // 情况1：节点是叶子节点
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        
        // 情况2：节点只有一个子节点
        if (root->left == NULL) {
            TreeNode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode *temp = root->left;
            free(root);
            return temp;
        }
        
        // 情况3：节点有两个子节点
        // 找到右子树中的最小节点（后继节点）
        TreeNode *temp = findMin(root->right);
        root->data = temp->data;  // 用后继节点的值替换当前节点的值
        root->right = bstDelete(root->right, temp->data);  // 删除后继节点
    }
    
    return root;
}

// 验证是否为BST
int isBST(TreeNode *root, int min, int max) {
    if (root == NULL) return 1;
    
    // 检查当前节点的值是否在有效范围内
    if (root->data <= min || root->data >= max) {
        return 0;
    }
    
    // 递归检查左右子树
    return isBST(root->left, min, root->data) && 
           isBST(root->right, root->data, max);
}

// ==================== 树的可视化打印 ====================

// 打印树结构（简单版本）
void printTree(TreeNode *root, int space) {
    if (root == NULL) return;
    
    space += 5;
    
    // 先打印右子树
    printTree(root->right, space);
    
    // 打印当前节点
    printf("\n");
    for (int i = 5; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->data);
    
    // 打印左子树
    printTree(root->left, space);
}

// 以括号形式打印树
void printTreeBrackets(TreeNode *root) {
    if (root == NULL) {
        printf("()");
        return;
    }
    
    printf("(%d", root->data);
    if (root->left != NULL || root->right != NULL) {
        printf(" ");
        printTreeBrackets(root->left);
        printf(" ");
        printTreeBrackets(root->right);
    }
    printf(")");
}

// ==================== 树的高级操作 ====================

// 查找两个节点的最近公共祖先（LCA）
TreeNode* findLCA(TreeNode *root, int n1, int n2) {
    if (root == NULL) return NULL;
    
    // 如果当前节点等于n1或n2，返回当前节点
    if (root->data == n1 || root->data == n2) {
        return root;
    }
    
    // 在左右子树中查找
    TreeNode *leftLCA = findLCA(root->left, n1, n2);
    TreeNode *rightLCA = findLCA(root->right, n1, n2);
    
    // 如果两个节点分别在左右子树中，当前节点就是LCA
    if (leftLCA != NULL && rightLCA != NULL) {
        return root;
    }
    
    // 否则返回非空的那个子树的结果
    return (leftLCA != NULL) ? leftLCA : rightLCA;
}

// 计算从根到叶子的所有路径和
void printRootToLeafPaths(TreeNode *root, int path[], int pathLen) {
    if (root == NULL) return;
    
    // 将当前节点加入路径
    path[pathLen] = root->data;
    pathLen++;
    
    // 如果是叶子节点，打印路径
    if (root->left == NULL && root->right == NULL) {
        printf("路径: ");
        for (int i = 0; i < pathLen; i++) {
            printf("%d", path[i]);
            if (i < pathLen - 1) printf(" -> ");
        }
        printf("\n");
    } else {
        // 递归遍历左右子树
        printRootToLeafPaths(root->left, path, pathLen);
        printRootToLeafPaths(root->right, path, pathLen);
    }
}

// 镜像翻转二叉树
TreeNode* mirrorTree(TreeNode *root) {
    if (root == NULL) return NULL;
    
    // 交换左右子树
    TreeNode *temp = root->left;
    root->left = root->right;
    root->right = temp;
    
    // 递归翻转左右子树
    mirrorTree(root->left);
    mirrorTree(root->right);
    
    return root;
}

// 判断两棵树是否相同
int isSameTree(TreeNode *root1, TreeNode *root2) {
    if (root1 == NULL && root2 == NULL) return 1;
    if (root1 == NULL || root2 == NULL) return 0;
    
    return (root1->data == root2->data) &&
           isSameTree(root1->left, root2->left) &&
           isSameTree(root1->right, root2->right);
}

// 释放二叉树
void freeTree(TreeNode *root) {
    if (root == NULL) return;
    
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// ==================== 主函数 ====================

int main() {
    printf("=== 二叉树数据结构 ===\n\n");
    
    // 1. 手动创建一个二叉树
    printf("1. 创建二叉树:\n");
    printf("         1\n");
    printf("       /   \\\n");
    printf("      2     3\n");
    printf("     / \\   /\n");
    printf("    4   5 6\n\n");
    
    TreeNode *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    
    // 2. 遍历二叉树
    printf("2. 遍历二叉树:\n");
    printf("前序遍历: ");
    preorderTraversal(root);
    printf("\n");
    
    printf("中序遍历: ");
    inorderTraversal(root);
    printf("\n");
    
    printf("后序遍历: ");
    postorderTraversal(root);
    printf("\n");
    
    printf("层次遍历: ");
    levelOrderTraversal(root);
    printf("\n");
    
    // 3. 二叉树统计信息
    printf("\n3. 二叉树统计:\n");
    printf("树的高度: %d\n", getHeight(root));
    printf("节点总数: %d\n", getNodeCount(root));
    printf("叶子节点数: %d\n", getLeafCount(root));
    
    // 4. 打印树结构
    printf("\n4. 树的结构表示:\n");
    printf("括号表示法: ");
    printTreeBrackets(root);
    printf("\n");
    
    // 5. 从根到叶子的路径
    printf("\n5. 从根到叶子的所有路径:\n");
    int path[100];
    printRootToLeafPaths(root, path, 0);
    
    // 6. 二叉搜索树（BST）演示
    printf("\n6. 二叉搜索树操作:\n");
    TreeNode *bst = NULL;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(values) / sizeof(values[0]);
    
    printf("插入元素: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", values[i]);
        bst = bstInsert(bst, values[i]);
    }
    printf("\n");
    
    printf("\nBST结构:\n");
    printf("         50\n");
    printf("       /    \\\n");
    printf("      30     70\n");
    printf("     / \\    / \\\n");
    printf("    20  40 60  80\n\n");
    
    printf("中序遍历BST（应该是有序的）: ");
    inorderTraversal(bst);
    printf("\n");
    
    // 7. BST查找
    printf("\n7. BST查找操作:\n");
    int searchValue = 40;
    TreeNode *found = bstSearch(bst, searchValue);
    if (found) {
        printf("找到节点: %d\n", found->data);
    } else {
        printf("未找到节点: %d\n", searchValue);
    }
    
    TreeNode *minNode = findMin(bst);
    TreeNode *maxNode = findMax(bst);
    printf("最小值: %d\n", minNode->data);
    printf("最大值: %d\n", maxNode->data);
    
    // 8. BST删除操作
    printf("\n8. BST删除操作:\n");
    printf("删除节点 30\n");
    bst = bstDelete(bst, 30);
    printf("删除后中序遍历: ");
    inorderTraversal(bst);
    printf("\n");
    
    // 9. 验证BST
    printf("\n9. 验证是否为BST:\n");
    printf("是否为BST: %s\n", isBST(bst, -2147483648, 2147483647) ? "是" : "否");
    
    // 10. 最近公共祖先
    printf("\n10. 查找最近公共祖先:\n");
    TreeNode *lca = findLCA(bst, 20, 40);
    if (lca) {
        printf("节点20和40的最近公共祖先: %d\n", lca->data);
    }
    
    // 11. 镜像翻转
    printf("\n11. 镜像翻转二叉树:\n");
    printf("翻转前中序遍历: ");
    inorderTraversal(root);
    printf("\n");
    
    mirrorTree(root);
    printf("翻转后中序遍历: ");
    inorderTraversal(root);
    printf("\n");
    
    // 12. 比较两棵树
    printf("\n12. 判断两棵树是否相同:\n");
    TreeNode *root2 = createNode(1);
    root2->left = createNode(3);  // 不同的值
    root2->right = createNode(2);
    
    printf("树1和树2是否相同: %s\n", isSameTree(root, root2) ? "相同" : "不同");
    
    // 释放内存
    freeTree(root);
    freeTree(bst);
    freeTree(root2);
    
    printf("\n=== 程序结束 ===\n");
    
    return 0;
}
