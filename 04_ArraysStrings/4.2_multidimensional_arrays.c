/*
 * 第四章：数组与字符串
 * 4.2 多维数组
 * 
 * 学习目标：
 * 1. 理解二维数组的概念
 * 2. 掌握多维数组的声明和初始化
 * 3. 学会多维数组的遍历和应用
 */

#include <stdio.h>

int main() {
    printf("=== 多维数组详解 ===\n\n");
    
    // 1. 二维数组的声明和初始化
    printf("1. 二维数组的声明和初始化:\n");
    
    // 方式1：逐个赋值
    int matrix1[2][3];
    matrix1[0][0] = 1;
    matrix1[0][1] = 2;
    matrix1[0][2] = 3;
    matrix1[1][0] = 4;
    matrix1[1][1] = 5;
    matrix1[1][2] = 6;
    
    printf("matrix1 (2×3):\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", matrix1[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    // 方式2：完全初始化
    int matrix2[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    
    printf("matrix2 (2×3):\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", matrix2[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    // 方式3：一维形式初始化
    int matrix3[2][3] = {1, 2, 3, 4, 5, 6};
    
    printf("matrix3 (2×3):\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", matrix3[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    // 方式4：部分初始化
    int matrix4[2][3] = {{1, 2}, {4}};  // 其余为0
    
    printf("matrix4 (2×3):\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", matrix4[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    // 2. 访问二维数组元素
    printf("2. 访问二维数组元素:\n");
    int arr[3][4] = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9, 10, 11, 12}
    };
    
    printf("arr[0][0] = %d (第1行第1列)\n", arr[0][0]);
    printf("arr[1][2] = %d (第2行第3列)\n", arr[1][2]);
    printf("arr[2][3] = %d (第3行第4列)\n\n", arr[2][3]);
    
    // 3. 遍历二维数组
    printf("3. 遍历二维数组:\n");
    int rows = 3;
    int cols = 4;
    
    printf("完整数组:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%3d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    // 4. 计算每行的和
    printf("4. 计算每行的和:\n");
    for (int i = 0; i < rows; i++) {
        int row_sum = 0;
        for (int j = 0; j < cols; j++) {
            row_sum += arr[i][j];
        }
        printf("第 %d 行的和: %d\n", i + 1, row_sum);
    }
    printf("\n");
    
    // 5. 计算每列的和
    printf("5. 计算每列的和:\n");
    for (int j = 0; j < cols; j++) {
        int col_sum = 0;
        for (int i = 0; i < rows; i++) {
            col_sum += arr[i][j];
        }
        printf("第 %d 列的和: %d\n", j + 1, col_sum);
    }
    printf("\n");
    
    // 6. 矩阵转置
    printf("6. 矩阵转置:\n");
    int original[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    int transposed[3][2];
    
    printf("原矩阵 (2×3):\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", original[i][j]);
            transposed[j][i] = original[i][j];  // 转置
        }
        printf("\n");
    }
    
    printf("\n转置后 (3×2):\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", transposed[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    // 7. 矩阵加法
    printf("7. 矩阵加法:\n");
    int matA[2][2] = {{1, 2}, {3, 4}};
    int matB[2][2] = {{5, 6}, {7, 8}};
    int matC[2][2];
    
    printf("矩阵 A:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", matA[i][j]);
        }
        printf("\n");
    }
    
    printf("\n矩阵 B:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", matB[i][j]);
        }
        printf("\n");
    }
    
    // 相加
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            matC[i][j] = matA[i][j] + matB[i][j];
        }
    }
    
    printf("\nA + B:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", matC[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    // 8. 矩阵乘法
    printf("8. 矩阵乘法:\n");
    int mat1[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int mat2[3][2] = {{7, 8}, {9, 10}, {11, 12}};
    int result[2][2] = {0};
    
    printf("矩阵1 (2×3):\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", mat1[i][j]);
        }
        printf("\n");
    }
    
    printf("\n矩阵2 (3×2):\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", mat2[i][j]);
        }
        printf("\n");
    }
    
    // 矩阵乘法
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 3; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    
    printf("\n矩阵1 × 矩阵2 (2×2):\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    // 9. 查找二维数组中的最大值
    printf("9. 查找最大值和位置:\n");
    int data[3][4] = {
        {12, 45, 23, 67},
        {89, 34, 56, 78},
        {23, 91, 45, 62}
    };
    
    int max_val = data[0][0];
    int max_row = 0, max_col = 0;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            if (data[i][j] > max_val) {
                max_val = data[i][j];
                max_row = i;
                max_col = j;
            }
        }
    }
    
    printf("数组:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%3d ", data[i][j]);
        }
        printf("\n");
    }
    printf("\n最大值: %d\n", max_val);
    printf("位置: [%d][%d]\n\n", max_row, max_col);
    
    // 10. 三维数组
    printf("10. 三维数组:\n");
    int cube[2][3][4] = {
        {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12}
        },
        {
            {13, 14, 15, 16},
            {17, 18, 19, 20},
            {21, 22, 23, 24}
        }
    };
    
    printf("三维数组 (2×3×4):\n");
    for (int i = 0; i < 2; i++) {
        printf("层 %d:\n", i);
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 4; k++) {
                printf("%3d ", cube[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
    
    // 11. 实际应用：学生成绩表
    printf("11. 实际应用 - 学生成绩表:\n");
    // 3个学生，4门课程
    int scores[3][4] = {
        {85, 90, 78, 92},  // 学生1
        {88, 76, 95, 84},  // 学生2
        {92, 85, 88, 90}   // 学生3
    };
    
    char* subjects[] = {"语文", "数学", "英语", "科学"};
    
    printf("成绩表:\n");
    printf("学生\\科目  ");
    for (int j = 0; j < 4; j++) {
        printf("%-6s ", subjects[j]);
    }
    printf("平均分\n");
    
    for (int i = 0; i < 3; i++) {
        printf("学生%d     ", i + 1);
        int total = 0;
        for (int j = 0; j < 4; j++) {
            printf("%-6d ", scores[i][j]);
            total += scores[i][j];
        }
        printf("%.2f\n", (float)total / 4);
    }
    
    // 计算每门课程的平均分
    printf("\n科目平均:  ");
    for (int j = 0; j < 4; j++) {
        int total = 0;
        for (int i = 0; i < 3; i++) {
            total += scores[i][j];
        }
        printf("%-6.2f ", (float)total / 3);
    }
    printf("\n");
    
    return 0;
}

/*
 * 知识点总结：
 * 
 * 多维数组的概念：
 * - 数组的数组
 * - 二维数组：表格/矩阵
 * - 三维数组：立方体
 * - 更高维度：根据需要
 * 
 * 二维数组的声明：
 * 类型 数组名[行数][列数];
 * 
 * 例如：
 * int matrix[3][4];  // 3行4列的二维数组
 * 
 * 内存布局：
 * - 按行优先存储
 * - 行内元素连续
 * - 例如：arr[2][3]
 *   存储顺序：[0][0], [0][1], [0][2], [1][0], [1][1], [1][2]
 * 
 * 二维数组的初始化：
 * 
 * 1. 分行初始化（推荐）：
 *    int arr[2][3] = {
 *        {1, 2, 3},
 *        {4, 5, 6}
 *    };
 * 
 * 2. 一维形式：
 *    int arr[2][3] = {1, 2, 3, 4, 5, 6};
 * 
 * 3. 部分初始化：
 *    int arr[2][3] = {{1, 2}, {4}};
 * 
 * 4. 省略行数（不能省略列数）：
 *    int arr[][3] = {1, 2, 3, 4, 5, 6};  // 行数自动为2
 * 
 * 访问元素：
 * arr[i][j]
 * - i：行索引（0开始）
 * - j：列索引（0开始）
 * 
 * 遍历二维数组：
 * for (int i = 0; i < rows; i++) {
 *     for (int j = 0; j < cols; j++) {
 *         处理 arr[i][j];
 *     }
 * }
 * 
 * 三维数组：
 * 类型 数组名[深度][行][列];
 * 
 * 例如：
 * int cube[2][3][4];
 * 
 * 访问：cube[i][j][k]
 * - i：第几层
 * - j：第几行
 * - k：第几列
 * 
 * 常见应用：
 * 
 * 1. 矩阵运算：
 *    - 加法、减法
 *    - 乘法
 *    - 转置
 * 
 * 2. 表格数据：
 *    - 学生成绩
 *    - 销售数据
 *    - 统计表
 * 
 * 3. 图像处理：
 *    - 像素矩阵
 *    - RGB数组
 * 
 * 4. 游戏开发：
 *    - 地图
 *    - 棋盘
 *    - 网格
 * 
 * 矩阵操作：
 * 
 * 1. 矩阵加法：
 *    C[i][j] = A[i][j] + B[i][j]
 * 
 * 2. 矩阵乘法：
 *    C[i][j] = Σ(A[i][k] × B[k][j])
 *    要求：A的列数 = B的行数
 * 
 * 3. 矩阵转置：
 *    B[j][i] = A[i][j]
 * 
 * 计算数组大小：
 * - 总元素数：(行数 × 列数)
 * - 行数：sizeof(arr) / sizeof(arr[0])
 * - 列数：sizeof(arr[0]) / sizeof(arr[0][0])
 * 
 * 传递给函数：
 * 
 * 1. 必须指定列数：
 *    void func(int arr[][COLS], int rows)
 * 
 * 2. 或使用指针：
 *    void func(int (*arr)[COLS], int rows)
 * 
 * 注意事项：
 * 1. 声明时必须指定所有维度（第一维可选）
 * 2. 初始化时最好分行写，提高可读性
 * 3. 访问时注意行列索引不要越界
 * 4. 传递给函数时列数必须指定
 * 5. 多维数组占用内存较大
 * 
 * 常见错误：
 * 1. 省略列数：
 *    int arr[][];  // 错误！
 * 
 * 2. 索引越界：
 *    int arr[2][3];
 *    arr[2][0] = 1;  // 错误！行索引最大为1
 * 
 * 3. 行列混淆：
 *    arr[行][列]，不是arr[列][行]
 * 
 * 4. 初始化不当：
 *    元素个数超过数组大小
 * 
 * 最佳实践：
 * - 使用宏定义行数和列数
 * - 初始化时分行写，提高可读性
 * - 遍历时使用常量表示边界
 * - 给数组元素添加有意义的注释
 * - 处理前检查数组边界
 * - 复杂运算封装成函数
 * - 大数组考虑使用动态分配
 * 
 * 性能考虑：
 * - 按行遍历比按列遍历快（缓存友好）
 * - 避免不必要的多维数组
 * - 大数组考虑一维展开
 */
