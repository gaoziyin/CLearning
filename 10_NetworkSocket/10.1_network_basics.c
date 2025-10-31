/*
 * 第十章：网络Socket编程
 * 10.1 网络基础概念
 * 
 * 本文件介绍网络编程的基础知识
 * 编译命令（Windows）：gcc 10.1_network_basics.c -o 10.1 -lws2_32
 * 编译命令（Linux）：  gcc 10.1_network_basics.c -o 10.1
 */

#include <stdio.h>
#include <string.h>

// 跨平台处理
#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <netdb.h>
#endif

// 示例1：OSI七层模型概念
void example_osi_model() {
    printf("=== 示例1：OSI七层模型 ===\n");
    
    printf("\n┌─────────────────────────────────────┐\n");
    printf("│  OSI七层模型                        │\n");
    printf("├──────┬──────────────────────────────┤\n");
    printf("│ 7层  │ 应用层 (Application)         │\n");
    printf("│      │ HTTP, FTP, SMTP, DNS...      │\n");
    printf("├──────┼──────────────────────────────┤\n");
    printf("│ 6层  │ 表示层 (Presentation)        │\n");
    printf("│      │ 数据格式转换、加密解密       │\n");
    printf("├──────┼──────────────────────────────┤\n");
    printf("│ 5层  │ 会话层 (Session)             │\n");
    printf("│      │ 会话管理、同步               │\n");
    printf("├──────┼──────────────────────────────┤\n");
    printf("│ 4层  │ 传输层 (Transport)           │\n");
    printf("│      │ TCP, UDP ← Socket编程在这层  │\n");
    printf("├──────┼──────────────────────────────┤\n");
    printf("│ 3层  │ 网络层 (Network)             │\n");
    printf("│      │ IP, ICMP, 路由               │\n");
    printf("├──────┼──────────────────────────────┤\n");
    printf("│ 2层  │ 数据链路层 (Data Link)       │\n");
    printf("│      │ MAC地址、以太网帧            │\n");
    printf("├──────┼──────────────────────────────┤\n");
    printf("│ 1层  │ 物理层 (Physical)            │\n");
    printf("│      │ 电信号、光信号、网线         │\n");
    printf("└──────┴──────────────────────────────┘\n");
    
    printf("\nSocket编程工作在传输层（第4层）\n");
    printf("我们使用TCP或UDP协议进行通信\n\n");
}

// 示例2：TCP/IP四层模型
void example_tcpip_model() {
    printf("=== 示例2：TCP/IP四层模型 ===\n");
    
    printf("\n┌─────────────────────────────────────┐\n");
    printf("│  TCP/IP四层模型（实际使用）         │\n");
    printf("├──────┬──────────────────────────────┤\n");
    printf("│ 4层  │ 应用层 (Application)         │\n");
    printf("│      │ HTTP, FTP, SMTP, DNS, SSH... │\n");
    printf("│      │ 对应OSI的5-7层               │\n");
    printf("├──────┼──────────────────────────────┤\n");
    printf("│ 3层  │ 传输层 (Transport)           │\n");
    printf("│      │ TCP (可靠) / UDP (快速)      │\n");
    printf("│      │ ← Socket API在这里           │\n");
    printf("├──────┼──────────────────────────────┤\n");
    printf("│ 2层  │ 网络层 (Internet)            │\n");
    printf("│      │ IP, ICMP, ARP                │\n");
    printf("├──────┼──────────────────────────────┤\n");
    printf("│ 1层  │ 网络接口层 (Link)            │\n");
    printf("│      │ 以太网、WiFi、驱动程序       │\n");
    printf("│      │ 对应OSI的1-2层               │\n");
    printf("└──────┴──────────────────────────────┘\n");
    
    printf("\n实际开发中通常使用TCP/IP模型\n\n");
}

// 示例3：TCP vs UDP
void example_tcp_vs_udp() {
    printf("=== 示例3：TCP vs UDP对比 ===\n");
    
    printf("\n┌─────────────┬──────────────┬──────────────┐\n");
    printf("│  特性       │     TCP      │     UDP      │\n");
    printf("├─────────────┼──────────────┼──────────────┤\n");
    printf("│ 连接        │ 面向连接     │ 无连接       │\n");
    printf("│ 可靠性      │ 可靠传输     │ 不保证可靠   │\n");
    printf("│ 顺序        │ 保证顺序     │ 不保证顺序   │\n");
    printf("│ 速度        │ 较慢         │ 快速         │\n");
    printf("│ 开销        │ 大（头部20B）│ 小（头部8B） │\n");
    printf("│ 流控制      │ 有           │ 无           │\n");
    printf("│ 拥塞控制    │ 有           │ 无           │\n");
    printf("│ 应用场景    │ 文件传输     │ 视频直播     │\n");
    printf("│             │ HTTP/HTTPS   │ DNS查询      │\n");
    printf("│             │ 邮件         │ 在线游戏     │\n");
    printf("│             │ SSH/Telnet   │ 语音通话     │\n");
    printf("└─────────────┴──────────────┴──────────────┘\n");
    
    printf("\n选择建议：\n");
    printf("  • 需要可靠传输 → TCP\n");
    printf("  • 实时性要求高 → UDP\n");
    printf("  • 传输大文件   → TCP\n");
    printf("  • 广播/组播    → UDP\n\n");
}

