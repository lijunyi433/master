#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <string.h>


using namespace std;

struct msg_buf
{
	long mtype;
	char mtext[256];
};

int main(int argc, const char * argv[]){
	pid_t pid;
	int msqid;
	key_t key = 1234;
	struct msg_buf message;
	
	// memset(&(message.message), ' ', sizeof(message.message));

	//创建消息队列
	// if ((msqid = msgget(key, IPC_CREAT | 0666)) < 0)
	if ((msqid = msgget(key, IPC_CREAT | 0666)) < 0)
	{
		cerr << "Failed to create message queue." << endl;
		return 1;
	}

	if((pid = fork()) < 0)
	{
		cerr << "Failed to create child process." << endl;
		return 1;
	}
	else if(pid > 0)
	{
		//父进程
		sleep(1);

		msgrcv(msqid, &message, sizeof(message.mtext), 2, 0);
		cout << "Message from child is " << message.mtext << endl;

		message.mtype = 3;
		strcpy(message.mtext, "Hello, child process.");
		msgsnd(msqid, &message, sizeof(message.mtext), IPC_NOWAIT);

		//等待子进程结束
		wait(NULL);

		//删除消息队列
		msgctl(msqid, IPC_RMID, NULL);

		
	}
	else
	{
		//子进程
		message.mtype = 2;
		strcpy(message.mtext, "Hello, parent process.");
		msgsnd(msqid, &message, sizeof(message.mtext), IPC_NOWAIT);
	
		msgrcv(msqid, &message, sizeof(message.mtext), 3, 0);
		cout << "Message from parent is " << message.mtext << endl;
	}

   	return 0;
}



// #include <iostream>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/ipc.h>
// #include <sys/msg.h>
// #include <sys/wait.h>
// #include <string.h>

// using namespace std;

// struct msg_buf {
//     long type;
//     char message[256];
// };

// int main() {
//     pid_t pid;
//     int msqid;
//     key_t key = 1234;
//     struct msg_buf message;

//     // 创建消息队列
//     if ((msqid = msgget(key, IPC_CREAT | 0666)) < 0) {
//         cerr << "Failed to create message queue." << endl;
//         return 1;
//     }
    
//     // 创建子进程
//     if ((pid = fork()) < 0) {
//         cerr << "Failed to create child process." << endl;
//         return 1;
//     } else if (pid > 0) { // 父进程
//         sleep(1); // 等待子进程执行
    
//         msgrcv(msqid, &message, sizeof(message.message), 2, 0); // 接收来自子进程的消息
//         cout << "Message from child process: " << message.message << endl;
    
//         message.type = 3;
//         strcpy(message.message, "Hello, child process.");
//         msgsnd(msqid, &message, sizeof(message.message), IPC_NOWAIT); // 向消息队列中发送消息
    
//         wait(NULL); // 等待子进程结束
    
//         // 删除消息队列
//         msgctl(msqid, IPC_RMID, NULL);
//     } else { // 子进程
//         message.type = 2;
//         strcpy(message.message, "Hello, parent process.");
//         msgsnd(msqid, &message, sizeof(message.message), IPC_NOWAIT); // 向消息队列中发送消息
    
//         msgrcv(msqid, &message, sizeof(message.message), 3, 0); // 接收来自父进程的消息
//         cout << "Message from parent process: " << message.message << endl;
//     }
    
//     return 0;

// }
