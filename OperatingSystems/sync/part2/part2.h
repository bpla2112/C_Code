#ifndef PART2_H
#define PART2_H

int Speaker();
int Reporter(int id);
void AnswerStart();
void AnswerDone();
void EnterConferenceRoom(int id);
void LeaveConferenceRoom(int id);
void QuestionStart(int id);
void QuestionDone(int id);

void SpeakerThread(void *args);
void ReporterThread(void *args);

#endif
