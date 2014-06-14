#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/ipc.h>
pthread_t id_th[3];
int main (void)
{	
	int i = 0;
	pthread_create(&id_th[0], NULL, read, NULL);
	pthread_create(&id_th[1], NULL, download, NULL);
	pthread_create(&id_th[2], NULL, write, NULL);

	for(i=0; i<3; i++)
	{
		pthread_join(id_th[i], NULL);
	}
	
	return 0;
}