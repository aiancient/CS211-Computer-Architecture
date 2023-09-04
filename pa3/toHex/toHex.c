#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return 0;
    }

    // first, read the number
    signed int input;
    fscanf(fp, "%d", &input);

    // print bits; you will see this kind of for loop often in this assignment
    for ( int bit=3; 0<=bit; bit-- ) {
        size_t bit_val = ((1<<4)-1) & input>>bit*4; // shift and mask
        //char character = bit_val ? '1' : '0';
        if(bit_val>9)
        {
            switch(bit_val) {
                case 10:
                    printf("A"); 
                    break; 

                case 11: 
                    printf("B"); 
                    break; 

                case 12: 
                    printf("C"); 
                    break; 

                case 13: 
                    printf("D"); 
                    break; 

                case 14: 
                    printf("E"); 
                    break; 

                case 15: 
                    printf("F"); 
                    break; 
            }
        }

        else
        {
            printf("%ld",bit_val);
        }
    }
    printf("\n");

    return EXIT_SUCCESS;

}
