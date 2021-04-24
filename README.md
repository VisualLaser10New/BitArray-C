# BitArray-C
A set of functions to handle a dynamic Array of Bits, in C-lang.

With this library it's possible to create one or more resizable Array of Bit. 
The array is allocated with chunks of 8 bits (char). Each bit take 1 real bit in memory.
The ArrayBit indexing is Zero based, instead the BitArray length is One based.

## Implementation
   It's enough include the file.c like a header:
   ```c
   #include "BitArray.c"
   ```
   
## Declaration
   To declare an array of bits:
   ```c
   BitArray nameofarray;
   ```
   
## Functions
* ### allocBit
  it returns a pointer to the allocated memory.
  
  ```c
  BitArray allocBit(BitArray bitArray, unsigned int nBitInc, size_t LengthNow, Bool isInitialized);
  ```
  
  To allocate in memory a specified number of Bit so create a BitArray, or to increase a pre-sized BitArray; use the allocBit function:
  
  * bitArray is the BitArray variable
  * nBitInc is the total number of bits to allocate or reallocate to the BitArray
  * LengthNow is the actual length of the array before the resize, if it's 0 set it to 0
  * isInitialized is a Bool type (defined in an enum), set it true if the BitArray is already initialized


* ### setBit

  ```c
  int setBit(BitArray bitArray, unsigned int Pos, unsigned char Value);
  ```
  
  To set a bit in a specified position in the BitArray use setBit function:
  
  * bitArray is the BitArray variable
  * Pos is the index of the bit to change
  * Value is the binary digit to set into this bit
  
  
* ### getBit

  ```c
  unsigned char getBit(BitArray bitArray, unsigned int Pos);
  ```
  
  This function return the bit at the specified position:
  
  * bitArray is the BitArray variable
  * Pos is the index of the bit to get
 
 
* ### printBitArr

  ```c
  void printBitArr(BitArray bitArray, size_t Length, Bool RtL, const char* stringAtEnd);
  ```
  
  To print the BitArray on the console, to make more readable the array, based on RtL it's printed in one way or another.
  
  * bitArray is the BitArray variable
  * Length it's the number of bits to print
  * RtL it's the mode of print (False = print from LSB to MSB, True = print from MSB to LSB)
  * stringAtEnd is the string printed at the end
  
  
* ### burstBit

  ```c
  void burstBit(BitArray bitArray, unsigned int fromPos, unsigned int toPos, unsigned char Value);
  ```
  
  Make a bit burst on BitArray.
  
  * bitArray is the BitArray variable
  * fromPos is the index of bit where the burst start, the change include this bit too
  * toPos is the index where the burst is stopped, it's also included in the burst
  * Value is the binary digit to set in all of the burst positiions


* ### arrBitArr

  ```c
  void arrBitArr(BitArray bitArray, unsigned int arr[], size_t arrLength, unsigned char Values[]);
  ```
  
  Set multiple bits on specified positions.
  
  * bitArray is the BitArray variable
  * arr is an integer array, that contains the indexes of the bits to change
  * arrLength is the length of arr, the positions are 1 based
  * Values is a parallel array of positionsArray, that contains the values to apply at specified indexes in the array: arr


* ### cpyBit

  ```c
  void cpyBit(BitArray destination, BitArray source, size_t fromPos, size_t toPos);
  ```
  
  Copy the bit in the bitArray from pos x to pos y in destination array.
  
  * destination is the BitArrai where the bit are copyed
  * source is the array containing the bit to be copied
  * fromPos is the position where the copy starts (it's included in the copy)
  * toPos is the position where the copy finish (it's included in the copy)


## Advice to use the library

  we advice to define our BitArray variables in a struct because u need to take track of their size to use them

  ### example
  
  ```c
  typedef struct {
	BitArray bitArray;
	size_t size;
  } newBitArray;
  
  void main() {
	newBitArray bitArray;
	bitArray.size = 10;
	
	allocBit(bitArray.bitArray, bitArray.size, 0, False);
  }
  ```