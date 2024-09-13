#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>

// Function prototypes
void decimalToBinary(int decimal);
void decimalToHex(int decimal);
void binaryToDecimal(char *binary);
void hexToDecimal(char *hex);

// my funcs
void ones_complement(char* binary_32bit);
void twos_complement(char* binary_32bit);

// Main function to handle inputs and trigger conversions
int main(int argc, char *argv[]) {
    // Ensure correct number of arguments are provided
    if (argc != 3) {
        printf("Usage: %s -[d|b|h] [number]\n", argv[0]);
        printf("Options:\n");
        printf("-d [decimal]     Convert decimal to binary and hexadecimal\n");
        printf("-b [binary]      Convert binary to decimal and hexadecimal\n");
        printf("-h [hexadecimal] Convert hexadecimal to decimal and binary\n");
        return 1;
    }

    // Extract the flag and value from arguments
    // Check which flag was provided and call the appropriate function

    // argv[1] is the option select (-d, -b, -h) and the second value in that array is the letter (d, b, h).
    switch (argv[1][1]) {
        case 'd':
            decimalToBinary(atoi(argv[2]));
            decimalToHex(atoi(argv[2]));
            break;
        case 'b':
            binaryToDecimal(argv[2]);
            break;
        case 'h':
            hexToDecimal(argv[2]);
            break;
        default:
            printf("Invalid option.");
            return 1;
    }

    return 0;
}

// Function to convert decimal to binary (placeholder)
void decimalToBinary(int decimal) {
    printf("Converting decimal %d to binary...\n", decimal);
    // Conversion logic will go here

    
    int negative_flag = 0;
    if ( decimal < 0 ) {        // Do we need to do 
        negative_flag = 1;      // complement conversions? 
        decimal = abs(decimal);
    }

    char binary[33] = { // 32 Bits, null terminated 
                        '0', '0', '0', '0', '0', '0', '0', '0',
                        '0', '0', '0', '0', '0', '0', '0', '0',
                        '0', '0', '0', '0', '0', '0', '0', '0',
                        '0', '0', '0', '0', '0', '0', '0', '0',
                        '\0'
                      };

    int i = 31;     
    while ( decimal > 0 ) {              // % 2 will get us correct bit value 
        binary[i] = (decimal % 2) + '0'; // '0' converts an int to a char 
        decimal /= 2;
        i--;
    }

    if ( negative_flag == 1 ) {
        ones_complement(binary); // Convert to one then two's 
        twos_complement(binary); // complemenet for negatives
    }

    printf("Binary: %s\n", binary);
}

// Function to convert decimal to hexadecimal (placeholder)
void decimalToHex(int decimal) {
    printf("Converting decimal %d to hexadecimal...\n", decimal);
    // Conversion logic will go here

    printf("Hexadecimal: %X\n", decimal);
}

// Function to convert binary to decimal (placeholder)
void binaryToDecimal(char *binary) {
    printf("Converting binary %s to decimal...\n", binary);
    // Conversion logic will go here
    // I WILL ASSUME THAT THE INPUT IS 32 BITS LIKE NORMAL C int

    int decimal = 0;
    int exponent = 0;
    int negative_flag = 0;

    if ( binary[0] == '1') {                                // is it negative?
        negative_flag = 1;
    }

    for ( int i = 31; i >= 1; i-- ) {                       // (0 or 1) * 2^placement
        decimal += (binary[i] - '0') * pow(2, exponent);    //  is simple binary -> decimal
        exponent++;
    }

    if ( negative_flag == 1 ) {                             // if it was negative,
        decimal += pow(-2, exponent);                       // do -2^MSB (1 always if neg)
    }                                                       
    
    printf("Decimal: %d\n", decimal);
}

// Function to convert hexadecimal to decimal (placeholder)
void hexToDecimal(char *hex) {
    printf("Converting hexadecimal %s to decimal...\n", hex);
    // Conversion logic will go here

    int decimal = (int)strtol(hex, NULL, 16);


    printf("Decimal: %d\n", decimal);
}



// My functions to do logic 

// converts a 32-bit binary cstring to its ones_complement 
// Input must be 32 bits and null terminated.
void ones_complement(char* binary_32bit) {
    for ( int j = 0; j < 32; j++ ) {
        if ( binary_32bit[j] == '0' ) {
            binary_32bit[j] = '1';
        } else {
            binary_32bit[j] = '0';
        }
    }
}

// Adds one to a ones_complement notation, 32 bit binary number. 
// Input must be 32 bits and null terminated.
void twos_complement(char* binary_32bit) {

    // Adding 1 is as simple as finding the rightmost 0, 
    // flipping it and all the 1's to its right 
    for ( int i = 31; i >= 0; i--) {
        if ( binary_32bit[i] == '1' ) {
            binary_32bit[i] = '0';
        } else if ( binary_32bit[i] == '0' ){
            binary_32bit[i] = '1';
            break;
        }
    }

}
