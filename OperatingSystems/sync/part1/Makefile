all: part1-1 part1-syncc part1-syncc-syscall

clean:
	rm part1-1 part1-syncc part1-syncc-syscall

part1-1: part1-1.c
	gcc -pthread -o part1-1 part1-1.c

part1-syncc: part1-syncc.c
	gcc -pthread -o part1-syncc part1-syncc.c

part1-syncc-syscall: part1-syncc-syscall.c
	gcc -pthread -o part1-syncc-syscall part1-syncc-syscall.c
