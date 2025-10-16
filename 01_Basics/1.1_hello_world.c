/*
 * 第一章：基础语法
 * 1.1 Hello World - 第一个C程序
 * 
 * 学习目标：
 * 1. 理解C程序的基本结构
 * 2. 学会使用printf函数输出信息
 * 3. 了解main函数的作用
 */

#include <stdio.h>  // 包含标准输入输出头文件

/*
 * main函数：程序的入口点
 * 每个C程序都必须有一个main函数
 * 返回值类型为int，表示程序的退出状态
 */
int main() {
    // printf函数用于在控制台输出文本
    // \n 表示换行符
    printf("Hello, World!\n");
    printf("欢迎学习C语言！\n");
    printf("这是你的第一个C程序\n");
    
    // 返回0表示程序正常结束
    return 0;
}

/*
 * 知识点总结：
 * 1. #include <stdio.h> - 包含标准输入输出库
 * 2. int main() - 程序入口函数
 * 3. printf() - 输出函数
 * 4. return 0 - 程序正常退出
 * 5. // 和 /* */ - 单行和多行注释
 * 
 * 编译命令：
 * gcc 1.1_hello_world.c -o hello_world.exe
 * 
 * 运行：
 * ./hello_world.exe
 */
