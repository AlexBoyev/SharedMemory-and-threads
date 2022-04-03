/* Alexander boyev 314393158
   Genady yolgin 321983413 */
#include <unistd.h>
#include <wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/ipc.h>
#include<math.h> 
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define SEGSIZE 100

long getPower(int a,int b){
    long result = 1;
    int i = 1;
    
    while(i <= b)
    {
        result *= a;
        i++;
    }

	return result;
}

int main(){


	//*********************************************************
	key_t key;
        int   shmid;
        int*  scanned;
		int r_pid;
         key = ftok(".", 'T');
        if((shmid = shmget(key, SEGSIZE,IPC_CREAT|IPC_EXCL|0666))== -1) 
       {
                if((shmid = shmget(key, SEGSIZE, 0)) == -1) 
                {perror(" bad shmget"); exit(1);             }
        }
        else
        {     printf("Creating new shared memory segment\n");        }
        if((scanned = shmat(shmid, 0, 0)) == NULL)
        {          perror("shmat");                exit(1);        }
	
	//*************************************************************
	pid_t pid;
	int i;
	int status;
	int result;
	time_t t;
	long power;
	int num1;
	int num2;
	int father_pid = getpid();
	for(i = 0; i < 2 ; i ++ ){
		pid = fork();
		if(pid == 0){
			srand((unsigned) time(&t));
			result = rand() % 15;
			scanned[i] = result;
			return 0;
		}
		else{
			sleep(1);
		}
	}

	for(i = 0 ; i < 2 ; i++){
		waitpid(-1,&status,WUNTRACED);

	}

	if(father_pid == getpid()){
		num1 = scanned[0];
		num2 = scanned[1];
		printf("base number is: %d\n",num1);
		printf("exponent number is: %d\n",num2);	
		printf("the result is: %ld.\n",getPower(num1,num2));
	}

	return 0;
}
