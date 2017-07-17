#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	long inputSize;
	char *testBuffer;
	size_t inputResult;
	size_t outputResult;

	if(argc != 3)
	{
		fprintf(stderr, "INVALID ARGS. Usage is: <program> <file> <cpy>");
		return -1;
	}

	char *infile = argv[1];
	char *outfile = argv [2];

	FILE *infilePoint = fopen(infile, "rb");
	FILE *outfilePoint = fopen(outfile, "wb+");
	fseek(infilePoint, 0, SEEK_END);
	inputSize = ftell(infilePoint);
	rewind(infilePoint);

	testBuffer = (char*) malloc(sizeof(char) * inputSize);
	
	if(testBuffer == NULL)
	{
		fprintf(stderr, "ERROR: NO BUFFER TO ALLOCATE\n");
		return -1;
	}

	inputResult = fread(testBuffer, 1, inputSize, infilePoint);

	if(inputResult != inputSize)
	{
		fprintf(stderr, "ERROR: FILE UNREADABLE \n");
		return -1;
	}
	
	fclose(infilePoint);

	outputResult = fwrite(testBuffer, 1, inputSize, outfilePoint);

	if(inputResult != inputSize)
	{
		fprintf(stderr, "ERROR: FILE UNWRITEABLE \n");
		return -1;
	}

	fclose(outfilePoint);
	free(testBuffer);
	
	return 0;
}
