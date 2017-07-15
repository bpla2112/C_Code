/*
Author: Bernardo Pla
PID:3885008
COP 4338 Section U05
I affirm that this program is entirely my own work
and none of it is the work of any other person.
<Bernardo Pla>
*/

/*
This program is a simple integer calculator. 
This is designed to perform 5 operations: + , - , * , %
*/

#include <stdio.h>

int main()
{
    char operator;
    
    int number1;
    int number2;
    
    printf("Enter operator of + - * / or %% : "); //user input for operation. Polish Notation
    scanf("%c", &operator);
    
    printf("Enter two operands separated by a space: "); //user input for operands
    scanf("%i%i",&number1, &number2);
    
    switch(operator) {
        case '+': //addition
            printf("%i + %i = %i\n", number1, number2, number1+number2);
            break;
            
        case '-': //subtraction
            printf("%i - %i = %i\n", number1, number2, number1-number2);
            break;
            
        case '*': //multiplication
            printf("%i * %i = %i\n", number1, number2, number1*number2);
            break;
            
        case '/': //division
        	if(number2 == 0) //checking for User input error
        	{
        		printf("ERROR: DIVISION BY 0\nEXITING NOW\n");
        	}
        	else
        	{        	
            	printf("%i / %i = %i\n", number1, number2, number1/number2);
            }
            break;
            
        case '%': //mod
        	if(number2 == 0) //checking for User input error
        	{
        		printf("ERROR: MOD BY 0\nEXITING NOW\n");
        	}
        	else
        	{
        		printf("%i %% %i = %i\n", number1, number2, number1%number2);
        	}
        	break;
        	
        default:
            //operand is invalid
            printf("ERROR: INVALID OPERAND\nEXITING NOW\n");
            break;
    }
    return 0; //end of calculator program
}