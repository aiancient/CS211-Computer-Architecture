#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define EXP_SZ 8
#define FRAC_SZ 23

int exponentt(float exponent)
{
    int result = 1; 
    while(exponent>0)
    {
        result = result * 2; 
        exponent--; 
    }
    return result; 
}

float exponenttF(float exponent)
{
    int result = 1; 
    while(exponent>0)
    {
        result = result * 2; 
        exponent--; 
    }
    return ((float) 1/result); 
}

int main(int argc, char *argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // SETUP

    // first, read the binary number representation of float point number

    bool bn[32];
    for (int i=EXP_SZ+FRAC_SZ; 0<=i; i--) { // read MSB first as that is what comes first in the file
        /* ... */
        unsigned char bit;
        if (!fscanf(fp, "%c", &bit)) {
            perror("reading bit failed");
            exit(EXIT_FAILURE);
        }
        
        if(bit == '0')
        {
            bn[i] = false; 
        }
        else
        {
            bn[i] = true; 
        }
    }

    // float number = *(float *)&binary; // you are not allowed to do this.

    /* ... */

    // E
    /* ... */
    int fe = 0;
    int count = 0; 
    for(int i = 23; i<=30;i++)
    { 
        int numm = (bn[i] == true)? 1: 0;  
        fe = fe + (numm * exponentt(count));
        count++; 
    }

    fe = fe - (exponentt(7) - 1);
  

    // M
    /* ... */
    float fm = 1.0;
    int countt = 23; 
    for(float i = 0; i<=22;i++)
    {
        int numm = (bn[(int) i] == true)? 1: 0;   
        fm = fm + (numm * exponenttF(countt));
        countt--; 
    }

    int sign = bn[31] == true? 1 : 0; 

    // https://www.tutorialspoint.com/c_standard_library/c_function_ldexp.htm
    double number = ldexp ( fm, fe );
    number = sign ? -number : number;
    printf("%e\n", number);

    return EXIT_SUCCESS;

}
