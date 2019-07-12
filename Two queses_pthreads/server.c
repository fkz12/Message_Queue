#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <string.h>
#define N 5

struct msgbuf {
	long mtype;
	char mtext[50];
} message[N];

int main() {
    
	time_t mytime;

	key_t key1, key2;	
	key1 = ftok("q", 'a');
	int id1 = msgget (key1, IPC_CREAT | 0666);
	key2 = ftok("q", 'b');
	int id2 = msgget (key2, IPC_CREAT | 0666);

	for (int i=0; i<N; i++) {
		message[i].mtype = i+1;	
		msgrcv(id1, &message[i], sizeof(message)*N, i+1, 0);
		mytime = time(NULL);
		strcpy(message[i].mtext, ctime(&mytime));
		msgsnd(id2, &message[i], sizeof(message)*N, 0);
	}

//	msgctl (id1, IPC_RMID, NULL); doesn't working
//	msgctl (id2, IPC_RMID, NULL); doesn't working

	return 0;
}


