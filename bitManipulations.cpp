// this program shows how to quicksort floats and ints

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//#include <bitset>


static void printHex( void* input, size_t numBytes ) {
    unsigned char* hexList = (unsigned char*) input;
    if (input == NULL) return;
    while ( numBytes > 0 ) {
        -- numBytes;
        printf("%02x ", hexList[numBytes]);
    }
    printf("\n");
}

static void printBits( void* input, size_t numBytes ) {
    unsigned char* hexList = (unsigned char*) input;
    if (input == NULL) return;
    
    while ( numBytes > 0 ) {
        -- numBytes;
        
        // ">>" shifts bits in i (by 1 here), so i = 128, 64, 32, etc
        //  !x shorthand for (x == 0 ? 0 : 1)
        // !!x shorthand for (x != 0 ? 0 : 1).
        for ( int i = 128; i; i >>= 1)
            printf("%x", !! ( hexList[numBytes] & i ) );
        printf(" ");
    }
    printf(" \n");
}

void printBitsFloat( float input ) {
    printBits( &input, sizeof(float) );
}

void printBitsInt( int input ) {
    printBits( &input, sizeof(int) );
}

// this is for big-endian numbers, so from left to right
void turnBitOff( void* input, size_t numBytes, int location ) {
    
    if ( location < 0 || location > numBytes*8 ) return;
    unsigned char* hexList = (unsigned char*) input;
    
    unsigned long int thisByte = location / 8;
    unsigned long int thisBit  = pow(2, (location % 8) - 1);
    
    hexList[thisByte] = hexList[thisByte] & ~thisBit;
}

// this is for big-endian numbers, so from left to right
void turnBitOn( void* input, size_t numBytes, int location ) {
    
    if ( location < 0 || location > numBytes*8 ) return;
    unsigned char* hexList = (unsigned char*) input;
    
    unsigned long int thisByte = location / 8;
    unsigned long int thisBit  = pow(2, (location % 8) - 1);
    
    hexList[thisByte] = hexList[thisByte] | thisBit;
}

// convert an integer into binary digits, store each digit as an element of an array
// 1 becomes { 1, 0, 0, 0 }
// 2 becomes { 0, 1, 0, 0 }
// 3 becomes { 1, 1, 0, 0 } etc.
void int2binaryIntsArray ( int * array, int n ) {
    *array++ = n & 0x1; // *array++ is array[0]
    *array++ = n & 0x2 ? 1 : 0;
    *array++ = n & 0x4 ? 1 : 0;
    *array++ = n & 0x8 ? 1 : 0;
}


//==============================================================================
int main( int argc, char *argv[] ) //  RUN PROGRAM
//==============================================================================
{
    int b = 95;
    printf("%d\n", b);
    printBitsInt(b);
    
    printHex( &b, sizeof(b) );
    printBitsFloat((float)b);
    printBitsFloat(-(float)b);
    printBits( &b, sizeof(b) );
    printBitsInt(-b);
    
    printf("\non and offs\n\n");
    printf("%d\n", b);
    printBitsInt(b);
    turnBitOn(&b, sizeof(b), 6);
    printf("%d\n", b);
    printBitsInt(b);
    turnBitOff(&b, sizeof(b), 1);
    printf("%d\n", b);
    printBitsInt(b);
    
    // floats have some special bit-structure, so not all bits can be accessed
    printf("\nfloats\n\n");
    float a = 3.4;
    printf("%f\n", a);
    printBitsFloat(a);
    turnBitOn(&a, sizeof(a), 10);
    printf("%f\n", a);
    printBitsFloat(a);
    turnBitOff(&a, sizeof(a), 10);
    printf("%f\n", a);
    printBitsFloat(a);
    
    // convert "n" into an array of binary stored as ints
    int maxNumDigits = 4;
    int array[5] = {1, 2, 3, 4, 5};
    int n = 12;
    printf("\noriginal array\n");
    for ( int i = 0; i < maxNumDigits; i++ )
        printf("%d ", array[i]);
    printf("converted %d to binary (in reverse)\n", n);
    int2binaryIntsArray(array, n);
    for ( int i = 0; i < maxNumDigits; i++ )
        printf("%d ", array[i]);
    printf("\n\n");
    
}
//==============================================================================
//==============================================================================
