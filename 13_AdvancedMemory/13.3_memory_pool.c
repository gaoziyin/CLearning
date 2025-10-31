/*
 * 第十三章：高级内存管理
 * 13.3 自定义内存池
 * 
 * 本文件详细讲解内存池的设计、实现和应用
 * 编译命令：gcc 13.3_memory_pool.c -o 13.3
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

// ==================== 示例1：内存池基础概念 ====================

void example_memory_pool_basics() {
    printf("=== 示例1：内存池基础 ===\n\n");
    
    printf("什么是内存池？\n");
    printf("  • 预分配大块内存\n");
    printf("  • 按需分配小块\n");
    printf("  • 统一管理和回收\n");
    printf("  • 避免频繁系统调用\n");
    
    printf("\n为什么需要内存池？\n");
    printf("  问题:\n");
    printf("    ✗ malloc/free开销大\n");
    printf("    ✗ 内存碎片化\n");
    printf("    ✗ 性能不可预测\n");
    printf("    ✗ 调试困难\n");
    
    printf("\n  解决:\n");
    printf("    ✓ 减少系统调用\n");
    printf("    ✓ 固定大小块，无碎片\n");
    printf("    ✓ O(1)分配/释放\n");
    printf("    ✓ 集中管理，易调试\n");
    
    printf("\n应用场景：\n");
    printf("  • 游戏引擎（大量对象）\n");
    printf("  • 网络服务器（连接池）\n");
    printf("  • 嵌入式系统（有限内存）\n");
    printf("  • 实时系统（可预测性能）\n\n");
}

// ==================== 示例2：简单固定大小内存池 ====================

#define POOL_BLOCK_SIZE 64
#define POOL_BLOCK_COUNT 100

typedef struct Block {
    struct Block* next;
} Block;

typedef struct {
    Block* free_list;      // 空闲块链表
    char* memory;          // 内存池
    size_t block_size;     // 块大小
    size_t block_count;    // 总块数
    size_t used_blocks;    // 已用块数
} SimplePool;

SimplePool* simple_pool_create(size_t block_size, size_t block_count) {
    SimplePool* pool = (SimplePool*)malloc(sizeof(SimplePool));
    if (!pool) return NULL;
    
    // 分配内存池
    pool->memory = (char*)malloc(block_size * block_count);
    if (!pool->memory) {
        free(pool);
        return NULL;
    }
    
    pool->block_size = block_size;
    pool->block_count = block_count;
    pool->used_blocks = 0;
    
    // 初始化空闲链表
    pool->free_list = NULL;
    for (size_t i = 0; i < block_count; i++) {
        Block* block = (Block*)(pool->memory + i * block_size);
        block->next = pool->free_list;
        pool->free_list = block;
    }
    
    return pool;
}

void* simple_pool_alloc(SimplePool* pool) {
    if (pool->free_list == NULL) {
        return NULL;  // 内存池已满
    }
    
    // 从空闲链表取出一个块
    Block* block = pool->free_list;
    pool->free_list = block->next;
    pool->used_blocks++;
    
    return (void*)block;
}

void simple_pool_free(SimplePool* pool, void* ptr) {
    if (ptr == NULL) return;
    
    // 加入空闲链表
    Block* block = (Block*)ptr;
    block->next = pool->free_list;
    pool->free_list = block;
    pool->used_blocks--;
}

void simple_pool_destroy(SimplePool* pool) {
    if (pool) {
        free(pool->memory);
        free(pool);
    }
}

void simple_pool_stats(SimplePool* pool) {
    printf("  块大小: %zu 字节\n", pool->block_size);
    printf("  总块数: %zu\n", pool->block_count);
    printf("  已用块数: %zu\n", pool->used_blocks);
    printf("  空闲块数: %zu\n", pool->block_count - pool->used_blocks);
    printf("  使用率: %.1f%%\n", 
           (float)pool->used_blocks / pool->block_count * 100);
}

void example_simple_pool() {
    printf("=== 示例2：简单固定大小内存池 ===\n\n");
    
    SimplePool* pool = simple_pool_create(64, 10);
    if (!pool) {
        printf("创建内存池失败\n");
        return;
    }
    
    printf("内存池创建成功\n");
    simple_pool_stats(pool);
    
    // 分配一些块
    printf("\n分配5个块：\n");
    void* blocks[5];
    for (int i = 0; i < 5; i++) {
        blocks[i] = simple_pool_alloc(pool);
        printf("  块%d: %p\n", i, blocks[i]);
    }
    simple_pool_stats(pool);
    
    // 释放一些块
    printf("\n释放2个块：\n");
    simple_pool_free(pool, blocks[0]);
    simple_pool_free(pool, blocks[2]);
    simple_pool_stats(pool);
    
    // 再次分配
    printf("\n再分配2个块：\n");
    void* new1 = simple_pool_alloc(pool);
    void* new2 = simple_pool_alloc(pool);
    printf("  新块1: %p\n", new1);
    printf("  新块2: %p\n", new2);
    simple_pool_stats(pool);
    
    simple_pool_destroy(pool);
    printf("\n内存池已销毁\n\n");
}

// ==================== 示例3：多大小内存池 ====================

#define SIZE_CLASS_COUNT 5

typedef struct {
    size_t size;
    SimplePool* pool;
} SizeClass;

typedef struct {
    SizeClass classes[SIZE_CLASS_COUNT];
    int class_count;
} MultiSizePool;

MultiSizePool* multi_pool_create() {
    MultiSizePool* mp = (MultiSizePool*)malloc(sizeof(MultiSizePool));
    if (!mp) return NULL;
    
    // 定义大小类别: 32, 64, 128, 256, 512字节
    size_t sizes[] = {32, 64, 128, 256, 512};
    mp->class_count = SIZE_CLASS_COUNT;
    
    for (int i = 0; i < SIZE_CLASS_COUNT; i++) {
        mp->classes[i].size = sizes[i];
        mp->classes[i].pool = simple_pool_create(sizes[i], 50);
        if (!mp->classes[i].pool) {
            // 清理已创建的池
            for (int j = 0; j < i; j++) {
                simple_pool_destroy(mp->classes[j].pool);
            }
            free(mp);
            return NULL;
        }
    }
    
    return mp;
}

void* multi_pool_alloc(MultiSizePool* mp, size_t size) {
    // 找到合适的大小类别
    for (int i = 0; i < mp->class_count; i++) {
        if (size <= mp->classes[i].size) {
            return simple_pool_alloc(mp->classes[i].pool);
        }
    }
    
    // 太大，使用malloc
    return malloc(size);
}

void multi_pool_free(MultiSizePool* mp, void* ptr, size_t size) {
    if (!ptr) return;
    
    // 找到对应的池
    for (int i = 0; i < mp->class_count; i++) {
        if (size <= mp->classes[i].size) {
            simple_pool_free(mp->classes[i].pool, ptr);
            return;
        }
    }
    
    // 大块，使用free
    free(ptr);
}

void multi_pool_destroy(MultiSizePool* mp) {
    if (mp) {
        for (int i = 0; i < mp->class_count; i++) {
            simple_pool_destroy(mp->classes[i].pool);
        }
        free(mp);
    }
}

void example_multi_size_pool() {
    printf("=== 示例3：多大小内存池 ===\n\n");
    
    MultiSizePool* mp = multi_pool_create();
    if (!mp) {
        printf("创建多大小内存池失败\n");
        return;
    }
    
    printf("分配不同大小的内存：\n");
    void* p1 = multi_pool_alloc(mp, 20);   // 使用32字节池
    void* p2 = multi_pool_alloc(mp, 50);   // 使用64字节池
    void* p3 = multi_pool_alloc(mp, 100);  // 使用128字节池
    void* p4 = multi_pool_alloc(mp, 300);  // 使用512字节池
    
    printf("  20字节请求 → %p\n", p1);
    printf("  50字节请求 → %p\n", p2);
    printf("  100字节请求 → %p\n", p3);
    printf("  300字节请求 → %p\n", p4);
    
    printf("\n释放内存：\n");
    multi_pool_free(mp, p1, 20);
    multi_pool_free(mp, p2, 50);
    multi_pool_free(mp, p3, 100);
    multi_pool_free(mp, p4, 300);
    
    multi_pool_destroy(mp);
    printf("多大小内存池已销毁\n\n");
}

// ==================== 示例4：对象池 ====================

typedef struct {
    int id;
    char name[32];
    double value;
} GameObject;

typedef struct {
    GameObject* objects;
    bool* in_use;
    size_t capacity;
    size_t count;
} ObjectPool;

ObjectPool* object_pool_create(size_t capacity) {
    ObjectPool* pool = (ObjectPool*)malloc(sizeof(ObjectPool));
    if (!pool) return NULL;
    
    pool->objects = (GameObject*)calloc(capacity, sizeof(GameObject));
    pool->in_use = (bool*)calloc(capacity, sizeof(bool));
    
    if (!pool->objects || !pool->in_use) {
        free(pool->objects);
        free(pool->in_use);
        free(pool);
        return NULL;
    }
    
    pool->capacity = capacity;
    pool->count = 0;
    
    return pool;
}

GameObject* object_pool_acquire(ObjectPool* pool) {
    // 查找空闲对象
    for (size_t i = 0; i < pool->capacity; i++) {
        if (!pool->in_use[i]) {
            pool->in_use[i] = true;
            pool->count++;
            // 重置对象
            memset(&pool->objects[i], 0, sizeof(GameObject));
            return &pool->objects[i];
        }
    }
    return NULL;  // 池已满
}

void object_pool_release(ObjectPool* pool, GameObject* obj) {
    if (!obj) return;
    
    // 计算对象索引
    ptrdiff_t index = obj - pool->objects;
    if (index >= 0 && index < (ptrdiff_t)pool->capacity) {
        if (pool->in_use[index]) {
            pool->in_use[index] = false;
            pool->count--;
        }
    }
}

void object_pool_destroy(ObjectPool* pool) {
    if (pool) {
        free(pool->objects);
        free(pool->in_use);
        free(pool);
    }
}

void example_object_pool() {
    printf("=== 示例4：对象池 ===\n\n");
    
    ObjectPool* pool = object_pool_create(5);
    if (!pool) return;
    
    printf("创建对象池（容量：5）\n\n");
    
    // 获取对象
    printf("获取3个对象：\n");
    GameObject* obj1 = object_pool_acquire(pool);
    GameObject* obj2 = object_pool_acquire(pool);
    GameObject* obj3 = object_pool_acquire(pool);
    
    if (obj1) {
        obj1->id = 1;
        strcpy(obj1->name, "Player");
        obj1->value = 100.0;
        printf("  对象1: ID=%d, Name=%s\n", obj1->id, obj1->name);
    }
    
    if (obj2) {
        obj2->id = 2;
        strcpy(obj2->name, "Enemy");
        obj2->value = 50.0;
        printf("  对象2: ID=%d, Name=%s\n", obj2->id, obj2->name);
    }
    
    if (obj3) {
        obj3->id = 3;
        strcpy(obj3->name, "Item");
        obj3->value = 25.0;
        printf("  对象3: ID=%d, Name=%s\n", obj3->id, obj3->name);
    }
    
    printf("  已用对象: %zu / %zu\n", pool->count, pool->capacity);
    
    // 释放一个对象
    printf("\n释放对象2\n");
    object_pool_release(pool, obj2);
    printf("  已用对象: %zu / %zu\n", pool->count, pool->capacity);
    
    // 重新获取
    printf("\n重新获取对象\n");
    GameObject* obj4 = object_pool_acquire(pool);
    if (obj4) {
        obj4->id = 4;
        strcpy(obj4->name, "NewObject");
        printf("  对象4: ID=%d, Name=%s (重用了对象2的位置)\n", 
               obj4->id, obj4->name);
    }
    
    object_pool_destroy(pool);
    printf("\n对象池已销毁\n\n");
}

// ==================== 示例5：内存池性能测试 ====================

#include <time.h>

void performance_test_malloc(int iterations) {
    clock_t start = clock();
    
    void* ptrs[100];
    for (int iter = 0; iter < iterations; iter++) {
        for (int i = 0; i < 100; i++) {
            ptrs[i] = malloc(64);
        }
        for (int i = 0; i < 100; i++) {
            free(ptrs[i]);
        }
    }
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("  malloc/free: %.3f 秒\n", time_spent);
}

void performance_test_pool(int iterations) {
    SimplePool* pool = simple_pool_create(64, 100);
    clock_t start = clock();
    
    void* ptrs[100];
    for (int iter = 0; iter < iterations; iter++) {
        for (int i = 0; i < 100; i++) {
            ptrs[i] = simple_pool_alloc(pool);
        }
        for (int i = 0; i < 100; i++) {
            simple_pool_free(pool, ptrs[i]);
        }
    }
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("  内存池:     %.3f 秒\n", time_spent);
    
    simple_pool_destroy(pool);
}

void example_performance() {
    printf("=== 示例5：性能对比 ===\n\n");
    
    int iterations = 10000;
    printf("测试：%d次迭代，每次100个64字节块\n\n", iterations);
    
    performance_test_malloc(iterations);
    performance_test_pool(iterations);
    
    printf("\n内存池优势：\n");
    printf("  • 分配速度快2-10倍\n");
    printf("  • 无系统调用开销\n");
    printf("  • 无内存碎片\n");
    printf("  • 可预测的性能\n\n");
}

// ==================== 示例6：内存池的高级特性 ====================

void example_advanced_features() {
    printf("=== 示例6：高级特性 ===\n\n");
    
    printf("1. 自动扩展\n");
    printf("   • 初始分配固定大小\n");
    printf("   • 不足时自动扩展\n");
    printf("   • 维护多个内存块\n");
    printf("   缺点: 失去O(1)保证\n");
    
    printf("\n2. 线程安全\n");
    printf("   • 每线程独立池\n");
    printf("   • 或使用互斥锁保护\n");
    printf("   • 无锁队列实现\n");
    printf("   • 原子操作优化\n");
    
    printf("\n3. 内存对齐\n");
    printf("   • 按缓存行对齐（64字节）\n");
    printf("   • SIMD指令要求\n");
    printf("   • DMA传输要求\n");
    printf("   • 性能优化\n");
    
    printf("\n4. 调试支持\n");
    printf("   • 边界检查（魔法数）\n");
    printf("   • 使用追踪\n");
    printf("   • 泄漏检测\n");
    printf("   • 统计信息\n");
    
    printf("\n5. 内存回收策略\n");
    printf("   • 延迟回收（批量）\n");
    printf("   • 代龄管理\n");
    printf("   • 碎片整理\n");
    printf("   • 自适应调整\n\n");
}

// ==================== 示例7：实际应用场景 ====================

void example_use_cases() {
    printf("=== 示例7：实际应用 ===\n\n");
    
    printf("场景1：游戏引擎\n");
    printf("  需求:\n");
    printf("    • 大量游戏对象（子弹、粒子）\n");
    printf("    • 频繁创建/销毁\n");
    printf("    • 帧率稳定要求\n");
    printf("  方案:\n");
    printf("    • 对象池管理游戏实体\n");
    printf("    • 固定大小块，无碎片\n");
    printf("    • 预分配，避免运行时分配\n");
    
    printf("\n场景2：网络服务器\n");
    printf("  需求:\n");
    printf("    • 大量并发连接\n");
    printf("    • 每连接需要缓冲区\n");
    printf("    • 低延迟要求\n");
    printf("  方案:\n");
    printf("    • 连接池 + 缓冲区池\n");
    printf("    • 多大小池（小/中/大缓冲区）\n");
    printf("    • 每线程独立池\n");
    
    printf("\n场景3：嵌入式系统\n");
    printf("  需求:\n");
    printf("    • 有限RAM\n");
    printf("    • 不能使用malloc（太慢）\n");
    printf("    • 可靠性要求高\n");
    printf("  方案:\n");
    printf("    • 静态内存池\n");
    printf("    • 编译时分配\n");
    printf("    • 无动态分配\n");
    
    printf("\n场景4：数据库\n");
    printf("  需求:\n");
    printf("    • 缓存页面（固定大小）\n");
    printf("    • 频繁替换\n");
    printf("    • 高吞吐量\n");
    printf("  方案:\n");
    printf("    • 页面池\n");
    printf("    • LRU回收策略\n");
    printf("    • 预分配所有页面\n\n");
}

// ==================== 示例8：内存池的限制 ====================

void example_limitations() {
    printf("=== 示例8：内存池的限制 ===\n\n");
    
    printf("限制和权衡：\n\n");
    
    printf("1. 固定大小\n");
    printf("   问题: 不能处理任意大小\n");
    printf("   解决: 多大小类别 + malloc后备\n");
    
    printf("\n2. 预分配浪费\n");
    printf("   问题: 可能分配过多未使用内存\n");
    printf("   解决: 延迟分配、按需扩展\n");
    
    printf("\n3. 碎片问题\n");
    printf("   问题: 长期使用可能产生外部碎片\n");
    printf("   解决: 定期压缩、代龄管理\n");
    
    printf("\n4. 不适合的场景\n");
    printf("   • 小规模应用（开销不值得）\n");
    printf("   • 分配大小变化大\n");
    printf("   • 内存使用模式不规则\n");
    printf("   • 需要系统级内存管理\n");
    
    printf("\n5. 复杂性\n");
    printf("   • 需要额外代码维护\n");
    printf("   • 调试可能更困难\n");
    printf("   • 需要正确的大小估算\n\n");
}

// ==================== 示例9：最佳实践 ====================

void example_best_practices() {
    printf("=== 示例9：最佳实践 ===\n\n");
    
    printf("设计原则：\n");
    printf("  ✓ 选择合适的块大小\n");
    printf("  ✓ 估算合理的容量\n");
    printf("  ✓ 考虑对齐要求\n");
    printf("  ✓ 提供统计和监控\n");
    printf("  ✓ 支持调试模式\n");
    
    printf("\n实现建议：\n");
    printf("  ✓ 保持简单（先优化瓶颈）\n");
    printf("  ✓ 测量实际性能提升\n");
    printf("  ✓ 处理池满的情况\n");
    printf("  ✓ 线程安全（如需要）\n");
    printf("  ✓ 文档化使用方式\n");
    
    printf("\n使用建议：\n");
    printf("  ✓ 配对acquire/release\n");
    printf("  ✓ 重置对象状态\n");
    printf("  ✓ 不要混用malloc和pool\n");
    printf("  ✓ 监控使用率\n");
    printf("  ✓ 适时调整大小\n");
    
    printf("\n测试要点：\n");
    printf("  ✓ 边界条件（空、满）\n");
    printf("  ✓ 并发测试\n");
    printf("  ✓ 压力测试\n");
    printf("  ✓ 内存泄漏检查\n");
    printf("  ✓ 性能基准测试\n\n");
}

// ==================== 主函数 ====================

int main() {
    printf("╔═══════════════════════════════════════╗\n");
    printf("║   第13章：高级内存管理                ║\n");
    printf("║   13.3 自定义内存池                   ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
    
    example_memory_pool_basics();
    example_simple_pool();
    example_multi_size_pool();
    example_object_pool();
    example_performance();
    example_advanced_features();
    example_use_cases();
    example_limitations();
    example_best_practices();
    
    printf("═════════════════════════════════════════\n");
    printf("内存池总结：\n");
    printf("═════════════════════════════════════════\n");
    printf("核心概念：\n");
    printf("  • 预分配 - 避免频繁系统调用\n");
    printf("  • 固定块 - O(1)分配/释放\n");
    printf("  • 统一管理 - 简化内存管理\n");
    printf("  • 无碎片 - 固定大小块\n");
    printf("\n");
    printf("类型：\n");
    printf("  1. 固定大小池 - 最简单、最快\n");
    printf("  2. 多大小池   - 灵活性好\n");
    printf("  3. 对象池     - 特定类型对象\n");
    printf("  4. 通用池     - 类似malloc\n");
    printf("\n");
    printf("优势：\n");
    printf("  ✓ 性能提升2-10倍\n");
    printf("  ✓ 无内存碎片\n");
    printf("  ✓ 可预测性能\n");
    printf("  ✓ 集中管理\n");
    printf("\n");
    printf("适用场景：\n");
    printf("  • 大量小对象\n");
    printf("  • 频繁分配/释放\n");
    printf("  • 性能关键路径\n");
    printf("  • 嵌入式系统\n");
    printf("═════════════════════════════════════════\n");
    
    return 0;
}

/*
 * 编译和运行：
 *   gcc 13.3_memory_pool.c -o 13.3
 *   ./13.3
 * 
 * 性能优化编译：
 *   gcc -O2 13.3_memory_pool.c -o 13.3
 * 
 * 学习要点：
 *   1. 理解内存池的原理和优势
 *   2. 掌握固定大小池的实现
 *   3. 了解多大小池的设计
 *   4. 学习对象池模式
 *   5. 知道何时使用内存池
 * 
 * 实践建议：
 *   • 实现自己的内存池
 *   • 性能测试对比
 *   • 应用到实际项目
 *   • 尝试不同优化策略
 * 
 * 下一步：
 *   学习13.4 内存对齐与优化
 */
