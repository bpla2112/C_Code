/*
Author: Bernardo Pla
PID:3885008
COP 4338 Section U05
I affirm that this program is entirely my own work
and none of it is the work of any other person.
<Bernardo Pla>
*/

/*
This program performs operations on arrays. Input comes
from a text file.  This will sort
and add all the odd and even numbers. The results are 
printed to an output file
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int fromfile(char *arr[], int arraylength);
int sortbyasc(char *arr[], int size, FILE *fp);
int oddsum(char *arr[], int size, FILE *fp);
int evensum(char *arr[], int size, FILE *fp);

int main(int argc, char *argv[])
{
	char *nums[100];
	int hold = 0;
	int arraylength = 100; 
	int counter = 0;
	int filled = 0;
	FILE *fp;
	
	hold = fromfile(nums, arraylength) + hold;
	
	//following used for validation
	while(nums[counter] != NULL)
	{
		printf("%s\n", nums[counter]);
		counter++;
		if(nums[counter] == NULL)
		{
			filled = counter;
			printf("Has been filled\n");
		}
	}
	
	printf("Filled %d\n", filled);
	hold = sortbyasc(nums, filled, fp);
	hold = oddsum(nums, filled, fp);
	hold = evensum(nums, filled, fp);
	printf("\n"); //spacing in program
	
	if (hold > 0)
	{
		return -1; 
	}
	else
	{
		return 0; //end program		
	}	
}

//next blocks are for methods

//retrieve numbers from infile.txt
int fromfile(char *arr[], int arraylength)
{
	char filepath[256]; //commonly looks like "C:\...\..." this varies depending on machine
	int arraysize = arraylength;
	
	if((getcwd(filepath, sizeof(filepath)) != NULL))
	{
		FILE *fp; 
		char name[20];
		
		strcpy(name, "/infile.txt"); //copy the fp to destination
		strcat(filepath, name);

		//open the fp for read mode
		fp = fopen(filepath, "r");
		
		if(!fp)
		{
			printf("ERROR: FILE NOT FOUND\n EXITING NOW");
			return -1;
		}
		
		char storage[arraysize];
		
		while(fgets(storage, arraysize, fp))
		{
			char *token = NULL;
			
			printf("String %s\n", storage);
			token = strtok(storage, " ");
			int i = 0;
			
			while (token != NULL)
			{
				printf("number from fp: %s\n", token);
				arr[i] = malloc(strlen(token) + 1);
				strcpy(arr[i], token);
				i++;
				token = strtok(NULL, " ");
			}
		}
		
		//we are now done with the fp read. it must be closed
		fclose(fp);
		return 0;
	}
	return -1;
}

int sortbyasc(char *arr[], int size, FILE *fp)
{
	int counter = 0;
	int ascendingi[size];
	
	while(arr[counter] != NULL)
	{
		ascendingi[counter] = atoi(arr[counter]);
		counter++;
		
		if(arr[counter] == NULL)
		{
			printf("Process Reached\n");
		}
	}
	
	int looping; //this will help for our upcoming loops for sorting the arr
	for(counter = 0; counter < size - 1; counter++)
	{
		for(looping = 0; looping < size - 1; looping++) 
		{
			if(ascendingi[counter] < ascendingi[looping])
			{
				int temp = ascendingi[counter];
				ascendingi[counter] = ascendingi[looping];
				ascendingi[looping] = temp;
			}
		}
	}
	
	char filepath[1024]; //allocated for the retrieval of the file in directory
	
	if(getcwd(filepath, sizeof(filepath)) != NULL)
	{
		char name[40];
		stpcpy(name, "/outfile.txt");
		strcat(filepath, name);
		
		//open our outfile fp
		fp = fopen(filepath, "a+"); //open the fp for appending
		fprintf(fp, "%s\n", "Ascending Sort ");
		for(looping = 0; looping < size - 1; looping++)
		{
			fprintf(fp, "%d ", ascendingi[looping]);
		}
		fprintf(fp, "\n");
		fclose(fp); //close the fp
		return 0;
	}
	else
	{
		return -1;		
	}
}

int oddsum(char *arr[], int size, FILE *fp)
{
	int counter = 0; //set counter to 0 for this function
	int ascendingi[size];
	
	while(arr[counter] != NULL) //looking for NULL to imply EOF
	{
		ascendingi[counter] = atoi(arr[counter]);
		counter++;
		
		if(arr[counter] == NULL)
		{
			printf("Process Reached\n");
		}
	}
	
	int looping; //loopcounter
	for(counter = 0; counter < size - 1; counter++)
	{
		for(looping = 0; looping < size - 1; looping++)
		{
			if(ascendingi[counter] < ascendingi[looping])
			{
				int temp = ascendingi[counter];
				ascendingi[counter] = ascendingi[looping];
				ascendingi[looping] = temp;
			}
		}
	}
	
	//retrieve directory of fp
	char filepath[1024]; //allocation
	if(getcwd(filepath, sizeof(filepath)) != NULL)
	{
		char name[40];
		strcpy(name, "/outfile.txt");
		strcat(filepath, name);
		
		fp = fopen(filepath, "a+"); //open in appending mode
		fprintf(fp, "%s\n", "SumOdds");
		
		int odd = 0;
		
		for(looping = 0; looping < size - 1; looping++)
		{
			if(ascendingi[looping] % 2 != 0) //filter out odd numbers by definition
			{
				odd = odd + ascendingi[looping]; //odd is initialized to 0. First iteration is 0 + ascendingi[looping]
				
			}
		}
		fprintf(fp, "%d\n", odd);
		fclose(fp);
		return 0;
	}
	else
	{
		return -1;
	}
}

int evensum(char *arr[], int size, FILE *fp)
{
	int counter = 0;
	int ascendingi[size];
	
	while(arr[counter] != NULL)
	{
		ascendingi[counter] = atoi(arr[counter]); 
		counter++;
		if(arr[counter] == NULL)
		{
			printf("Process Reached\n");
		}
	}
	
	int looping;
	for(counter = 0; counter < size - 1; counter++)
	{
		for(looping = 0; looping < size - 1; looping++)
		{
			if(ascendingi[counter] < ascendingi[looping])
			{
				int temp = ascendingi[counter];
				ascendingi[counter] = ascendingi[looping];
				ascendingi[looping] = temp;
			}
		}
	}
	
	char filepath[1024];
	if(getcwd(filepath, sizeof(filepath)) != NULL)
	{
		char name[40];
		stpcpy(name, "/outfile.txt");
		strcat(filepath, name);
		fp = fopen(filepath, "a+"); //appending mode
		fprintf(fp, "%s\n", "Even Count");
		
		int counter = 0; 
		for(looping = 0; looping < size - 1; looping++)
		{
			if(ascendingi[looping] % 2 == 0) //definition of even numbers
			{
				counter++;
			}
		}
		fprintf(fp, "%d\n", counter);
		fclose(fp);
		return 0; 
	}
	else
	{
		return -1;
	}
}
