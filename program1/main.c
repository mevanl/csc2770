#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void decimalToBinary(int decimal);
void decimalToHex(int decimal);
void binaryToDecimal(char *binary);
void binaryToHex(char *binary);
void hexToDecimal(char *hex);
void hexToBinary(char *hex);
// my funcs
int checkIfInvalidDecimal(char *decimal);
// checkIfInvalidHexadecimal
// checkIfInvalidBinary
int hexToDec(char hex);
char decToHex(int dec);
int fourBitsToInt(char bits[]);

// Function to print the hexadecimal number in reverse order
void printHexInReverse(char hex[], int length)
{
  printf("Hexadecimal: ");
  for (int j = length - 1; j >= 0; j--)
  {
    printf("%c", hex[j]);
  }
  printf("\n");
}

// Convert decimal to binary
void decimalToBinary(int decimal)
{
  printf("Converting decimal %d to binary...\n", decimal);
   
  char binary[33];                    // 32-bit binary number
  binary[32] = '\0';                  // Null terminate the string
  for (int i = 1; i < 32; i++)        // fill it up with '0'
  {
    binary[i] = '0';
  }
  
  int total = 0;                      // will add up to our decimal 
  if (decimal < 0)
  {
    binary[0] = '1';
    total = -2147483648 ;             // initialize to min so can add to value
  } 
  else 
  {
    binary[0] = '0';
  }

  int i = 1;


  while (total != decimal)
  {
    int exponent = 32 - i; 
    int value = 1 << exponent - 1;  // get the correct decimal value for a given bit

    if (value + total <= decimal)   // if total + value gets us closer
    {                               // to our desired decimal number
      binary[i] = '1';              // flip the bit
      total += value; 
      i++;
      continue;
    }

    i++;
  }

  printf("Binary: %s\n", binary);
}

// Function to convert decimal to hexadecimal (placeholder)
void decimalToHex(int decimal)
{
  printf("Converting decimal %d to hexadecimal...\n", decimal);

  char backwards_hex[8];
  int i = 0;
  // Call the function to print the hexadecimal number in reverse order
  printHexInReverse(backwards_hex, i);
}

// Convert binary to decimal
void binaryToDecimal(char *binary)
{
  printf("Converting binary %s to decimal...\n", binary);
  
  int decimal = 0;

  
  int bits = 0;
  while (binary[bits] != '\0')
  {
    bits++;                               // count bit count
  }

  int exponent = bits - 1;
  int value = 0; 

  // TA SAID ASSUME UNSIGNED INPUT
  for (int i = 0; i < bits; i++)
  {
    if (binary[i] == '1')                 // if bit is 1
    {              
      decimal += 1 << exponent;           // get decimal amount at that bit location
    }

    exponent--;                           // as we go right in memory, exponent lowers
  }

  printf("Decimal: %d\n", decimal);
}

// Function to convert binary to hexadecimal (placeholder)
void binaryToHex(char *binary)
{
  printf("Converting binary %s to hexadecimal...\n", binary);
  // Conversion logic will go here

  char hex[9];
  char fourBits[4];

  // count bits
  int bits = 0;
  while (binary[bits] != '\0')
  {
    bits++;
  }

  // what if we dont have more than 4 bits?
  switch (bits)
  {
    case 1:
      fourBits[0] = '0';
      fourBits[1] = '0';
      fourBits[2] = '0';
      fourBits[3] = binary[0];

      hex[0] = decToHex(fourBitsToInt(fourBits));
      hex[1] = '\0';
      printf("Hexadecimal: %s\n", hex);
      return;
    
    case 2:
      fourBits[0] = '0';
      fourBits[1] = '0';
      fourBits[2] = binary[0];
      fourBits[3] = binary[1];
      
      hex[0] = decToHex(fourBitsToInt(fourBits));
      hex[1] = '\0';
      printf("Hexadecimal: %s\n", hex);
      return;

    case 3:
      fourBits[0] = '0';
      fourBits[1] = binary[0];
      fourBits[2] = binary[1];
      fourBits[3] = binary[2];
      
      hex[0] = decToHex(fourBitsToInt(fourBits));
      hex[1] = '\0';
      printf("Hexadecimal: %s\n", hex);
      return;

    case 4: 
      fourBits[0] = binary[0];
      fourBits[1] = binary[1];
      fourBits[2] = binary[2];
      fourBits[3] = binary[3];
      
      hex[0] = decToHex(fourBitsToInt(fourBits));
      hex[1] = '\0';
      printf("Hexadecimal: %s\n", hex);
      return;
  }

  // Do we need to add bits to create
  // a collection of 4 bits, if yes how many?
  int padding = 4 - (bits % 4);           
  int initial_bit = 0;
  while (padding != 0 && padding != 4)        
  {
    fourBits[initial_bit] = '0';          // pad with zero
    initial_bit++;                        // keep track of where to start
    padding--;
  }

  

  int i = 0;
  int j = 0;
  while (binary[i] != '\0')
  {
    while (initial_bit != 4)
    {
      fourBits[initial_bit] = binary[i];
      i++;
      initial_bit++;
    }

    hex[j] = decToHex(fourBitsToInt(fourBits));

    initial_bit = 0;
    j++; 
  }

  hex[j] = '\0';
  printf("Hexadecimal: %s\n", hex);


  // I implemented this before you edited the template....
  //printHexInReverse(hex, j);
}