// 示例4：IP地址概念
void example_ip_address() {
    printf("=== 示例4：IP地址 ===\n");
    
    printf("\nIPv4地址（32位）：\n");
    printf("  格式：xxx.xxx.xxx.xxx\n");
    printf("  示例：192.168.1.100\n");
    printf("  范围：0.0.0.0 ~ 255.255.255.255\n");
    
    printf("\n特殊IP地址：\n");
    printf("  127.0.0.1      - 本机回环地址 (localhost)\n");
    printf("  0.0.0.0        - 所有接口/未指定地址\n");
    printf("  255.255.255.255- 广播地址\n");
    printf("  192.168.x.x    - 私有网络（C类）\n");
    printf("  10.x.x.x       - 私有网络（A类）\n");
    printf("  172.16-31.x.x  - 私有网络（B类）\n");
    
    printf("\nIPv6地址（128位）：\n");
    printf("  格式：xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx\n");
    printf("  示例：2001:0db8:85a3:0000:0000:8a2e:0370:7334\n");
    printf("  简写：2001:db8:85a3::8a2e:370:7334\n");
    printf("  本机：::1\n");
    
    printf("\n");
}

// 示例5：端口号概念
void example_port_numbers() {
    printf("=== 示例5：端口号 ===\n");
    
    printf("\n端口号范围（0-65535）：\n");
    printf("  • 0-1023     : 知名端口（需要root/管理员权限）\n");
    printf("  • 1024-49151 : 注册端口（应用程序使用）\n");
    printf("  • 49152-65535: 动态端口（临时使用）\n");
    
    printf("\n常用端口号：\n");
    printf("  ┌──────┬─────────────────┐\n");
    printf("  │ 端口 │ 服务            │\n");
    printf("  ├──────┼─────────────────┤\n");
    printf("  │  20  │ FTP数据         │\n");
    printf("  │  21  │ FTP控制         │\n");
    printf("  │  22  │ SSH             │\n");
    printf("  │  23  │ Telnet          │\n");
    printf("  │  25  │ SMTP（邮件）    │\n");
    printf("  │  53  │ DNS             │\n");
    printf("  │  80  │ HTTP            │\n");
    printf("  │ 443  │ HTTPS           │\n");
    printf("  │ 3306 │ MySQL           │\n");
    printf("  │ 5432 │ PostgreSQL      │\n");
    printf("  │ 6379 │ Redis           │\n");
    printf("  │ 8080 │ HTTP代理        │\n");
    printf("  └──────┴─────────────────┘\n");
    
    printf("\n⚠ 自定义程序建议使用1024以上的端口\n\n");
}

// 示例6：字节序（大端/小端）
void example_byte_order() {
    printf("=== 示例6：字节序（Endianness）===\n");
    
    unsigned short test = 0x1234;
    unsigned char *ptr = (unsigned char *)&test;
    
    printf("\n测试数值：0x1234\n");
    printf("内存布局：\n");
    
    if (ptr[0] == 0x34) {
        printf("  地址0: 0x%02X (低字节)\n", ptr[0]);
        printf("  地址1: 0x%02X (高字节)\n", ptr[1]);
        printf("  → 小端序 (Little-Endian) - x86/x64\n");
    } else {
        printf("  地址0: 0x%02X (高字节)\n", ptr[0]);
        printf("  地址1: 0x%02X (低字节)\n", ptr[1]);
        printf("  → 大端序 (Big-Endian) - 网络字节序\n");
    }
    
    printf("\n网络编程中的字节序：\n");
    printf("  • 网络字节序：大端序（Big-Endian）\n");
    printf("  • 主机字节序：取决于CPU架构\n");
    printf("  • 转换函数：\n");
    printf("    - htons()  Host TO Network Short (16位)\n");
    printf("    - htonl()  Host TO Network Long (32位)\n");
    printf("    - ntohs()  Network TO Host Short\n");
    printf("    - ntohl()  Network TO Host Long\n");
    
    // 演示转换
    unsigned short port = 8080;
    unsigned short net_port = htons(port);
    printf("\n转换示例：\n");
    printf("  主机字节序端口: %u (0x%04X)\n", port, port);
    printf("  网络字节序端口: %u (0x%04X)\n", ntohs(net_port), net_port);
    
    printf("\n");
}

