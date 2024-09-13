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

// Function to convert decimal to binary (placeholder)
void decimalToBinary(int decimal)
{
  printf("Converting decimal %d to binary...\n", decimal);
  // Conversion logic will go here

  // Set up our 32-bit binary number 
  char binary[33];    
  binary[32] = '\0';              // Null terminate the string
  for (int i = 1; i < 32; i++)    // fill it up with '0'
  {
    binary[i] = '0';
  }
  
  // set up number that will add up to our decimal
  long long total = 0;
  if (decimal < 0)
  {
    binary[0] = '1';
    total = -2147483648 ;    // initialize to negative
  } 
  else 
  {
    binary[0] = '0';
  }
  
  // do the conversion 
  int i = 1;

  while (total != decimal)
  {
    int exponent = 32 - i; 
    int value = 1 << exponent - 1;

    //printf("\niteration: %d\nvalue: %d\nexponent: %d\ntotal: %d\n", i, value, exponent, total);
  
    // // For positive values
    // if (decimal > 0 && value + total <= decimal) 
    // {
    //   binary[i] = '1';
    //   total += value; 
    //   i++;
    //   continue;
    // }

    // // For negative values 
    // if (decimal < 0 && value + total <= decimal)
    // {
    //   binary[i] = '1';
    //   total += value;
    //   i++;
    //   continue;
    // }

    if (value + total <= decimal) 
    {
      binary[i] = '1';
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
  // Conversion logic will go here

  // temp
  char* hex;
  int i;

  // Call the function to print the hexadecimal number in reverse order
  printHexInReverse(hex, i);
}

// Function to convert binary to decimal (placeholder)
void binaryToDecimal(char *binary)
{
  printf("Converting binary %s to decimal...\n", binary);
  // Conversion logic will go here

  // temp
  int decimal;

  printf("Decimal: %d\n", decimal);
}

// Function to convert binary to hexadecimal (placeholder)
void binaryToHex(char *binary)
{
  printf("Converting binary %s to hexadecimal...\n", binary);
  // Conversion logic will go here

   // temp
  char* hex;
  int i;

  // Call the function to print the hexadecimal number in reverse order
  printHexInReverse(hex, i);
}

// Function to convert hexadecimal to decimal (placeholder)
void hexToDecimal(char *hex)
{
  printf("Converting hexadecimal %s to decimal...\n", hex);
  // Conversion logic will go here

  // temp
  int decimal;
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
  char* number = argv[2];

  switch (option)
  {
  case 'd':
    decimalToBinary(atoi(number));
    //decimalToHex(number + '0');
    break;
  case 'b':
    binaryToDecimal(number);
    binaryToHex(number);
    break;
  case 'h':
    hexToBinary(number);
    hexToDecimal(number);
    break;
  default:
    return 1;
  }

  return 0;
}
