工作流程详解：

server端先运行
->准备好网络库(即socket所需环境)
->创建serverSocket挂在端口等待客户端连接(中间会用到accept函数阻塞以等待)
->确认客户端已连接，则accept返回一个socket。此时由clientSocket与客户端通信传递信息(serverSocket不被占用保证并发任务正常进行)
->准备buffer缓冲数组，通过recv(...)接收客户端信息
->send作服务器向客户端的response


2026-6-4:对server重构为server_multi_tenor.cpp便于处理多线程问题