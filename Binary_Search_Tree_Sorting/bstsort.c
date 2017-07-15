/*
Author: Bernardo Pla
PID:3885008
COP 4338 Section U05
I affirm that this program is entirely my own work
and none of it is the work of any other person.
<Bernardo Pla>
*/

/*
This program creates and sorts a Binary Search Tree. 
The values sorted in the BST are all string types
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <malloc.h>
#include <unistd.h>
#include <string.h>

//indicate a new data type of node
struct node
{
	int notunique;
	char* datastream;
	struct node* lside; //left of node
	struct node* rside; //right of node
};

struct node* insert(struct node* center, char* datastream, int cflag)
{
	if(center == NULL)
	{
		struct node* temppoint = malloc(sizeof(struct node));
		temppoint->notunique = 0;
		temppoint->datastream = datastream;
		temppoint->lside = NULL;
		temppoint->rside = NULL;
		return temppoint;
	}
	else
	{
		if(cflag)
		{
			if(casesensitive(datastream, center->datastream) < 0)
			{
				center->lside = insert(center->lside, datastream, cflag);
			}
			else if(casesensitive(datastream, center->datastream) > 0)
			{
				center->rside = insert(center->rside, datastream, cflag);
			}
			else
			{
				center->notunique++;
			}
			return center;
		}
		 else 
		{
			if(caseinsensitive(datastream, center-> datastream) < 0)
			{
				center->lside = insert(center->lside, datastream, cflag);
			}
			else if(caseinsensitive(datastream, center->datastream) > 0)
			{
				center->rside = insert(center->rside, datastream, cflag);
			}
			else
			{
				center->notunique++;
			}
			return center;
		} 
	
	}
}


//meant to free memory occupied by the tree
int freethetree(struct node* center)
{
	if(center == NULL)
	{
		return 0;
	}
	freethetree(center->rside);
	freethetree(center->lside);
	free(center);
}

int main(int argc, char* argv[])
{
	FILE* infile;
	FILE* outfile;
	int cflag = 0;
	int oflag = 0;
	char* in = 0;
	char* out = 0;
	int command; 	
	char tempstorage[1024];	
	struct node* center = 0; 
	
	//next section enables logic to parse the command line
	while((command = getopt(argc, argv, "co:")) != -1)
	{
		switch(command)
		{
			case 'c':
					cflag = 1;
					break;
			
			case 'o':
					oflag = 1;
					out = optarg;
					break;
				
			case '?':
					if (optopt == 'o')
					{
						fprintf(stderr, "Unknown argument: -%c requires an argument! \n", optopt);
					}
					else if (isprint(optopt))
					{
						fprintf(stderr, "Unknown Option", optopt);
					}
					else
					{
						fprintf(stderr, "Unknown Option: Cannot continue.\n", optopt);		
										
					}
					return 1;
				//break;
				
			default:
				abort();
		}
	}
	
	if (optind < (argc))
	{
		in = argv[optind];
	}
	
	if (in)
	{
		infile = fopen(in, "r");
		
		while(!feof(infile))
		{
			int i = 0;
			for(i = 0; i < 1024; i++)
			{
				tempstorage[i] = '\0';  
			}
			
			while(fgets(tempstorage, sizeof(tempstorage), infile) != NULL)
			{
				center = insert(center, strdup(tempstorage), cflag);
			}
		}
		fclose(infile);
	}
	else
	{
		printf("FILE NOT FOUND. Press CTRL-D for end of file. \n");
		
		while(fgets(tempstorage, sizeof(tempstorage), stdin) != NULL)
		{
			center = insert(center, strdup(tempstorage), cflag);
		}
	}
	
	if(out)
	{
		outfile = fopen(out, "w");
		fprintf(outfile, "Binary Tree OUTPUT: \n");
		orderingfile(outfile, center);
		fclose(outfile);
	}
	else
	{
		printf("Binary Tree Output: \n");
		order(center);
	}
	
	freethetree(center); //free the memory from the tree 
	return 0; //end of main 
}

//the function below compares strings. This is for case insensitive strings
int caseinsensitive(const char* stringa, const char* stringb)
{
	while(*stringa != '\0')
	{
		if(*stringb == '\0')
		{
			return 1; //stringa is larger than stringb
		}
		if(tolower(*stringa) > tolower(*stringb))
		{
			return 1; //stringa greater than stringb 
		}
		if(tolower(*stringb) > tolower(*stringa))
		{
			return -1; //stringb is greater than stringa
		}
		
		stringa++; //move strings to next character
		stringb++;
	}
	
	if(*stringb != '\0')
	{
		return -1; 
	}
	
	return 0; //end of function
}

//compare strings. case does matter 
int casesensitive(const char* stringa, const char* stringb)
{
	while(*stringa != '\0')
	{
		if(*stringb == '\0')
		{
			return 1; //stringa is larger than stringb
		}
		if(*stringa > *stringb)
		{
			return 1; //stringa greater than stringb 
		}
		if(*stringa < *stringb)
		{
			return -1; //stringb is greater than stringa
		}
		
		*stringa++; //move strings to next character
		*stringb++;
	}
	
	if(*stringb != '\0')
	{
		return -1; 
	}
	
	return 0; //end of function
}

int order(struct node* center)
{
	if(center == NULL)
	{
		return 0; 
	}
	order(center -> lside);
	
	int i = 0; 
	for(i = -1; i < center->notunique; i++)
	{
		printf("%s", center->datastream);
	}
	order(center->rside);
	
}

int orderingfile(FILE* fstream, struct node* center)
{
	if(center == NULL)
	{
		return 0;
	}
	orderingfile(fstream, center->lside);
	
	int i = 0;
	for(i = -1; i < center->notunique; i++)
	{
		fprintf(fstream, "%s", center->datastream);
	}
	orderingfile(fstream, center->rside);
}



