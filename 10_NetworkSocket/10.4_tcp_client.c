/*
 * 第十章：网络Socket编程
 * 10.4 TCP客户端实现
 * 
 * 本文件包含完整的TCP客户端示例代码
 * 编译命令（Windows）：gcc 10.4_tcp_client.c -o tcp_client -lws2_32
 * 编译命令（Linux）：  gcc 10.4_tcp_client.c -o tcp_client
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
    #include <netdb.h>
    #define SOCKET int
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define closesocket close
#endif

#define BUFFER_SIZE 1024

// 示例1：最简单的TCP客户端
void example_simple_client() {
    printf("=== 示例1：简单TCP客户端 ===\n");
    printf("连接到Echo服务器并发送消息\n\n");
    
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("❌ WSAStartup失败\n");
        return;
    }
#endif
    
    // 1. 创建Socket
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("❌ Socket创建失败\n");
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }
    printf("✓ Socket创建成功\n");
    
    // 2. 配置服务器地址
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);
    
    // 转换IP地址
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        printf("❌ IP地址格式错误\n");
        closesocket(sock);
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }
    
    printf("目标服务器: 127.0.0.1:8888\n");
    
    // 3. 连接服务器
    printf("正在连接...\n");
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("❌ 连接失败\n");
        printf("  请确保服务器正在运行（运行10.3的示例1）\n");
        closesocket(sock);
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }
    printf("✓ 连接成功！\n\n");
    
    // 4. 发送消息
    const char *message = "Hello, Server!\n";
    printf("发送: %s", message);
    int sent = send(sock, message, strlen(message), 0);
    if (sent > 0) {
        printf("✓ 发送了 %d 字节\n", sent);
    } else {
        printf("❌ 发送失败\n");
    }
    
    // 5. 接收响应
    char buffer[BUFFER_SIZE];
    int received = recv(sock, buffer, BUFFER_SIZE-1, 0);
    if (received > 0) {
        buffer[received] = '\0';
        printf("收到: %s", buffer);
        printf("✓ 接收了 %d 字节\n", received);
    } else if (received == 0) {
        printf("服务器关闭了连接\n");
    } else {
        printf("❌ 接收失败\n");
    }
    
    // 6. 关闭Socket
    closesocket(sock);
    printf("\n连接已关闭\n");
    
#ifdef _WIN32
    WSACleanup();
#endif
    
    printf("\n");
}

// 示例2：交互式客户端
void example_interactive_client() {
    printf("=== 示例2：交互式客户端 ===\n");
    printf("可以多次发送消息\n\n");
    
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
    
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("❌ Socket创建失败\n");
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }
    
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
    
    printf("连接到 127.0.0.1:8888...\n");
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("❌ 连接失败（确保服务器正在运行）\n");
        closesocket(sock);
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }
    printf("✓ 已连接！\n\n");
    printf("输入消息（输入'quit'退出）：\n");
    
    char buffer[BUFFER_SIZE];
    char input[BUFFER_SIZE];
    
    while (1) {
        printf("> ");
        fflush(stdout);
        
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        
        // 检查退出命令
        if (strncmp(input, "quit", 4) == 0) {
            printf("退出...\n");
            break;
        }
        
        // 发送
        int sent = send(sock, input, strlen(input), 0);
        if (sent <= 0) {
            printf("❌ 发送失败\n");
            break;
        }
        
        // 接收回显
        int received = recv(sock, buffer, BUFFER_SIZE-1, 0);
        if (received > 0) {
            buffer[received] = '\0';
            printf("回显: %s", buffer);
        } else if (received == 0) {
            printf("服务器关闭了连接\n");
            break;
        } else {
            printf("❌ 接收失败\n");
            break;
        }
    }
    
    closesocket(sock);
    
#ifdef _WIN32
    WSACleanup();
#endif
    
    printf("\n");
}

// 示例3：域名解析客户端
void example_dns_client() {
    printf("=== 示例3：使用域名连接 ===\n");
    printf("通过域名解析连接服务器\n\n");
    
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
    
    const char *hostname = "www.example.com";
    const char *port = "80";
    
    printf("解析域名: %s\n", hostname);
    
    // 使用getaddrinfo解析域名
    struct addrinfo hints, *result, *rp;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;    // IPv4或IPv6
    hints.ai_socktype = SOCK_STREAM;// TCP
    
    int status = getaddrinfo(hostname, port, &hints, &result);
    if (status != 0) {
        printf("❌ 域名解析失败\n");
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }
    
    printf("✓ 域名解析成功\n");
    
    // 尝试连接
    SOCKET sock = INVALID_SOCKET;
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        // 显示IP地址
        char ipstr[INET6_ADDRSTRLEN];
        if (rp->ai_family == AF_INET) {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)rp->ai_addr;
            inet_ntop(AF_INET, &ipv4->sin_addr, ipstr, sizeof(ipstr));
            printf("  尝试连接 IPv4: %s\n", ipstr);
        } else {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)rp->ai_addr;
            inet_ntop(AF_INET6, &ipv6->sin6_addr, ipstr, sizeof(ipstr));
            printf("  尝试连接 IPv6: %s\n", ipstr);
        }
        
        // 创建Socket
        sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sock == INVALID_SOCKET) {
            continue;
        }
        
        // 连接
        if (connect(sock, rp->ai_addr, rp->ai_addrlen) == 0) {
            printf("✓ 连接成功！\n");
            break;
        }
        
        closesocket(sock);
        sock = INVALID_SOCKET;
    }
    
    freeaddrinfo(result);
    
    if (sock == INVALID_SOCKET) {
        printf("❌ 所有地址都连接失败\n");
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }
    
    // 发送HTTP GET请求
    const char *request = "GET / HTTP/1.1\r\nHost: www.example.com\r\nConnection: close\r\n\r\n";
    printf("\n发送HTTP请求...\n");
    send(sock, request, strlen(request), 0);
    
    // 接收响应（前1000字节）
    char buffer[1024];
    int received = recv(sock, buffer, sizeof(buffer)-1, 0);
    if (received > 0) {
        buffer[received] = '\0';
        printf("\n收到响应（前%d字节）：\n", received);
        printf("─────────────────────────────────────\n");
        printf("%s", buffer);
        printf("─────────────────────────────────────\n");
    }
    
    closesocket(sock);
    
#ifdef _WIN32
    WSACleanup();
#endif
    
    printf("\n");
}

// 示例4：超时设置
void example_timeout_client() {
    printf("=== 示例4：设置超时 ===\n");
    printf("演示接收超时设置\n\n");
    
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
    
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }
    
    // 设置接收超时为3秒
    printf("设置接收超时: 3秒\n");
#ifdef _WIN32
    DWORD timeout = 3000;  // 毫秒
#else
    struct timeval timeout;
    timeout.tv_sec = 3;
    timeout.tv_usec = 0;
#endif
    
    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, 
                   (char*)&timeout, sizeof(timeout)) == 0) {
        printf("✓ 超时设置成功\n");
    } else {
        printf("❌ 超时设置失败\n");
    }
    
    // 设置连接超时（仅Linux，Windows需要异步Socket）
#ifndef _WIN32
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout, sizeof(timeout));
    printf("✓ 连接超时设置为5秒\n");
#endif
    
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
    
    printf("\n连接服务器...\n");
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == 0) {
        printf("✓ 连接成功\n");
        
        printf("\n等待服务器数据（3秒超时）...\n");
        char buffer[BUFFER_SIZE];
        int received = recv(sock, buffer, BUFFER_SIZE-1, 0);
        
        if (received > 0) {
            buffer[received] = '\0';
            printf("收到: %s", buffer);
        } else if (received == 0) {
            printf("连接关闭\n");
        } else {
#ifdef _WIN32
            if (WSAGetLastError() == WSAETIMEDOUT) {
                printf("⏱ 接收超时（3秒内没有数据）\n");
            } else {
                printf("❌ 接收错误\n");
            }
#else
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                printf("⏱ 接收超时（3秒内没有数据）\n");
            } else {
                printf("❌ 接收错误: %s\n", strerror(errno));
            }
#endif
        }
    } else {
        printf("❌ 连接失败\n");
    }
    
    closesocket(sock);
    
#ifdef _WIN32
    WSACleanup();
#endif
    
    printf("\n");
}

// 示例5：发送大数据（确保完整发送）
void example_send_large_data() {
    printf("=== 示例5：发送大数据 ===\n");
    printf("演示如何完整发送大量数据\n\n");
    
    printf("完整发送函数示例：\n");
    printf("  int send_all(SOCKET sock, const char *buf, int len) {\n");
    printf("      int total = 0;\n");
    printf("      int bytes_left = len;\n");
    printf("      int n;\n");
    printf("      \n");
    printf("      while (total < len) {\n");
    printf("          n = send(sock, buf + total, bytes_left, 0);\n");
    printf("          if (n == -1) {\n");
    printf("              return -1;  // 错误\n");
    printf("          }\n");
    printf("          total += n;\n");
    printf("          bytes_left -= n;\n");
    printf("      }\n");
    printf("      \n");
    printf("      return total;  // 成功发送的总字节数\n");
    printf("  }\n");
    
    printf("\n为什么需要循环发送？\n");
    printf("  • send()可能只发送部分数据\n");
    printf("  • 返回值<请求长度是正常的\n");
    printf("  • 必须循环直到全部发送完成\n");
    printf("  • 只有返回-1才是真正的错误\n");
    
    printf("\n接收大数据同理：\n");
    printf("  • recv()可能只接收部分数据\n");
    printf("  • 需要根据协议判断数据是否完整\n");
    printf("  • 常见方法：\n");
    printf("    1. 固定长度\n");
    printf("    2. 特殊结束符（如\\n）\n");
    printf("    3. 消息头包含长度信息\n");
    
    printf("\n");
}

// 示例6：错误处理
void example_client_error_handling() {
    printf("=== 示例6：客户端错误处理 ===\n\n");
    
    printf("常见连接错误：\n\n");
    
    printf("1. ECONNREFUSED（连接被拒绝）\n");
    printf("   原因：服务器未运行或未监听该端口\n");
    printf("   解决：启动服务器，检查端口号\n\n");
    
    printf("2. ETIMEDOUT（连接超时）\n");
    printf("   原因：服务器不可达或防火墙阻止\n");
    printf("   解决：检查网络连接，检查防火墙\n\n");
    
    printf("3. ENETUNREACH（网络不可达）\n");
    printf("   原因：路由问题\n");
    printf("   解决：检查网络配置\n\n");
    
    printf("4. EHOSTUNREACH（主机不可达）\n");
    printf("   原因：目标主机不存在或不可达\n");
    printf("   解决：检查IP地址\n\n");
    
    printf("发送/接收错误：\n\n");
    
    printf("1. recv()返回0\n");
    printf("   含义：对方正常关闭连接\n");
    printf("   处理：关闭Socket\n\n");
    
    printf("2. recv()返回-1\n");
    printf("   原因：连接异常、超时、Socket关闭\n");
    printf("   处理：检查错误码，关闭Socket\n\n");
    
    printf("3. send()返回-1\n");
    printf("   原因：连接已断开、缓冲区满\n");
    printf("   处理：检查连接状态\n\n");
    
    printf("错误检查示例：\n");
#ifdef _WIN32
    printf("  Windows: int err = WSAGetLastError();\n");
    printf("           if (err == WSAECONNREFUSED) {...}\n");
#else
    printf("  Linux:   if (errno == ECONNREFUSED) {...}\n");
    printf("           printf(\"错误: %%s\", strerror(errno));\n");
#endif
    
    printf("\n");
}

// 主菜单
void show_menu() {
    printf("\n");
    printf("╔═══════════════════════════════════════╗\n");
    printf("║   TCP客户端示例菜单                   ║\n");
    printf("╚═══════════════════════════════════════╝\n");
    printf("1. 简单客户端（发送一条消息）\n");
    printf("2. 交互式客户端（多次通信）\n");
    printf("3. 域名解析客户端\n");
    printf("4. 超时设置示例\n");
    printf("5. 发送大数据示例\n");
    printf("6. 错误处理说明\n");
    printf("0. 退出\n");
    printf("───────────────────────────────────────\n");
    printf("选择 (0-6): ");
}

int main() {
    printf("╔═══════════════════════════════════════╗\n");
    printf("║   第10章：网络Socket编程              ║\n");
    printf("║   10.4 TCP客户端实现                  ║\n");
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
                example_simple_client();
                break;
            case 2:
                example_interactive_client();
                break;
            case 3:
                example_dns_client();
                break;
            case 4:
                example_timeout_client();
                break;
            case 5:
                example_send_large_data();
                break;
            case 6:
                example_client_error_handling();
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
 *   Windows: gcc 10.4_tcp_client.c -o tcp_client -lws2_32
 *            tcp_client.exe
 * 
 *   Linux:   gcc 10.4_tcp_client.c -o tcp_client
 *            ./tcp_client
 * 
 * 测试方法：
 *   1. 先运行10.3的服务器程序
 *   2. 再运行本客户端程序
 *   3. 选择不同的示例测试
 * 
 * 学习要点：
 *   1. 掌握TCP客户端的基本流程
 *   2. 理解connect()的使用
 *   3. 学习域名解析（getaddrinfo）
 *   4. 掌握超时设置
 *   5. 理解完整发送/接收的重要性
 *   6. 熟悉常见错误及处理方法
 * 
 * 下一步：
 *   学习10.5 UDP编程
 */
