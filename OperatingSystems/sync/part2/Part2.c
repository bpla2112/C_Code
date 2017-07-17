#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>	
#include "part2.h"

//Question_asker holds the ID of the reporter currently talking and is
//synched with the speak_mutex	
int question_asker = -1;	
int speaker_started = 0;
int num_conference;
//Places a limit for how many can be in the room	
sem_t conference_room_limit;
//Locks on the reporter speaking so that only one goes at a time
//along with locks on the speaker and reporter so that they can
//take turns talkings	
pthread_mutex_t speak_mutex;	
pthread_mutex_t floor_mutex;
pthread_cond_t floor_cond;
	
int main(int argc, char *argv[]) {
	if(argc != 3) {
	printf("usage: %s <number of reporter threads> <conference room capacity>\n", argv[0]);
	return 0;
	}
	else {
	int num_threads = atoi(argv[1]);
	num_conference = atoi(argv[2]);
	
	char check_num_threads[strlen(argv[1]) + 1];
	char check_num_conference[strlen(argv[2]) + 1];
	
	sprintf(check_num_threads, "%d", num_threads);
	sprintf(check_num_conference, "%d", num_conference);
	
	if(strcmp(argv[1], check_num_threads) != 0 ||
	strcmp(argv[2], check_num_conference) != 0 ||
	num_threads <= 0 ||
	num_conference <= 0) {
	printf("Error: Invalid input\n");
	return -1;
	}
	
	if(sem_init(&conference_room_limit, 0, num_conference) ||
	pthread_mutex_init(&speak_mutex, NULL) ||
	pthread_mutex_init(&floor_mutex, NULL) ||
	pthread_cond_init(&floor_cond, NULL)) {
	printf("Error: Could not initialize mutex\n");
	return -1;
	}
	
	int i;
	pthread_t speaker;
	pthread_t reporters[num_threads];
	
	pthread_mutex_lock(&floor_mutex);
	
	speaker = Speaker();
	if(speaker == 0) {
	printf("Error: Could not create the speaker thread.\n");
	return -1;
	}
	
	pthread_cond_wait(&floor_cond, &floor_mutex);
	
	speaker_started = 1;
	pthread_mutex_unlock(&floor_mutex);
	
	for(i = 0; i < num_threads; i++) {
	reporters[i] = Reporter(i);
	if(reporters[i] == 0) {
	printf("Error: Could not create reporter(%d) thread.\n", i);
	return -1;
	}
	}
	
	for(i = 0; i < num_threads; i++) {
	if(pthread_join(reporters[i], NULL)) {
	printf("Error: Could not join reporter(%d) thread.\n", i);
	return -1;
	}
	}
	
	}
	return 0;
	}
	
	int Speaker() {
	pthread_t thread;
	if(pthread_create(&thread, NULL, (void *)&SpeakerThread, NULL)) {
	return 0;
	}
	return thread;
	}
	
	int Reporter(int id) {
	pthread_t thread;
	if(pthread_create(&thread, NULL, (void *)&ReporterThread, (void *)id)) {
	return 0;
	}
	return thread;
	}
	
	void AnswerStart() {
	if(!speaker_started) {
	pthread_cond_signal(&floor_cond);
	}
	pthread_cond_wait(&floor_cond, &floor_mutex);
	
	printf("Speaker starts to answer question for reporter %d.\n", question_asker);
	}
	
	void AnswerDone() {
	printf("Speaker is done with answer for reporter %d.\n", question_asker);
	
	pthread_cond_signal(&floor_cond);
	}
	
	void EnterConferenceRoom(int id) {
	sem_wait(&conference_room_limit);
	printf("Reporter %d enters the conference room.\n", id);
	}
	
	void LeaveConferenceRoom(int id) {
	printf("Reporter %d leaves the conference room.\n", id);
	sem_post(&conference_room_limit);
	}
	
	void QuestionStart(int id) {
	pthread_mutex_lock(&speak_mutex);
	
	printf("Reporter %d asks a question.\n", id);
	question_asker = id;
	
	pthread_mutex_lock(&floor_mutex);
	pthread_cond_signal(&floor_cond);
	pthread_cond_wait(&floor_cond, &floor_mutex);
	}
	
	void QuestionDone(int id) {
	pthread_mutex_unlock(&floor_mutex);
	
	printf("Reporter %d is satisfied.\n", id);
	question_asker = -1;
	
	pthread_mutex_unlock(&speak_mutex);
	}
	
	void SpeakerThread(void *args) {
	pthread_mutex_lock(&floor_mutex);
	while(1) {
	AnswerStart();
	AnswerDone();
	}
	}
	
	void ReporterThread(void *args) {
	int id = (int)args;
	int questions = id % 4 + 2;
	
	EnterConferenceRoom(id);
	
	while(questions > 0) {
	QuestionStart(id);
	QuestionDone(id);
	
	questions--;
	}
	
	LeaveConferenceRoom(id);
	}
