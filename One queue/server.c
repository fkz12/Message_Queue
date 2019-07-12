#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf {
	long mtype;
	char mtext[50];
} message;

int main() {
    
	key_t key;

	key = ftok("q", 'c');
	int id = msgget (key, IPC_CREAT | 0666);

	message.mtype = 1;
	
	printf("Server: ");
	gets(message.mtext);
	msgsnd(id, &message, sizeof(message), 0);
	
	msgrcv(id, &message, sizeof(message), 1, 0);
	printf("Client: %s\n", message.mtext);

	msgctl (id, IPC_RMID, NULL);

	return 0;
}


