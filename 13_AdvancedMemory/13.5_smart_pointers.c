/*
 * 第十三章：高级内存管理
 * 13.5 智能指针模拟
 * 
 * 本文件详细讲解如何在C语言中模拟C++的智能指针
 * 编译命令：gcc 13.5_smart_pointers.c -o 13.5
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdatomic.h>

// ==================== 示例1：智能指针概念 ====================

void example_smart_pointer_basics() {
    printf("=== 示例1：智能指针基础 ===\n\n");
    
    printf("什么是智能指针？\n");
    printf("  • 自动管理内存的指针封装\n");
    printf("  • 离开作用域自动释放\n");
    printf("  • 防止内存泄漏\n");
    printf("  • C++的核心特性之一\n\n");
    
    printf("C++智能指针类型：\n");
    printf("  1. unique_ptr - 独占所有权\n");
    printf("     • 不能复制，只能移动\n");
    printf("     • 资源独占\n");
    printf("     • 零开销\n");
    printf("  \n");
    printf("  2. shared_ptr - 共享所有权\n");
    printf("     • 引用计数\n");
    printf("     • 多个指针共享\n");
    printf("     • 最后一个释放资源\n");
    printf("  \n");
    printf("  3. weak_ptr - 弱引用\n");
    printf("     • 不增加引用计数\n");
    printf("     • 打破循环引用\n");
    printf("     • 需要提升为shared_ptr使用\n\n");
    
    printf("为什么在C中模拟？\n");
    printf("  • 提高代码安全性\n");
    printf("  • 减少内存泄漏\n");
    printf("  • 学习内存管理原理\n");
    printf("  • 理解C++实现机制\n\n");
}

// ==================== 示例2：简单的unique_ptr实现 ====================

typedef struct {
    void* ptr;
    void (*deleter)(void*);
} UniquePtr;

UniquePtr unique_ptr_create(void* ptr, void (*deleter)(void*)) {
    UniquePtr up = {ptr, deleter ? deleter : free};
    return up;
}

void* unique_ptr_get(UniquePtr* up) {
    return up ? up->ptr : NULL;
}

void* unique_ptr_release(UniquePtr* up) {
    if (!up) return NULL;
    void* ptr = up->ptr;
    up->ptr = NULL;
    up->deleter = NULL;
    return ptr;
}

void unique_ptr_reset(UniquePtr* up, void* new_ptr) {
    if (!up) return;
    
    if (up->ptr && up->deleter) {
        up->deleter(up->ptr);
    }
    
    up->ptr = new_ptr;
}

void unique_ptr_destroy(UniquePtr* up) {
    if (!up) return;
    
    if (up->ptr && up->deleter) {
        up->deleter(up->ptr);
    }
    
    up->ptr = NULL;
    up->deleter = NULL;
}

void example_unique_ptr() {
    printf("=== 示例2：UniquePtr实现 ===\n\n");
    
    printf("创建UniquePtr：\n");
    int* data = (int*)malloc(sizeof(int) * 5);
    for (int i = 0; i < 5; i++) {
        data[i] = i * 10;
    }
    
    UniquePtr up = unique_ptr_create(data, free);
    printf("  UniquePtr创建成功\n");
    
    printf("\n访问数据：\n");
    int* ptr = (int*)unique_ptr_get(&up);
    if (ptr) {
        printf("  数据: ");
        for (int i = 0; i < 5; i++) {
            printf("%d ", ptr[i]);
        }
        printf("\n");
    }
    
    printf("\n重置指针：\n");
    int* new_data = (int*)malloc(sizeof(int));
    *new_data = 100;
    unique_ptr_reset(&up, new_data);
    printf("  原数据已自动释放\n");
    printf("  新数据: %d\n", *(int*)unique_ptr_get(&up));
    
    printf("\n销毁UniquePtr：\n");
    unique_ptr_destroy(&up);
    printf("  内存已自动释放\n\n");
    
    printf("特点：\n");
    printf("  ✓ 独占所有权\n");
    printf("  ✓ 自动释放\n");
    printf("  ✓ 可自定义删除器\n");
    printf("  ✓ 零开销（编译器优化）\n\n");
}

// ==================== 示例3：引用计数的shared_ptr实现 ====================

typedef struct {
    void* data;
    atomic_int ref_count;
    void (*deleter)(void*);
} ControlBlock;

typedef struct {
    ControlBlock* control;
} SharedPtr;

SharedPtr shared_ptr_create(void* data, void (*deleter)(void*)) {
    SharedPtr sp = {NULL};
    
    ControlBlock* cb = (ControlBlock*)malloc(sizeof(ControlBlock));
    if (!cb) {
        if (deleter) deleter(data);
        else free(data);
        return sp;
    }
    
    cb->data = data;
    atomic_init(&cb->ref_count, 1);
    cb->deleter = deleter ? deleter : free;
    
    sp.control = cb;
    return sp;
}

SharedPtr shared_ptr_copy(SharedPtr* sp) {
    SharedPtr copy = {NULL};
    
    if (sp && sp->control) {
        atomic_fetch_add(&sp->control->ref_count, 1);
        copy.control = sp->control;
    }
    
    return copy;
}

void* shared_ptr_get(SharedPtr* sp) {
    return (sp && sp->control) ? sp->control->data : NULL;
}

int shared_ptr_use_count(SharedPtr* sp) {
    return (sp && sp->control) ? 
           atomic_load(&sp->control->ref_count) : 0;
}

void shared_ptr_destroy(SharedPtr* sp) {
    if (!sp || !sp->control) return;
    
    int old_count = atomic_fetch_sub(&sp->control->ref_count, 1);
    
    if (old_count == 1) {
        // 最后一个引用，释放资源
        if (sp->control->data && sp->control->deleter) {
            sp->control->deleter(sp->control->data);
        }
        free(sp->control);
    }
    
    sp->control = NULL;
}

void example_shared_ptr() {
    printf("=== 示例3：SharedPtr实现 ===\n\n");
    
    printf("创建SharedPtr：\n");
    int* data = (int*)malloc(sizeof(int));
    *data = 42;
    
    SharedPtr sp1 = shared_ptr_create(data, free);
    printf("  sp1创建，值: %d\n", *(int*)shared_ptr_get(&sp1));
    printf("  引用计数: %d\n", shared_ptr_use_count(&sp1));
    
    printf("\n复制SharedPtr：\n");
    SharedPtr sp2 = shared_ptr_copy(&sp1);
    printf("  sp2创建（共享数据）\n");
    printf("  引用计数: %d\n", shared_ptr_use_count(&sp1));
    
    SharedPtr sp3 = shared_ptr_copy(&sp1);
    printf("  sp3创建（共享数据）\n");
    printf("  引用计数: %d\n", shared_ptr_use_count(&sp1));
    
    printf("\n销毁sp2：\n");
    shared_ptr_destroy(&sp2);
    printf("  引用计数: %d\n", shared_ptr_use_count(&sp1));
    
    printf("\n销毁sp3：\n");
    shared_ptr_destroy(&sp3);
    printf("  引用计数: %d\n", shared_ptr_use_count(&sp1));
    
    printf("\n销毁sp1：\n");
    shared_ptr_destroy(&sp1);
    printf("  最后一个引用，资源已释放\n\n");
    
    printf("特点：\n");
    printf("  ✓ 共享所有权\n");
    printf("  ✓ 引用计数\n");
    printf("  ✓ 线程安全（atomic）\n");
    printf("  ✓ 自动释放\n\n");
}

// ==================== 示例4：弱引用weak_ptr ====================

typedef struct {
    ControlBlock* control;
} WeakPtr;

WeakPtr weak_ptr_create(SharedPtr* sp) {
    WeakPtr wp = {NULL};
    
    if (sp && sp->control) {
        wp.control = sp->control;
        // 注意：不增加引用计数
    }
    
    return wp;
}

SharedPtr weak_ptr_lock(WeakPtr* wp) {
    SharedPtr sp = {NULL};
    
    if (!wp || !wp->control) return sp;
    
    // 尝试增加引用计数
    int old_count = atomic_load(&wp->control->ref_count);
    if (old_count > 0) {
        atomic_fetch_add(&wp->control->ref_count, 1);
        sp.control = wp->control;
    }
    
    return sp;
}

int weak_ptr_expired(WeakPtr* wp) {
    if (!wp || !wp->control) return 1;
    return atomic_load(&wp->control->ref_count) == 0;
}

void example_weak_ptr() {
    printf("=== 示例4：WeakPtr实现 ===\n\n");
    
    printf("创建SharedPtr和WeakPtr：\n");
    int* data = (int*)malloc(sizeof(int));
    *data = 100;
    
    SharedPtr sp = shared_ptr_create(data, free);
    WeakPtr wp = weak_ptr_create(&sp);
    
    printf("  SharedPtr值: %d\n", *(int*)shared_ptr_get(&sp));
    printf("  引用计数: %d\n", shared_ptr_use_count(&sp));
    printf("  WeakPtr过期: %s\n", weak_ptr_expired(&wp) ? "是" : "否");
    
    printf("\n从WeakPtr提升为SharedPtr：\n");
    SharedPtr sp2 = weak_ptr_lock(&wp);
    if (shared_ptr_get(&sp2)) {
        printf("  提升成功\n");
        printf("  引用计数: %d\n", shared_ptr_use_count(&sp));
        shared_ptr_destroy(&sp2);
    }
    
    printf("\n销毁SharedPtr：\n");
    shared_ptr_destroy(&sp);
    printf("  WeakPtr过期: %s\n", weak_ptr_expired(&wp) ? "是" : "否");
    
    printf("\n尝试再次提升：\n");
    SharedPtr sp3 = weak_ptr_lock(&wp);
    if (!shared_ptr_get(&sp3)) {
        printf("  提升失败（对象已销毁）\n");
    }
    
    printf("\nWeakPtr用途：\n");
    printf("  • 打破循环引用\n");
    printf("  • 缓存（不阻止释放）\n");
    printf("  • 观察者模式\n\n");
}

// ==================== 示例5：自动清理（类似RAII）====================

#define AUTO_FREE __attribute__((cleanup(auto_free_func)))

void auto_free_func(void* pp) {
    void** ptr = (void**)pp;
    if (*ptr) {
        printf("    [自动释放: %p]\n", *ptr);
        free(*ptr);
        *ptr = NULL;
    }
}

void example_auto_cleanup() {
    printf("=== 示例5：自动清理（GCC扩展）===\n\n");
    
    #ifdef __GNUC__
    printf("使用__attribute__((cleanup))：\n\n");
    
    {
        printf("进入作用域\n");
        AUTO_FREE int* data = (int*)malloc(sizeof(int) * 5);
        
        if (data) {
            printf("  分配内存: %p\n", (void*)data);
            for (int i = 0; i < 5; i++) {
                data[i] = i;
            }
        }
        
        printf("离开作用域...\n");
    }
    printf("已自动释放\n\n");
    
    printf("原理：\n");
    printf("  • GCC/Clang扩展\n");
    printf("  • 变量离开作用域时调用函数\n");
    printf("  • 类似C++的析构函数\n");
    printf("  • 可用于任何资源\n\n");
    #else
    printf("需要GCC或Clang编译器\n\n");
    #endif
}

// ==================== 示例6：实际应用 - 文件智能指针 ====================

typedef struct {
    FILE* file;
} SmartFile;

void smart_file_deleter(void* ptr) {
    FILE* file = (FILE*)ptr;
    if (file) {
        printf("    [关闭文件]\n");
        fclose(file);
    }
}

SmartFile* smart_file_open(const char* filename, const char* mode) {
    SmartFile* sf = (SmartFile*)malloc(sizeof(SmartFile));
    if (!sf) return NULL;
    
    sf->file = fopen(filename, mode);
    if (!sf->file) {
        free(sf);
        return NULL;
    }
    
    return sf;
}

void smart_file_close(SmartFile* sf) {
    if (sf) {
        if (sf->file) {
            fclose(sf->file);
            sf->file = NULL;
        }
        free(sf);
    }
}

void example_smart_file() {
    printf("=== 示例6：文件智能指针 ===\n\n");
    
    printf("创建临时文件：\n");
    FILE* temp = fopen("test.txt", "w");
    if (temp) {
        fprintf(temp, "Hello, Smart Pointers!\n");
        fclose(temp);
        printf("  test.txt已创建\n");
    }
    
    printf("\n使用智能文件指针：\n");
    SmartFile* sf = smart_file_open("test.txt", "r");
    if (sf && sf->file) {
        printf("  文件打开成功\n");
        
        char buffer[100];
        if (fgets(buffer, sizeof(buffer), sf->file)) {
            printf("  内容: %s", buffer);
        }
        
        printf("  关闭文件...\n");
        smart_file_close(sf);
        printf("  文件已自动关闭\n");
    }
    
    // 清理测试文件
    remove("test.txt");
    
    printf("\n优势：\n");
    printf("  • 异常安全（C中的错误处理）\n");
    printf("  • 资源自动释放\n");
    printf("  • 减少泄漏风险\n\n");
}

// ==================== 示例7：循环引用问题 ====================

typedef struct Node Node;

struct Node {
    int value;
    SharedPtr parent;  // 如果用SharedPtr会循环引用
    // WeakPtr parent; // 应该用WeakPtr
    SharedPtr child;
};

void node_deleter(void* ptr) {
    Node* node = (Node*)ptr;
    if (node) {
        printf("    [删除节点: %d]\n", node->value);
        shared_ptr_destroy(&node->parent);
        shared_ptr_destroy(&node->child);
        free(node);
    }
}

void example_circular_reference() {
    printf("=== 示例7：循环引用问题 ===\n\n");
    
    printf("问题：父子节点互相持有SharedPtr\n");
    printf("  • 父节点持有子节点的SharedPtr\n");
    printf("  • 子节点持有父节点的SharedPtr\n");
    printf("  • 引用计数永远不为0\n");
    printf("  • 导致内存泄漏\n\n");
    
    printf("解决方案：\n");
    printf("  1. 使用WeakPtr打破循环\n");
    printf("     • 子节点用WeakPtr引用父节点\n");
    printf("     • 父节点用SharedPtr拥有子节点\n");
    printf("  \n");
    printf("  2. 明确所有权\n");
    printf("     • 只有一方拥有另一方\n");
    printf("     • 另一方使用普通指针（需小心）\n");
    printf("  \n");
    printf("  3. 手动打破循环\n");
    printf("     • 销毁前显式清理引用\n\n");
}

// ==================== 示例8：线程安全考虑 ====================

void example_thread_safety() {
    printf("=== 示例8：线程安全 ===\n\n");
    
    printf("SharedPtr的线程安全：\n");
    printf("  引用计数操作：\n");
    printf("    ✓ 使用atomic操作\n");
    printf("    ✓ 多线程可安全复制/销毁同一个SharedPtr\n");
    printf("  \n");
    printf("  数据访问：\n");
    printf("    ✗ 不保护指向的数据\n");
    printf("    ✗ 需要额外的同步机制\n\n");
    
    printf("示例：\n");
    printf("  SharedPtr<Data> sp = ...;\n");
    printf("  \n");
    printf("  线程1: sp2 = sp;  // 安全（引用计数是原子的）\n");
    printf("  线程2: sp3 = sp;  // 安全\n");
    printf("  \n");
    printf("  线程1: sp->value = 10;  // 不安全！需要锁保护\n");
    printf("  线程2: x = sp->value;   // 不安全！需要锁保护\n\n");
    
    printf("最佳实践：\n");
    printf("  • SharedPtr本身的复制是线程安全的\n");
    printf("  • 访问共享数据需要额外保护\n");
    printf("  • 考虑使用互斥锁或读写锁\n\n");
}

// ==================== 示例9：性能考虑 ====================

void example_performance() {
    printf("=== 示例9：性能考虑 ===\n\n");
    
    printf("智能指针开销：\n");
    printf("  UniquePtr:\n");
    printf("    • 大小: sizeof(void*) + sizeof(function_ptr)\n");
    printf("    • 开销: 几乎为零（编译器优化）\n");
    printf("    • 推荐用于独占所有权\n");
    printf("  \n");
    printf("  SharedPtr:\n");
    printf("    • 大小: sizeof(void*)\n");
    printf("    • 额外分配: 控制块（引用计数等）\n");
    printf("    • atomic操作开销\n");
    printf("    • 适用于需要共享的场景\n");
    printf("  \n");
    printf("  WeakPtr:\n");
    printf("    • 大小: sizeof(void*)\n");
    printf("    • 不增加引用计数\n");
    printf("    • lock()操作有开销\n\n");
    
    printf("优化建议：\n");
    printf("  1. 优先使用UniquePtr\n");
    printf("  2. 必要时使用SharedPtr\n");
    printf("  3. 避免过度使用\n");
    printf("  4. 考虑对象池\n");
    printf("  5. 注意缓存局部性\n\n");
}

// ==================== 示例10：最佳实践 ====================

void example_best_practices() {
    printf("=== 示例10：最佳实践 ===\n\n");
    
    printf("设计原则：\n");
    printf("  1. 明确所有权\n");
    printf("     • 谁拥有资源？\n");
    printf("     • 谁负责释放？\n");
    printf("     • 使用类型表达所有权\n");
    printf("  \n");
    printf("  2. 选择合适的指针\n");
    printf("     • 独占 → UniquePtr\n");
    printf("     • 共享 → SharedPtr\n");
    printf("     • 观察 → WeakPtr\n");
    printf("     • 临时 → 普通指针\n");
    printf("  \n");
    printf("  3. 避免循环引用\n");
    printf("     • 使用WeakPtr打破循环\n");
    printf("     • 重新设计数据结构\n");
    printf("     • 明确父子关系\n\n");
    
    printf("实现建议：\n");
    printf("  • 提供完整的API\n");
    printf("  • 处理NULL指针\n");
    printf("  • 线程安全考虑\n");
    printf("  • 添加调试支持\n");
    printf("  • 文档化使用方式\n\n");
    
    printf("C语言限制：\n");
    printf("  ✗ 无RAII（需手动销毁）\n");
    printf("  ✗ 无移动语义\n");
    printf("  ✗ 无模板（类型不安全）\n");
    printf("  ✗ 编译器不强制\n");
    printf("  \n");
    printf("  解决：\n");
    printf("  • 使用宏简化\n");
    printf("  • 约定命名规范\n");
    printf("  • 严格的代码审查\n");
    printf("  • 使用静态分析工具\n\n");
}

// ==================== 主函数 ====================

int main() {
    printf("╔═══════════════════════════════════════╗\n");
    printf("║   第13章：高级内存管理                ║\n");
    printf("║   13.5 智能指针模拟                   ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
    
    example_smart_pointer_basics();
    example_unique_ptr();
    example_shared_ptr();
    example_weak_ptr();
    example_auto_cleanup();
    example_smart_file();
    example_circular_reference();
    example_thread_safety();
    example_performance();
    example_best_practices();
    
    printf("═════════════════════════════════════════\n");
    printf("智能指针总结：\n");
    printf("═════════════════════════════════════════\n");
    printf("核心思想：\n");
    printf("  • 自动内存管理\n");
    printf("  • 明确所有权\n");
    printf("  • 防止泄漏\n");
    printf("  • 异常安全\n");
    printf("\n");
    printf("类型对比：\n");
    printf("  UniquePtr  - 独占所有权，零开销\n");
    printf("  SharedPtr  - 共享所有权，引用计数\n");
    printf("  WeakPtr    - 弱引用，打破循环\n");
    printf("\n");
    printf("应用场景：\n");
    printf("  • 资源管理（文件、网络等）\n");
    printf("  • 树形结构（父子关系）\n");
    printf("  • 缓存系统\n");
    printf("  • 观察者模式\n");
    printf("\n");
    printf("C语言实现要点：\n");
    printf("  • 封装指针和元数据\n");
    printf("  • 提供创建/销毁函数\n");
    printf("  • 引用计数（SharedPtr）\n");
    printf("  • 使用atomic保证线程安全\n");
    printf("  • 自定义删除器\n");
    printf("\n");
    printf("第13章完成！\n");
    printf("═════════════════════════════════════════\n");
    
    return 0;
}

/*
 * 编译和运行：
 *   gcc -std=c11 13.5_smart_pointers.c -o 13.5
 *   ./13.5
 * 
 * 注意：
 *   • 需要C11支持（atomic）
 *   • GCC/Clang: -std=c11
 *   • 链接: -latomic（某些平台）
 * 
 * 学习要点：
 *   1. 理解智能指针的原理
 *   2. 掌握引用计数实现
 *   3. 了解循环引用问题
 *   4. 学习线程安全考虑
 *   5. 知道何时使用哪种智能指针
 * 
 * 实践建议：
 *   • 实现完整的智能指针库
 *   • 应用到实际项目
 *   • 比较C和C++实现
 *   • 测试线程安全性
 * 
 * 下一步：
 *   学习第14章 - 数据结构实现
 */
