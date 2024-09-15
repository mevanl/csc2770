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
int checkIfInvalidHex(char *hex);
int checkIfInvalidBinary(char *binary);
int hexToDec(char hex);
char decToHex(int dec);
int fourBitsToDec(char bits[]);
char* hexBits(char hex);
char flipBit(char bit);


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
    int value = 1 << (exponent - 1);  // get the correct decimal value for a given bit

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

// Convert decimal to hexadecimal
void decimalToHex(int decimal)
{

  long long temp = decimal; // this is needed in case
                            // the dec is -2147483648
                            // bc we use positive ver to convert

  printf("Converting decimal %d to hexadecimal...\n", decimal);

  int negative_flag = 0;
  if (temp < 0)
  {
    temp *= -1; 

    negative_flag = 1; 
  }

  char hex[8];
  int mod = 0;
  int i = 0;

  if (temp == 0)
  {
    hex[0] = '0';
    i++;
  }

  while (temp != 0)
  {
    mod = temp % 16;

    if (mod < 10)
    {
      mod += '0';  // change digit from int to char 
    }
    else
    {
      mod += '7';        // convert 10 - 11 int into A - F char
    }

    hex[i] = mod;
    temp /= 16; 

    i++;
  }

  if (negative_flag == 1)
  {
    int j = 0;
    int twos_complement_done = 0;
    
    while (j != i)
    {
      // take one's complement 
      //unsigned int dec = ~(fourBitsToDec(hexBits(hex[j]))); // NOTE: 
                                                              // Does not work because it is flipping
                                                              // all 32 bits in the int (the return type
                                                              // for fourBitsToDec)

      const char* bits = hexBits(hex[j]);
      char flipped_bits[5];
      flipped_bits[4] = '\0';

      for (int k = 0; k != 4; k++)
      {
        flipped_bits[k] = flipBit(bits[k]);
      }

      int dec = fourBitsToDec(flipped_bits);

      char new_hex = decToHex(dec);

      // can we add the one now?
      if ((new_hex != 'F' || new_hex != 'f') && twos_complement_done == 0)
      {
        new_hex++;
        twos_complement_done = 1;     // we can do this in advance because
                                      // we are in reverse order (least bit first)
        hex[j] = new_hex;
      }
      else if ((new_hex == 'F' || new_hex == 'f') && twos_complement_done == 0)
      {
        new_hex = '0';
      }
      else
      {
        hex[j] = new_hex;
      }

      j++;
    }
    
  }

  for (int l = i; l != 8; l++)
  {
    if (negative_flag == 1)
    {
      hex[l] = 'F';
      i++;
    }
    else
    {
      hex[l] = '0';
      i++;
    }
  }


  // Call the function to print the hexadecimal number in reverse order
  printHexInReverse(hex, i);
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

// Convert binary to hexadecimal 
void binaryToHex(char *binary)
{
  printf("Converting binary %s to hexadecimal...\n", binary);

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

      hex[0] = decToHex(fourBitsToDec(fourBits));
      hex[1] = '\0';
      printf("Hexadecimal: %s\n", hex);
      return;
    
    case 2:
      fourBits[0] = '0';
      fourBits[1] = '0';
      fourBits[2] = binary[0];
      fourBits[3] = binary[1];
      
      hex[0] = decToHex(fourBitsToDec(fourBits));
      hex[1] = '\0';
      printf("Hexadecimal: %s\n", hex);
      return;

    case 3:
      fourBits[0] = '0';
      fourBits[1] = binary[0];
      fourBits[2] = binary[1];
      fourBits[3] = binary[2];
      
      hex[0] = decToHex(fourBitsToDec(fourBits));
      hex[1] = '\0';
      printf("Hexadecimal: %s\n", hex);
      return;

    case 4: 
      fourBits[0] = binary[0];
      fourBits[1] = binary[1];
      fourBits[2] = binary[2];
      fourBits[3] = binary[3];
      
      hex[0] = decToHex(fourBitsToDec(fourBits));
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

    hex[j] = decToHex(fourBitsToDec(fourBits));

    initial_bit = 0;
    j++; 
  }

  hex[j] = '\0';
  printf("Hexadecimal: %s\n", hex);


  // I implemented this before templated was change
  //printHexInReverse(hex, j);
}

