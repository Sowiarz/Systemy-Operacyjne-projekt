#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <ctype.h>
#include <string.h>
#include <sys/shm.h>

#define SIZE 256

pthread_t id_th[3];
key_t key, klucz_pamieci_wsp;
int id_sem;
char buf[SIZE];
struct sembuf writer;
struct sembuf reader;
int id_pamieci_wsp;
char * shm;
int symbol_count;
short sus_reader = 0;
short sus_processor = 0;
short sus_output = 0;
char *buf_pamiec_wsp;

struct bufor_shm
{
	char bufor[SIZE];
	
} bufor_shm;

int licz_znaki(char* str)
{
  	int licznik = 0;
 
  	while(*str)
  	{
  		if(!isspace(*str++))
   		licznik++;
  	}
 
 return licznik;
}

void* thr_reader(void * par){
	
	
	#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <ctype.h>
#include <string.h>
#include <sys/shm.h>

#define KANAL_KOLEJKI 56789
#define ROZ_PAM_WSP 1024

pid_t tid[3];
pthread_t id_watki[3];

key_t klucz_pamieci_wsp;
int id_pamieci_wsp;
char * buf_pamiec_wsp;

key_t klucz_semafory;
int id_semafory;
struct sembuf semafor;

union semun {
               int              val;    
               struct semid_ds *buf;    
               unsigned short  *array;  
               struct seminfo  *__buf;  
           };

union semun inicjalizacja_semafor;

int id_kolejki[2];

struct komunikat
 {
	long typ;
	long int TID;
	int stan_czytajacy;
	int stan_pobierajacy;
	int stan_wypisujacy;
 } komunikat;

int watek_pomoc = 0;
int stan = 1;
struct komunikat stan_watkow = {0,0,1,1,1}; 

int licz_znaki(char* str)
{
 	int licznik = 0;
 
 	while(*str)
 	{
  		if(!isspace(*str++))
   		licznik++;
 	}
 
 return licznik;
}

void ustaw_semafor()
{
	klucz_semafory = ftok("/home/Sowiarz/Desktop/", 'Z');
	id_semafory = semget(klucz_semafory, 1, IPC_CREAT | 0666);
	inicjalizacja_semafor.val = 1;
	semctl(id_semafory,0,SETVAL,inicjalizacja_semafor);
}

/*
void usr1()
{	

}

void usr2()
{

}

void cont()
{

}

void sygnal_sigtstp()
{
	exit(0);

	//TO DO: KONIECZNE ZWALNIANIE PAMIECI WSPOLDZIELONEJ I KOLEJEK KOMUNIKATOW!!!
}

void sygnal()
{
	 if(signal(SIGTSTP, sygsem_flg = 0;nal_sigtstp) == SIG_ERR || signal(SIGUSR1, usr1) == SIG_ERR || signal(SIGUSR2, usr2) == SIG_ERR || signal(SIGCONT, cont) == SIG_ERR)
		printf("Blad przechwytywania sygnalu!\n");
}
*/

void * czytajacy(void * wejscie)
{
	tid[0] = syscall(SYS_gettid);
	char bufor[ROZ_PAM_WSP];

	while(stan_watkow.stan_czytajacy)
	{
		semafor.sem_num = 0;
		semafor.sem_op = -1;
		semafor.sem_flg = 0;

		semop(id_semafory,&semafor,1); //opuszczenie semafora

		printf("TID (0): %ld\n",tid[0]);
		printf("Wpisz tekst: \n");
		gets(&bufor);

		strncpy(buf_pamiec_wsp, bufor, ROZ_PAM_WSP);

		semafor.sem_num = 0;
		semafor.sem_op = 1;
		semafor.sem_flg = 0;

		semop(id_semafory,&semafor,1); //podniesienie semafora
	}
}

void * pobierajacy(void * wejscie)
{	
	sleep(3);

	tid[1] = syscall(SYS_gettid);
	char bufor[ROZ_PAM_WSP];
	int pomoc_liczba_znakow;

	while(stan_watkow.stan_pobierajacy)
	{
		semafor.sem_num = 0;
		semafor.sem_op = -1;
		semafor.sem_flg = 0;

		semop(id_semafory,&semafor,1); //opuszczenie semafora

		strncpy(bufor,buf_pamiec_wsp,ROZ_PAM_WSP);

		printf("Watek pobierajacy - odczytano: \n");
		printf("%s",bufor);
		printf("\n");

		pomoc_liczba_znakow = licz_znaki(bufor);
		printf("Watek pobierajacy - liczba znakow: %d\n",pomoc_liczba_znakow);

		sprintf(bufor, "%d", pomoc_liczba_znakow);

		strncpy(buf_pamiec_wsp,bufor,ROZ_PAM_WSP);

		semafor.sem_num = 0;
		semafor.sem_op = 1;
		semafor.sem_flg = 0;

		semop(id_semafory,&semafor,1); //podniesienie semafora
	}
}

void * wypisujacy(void * wejscie)
{
	sleep(6);

	tid[2] = syscall(SYS_gettid);
	char bufor[ROZ_PAM_WSP];

	while(stan_watkow.stan_wypisujacy)
	{
		semafor.sem_num = 0;
		semafor.sem_op = -1;
		semafor.sem_flg = 0;

		semop(id_semafory,&semafor,1); //opuszczenie semafora
		strncpy(bufor,buf_pamiec_wsp,ROZ_PAM_WSP);

		printf("Watek wypisujacy - odczytano liczbe znakow: ");
		printf("%s",bufor);

		semafor.sem_num = 0;
		semafor.sem_op = 1;
		semafor.sem_flg = 0;

		semop(id_semafory,&semafor,1); //podniesienie semafora
	}
}

int main(void)
{	
	int i = 0;

	ustaw_semafor();

	if((klucz_pamieci_wsp = ftok("/home/Sowiarz/Desktop/", 'H')) == -1)
	{
		printf("ERROR - FTOK!\n");
	}

	if((id_pamieci_wsp = shmget(klucz_pamieci_wsp, sizeof(int), IPC_CREAT|SHM_R|SHM_W) < 0))
	{
		printf("ERROR - SHMGET!\n");
	}
	
	if((buf_pamiec_wsp = shmat(id_pamieci_wsp, 0, 0)) == (char *) -1)
	{
		printf("ERROR - SHMAT!\n");
	}

	pthread_create(&id_watki[0], NULL, czytajacy, NULL);
	pthread_create(&id_watki[1], NULL, pobierajacy, NULL);
	pthread_create(&id_watki[2], NULL, wypisujacy, NULL);

	//sygnal();

	for(i = 0; i < 3; i++)
	{
		pthread_join(id_watki[i], NULL);
	}

	return 0;
}