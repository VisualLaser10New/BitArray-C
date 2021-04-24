/*	Visual Laser 10 New:
*
*	Developer:
*		-https://github.com/VisualLaser10New
*		-https://github.com/Giova-Bell
*	
*	Copyright Visual Laser 10 New
*
*	Release: 1.1.0 - 04/2021
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*
* DESCRIPTION:
* Used bit-masks to edit bif fields
* Used u_char to contain the bits
* 
* Dynamic allocation
* Variable type BitArray: unsigned char*
* 
* The ArrayBit indexing is Zero based, instead the BitArray length is One based
*/

#define SIZE sizeof(char)


/***************************** GLOBAL VARIABLE *****************************/
typedef unsigned char* BitArray; 								//type of Array bits

typedef enum
{
	False,
	True
}Bool;

typedef enum
{
	And,
	Or,
	Xor,
	Nand,
	Nor,
	Xnor
}LogicSign;


/*************************** STANDARD FUNCTION ******************************/

//SET THE BIT
int setBit(BitArray bitArray, unsigned int Pos, unsigned char Value )
{
	unsigned int bytePos = (unsigned)(floor((float)Pos/8.0));	//number of byte to access the value
	unsigned int realPos = (unsigned)(Pos%8);			   	 	//position of bit inside the byte
	
	if(Value)
	{
		//set 1
		bitArray[bytePos] |= 1<<realPos;
	}
	else
	{
		//set 0
		bitArray[bytePos] &= ~(1<<realPos);
	}
	return 0;	
}


//GET THE BIT
unsigned char getBit(BitArray bitArray, unsigned int Pos)
{
	unsigned int bytePos = (unsigned)(floor((float)Pos/8.0));	//number of byte to access the value
	unsigned int realPos = (unsigned)(Pos%8);		       	 	//position of bit inside the byte


	return ((bitArray[bytePos]&(1<<realPos))>>realPos);
}


//ALLOC AND REALLOC
BitArray allocBit(BitArray bitArray, unsigned int nBitInc, unsigned int LengthNow, Bool isInitialized) {
	BitArray tmp;
	size_t n_byte = ((size_t)ceil((float)nBitInc/8.0));			//number of byte
	size_t n_byteNow = ((size_t)ceil((float)LengthNow/8.0));	//number of byte Now
	
	if(!isInitialized) {
		bitArray = (BitArray)malloc(SIZE);		
	}
	
	tmp = (BitArray)realloc(bitArray, n_byte*SIZE);

	if(!tmp) {
		free(tmp);
		return (BitArray)-1;
	}
	
	bitArray = tmp;
	
	//assign all new bit to 0
	for(int i=(isInitialized)?LengthNow-1:0; i<nBitInc; i++)
	{
		setBit(bitArray,i,0);
	}
	return bitArray;
}


/**************************** EXTENDED FUNCTION *******************************/

//PRINT BITS
void printBitArr(BitArray bitArray, size_t Length, Bool RtL, const char* stringAtEnd)
{
	if(RtL)
	{
		for(int i = Length-1; i >= 0; --i)
		{
			printf("%c", getBit(bitArray, i) + '0');
		}
	}
	else
	{
		for(int i = 0; i < Length; ++i)
		{
			printf("%c", getBit(bitArray, i) + '0');
		}
	}
	
	printf(stringAtEnd);
}


//SET BURST BITS
void burstBit(BitArray bitArray, unsigned int fromPos, unsigned int toPos, unsigned char Value)
{
	//the position specified are included in the change
	for(unsigned int i = fromPos; i <= toPos; ++i)
	{
		setBit(bitArray, i, Value);
	}
}


//BASED ON ARRAY[] SET MULTIPLE POSITION IN BITARRAY
void arrBitArr(BitArray bitArray, unsigned int arr[], size_t arrLength, unsigned char Values[])
{
	for(unsigned int i=0; i < arrLength; ++i)
	{
		setBit(bitArray, arr[i], Values[i]);
	}
}


