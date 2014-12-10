/*Daniel Salo
CS 351 Prog Assignment 2

This program performs integer division with accuracy to any desired decimal place.
Each input consists of 4 positive integers: dividend a, divisor b, starting position m
and ending posion n, where M<=N.  The program divides a by b, and prints the mth through
nth positions of the result.  

The main method consists of a while loop that executes while the return value from scanf is 1,
or the value 0 is entered into the dividend.  The program is capable of handling up to a thousand
digits of both the characteristic and mantissa portions.  The characteristic is first computed and
converted from int type to char[] type with the sprintf function.  The decimal place is concatenated
to the new char[] string.  The mantissa is then calculated to 999 decimal places with a for loop, with each
iteration calculating one decimal place of the mantissa.  During this process, each decimal
place is converted from int to char form.  

The mantissa char[] array is concatenated to the previously created char[] array to create the 
solution to the division problem in char[] form.  The output is then displayed to the user to meet
the desired number of decimal places.  
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>

void concat(char s1[], char s2[])
{
	/*Custom concatenation function.  Concatenates char 2 to char 1.  */
	int i, j;

	i = strlen(s1);/*number of elements in array 1*/

	for (j = 0; s2[j] != '\0'; i++, j++) 
		s1[i] = s2[j];/*iterates through until null character is reached, so char[]2 can begin to be compied into char[]1*/

	s1[i] = '\0';/*null terminates the modified string*/
}

int main(void)
{
	long a, b, m, n;/*dividend, divisor, starting, ending characters initialized*/
	long quotientCharacteristic;/*used for storing the characteristic*/
	long remainder;/*used in storing the remainder before the first for loop, and during that loop*/
	long minuend, subtrahend;/*used during the for loop to calculate the subtraction operations needed in the division operations*/
	int quotientInt; /*used for storing the int value calculated for the mantissa values*/
	int i;/*loop counter*/
	char quotientMantissaString[2000], quotientWholeString[2000];/*for holding the complement and mantissa strings*/
	char quotientChar;
	char period[2] = ".";
	
	printf("\n*This program finds the correct desired place digits for the output of a division operation.*\n\n");
	
	int status = 1;  /*For while loop condition, assigned value of 1 and then from scanf for subsequent evaluations*/
	while (status == 1)
	{
		
		printf("\n*Enter values to continue program, or 0 to exit program.*\n\n");
		
		/*dividend input operation*/
		printf("\tDividend:        ");
		status = scanf("%d", &a);
		if (a == 0)/*for user termination*/
		{
			return 0;/*Terminate*/
		}
		
		/*Divisor input operation*/
		printf("\tDivisor:        ");
		scanf("%d", &b);
		while (b == 0)/*to prevent division by zero*/
		{
			printf("\tCannot divide by zero. Enter positive nonzero value:   ");
			scanf("%d", &b);
		}

		/*Startin digit input operation*/
		printf("\tStarting Digit:  ");
		scanf("%d", &m);
		while ((m <= 0) || (m >= 999))/*to prevent array index going out of bounds*/
		{
			printf("\tm digit must be between 1 and 999.  Try again:"   );
			scanf("%d", &m);
		}
		
		/*Ending digit input operation*/
		printf("\tEnding Digit:    ");
		scanf("%d", &n);
		while (n < m)/*ending digit should not be less than starting digit*/
		{
			printf("\tEnding digit must be equal to or greater than the starting digit.  Try again :   ");
			scanf("%d", &n);
		}
		while (n <= 0 || n >= 999)/*to prevent array index going out of bounds*/
		{
			printf("\tn digit must be between 1 and 999.  Try again:   ");
			scanf("%d", &n);
		}

		quotientCharacteristic = a / b; /*characteristic is easily calculated here.  */
		sprintf(quotientWholeString, "%d", quotientCharacteristic);/*characteristic converted form int to char[] type*/
		concat(quotientWholeString, period);/*decimal place is concatenated to the characteristic*/
		
		remainder = a % b;          /*values for first remainder and  minuend calculated*/
		minuend = remainder * 10;
		for (i = 0; i <= 999; ++i)  /*while index is <=999, taking into account the max length 
									of the characteristic, decimal place, and null termianate symbols*/
		{
			subtrahend = (minuend / b)*b;  /*subtrahend calculated*/
			quotientInt = minuend / b;		/*quotientint will always be 1 character, */
			quotientChar = (char)(((int)'0') + quotientInt);/*so we will convert the int into a char.  */
			quotientMantissaString[i] = quotientChar;/*and put the char into the index of the counter for the mantissa string*/
			minuend = minuend - subtrahend;  /*subtrahend is subtracted from the minuend and the result is then multiplied by 
											 10 for the next iteration.  */
			minuend = minuend * 10;
		}
		
		printf("\n\n"); 
		
		concat(quotientWholeString, quotientMantissaString);/*mantissa is concatenated to the string for the characteristic and 
															decimal place*/

		printf("\tPosition %d to position %d of %d/%d = ", m, n, a, b);
		
		for (i = m - 1; i < n; ++i)/*prints inclusivly between the startin and ending positions.*/
			printf("%c",quotientWholeString[i]);  
		
		printf("\n\tBecause %d/%d = ", a, b);

		for (i = 0; (i < n) || (i < 20); ++i) /*prints from the beginning of the output string to 20th digit, or the ending digit.  */
			printf("%c", quotientWholeString[i]);

		printf("...\n\n");
	}
}