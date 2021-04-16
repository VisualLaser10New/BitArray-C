/*	Visual Laser 10 New:
*
*	Developer:
*		-https://github.com/VisualLaser10New
*		-https://github.com/Giova-Bell
*	
*	Copyright Visual Laser 10 New
*
*	Release: 1.0.1 - 04/2021
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE sizeof(char)

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

/***************************** GLOBAL VARIABLE *****************************/
typedef unsigned char* BitArray; 							//type of Array bits
//typedef struct {unsigned char bit:1;}Bit;
typedef enum
{
	False,
	True
}Bool;

/*************************** STANDARD FUNCTION ******************************/

//ALLOC AND REALLOC
BitArray allocBit(BitArray bitArray, unsigned int nBitInc, size_t LengthNow, Bool isInitialized) {
	BitArray tmp;
	size_t n_byte = ((size_t)ceil((float)nBitInc/8.0));		//number of byte
	
	
	if(!isInitialized) {
		bitArray = (BitArray)malloc(SIZE);		
	}
	
	tmp = (BitArray)realloc(bitArray, n_byte*SIZE);

	if(!tmp) {
		free(tmp);
		return (BitArray)-1;
	}
	
	bitArray = tmp;
	
	//assign new bit all to 0
	for(int i=(isInitialized)?LengthNow-1:0; i<n_byte; i++)
	{
		bitArray[i]=0;
	}	
	return bitArray;
}


//SET THE BIT
int setBit(BitArray bitArray, unsigned int Pos, unsigned char Value )
{
	unsigned int bytePos = (unsigned)(floor((float)Pos/8.0));//number of byte to access the value
	unsigned int realPos = (unsigned)(Pos%8);			   	 //position of bit inside the byte
	
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
	unsigned int bytePos = (unsigned)(floor((float)Pos/8.0));//number of byte to access the value
	unsigned int realPos = (unsigned)(Pos%8);		       	 //position of bit inside the byte


	return ((bitArray[bytePos]&(1<<realPos))>>realPos);
}


/**************************** EXTENDED FUNCTION *******************************/

//PRINT BITS
void printBitArr(BitArray bitArray, size_t Length)
{
	for(int i=Length-1;i>=0;i--)
	{
		printf("%c",getBit(bitArray,i)+'0');
	}
}


//SET BURST BITS
void burstBit(BitArray bitArray, unsigned int fromPos, unsigned int toPos, unsigned char Value)
{
	//the position specified are included in the change
	for(unsigned int i = fromPos; i<=toPos; i++)
	{
		setBit(bitArray,i,Value);
	}
}


//BASED ON ARRAY[] SET MULTIPLE POSITION IN BITARRAY
void arrBitArr(BitArray bitArray, unsigned int arr[], size_t arrLength, unsigned char Values[])
{
	for(unsigned int i=0;i<arrLength;i++)
	{
		setBit(bitArray,arr[i],Values[i]);
	}
}
