/*
 * 第三章：函数
 * 3.6 存储类别 - static 和 extern
 * 
 * 学习目标：
 * 1. 掌握static关键字的用法
 * 2. 理解extern关键字的作用
 * 3. 了解变量的存储类别
 */

#include <stdio.h>

// ========== 全局变量 ==========
int global_count = 0;           // 全局变量，默认extern
static int file_count = 0;      // 文件作用域的静态变量，只在本文件可见

// 外部变量声明（假设在其他文件中定义）
// extern int external_var;      // 声明外部变量

// ========== 函数声明 ==========
void normalFunction(void);
static void fileFunction(void); // 静态函数，只在本文件可见
void useStaticVariable(void);
void useNormalVariable(void);
int getUniqueID(void);
void resetID(void);

int main() {
    printf("=== 存储类别：static 和 extern ===\n\n");
    
    // 1. 静态局部变量
    printf("1. 静态局部变量（保持值）:\n");
    for (int i = 0; i < 5; i++) {
        printf("第 %d 次调用: ", i + 1);
        useStaticVariable();
    }
    printf("\n");
    
    // 2. 普通局部变量对比
    printf("2. 普通局部变量（每次重置）:\n");
    for (int i = 0; i < 5; i++) {
        printf("第 %d 次调用: ", i + 1);
        useNormalVariable();
    }
    printf("\n");
    
    // 3. 全局变量
    printf("3. 全局变量（所有函数可访问）:\n");
    printf("初始 global_count = %d\n", global_count);
    normalFunction();
    printf("调用后 global_count = %d\n\n", global_count);
    
    // 4. 文件静态变量
    printf("4. 文件静态变量（文件内可见）:\n");
    printf("初始 file_count = %d\n", file_count);
    fileFunction();
    printf("调用后 file_count = %d\n\n", file_count);
    
    // 5. 生成唯一ID
    printf("5. 使用静态变量生成唯一ID:\n");
    for (int i = 0; i < 5; i++) {
        printf("ID: %d\n", getUniqueID());
    }
    printf("\n");
    
    // 6. 重置ID
    printf("6. 重置ID计数器:\n");
    resetID();
    printf("重置后的ID: %d\n\n", getUniqueID());
    
    // 7. 静态变量的初始化
    printf("7. 静态变量的初始化:\n");
    demonstrateInitialization();
    printf("\n");
    
    // 8. 函数调用计数器
    printf("8. 函数调用计数器:\n");
    for (int i = 0; i < 5; i++) {
        countCalls();
    }
    printf("\n");
    
    // 9. 实际应用：状态机
    printf("9. 实际应用 - 简单状态机:\n");
    for (int i = 0; i < 8; i++) {
        printf("状态 %d: %s\n", i + 1, getStateName());
    }
    printf("\n");
    
    // 10. 实际应用：缓存上次的值
    printf("10. 实际应用 - 缓存计算结果:\n");
    printf("第一次计算 5! = %d\n", cachedFactorial(5));
    printf("第二次计算 5! = %d (使用缓存)\n", cachedFactorial(5));
    printf("计算 6! = %d\n", cachedFactorial(6));
    
    return 0;
}

// ========== 函数定义 ==========

/*
 * 普通函数（默认extern）
 */
void normalFunction(void) {
    global_count++;
    printf("normalFunction: 修改全局变量\n");
}

/*
 * 静态函数（只在本文件可见）
 */
static void fileFunction(void) {
    file_count++;
    printf("fileFunction: 修改文件静态变量\n");
}

/*
 * 使用静态局部变量
 */
void useStaticVariable(void) {
    static int count = 0;  // 静态局部变量，保持值
    count++;
    printf("static count = %d\n", count);
}

/*
 * 使用普通局部变量
 */
void useNormalVariable(void) {
    int count = 0;  // 普通局部变量，每次重置
    count++;
    printf("normal count = %d\n", count);
}

/*
 * 生成唯一ID
 */
int getUniqueID(void) {
    static int id = 1000;  // 静态变量保持值
    return id++;
}

/*
 * 重置ID（访问静态变量）
 */
void resetID(void) {
    // 注意：无法直接重置getUniqueID中的静态变量
    // 这里演示一个独立的重置函数
    static int reset_flag = 0;
    reset_flag = 1;
    printf("ID计数器已重置\n");
}

/*
 * 演示静态变量的初始化
 */
void demonstrateInitialization(void) {
    static int initialized = 100;  // 只在第一次调用时初始化
    int not_initialized;           // 未初始化的局部变量
    
    printf("静态变量 initialized = %d（第一次为100，后续保持上次值）\n", initialized);
    // printf("局部变量 not_initialized = %d（未初始化，值不确定）\n", not_initialized);
    
    initialized++;
    
    static int auto_zero;  // 静态变量自动初始化为0
    printf("未显式初始化的静态变量 auto_zero = %d\n", auto_zero);
}

/*
 * 函数调用计数器
 */
void countCalls(void) {
    static int call_count = 0;
    call_count++;
    printf("函数被调用了 %d 次\n", call_count);
}

/*
 * 简单状态机
 */
char* getStateName(void) {
    static int state = 0;  // 状态变量
    
    // 状态数组
    static char* states[] = {
        "初始化",
        "就绪",
        "运行",
        "等待"
    };
    
    int current_state = state;
    state = (state + 1) % 4;  // 循环状态
    
    return states[current_state];
}

