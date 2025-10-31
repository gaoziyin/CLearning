/*
 * 第十章：网络Socket编程
 * 10.3 TCP服务器实现
 * 
 * 本文件包含完整的TCP服务器示例代码
 * 编译命令（Windows）：gcc 10.3_tcp_server.c -o tcp_server -lws2_32
 * 编译命令（Linux）：  gcc 10.3_tcp_server.c -o tcp_server
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 跨平台处理
#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
    typedef int socklen_t;
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <errno.h>
    #include <sys/select.h>
    #define SOCKET int
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define closesocket close
#endif

#define PORT 8888
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 10

// 示例1：最简单的TCP Echo服务器
void example_simple_echo_server() {
    printf("=== 示例1：简单Echo服务器 ===\n");
    printf("功能：接收客户端消息并原样返回\n\n");
    
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("❌ WSAStartup失败\n");
        return;
    }
#endif
    
    // 1. 创建Socket
    SOCKET server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == INVALID_SOCKET) {
        printf("❌ Socket创建失败\n");
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }
    printf("✓ Socket创建成功\n");
    
    // 2. 设置地址重用
    int reuse = 1;
    setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(reuse));
    
    // 3. 绑定地址
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    
    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("❌ 绑定失败（端口%d可能已被占用）\n", PORT);
        closesocket(server_sock);
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }
    printf("✓ 绑定成功，监听端口: %d\n", PORT);
    
    // 4. 监听
    if (listen(server_sock, 5) == SOCKET_ERROR) {
        printf("❌ 监听失败\n");
        closesocket(server_sock);
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }
    printf("✓ 开始监听连接...\n");
    printf("  提示：可用 telnet 127.0.0.1 %d 测试\n", PORT);
    printf("  提示：按Ctrl+C停止服务器\n\n");
    
    // 5. 接受连接并处理
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    
    SOCKET client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_len);
    if (client_sock == INVALID_SOCKET) {
        printf("❌ 接受连接失败\n");
    } else {
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));
        int client_port = ntohs(client_addr.sin_port);
        printf("✓ 客户端连接: %s:%d\n", client_ip, client_port);
        
        // Echo循环
        char buffer[BUFFER_SIZE];
        int bytes_received;
        
        while ((bytes_received = recv(client_sock, buffer, BUFFER_SIZE-1, 0)) > 0) {
            buffer[bytes_received] = '\0';
            printf("  收到: %s", buffer);
            
            // 回显
            send(client_sock, buffer, bytes_received, 0);
        }
        
        if (bytes_received == 0) {
            printf("  客户端关闭连接\n");
        } else {
            printf("  接收错误\n");
        }
        
        closesocket(client_sock);
    }
    
    closesocket(server_sock);
    
#ifdef _WIN32
    WSACleanup();
#endif
    
    printf("\n服务器已关闭\n\n");
}

// 示例2：支持多客户端的服务器（循环接受）
void example_multi_client_server() {
    printf("=== 示例2：多客户端服务器（循环）===\n");
    printf("功能：依次处理每个客户端的连接\n\n");
    
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
    
    SOCKET server_sock = socket(AF_INET, SOCK_STREAM, 0);
    int reuse = 1;
    setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(reuse));
    
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT + 1);
    
    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) != 0) {
        printf("❌ 绑定失败\n");
        closesocket(server_sock);
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }
    
    listen(server_sock, 5);
    printf("✓ 服务器监听在端口 %d\n", PORT + 1);
    printf("  支持多个客户端（依次处理）\n\n");
    
    int client_count = 0;
    
    // 循环接受客户端连接（演示3个客户端）
    for (int i = 0; i < 3; i++) {
        struct sockaddr_in client_addr;
        socklen_t addr_len = sizeof(client_addr);
        
        printf("等待第 %d 个客户端连接...\n", i + 1);
        SOCKET client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_len);
        
        if (client_sock != INVALID_SOCKET) {
            client_count++;
            char client_ip[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));
            printf("✓ 客户端 #%d 连接: %s:%d\n", 
                   client_count, client_ip, ntohs(client_addr.sin_port));
            
            // 处理这个客户端
            char buffer[BUFFER_SIZE];
            const char *welcome = "Welcome to Server!\r\n";
            send(client_sock, welcome, strlen(welcome), 0);
            
            int bytes = recv(client_sock, buffer, BUFFER_SIZE-1, 0);
            if (bytes > 0) {
                buffer[bytes] = '\0';
                printf("  收到消息: %s", buffer);
            }
            
            closesocket(client_sock);
            printf("  客户端 #%d 断开\n\n", client_count);
        }
    }
    
    closesocket(server_sock);
    
#ifdef _WIN32
    WSACleanup();
#endif
    
    printf("服务器已关闭\n\n");
}

// 示例3：使用select实现并发服务器
void example_select_server() {
    printf("=== 示例3：使用select的并发服务器 ===\n");
    printf("功能：同时处理多个客户端连接\n\n");
    
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
    
    // 创建服务器Socket
    SOCKET server_sock = socket(AF_INET, SOCK_STREAM, 0);
    int reuse = 1;
    setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(reuse));
    
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT + 2);
    
    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) != 0) {
        printf("❌ 绑定失败\n");
        closesocket(server_sock);
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }
    
    listen(server_sock, 5);
    printf("✓ select服务器启动，端口: %d\n", PORT + 2);
    printf("  可同时处理多个客户端\n");
    printf("  演示：处理前3个连接后退出\n\n");
    
    // 客户端Socket数组
    SOCKET client_socks[MAX_CLIENTS];
    for (int i = 0; i < MAX_CLIENTS; i++) {
        client_socks[i] = INVALID_SOCKET;
    }
    
    int connection_count = 0;
    
    // 主循环（演示：处理3个连接）
    while (connection_count < 3) {
        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(server_sock, &read_fds);
        
        SOCKET max_fd = server_sock;
        
        // 添加所有客户端Socket到集合
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (client_socks[i] != INVALID_SOCKET) {
                FD_SET(client_socks[i], &read_fds);
                if (client_socks[i] > max_fd) {
                    max_fd = client_socks[i];
                }
            }
        }
        
        // 设置超时（1秒）
        struct timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;
        
        int activity = select(max_fd + 1, &read_fds, NULL, NULL, &timeout);
        
        if (activity < 0) {
            printf("select错误\n");
            break;
        }
        
        if (activity == 0) {
            // 超时
            continue;
        }
        
        // 检查服务器Socket（新连接）
        if (FD_ISSET(server_sock, &read_fds)) {
            struct sockaddr_in client_addr;
            socklen_t addr_len = sizeof(client_addr);
            SOCKET new_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_len);
            
            if (new_sock != INVALID_SOCKET) {
                char client_ip[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));
                printf("✓ 新客户端连接: %s:%d\n", 
                       client_ip, ntohs(client_addr.sin_port));
                
                // 找空位置
                int added = 0;
                for (int i = 0; i < MAX_CLIENTS; i++) {
                    if (client_socks[i] == INVALID_SOCKET) {
                        client_socks[i] = new_sock;
                        printf("  分配槽位: %d\n", i);
                        added = 1;
                        connection_count++;
                        break;
                    }
                }
                
                if (!added) {
                    printf("  服务器已满，拒绝连接\n");
                    closesocket(new_sock);
                }
            }
        }
        
        // 检查客户端Socket（数据接收）
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (client_socks[i] != INVALID_SOCKET && FD_ISSET(client_socks[i], &read_fds)) {
                char buffer[BUFFER_SIZE];
                int bytes = recv(client_socks[i], buffer, BUFFER_SIZE-1, 0);
                
                if (bytes > 0) {
                    buffer[bytes] = '\0';
                    printf("  客户端[%d]: %s", i, buffer);
                    // Echo
                    send(client_socks[i], buffer, bytes, 0);
                } else {
                    printf("  客户端[%d]断开\n", i);
                    closesocket(client_socks[i]);
                    client_socks[i] = INVALID_SOCKET;
                }
            }
        }
    }
    
    // 清理
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client_socks[i] != INVALID_SOCKET) {
            closesocket(client_socks[i]);
        }
    }
    closesocket(server_sock);
    
#ifdef _WIN32
    WSACleanup();
#endif
    
    printf("\nselect服务器已关闭\n\n");
}

// 示例4：HTTP服务器基础（返回简单网页）
void example_http_server() {
    printf("=== 示例4：简单HTTP服务器 ===\n");
    printf("功能：返回HTML页面\n\n");
    
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
    
    SOCKET server_sock = socket(AF_INET, SOCK_STREAM, 0);
    int reuse = 1;
    setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(reuse));
    
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);
    
    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) != 0) {
        printf("❌ 绑定失败（可能8080端口被占用）\n");
        closesocket(server_sock);
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }
    
    listen(server_sock, 5);
    printf("✓ HTTP服务器启动\n");
    printf("  访问: http://127.0.0.1:8080\n");
    printf("  处理1个请求后退出\n\n");
    
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    SOCKET client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_len);
    
    if (client_sock != INVALID_SOCKET) {
        char buffer[BUFFER_SIZE];
        int bytes = recv(client_sock, buffer, BUFFER_SIZE-1, 0);
        
        if (bytes > 0) {
            buffer[bytes] = '\0';
            printf("收到HTTP请求：\n%s\n", buffer);
            
            // HTTP响应
            const char *response = 
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html; charset=utf-8\r\n"
                "Connection: close\r\n"
                "\r\n"
                "<!DOCTYPE html>\n"
                "<html>\n"
                "<head><title>C语言HTTP服务器</title></head>\n"
                "<body>\n"
                "<h1>欢迎访问C语言HTTP服务器！</h1>\n"
                "<p>这是一个用C语言编写的简单HTTP服务器示例。</p>\n"
                "<p>当前时间戳：服务器已响应</p>\n"
                "</body>\n"
                "</html>\n";
            
            send(client_sock, response, strlen(response), 0);
            printf("✓ 已发送HTTP响应\n");
        }
        
        closesocket(client_sock);
    }
    
    closesocket(server_sock);
    
#ifdef _WIN32
    WSACleanup();
#endif
    
    printf("\nHTTP服务器已关闭\n\n");
}

// 示例5：错误处理示例
void example_error_handling() {
    printf("=== 示例5：错误处理 ===\n\n");
    
    printf("常见错误处理模式：\n\n");
    
    printf("1. Socket创建失败：\n");
    printf("   if (sock == INVALID_SOCKET) {\n");
#ifdef _WIN32
    printf("       printf(\"错误代码: %%d\\n\", WSAGetLastError());\n");
#else
    printf("       printf(\"错误: %%s\\n\", strerror(errno));\n");
#endif
    printf("       return;\n");
    printf("   }\n\n");
    
    printf("2. bind失败：\n");
    printf("   原因：\n");
    printf("     • 端口已被占用\n");
    printf("     • 权限不足（<1024端口需要root）\n");
    printf("     • 地址格式错误\n");
    printf("   解决：\n");
    printf("     • 更换端口\n");
    printf("     • 启用SO_REUSEADDR\n");
    printf("     • 使用sudo运行\n\n");
    
    printf("3. accept失败：\n");
    printf("   原因：\n");
    printf("     • 服务器Socket已关闭\n");
    printf("     • 系统资源不足\n");
    printf("   处理：\n");
    printf("     • 检查服务器状态\n");
    printf("     • 重试或退出\n\n");
    
    printf("4. recv返回0：\n");
    printf("   含义：客户端正常关闭连接\n");
    printf("   处理：关闭Socket，清理资源\n\n");
    
    printf("5. recv返回-1：\n");
    printf("   原因：\n");
    printf("     • 连接异常中断\n");
    printf("     • 超时\n");
    printf("     • Socket已关闭\n");
    printf("   处理：记录日志，关闭连接\n\n");
}

// 主菜单
void show_menu() {
    printf("\n");
    printf("╔═══════════════════════════════════════╗\n");
    printf("║   TCP服务器示例菜单                   ║\n");
    printf("╚═══════════════════════════════════════╝\n");
    printf("1. 简单Echo服务器（单客户端）\n");
    printf("2. 多客户端服务器（循环处理）\n");
    printf("3. select并发服务器\n");
    printf("4. 简单HTTP服务器\n");
    printf("5. 错误处理示例\n");
    printf("0. 退出\n");
    printf("───────────────────────────────────────\n");
    printf("选择 (0-5): ");
}

int main() {
    printf("╔═══════════════════════════════════════╗\n");
    printf("║   第10章：网络Socket编程              ║\n");
    printf("║   10.3 TCP服务器实现                  ║\n");
    printf("╚═══════════════════════════════════════╝\n");
    
    int choice;
    
    while (1) {
        show_menu();
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');
        
        printf("\n");
        
        switch (choice) {
            case 1:
                example_simple_echo_server();
                break;
            case 2:
                example_multi_client_server();
                break;
            case 3:
                example_select_server();
                break;
            case 4:
                example_http_server();
                break;
            case 5:
                example_error_handling();
                break;
            case 0:
                printf("退出程序\n");
                return 0;
            default:
                printf("无效选择\n");
        }
    }
    
    return 0;
}

/*
 * 编译和运行：
 *   Windows: gcc 10.3_tcp_server.c -o tcp_server -lws2_32
 *            tcp_server.exe
 * 
 *   Linux:   gcc 10.3_tcp_server.c -o tcp_server
 *            ./tcp_server
 * 
 * 测试方法：
 *   1. 运行服务器程序
 *   2. 使用telnet测试：
 *      telnet 127.0.0.1 8888
 *   3. 使用浏览器测试HTTP服务器：
 *      http://127.0.0.1:8080
 *   4. 使用下一节的客户端程序测试
 * 
 * 学习要点：
 *   1. 掌握TCP服务器的完整实现流程
 *   2. 理解单客户端vs多客户端处理
 *   3. 学习使用select实现并发
 *   4. 了解基本的HTTP协议
 *   5. 掌握错误处理的最佳实践
 * 
 * 下一步：
 *   学习10.4 TCP客户端实现
 */