//COPY A PART OF ARRAY INTO ANOTHER ARRAY
void cpyBit(BitArray destination, BitArray source, size_t fromPos, size_t toPos)
{
	size_t j = 0;
	for(size_t i=fromPos; i <= toPos; i++, j++)
	{		
		setBit(destination, j, getBit(source, i));
	}
}


/**************************** LOGICAL FUNCTION *******************************/

//DO THE SHIFT OPERATION
void shiftBitArr(BitArray destination, BitArray source, size_t shiftNum, size_t Length, Bool RtL)
{
	size_t j, i;												//i seeks the bit to replace in position j
	unsigned int frP, toP;										//the begin and the end of burst
	
	if(RtL)
	{
		j = 0;
		i = shiftNum;
		
		frP = (unsigned) (Length - shiftNum - 1);				//-1 is for the zero based
		toP = (unsigned) (Length - 1);
		
		for(; j<Length; ++i, ++j)
		{
			setBit(destination, j, getBit(source, i));			//shift the bits
		}
	}
	else
	{
		j = Length - 1;
		i = Length - shiftNum - 1;
		
		frP = (unsigned) (0);
		toP = (unsigned) (shiftNum);
		
		for(; i>0; --i, --j)
		{
			setBit(destination, j, getBit(source, i));			//shift the bits
		}
	}
	
	burstBit(destination, frP, toP, 0);							//set the padding bits
}


//DO BITtoBIT OPERATIONS
void logicBit(BitArray op1, BitArray op2, BitArray result, size_t *op1Length,  size_t *op2Length,  size_t *resLength, LogicSign sign)
{
	size_t i;
	// define the size of the biggest array
	size_t max = (*op1Length >= *op2Length) ? *op1Length : *op2Length;
	
  	// initialize the array at the rigth size
  	if(*op1Length < *op2Length)
  	{
  		op1 = allocBit(op1, max, *op1Length,True);
  		*op1Length = max;
	}
	else if(*op1Length > *op2Length)
	{
		op2 = allocBit(op2, max, *op2Length,True);
  		*op2Length = max;
	}
															
	if(*resLength < max) {
	  	result = allocBit(result, max, 0, False);				//reset all bit to 0
	    *resLength = max;
	}

	
	//start bool operations
	if(sign == And)									
	{
		for(i=0; i < max; ++i)
		{
	     	setBit(result, i, getBit(op1,i) & getBit(op2,i));
		}
	}
	else if(sign == Or)
	{
		for(i=0; i < max; ++i)
		{
	     	setBit(result, i, getBit(op1,i) | getBit(op2,i));
		}
	}
	else if(sign == Xor)
	{
		for(i=0; i < max; ++i)
	    {
	     	setBit(result, i, getBit(op1,i) ^ getBit(op2,i));
	    }
	}
	else if(sign == Nand)
	{
		for(i=0; i < max; ++i)
	    {
	     	setBit(result, i, !( getBit(op1,i) & getBit(op2,i) ));
	    }
	}
	else if(sign == Nor)
	{
		for(i=0; i < max; ++i)
	    {
	     	setBit(result, i, !( getBit(op1,i) | getBit(op2,i) ));
	    }
	}
	else if(sign == Xnor)
	{
		for(i=0; i < max; ++i)
	    {
	     	setBit(result, i, !( getBit(op1,i) ^ getBit(op2,i) ));
	    }
	}
}


//DO CA1 BITWISE
void ca1Bit(BitArray destination, BitArray source, size_t *destLength, size_t sourceLength)
{
  	size_t n_byte = ((size_t)ceil((float)sourceLength/8.0));			//number of byte
	if(sourceLength > *destLength)
    {
    	destination = allocBit(destination, *destLength, 0, False);
    	*destLength = sourceLength;
    }
	
	
  	for(size_t i = 0; i < n_byte; ++i)
  	{
    	destination[i] = ~(source[i]);
  	}
}


/**************************** BASES FUNCTION *******************************/
/*
->in dec, in oct, in hex (base conversion) //1001 -> 9
->in dec (base transcript) //1001 -> milleuno
->from dec, from oct, from hex
->to string
*/
