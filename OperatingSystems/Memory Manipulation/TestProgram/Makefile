all: testsyscall 
testsyscall: testsyscall.c testsyscall.h
	gcc -std=c99 -o  testsyscall -include testsyscall.h testsyscall.c

HEADERS = testsyscall.h

default: testsyscall

testsyscall.o: testsyscall.c $(HEADERS)
	gcc -std=c99 -c testsyscall.c -o testsyscall.o

testsyscall: testsyscall.o
	gcc testsyscall.o -o testsyscall

clean:
	-rm -f *.o
	-rm -f testsyscall
