/*
 * 第十章：网络Socket编程
 * 10.5 UDP编程
 * 
 * 本文件包含UDP服务器和客户端示例
 * 编译命令（Windows）：gcc 10.5_udp_programming.c -o udp_demo -lws2_32
 * 编译命令（Linux）：  gcc 10.5_udp_programming.c -o udp_demo
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
    #define SOCKET int
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define closesocket close
#endif

#define UDP_PORT 9999
#define BUFFER_SIZE 1024

// 示例1：UDP vs TCP对比
void example_udp_vs_tcp() {
    printf("=== 示例1：UDP vs TCP 对比 ===\n\n");
    
    printf("┌──────────────┬─────────────────────┬─────────────────────┐\n");
    printf("│   特性       │        TCP          │        UDP          │\n");
    printf("├──────────────┼─────────────────────┼─────────────────────┤\n");
    printf("│ 连接         │ 需要建立连接        │ 无连接              │\n");
    printf("│ 可靠性       │ 可靠（保证送达）    │ 不保证送达          │\n");
    printf("│ 顺序         │ 保证顺序            │ 不保证顺序          │\n");
    printf("│ 速度         │ 慢（有开销）        │ 快（开销小）        │\n");
    printf("│ 流控制       │ 有                  │ 无                  │\n");
    printf("│ 广播/组播    │ 不支持              │ 支持                │\n");
    printf("│ 消息边界     │ 流式（无边界）      │ 保持消息边界        │\n");
    printf("└──────────────┴─────────────────────┴─────────────────────┘\n");
    
    printf("\nUDP适用场景：\n");
    printf("  ✓ 视频/音频实时传输\n");
    printf("  ✓ 在线游戏（位置同步）\n");
    printf("  ✓ DNS查询\n");
    printf("  ✓ 广播/组播消息\n");
    printf("  ✓ 对实时性要求高，可容忍少量丢包\n");
    
    printf("\nTCP适用场景：\n");
    printf("  ✓ 文件传输\n");
    printf("  ✓ 网页浏览（HTTP/HTTPS）\n");
    printf("  ✓ 电子邮件\n");
    printf("  ✓ 需要可靠传输的应用\n");
    
    printf("\n");
}

// 示例2：简单的UDP服务器
void example_udp_server() {
    printf("=== 示例2：UDP Echo服务器 ===\n");
    printf("接收消息并原样返回\n\n");
    
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("❌ WSAStartup失败\n");
        return;
    }
#endif
    
    // 1. 创建UDP Socket
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("❌ Socket创建失败\n");
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }
    printf("✓ UDP Socket创建成功\n");
    
    // 2. 绑定地址（UDP服务器需要bind）
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(UDP_PORT);
    
    if (bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("❌ 绑定失败（端口%d可能已被占用）\n", UDP_PORT);
        closesocket(sock);
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }
    printf("✓ 绑定成功，监听端口: %d\n", UDP_PORT);
    printf("  注意：UDP不需要listen()和accept()\n\n");
    
    printf("服务器运行中，等待消息...\n");
    printf("  可用UDP客户端测试（示例3）\n");
    printf("  演示：接收3条消息后退出\n\n");
    
    char buffer[BUFFER_SIZE];
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    
    // 3. 接收并回显消息（演示3次）
    for (int i = 0; i < 3; i++) {
        int received = recvfrom(sock, buffer, BUFFER_SIZE-1, 0,
                               (struct sockaddr*)&client_addr, &addr_len);
        
        if (received > 0) {
            buffer[received] = '\0';
            
            // 获取客户端信息
            char client_ip[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));
            int client_port = ntohs(client_addr.sin_port);
            
            printf("✓ 收到来自 %s:%d 的消息：%s", client_ip, client_port, buffer);
            
            // 回显给客户端
            int sent = sendto(sock, buffer, received, 0,
                            (struct sockaddr*)&client_addr, addr_len);
            if (sent > 0) {
                printf("  已回显 %d 字节\n", sent);
            }
        } else {
            printf("❌ 接收错误\n");
            break;
        }
    }
    
    closesocket(sock);
    printf("\nUDP服务器已关闭\n");
    
#ifdef _WIN32
    WSACleanup();
#endif
    
    printf("\n");
}

// 示例3：简单的UDP客户端
void example_udp_client() {
    printf("=== 示例3：UDP客户端 ===\n");
    printf("向服务器发送消息\n\n");
    
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
    
    // 1. 创建UDP Socket
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("❌ Socket创建失败\n");
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }
    printf("✓ UDP Socket创建成功\n");
    printf("  注意：UDP客户端通常不需要bind\n");
    printf("        系统会自动分配端口\n\n");
    
    // 2. 配置服务器地址
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(UDP_PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
    
    printf("目标服务器: 127.0.0.1:%d\n", UDP_PORT);
    printf("  注意：UDP不需要connect（除非想设置默认目标）\n\n");
    
    // 3. 发送消息
    const char *message = "Hello from UDP client!\n";
    printf("发送: %s", message);
    
    int sent = sendto(sock, message, strlen(message), 0,
                     (struct sockaddr*)&server_addr, sizeof(server_addr));
    
    if (sent > 0) {
        printf("✓ 发送了 %d 字节\n", sent);
    } else {
        printf("❌ 发送失败\n");
        closesocket(sock);
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }
    
    // 4. 接收回显
    char buffer[BUFFER_SIZE];
    struct sockaddr_in from_addr;
    socklen_t addr_len = sizeof(from_addr);
    
    // 设置接收超时
#ifdef _WIN32
    DWORD timeout = 5000;  // 5秒
#else
    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
#endif
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
    
    printf("\n等待回复（5秒超时）...\n");
    int received = recvfrom(sock, buffer, BUFFER_SIZE-1, 0,
                           (struct sockaddr*)&from_addr, &addr_len);
    
    if (received > 0) {
        buffer[received] = '\0';
        char from_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &from_addr.sin_addr, from_ip, sizeof(from_ip));
        printf("✓ 收到来自 %s:%d 的回复：%s", 
               from_ip, ntohs(from_addr.sin_port), buffer);
    } else if (received == 0) {
        printf("对方关闭了连接（UDP不应出现此情况）\n");
    } else {
#ifdef _WIN32
        if (WSAGetLastError() == WSAETIMEDOUT) {
            printf("⏱ 接收超时（确保服务器正在运行）\n");
        } else {
            printf("❌ 接收错误，代码: %d\n", WSAGetLastError());
        }
#else
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            printf("⏱ 接收超时（确保服务器正在运行）\n");
        } else {
            printf("❌ 接收错误: %s\n", strerror(errno));
        }
#endif
    }
    
    closesocket(sock);
    
#ifdef _WIN32
    WSACleanup();
#endif
    
    printf("\n");
}

// 示例4：UDP广播
void example_udp_broadcast() {
    printf("=== 示例4：UDP广播 ===\n");
    printf("向局域网内所有主机发送广播消息\n\n");
    
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
    
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("❌ Socket创建失败\n");
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }
    
    // 启用广播权限
    int broadcast = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, 
                   (char*)&broadcast, sizeof(broadcast)) == 0) {
        printf("✓ 广播权限已启用\n");
    } else {
        printf("❌ 启用广播失败\n");
        closesocket(sock);
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }
    
    // 广播地址
    struct sockaddr_in broadcast_addr;
    memset(&broadcast_addr, 0, sizeof(broadcast_addr));
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_port = htons(9998);
    broadcast_addr.sin_addr.s_addr = inet_addr("255.255.255.255");
    
    printf("广播地址: 255.255.255.255:9998\n");
    printf("  255.255.255.255 是有限广播地址\n");
    printf("  也可以使用定向广播（如192.168.1.255）\n\n");
    
    // 发送广播消息
    const char *message = "UDP Broadcast Message!";
    printf("发送广播: %s\n", message);
    
    int sent = sendto(sock, message, strlen(message), 0,
                     (struct sockaddr*)&broadcast_addr, sizeof(broadcast_addr));
    
    if (sent > 0) {
        printf("✓ 广播发送成功（%d 字节）\n", sent);
        printf("  局域网内所有监听9998端口的程序都会收到\n");
    } else {
        printf("❌ 广播发送失败\n");
    }
    
    closesocket(sock);
    
#ifdef _WIN32
    WSACleanup();
#endif
    
    printf("\n广播注意事项：\n");
    printf("  • 需要启用SO_BROADCAST选项\n");
    printf("  • 只能在局域网内使用\n");
    printf("  • 路由器通常会阻止广播\n");
    printf("  • 慎用，避免网络拥塞\n");
    
    printf("\n");
}

// 示例5：UDP组播（多播）
void example_udp_multicast() {
    printf("=== 示例5：UDP组播（多播）===\n");
    printf("发送到特定组播组的消息\n\n");
    
    printf("组播概念：\n");
    printf("  • 组播地址：224.0.0.0 - 239.255.255.255\n");
    printf("  • 一对多通信（订阅者才能收到）\n");
    printf("  • 比广播更高效、更可控\n");
    printf("  • 常用于视频会议、IPTV等\n\n");
    
    printf("组播发送端代码示例：\n");
    printf("  SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);\n");
    printf("  \n");
    printf("  struct sockaddr_in multicast_addr;\n");
    printf("  multicast_addr.sin_family = AF_INET;\n");
    printf("  multicast_addr.sin_port = htons(9997);\n");
    printf("  multicast_addr.sin_addr.s_addr = inet_addr(\"224.0.0.1\");\n");
    printf("  \n");
    printf("  // 发送到组播组\n");
    printf("  sendto(sock, data, len, 0,\n");
    printf("         (struct sockaddr*)&multicast_addr, sizeof(multicast_addr));\n");
    
    printf("\n组播接收端代码示例：\n");
    printf("  SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);\n");
    printf("  \n");
    printf("  // 绑定到任意地址+组播端口\n");
    printf("  struct sockaddr_in local_addr;\n");
    printf("  local_addr.sin_family = AF_INET;\n");
    printf("  local_addr.sin_port = htons(9997);\n");
    printf("  local_addr.sin_addr.s_addr = INADDR_ANY;\n");
    printf("  bind(sock, (struct sockaddr*)&local_addr, sizeof(local_addr));\n");
    printf("  \n");
    printf("  // 加入组播组\n");
    printf("  struct ip_mreq mreq;\n");
    printf("  mreq.imr_multiaddr.s_addr = inet_addr(\"224.0.0.1\");\n");
    printf("  mreq.imr_interface.s_addr = INADDR_ANY;\n");
    printf("  setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP,\n");
    printf("             (char*)&mreq, sizeof(mreq));\n");
    printf("  \n");
    printf("  // 接收组播消息\n");
    printf("  recvfrom(sock, buffer, size, 0, NULL, NULL);\n");
    
    printf("\n常用组播地址：\n");
    printf("  224.0.0.1   - 所有主机\n");
    printf("  224.0.0.2   - 所有路由器\n");
    printf("  224.0.0.251 - mDNS\n");
    printf("  239.x.x.x   - 本地组播（不经过路由器）\n");
    
    printf("\n");
}

// 示例6：UDP connect()用法
void example_udp_connect() {
    printf("=== 示例6：UDP的connect()用法 ===\n\n");
    
    printf("UDP可以调用connect()吗？可以！\n");
    printf("但含义与TCP不同：\n\n");
    
    printf("TCP的connect()：\n");
    printf("  • 建立连接（三次握手）\n");
    printf("  • 必须成功才能通信\n\n");
    
    printf("UDP的connect()：\n");
    printf("  • 不建立连接（UDP无连接）\n");
    printf("  • 只是设置默认目标地址\n");
    printf("  • 之后可用send()/recv()代替sendto()/recvfrom()\n\n");
    
    printf("代码示例：\n");
    printf("  SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);\n");
    printf("  \n");
    printf("  struct sockaddr_in server_addr;\n");
    printf("  // ... 配置地址 ...\n");
    printf("  \n");
    printf("  // \"连接\"到服务器（仅设置默认目标）\n");
    printf("  connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));\n");
    printf("  \n");
    printf("  // 之后可以用send/recv（更简洁）\n");
    printf("  send(sock, data, len, 0);     // 发送到默认目标\n");
    printf("  recv(sock, buffer, size, 0);  // 只接收来自默认目标的数据\n");
    
    printf("\nUDP connect()的好处：\n");
    printf("  ✓ 代码更简洁（不用每次指定地址）\n");
    printf("  ✓ 过滤其他来源的数据\n");
    printf("  ✓ 可以收到ICMP错误通知\n");
    printf("  ✓ 性能略有提升\n");
    
    printf("\nUDP connect()的缺点：\n");
    printf("  ✗ 只能与一个对端通信\n");
    printf("  ✗ 失去了UDP的灵活性\n");
    
    printf("\n使用建议：\n");
    printf("  • 客户端与固定服务器通信 → 使用connect\n");
    printf("  • 服务器响应多个客户端   → 不用connect\n");
    printf("  • 需要广播/组播          → 不能用connect\n");
    
    printf("\n");
}

// 示例7：UDP消息边界
void example_udp_message_boundary() {
    printf("=== 示例7：UDP消息边界 ===\n\n");
    
    printf("TCP vs UDP 消息边界：\n\n");
    
    printf("TCP（流式，无边界）：\n");
    printf("  发送端：\n");
    printf("    send(sock, \"Hello\", 5, 0);\n");
    printf("    send(sock, \"World\", 5, 0);\n");
    printf("  \n");
    printf("  接收端可能收到：\n");
    printf("    recv() → \"HelloWorld\" (10字节)\n");
    printf("    或\n");
    printf("    recv() → \"Hello\" (5字节)\n");
    printf("    recv() → \"World\" (5字节)\n");
    printf("    或\n");
    printf("    recv() → \"Hel\" (3字节)\n");
    printf("    recv() → \"loWorld\" (7字节)\n");
    printf("  \n");
    printf("  → 需要应用层协议解析消息边界\n\n");
    
    printf("UDP（数据报，有边界）：\n");
    printf("  发送端：\n");
    printf("    sendto(sock, \"Hello\", 5, 0, ...);\n");
    printf("    sendto(sock, \"World\", 5, 0, ...);\n");
    printf("  \n");
    printf("  接收端收到：\n");
    printf("    recvfrom() → \"Hello\" (5字节，完整的一个数据报)\n");
    printf("    recvfrom() → \"World\" (5字节，完整的一个数据报)\n");
    printf("  \n");
    printf("  → 每次recvfrom()收到完整的一个sendto()\n\n");
    
    printf("UDP消息边界特点：\n");
    printf("  ✓ 一次sendto()对应一次recvfrom()\n");
    printf("  ✓ 不会粘包（多个消息合并）\n");
    printf("  ✓ 不会拆包（一个消息分割）\n");
    printf("  ⚠ 如果recvfrom()缓冲区太小，消息会被截断\n");
    printf("  ⚠ 丢包时，整个消息丢失，不会收到部分消息\n");
    
    printf("\n⚠ 重要提醒：\n");
    printf("  UDP缓冲区必须足够大！\n");
    printf("  如果数据报大于缓冲区，超出部分会被丢弃\n");
    printf("  建议缓冲区至少1500字节（以太网MTU）\n");
    
    printf("\n");
}

// 示例8：UDP最大传输单元（MTU）
void example_udp_mtu() {
    printf("=== 示例8：UDP与MTU ===\n\n");
    
    printf("MTU（Maximum Transmission Unit）最大传输单元：\n");
    printf("  • 以太网MTU：1500字节\n");
    printf("  • IPv4头部：20字节\n");
    printf("  • UDP头部：8字节\n");
    printf("  • UDP数据最大：1500 - 20 - 8 = 1472字节\n\n");
    
    printf("超过MTU会怎样？\n");
    printf("  1. IPv4分片：\n");
    printf("     • 系统自动将数据分成多个IP包\n");
    printf("     • 任一分片丢失，整个数据报丢失\n");
    printf("     • 增加丢包概率\n");
    printf("  \n");
    printf("  2. 路径MTU发现：\n");
    printf("     • 路径上的最小MTU\n");
    printf("     • 可能小于1500字节\n\n");
    
    printf("UDP数据大小建议：\n");
    printf("  ✓ 小消息（<512字节）：无问题\n");
    printf("  ✓ 中等消息（512-1472字节）：通常可行\n");
    printf("  ⚠ 大消息（>1472字节）：\n");
    printf("     • 会导致IP分片\n");
    printf("     • 建议应用层分片\n");
    printf("     • 或使用TCP\n\n");
    
    printf("查看MTU（命令行）：\n");
#ifdef _WIN32
    printf("  Windows: netsh interface ipv4 show subinterfaces\n");
#else
    printf("  Linux:   ip link show\n");
    printf("           ifconfig\n");
#endif
    
    printf("\n实际建议：\n");
    printf("  • UDP包保持在1400字节以下最安全\n");
    printf("  • DNS查询限制为512字节\n");
    printf("  • 大数据传输考虑使用TCP\n");
    
    printf("\n");
}

// 主菜单
void show_menu() {
    printf("\n");
    printf("╔═══════════════════════════════════════╗\n");
    printf("║   UDP编程示例菜单                     ║\n");
    printf("╚═══════════════════════════════════════╝\n");
    printf("1. UDP vs TCP对比\n");
    printf("2. UDP Echo服务器\n");
    printf("3. UDP客户端\n");
    printf("4. UDP广播\n");
    printf("5. UDP组播说明\n");
    printf("6. UDP的connect()用法\n");
    printf("7. UDP消息边界\n");
    printf("8. UDP与MTU\n");
    printf("0. 退出\n");
    printf("───────────────────────────────────────\n");
    printf("选择 (0-8): ");
}

int main() {
    printf("╔═══════════════════════════════════════╗\n");
    printf("║   第10章：网络Socket编程              ║\n");
    printf("║   10.5 UDP编程                        ║\n");
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
                example_udp_vs_tcp();
                break;
            case 2:
                example_udp_server();
                break;
            case 3:
                example_udp_client();
                break;
            case 4:
                example_udp_broadcast();
                break;
            case 5:
                example_udp_multicast();
                break;
            case 6:
                example_udp_connect();
                break;
            case 7:
                example_udp_message_boundary();
                break;
            case 8:
                example_udp_mtu();
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
 *   Windows: gcc 10.5_udp_programming.c -o udp_demo -lws2_32
 *            udp_demo.exe
 * 
 *   Linux:   gcc 10.5_udp_programming.c -o udp_demo
 *            ./udp_demo
 * 
 * 测试方法：
 *   1. 运行示例2启动UDP服务器
 *   2. 另开终端运行示例3测试客户端
 *   3. 观察UDP通信过程
 * 
 * 学习要点：
 *   1. 掌握UDP的基本API（sendto/recvfrom）
 *   2. 理解UDP与TCP的根本区别
 *   3. 了解UDP广播和组播
 *   4. 理解UDP消息边界的重要性
 *   5. 掌握UDP的MTU限制
 *   6. 学会选择TCP还是UDP
 * 
 * 第10章总结：
 *   ✓ 网络基础概念（OSI模型、TCP/IP）
 *   ✓ Socket API详解
 *   ✓ TCP服务器和客户端实现
 *   ✓ UDP编程
 *   ✓ 跨平台网络编程技巧
 * 
 * 下一步学习建议：
 *   • I/O多路复用（select/poll/epoll）
 *   • 非阻塞Socket
 *   • 多线程/多进程服务器
 *   • HTTP/WebSocket协议实现
 *   • 安全通信（SSL/TLS）
 */
