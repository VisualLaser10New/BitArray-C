# BitArray-C
A set of functions to handle a dynamic Array of Bits, in C-lang.

With this source it's possible to create one or more resizable Array of Bit. 
The array is allocated with chunks of 8 bits. Each bit take 1 real bit in memory.
The ArrayBit indexing is Zero based, instead the BitArray length is One based.

## Implementation
   It's enough include the file.c like a header:
   ```c
   #include "BitArray.c"
   ```
   
## Declaration
   To declare a Array of bits:
   ```c
   BitArray nameofarray;
   ```
   
## Functions
* ### allocBit
  ```c
  BitArray allocBit(BitArray bitArray, unsigned int nBitInc, size_t LengthNow, Bool isInitialized);
  ```
  To allocate in memory a specified number of Bit so create a BitArray, or to increase a pre-sized BitArray; use the allocBit function:
  ```c
  bitArray = allocBit(bitArray, numBit, LengthNow, initialized);
  ```
  
  * bitArray is name of BitArray
  * numBit is the total number of bits to allocate or reallocate the BitArray
  * LenghtNow is the actual length of arrays before the resize, if is 0 set it to 0
  * initialized is a bool type where true is **True** and false is **False**, set it true if the BitArray is already initialized


* ### setBit
  ```c
  int setBit(BitArray bitArray, unsigned int Pos, unsigned char Value);
  ```
  To set a bit in a specified position in the BitArray use setBit function:
  ```c
  setBit(bitArray, position, Value);
  ```
  * bitArray is name of BitArray
  * position is the index of the bit to change
  * Value is binary digit to set into this bit
  
  
* ### getBit
  ```c
  unsigned char getBit(BitArray bitArray, unsigned int Pos);
  ```
  This function return the bit at the specified position:
  ```c
  getBit(bitArray, position);
  ```
  * bitArray is name of BitArray
  * position is the index of the bit to get
 
 
* ### printBitArr
  ```c
  void printBitArr(BitArray bitArray, size_t Length, unsigned int RtL);
  ```
  To print the BitArray on the console, to make more readable the array, based on RtL it's printed in one way or another.
  ```c
  printBitArr(bitArray, length);
  ```
  * bitArray is name of BitArray
  * length it's the number of bits to be printed
  * RtL it's the mode of print (0 = print from LSB to MSB, 1 = print from MSB to LSB)
  
  
* ### burstBit
  ```c
  void burstBit(BitArray bitArray, unsigned int fromPos, unsigned int toPos, unsigned char Value);
  ```
  Make a bit burst on BitArray.
  ```c
  burstBit(bitArray, fromPosition, toPosition, Value);
  ```
  * bitArray is name of BitArray
  * fromPosition is the index of bit to start the burst, the change include this bit too
  * toPosition is the index to stop the burst, it's also included in the burst
  * Value is binary digit to set in all of the burst


* ### arrBitArr
  ```c
  void arrBitArr(BitArray bitArray, unsigned int arr[], size_t arrLength, unsigned char Values[]);
  ```
  Set multiple bits on specified positions.
  ```c
  arrBitArr(bitArray, positionsArray, lengthPosArr, valuesArray);
  ```
  * bitArray is name of BitArray
  * positionsArray is an integer array, that contains the indexes of bits to change
  * lengthPosArr specific what is the length of positionsArray, the number is 1 based
  * valuesArray is a parallel array of positionsArray, that contains the values to apply at specified indexes in the array: positionsArray


* ### cpyBit
  ```c
  void cpyBit(BitArray destination, BitArray source, size_t fromPos, size_t toPos);
  ```
  Copy the bit in the bitArray from pos x to pos y in destination array.
  ```c
  arrBitArr(destination, bitArray, fromPos, toPos);
  ```
  * destination is the name of the BitArrai where the bit are copyed
  * bitArray is the array containing the bit to be copied
  * fromPos is the position where the copy starts (it's included in the copy)
  * toPos is the position where the copy finish (it's included in the copy)


## Example
```c
#include <stdio.h>
#include "BitArray.c"

void main() {
   size_t size = 4;                                // you can see this as bit or as byte (in case you define it as number of bit it will resized with the minimum number of byte
   BitArray bitArray;
   
   int arrIndexes[] = {0, 3};
   char arrValues[] = {0, 0};
   
   bitArray = allocBit(bitArray, size, 0, False);  // initialize the array of bit
   
   setBit(bitArray, 0, 1);                         // set the first bit to 1
   
   printf("%d\n", getBit(bitArray, 0));            // 1
   
   printBitArr(bitArray, size, 0);                 // 0001
   
   burstBit(bitArray, 1, 3, 1);                    // 1111
   
   arrBitArr(bitArray, arrIndexes, 2, arrValues);  // 0110
}
```
