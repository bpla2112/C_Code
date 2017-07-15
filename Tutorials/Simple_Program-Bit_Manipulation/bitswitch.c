#include <stdio.h>
#include <stdlib.h>

int main()
{
	int choice;
	int nvalue;
	int input;
	
	while(1) //create menu of choices for user
	{
		printf("1. Set bit n\n");
		printf("2. Reset bit n\n");
		printf("3. Check bit n\n");
		printf("4. Clear bit n\n");
		printf("5. Switch/Toggle bit n\n");
		printf("6. Quit\n");
		printf("What would you like to do?\n");
		scanf("%d", &choice); //scan for user input
		
		if(choice != 6)
		{
			printf("Please give an integer value \n");
			scanf("%d", &input);
			
			printf("Please give an n value\n");
			scanf("%d", &nvalue);
		}
	
	
	switch(choice)
	{
		case 1:
			input = input | (1 << nvalue);
			printf("Output: %d\n", input);
			break;
			
		case 2:
			input  = input & (~0);
			printf("Output: %d\n", input);
			break;
			
		case 3:
			input = input & (1 << nvalue);
			printf("Bit %d is %s\n", nvalue, input?"set":"not set");
			break;
			
		case 4:
			input = input & (~(1 << nvalue));
			printf("Output: %d\n", input);
			break;
			
		case 5:
			input = input ^ (1 << nvalue);
			printf("Output: %d\n", input);
			break;
			
		case 6:
			exit(0);
			break;
			
		default:
			printf("Invalid option. Please try again");
			break;
	}
}
	return 0;
}