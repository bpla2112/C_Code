/*Alejandro Thornton, Bernardo Pla, Ruben Valdes */
/*COP 4610 Lab 2, Spring 2017*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int SharedVariable = 0;

void SimpleThread(int threadID) {
	int num, val;

	for(num = 0; num < 20; num++) {
		if(random() > RAND_MAX / 2)
			usleep(10);

		val = SharedVariable;
		printf("*** thread %d sees value %d\n", threadID, val);
		SharedVariable = val + 1;
	}

	val = SharedVariable;
	printf("Thread %d sees final value %d\n", threadID, val);
}

void printUsage(char *application){
printf("usage: %s <# of threads to run>\n", application);
printf("The number of threads to run must be an integer.\n");
}

void printInputError(){
printf("Error\n");
}

int main(int argc, char *argv[])
{
	if(argc !=2) {
		printUsage(argv[0]);
		return -1;
	}

	int threadcount = atoi(argv[1]);
	
	char check_it[strlen(argv[1]) + 1];
	sprintf(check_it, "%d", threadcount);

	if(strcmp(argv[1], check_it) !=0 || threadcount <= 0){
		printInputError();
		return -1;
	}

	int i;
	pthread_t th_id[threadcount+1];

	for(i = 1; i <= threadcount; i++){
		if(pthread_create(&th_id[i], NULL, (void *)&SimpleThread, (void *)i)){
		printf("Error: Thread not created %d\n", i);
		return-1;
		}
	}

	for(i=1; i<= threadcount; i++){
		if(pthread_join(th_id[i], NULL)){
			printf("Error: Thread not joined %d\n", i);
			return -1;
		}
	}

	return 0;
}




