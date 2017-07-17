README Part 1 Simple Multi-thread Programming

1) Navigate to the part1 directory. This directory should have all you would need to compile the code. 

2) In the part1 directory. Type "make" (without quotation marks).
	a) This should create 3 executables called "part1-1", "part1-syncc", and "part1-syncc-syscall"

3) To execute part1-1:
	a) Type "./part1-1 N" where N is any arbitrary number
	b) Press Enter. You should see thread outputs of threads that do not use synchronization
	c) If you have an error, type "make clean" to clean the directory and go back to step 2
	
4) To execute part1-syncc:
	a) Type "./part1-syncc N" where N is any arbitrary number
	b) Press Enter. You should see the output of synchronized threads
	c) If you have an error, type "make clean" to clean the directory and go back to step 2
	
5) To execute part1-syncc-syscall (This code is a copy of part1-syncc with an extra line for the system call):
	a) Type "./part1-syncc-syscall N" where N is any arbitrary number
	b) Press Enter. You should see the same output as "part1-syncc"
	c) Type "dmesg" or "dmesg | tail" and press enter to see the system call output 
	d) If you have an error, type "make clean" to clean the directory and go back to step 2