// 示例7：Socket地址结构
void example_socket_address() {
    printf("=== 示例7：Socket地址结构 ===\n");
    
    printf("\nIPv4地址结构 (struct sockaddr_in):\n");
    printf("  struct sockaddr_in {\n");
    printf("      short            sin_family;   // AF_INET\n");
    printf("      unsigned short   sin_port;     // 端口（网络字节序）\n");
    printf("      struct in_addr   sin_addr;     // IP地址\n");
    printf("      char             sin_zero[8];  // 填充字节\n");
    printf("  };\n");
    
    printf("\nIPv6地址结构 (struct sockaddr_in6):\n");
    printf("  struct sockaddr_in6 {\n");
    printf("      short            sin6_family;  // AF_INET6\n");
    printf("      unsigned short   sin6_port;    // 端口\n");
    printf("      unsigned long    sin6_flowinfo;// 流信息\n");
    printf("      struct in6_addr  sin6_addr;    // IPv6地址\n");
    printf("      unsigned long    sin6_scope_id;// 作用域ID\n");
    printf("  };\n");
    
    printf("\n通用地址结构 (struct sockaddr):\n");
    printf("  struct sockaddr {\n");
    printf("      unsigned short   sa_family;    // 地址族\n");
    printf("      char             sa_data[14];  // 地址数据\n");
    printf("  };\n");
    
    printf("\n⚠ sockaddr只是通用接口，实际使用sockaddr_in/in6\n");
    printf("   传递给函数时强制转换为 (struct sockaddr *)\n");
    
    printf("\n");
}

// 示例8：IP地址转换函数
void example_ip_conversion() {
    printf("=== 示例8：IP地址转换 ===\n");
    
#ifdef _WIN32
    // Windows需要初始化Winsock
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
    
    // 字符串 → 二进制
    struct sockaddr_in addr;
    const char *ip_str = "192.168.1.100";
    
    printf("\n1. 字符串 → 二进制（inet_pton）:\n");
    if (inet_pton(AF_INET, ip_str, &addr.sin_addr) == 1) {
        printf("   输入: %s\n", ip_str);
        printf("   输出: 0x%08X\n", ntohl(addr.sin_addr.s_addr));
    }
    
    // 二进制 → 字符串
    char ip_buf[INET_ADDRSTRLEN];
    printf("\n2. 二进制 → 字符串（inet_ntop）:\n");
    if (inet_ntop(AF_INET, &addr.sin_addr, ip_buf, sizeof(ip_buf)) != NULL) {
        printf("   输入: 0x%08X\n", ntohl(addr.sin_addr.s_addr));
        printf("   输出: %s\n", ip_buf);
    }
    
    // 旧函数（不推荐）
    printf("\n3. 旧版函数（不推荐，仅IPv4）:\n");
    printf("   inet_addr()  : 字符串 → 二进制\n");
    printf("   inet_ntoa()  : 二进制 → 字符串\n");
    printf("   推荐使用inet_pton/inet_ntop（支持IPv6）\n");
    
#ifdef _WIN32
    WSACleanup();
#endif
    
    printf("\n");
}

// 示例9：域名解析（DNS）
void example_dns_resolution() {
    printf("=== 示例9：域名解析 ===\n");
    
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
    
    const char *hostname = "www.example.com";
    struct addrinfo hints, *result, *rp;
    
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;    // IPv4或IPv6
    hints.ai_socktype = SOCK_STREAM;// TCP
    
    printf("\n解析域名：%s\n", hostname);
    
    int status = getaddrinfo(hostname, NULL, &hints, &result);
    if (status == 0) {
        printf("\n解析结果：\n");
        int count = 0;
        for (rp = result; rp != NULL; rp = rp->ai_next) {
            count++;
            char ipstr[INET6_ADDRSTRLEN];
            void *addr;
            
            if (rp->ai_family == AF_INET) {
                struct sockaddr_in *ipv4 = (struct sockaddr_in *)rp->ai_addr;
                addr = &(ipv4->sin_addr);
                inet_ntop(AF_INET, addr, ipstr, sizeof(ipstr));
                printf("  %d. IPv4: %s\n", count, ipstr);
            } else if (rp->ai_family == AF_INET6) {
                struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)rp->ai_addr;
                addr = &(ipv6->sin6_addr);
                inet_ntop(AF_INET6, addr, ipstr, sizeof(ipstr));
                printf("  %d. IPv6: %s\n", count, ipstr);
            }
        }
        freeaddrinfo(result);
    } else {
        printf("  解析失败（可能是网络问题或域名不存在）\n");
    }
    
    printf("\ngetaddrinfo()函数：\n");
    printf("  • 现代DNS解析API\n");
    printf("  • 支持IPv4和IPv6\n");
    printf("  • 返回多个地址（负载均衡）\n");
    
