all: test-iosched
test-iosched: test-iosched.c
	gcc -std=c99 -o test-iosched -include test-iosched.c

default: test-iosched

test-iosched.o: test-iosched.c
	gcc -std=c99 -c test-iosched.c -o test-iosched.o

test-iosched: test-iosched.o
	gcc test-iosched.o -o test-iosched

clean:
	-rm -f *.o
	-rm -f test-iosched
