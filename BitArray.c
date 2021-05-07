/*	Visual Laser 10 New:
*
*	Developer:
*		-https://github.com/VisualLaser10New
*		-https://github.com/Giova-Bell
*	
*	Copyright Visual Laser 10 New
*
*	Release: 1.0.0.1 - 04/2021
*
*	DESCRIPTION:
*		library that introduce a "new" type that contains bits
*		to edit the bit-fields are used bit-masks
* 
*		it uses dynamic allocation
*		Variable type BitArray: unsigned char*
* 
*		The ArrayBit indexing is Zero based, instead the BitArray length is One based
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define SIZE sizeof(char)



/***************************** GLOBAL VARIABLE *****************************/
typedef unsigned char* BitArray; // definition of the type of the BitArray


typedef enum // simulate the use of a Bool variable
{
	False,
	True
}Bool;


typedef enum // used to distinguish different logic operations
{
	And,
	Or,
	Xor,
	Nand,
	Nor,
	Xnor
}LogicSign;


typedef enum // used to distinguish different base operation
{
	Bin,
	Dec,
	Oct,
	Hex
}BaseType;


union
{
	int int32;
	float float32;
}Share;



/*************************** STANDARD FUNCTION ******************************/

//SET 1 BIT
#define setBit(...) _setBit(__VA_ARGS__, 1)
#define _setBit(bitArray, Pos, Value, ...) setBit(bitArray, Pos, Value)
int (setBit)(BitArray bitArray, unsigned int Pos, unsigned char Value )
{
	unsigned int bytePos = (unsigned)(floor((float)Pos/8.0)); // number of byte to access the value
	unsigned int realPos = (unsigned)(Pos%8); // position of bit inside the byte
	
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


//GET 1 BIT
unsigned char getBit(BitArray bitArray, unsigned int Pos)
{
	unsigned int bytePos = (unsigned)(floor((float)Pos/8.0)); // number of byte to access the value
	unsigned int realPos = (unsigned)(Pos%8); // position of bit inside the byte


	return ((bitArray[bytePos]&(1<<realPos))>>realPos);
}


//ALLOC AND REALLOC
#define allocBit(...) _allocBit(__VA_ARGS__, True)
#define _allocBit(bitArray, nBitInc, LengthNow, isInitialized, ...) allocBit(bitArray, nBitInc, LengthNow, isInitialized)
BitArray (allocBit)(BitArray bitArray, unsigned int nBitInc, unsigned int LengthNow, Bool isInitialized) {
	BitArray tmp;
	size_t n_byte = ((size_t)ceil((float)nBitInc/8.0)); // number of total byte (the bit to add are included)
	size_t n_byteNow = ((size_t)ceil((float)LengthNow/8.0)); // number of byte of the passed variable (the bit to add are excluded)
	
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

//PRINT THE PASSED BITS
#define printBitArr(...) _printBitArr(__VA_ARGS__, True, "\n")
#define _printBitArr(bitArray, Length, RtL, stringAtEnd, ...) printBitArr(bitArray, Length, RtL, stringAtEnd)
void (printBitArr)(BitArray bitArray, size_t Length, Bool RtL, const char* stringAtEnd)
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
#define burstBit(...) _burstBit(__VA_ARGS__, 1)
#define _burstBit(bitArray, fromPos, toPos, Value, ...) burstBit(bitArray, fromPos, toPos, Value)
void (burstBit)(BitArray bitArray, unsigned int fromPos, unsigned int toPos, unsigned char Value)
{
	//the position specified are included in the change
	for(unsigned int i = fromPos; i <= toPos; ++i)
	{
		setBit(bitArray, i, Value);
	}
}


//BASED ON ARRAY[] SET MULTIPLE POSITION IN BITARRAY ON THE PASSED VALUES
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
	for(size_t i=fromPos; i <= toPos; ++i, ++j)
	{
		setBit(destination, j, getBit(source, i));
	}
}


//INVERT THE SOURCE BITARRAY IN DESTINATION BITARRAY
void invBit(BitArray destination, BitArray source, size_t *destinationLength, size_t sourceLength)
{
	*destinationLength = sourceLength;
	destination = allocBit(destination, *destinationLength, 0, True);
	
	unsigned temp = 0;
	
	for(size_t i = 0, j = *destinationLength - 1; i < (int)sourceLength/2; ++i, --j)
	{
		temp = getBit(source, j);
		
		setBit(destination, j, getBit(source, i));
		setBit(destination, i, temp);
	}
}


//RETURN IF 2 BITARRAYS ARE EQUAL
Bool cmpBit(BitArray op1, BitArray op2, size_t op1Length, size_t op2Length)
{	
	if(op1Length != op2Length) // return True is are equal, False if not
		return False;
		
	for(size_t i = 0; i<op1Length; ++i)
	{
		if(getBit(op1,i) != getBit(op2,i))
			return False;
	}
	
	return True;
}


//READ BITARRAY FROM STDIN
void readBitArr(BitArray bitArray, size_t *Length, Bool autoIncrease)
{
	BitArray tmp = allocBit(tmp, *Length, 0, False);
	char input = 0;
	size_t i = 0;
	
	
	while(i <= *Length){
		input = getchar();
		
		if(input == '\n' || input == EOF)
			break;
		
		if(autoIncrease && i == (*Length))
		{
			++(*Length);
			tmp = allocBit(tmp, (*Length), *Length, True);
		}
		else if((!autoIncrease) && i == (*Length))
			break;
		
		setBit(tmp, i, input-48);
		
		++i;
	}
	
	invBit(bitArray, tmp, Length, *Length);
}



/**************************** LOGICAL FUNCTION *******************************/
/*
	TODO: linear bitwise operations 001 & -> 0&0&1 -> 0
*/


//DO THE SHIFT OPERATION
void shiftBitArr(BitArray destination, BitArray source, size_t shiftNum, size_t Length, Bool RtL)
{
	size_t j, i; // i seeks the bit to replace in position j
	unsigned int frP, toP; // the begin and the end of burst
	
	// True -> shift to the right >>
	// False -> shift to the left <<
	if(RtL)
	{
		j = 0;
		i = shiftNum;
		
		frP = (unsigned) (Length - shiftNum - 1); // -1 is for the zero based
		toP = (unsigned) (Length - 1);
		
		for(; j < Length; ++i, ++j)
		{
			setBit(destination, j, getBit(source, i)); // shift the bits
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
			setBit(destination, j, getBit(source, i)); // shift the bits
		}
	}
	
	burstBit(destination, frP, toP, 0); // set the "padding" bits
}


//DO BIT to BIT OPERATIONS
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
	  	result = allocBit(result, max, 0, False); // reset all bit to 0
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


//DO BITWISE CA1
void ca1Bit(BitArray destination, BitArray source, size_t *destLength, size_t sourceLength)
{
  	size_t n_byte = ((size_t)ceil((float)sourceLength/8.0)); // number of byte
	if(sourceLength > *destLength)
    {
    	destination = allocBit(destination, sourceLength, 0);
    	*destLength = sourceLength;
    }
	
  	for(size_t i = 0; i < n_byte; ++i)
  	{
    	destination[i] = ~(source[i]);
  	}
}


//LINEAR LOGIC OPERATIONS
unsigned linearLogicBit(BitArray bitArray, size_t Length, LogicSign sign)
{
	size_t i;
	unsigned output = getBit(bitArray,0);
	
	if(sign == And)									
	{
		for(i=1; i < Length; ++i)
		{
	     	output &= getBit(bitArray,i);
		}
	}
	else if(sign == Or)
	{
		for(i=1; i < Length; ++i)
		{
	     	output |= getBit(bitArray,i);
		}
	}
	else if(sign == Xor)
	{
		for(i=1; i < Length; ++i)
	    {
	     	output ^= getBit(bitArray,i);
	    }
	}
	else if(sign == Nand)
	{
		for(i=1; i < Length; ++i)
	    {
	     	output &= getBit(bitArray,i);
	     	output = !output;
	    }
	}
	else if(sign == Nor) // forse sbagliata
	{
		for(i=1; i < Length; ++i)
	    {
	     	output |= getBit(bitArray,i);
	     	output = !output;
	    }
	}
	else if(sign == Xnor)
	{
		for(i=1; i < Length; ++i)
	    {
	     	output ^= getBit(bitArray,i);
	     	output = !output;
	    }
	}
	
	return output;
}



/**************************** BASES FUNCTION *******************************/

//CONVERT THE BIT ARRAY TO INT (BASE BIN TO DEC)
long long unsigned baseExportBit(BitArray bitArray, size_t Length)
{
	long long unsigned int output = 0;
	for(size_t i = 0; i < Length; i++)
	{
		(output) += getBit(bitArray, i) * (1<<i);
	}
	return output;
}


//TRANSCRIPT THE BITARRAY TO INT (1001(2) -> 1001(10))
long long unsigned baseTranscBit(BitArray bitArray, size_t Length)
{
	long long unsigned int output = 0;
	for(size_t i = 0; i<Length; i++)
	{
		(output) += getBit(bitArray, i) * pow(10,i);
	}
	return output;
}


//CONVERT INT NUMBER TO BITARRAY (BASE 10 TO BASE 2)
void baseImportBit(BitArray bitArray, long long unsigned int input, size_t *Length)
{
	size_t n_byteNow = ((size_t)ceil((float)*Length/8.0));
	size_t n_bitNeed = ((size_t)(floor(log2((float)abs(input))+1)));
	unsigned i = 0;


	if(n_byteNow*8 < n_bitNeed)
	{
		bitArray = allocBit(bitArray, n_bitNeed, *Length, True);
		*Length = n_bitNeed;
	}
	
	
	while(input)
	{
		setBit(bitArray, i, (unsigned)(input&1));
		input>>=1;
		++i;
	}
}


//TRANSOFRM THE BITARRAY TO CHAR ARRAY WITH CHOOSEN BASE (BIN, DEC, OCT, HEX)
#define charfromBit(...) _charfromBit(__VA_ARGS__, Dec)
#define _charfromBit(bitArray, output, Length, base, ...) charfromBit(bitArray, output, Length, base)
unsigned (charfromBit)(BitArray bitArray, char output[], size_t Length, BaseType base)
{
	size_t i;
	size_t end;
	char tmp;
	
	if(base == Bin)
	{
		size_t j;
		for(i = 0, j = Length-1; i < Length; ++i, --j)
		{
			output[j] = getBit(bitArray, i) + '0';
		}
	}
	else if(base == Dec)
	{
		long long unsigned num = baseExportBit(bitArray, Length);
		i = 0;
		while(num)
		{
			output[i] = (num % 10) + '0';
			num /= 10;
			++i;
		}
	}
	else if(base == Oct)
	{
		long long unsigned num = baseExportBit(bitArray, Length);
		i = 0;
		while(num)
		{
			output[i] = (num % 8) + '0';
			num /= 8;
			++i;
		}
	}
	else if(base == Hex)
	{
		long long unsigned num = baseExportBit(bitArray, Length);
		unsigned a = 0;
		i = 0;
		while(num)
		{
			a = num % 16;
			output[i] = a + ((a<10)?'0':('A' - 0xA));
			num /= 16;
			++i;
		}
	}
	output[++i]='\0';
	
	
	if(base != Bin)
	{
		end = strlen(output)-1;
	
		for(i=0; i < end; i++){
			tmp = output[end-i];
			output[end-i] = output[i];
			output[i] = tmp;
		}
	}	
}


//TRANSFORM INT OR FLOAT TO BITARRAY (EXTRACT THE BIT OF THE PASSED NUMBER)
void n32ImportBit(BitArray bitArray, float input, size_t *Length, Bool isFloat)
{
	if(*Length < 32)
	{
		bitArray = allocBit(bitArray, 32, *Length, True);
		*Length = 32;
	}
	
	
	if(isFloat)
	{
		Share.float32 = input;
	}
	else
	{
		Share.int32 = (int)input;
	}

	baseImportBit(bitArray, Share.int32, Length);
}