#ifdef _WIN32
    WSACleanup();
#endif
    
    printf("\n");
}

// 示例10：Socket编程流程预览
void example_socket_flow() {
    printf("=== 示例10：Socket编程流程 ===\n");
    
    printf("\nTCP服务器流程：\n");
    printf("  1. socket()   → 创建套接字\n");
    printf("  2. bind()     → 绑定IP和端口\n");
    printf("  3. listen()   → 监听连接\n");
    printf("  4. accept()   → 接受客户端连接\n");
    printf("  5. recv()     → 接收数据\n");
    printf("  6. send()     → 发送数据\n");
    printf("  7. close()    → 关闭连接\n");
    
    printf("\nTCP客户端流程：\n");
    printf("  1. socket()   → 创建套接字\n");
    printf("  2. connect()  → 连接服务器\n");
    printf("  3. send()     → 发送数据\n");
    printf("  4. recv()     → 接收数据\n");
    printf("  5. close()    → 关闭连接\n");
    
    printf("\nUDP服务器流程：\n");
    printf("  1. socket()   → 创建套接字\n");
    printf("  2. bind()     → 绑定IP和端口\n");
    printf("  3. recvfrom() → 接收数据（包含客户端地址）\n");
    printf("  4. sendto()   → 发送数据到客户端\n");
    printf("  5. close()    → 关闭套接字\n");
    
    printf("\nUDP客户端流程：\n");
    printf("  1. socket()   → 创建套接字\n");
    printf("  2. sendto()   → 发送数据到服务器\n");
    printf("  3. recvfrom() → 接收数据\n");
    printf("  4. close()    → 关闭套接字\n");
    
    printf("\n");
}

int main() {
    printf("╔═══════════════════════════════════════╗\n");
    printf("║   第10章：网络Socket编程              ║\n");
    printf("║   10.1 网络基础概念                   ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
    
    example_osi_model();
    example_tcpip_model();
    example_tcp_vs_udp();
    example_ip_address();
    example_port_numbers();
    example_byte_order();
    example_socket_address();
    example_ip_conversion();
    example_dns_resolution();
    example_socket_flow();
    
    printf("═════════════════════════════════════════\n");
    printf("核心知识点总结：\n");
    printf("═════════════════════════════════════════\n");
    printf("1. 网络模型：\n");
    printf("   • OSI七层模型（理论）\n");
    printf("   • TCP/IP四层模型（实际）\n");
    printf("   • Socket工作在传输层\n");
    printf("\n");
    printf("2. 传输协议：\n");
    printf("   • TCP：可靠、有序、面向连接\n");
    printf("   • UDP：快速、无连接、不可靠\n");
    printf("\n");
    printf("3. 地址系统：\n");
    printf("   • IP地址：主机标识（IPv4/IPv6）\n");
    printf("   • 端口号：应用程序标识（0-65535）\n");
    printf("   • Socket地址：IP + 端口\n");
    printf("\n");
    printf("4. 字节序：\n");
    printf("   • 网络字节序：大端序\n");
    printf("   • 主机字节序：与CPU相关\n");
    printf("   • 转换函数：htons/htonl/ntohs/ntohl\n");
    printf("\n");
    printf("5. 重要函数：\n");
    printf("   • inet_pton/inet_ntop：IP地址转换\n");
    printf("   • getaddrinfo：域名解析（推荐）\n");
    printf("   • socket/bind/listen/accept：服务器\n");
    printf("   • socket/connect：客户端\n");
    printf("═════════════════════════════════════════\n");
    
    return 0;
}

/*
 * 编译和运行：
 *   Windows: gcc 10.1_network_basics.c -o 10.1 -lws2_32
 *            10.1.exe
 * 
 *   Linux:   gcc 10.1_network_basics.c -o 10.1
 *            ./10.1
 * 
 * 学习要点：
 *   1. 理解OSI和TCP/IP模型
 *   2. 掌握TCP和UDP的区别
 *   3. 熟悉IP地址、端口号概念
 *   4. 理解字节序及转换
 *   5. 了解Socket编程的基本流程
 * 
 * 下一步：
 *   学习10.2 Socket编程基础，实际创建和使用套接字
 */
