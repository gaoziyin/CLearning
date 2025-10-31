/*
 * 第十三章：高级内存管理
 * 13.1 内存分配详解
 * 
 * 本文件详细讲解C语言内存分配函数及其使用技巧
 * 编译命令：gcc 13.1_memory_allocation.c -o 13.1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 示例1：malloc - 分配未初始化的内存
void example_malloc() {
    printf("=== 示例1：malloc（内存分配）===\n\n");
    
    // malloc分配指定字节数的内存
    int* ptr = (int*)malloc(sizeof(int) * 5);
    
    if (ptr == NULL) {
        printf("内存分配失败！\n");
        return;
    }
    
    printf("malloc分配的内存（未初始化）：\n");
    for (int i = 0; i < 5; i++) {
        printf("  ptr[%d] = %d (垃圾值)\n", i, ptr[i]);
    }
    
    // 手动初始化
    for (int i = 0; i < 5; i++) {
        ptr[i] = i * 10;
    }
    
    printf("\n初始化后：\n");
    for (int i = 0; i < 5; i++) {
        printf("  ptr[%d] = %d\n", i, ptr[i]);
    }
    
    printf("\nmalloc特点：\n");
    printf("  • 分配size字节的内存\n");
    printf("  • 内容未初始化（包含垃圾值）\n");
    printf("  • 返回void*，需要类型转换\n");
    printf("  • 失败返回NULL\n");
    printf("  • 必须手动free释放\n");
    
    free(ptr);
    printf("\n内存已释放\n\n");
}

// 示例2：calloc - 分配并初始化为0
void example_calloc() {
    printf("=== 示例2：calloc（清零分配）===\n\n");
    
    // calloc分配n个元素，每个size字节，并初始化为0
    int* arr = (int*)calloc(5, sizeof(int));
    
    if (arr == NULL) {
        printf("内存分配失败！\n");
        return;
    }
    
    printf("calloc分配的内存（自动初始化为0）：\n");
    for (int i = 0; i < 5; i++) {
        printf("  arr[%d] = %d\n", i, arr[i]);
    }
    
    // 结构体数组示例
    typedef struct {
        int id;
        char name[20];
    } Person;
    
    Person* people = (Person*)calloc(3, sizeof(Person));
    if (people != NULL) {
        printf("\ncalloc分配的结构体数组（自动清零）：\n");
        for (int i = 0; i < 3; i++) {
            printf("  people[%d]: id=%d, name=\"%s\"\n", 
                   i, people[i].id, people[i].name);
        }
        free(people);
    }
    
    printf("\ncalloc特点：\n");
    printf("  • 分配count个元素，每个size字节\n");
    printf("  • 自动初始化为0（所有字节为0）\n");
    printf("  • 适合数组和结构体\n");
    printf("  • 比malloc略慢（需要清零）\n");
    printf("  • 更安全（避免垃圾值）\n");
    
    free(arr);
    printf("\n内存已释放\n\n");
}

// 示例3：realloc - 调整内存大小
void example_realloc() {
    printf("=== 示例3：realloc（重新分配）===\n\n");
    
    // 初始分配
    int* data = (int*)malloc(sizeof(int) * 5);
    if (data == NULL) return;
    
    // 初始化
    for (int i = 0; i < 5; i++) {
        data[i] = i + 1;
    }
    
    printf("原始数组（5个元素）：\n  ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
    
    // 扩大到10个元素
    int* new_data = (int*)realloc(data, sizeof(int) * 10);
    if (new_data == NULL) {
        printf("重新分配失败！\n");
        free(data);
        return;
    }
    data = new_data;
    
    // 初始化新增的元素
    for (int i = 5; i < 10; i++) {
        data[i] = i + 1;
    }
    
    printf("\n扩展后（10个元素）：\n  ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
    
    // 缩小到3个元素
    data = (int*)realloc(data, sizeof(int) * 3);
    if (data == NULL) return;
    
    printf("\n缩小后（3个元素）：\n  ");
    for (int i = 0; i < 3; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
    
    printf("\nrealloc特点：\n");
    printf("  • 调整已分配内存的大小\n");
    printf("  • 可能移动到新位置\n");
    printf("  • 保留原有数据（尽可能）\n");
    printf("  • 扩大：新增部分未初始化\n");
    printf("  • 缩小：截断多余数据\n");
    printf("  • 失败时原内存不变\n");
    
    printf("\n⚠ 重要：realloc使用注意事项\n");
    printf("  1. 必须检查返回值\n");
    printf("  2. 不要直接赋值给原指针（可能导致泄漏）\n");
    printf("     错误: data = realloc(data, new_size);\n");
    printf("     正确: new_data = realloc(data, new_size);\n");
    printf("           if (new_data) data = new_data;\n");
    printf("  3. realloc(NULL, size) 等价于 malloc(size)\n");
    printf("  4. realloc(ptr, 0) 等价于 free(ptr)\n");
    
    free(data);
    printf("\n内存已释放\n\n");
}

// 示例4：malloc vs calloc vs realloc 对比
void example_comparison() {
    printf("=== 示例4：内存分配函数对比 ===\n\n");
    
    printf("┌─────────────┬────────────────┬─────────────────┬─────────────┐\n");
    printf("│   函数      │    用途        │    初始化       │   速度      │\n");
    printf("├─────────────┼────────────────┼─────────────────┼─────────────┤\n");
    printf("│ malloc      │ 分配新内存     │ 否（垃圾值）    │ 快          │\n");
    printf("│ calloc      │ 分配新内存     │ 是（清零）      │ 较慢        │\n");
    printf("│ realloc     │ 调整大小       │ 新增部分不清零  │ 中等        │\n");
    printf("└─────────────┴────────────────┴─────────────────┴─────────────┘\n");
    
    printf("\n函数原型：\n");
    printf("  void* malloc(size_t size);\n");
    printf("  void* calloc(size_t count, size_t size);\n");
    printf("  void* realloc(void* ptr, size_t new_size);\n");
    printf("  void free(void* ptr);\n");
    
    printf("\n选择建议：\n");
    printf("  malloc:  性能关键且会立即初始化\n");
    printf("  calloc:  需要清零或处理结构体数组\n");
    printf("  realloc: 动态调整已分配内存大小\n\n");
}

// 示例5：内存分配失败处理
void* safe_malloc(size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "错误：内存分配失败（%zu字节）\n", size);
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void example_error_handling() {
    printf("=== 示例5：错误处理 ===\n\n");
    
    printf("方法1：检查并返回错误\n");
    printf("  int* ptr = malloc(size);\n");
    printf("  if (ptr == NULL) {\n");
    printf("    return -1;  // 或其他错误码\n");
    printf("  }\n");
    
    printf("\n方法2：检查并退出\n");
    printf("  int* ptr = malloc(size);\n");
    printf("  if (ptr == NULL) {\n");
    printf("    perror(\"malloc\");\n");
    printf("    exit(EXIT_FAILURE);\n");
    printf("  }\n");
    
    printf("\n方法3：封装安全函数\n");
    printf("  void* safe_malloc(size_t size) {\n");
    printf("    void* ptr = malloc(size);\n");
    printf("    if (ptr == NULL) {\n");
    printf("      fprintf(stderr, \"内存分配失败\\n\");\n");
    printf("      exit(1);\n");
    printf("    }\n");
    printf("    return ptr;\n");
    printf("  }\n");
    
    // 演示安全分配
    int* data = (int*)safe_malloc(sizeof(int) * 10);
    printf("\n安全分配成功：%p\n", (void*)data);
    free(data);
    
    printf("\n最佳实践：\n");
    printf("  ✓ 始终检查返回值\n");
    printf("  ✓ 记录失败原因\n");
    printf("  ✓ 清理已分配资源\n");
    printf("  ✓ 提供降级策略\n\n");
}

// 示例6：对齐内存分配
#include <stdint.h>

void* aligned_malloc(size_t size, size_t alignment) {
    // 确保alignment是2的幂
    if ((alignment & (alignment - 1)) != 0) {
        return NULL;
    }
    
    // 分配额外空间存储原始指针和对齐
    size_t total_size = size + alignment + sizeof(void*);
    void* raw_ptr = malloc(total_size);
    if (raw_ptr == NULL) {
        return NULL;
    }
    
    // 计算对齐地址
    uintptr_t raw_addr = (uintptr_t)raw_ptr;
    uintptr_t aligned_addr = (raw_addr + sizeof(void*) + alignment - 1) & ~(alignment - 1);
    
    // 在对齐地址前存储原始指针
    void** ptr_slot = (void**)(aligned_addr - sizeof(void*));
    *ptr_slot = raw_ptr;
    
    return (void*)aligned_addr;
}

void aligned_free(void* ptr) {
    if (ptr != NULL) {
        // 获取原始指针
        void** ptr_slot = (void**)ptr - 1;
        void* raw_ptr = *ptr_slot;
        free(raw_ptr);
    }
}

void example_aligned_allocation() {
    printf("=== 示例6：对齐内存分配 ===\n\n");
    
    printf("16字节对齐分配：\n");
    void* ptr1 = aligned_malloc(100, 16);
    printf("  地址: %p\n", ptr1);
    printf("  对齐: %s\n", ((uintptr_t)ptr1 % 16 == 0) ? "是" : "否");
    aligned_free(ptr1);
    
    printf("\n64字节对齐分配：\n");
    void* ptr2 = aligned_malloc(256, 64);
    printf("  地址: %p\n", ptr2);
    printf("  对齐: %s\n", ((uintptr_t)ptr2 % 64 == 0) ? "是" : "否");
    aligned_free(ptr2);
    
    printf("\n为什么需要对齐？\n");
    printf("  • CPU访问对齐数据更快\n");
    printf("  • SIMD指令要求（SSE/AVX）\n");
    printf("  • DMA传输要求\n");
    printf("  • 缓存行优化\n");
    
    printf("\nC11标准函数（如果支持）：\n");
    printf("  void* aligned_alloc(size_t alignment, size_t size);\n");
    printf("  void* posix_memalign(void** memptr, size_t align, size_t size);\n\n");
}

// 示例7：灵活数组成员（Flexible Array Member）
typedef struct {
    int count;
    int data[];  // 灵活数组成员（C99）
} FlexArray;

void example_flexible_array() {
    printf("=== 示例7：灵活数组成员 ===\n\n");
    
    int n = 5;
    FlexArray* arr = (FlexArray*)malloc(sizeof(FlexArray) + n * sizeof(int));
    if (arr == NULL) return;
    
    arr->count = n;
    for (int i = 0; i < n; i++) {
        arr->data[i] = i * 10;
    }
    
    printf("灵活数组内容：\n");
    printf("  count = %d\n", arr->count);
    printf("  data = [");
    for (int i = 0; i < arr->count; i++) {
        printf("%d", arr->data[i]);
        if (i < arr->count - 1) printf(", ");
    }
    printf("]\n");
    
    printf("\n灵活数组成员特点：\n");
    printf("  • C99标准引入\n");
    printf("  • 必须是结构体最后一个成员\n");
    printf("  • 不占用sizeof计算的大小\n");
    printf("  • 需要手动计算总大小\n");
    printf("  • 单次分配，无碎片\n");
    
    printf("\n语法：\n");
    printf("  struct MyStruct {\n");
    printf("    int size;\n");
    printf("    int data[];  // 灵活数组\n");
    printf("  };\n");
    
    free(arr);
    printf("\n");
}

// 示例8：内存分配的性能考虑
#include <time.h>

void example_performance() {
    printf("=== 示例8：性能考虑 ===\n\n");
    
    const int iterations = 100000;
    clock_t start, end;
    
    // 测试malloc
    start = clock();
    for (int i = 0; i < iterations; i++) {
        int* ptr = (int*)malloc(sizeof(int) * 10);
        free(ptr);
    }
    end = clock();
    double malloc_time = (double)(end - start) / CLOCKS_PER_SEC;
    
    // 测试calloc
    start = clock();
    for (int i = 0; i < iterations; i++) {
        int* ptr = (int*)calloc(10, sizeof(int));
        free(ptr);
    }
    end = clock();
    double calloc_time = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("性能测试（%d次分配/释放）：\n", iterations);
    printf("  malloc: %.3f 秒\n", malloc_time);
    printf("  calloc: %.3f 秒\n", calloc_time);
    printf("  差异: %.1f%%\n", (calloc_time / malloc_time - 1) * 100);
    
    printf("\n性能优化建议：\n");
    printf("  1. 减少分配次数\n");
    printf("     • 一次分配大块内存\n");
    printf("     • 重用已分配内存\n");
    printf("  2. 使用内存池\n");
    printf("     • 预分配固定大小块\n");
    printf("     • 快速分配/回收\n");
    printf("  3. 避免碎片\n");
    printf("     • 按大小分类\n");
    printf("     • 定期整理\n");
    printf("  4. 批量操作\n");
    printf("     • 一次分配多个对象\n");
    printf("     • 使用数组而非链表\n\n");
}

// 示例9：常见错误及避免方法
void example_common_mistakes() {
    printf("=== 示例9：常见错误 ===\n\n");
    
    printf("错误1：忘记检查NULL\n");
    printf("  ✗ int* p = malloc(size);\n");
    printf("     *p = 10;  // p可能是NULL！\n");
    printf("  ✓ int* p = malloc(size);\n");
    printf("     if (p != NULL) *p = 10;\n");
    
    printf("\n错误2：内存泄漏\n");
    printf("  ✗ void func() {\n");
    printf("       int* p = malloc(100);\n");
    printf("       // 忘记free(p);\n");
    printf("     }\n");
    printf("  ✓ 始终配对malloc/free\n");
    
    printf("\n错误3：重复释放\n");
    printf("  ✗ free(ptr);\n");
    printf("     free(ptr);  // 双重释放！\n");
    printf("  ✓ free(ptr);\n");
    printf("     ptr = NULL;  // 防止误用\n");
    
    printf("\n错误4：使用已释放内存\n");
    printf("  ✗ free(ptr);\n");
    printf("     *ptr = 10;  // 悬空指针！\n");
    printf("  ✓ free后将指针设为NULL\n");
    
    printf("\n错误5：realloc错误使用\n");
    printf("  ✗ ptr = realloc(ptr, new_size);\n");
    printf("     // realloc失败时ptr丢失！\n");
    printf("  ✓ tmp = realloc(ptr, new_size);\n");
    printf("     if (tmp != NULL) ptr = tmp;\n");
    
    printf("\n错误6：sizeof错误\n");
    printf("  ✗ int* arr = malloc(10);  // 只分配10字节\n");
    printf("  ✓ int* arr = malloc(10 * sizeof(int));\n");
    
    printf("\n错误7：栈上的指针\n");
    printf("  ✗ int* func() {\n");
    printf("       int x = 10;\n");
    printf("       return &x;  // 返回栈地址！\n");
    printf("     }\n");
    printf("  ✓ 使用malloc分配堆内存\n\n");
}

// 示例10：最佳实践
void example_best_practices() {
    printf("=== 示例10：最佳实践 ===\n\n");
    
    printf("1. 配对原则\n");
    printf("   • 每个malloc/calloc对应一个free\n");
    printf("   • 在同一层级分配和释放\n");
    printf("   • 使用RAII模式（C++）或自定义清理函数\n");
    
    printf("\n2. 初始化\n");
    printf("   • malloc后立即初始化\n");
    printf("   • 或使用calloc自动清零\n");
    printf("   • 避免使用未初始化内存\n");
    
    printf("\n3. 错误处理\n");
    printf("   • 始终检查返回值\n");
    printf("   • 失败时清理已分配资源\n");
    printf("   • 提供错误信息\n");
    
    printf("\n4. 防御性编程\n");
    printf("   • free后设置指针为NULL\n");
    printf("   • 使用assert检查前提条件\n");
    printf("   • 边界检查\n");
    
    printf("\n5. 文档和注释\n");
    printf("   • 明确谁负责释放内存\n");
    printf("   • 函数注释说明内存所有权\n");
    printf("   • 标记资源获取点\n");
    
    printf("\n6. 工具辅助\n");
    printf("   • Valgrind检测内存问题\n");
    printf("   • AddressSanitizer（ASan）\n");
    printf("   • 静态分析工具\n\n");
}

int main() {
    printf("╔═══════════════════════════════════════╗\n");
    printf("║   第13章：高级内存管理                ║\n");
    printf("║   13.1 内存分配详解                   ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
    
    example_malloc();
    example_calloc();
    example_realloc();
    example_comparison();
    example_error_handling();
    example_aligned_allocation();
    example_flexible_array();
    example_performance();
    example_common_mistakes();
    example_best_practices();
    
    printf("═════════════════════════════════════════\n");
    printf("内存分配总结：\n");
    printf("═════════════════════════════════════════\n");
    printf("核心函数：\n");
    printf("  malloc(size)          分配size字节\n");
    printf("  calloc(n, size)       分配n个元素并清零\n");
    printf("  realloc(ptr, size)    调整大小\n");
    printf("  free(ptr)             释放内存\n");
    printf("\n");
    printf("关键原则：\n");
    printf("  1. 检查返回值（是否为NULL）\n");
    printf("  2. 配对使用（malloc/free）\n");
    printf("  3. 释放后置NULL\n");
    printf("  4. 不要重复释放\n");
    printf("  5. 不要使用已释放内存\n");
    printf("\n");
    printf("选择指南：\n");
    printf("  • 性能优先 → malloc\n");
    printf("  • 安全优先 → calloc\n");
    printf("  • 动态调整 → realloc\n");
    printf("  • 对齐需求 → aligned_alloc\n");
    printf("═════════════════════════════════════════\n");
    
    return 0;
}

/*
 * 编译和运行：
 *   gcc 13.1_memory_allocation.c -o 13.1
 *   ./13.1
 * 
 * 内存检查工具：
 *   valgrind ./13.1
 *   gcc -fsanitize=address 13.1_memory_allocation.c -o 13.1
 * 
 * 学习要点：
 *   1. 理解malloc/calloc/realloc的区别
 *   2. 掌握错误处理方法
 *   3. 了解内存对齐的重要性
 *   4. 避免常见内存错误
 *   5. 遵循最佳实践
 * 
 * 下一步：
 *   学习13.2 内存泄漏检测与防止
 */
