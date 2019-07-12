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
	int id = msgget(key, 0);

	message.mtype = 1;	

	msgrcv(id, &message, sizeof(message), 1, 0);
	printf("Server: %s\n", message.mtext);
		
	printf("Client: ");
	gets(message.mtext);
	msgsnd(id, &message, sizeof(message), 0);
	
	return 0;
}
