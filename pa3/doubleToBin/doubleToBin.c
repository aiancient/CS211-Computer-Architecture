#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define EXP_SZ 11
#define FRAC_SZ 52

double exponentt(double ans,int exponent)
{
    double result = 1; 
    while(exponent>0)
    {
        result = result * ans; 
        exponent--; 
    }
    return result; 
}

double exponentN(double ans,int exponent)
{
    int result = 1; 
    while(exponent>0)
    {
        result = result * 2; 
        exponent--; 
    }
    return ((double) 1/result); 
}


int main(int argc, char *argv[]) {

    // SETUP

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return 0;
    }

    // first, read the number
    double value;
    fscanf(fp, "%lf", &value);

    // the reference solution ('the easy way')
    // you are not allowed to print from this casted 'ref_bits' variable below
    // but, it is helpful for validating your solution
   unsigned long int ref_bits = *(unsigned long int*) &value;

    // THE SIGN BIT
    bool sign = value<0.0;
    printf("%d_",sign);
    assert (sign == (1&ref_bits>>(EXP_SZ+FRAC_SZ))); // validate your result against the reference

    // THE EXP FIELD
    // find the exponent E such that the fraction will be a canonical fraction:
    // 1.0 <= fraction < 2.0
    double fraction = sign ? -value : value;
    signed int input = (int) fraction; 

    signed short trial_exp=(1<<(EXP_SZ-1))-1; // start by assuming largest possible exp (before infinity) 
    // do trial division until the proper exponent E is found
    /* ... */
    for(short i = 0; i<=trial_exp; i++)
    {
      //  printf("Value of 2^: %d",2^i); 
        if((value<=0 && value>-1) || (value>0 && value<1))
        {
            if(exponentN(2,i)<=fraction)
            {
                trial_exp=-i; 
                break; 
            }
        }

        else{
            double ans = (double) (fraction / (exponentt(2,i)));
            if(1.0<=ans && ans<2.0)
            {
                trial_exp=i;
                break;
            }

        }
    }

    unsigned short bias = (1<<(EXP_SZ-1))-1;
    signed short exp = trial_exp + bias;

    if(fraction==0 || fraction<0.0000000000000001)
    {
        exp = 0; 
    }

    for ( int exp_index=EXP_SZ-1; 0<=exp_index; exp_index-- ) {
        bool exp_bit = 1&exp>>exp_index;
        printf("%d",exp_bit);
        assert (exp_bit == (1&ref_bits>>(exp_index+FRAC_SZ))); // validate your result against the reference
    }
    printf("_");



    // you get partial credit by getting the exp field correct
    // even if you print zeros for the frac field next
    // you should be able to pass test cases 0, 1, 2, 3

    // THE FRAC FIELD
    // prepare the canonical fraction such that:
    // 1.0 <= fraction < 2.0
    /* ... */

    int changedValue = (int) value; 
    double decVal = value - changedValue; 
    double frac = sign ? -decVal : decVal;
    bool canPrint = false; 

    int frac_indexx = 52; 
     bool frac_array[FRAC_SZ+1]; 
    for ( int bit=sizeof(signed int)*8-1; 0<=bit; bit-- ) {
        size_t bit_val = ((1<<1)-1) & input>>bit*1; // shift and mask
        if(canPrint==false && bit_val==1)
        {
            canPrint = true; 
            continue; 
        }
        if(canPrint)
        {
            frac_array[frac_indexx] = bit_val; 
            frac_indexx--; 
        }
    }

    // one extra LSB bit for rounding
    for ( int frac_index=frac_indexx; 0<=frac_index; frac_index-- ) {

        if(frac==0)
        {
           frac_array[frac_indexx] = false;
            frac_indexx--;
            continue; 
        }

        frac = (2.0*frac); 
        int sub = (int) frac;  
        if(!canPrint && frac>1)
        {
            frac = frac - 1;  
            canPrint=true; 
            continue; 
        }

        if(canPrint && frac>=0 && frac<1)
        {
          frac_array[frac_indexx] = false;
          frac_indexx--; 
        }

        else if(canPrint && frac>=1 && frac<2)
        {
          frac_array[frac_indexx] = true; 
          frac_indexx--; 
          frac = frac - 1; 
        }

        else if(canPrint)
        {
          frac_array[frac_indexx] = false; // frac set to zero to enable partial credit
          frac = frac - sub; 
          frac_indexx--; 
        }
        
        /* ... */
    }

    // rounding
    /* ... */
    for ( int frac_index=FRAC_SZ-1; 0<=frac_index; frac_index-- ) {
        bool frac_bit = frac_array[frac_index+1]; // skipping the extra LSB bit for rounding
        printf("%d", frac_bit);
       assert (frac_bit == (1&ref_bits>>frac_index)); // validate your result against the reference
    }

}
