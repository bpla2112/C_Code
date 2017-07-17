#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "part1-syscall.h"

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barrier1;

int SharedVariable = 0;

void *SimpleThread(void *args)
{
	int num, val;
	int which = (int)args;

	for(num = 0; num < 20; num++){
#ifdef PTHREAD_SYNC
	if(random() > RAND_MAX / 2)
		usleep(10);
#endif
	pthread_mutex_lock(&mutex1);
	val = SharedVariable;
	printf("*** thread %d sees value %d\n", which, val);
	SharedVariable = val + 1;
	pthread_mutex_unlock(&mutex1);
	}

pthread_barrier_wait(&barrier1);

val = SharedVariable;
printf("Thread %d sees final value %d\n", which, val);
return 0;
}

int main (int argc, char *argv[])
{
	int num_threads = argc > 1 ? atoi(argv[1]) : 0;

	if(num_threads > 0){
	pthread_t threads[num_threads];
	int rc;
	long t;

	rc = pthread_barrier_init(&barrier1, NULL, num_threads);

	if(rc) {
	fprintf(stderr, "pthread_barrier_init: %s\n", strerror(rc));
	exit(1);
	}

	for(t = 0; t < num_threads; t++){
	printf("In main: creating thread %ld\n", t);
	rc = pthread_create(&threads[t], NULL, SimpleThread, (void* )t);
	if (rc) {
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		exit(-1);
		}
	}

	//CALL HERE
	printf("%ld\n", syscall(__NR_sys_pla_thornton_valdes));

	for (t = 0; t<num_threads; t++){
	pthread_join(threads[t], NULL);
	}
      }
   else{
	printf("ERROR: The parameter should be a valid positive number.\n");
	exit(-1);
	}
return 0;
}
