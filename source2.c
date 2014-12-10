/*Daniel Salo
CS 351 Prog Assignment 2, CS 390 Clean Code Assignment
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>


long enterDividend()
{
	long dividend;

	printf("\n*Enter values to continue program, or 0 to exit program.*\n\n");
	printf("\tDividend:        ");
	scanf("%d", &dividend);
	return dividend;
}

long enterDivisor()
{
	long divisor;
	printf("\tDivisor:        ");
	scanf("%d", &divisor);
	while (divisor < 1)
	{
		printf("\tCannot divide by anything < 1. Enter positive nonzero value:   ");
		scanf("%d", &divisor);
	}
	return divisor;
}

long enterStartingCharacter()
{
	long startingCharacter;
	printf("\tStarting Digit:  ");
	scanf("%d", &startingCharacter);
	while ((startingCharacter <= 0) || (startingCharacter >= 999))/*Prevent array index going out of bounds*/
	{
		printf("\tStarting digit must be between 1 and 999.  Try again:");
		scanf("%d", &startingCharacter);
	}
	return startingCharacter;
}

long enterEndingCharacter(long startingCharacter)
{
	long endingCharacter;
	printf("\tEnding Digit:    ");
	scanf("%d", &endingCharacter);
	while (endingCharacter < startingCharacter)
	{
		printf("\tEnding digit must be equal to or greater than the startingCharacter digit.  Try again :   ");
		scanf("%d", &endingCharacter);
	}
	while (endingCharacter <= 0 || endingCharacter >= 999)/*Prevent array index going out of bounds*/
	{
		printf("\tEnding digit must be between 1 and 999.  Try again:   ");
		scanf("%d", &endingCharacter);
	}
	return endingCharacter;
}

void insertQuotientCharacteristicIntoString(long dividend, long divisor, char quotientWholeString[])
{
	int quotientCharacteristic = dividend / divisor;
	sprintf(quotientWholeString, "%d", quotientCharacteristic);/*characteristic converted form int to char[] type*/
}
void concatPeriodtoCharacteristic(char s1[], char s2[])
{
	int i, j;
	i = strlen(s1);
	for (j = 0; s2[j] != '\0'; i++, j++)
		s1[i] = s2[j];
	s1[i] = '\0';
}

void concatMantissaToCharacteristic(char s1[], char s2[])
{
	int i, j;
	i = strlen(s1);
	for (j = 0; s2[j] != '\0'; i++, j++) 
		s1[i] = s2[j];
	s1[i] = '\0';
}

int calculateMinuend(long remainder, long dividend, long divisor, long minuend)
{
	remainder = dividend % divisor;
	minuend = remainder * 10;
	return minuend;
}

void calculateAndPopulateMantissaString(int subtrahend, int minuend, int divisor, char quotientChar, int quotientInt, char quotientMantissaString[])
{
	int i = 0;
	for (i = 0; i <= 999; ++i)
	{
		subtrahend = (minuend / divisor)*divisor;
		quotientInt = minuend / divisor;
		quotientChar = (char)(((int)'0') + quotientInt);/*we will convert the int into a char.  */
		quotientMantissaString[i] = quotientChar;
		minuend = minuend - subtrahend;
		minuend = minuend * 10;
	}
}

void printUsersStringPositions(int startingCharacter,int endingCharacter,int dividend, int divisor, char quotientWholeString[])
{
	int i = 0;
	printf("\n\n\tPosition %d to position %d of %d/%d = ", startingCharacter, endingCharacter, dividend, divisor);
	for (i = startingCharacter - 1; i < endingCharacter; ++i)
		printf("%c", quotientWholeString[i]);
	printf("\n");
}

void printWholeString(int endingCharacter, char quotientWholeString[], int dividend, int divisor)
{
	int i = 0;
	printf("\n\tBecause %d/%d = ", dividend, divisor);
	for (i = 0; (i < (endingCharacter + 3)) || (i < 20); ++i)
		printf("%c", quotientWholeString[i]);
	printf("...\n\n");
}



int main(void)
{
	long dividend, divisor, startingCharacter, endingCharacter;
	long minuend = 0, subtrahend = 0, remainder = 0;
	int quotientInt = 0;												
	char quotientMantissaString[2000], quotientWholeString[2000];
	char quotientChar ='z';
	char period[2] = ".";
	
	printf("\n*This program finds the correct desired place digits for the output of a division operation.*\n\n");
	 
	while (1)
	{
		dividend = enterDividend();
		if (dividend == 0)
		{
			return 0;
		}
		divisor = enterDivisor();
		startingCharacter = enterStartingCharacter();
		endingCharacter = enterEndingCharacter(startingCharacter);

		insertQuotientCharacteristicIntoString(dividend, divisor, quotientWholeString);
		
		concatPeriodtoCharacteristic(quotientWholeString, period);
		
		calculateAndPopulateMantissaString(subtrahend, calculateMinuend(remainder, dividend, divisor, minuend), divisor, quotientChar, quotientInt, quotientMantissaString);
		
		concatMantissaToCharacteristic(quotientWholeString, quotientMantissaString);

		printUsersStringPositions(startingCharacter, endingCharacter, dividend, divisor, quotientWholeString);
		
		printWholeString(endingCharacter, quotientWholeString, dividend, divisor);
	}
}