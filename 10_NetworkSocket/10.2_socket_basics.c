/*
 * 第十章：网络Socket编程
 * 10.2 Socket编程基础
 * 
 * 本文件详细讲解Socket API的使用方法
 * 编译命令（Windows）：gcc 10.2_socket_basics.c -o 10.2 -lws2_32
 * 编译命令（Linux）：  gcc 10.2_socket_basics.c -o 10.2
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

// 示例1：初始化Socket库（Windows专用）
void example_winsock_init() {
    printf("=== 示例1：Socket库初始化 ===\n");
    
#ifdef _WIN32
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    
    if (result != 0) {
        printf("❌ WSAStartup失败，错误代码: %d\n", result);
        return;
    }
    
    printf("✓ Windows Winsock初始化成功\n");
    printf("  版本: %d.%d\n", LOBYTE(wsaData.wVersion), HIBYTE(wsaData.wVersion));
    printf("  描述: %s\n", wsaData.szDescription);
    printf("  状态: %s\n", wsaData.szSystemStatus);
    
    printf("\n⚠ Windows必须在使用Socket前调用WSAStartup()\n");
    printf("   使用完毕后调用WSACleanup()\n");
    
    WSACleanup();
#else
    printf("✓ Linux系统不需要初始化Socket库\n");
    printf("  可以直接使用socket()函数\n");
#endif
    
    printf("\n");
}

// 示例2：创建Socket
void example_socket_create() {
    printf("=== 示例2：创建Socket ===\n");
    
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
    
    printf("\nsocket()函数原型：\n");
    printf("  int socket(int domain, int type, int protocol);\n");
    
    printf("\n参数说明：\n");
    printf("  domain (地址族)：\n");
    printf("    AF_INET  - IPv4\n");
    printf("    AF_INET6 - IPv6\n");
    printf("\n");
    printf("  type (套接字类型)：\n");
    printf("    SOCK_STREAM - TCP流式套接字（可靠）\n");
    printf("    SOCK_DGRAM  - UDP数据报套接字（快速）\n");
    printf("    SOCK_RAW    - 原始套接字（需要root权限）\n");
    printf("\n");
    printf("  protocol (协议)：\n");
    printf("    0           - 自动选择（推荐）\n");
    printf("    IPPROTO_TCP - 明确指定TCP\n");
    printf("    IPPROTO_UDP - 明确指定UDP\n");
    
    // 创建TCP套接字
    printf("\n创建TCP套接字：\n");
    SOCKET tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_sock == INVALID_SOCKET) {
        printf("❌ TCP套接字创建失败\n");
    } else {
        printf("✓ TCP套接字创建成功，描述符: %d\n", (int)tcp_sock);
        closesocket(tcp_sock);
    }
    
    // 创建UDP套接字
    printf("\n创建UDP套接字：\n");
    SOCKET udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_sock == INVALID_SOCKET) {
        printf("❌ UDP套接字创建失败\n");
    } else {
        printf("✓ UDP套接字创建成功，描述符: %d\n", (int)udp_sock);
        closesocket(udp_sock);
    }
    
#ifdef _WIN32
    WSACleanup();
#endif
    
    printf("\n");
}

// 示例3：设置Socket选项（setsockopt）
void example_setsockopt() {
    printf("=== 示例3：设置Socket选项 ===\n");
    
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
    
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("❌ 套接字创建失败\n");
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }
    
    printf("\nsetsockopt()函数原型：\n");
    printf("  int setsockopt(int socket, int level, int optname,\n");
    printf("                 const void *optval, socklen_t optlen);\n");
    
    // 1. 设置地址重用（重要！）
    printf("\n1. SO_REUSEADDR - 地址重用：\n");
    int reuse = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, 
                   (char*)&reuse, sizeof(reuse)) == 0) {
        printf("   ✓ 已启用地址重用\n");
        printf("   作用：程序崩溃后可立即重启（不用等待TIME_WAIT）\n");
    }
    
    // 2. 设置接收缓冲区大小
    printf("\n2. SO_RCVBUF - 接收缓冲区：\n");
    int rcvbuf = 8192;
    if (setsockopt(sock, SOL_SOCKET, SO_RCVBUF, 
                   (char*)&rcvbuf, sizeof(rcvbuf)) == 0) {
        printf("   ✓ 接收缓冲区设置为 %d 字节\n", rcvbuf);
    }
    
    // 3. 设置发送缓冲区大小
    printf("\n3. SO_SNDBUF - 发送缓冲区：\n");
    int sndbuf = 8192;
    if (setsockopt(sock, SOL_SOCKET, SO_SNDBUF, 
                   (char*)&sndbuf, sizeof(sndbuf)) == 0) {
        printf("   ✓ 发送缓冲区设置为 %d 字节\n", sndbuf);
    }
    
    // 4. 设置接收超时
    printf("\n4. SO_RCVTIMEO - 接收超时：\n");
#ifdef _WIN32
    DWORD timeout = 5000;  // 毫秒
#else
    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
#endif
    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, 
                   (char*)&timeout, sizeof(timeout)) == 0) {
        printf("   ✓ 接收超时设置为 5 秒\n");
    }
    
    printf("\n常用Socket选项：\n");
    printf("  SO_REUSEADDR - 地址重用（推荐服务器使用）\n");
    printf("  SO_KEEPALIVE - 保持连接检测\n");
    printf("  SO_RCVBUF    - 接收缓冲区大小\n");
    printf("  SO_SNDBUF    - 发送缓冲区大小\n");
    printf("  SO_RCVTIMEO  - 接收超时\n");
    printf("  SO_SNDTIMEO  - 发送超时\n");
    printf("  TCP_NODELAY  - 禁用Nagle算法（减少延迟）\n");
    
    closesocket(sock);
    
#ifdef _WIN32
    WSACleanup();
#endif
    
    printf("\n");
}

// 示例4：绑定地址（bind）
void example_bind() {
    printf("=== 示例4：绑定地址 ===\n");
    
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
    
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("❌ 套接字创建失败\n");
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }
    
    // 启用地址重用
    int reuse = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(reuse));
    
    printf("\nbind()函数原型：\n");
    printf("  int bind(int socket, struct sockaddr *addr, socklen_t len);\n");
    
    // 配置服务器地址
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;           // IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY;   // 所有网卡接口
    server_addr.sin_port = htons(9999);         // 端口9999
    
    printf("\n绑定配置：\n");
    printf("  地址族:   AF_INET (IPv4)\n");
    printf("  IP地址:   0.0.0.0 (INADDR_ANY - 所有接口)\n");
    printf("  端口:     9999\n");
    
    if (bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == 0) {
        printf("\n✓ 绑定成功！\n");
        printf("  服务器现在监听在 0.0.0.0:9999\n");
    } else {
        printf("\n❌ 绑定失败\n");
#ifdef _WIN32
        printf("  错误代码: %d\n", WSAGetLastError());
#else
        printf("  错误: %s\n", strerror(errno));
#endif
        printf("  可能原因：\n");
        printf("    • 端口已被占用\n");
        printf("    • 权限不足（端口<1024需要root）\n");
    }
    
    printf("\nbind()注意事项：\n");
    printf("  • INADDR_ANY (0.0.0.0) 监听所有网卡\n");
    printf("  • 端口号必须用htons()转换为网络字节序\n");
    printf("  • 客户端通常不需要bind，系统自动分配\n");
    printf("  • 服务器必须bind指定端口\n");
    
    closesocket(sock);
    
#ifdef _WIN32
    WSACleanup();
#endif
    
    printf("\n");
}

// 示例5：监听连接（listen）
void example_listen() {
    printf("=== 示例5：监听连接 ===\n");
    
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
    
    int reuse = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(reuse));
    
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(9999);
    
    if (bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) != 0) {
        closesocket(sock);
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }
    
    printf("\nlisten()函数原型：\n");
    printf("  int listen(int socket, int backlog);\n");
    
    printf("\n参数说明：\n");
    printf("  backlog - 等待连接队列的最大长度\n");
    printf("          - 建议值：5-128\n");
    printf("          - 过大：浪费资源\n");
    printf("          - 过小：连接被拒绝\n");
    
    int backlog = 5;
    printf("\n设置backlog = %d\n", backlog);
    
    if (listen(sock, backlog) == 0) {
        printf("✓ 监听成功！\n");
        printf("  服务器进入监听状态\n");
        printf("  最多允许 %d 个连接在队列中等待\n", backlog);
        printf("  现在可以调用accept()接受客户端连接\n");
    } else {
        printf("❌ 监听失败\n");
    }
    
    printf("\nlisten()注意事项：\n");
    printf("  • 仅用于TCP服务器（SOCK_STREAM）\n");
    printf("  • 必须在bind()之后调用\n");
    printf("  • 调用后Socket进入被动监听状态\n");
    printf("  • UDP不需要listen\n");
    
    closesocket(sock);
    
#ifdef _WIN32
    WSACleanup();
#endif
    
    printf("\n");
}

// 示例6：接受连接（accept）
void example_accept() {
    printf("=== 示例6：接受连接（演示）===\n");
    
    printf("\naccept()函数原型：\n");
    printf("  int accept(int socket, struct sockaddr *addr, socklen_t *len);\n");
    
    printf("\n返回值：\n");
    printf("  成功：新的Socket描述符（用于与客户端通信）\n");
    printf("  失败：INVALID_SOCKET (-1)\n");
    
    printf("\n参数说明：\n");
    printf("  socket - 监听套接字\n");
    printf("  addr   - 输出客户端地址信息\n");
    printf("  len    - 地址结构大小（输入/输出参数）\n");
    
    printf("\n典型用法：\n");
    printf("  struct sockaddr_in client_addr;\n");
    printf("  socklen_t addr_len = sizeof(client_addr);\n");
    printf("  \n");
    printf("  // accept会阻塞，直到有客户端连接\n");
    printf("  int client_sock = accept(listen_sock, \n");
    printf("                           (struct sockaddr*)&client_addr,\n");
    printf("                           &addr_len);\n");
    printf("  \n");
    printf("  if (client_sock != INVALID_SOCKET) {\n");
    printf("      // 获取客户端信息\n");
    printf("      char ip[INET_ADDRSTRLEN];\n");
    printf("      inet_ntop(AF_INET, &client_addr.sin_addr, ip, sizeof(ip));\n");
    printf("      int port = ntohs(client_addr.sin_port);\n");
    printf("      printf(\"客户端连接：%%s:%%d\\n\", ip, port);\n");
    printf("  }\n");
    
    printf("\naccept()特点：\n");
    printf("  • 阻塞函数（默认）\n");
    printf("  • 返回新的Socket用于通信\n");
    printf("  • 原监听Socket继续监听\n");
    printf("  • 可以通过设置非阻塞模式改变行为\n");
    
    printf("\n");
}

// 示例7：连接服务器（connect）
void example_connect() {
    printf("=== 示例7：连接服务器（演示）===\n");
    
    printf("\nconnect()函数原型：\n");
    printf("  int connect(int socket, struct sockaddr *addr, socklen_t len);\n");
    
    printf("\n返回值：\n");
    printf("  成功：0\n");
    printf("  失败：SOCKET_ERROR (-1)\n");
    
    printf("\n典型用法：\n");
    printf("  // 创建客户端Socket\n");
    printf("  int sock = socket(AF_INET, SOCK_STREAM, 0);\n");
    printf("  \n");
    printf("  // 配置服务器地址\n");
    printf("  struct sockaddr_in server_addr;\n");
    printf("  server_addr.sin_family = AF_INET;\n");
    printf("  server_addr.sin_port = htons(8080);\n");
    printf("  inet_pton(AF_INET, \"127.0.0.1\", &server_addr.sin_addr);\n");
    printf("  \n");
    printf("  // 连接服务器\n");
    printf("  if (connect(sock, (struct sockaddr*)&server_addr,\n");
    printf("              sizeof(server_addr)) == 0) {\n");
    printf("      printf(\"连接成功！\\n\");\n");
    printf("  } else {\n");
    printf("      printf(\"连接失败！\\n\");\n");
    printf("  }\n");
    
    printf("\nconnect()特点：\n");
    printf("  • TCP客户端使用\n");
    printf("  • 会发起三次握手\n");
    printf("  • 阻塞直到连接成功或超时\n");
    printf("  • UDP也可以用connect（设置默认目标）\n");
    
    printf("\n常见错误：\n");
    printf("  ECONNREFUSED  - 连接被拒绝（服务器未监听）\n");
    printf("  ETIMEDOUT     - 连接超时\n");
    printf("  ENETUNREACH   - 网络不可达\n");
    printf("  EHOSTUNREACH  - 主机不可达\n");
    
    printf("\n");
}

// 示例8：发送数据（send/sendto）
void example_send() {
    printf("=== 示例8：发送数据 ===\n");
    
    printf("\nTCP发送 - send()：\n");
    printf("  int send(int socket, const void *buffer, size_t length, int flags);\n");
    printf("  \n");
    printf("  参数：\n");
    printf("    buffer - 要发送的数据\n");
    printf("    length - 数据长度（字节）\n");
    printf("    flags  - 通常为0\n");
    printf("  \n");
    printf("  返回值：\n");
    printf("    成功：实际发送的字节数\n");
    printf("    失败：-1\n");
    
    printf("\n典型用法：\n");
    printf("  const char *msg = \"Hello, Server!\";\n");
    printf("  int sent = send(sock, msg, strlen(msg), 0);\n");
    printf("  if (sent > 0) {\n");
    printf("      printf(\"发送了 %%d 字节\\n\", sent);\n");
    printf("  }\n");
    
    printf("\nUDP发送 - sendto()：\n");
    printf("  int sendto(int socket, const void *buffer, size_t length,\n");
    printf("             int flags, struct sockaddr *addr, socklen_t len);\n");
    printf("  \n");
    printf("  额外参数：\n");
    printf("    addr - 目标地址\n");
    printf("    len  - 地址结构大小\n");
    
    printf("\n⚠ 注意事项：\n");
    printf("  • send可能只发送部分数据\n");
    printf("  • 需要循环发送直到全部完成\n");
    printf("  • 返回值<length不是错误\n");
    printf("  • 返回-1才是真正的错误\n");
    
    printf("\n");
}

// 示例9：接收数据（recv/recvfrom）
void example_recv() {
    printf("=== 示例9：接收数据 ===\n");
    
    printf("\nTCP接收 - recv()：\n");
    printf("  int recv(int socket, void *buffer, size_t length, int flags);\n");
    printf("  \n");
    printf("  参数：\n");
    printf("    buffer - 接收缓冲区\n");
    printf("    length - 缓冲区大小\n");
    printf("    flags  - 通常为0\n");
    printf("  \n");
    printf("  返回值：\n");
    printf("    >0  - 接收到的字节数\n");
    printf("    0   - 连接关闭\n");
    printf("    -1  - 错误\n");
    
    printf("\n典型用法：\n");
    printf("  char buffer[1024];\n");
    printf("  int received = recv(sock, buffer, sizeof(buffer)-1, 0);\n");
    printf("  \n");
    printf("  if (received > 0) {\n");
    printf("      buffer[received] = '\\0';  // 字符串结束符\n");
    printf("      printf(\"收到: %%s\\n\", buffer);\n");
    printf("  } else if (received == 0) {\n");
    printf("      printf(\"连接关闭\\n\");\n");
    printf("  } else {\n");
    printf("      printf(\"接收错误\\n\");\n");
    printf("  }\n");
    
    printf("\nUDP接收 - recvfrom()：\n");
    printf("  int recvfrom(int socket, void *buffer, size_t length, int flags,\n");
    printf("               struct sockaddr *addr, socklen_t *len);\n");
    printf("  \n");
    printf("  额外参数：\n");
    printf("    addr - 输出发送方地址\n");
    printf("    len  - 地址结构大小\n");
    
    printf("\n⚠ 注意事项：\n");
    printf("  • recv默认阻塞\n");
    printf("  • 返回0表示对方关闭连接\n");
    printf("  • 接收的数据可能不完整\n");
    printf("  • 字符串数据记得加'\\0'\n");
    
    printf("\n");
}

// 示例10：关闭Socket
void example_close() {
    printf("=== 示例10：关闭Socket ===\n");
    
    printf("\n关闭函数：\n");
#ifdef _WIN32
    printf("  Windows: closesocket(sock);\n");
#else
    printf("  Linux:   close(sock);\n");
#endif
    
    printf("\n优雅关闭 - shutdown()：\n");
    printf("  int shutdown(int socket, int how);\n");
    printf("  \n");
    printf("  参数how：\n");
    printf("    SHUT_RD   (0) - 关闭接收（不再接收数据）\n");
    printf("    SHUT_WR   (1) - 关闭发送（不再发送数据）\n");
    printf("    SHUT_RDWR (2) - 关闭接收和发送\n");
    
    printf("\n典型流程：\n");
    printf("  // 1. 关闭发送，告诉对方不再发送数据\n");
    printf("  shutdown(sock, SHUT_WR);\n");
    printf("  \n");
    printf("  // 2. 继续接收对方的剩余数据\n");
    printf("  while (recv(sock, buffer, size, 0) > 0) {\n");
    printf("      // 处理数据\n");
    printf("  }\n");
    printf("  \n");
    printf("  // 3. 完全关闭Socket\n");
    printf("  closesocket(sock);\n");
    
    printf("\nshutdown() vs close()：\n");
    printf("  shutdown：\n");
    printf("    • 半关闭，可选择关闭方向\n");
    printf("    • 立即生效\n");
    printf("    • 影响所有副本\n");
    printf("  \n");
    printf("  close/closesocket：\n");
    printf("    • 完全关闭\n");
    printf("    • 减少引用计数\n");
    printf("    • 只影响当前描述符\n");
    
    printf("\n");
}

int main() {
    printf("╔═══════════════════════════════════════╗\n");
    printf("║   第10章：网络Socket编程              ║\n");
    printf("║   10.2 Socket编程基础                 ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
    
    example_winsock_init();
    example_socket_create();
    example_setsockopt();
    example_bind();
    example_listen();
    example_accept();
    example_connect();
    example_send();
    example_recv();
    example_close();
    
    printf("═════════════════════════════════════════\n");
    printf("Socket API速查表：\n");
    printf("═════════════════════════════════════════\n");
    printf("初始化（Windows）：\n");
    printf("  WSAStartup()  - 初始化Winsock\n");
    printf("  WSACleanup()  - 清理Winsock\n");
    printf("\n");
    printf("基础操作：\n");
    printf("  socket()      - 创建套接字\n");
    printf("  setsockopt()  - 设置选项\n");
    printf("  bind()        - 绑定地址和端口\n");
    printf("  listen()      - 监听连接（TCP服务器）\n");
    printf("  accept()      - 接受连接（TCP服务器）\n");
    printf("  connect()     - 连接服务器（TCP客户端）\n");
    printf("\n");
    printf("数据传输：\n");
    printf("  send()        - 发送数据（TCP）\n");
    printf("  recv()        - 接收数据（TCP）\n");
    printf("  sendto()      - 发送数据（UDP）\n");
    printf("  recvfrom()    - 接收数据（UDP）\n");
    printf("\n");
    printf("关闭：\n");
    printf("  shutdown()    - 优雅关闭\n");
    printf("  close()       - 完全关闭（Linux）\n");
    printf("  closesocket() - 完全关闭（Windows）\n");
    printf("\n");
    printf("TCP服务器流程：\n");
    printf("  socket() → setsockopt() → bind() → listen()\n");
    printf("  → accept() → recv()/send() → close()\n");
    printf("\n");
    printf("TCP客户端流程：\n");
    printf("  socket() → connect() → send()/recv() → close()\n");
    printf("═════════════════════════════════════════\n");
    
    return 0;
}

/*
 * 编译和运行：
 *   Windows: gcc 10.2_socket_basics.c -o 10.2 -lws2_32
 *            10.2.exe
 * 
 *   Linux:   gcc 10.2_socket_basics.c -o 10.2
 *            ./10.2
 * 
 * 学习要点：
 *   1. 掌握Socket基本API的使用
 *   2. 理解服务器和客户端的流程差异
 *   3. 熟悉常用的Socket选项设置
 *   4. 注意跨平台的差异（Windows vs Linux）
 *   5. 理解阻塞和非阻塞的概念
 * 
 * 下一步：
 *   学习10.3 TCP服务器实现，完整的可运行示例
 */
