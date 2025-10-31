/*
 * 第十三章：高级内存管理
 * 13.4 内存对齐与优化
 * 
 * 本文件详细讲解内存对齐的原理、重要性和优化技巧
 * 编译命令：gcc 13.4_memory_alignment.c -o 13.4
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <time.h>

// ==================== 示例1：什么是内存对齐 ====================

void example_alignment_basics() {
    printf("=== 示例1：内存对齐基础 ===\n\n");
    
    printf("什么是内存对齐？\n");
    printf("  数据存储在内存中特定边界的位置\n");
    printf("  例如：4字节数据存储在4的倍数地址\n\n");
    
    printf("为什么需要对齐？\n");
    printf("  1. CPU访问效率\n");
    printf("     • 对齐数据：1次内存访问\n");
    printf("     • 未对齐：可能需要2次访问\n");
    printf("  2. 硬件要求\n");
    printf("     • 某些CPU不支持未对齐访问\n");
    printf("     • SIMD指令（SSE/AVX）要求对齐\n");
    printf("  3. 原子操作\n");
    printf("     • 多线程同步需要对齐\n\n");
    
    printf("对齐规则：\n");
    printf("  char:    1字节对齐\n");
    printf("  short:   2字节对齐\n");
    printf("  int:     4字节对齐\n");
    printf("  long:    4或8字节（平台相关）\n");
    printf("  float:   4字节对齐\n");
    printf("  double:  8字节对齐\n");
    printf("  pointer: 4或8字节（平台相关）\n\n");
}

// ==================== 示例2：查看基本类型对齐 ====================

void example_basic_alignment() {
    printf("=== 示例2：基本类型对齐 ===\n\n");
    
    printf("类型大小和对齐要求：\n\n");
    
    printf("  %-15s size=%2zu  align=%2zu\n", "char", 
           sizeof(char), _Alignof(char));
    printf("  %-15s size=%2zu  align=%2zu\n", "short", 
           sizeof(short), _Alignof(short));
    printf("  %-15s size=%2zu  align=%2zu\n", "int", 
           sizeof(int), _Alignof(int));
    printf("  %-15s size=%2zu  align=%2zu\n", "long", 
           sizeof(long), _Alignof(long));
    printf("  %-15s size=%2zu  align=%2zu\n", "long long", 
           sizeof(long long), _Alignof(long long));
    printf("  %-15s size=%2zu  align=%2zu\n", "float", 
           sizeof(float), _Alignof(float));
    printf("  %-15s size=%2zu  align=%2zu\n", "double", 
           sizeof(double), _Alignof(double));
    printf("  %-15s size=%2zu  align=%2zu\n", "void*", 
           sizeof(void*), _Alignof(void*));
    
    printf("\n_Alignof是C11标准操作符\n");
    printf("返回类型的对齐要求（字节数）\n\n");
}

// ==================== 示例3：结构体对齐 ====================

// 未优化的结构体
struct UnalignedStruct {
    char a;      // 1字节
    int b;       // 4字节
    char c;      // 1字节
    double d;    // 8字节
};

// 优化后的结构体
struct AlignedStruct {
    double d;    // 8字节
    int b;       // 4字节
    char a;      // 1字节
    char c;      // 1字节
    // 2字节填充
};

// 紧凑结构体（不推荐）
struct __attribute__((packed)) PackedStruct {
    char a;
    int b;
    char c;
    double d;
};

void example_struct_alignment() {
    printf("=== 示例3：结构体对齐 ===\n\n");
    
    printf("未优化结构体：\n");
    printf("  struct UnalignedStruct {\n");
    printf("    char a;    // offset 0,  size 1\n");
    printf("    int b;     // offset 4,  size 4 (3字节填充)\n");
    printf("    char c;    // offset 8,  size 1\n");
    printf("    double d;  // offset 16, size 8 (7字节填充)\n");
    printf("  };  // 总大小: 24字节\n");
    printf("  实际大小: %zu 字节\n\n", sizeof(struct UnalignedStruct));
    
    printf("优化后结构体：\n");
    printf("  struct AlignedStruct {\n");
    printf("    double d;  // offset 0, size 8\n");
    printf("    int b;     // offset 8, size 4\n");
    printf("    char a;    // offset 12, size 1\n");
    printf("    char c;    // offset 13, size 1\n");
    printf("  };  // 总大小: 16字节 (2字节尾部填充)\n");
    printf("  实际大小: %zu 字节\n", sizeof(struct AlignedStruct));
    printf("  节省: %zu 字节 (%.1f%%)\n\n",
           sizeof(struct UnalignedStruct) - sizeof(struct AlignedStruct),
           (1.0 - (double)sizeof(struct AlignedStruct) / 
            sizeof(struct UnalignedStruct)) * 100);
    
    printf("紧凑结构体（packed）：\n");
    printf("  实际大小: %zu 字节\n", sizeof(struct PackedStruct));
    printf("  警告: 访问可能变慢！\n\n");
    
    // 显示成员偏移
    printf("UnalignedStruct成员偏移：\n");
    printf("  a: %zu\n", offsetof(struct UnalignedStruct, a));
    printf("  b: %zu\n", offsetof(struct UnalignedStruct, b));
    printf("  c: %zu\n", offsetof(struct UnalignedStruct, c));
    printf("  d: %zu\n", offsetof(struct UnalignedStruct, d));
    
    printf("\nAlignedStruct成员偏移：\n");
    printf("  d: %zu\n", offsetof(struct AlignedStruct, d));
    printf("  b: %zu\n", offsetof(struct AlignedStruct, b));
    printf("  a: %zu\n", offsetof(struct AlignedStruct, a));
    printf("  c: %zu\n", offsetof(struct AlignedStruct, c));
    printf("\n");
}

// ==================== 示例4：手动对齐 ====================

#define ALIGN_UP(x, align) (((x) + (align) - 1) & ~((align) - 1))
#define ALIGN_DOWN(x, align) ((x) & ~((align) - 1))
#define IS_ALIGNED(x, align) (((x) & ((align) - 1)) == 0)

void example_manual_alignment() {
    printf("=== 示例4：手动对齐计算 ===\n\n");
    
    printf("对齐宏定义：\n");
    printf("  ALIGN_UP(x, align)    - 向上对齐\n");
    printf("  ALIGN_DOWN(x, align)  - 向下对齐\n");
    printf("  IS_ALIGNED(x, align)  - 检查是否对齐\n\n");
    
    printf("示例（对齐到8字节）：\n");
    for (uintptr_t addr = 10; addr <= 25; addr += 3) {
        printf("  %2lu → 向上:%2lu 向下:%2lu 已对齐:%s\n",
               addr,
               ALIGN_UP(addr, 8),
               ALIGN_DOWN(addr, 8),
               IS_ALIGNED(addr, 8) ? "是" : "否");
    }
    
    printf("\n原理：\n");
    printf("  向上对齐: (x + align - 1) & ~(align - 1)\n");
    printf("  向下对齐: x & ~(align - 1)\n");
    printf("  检查对齐: (x & (align - 1)) == 0\n");
    printf("  注意: align必须是2的幂！\n\n");
}

// ==================== 示例5：aligned_alloc（C11）====================

void example_aligned_alloc() {
    printf("=== 示例5：aligned_alloc (C11) ===\n\n");
    
    #if __STDC_VERSION__ >= 201112L && !defined(_WIN32)
    // 分配16字节对齐的内存
    void* ptr1 = aligned_alloc(16, 128);
    if (ptr1) {
        printf("16字节对齐分配：\n");
        printf("  地址: %p\n", ptr1);
        printf("  对齐检查: %s\n", 
               IS_ALIGNED((uintptr_t)ptr1, 16) ? "成功" : "失败");
        free(ptr1);
    }
    
    // 分配64字节对齐（缓存行）
    void* ptr2 = aligned_alloc(64, 256);
    if (ptr2) {
        printf("\n64字节对齐分配（缓存行）：\n");
        printf("  地址: %p\n", ptr2);
        printf("  对齐检查: %s\n", 
               IS_ALIGNED((uintptr_t)ptr2, 64) ? "成功" : "失败");
        free(ptr2);
    }
    
    printf("\naligned_alloc要求：\n");
    printf("  • size必须是alignment的倍数\n");
    printf("  • alignment必须是sizeof(void*)的倍数\n");
    printf("  • alignment必须是2的幂\n");
    #else
    printf("aligned_alloc需要C11支持\n");
    printf("替代方案：\n");
    printf("  • POSIX: posix_memalign\n");
    printf("  • Windows: _aligned_malloc\n");
    printf("  • 自定义实现\n");
    #endif
    printf("\n");
}

// ==================== 示例6：缓存行对齐 ====================

#define CACHE_LINE_SIZE 64

// 无填充的结构
struct Counter {
    long value;
};

// 缓存行对齐的结构
struct __attribute__((aligned(CACHE_LINE_SIZE))) AlignedCounter {
    long value;
    char padding[CACHE_LINE_SIZE - sizeof(long)];
};

void example_cache_line() {
    printf("=== 示例6：缓存行对齐 ===\n\n");
    
    printf("什么是缓存行？\n");
    printf("  • CPU缓存的最小单位\n");
    printf("  • 通常64字节（x86/x64）\n");
    printf("  • 加载一个字节会加载整行\n\n");
    
    printf("伪共享问题：\n");
    printf("  • 两个线程访问同一缓存行的不同数据\n");
    printf("  • 导致缓存行频繁失效\n");
    printf("  • 严重影响性能\n\n");
    
    printf("结构体大小对比：\n");
    printf("  Counter:        %zu 字节\n", sizeof(struct Counter));
    printf("  AlignedCounter: %zu 字节\n", sizeof(struct AlignedCounter));
    
    printf("\n数组中的差异：\n");
    struct Counter counters[4];
    struct AlignedCounter aligned_counters[4];
    
    printf("  Counter数组:\n");
    for (int i = 0; i < 4; i++) {
        printf("    [%d]: %p (偏移: %td)\n", 
               i, (void*)&counters[i], 
               (char*)&counters[i] - (char*)&counters[0]);
    }
    
    printf("  AlignedCounter数组:\n");
    for (int i = 0; i < 4; i++) {
        printf("    [%d]: %p (偏移: %td)\n", 
               i, (void*)&aligned_counters[i],
               (char*)&aligned_counters[i] - (char*)&aligned_counters[0]);
    }
    
    printf("\n优势：\n");
    printf("  • 避免伪共享\n");
    printf("  • 多线程性能提升\n");
    printf("  • 减少缓存冲突\n\n");
}

// ==================== 示例7：SIMD对齐 ====================

void example_simd_alignment() {
    printf("=== 示例7：SIMD对齐要求 ===\n\n");
    
    printf("SIMD指令对齐要求：\n");
    printf("  SSE (128位):    16字节对齐\n");
    printf("  AVX (256位):    32字节对齐\n");
    printf("  AVX-512 (512位): 64字节对齐\n\n");
    
    printf("未对齐的后果：\n");
    printf("  • 性能显著下降\n");
    printf("  • 某些指令可能崩溃\n");
    printf("  • 编译器可能生成更慢代码\n\n");
    
    printf("示例：SSE要求的16字节对齐\n");
    
    // 对齐的数组
    float aligned_array[4] __attribute__((aligned(16)));
    for (int i = 0; i < 4; i++) {
        aligned_array[i] = i * 1.5f;
    }
    
    printf("  对齐数组地址: %p\n", (void*)aligned_array);
    printf("  16字节对齐: %s\n", 
           IS_ALIGNED((uintptr_t)aligned_array, 16) ? "是" : "否");
    
    printf("\n编译器指令：\n");
    printf("  GCC/Clang: __attribute__((aligned(N)))\n");
    printf("  MSVC:      __declspec(align(N))\n");
    printf("  C11:       _Alignas(N)\n\n");
}

// ==================== 示例8：性能影响 ====================

#define ARRAY_SIZE 1000000

void performance_test_unaligned() {
    // 故意创建未对齐的访问
    char* buffer = (char*)malloc(ARRAY_SIZE * sizeof(int) + 1);
    int* unaligned = (int*)(buffer + 1);  // 未对齐！
    
    clock_t start = clock();
    long sum = 0;
    for (int iter = 0; iter < 100; iter++) {
        for (int i = 0; i < ARRAY_SIZE; i++) {
            sum += unaligned[i];
        }
    }
    clock_t end = clock();
    
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("  未对齐访问: %.3f 秒\n", time_spent);
    
    free(buffer);
}

void performance_test_aligned() {
    int* aligned = (int*)malloc(ARRAY_SIZE * sizeof(int));
    
    clock_t start = clock();
    long sum = 0;
    for (int iter = 0; iter < 100; iter++) {
        for (int i = 0; i < ARRAY_SIZE; i++) {
            sum += aligned[i];
        }
    }
    clock_t end = clock();
    
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("  对齐访问:   %.3f 秒\n", time_spent);
    
    free(aligned);
}

void example_performance_impact() {
    printf("=== 示例8：性能影响测试 ===\n\n");
    
    printf("测试：%d个整数，100次迭代\n\n", ARRAY_SIZE);
    
    performance_test_aligned();
    performance_test_unaligned();
    
    printf("\n注意：\n");
    printf("  • x86/x64可以处理未对齐访问（但慢）\n");
    printf("  • ARM等平台可能直接崩溃\n");
    printf("  • 性能差异取决于硬件\n\n");
}

// ==================== 示例9：最佳实践 ====================

void example_best_practices() {
    printf("=== 示例9：对齐最佳实践 ===\n\n");
    
    printf("结构体设计：\n");
    printf("  1. 按大小排序成员\n");
    printf("     • 大成员在前（double, long）\n");
    printf("     • 小成员在后（char, short）\n");
    printf("  2. 分组相关成员\n");
    printf("     • 一起访问的放一起\n");
    printf("     • 减少缓存行数量\n");
    printf("  3. 考虑缓存行\n");
    printf("     • 频繁访问的独立缓存行\n");
    printf("     • 避免伪共享\n\n");
    
    printf("动态分配：\n");
    printf("  1. 使用aligned_alloc (C11)\n");
    printf("  2. 检查返回的地址对齐\n");
    printf("  3. SIMD代码强制对齐\n");
    printf("  4. 大块分配考虑页对齐\n\n");
    
    printf("性能关键代码：\n");
    printf("  1. 测量实际影响\n");
    printf("  2. 使用编译器对齐属性\n");
    printf("  3. 检查生成的汇编代码\n");
    printf("  4. 多平台测试\n\n");
    
    printf("避免的陷阱：\n");
    printf("  ✗ 不要过度使用packed\n");
    printf("  ✗ 不要忽视平台差异\n");
    printf("  ✗ 不要假设对齐\n");
    printf("  ✗ 不要盲目优化\n\n");
}

// ==================== 示例10：实用工具函数 ====================

// 打印内存布局
void print_memory_layout(void* ptr, size_t size, const char* name) {
    unsigned char* bytes = (unsigned char*)ptr;
    printf("%s @ %p:\n", name, ptr);
    printf("  ");
    for (size_t i = 0; i < size; i++) {
        printf("%02X ", bytes[i]);
        if ((i + 1) % 16 == 0) printf("\n  ");
    }
    printf("\n");
}

// 检查指针对齐
int check_alignment(void* ptr, size_t alignment) {
    return IS_ALIGNED((uintptr_t)ptr, alignment);
}

void example_utility_functions() {
    printf("=== 示例10：实用工具 ===\n\n");
    
    // 分配测试内存
    int data[] = {0x12345678, 0xABCDEF00, 0x11223344};
    
    printf("内存布局打印：\n");
    print_memory_layout(data, sizeof(data), "data数组");
    
    printf("\n对齐检查：\n");
    void* test_ptr = malloc(100);
    if (test_ptr) {
        printf("  malloc返回: %p\n", test_ptr);
        printf("    4字节对齐: %s\n", 
               check_alignment(test_ptr, 4) ? "是" : "否");
        printf("    8字节对齐: %s\n", 
               check_alignment(test_ptr, 8) ? "是" : "否");
        printf("    16字节对齐: %s\n", 
               check_alignment(test_ptr, 16) ? "是" : "否");
        free(test_ptr);
    }
    
    printf("\n实用宏：\n");
    printf("  • ALIGN_UP/DOWN - 对齐计算\n");
    printf("  • IS_ALIGNED    - 对齐检查\n");
    printf("  • offsetof      - 成员偏移\n");
    printf("  • _Alignof      - 对齐要求\n\n");
}

// ==================== 主函数 ====================

int main() {
    printf("╔═══════════════════════════════════════╗\n");
    printf("║   第13章：高级内存管理                ║\n");
    printf("║   13.4 内存对齐与优化                 ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
    
    example_alignment_basics();
    example_basic_alignment();
    example_struct_alignment();
    example_manual_alignment();
    example_aligned_alloc();
    example_cache_line();
    example_simd_alignment();
    example_performance_impact();
    example_best_practices();
    example_utility_functions();
    
    printf("═════════════════════════════════════════\n");
    printf("内存对齐总结：\n");
    printf("═════════════════════════════════════════\n");
    printf("为什么重要：\n");
    printf("  • CPU访问效率\n");
    printf("  • 硬件要求（SIMD）\n");
    printf("  • 原子操作正确性\n");
    printf("  • 多线程性能（避免伪共享）\n");
    printf("\n");
    printf("关键概念：\n");
    printf("  • 自然对齐 - 大小等于对齐\n");
    printf("  • 结构体填充 - 满足对齐要求\n");
    printf("  • 缓存行 - 64字节\n");
    printf("  • SIMD对齐 - 16/32/64字节\n");
    printf("\n");
    printf("优化技巧：\n");
    printf("  1. 结构体成员按大小排序\n");
    printf("  2. 使用缓存行对齐避免伪共享\n");
    printf("  3. SIMD代码强制对齐\n");
    printf("  4. 使用aligned_alloc\n");
    printf("\n");
    printf("工具：\n");
    printf("  • _Alignof    - 查询对齐\n");
    printf("  • aligned_alloc - 对齐分配\n");
    printf("  • offsetof    - 成员偏移\n");
    printf("  • __attribute__((aligned)) - 强制对齐\n");
    printf("═════════════════════════════════════════\n");
    
    return 0;
}

/*
 * 编译和运行：
 *   gcc -std=c11 13.4_memory_alignment.c -o 13.4
 *   ./13.4
 * 
 * 查看汇编：
 *   gcc -S -O2 13.4_memory_alignment.c
 * 
 * 学习要点：
 *   1. 理解内存对齐的原理和重要性
 *   2. 掌握结构体对齐优化技巧
 *   3. 了解缓存行对齐和伪共享
 *   4. 学习SIMD对齐要求
 *   5. 测量对齐对性能的影响
 * 
 * 实践建议：
 *   • 检查项目中的结构体布局
 *   • 优化热点数据结构
 *   • 多线程代码考虑缓存行对齐
 *   • 使用工具验证对齐
 * 
 * 下一步：
 *   学习13.5 智能指针模拟
 */
