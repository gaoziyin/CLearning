/*
 * 第三章：函数
 * 3.5 变量作用域与生命周期
 * 
 * 学习目标：
 * 1. 理解局部变量和全局变量
 * 2. 掌握变量的作用域规则
 * 3. 了解变量的生命周期
 */

#include <stdio.h>

// 全局变量定义
int global_var = 100;  // 全局变量，整个程序可见
int counter = 0;       // 全局计数器

// 函数声明
void demonstrateLocal(void);
void modifyGlobal(void);
void demonstrateStatic(void);
void blockScope(void);
int incrementCounter(void);
void shadowingExample(void);

int main() {
    printf("=== 变量作用域与生命周期 ===\n\n");
    
    // 1. 全局变量
    printf("1. 全局变量:\n");
    printf("全局变量 global_var = %d\n", global_var);
    printf("在main函数中可以直接访问\n");
    modifyGlobal();
    printf("函数修改后 global_var = %d\n\n", global_var);
    
    // 2. 局部变量
    printf("2. 局部变量:\n");
    int local_var = 50;  // 局部变量，只在main函数中可见
    printf("main函数的局部变量 local_var = %d\n", local_var);
    demonstrateLocal();
    printf("main函数的 local_var 仍然是 %d（不受其他函数影响）\n\n", local_var);
    
    // 3. 变量的作用域
    printf("3. 变量的作用域:\n");
    int x = 10;
    printf("外层作用域: x = %d\n", x);
    
    {  // 新的代码块
        int x = 20;  // 内层作用域的x，屏蔽外层的x
        printf("内层作用域: x = %d\n", x);
    }
    
    printf("返回外层作用域: x = %d\n\n", x);
    
    // 4. 静态局部变量
    printf("4. 静态局部变量（保持值）:\n");
    for (int i = 0; i < 5; i++) {
        demonstrateStatic();
    }
    printf("\n");
    
    // 5. 代码块作用域
    printf("5. 代码块作用域:\n");
    blockScope();
    printf("\n");
    
    // 6. for循环中的变量作用域
    printf("6. for循环变量作用域:\n");
    for (int i = 0; i < 3; i++) {
        printf("循环内: i = %d\n", i);
    }
    // printf("循环外: i = %d\n", i);  // 错误！i在这里不可见
    printf("循环变量i的作用域仅限于for循环内\n\n");
    
    // 7. 全局变量计数器
    printf("7. 全局变量作为计数器:\n");
    for (int i = 0; i < 5; i++) {
        printf("调用 %d: counter = %d\n", i + 1, incrementCounter());
    }
    printf("\n");
    
    // 8. 变量屏蔽（shadowing）
    printf("8. 变量屏蔽示例:\n");
    shadowingExample();
    printf("\n");
    
    // 9. 函数参数的作用域
    printf("9. 函数参数作用域:\n");
    int param = 100;
    printf("实参 param = %d\n", param);
    testParameter(param);
    printf("调用后 param = %d（未改变）\n\n", param);
    
    // 10. 实际应用：使用静态变量生成唯一ID
    printf("10. 实际应用 - 生成唯一ID:\n");
    for (int i = 0; i < 5; i++) {
        printf("生成ID: %d\n", generateID());
    }
    
    return 0;
}

// ========== 函数定义 ==========

/*
 * 演示局部变量
 */
void demonstrateLocal(void) {
    int local_var = 200;  // 这是该函数的局部变量
    printf("demonstrateLocal函数的局部变量 local_var = %d\n", local_var);
}

/*
 * 修改全局变量
 */
void modifyGlobal(void) {
    global_var = 200;  // 修改全局变量
    printf("modifyGlobal函数修改了全局变量\n");
}

/*
 * 演示静态局部变量
 */
void demonstrateStatic(void) {
    static int static_var = 0;  // 静态局部变量，只初始化一次
    int normal_var = 0;          // 普通局部变量，每次调用都初始化
    
    static_var++;
    normal_var++;
    
    printf("static_var = %d, normal_var = %d\n", static_var, normal_var);
}

/*
 * 演示代码块作用域
 */
void blockScope(void) {
    int outer = 10;
    printf("外层: outer = %d\n", outer);
    
    if (1) {  // if语句创建新的作用域
        int inner = 20;
        printf("if块内: outer = %d, inner = %d\n", outer, inner);
        outer = 30;  // 可以访问外层变量
    }
    
    printf("if块外: outer = %d\n", outer);
    // printf("inner = %d\n", inner);  // 错误！inner在这里不可见
}

/*
 * 递增全局计数器
 */
int incrementCounter(void) {
    return ++counter;
}

/*
 * 演示变量屏蔽
 */
void shadowingExample(void) {
    int value = 100;  // 局部变量屏蔽全局变量（如果有同名全局变量）
    printf("局部变量 value = %d\n", value);
    
    {
        int value = 200;  // 内层变量屏蔽外层变量
        printf("内层块 value = %d\n", value);
    }
    
    printf("外层 value = %d\n", value);
}

