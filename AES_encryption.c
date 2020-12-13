#include <stdio.h>
#include <string.h>

#define MAX_BUF 256

unsigned char getBit(unsigned char, int);
unsigned char setBit(unsigned char, int);
unsigned char clearBit(unsigned char, int);
unsigned char returnEndOfStringLiteral(unsigned char, int);
unsigned char processCounterValue(unsigned char counterValue, unsigned char keyValue);
unsigned char incrementByOne(unsigned char binaryNum);
unsigned char processSourceByte(unsigned char c, unsigned char counterValue);

/*
  Author:	
  Student#:	  
  Purpose:  A simple encryption program that uses an
  			implementation of incrementation counter,similar to 
			the Counter mode of the Advanced Encryption Standard algorithm
  Usage:	Use gcc to compile with the -o flag: "gcc -o output assignment1.c"
			Run program using "./output"
			Command Line arguments: (1), (2); where (1),(2) are single input numbers
			Then enter plaintext to encrypt for choice (1) or enter encrypted 
			sequence to de-crypt for choice (2) 
*/
int main()
{
	char str[8];
	int choice;
	unsigned char keyValue = 0b10110010;
	unsigned char counterValue = 0b00101000;
	unsigned char x;
	char message[MAX_BUF];
	// //char tempVar[MAX_BUF];

	printf("\nYou may:\n");
	printf("  (1) Encrypt a message \n");
	printf("  (2) Decrypt a message \n");
	printf("\n  what is your selection: ");
	fgets(str, sizeof(str), stdin);
	sscanf(str, "%d", &choice);
	printf("\n");
	//x = processCounterValue(counterValue, keyValue);

	//printf("%d", x);
	switch (choice)
	{

	case 1:
		printf("Please enter your plain-text message to be encrypted:\n");
		fgets(message, sizeof(message), stdin);
		//printf("%s", message);
		//scanf("%c", message);
		printf("\n");
		int messangeLen = strlen(message) - 1;
		int position;
		//printf("%d", messangeLen);
		for (position = 0; position < messangeLen; position++)
		{
			counterValue = processCounterValue(counterValue, keyValue);
			keyValue = incrementByOne(keyValue);
			counterValue = incrementByOne(counterValue);
			message[position] = processSourceByte(message[position], counterValue);
		}
		printf("\n");
		for (position = 0; position < messangeLen; position++)
		{
			printf("%d ", message[position]);
		}
		printf("-1\n");
		break;

	case 2:
		printf("Please enter your encrypted message to be de-crypted:\n");
		int count = 0;
		int number;
		while (1)
		{
			scanf("%d", &number);
			if (number == -1)
			{
				//message[count] = "\n";
				//message[count] = returnEndOfStringLiteral(number);
				break;
			}
			counterValue = processCounterValue(counterValue, keyValue);
			keyValue = incrementByOne(keyValue);
			counterValue = incrementByOne(counterValue);
			message[count] = processSourceByte(number, counterValue);
			printf("%c", message[count]);
			count++;
			//printf("%d", number);
		}
		printf("\n");
		//int messageLen = strlen(message);
		//rintf("%s", message);
		break;

		default:
			printf("\nSorry, you can only choose 1 or 2 as input, please try again");
			exit;
		}
	return 0;
}

/*
  Function:  processCounterValue
  Purpose:   process the counterValue with the keyValue as described by (1)
       in:   byte of counterValue
       in:   byte of keyValue
   return:   byte value of processed counterValue byte
*/
// Part (1) of the algorithm
unsigned char processCounterValue(unsigned char counterValue, unsigned char keyValue)
{
	int position, bitPosition1, bitPosition2;
	unsigned char bit1;
	unsigned char bit2;
	int exOR = 0;
	unsigned char returnBitVal = 0;
	// (b)
	for (position = 7; position >= 0; position--)
	{
		// (a)
		bitPosition1 = position;

		if (getBit(keyValue, position))
		{
			bitPosition2 = ((position + 1) % 8);
		}
		else
		{
			bitPosition2 = ((position + 2) % 8);
		}

		bit1 = getBit(counterValue, bitPosition1);
		bit2 = getBit(counterValue, bitPosition2);
		exOR = (((bit1 ^ bit2)));

		if (exOR)
		{
			returnBitVal = setBit(counterValue, position);
		}
		else
		{
			returnBitVal = clearBit(counterValue, position);
		}
	}
	return returnBitVal;
}

