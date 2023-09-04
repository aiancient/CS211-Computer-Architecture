#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // SETUP

    // first, read the minuend (number to be subtracted from)
    bool minuend[8]; // suggested that you store bits as array of bools; minuend[0] is the LSB
    for (int i=7; 0<=i; i--) { // read MSB first as that is what comes first in the file
        /* ... */
        unsigned char bit;
        if (!fscanf(fp, "%c", &bit)) {
            perror("reading bit failed");
            exit(EXIT_FAILURE);
        }
        
        if(bit == '0')
        {
            minuend[i] = false; 
        }
        else
        {
            minuend[i] = true; 
        }
    }

    fscanf(fp,"\n"); 

   // second, read the subtrahend (number to subtract)
    bool subtrahend[8]; // suggested that you store bits as array of bools; subtrahend[0] is the LSB
    for (int i=7; 0<=i; i--) { // read MSB first as that is what comes first in the file
        /* ... */
        unsigned char bit;
        if (!fscanf(fp, "%c", &bit)) {
            perror("reading bit failed");
            exit(EXIT_FAILURE);
        }

        if(bit == '0')
        {
            subtrahend[i] = false; 
        }
        else
        {
            subtrahend[i] = true; 
        }
    }

    // WE WILL DO SUBTRACTION BY NEGATING THE SUBTRAHEND AND ADD THAT TO THE MINUEND

    // Negate the subtrahend
    // flip all bits
    /* ... */
    for(int i=7; 0<=i; i--)
    {
        if(subtrahend[i] ==false)
        {
            subtrahend[i] = true; 
        }
        else{
            subtrahend[i] = false; 
        }
    }

    // add one
    bool carry = true; // to implement the 'add one' logic, we do binary addition logic with carry set to true at the beginning
    for (int i=0; i<8; i++) { // iterate from LSB to MSB
        /* ... */
        if(subtrahend[i]==true)
        {
            if(carry)
            {
                subtrahend[i] = false; 
            }
            else{
                subtrahend[i] = true; 
            }
        }

        else{
            if(carry)
            {
                subtrahend[i] = true; 
                carry = false; 
            }
            else{
                subtrahend[i] = false; 
            }
        }

    }

    bool top = false; 
    //Add the minuend and the negated subtrahend
    bool difference[8];
    /* ... */
    for(int i=0; i<8; i++)
    {
        if(top)
        {
            if(subtrahend[i] == false && minuend[i] ==false)
            {
                difference[i] = true; 
                top = false; 
            }

            if(subtrahend[i] == true && minuend[i] ==true)
            {
                difference[i] = true; 
            }

            if((subtrahend[i] == false && minuend[i] == true) || (subtrahend[i] == true && minuend[i] == false) )
            {
                difference[i] = false; 
            }

        }

        else{

            if(subtrahend[i] == false && minuend[i] == false)
            {
                difference[i] = false; 
            }

            if(subtrahend[i] == true && minuend[i] == true)
            {
                difference[i] = false; 
                top = true; 
            }

            if((subtrahend[i] == false && minuend[i] == true) || (subtrahend[i] == true && minuend[i] == false) )
            {
                difference[i] = true; 
            }

        }
    }

    // print the difference bit string
    for (int i=7; 0<=i; i--)
    {
        printf("%d",difference[i]);
    }

    return EXIT_SUCCESS;

}