// Convert hexadecimal to decimal
void hexToDecimal(char *hex)
{
  printf("Converting hexadecimal %s to decimal...\n", hex);

  // I will assume that it is unsigned, its impossible to tell otherwise
  unsigned int decimal = 0;

  // count chars
  int chars = 0;
  while (hex[chars] != '\0')
  {
    chars++;
  }

  int exponenet = 0;
  int offset = 0;
  int i = 0;

  while (chars != 0)
  {

    offset = 1;
    i = exponenet;

    while (i != 0)
    {
      offset *= 16;
      i--;
    }
    
    
    decimal += hexToDec(hex[chars-1]) * offset;

    
    exponenet++;
    chars--; 
  }
  

  printf("Decimal: %d\n", decimal);
}

// Cwonvert hexadecimal to binary 
void hexToBinary(char *hex)
{
  printf("Converting hexadecimal %s to binary...\n", hex);
  // Conversion logic will go here

  char binary[33];

  for (int i = 0; i < 32; i++)
  {
    binary[i] = '0';
  }
  binary[32] = '\0';

  // count chars in hex
  int chars = 0;
  while (hex[chars] != '\0')
  {
    chars++;
  }

  int place = 32;

  while (chars != 0)
  {
    const char* bits = hexBits(hex[chars-1]);

    binary[--place] = bits[3];
    binary[--place] = bits[2];
    binary[--place] = bits[1];
    binary[--place] = bits[0];

    chars--;
  }

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
    decimalToHex(atoi(argv[2]));
    break;
  case 'b':
    if (checkIfInvalidBinary(argv[2]) == 1)
    {
      return 1;
    }
    
    binaryToDecimal(argv[2]);
    binaryToHex(argv[2]);
    break;
  case 'h':
    if (checkIfInvalidHex(argv[2]) == 1)
    {
      return 1;
    }
    hexToBinary(argv[2]);
    hexToDecimal(argv[2]);
    break;
  default:
    printf("ERROR: Invalid flag. Run %s to see valid flags.", argv[0]);
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

  if (decimal[i] == '\0')
  {
    printf("ERROR: empty number value");
    return 1;
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

int checkIfInvalidBinary(char *binary)
{
  int i = 0; 

  if (binary[i] == '\0')
  {
    printf("ERROR: empty number value");
    return 1;
  }


  while (binary[i] != '\0')
  {
    if (strtoull(binary, NULL, 2) > 4294967295 || i > 32)
    {
      printf("ERROR: binary value is too large to fit in unsigned 32 bits.");
      return 1;
    }

    if (binary[i] != '0' && binary[i] != '1')
    {
      printf("ERROR: binary contains illegal characters");
      return 1;
    }

    i++; 
  }

  return 0;
}

int checkIfInvalidHex(char *hex)
{
  int i = 0; 

  if (hex[i] == '\0')
  {
    printf("ERROR: empty number value");
    return 1;
  }

  while (hex[i] != '\0')
  {
    if (strtoull(hex, NULL, 16) > 4294967295 || i > 8)
    {
      printf("ERROR: hex value is too large to fit in unsigned 32 bits.");
      return 1;
    }

    if ((hex[i] < '0' || hex[i] > '9') && 
        (hex[i] < 'A' || hex[i] > 'F') &&
        (hex[i] < 'a' || hex[i] > 'f')
       )
    {
      printf("ERROR: hex value has illegal characters.");
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

  printf("Invalid input");
  return 'm';
}

int fourBitsToDec(char bits[])
{
  return ((bits[0] - '0') * 8) + ((bits[1] - '0') * 4) + ((bits[2] - '0') * 2) + ((bits[3] - '0') * 1);
}

char* hexBits(char hex)
{
  switch (hex) 
  {
    case '0':
      return "0000";
    case '1':
      return "0001";
    case '2':
      return "0010";
    case '3':
      return "0011";
    case '4':
      return "0100";
    case '5':
      return "0101";
    case '6':
      return "0110";
    case '7':
      return "0111";
    case '8':
      return "1000";
    case '9':
      return "1001";
    case 'a':
      return "1010";
    case 'b':
      return "1011";
    case 'c':
      return "1100";
    case 'd':
      return "1101";
    case 'e':
      return "1110";
    case 'f':
      return "1111";
    case 'A':
      return "1010";
    case 'B':
      return "1011";
    case 'C':
      return "1100";
    case 'D':
      return "1101";
    case 'E':
      return "1110";
    case 'F':
      return "1111";
  }
  printf("hexBits: Invalid input value: %c\n", hex);
  return "no";
}

char flipBit(char bit)
{
  if (bit == '0')
  {
    return '1';
  }

  return '0';
}