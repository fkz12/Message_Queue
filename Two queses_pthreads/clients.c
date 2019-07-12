#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#define N 5

struct msgbuf {
	long mtype;
	char mtext[50];
} message[N];

void *msgrcv_pthreads (void* ptr) {
	int *i = (int*) ptr;		
	key_t key2 = ftok("q", 'b');
	int id2 = msgget(key2, 0);

	msgrcv(id2, &message[*i-1], sizeof(message)*N, *i, 0);
	printf("Recieved time[%d]: %s\n", *i-1, message[*i-1].mtext);	
	}

int main() {
	
	pthread_t tid[N];

	key_t key1;	
	key1 = ftok("q", 'a');
	int id1 = msgget(key1, 0); 

	for (int i=0; i<N; i++) {
		message[i].mtype = i+1;	
		printf("Sending %d message...\n", i);
		sleep(1);
		msgsnd(id1, &message[i], sizeof(message)*N, 0);	
	}

	int arr[N];
	for (int i=0; i<N; i++) {
		arr[i]=i+1;	
		pthread_create(&tid[i], NULL, msgrcv_pthreads, (void*)&arr[i]);
	}

	for (int i=0; i<N; i++)
		pthread_join(tid[i], NULL);

	key_t key2 = ftok("q", 'b'); //this
	int id2 = msgget(key2, 0);   //part
	msgctl (id1, IPC_RMID, NULL);//will be
	msgctl (id2, IPC_RMID, NULL);//changed

	return 0;
}
