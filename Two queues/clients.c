#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#define N 5

struct msgbuf {
	long mtype;
	char mtext[50];
} message[N];

int main() {

	key_t key1, key2;
	
	key1 = ftok("q", 'a');
	int id1 = msgget(key1, 0); 

	key2 = ftok("q", 'b');
	int id2 = msgget(key2, 0);

	for (int i=0; i<N; i++) {
	
		message[i].mtype = i+1;	
		printf("Send %d message...\n", i);
		sleep(1);
		msgsnd(id1, &message[i], sizeof(message)*N, 0);		
		msgrcv(id2, &message[i], sizeof(message)*N, i+1, 0);
	}

	for (int i=0; i<N; i++) 
		printf("Recieved time[%d]: %s\n", i, message[i].mtext);	

	return 0;
}
