/*
Author: Bernardo Pla
PID:3885008
COP 4338 Section U05
I affirm that this program is entirely my own work
and none of it is the work of any other person.
<Bernardo Pla>
*/

#include <stdio.h>

int main()
{
	char itemnum1[] = "00034523";
	char itemnum2[] = "00747482";
	char itemnum3[] = "00098754";
	char itemnum4[] = "00234234"; 
	char itemnum5[] = "00012415"; //My data input value

	char item1[] = "Bookshelf";
	char item2[] = "Pen";
	char item3[] = "Chair";
	char item4[] = "Camera";
	char myitem[] = "Jeep"; //my data input value
	
	double price1 = 79.50;
	double price2 = 2.99;
	double price3 = 129.99;
	double price4 = 1295.40;
	double myprice = 22050.97; //my data input value
	
	int count1 = 4;
	int count2 = 100;
	int count3 = 6;
	int count4 = 3;
	int mycount = 7; //my data input value
	
	double exprice1 = price1 * count1;
	double exprice2 = price2 * count2;
	double exprice3 = price3 * count3;
	double exprice4 = price4 * count4;
	double myexprice = myprice * mycount; //my data input value
	
	//the following is the formatted data
	printf("Item Num\t Description\t Price\t Count\t Extended Price\n");
	printf("%s\t %s    $%7.2f\t %d\t $%7.2f\n", itemnum1, item1, price1, count1, exprice1);
	printf("%s\t %s\t      $%7.2f\t %d\t $%7.2f\n", itemnum2, item2, price2, count2, exprice2);
	printf("%s\t %s\t      $%7.2f\t %d\t $%7.2f\n", itemnum3, item3, price3, count3, exprice3);
	printf("%s\t %s\t      $%7.2f\t %d\t $%7.2f\n", itemnum4, item4, price4, count4, exprice4);
	printf("%s\t %s\t      $%7.2f\t %d\t $%7.2f\n", itemnum5, myitem, myprice, mycount, myexprice);
	
	return 0;	
}
