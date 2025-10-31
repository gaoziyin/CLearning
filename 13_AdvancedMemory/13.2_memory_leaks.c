/*
 * 第十三章：高级内存管理
 * 13.2 内存泄漏检测与防止
 * 
 * 本文件详细讲解内存泄漏的原因、检测方法和防止策略
 * 编译命令：
 *   基本: gcc 13.2_memory_leaks.c -o 13.2
 *   调试: gcc -g 13.2_memory_leaks.c -o 13.2
 *   ASan: gcc -fsanitize=address -g 13.2_memory_leaks.c -o 13.2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==================== 示例1：什么是内存泄漏 ====================
void leak_example_basic() {
    printf("=== 示例1：内存泄漏基础 ===\n\n");
    
    printf("内存泄漏定义：\n");
    printf("  程序分配的内存无法被访问和释放\n\n");
    
    printf("示例代码：\n");
    printf("  void leak_function() {\n");
    printf("    int* ptr = malloc(100);\n");
    printf("    // 忘记free(ptr);\n");
    printf("    return;  // ptr丢失，内存泄漏！\n");
    printf("  }\n\n");
    
    printf("后果：\n");
    printf("  ✗ 可用内存逐渐减少\n");
    printf("  ✗ 程序变慢\n");
    printf("  ✗ 最终内存耗尽\n");
    printf("  ✗ 系统不稳定\n\n");
}

// ==================== 示例2：常见泄漏场景 ====================

// 场景1：简单遗忘
void leak_scenario_1() {
    printf("场景1：简单遗忘\n");
    int* data = (int*)malloc(sizeof(int) * 100);
    // 忘记free(data);  <- 泄漏！
    printf("  ✗ 分配后未释放\n");
}

// 场景2：早期返回
int leak_scenario_2(int condition) {
    printf("场景2：早期返回\n");
    char* buffer = (char*)malloc(1024);
    
    if (condition) {
        // 忘记free(buffer);  <- 泄漏！
        printf("  ✗ 提前返回，未释放\n");
        return -1;
    }
    
    free(buffer);
    return 0;
}

// 场景3：异常分支
void leak_scenario_3(const char* filename) {
    printf("场景3：异常分支\n");
    FILE* file = fopen(filename, "r");
    char* data = (char*)malloc(1024);
    
    if (file == NULL) {
        // 忘记free(data);  <- 泄漏！
        printf("  ✗ 错误处理不完整\n");
        return;
    }
    
    fclose(file);
    free(data);
}

// 场景4：重新赋值
void leak_scenario_4() {
    printf("场景4：重新赋值\n");
    int* ptr = (int*)malloc(100);
    ptr = (int*)malloc(200);  // 前一个malloc泄漏！
    printf("  ✗ 指针覆盖，原内存无法访问\n");
    free(ptr);  // 只释放了第二个
}

void example_common_leaks() {
    printf("=== 示例2：常见泄漏场景 ===\n\n");
    
    leak_scenario_1();
    leak_scenario_2(1);
    leak_scenario_3("nonexistent.txt");
    leak_scenario_4();
    
    printf("\n预防措施：\n");
    printf("  • 每个malloc对应一个free\n");
    printf("  • 使用goto统一清理\n");
    printf("  • 错误处理要完整\n");
    printf("  • 重新赋值前先释放\n\n");
}

// ==================== 示例3：正确的错误处理 ====================

// 错误示范
int wrong_error_handling(const char* filename) {
    FILE* file = fopen(filename, "r");
    char* buffer1 = (char*)malloc(1024);
    char* buffer2 = (char*)malloc(2048);
    
    if (file == NULL) return -1;  // 泄漏buffer1和buffer2
    if (buffer1 == NULL) {
        fclose(file);
        return -1;  // 泄漏buffer2
    }
    if (buffer2 == NULL) {
        free(buffer1);
        fclose(file);
        return -1;  // 正确
    }
    
    // 正常处理...
    
    free(buffer1);
    free(buffer2);
    fclose(file);
    return 0;
}

// 正确示范：使用goto清理
int correct_error_handling(const char* filename) {
    FILE* file = NULL;
    char* buffer1 = NULL;
    char* buffer2 = NULL;
    int result = 0;
    
    file = fopen(filename, "r");
    if (file == NULL) {
        result = -1;
        goto cleanup;
    }
    
    buffer1 = (char*)malloc(1024);
    if (buffer1 == NULL) {
        result = -1;
        goto cleanup;
    }
    
    buffer2 = (char*)malloc(2048);
    if (buffer2 == NULL) {
        result = -1;
        goto cleanup;
    }
    
    // 正常处理...
    
cleanup:
    if (buffer2) free(buffer2);
    if (buffer1) free(buffer1);
    if (file) fclose(file);
    return result;
}

void example_proper_cleanup() {
    printf("=== 示例3：正确的错误处理 ===\n\n");
    
    printf("错误的清理方式：\n");
    printf("  if (error1) return -1;  // 泄漏\n");
    printf("  if (error2) {\n");
    printf("    free(res1);\n");
    printf("    return -1;  // 泄漏res2\n");
    printf("  }\n");
    
    printf("\n正确的清理方式（使用goto）：\n");
    printf("  FILE* file = NULL;\n");
    printf("  char* buf1 = NULL;\n");
    printf("  char* buf2 = NULL;\n");
    printf("  \n");
    printf("  buf1 = malloc(size1);\n");
    printf("  if (!buf1) goto cleanup;\n");
    printf("  \n");
    printf("  buf2 = malloc(size2);\n");
    printf("  if (!buf2) goto cleanup;\n");
    printf("  \n");
    printf("  // 处理...\n");
    printf("  \n");
    printf("cleanup:\n");
    printf("  if (buf2) free(buf2);\n");
    printf("  if (buf1) free(buf1);\n");
    printf("  if (file) fclose(file);\n");
    
    printf("\n优点：\n");
    printf("  ✓ 单一退出点\n");
    printf("  ✓ 统一清理逻辑\n");
    printf("  ✓ 不易遗漏\n");
    printf("  ✓ 易于维护\n\n");
}

// ==================== 示例4：自定义内存跟踪器 ====================

#define MAX_ALLOCATIONS 1000

typedef struct {
    void* ptr;
    size_t size;
    const char* file;
    int line;
    int active;
} AllocationInfo;

static AllocationInfo allocations[MAX_ALLOCATIONS];
static int allocation_count = 0;
static size_t total_allocated = 0;

void* tracked_malloc(size_t size, const char* file, int line) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        return NULL;
    }
    
    // 记录分配信息
    for (int i = 0; i < MAX_ALLOCATIONS; i++) {
        if (!allocations[i].active) {
            allocations[i].ptr = ptr;
            allocations[i].size = size;
            allocations[i].file = file;
            allocations[i].line = line;
            allocations[i].active = 1;
            allocation_count++;
            total_allocated += size;
            break;
        }
    }
    
    return ptr;
}

void tracked_free(void* ptr) {
    if (ptr == NULL) return;
    
    // 查找并标记为已释放
    for (int i = 0; i < MAX_ALLOCATIONS; i++) {
        if (allocations[i].active && allocations[i].ptr == ptr) {
            allocations[i].active = 0;
            allocation_count--;
            total_allocated -= allocations[i].size;
            free(ptr);
            return;
        }
    }
    
    // 未找到记录，可能是未跟踪的分配
    free(ptr);
}

void print_memory_report() {
    printf("\n=== 内存泄漏报告 ===\n");
    printf("活动分配数: %d\n", allocation_count);
    printf("总分配内存: %zu 字节\n\n", total_allocated);
    
    if (allocation_count > 0) {
        printf("未释放的内存：\n");
        for (int i = 0; i < MAX_ALLOCATIONS; i++) {
            if (allocations[i].active) {
                printf("  %zu 字节 @ %p - %s:%d\n",
                       allocations[i].size,
                       allocations[i].ptr,
                       allocations[i].file,
                       allocations[i].line);
            }
        }
    } else {
        printf("✓ 没有内存泄漏！\n");
    }
}

#define MALLOC(size) tracked_malloc(size, __FILE__, __LINE__)
#define FREE(ptr) tracked_free(ptr)

void example_memory_tracker() {
    printf("=== 示例4：内存跟踪器 ===\n\n");
    
    printf("使用自定义跟踪器：\n");
    int* arr1 = (int*)MALLOC(sizeof(int) * 10);
    int* arr2 = (int*)MALLOC(sizeof(int) * 20);
    char* str = (char*)MALLOC(100);
    
    printf("  分配了3块内存\n");
    
    FREE(arr1);
    printf("  释放了1块内存\n");
    
    print_memory_report();
    
    // 清理剩余内存
    FREE(arr2);
    FREE(str);
    
    printf("\n实现原理：\n");
    printf("  • 维护分配记录表\n");
    printf("  • 记录文件名和行号\n");
    printf("  • 追踪活动分配\n");
    printf("  • 生成泄漏报告\n\n");
}

// ==================== 示例5：使用Valgrind ====================

void example_valgrind() {
    printf("=== 示例5：Valgrind工具 ===\n\n");
    
    printf("Valgrind是什么？\n");
    printf("  • Linux下的内存调试工具\n");
    printf("  • 检测内存泄漏\n");
    printf("  • 检测非法内存访问\n");
    printf("  • 检测未初始化内存使用\n");
    
    printf("\n基本使用：\n");
    printf("  # 编译（带调试信息）\n");
    printf("  gcc -g -O0 program.c -o program\n");
    printf("  \n");
    printf("  # 运行Valgrind\n");
    printf("  valgrind --leak-check=full ./program\n");
    printf("  valgrind --leak-check=full --show-leak-kinds=all ./program\n");
    
    printf("\n输出解读：\n");
    printf("  definitely lost: 确定泄漏\n");
    printf("  indirectly lost: 间接泄漏\n");
    printf("  possibly lost:   可能泄漏\n");
    printf("  still reachable: 仍可达（程序结束时未释放）\n");
    
    printf("\n示例报告：\n");
    printf("  ==12345== HEAP SUMMARY:\n");
    printf("  ==12345==     in use at exit: 100 bytes in 1 blocks\n");
    printf("  ==12345==   total heap usage: 1 allocs, 0 frees, 100 bytes\n");
    printf("  ==12345==\n");
    printf("  ==12345== 100 bytes in 1 blocks are definitely lost\n");
    printf("  ==12345==    at 0x4C2FB0F: malloc (in /usr/lib/valgrind/...)\n");
    printf("  ==12345==    by 0x108667: main (program.c:10)\n\n");
}

// ==================== 示例6：AddressSanitizer ====================

void example_asan() {
    printf("=== 示例6：AddressSanitizer ===\n\n");
    
    printf("AddressSanitizer (ASan):\n");
    printf("  • Google开发的内存错误检测器\n");
    printf("  • 编译时插桩\n");
    printf("  • 运行时检测\n");
    printf("  • GCC和Clang内置\n");
    
    printf("\n编译启用：\n");
    printf("  gcc -fsanitize=address -g -O1 program.c -o program\n");
    printf("  clang -fsanitize=address -g -O1 program.c -o program\n");
    
    printf("\n检测功能：\n");
    printf("  ✓ 内存泄漏\n");
    printf("  ✓ 堆缓冲区溢出\n");
    printf("  ✓ 栈缓冲区溢出\n");
    printf("  ✓ 使用已释放内存\n");
    printf("  ✓ 重复释放\n");
    printf("  ✓ 返回栈地址\n");
    
    printf("\n环境变量：\n");
    printf("  export ASAN_OPTIONS=detect_leaks=1\n");
    printf("  export ASAN_OPTIONS=symbolize=1:detect_leaks=1\n");
    
    printf("\n优点：\n");
    printf("  • 快速（2-3倍慢）\n");
    printf("  • 准确\n");
    printf("  • 易于集成\n");
    printf("  • 详细报告\n\n");
}

// ==================== 示例7：防止泄漏的设计模式 ====================

// 模式1：RAII风格（资源获取即初始化）
typedef struct {
    void* data;
} Resource;

Resource* resource_create(size_t size) {
    Resource* res = (Resource*)malloc(sizeof(Resource));
    if (res) {
        res->data = malloc(size);
        if (!res->data) {
            free(res);
            return NULL;
        }
    }
    return res;
}

void resource_destroy(Resource* res) {
    if (res) {
        if (res->data) free(res->data);
        free(res);
    }
}

// 模式2：智能指针风格
typedef struct {
    void* ptr;
    void (*deleter)(void*);
} SmartPtr;

SmartPtr* smart_ptr_create(void* ptr, void (*deleter)(void*)) {
    SmartPtr* sp = (SmartPtr*)malloc(sizeof(SmartPtr));
    if (sp) {
        sp->ptr = ptr;
        sp->deleter = deleter;
    }
    return sp;
}

void smart_ptr_destroy(SmartPtr* sp) {
    if (sp) {
        if (sp->ptr && sp->deleter) {
            sp->deleter(sp->ptr);
        }
        free(sp);
    }
}

void example_design_patterns() {
    printf("=== 示例7：防泄漏设计模式 ===\n\n");
    
    printf("模式1：资源封装\n");
    printf("  • 将内存封装在结构体中\n");
    printf("  • 提供create/destroy函数\n");
    printf("  • destroy负责所有清理\n");
    printf("  \n");
    printf("  Resource* res = resource_create(size);\n");
    printf("  // 使用资源...\n");
    printf("  resource_destroy(res);  // 一次性清理\n");
    
    printf("\n模式2：智能指针\n");
    printf("  • 封装指针和删除器\n");
    printf("  • 自动管理生命周期\n");
    printf("  • 类似C++的unique_ptr\n");
    
    printf("\n模式3：引用计数\n");
    printf("  • 跟踪引用数量\n");
    printf("  • 引用归零时释放\n");
    printf("  • 适合共享资源\n");
    
    printf("\n模式4：内存池\n");
    printf("  • 预分配大块内存\n");
    printf("  • 统一释放\n");
    printf("  • 避免碎片和泄漏\n\n");
}

// ==================== 示例8：静态分析工具 ====================

void example_static_analysis() {
    printf("=== 示例8：静态分析工具 ===\n\n");
    
    printf("1. Clang Static Analyzer\n");
    printf("   编译: scan-build gcc program.c\n");
    printf("   查看: scan-view /tmp/scan-build-xxxx\n");
    
    printf("\n2. Cppcheck\n");
    printf("   安装: sudo apt install cppcheck\n");
    printf("   运行: cppcheck --enable=all program.c\n");
    
    printf("\n3. Splint\n");
    printf("   运行: splint program.c\n");
    printf("   特点: 严格的语义检查\n");
    
    printf("\n4. 编译器警告\n");
    printf("   gcc -Wall -Wextra -Wpedantic program.c\n");
    printf("   始终开启所有警告！\n");
    
    printf("\n优势：\n");
    printf("  • 编译时发现问题\n");
    printf("  • 无运行时开销\n");
    printf("  • 全面覆盖\n");
    printf("  • 可集成到CI/CD\n\n");
}

// ==================== 示例9：最佳实践清单 ====================

void example_best_practices() {
    printf("=== 示例9：最佳实践 ===\n\n");
    
    printf("编码规范：\n");
    printf("  ✓ 初始化指针为NULL\n");
    printf("  ✓ 释放后设置为NULL\n");
    printf("  ✓ 检查malloc返回值\n");
    printf("  ✓ 使用sizeof(变量)而非sizeof(类型)\n");
    printf("  ✓ 避免全局变量持有动态内存\n");
    
    printf("\n错误处理：\n");
    printf("  ✓ 使用goto统一清理\n");
    printf("  ✓ 清理要完整\n");
    printf("  ✓ 考虑所有分支\n");
    printf("  ✓ 测试错误路径\n");
    
    printf("\n开发流程：\n");
    printf("  ✓ 使用ASan开发\n");
    printf("  ✓ 定期Valgrind检查\n");
    printf("  ✓ 静态分析扫描\n");
    printf("  ✓ 代码审查关注内存\n");
    
    printf("\n设计原则：\n");
    printf("  ✓ 明确所有权\n");
    printf("  ✓ 封装资源管理\n");
    printf("  ✓ 使用智能指针模式\n");
    printf("  ✓ 避免复杂生命周期\n");
    
    printf("\n文档要求：\n");
    printf("  ✓ 注释谁负责释放\n");
    printf("  ✓ 标注资源获取点\n");
    printf("  ✓ 说明生命周期\n\n");
}

// ==================== 示例10：实战练习 ====================

void example_practice() {
    printf("=== 示例10：实战练习 ===\n\n");
    
    printf("练习1：找出泄漏\n");
    printf("  void func() {\n");
    printf("    char* p1 = malloc(100);\n");
    printf("    char* p2 = malloc(200);\n");
    printf("    if (condition) return;  // 泄漏！\n");
    printf("    free(p1);\n");
    printf("    free(p2);\n");
    printf("  }\n");
    
    printf("\n练习2：修复泄漏\n");
    printf("  • 使用goto cleanup模式\n");
    printf("  • 确保所有路径清理\n");
    printf("  • 用Valgrind验证\n");
    
    printf("\n练习3：实现内存池\n");
    printf("  • 预分配固定大小块\n");
    printf("  • 实现分配/回收\n");
    printf("  • 统一释放所有内存\n");
    
    printf("\n练习4：智能指针\n");
    printf("  • 实现引用计数\n");
    printf("  • 自动释放\n");
    printf("  • 处理循环引用\n\n");
}

int main() {
    printf("╔═══════════════════════════════════════╗\n");
    printf("║   第13章：高级内存管理                ║\n");
    printf("║   13.2 内存泄漏检测与防止             ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
    
    leak_example_basic();
    example_common_leaks();
    example_proper_cleanup();
    example_memory_tracker();
    example_valgrind();
    example_asan();
    example_design_patterns();
    example_static_analysis();
    example_best_practices();
    example_practice();
    
    printf("═════════════════════════════════════════\n");
    printf("内存泄漏防止总结：\n");
    printf("═════════════════════════════════════════\n");
    printf("检测工具：\n");
    printf("  • Valgrind          最全面\n");
    printf("  • AddressSanitizer  最快速\n");
    printf("  • 自定义跟踪器      可定制\n");
    printf("  • 静态分析          编译时\n");
    printf("\n");
    printf("预防策略：\n");
    printf("  1. goto cleanup模式\n");
    printf("  2. 资源封装\n");
    printf("  3. 智能指针\n");
    printf("  4. 引用计数\n");
    printf("  5. 内存池\n");
    printf("\n");
    printf("关键原则：\n");
    printf("  • 每个malloc对应一个free\n");
    printf("  • 统一清理逻辑\n");
    printf("  • 释放后置NULL\n");
    printf("  • 使用工具验证\n");
    printf("═════════════════════════════════════════\n");
    
    return 0;
}

/*
 * 编译和运行：
 *   基本编译:
 *     gcc 13.2_memory_leaks.c -o 13.2
 *   
 *   使用AddressSanitizer:
 *     gcc -fsanitize=address -g -O1 13.2_memory_leaks.c -o 13.2
 *     ./13.2
 *   
 *   使用Valgrind (Linux):
 *     gcc -g -O0 13.2_memory_leaks.c -o 13.2
 *     valgrind --leak-check=full ./13.2
 *     valgrind --leak-check=full --show-leak-kinds=all ./13.2
 * 
 * 学习要点：
 *   1. 理解内存泄漏的原因
 *   2. 掌握检测工具的使用
 *   3. 学习防泄漏设计模式
 *   4. 养成良好编码习惯
 *   5. 建立完整的测试流程
 * 
 * 实践建议：
 *   • 所有代码用ASan编译测试
 *   • 定期用Valgrind扫描
 *   • 实现自己的内存跟踪器
 *   • 练习goto cleanup模式
 * 
 * 下一步：
 *   学习13.3 自定义内存池
 */