// Function to convert hexadecimal to decimal (placeholder)
void hexToDecimal(char *hex)
{
  printf("Converting hexadecimal %s to decimal...\n", hex);

  int decimal = 0;

  printf("Decimal: %d\n", decimal);
}

// Function to convert hexadecimal to binary (placeholder)
void hexToBinary(char *hex)
{
  printf("Converting hexadecimal %s to binary...\n", hex);
  // Conversion logic will go here

  // temp
  char* binary;

  printf("Binary: %s\n", binary);
}

// Main function to handle inputs and trigger conversions
int main(int argc, char *argv[])
{
  // Ensure correct number of arguments are provided
  if (argc != 3)
  {
    printf("Usage: %s -[d|b|h] [number]\n", argv[0]);
    printf("Options:\n");
    printf("-d [decimal]     Convert decimal to binary and hexadecimal\n");
    printf("-b [binary]      Convert binary to decimal and hexadecimal\n");
    printf("-h [hexadecimal] Convert hexadecimal to decimal and binary\n");
    return 1;
  }

  // Extract the flag and value from arguments
  // Check which flag was provided and call the appropriate function
  char option = argv[1][1];

  switch (option)
  {
  case 'd':
    if (checkIfInvalidDecimal(argv[2]) == 1)
    {
      return 1;
    }
    decimalToBinary(atoi(argv[2]));
    //decimalToHex(atoi(argv[2]));
    break;
  case 'b':
    binaryToDecimal(argv[2]);
    binaryToHex(argv[2]);
    break;
  case 'h':
    //hexToBinary(argv[2]);
    hexToDecimal(argv[2]);
    break;
  default:
    return 1;
  }

  return 0;
}


// My functions
int checkIfInvalidDecimal(char *decimal)
{
  int i = 0; 

  if (decimal[0] == '-')
  {
    i++;
  }

  while (decimal[i] != '\0') 
  {
    // if integer is too big (signed int)
    if (strtoll(decimal, NULL, 10) > 2147483647 || strtoll(decimal, NULL, 10) < -2147483648)
    {
      printf("ERROR: decimal value is too large to fit in signed int.");
      return 1; 
    }

    if (decimal[i] - '0' > 9 || decimal[i] - '0' < 0)
    {
      printf("ERROR: decimal value contains illegal characters");
      return 1;
    }

    i++;
  }

  return 0; 
}

int hexToDec(char hex)
{
  if (hex >= '0' && hex <= '9')
      {
        return hex - '0';
      }
      else if (hex >= 'A' && hex <= 'F')
      {
        return hex - 'A' + 10;
      }
      else 
      {
        return hex - 'a' + 10;
      }
}

char decToHex(int integer)
{
  if (integer < 10)
  {
    return integer + '0';
  }

  switch (integer)
  {
    case 10:
      return 'A';
    case 11:
      return 'B';
    case 12:
      return 'C';    
    case 13:
      return 'D';    
    case 14:
      return 'E';
    case 15:
      return 'F';    
  }
}

int fourBitsToInt(char bits[])
{
  return ((bits[0] - '0') * 8) + ((bits[1] - '0') * 4) + ((bits[2] - '0') * 2) + ((bits[3] - '0') * 1);
}