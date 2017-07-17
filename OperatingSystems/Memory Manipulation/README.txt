README - Lab 3: Memory Management
By: Bernardo Pla, Ruben Valdes, Alejandro Thornton

NOTES (do not include in final report):

-slob.c Makefile is the Kernel's Makefile. Since it was already a compilation target, there was no need to modify the Makefile for this 

-first fit system call for free memory did not work as intended. 
--in theory, first fit is a faster algorithm but will have more equal amounts of claimed and free memory due to increased fragmentation. 

-best fit algorithm is a slower algorithm due to the fact that it searches for the perfect block of memory when allocating. 
--however, amount of memory free is much higher than the amount of memory that was claimed due to lack of fragmentation compared to first fit. 
--slowness of best fit algorithm can be seen when you try to compile the kernel after this algorithm has been implemented. 

-we did have trouble and used cited source for assistance

Citation:
[1]GitHub, 2017. [Online]. Available: https://github.com/fusion2004/cop4610/blob/master/lab3/slob.c. 