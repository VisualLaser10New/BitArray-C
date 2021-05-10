# BitArray-C
A set of functions to handle a dynamic Array of Bits, in C-lang.

---------------------

With this library is possible to create one or more resizable Array of Bit. 
The array is allocated with chunks of 8 bits (char). Each bit take 1 real bit in memory.
The ArrayBit indexing is Zero based, instead the BitArray length is One based.

---------------------

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

---------------------

# Functions

* ### allocBit
  it returns a pointer to the allocated memory.
  
  ```c
  BitArray allocBit(BitArray bitArray, unsigned int nBitInc, size_t LengthNow, Bool isInitialized);
  ```
  
  To allocate in memory a specified number of Bit so create a BitArray, or to increase a pre-sized BitArray; use the allocBit function:
  
  * `bitArray` is the BitArray variable
  * `nBitInc` is the total number of bits to allocate or reallocate to the BitArray
  * `LengthNow` is the actual length of the array before the resize, if it's 0 set it to 0
  * `isInitialized` is a Bool type (defined in an enum), set it true if the BitArray is already initialized

  ----

* ### setBit

  ```c
  int setBit(BitArray bitArray, unsigned int Pos, unsigned char Value);
  ```
  
  To set a bit in a specified position in the BitArray use setBit function:
  
  * `bitArray` is the BitArray variable
  * `Pos` is the index of the bit to change
  * `Value` is the binary digit to set into this bit
  
  ----
  
* ### getBit

  ```c
  unsigned char getBit(BitArray bitArray, unsigned int Pos);
  ```
  
  This function return the bit at the specified position:
  
  * `bitArray` is the BitArray variable
  * `Pos` is the index of the bit to get

  ----

* ### printBitArr

  ```c
  void printBitArr(BitArray bitArray, size_t Length, Bool RtL, const char* stringAtEnd);
  ```
  
  To print the BitArray on the console, to make more readable the array, based on RtL it's printed in one way or another.
  
  * `bitArray` is the BitArray variable
  * `Length` it's the number of bits to print
  * `RtL` it's the mode of print (False = print from LSB to MSB, True = print from MSB to LSB)
  * `stringAtEnd` is the string printed at the end (\n to default)
  
  ----
  
* ### burstBit

  ```c
  void burstBit(BitArray bitArray, unsigned int fromPos, unsigned int toPos, unsigned char Value);
  ```
  
  Make a bit burst on BitArray.
  
  * `bitArray` is the BitArray variable
  * `fromPos` is the index of bit where the burst start, the change include this bit too
  * `toPos` is the index where the burst is stopped, it's also included in the burst
  * `Value` is the binary digit to set in all of the burst positiions

  ----

