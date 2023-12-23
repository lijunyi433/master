#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <strings.h>
#include <sys/socket.h>
#include <string.h>
#include <fcntl.h>

#define BUF_SIZE 256

using namespace std;


int main(int argc, char* argv[])
{
	pid_t pid = 0;
	int acceptfd = 0;
	int clientfd = 0;
	int listenfd = 0;
	int port_num = 0;
	char buf[BUF_SIZE] = {};
	struct sockaddr_in server_addr;
	struct sockaddr_in accept_addr;
	socklen_t accept_len = 0;
	
	//创建套接字
	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Failed to create socket");
		cout << "Errno = " << errno << endl;
		return 1;
	}
	// fcntl(socketfd, F_SETFL, O_NONBLOCK);
	//设置服务器地址结构体
	// bzero((char *)&server_addr, sizeof(server_addr));
	port_num = 33507;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(port_num);
	
	//绑定套接字到服务器端口
	if(bind(listenfd,  (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
	{
		perror("Failed to bind socket");
		cout << "Errno = " << errno << endl;
		close(listenfd);
		return 1;
	}
	
	//监听套接字
	if(listen(listenfd, 1) == -1)
	{
		perror("Failed to listen socket");
		cout << "Errno = " << errno << endl;
		close(listenfd);
		return 1;
	}
	
	if((pid = fork()) < 0)
	{
		perror("Failed to create chile process");
		cout << "Errno = " << errno << endl;
		close(listenfd);
		return 1;
	}
	else if(pid > 0)
	{
		//父进程
		accept_len = sizeof(accept_addr);
		acceptfd = accept(listenfd, (struct sockaddr *)&accept_addr, &accept_len);
		bzero(buf, sizeof(buf));
		if(read(acceptfd, buf, sizeof(buf) - 1) == -1)
		{
			perror("Failed to read message");
			cout << "Errno = " << errno << endl;
			close(acceptfd);
			close(listenfd);
			return 1;
		}
		cout << "I am server.Client said : " << buf << endl;
		
		bzero(buf, sizeof(buf));
		strncpy(buf, "I am server, and I has received the message.\r\n", sizeof(buf));
		if(write(acceptfd, buf, sizeof(buf)) == -1)
		{
			perror("Failed to write message");
			cout << "Errno = " << errno << endl;
			close(acceptfd);
			close(listenfd);
			return 1;
		}
		
		close(acceptfd);
		close(listenfd);
		wait(NULL);
	} 
	else
	{
		//子进程
		if((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
			perror("Failed to create socket");
			cout << "Errno = " << errno << endl;
			return 1;
		}
		// int val = 1;
		// socklen_t len = sizeof(val);
		// setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
		if(connect(clientfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
		{
			perror("Failed to connect socket");
			cout << "Errno = " << errno << endl;
			close(clientfd);
			return 1;
		}
		// int ret = getsockopt(socketfd, SOL_SOCKET, SO_SNDBUF, &val, &len);
		// cout << ret << endl;
		// if(ret == -1)
		// {
		// 	perror("Getsockopt error");
		// }
		
		bzero(buf, sizeof(buf));
		strncpy(buf, "Hello, I am server.Can you hear me?\r\n", sizeof(buf));

		// string str = "Hello, I am client.Can you hear me?";
		if(write(clientfd, buf, sizeof(buf)) == -1)
		{
			perror("Failed to write message");
			cout << "Errno = " << errno << endl;
			close(clientfd);
			return 1;
		}
		// write(clientfd, str.c_str(), str.length());
		bzero(buf, sizeof(buf));
		if(read(clientfd, buf, sizeof(buf) - 1) == -1)
		{
			perror("Failed to read message");
			cout << "Errno = " << errno << endl;
			close(clientfd);
			return 1;
		}
		cout << "I am client.Server said : " << buf << endl;
		
		close(clientfd);
	}
	return 0;
}


// 反面教材
// #include <iostream>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <sys/wait.h>
// #include <string.h>

// using namespace std;

// int main() {
//     pid_t pid;
//     int sockfd, newsockfd, portno;
//     socklen_t clilen;
//     char buffer[256];
//     struct sockaddr_in serv_addr, cli_addr;

//     // 创建套接字
//     if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
//         cerr << "Failed to create socket." << endl;
//         return 1;
//     }
    
//     // 设置服务器地址结构体
//     bzero((char*)&serv_addr, sizeof(serv_addr));
//     portno = 29214;
//     serv_addr.sin_family = AF_INET;
//     serv_addr.sin_addr.s_addr = INADDR_ANY;
//     serv_addr.sin_port = htons(portno);
    
//     // 绑定套接字到端口号
//     if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
//         perror("Failed to bind socket");
//         return 1;
//     }
    
//     // 监听套接字
//     listen(sockfd, 5);
    
//     // 创建子进程
//     if ((pid = fork()) < 0) {
//         cerr << "Failed to create child process." << endl;
//         return 1;
//     } else if (pid > 0) { // 父进程
//         cout << "Parent process is waiting for child process..." << endl;
    
//         clilen = sizeof(cli_addr);
//         newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clilen); // 等待客户端连接
    
//         bzero(buffer, 256);
//         read(newsockfd, buffer, 255); // 从套接字中读取消息
//         cout << "Message from child process: " << buffer << endl;
    
//         string message = "Hello, child process.";
//         write(newsockfd, message.c_str(), message.length()); // 向套接字中写入消息
    
//         close(newsockfd); // 关闭新的套接字
//         wait(NULL); // 等待子进程结束
//     } else { // 子进程
//         sleep(1); // 等待父进程执行
    
//         // 连接服务器
//         if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
//             perror("Failed to connect to server");
//             return 1;
//         }
    
//         string message = "Hello, parent process.";
//         write(sockfd, message.c_str(), message.length()); // 向套接字中写入消息
    
//         bzero(buffer, 256);
//         read(sockfd, buffer, 255); // 从套接字中读取消息
//         cout << "Message from parent process: " << buffer << endl;
    
//         close(sockfd); // 关闭套接字
//     }
    
//     return 0;

// }