/*
  Function:  incrementByOne
  Purpose:   increment the input byte by a value 1 as decribed in (2), (3)
       in:   byte of key or counter
   return:   byte value that has been incremented by a value of 1
*/
unsigned char incrementByOne(unsigned char binaryNum)
{
	unsigned char binaryOne = 0b00000001;
	while (binaryOne != 0)
	{
		unsigned char carry = binaryNum & binaryOne;
		binaryNum = binaryNum ^ binaryOne;
		binaryOne = carry << 1;
	}
	return binaryNum;
}

/*
  Function:  processSourceByte
  Purpose:   process the source byte with the counter value as described by (4)
       in:   byte of character of plain/encrypted text
       in:   byte of counter value
   return:   byte value of processed source byte using the counter value
*/
unsigned char processSourceByte(unsigned char c, unsigned char counterValue)
{
	unsigned char tempCharValue = c;
	unsigned char sourceBit = 0;
	unsigned char counterBit = 0;
	unsigned char exOR = 0;
	unsigned char remainder = counterValue % 9;
	if (remainder < 3)
	{
		for (int position = 0; position < 8; position++)
		{
			if (position % 2 == 0)
			{
				sourceBit = getBit(c, position);
				counterBit = getBit(counterValue, position);
				exOR = ((sourceBit ^ counterBit) & 1);

				if ((exOR))
				{
					tempCharValue = setBit(tempCharValue, position);
				}
				else
				{
					tempCharValue = clearBit(tempCharValue, position);
				}
			}
			return tempCharValue;
		}
	}
	else if (remainder <= 5 && remainder >= 3)
	{
		for (int position = 1; position < 8; position++)
		{
			if (position % 2 == 0)
			{
				sourceBit = getBit(c, position);
				counterBit = getBit(counterValue, position);
				exOR = ((sourceBit ^ counterBit) & 1);

				if ((exOR))
				{
					tempCharValue = setBit(tempCharValue, position);
				}
				else
				{
					tempCharValue = clearBit(tempCharValue, position);
				}
			}
			return tempCharValue;
		}
	}
	else if (remainder > 5)
	{
		for (int position = 0; position < 8; position++)
		{

			sourceBit = getBit(c, position);
			counterBit = getBit(counterValue, position);
			exOR = ((sourceBit ^ counterBit));

			if ((exOR))
			{
				tempCharValue = setBit(tempCharValue, position);
			}
			else
			{
				tempCharValue = clearBit(tempCharValue, position);
			}
			return tempCharValue;
		}
	}
	return tempCharValue;
}

/*
  Function:  getBit
  Purpose:   retrieve value of bit at specified position
       in:   character from which a bit will be returned
       in:   position of bit to be returned
   return:   value of bit n in character c (0 or 1)
*/
unsigned char getBit(unsigned char c, int n)
{
	return ((c & (1 << n)) >> n);
}

/*
  Function:  setBit
  Purpose:   set specified bit to 1
       in:   character in which a bit will be set to 1
       in:   position of bit to be set to 1
   return:   new value of character c with bit n set to 1
*/
unsigned char setBit(unsigned char c, int n)
{
	return (c | (1 << n));
}

/*
  Function:  clearBit
  Purpose:   set specified bit to 0
       in:   character in which a bit will be set to 0
       in:   position of bit to be set to 0
   return:   new value of character c with bit n set to 0
*/
unsigned char clearBit(unsigned char c, int n)
{
	return (c & (~(1 << n)));
}