/*
 * 测试参数作用域
 */
void testParameter(int param) {
    printf("形参 param = %d\n", param);
    param = 999;  // 修改形参不影响实参
    printf("函数内修改后 param = %d\n", param);
}

/*
 * 使用静态变量生成唯一ID
 */
int generateID(void) {
    static int id = 1000;  // 静态变量，保持值
    return id++;
}

/*
 * 演示自动变量（局部变量）
 */
void autoVariable(void) {
    auto int auto_var = 10;  // auto关键字（通常省略）
    printf("自动变量: %d\n", auto_var);
}

// 另一个文件中可能有相同名称的静态全局变量
static int file_static = 500;  // 文件作用域的静态变量

/*
 * 访问文件静态变量
 */
void accessFileStatic(void) {
    printf("文件静态变量: %d\n", file_static);
}

/*
 * 知识点总结：
 * 
 * 变量的作用域：
 * 作用域是指变量可以被访问的代码区域
 * 
 * 1. 局部作用域（Local Scope）：
 *    - 在函数或代码块内定义
 *    - 只在定义的函数/块内可见
 *    - 函数参数也是局部变量
 *    - 生命周期：函数调用开始到结束
 * 
 * 2. 全局作用域（Global Scope）：
 *    - 在所有函数外定义
 *    - 整个程序可见
 *    - 生命周期：程序开始到结束
 *    - 默认初始化为0
 * 
 * 3. 代码块作用域（Block Scope）：
 *    - 在{}内定义
 *    - 只在该代码块内可见
 *    - 如：if、for、while的{}内
 * 
 * 4. 文件作用域（File Scope）：
 *    - 使用static修饰的全局变量
 *    - 只在当前文件可见
 *    - 避免命名冲突
 * 
 * 变量的存储类别：
 * 
 * 1. auto（自动变量）：
 *    - 默认的局部变量类型
 *    - 关键字通常省略
 *    - 存储在栈上
 *    - 函数结束时销毁
 * 
 * 2. static（静态变量）：
 *    - 静态局部变量：
 *      * 在函数内定义
 *      * 只初始化一次
 *      * 保持值到下次调用
 *      * 生命周期：程序开始到结束
 *    
 *    - 静态全局变量：
 *      * 在函数外定义
 *      * 限制在当前文件内
 *      * 避免命名冲突
 * 
 * 3. extern（外部变量）：
 *    - 声明全局变量
 *    - 变量定义在其他文件
 *    - 用于多文件程序
 * 
 * 4. register（寄存器变量）：
 *    - 建议存储在寄存器
 *    - 访问速度快
 *    - 现代编译器自动优化
 *    - 不能取地址
 * 
 * 变量的生命周期：
 * 
 * 1. 局部变量：
 *    - 创建：函数调用时
 *    - 销毁：函数返回时
 *    - 每次调用重新创建
 * 
 * 2. 静态局部变量：
 *    - 创建：程序开始时
 *    - 销毁：程序结束时
 *    - 只初始化一次
 *    - 保持值在函数调用之间
 * 
 * 3. 全局变量：
 *    - 创建：程序开始时
 *    - 销毁：程序结束时
 *    - 自动初始化为0
 * 
 * 变量屏蔽（Shadowing）：
 * - 内层作用域的变量与外层同名
 * - 内层变量屏蔽外层变量
 * - 外层变量仍然存在，只是暂时不可访问
 * - 离开内层作用域后，外层变量恢复可见
 * 
 * 全局变量 vs 局部变量：
 * 
 * 全局变量：
 * 优点：
 * - 所有函数可访问
 * - 数据共享方便
 * 
 * 缺点：
 * - 难以追踪修改
 * - 命名冲突风险
 * - 降低代码可维护性
 * - 可能意外修改
 * 
 * 局部变量：
 * 优点：
 * - 作用域明确
 * - 不会相互干扰
 * - 便于理解和维护
 * - 栈自动管理
 * 
 * 缺点：
 * - 需要通过参数传递
 * - 不能在函数间共享
 * 
 * 注意事项：
 * 1. 尽量使用局部变量
 * 2. 避免过多全局变量
 * 3. 注意变量屏蔽问题
 * 4. 静态变量慎用（隐藏的状态）
 * 5. 全局变量要有清晰命名
 * 6. 不要返回局部变量的地址
 * 
 * 常见错误：
 * 1. 在函数外访问局部变量
 * 2. 返回局部变量的地址
 * 3. 忘记初始化局部变量
 * 4. 过度使用全局变量
 * 5. 变量屏蔽导致的逻辑错误
 * 
 * 最佳实践：
 * - 优先使用局部变量
 * - 变量作用域尽可能小
 * - 全局变量要谨慎使用
 * - 使用static限制全局变量的文件作用域
 * - 为全局变量添加前缀避免冲突
 * - 静态局部变量用于需要保持状态的场景
 * - 避免变量屏蔽，使用不同名称
 * - 局部变量及时初始化
 */