* ### arrBitArr

  ```c
  void arrBitArr(BitArray bitArray, unsigned int arr[], size_t arrLength, unsigned char Values[]);
  ```
  
  Set multiple bits on specified positions.
  
  * `bitArray` is the BitArray variable
  * `arr` is an integer array, that contains the indexes of the bits to change
  * `arrLength` is the length of `arr`, the positions are 1 based
  * `Values` contains the values to apply at specified indexes in the array: `arr` (it's parallel to it)

  ----

* ### cpyBit

  ```c
  void cpyBit(BitArray destination, BitArray source, size_t fromPos, size_t toPos);
  ```
  
  Copy the bit in the bitArray from pos x to pos y in destination array.
  
  * `destination` is the BitArrai where the bit are copyed
  * `source` is the array containing the bit to be copied
  * `fromPos` is the position where the copy starts (it's included in the copy)
  * `toPos` is the position where the copy finish (it's included in the copy)

  ----

* ### invBit
  ```c
  void invBit(BitArray destination, BitArray source, size_t *destinationLength, size_t sourceLength)
  ```
  
  Invert the source BitAy in the destination BitArray
  
  * `destination` is the BitArray where the inverted array is copied
  * `source` is the BitArray that will be inverted
  * `destinationLength` is the length of `destination`
  * `sourceLength` is the length of `source`

  ----

* ### cmpBit
  ```c
  Bool cmpBit(BitArray op1, BitArray op2, size_t op1Length, size_t op2Length)
  ```
  
  Return if two BitArray are equal
  
  * `op1` is the first operand that will be compared
  * `op2` is the second operant that will be compared
  * `op1Length` length of `op1`
  * `op2Length` length of `op2`

  ----

* ### readBitArr
  ```c
  void readBitArr(BitArray bitArray, size_t *Length, Bool autoIncrease)
  ```
  
  Read an input for BitArray
  
  * `bitArray` the BitArray in which will be inserted the input
  * `Length` is the length of the BitArray
  * `autoIncrease` you can select if it can adapt to the input of the user or have a pre-established length

  ----

* ### shiftBitArr
  ```c
  void shiftBitArr(BitArray destination, BitArray source, size_t shiftNum, size_t Length, Bool RtL)
  ```
  
  Shift the BitArray in the selected direction (is the equivalent to the `<` or `>` operations)
  
  * `destination` is the BitArray in which will be inserted the result of the shift
  * `source` is the BitArray that will be shifted
  * `shiftNum` is the number of positions to shift
  * `Length` is the length of the `source` BitArray
  * `RtL` is the direction of the shift (RtL if True > if False <)

  ----

* ### logicBit
  ```c
  void logicBit(BitArray op1, BitArray op2, BitArray result, size_t *op1Length,  size_t *op2Length,  size_t *resLength, LogicSign sign)
  ```
  
  Execute a logic operation between two BitArray
  
  * `op1` first operator of the operation
  * `op2` second operator of the operation
  * `result` is the BitArray in which the result is copied
  * `op1Length` is the length of `op1`
  * `op2Length` is the length of `op2`
  * `resLength` is the length of `result`
  * `sign` is the name of the logic operation (And, Or, Xor, Nand, Nor, Xnor)

  ----

* ### ca1Bit
  ```c
  void ca1Bit(BitArray destination, BitArray source, size_t *destLength, size_t sourceLength)
  ```
  
  Do logic CA1 of the first source array and put the result in destination
  
  * `destination` is the BitArray in which will be inserted the result of the CA1
  * `source` the BitArray upon which the CA1 will be execute
  * `destLength` this number indicate the length of destination BitArray
  * `sourceLength` is the length of the `source` BitArray

  ----

* ### linearLogicBit
  ```c
  unsigned linearLogicBit(BitArray bitArray, size_t Length, LogicSign sign, Bool Rtl)
  ```
  
  This Function make any logic operation with the bit contained in the BitArray
  
  * `bitArray` is the BitArray variable Type on which the logical operation will be made
  * `Length` is the `bitArray` Length
  * `sign` is the name of the logic operation (And, Or, Xor, Nand, Nor, Xnor)
  * `RtL` is the direction of the logic operation flow

  ----

* ### baseExportBit
  ```c
  long long unsigned baseExportBit(BitArray bitArray, size_t Length)
  ```
  
  Convert a bit number composed by BitArray in decimal base and return it
  
  * `bitArray` the BitArray will be converted in decimal number
  * `Length` the BitArray's length expressed in number of bits
  
  ----

* ### baseTranscBit
  ```c
  long long unsigned baseTranscBit(BitArray bitArray, size_t Length)
  ```
  
  Transcript the bit from base 2 to base 10 ES: 1001(2) -> 1001(10)
  
  * `bitArray` the BitArray that will be transcripted
  * `Length` the length of `bitArray`

   ----

* ### baseImportBit
  ```c
  void baseImportBit(BitArray bitArray, long long unsigned int input, size_t *Length)
  ```
  
  Convert an input number in decimal base to a bitArray in binary base
  
  * `bitArray` is the BitArray in which set the converted number
  * `input` is the number to convert from dec to bin
  * `Length` is the length of the BitArray
  
  ----

* ### charfromBit
  ```c
  void charfromBit (BitArray bitArray, char output[], size_t Length, BaseType base)
  ```
  
  Tranform the bit BitArray in a string with chosen base
  
  * `bitArray` is the BitArray that will be converted
  * `output` is the output string
  * `Length` is the length of `bitArray`
  * `base` is the base in which will be transformed the BitArray (Bin, Dec, Oct, Hex)

   ----
   
* ### n32ImportBit
  ```c
  void n32ImportBit(BitArray bitArray, float input, size_t *Length, Bool isFloat)
  ```
  
  Copy the bits of INT or FLOAT number saved in memory into a bitArray
  
  * `bitArray` the BitArray in which will be copy the bits
  * `input` is the input number can be INT or FLOAT from which converted
  * `Length` the length of bitArray
  * `isFloat` if the input is a FLOAT set it as `True`, otherwise `False`

## Advice to use the library

  We advice to define our BitArray variables in a struct because u need to take track of their size to use them

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