/*
 * 缓存阶乘计算结果
 */
int cachedFactorial(int n) {
    static int last_n = -1;      // 上次计算的n
    static int last_result = 0;   // 上次的结果
    
    // 如果是相同的输入，直接返回缓存结果
    if (n == last_n) {
        printf("(使用缓存) ");
        return last_result;
    }
    
    // 计算阶乘
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    
    // 更新缓存
    last_n = n;
    last_result = result;
    
    printf("(重新计算) ");
    return result;
}

/*
 * 静态函数示例：辅助函数
 */
static int helperFunction(int x) {
    return x * 2;
}

/*
 * 公共接口函数
 */
int publicFunction(int x) {
    // 调用静态辅助函数
    return helperFunction(x) + 10;
}

/*
 * 演示register关键字
 */
void demonstrateRegister(void) {
    register int fast_var = 100;  // 建议存储在寄存器
    printf("寄存器变量: %d\n", fast_var);
    // &fast_var;  // 错误！不能获取寄存器变量的地址
}

/*
 * 知识点总结：
 * 
 * 存储类别关键字：
 * 
 * 1. auto（自动）：
 *    - 默认的局部变量存储类别
 *    - 关键字通常省略
 *    - 存储在栈上
 *    - 函数返回时自动销毁
 *    
 *    int auto_var = 10;  // 等价于
 *    auto int auto_var = 10;
 * 
 * 2. static（静态）：
 *    A. 静态局部变量：
 *       - 在函数内定义
 *       - 只初始化一次
 *       - 保持值在函数调用之间
 *       - 生命周期：程序运行期间
 *       - 作用域：函数内
 *       - 存储在静态存储区
 *    
 *    B. 静态全局变量：
 *       - 在函数外定义
 *       - 限制在当前文件
 *       - 其他文件不可访问
 *       - 避免命名冲突
 *    
 *    C. 静态函数：
 *       - 限制在当前文件
 *       - 其他文件不可调用
 *       - 用于内部实现
 * 
 * 3. extern（外部）：
 *    - 声明变量/函数在其他文件中定义
 *    - 不分配存储空间
 *    - 用于多文件程序
 *    - 全局变量默认是extern
 *    
 *    // 文件1
 *    int shared_var = 100;
 *    
 *    // 文件2
 *    extern int shared_var;  // 声明，不是定义
 * 
 * 4. register（寄存器）：
 *    - 建议存储在CPU寄存器
 *    - 访问速度快
 *    - 不能取地址(&)
 *    - 现代编译器自动优化
 *    - 很少使用
 * 
 * static的用途：
 * 
 * 1. 保持局部变量的值：
 *    - 函数调用之间保持状态
 *    - 计数器、累加器
 *    - 缓存计算结果
 * 
 * 2. 限制作用域：
 *    - 防止全局变量冲突
 *    - 隐藏内部实现
 *    - 模块化设计
 * 
 * 3. 单例模式：
 *    - 确保只有一个实例
 *    - 保持全局状态
 * 
 * extern的用途：
 * 
 * 1. 多文件程序：
 *    - 共享全局变量
 *    - 声明在其他文件定义的变量
 * 
 * 2. 声明与定义分离：
 *    - 头文件：extern声明
 *    - 源文件：实际定义
 * 
 * 变量定义 vs 声明：
 * 
 * 定义：
 * - 分配存储空间
 * - 只能有一次
 * - int var = 10;
 * 
 * 声明：
 * - 不分配空间
 * - 可以多次
 * - extern int var;
 * 
 * 存储位置：
 * 
 * 1. 栈（Stack）：
 *    - auto局部变量
 *    - 函数参数
 *    - 自动管理
 * 
 * 2. 堆（Heap）：
 *    - 动态分配（malloc）
 *    - 手动管理
 * 
 * 3. 静态存储区：
 *    - 全局变量
 *    - static变量
 *    - 字符串常量
 * 
 * 4. 寄存器：
 *    - register变量
 *    - 编译器优化
 * 
 * 初始化：
 * 
 * 1. 局部变量：
 *    - 不自动初始化
 *    - 值不确定
 *    - 必须显式初始化
 * 
 * 2. 全局/静态变量：
 *    - 自动初始化为0
 *    - 可以显式初始化
 *    - 只初始化一次
 * 
 * 注意事项：
 * 1. static局部变量只初始化一次
 * 2. static限制作用域，不是生命周期
 * 3. 过多static变量降低可维护性
 * 4. extern声明不要加初始值
 * 5. 局部变量记得初始化
 * 
 * 常见错误：
 * 1. 混淆声明和定义
 * 2. 重复定义全局变量
 * 3. 忘记初始化局部变量
 * 4. static变量的意外副作用
 * 5. 在头文件中定义全局变量
 * 
 * 最佳实践：
 * - 尽量使用局部变量
 * - 用static限制文件作用域
 * - 全局变量要谨慎使用
 * - extern声明放在头文件
 * - 定义放在源文件
 * - static函数用于内部实现
 * - 避免过多static局部变量
 * - 为全局变量添加前缀
 * - 使用const保护只读数据
 */
