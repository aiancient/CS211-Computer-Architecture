#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
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

double exponenttmethod(double ans,int exponent)
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

    // float value = *(float *) &binary; // you are not allowed to do this.
    // unsigned int binary = *(unsigned int*) &value; // you are not allowed to do this.

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // SETUP

    // first, read the binary number representation of multiplier
    /* ... */
    bool multiplier[32];
    bool zeroNum = true; 
    for (int i=EXP_SZ+FRAC_SZ; 0<=i; i--) { // read MSB first as that is what comes first in the file
        /* ... */
        unsigned char bit;
        if (!fscanf(fp, "%c", &bit)) {
            perror("reading bit failed");
            exit(EXIT_FAILURE);
        }
        
        if(bit == '0')
        {
            multiplier[i] = false; 
        }
        else
        {
            zeroNum = false; 
            multiplier[i] = true; 
        }
    }

    int fe = 0;
    int count = 0; 
    for(int i = 23; i<=30;i++)
    { 
        int numm = (multiplier[i] == true)? 1: 0;  
        fe = fe + (numm * exponentt(count));
        count++; 
    }

    fe = fe - (exponentt(7) - 1);

    float fm = 1.0;
    int countt = 23; 
    for(float i = 0; i<=22;i++)
    {
        int numm = (multiplier[(int) i] == true)? 1: 0;   
        fm = fm + (numm * exponenttF(countt));
        countt--; 
    }

    int sign = multiplier[31] == true? 1 : 0; 

    double number = ldexp ( fm, fe );
    number = sign ? -number : number;

    // notice that you are reading two different lines; caution with reading
    /* ... */
    fscanf(fp,"\n"); 

    // first, read the binary number representation of multiplicand
    /* ... */
    bool multiplicand[32];
    bool zeroNumSec = true; 
    for (int i=EXP_SZ+FRAC_SZ; 0<=i; i--) { // read MSB first as that is what comes first in the file
        /* ... */
        unsigned char bit;
        if (!fscanf(fp, "%c", &bit)) {
            perror("reading bit failed");
            exit(EXIT_FAILURE);
        }
        
        if(bit == '0')
        {
            multiplicand[i] = false; 
        }
        else
        {
            zeroNumSec = false; 
            multiplicand[i] = true; 
        }
    }

    int fee = 0;
    int counttt = 0; 
    for(int i = 23; i<=30;i++)
    { 
        int numm = (multiplicand[i] == true)? 1: 0;  
        fee = fee + (numm * exponentt(counttt));
        counttt++; 
    }

    fee = fee - (exponentt(7) - 1);

    float fmm = 1.0;
    int countttt = 23; 
    for(float i = 0; i<=22;i++)
    {
        int numm = (multiplicand[(int) i] == true)? 1: 0;   
        fmm = fmm + (numm * exponenttF(countttt));
        countttt--; 
    }

    int signn = multiplicand[31] == true? 1 : 0; 

    double numberr = ldexp ( fmm, fee );
    numberr = signn ? -numberr : numberr;

    double value = number*numberr; 
    if(zeroNum==true || zeroNumSec==true)
    {
        value = 0.0; 
    }


    bool signnnn = value<0.0;
    printf("%d_",signnnn);
    //assert (signnnn == (1&ref_bits>>(EXP_SZ+FRAC_SZ))); // validate your result against the reference

    // THE EXP FIELD
    // find the exponent E such that the fraction will be a canonical fraction:
    // 1.0 <= fraction < 2.0
    double fraction = signnnn ? -value : value;
    signed int input = (int) fraction; 

    signed short trial_exp=(1<<(EXP_SZ-1))-1; // start by assuming largest possible exp (before infinity)
    //printf("TrailExp: %d\n",trial_exp); 
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
            double ans = (double) (fraction / (exponenttmethod(2,i)));
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
       // assert (exp_bit == (1&ref_bits>>(exp_index+FRAC_SZ))); // validate your result against the reference
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
    double frac = signnnn ? -decVal : decVal;
    bool canPrint = false; 

    int frac_indexx = 23; 
     bool frac_array[FRAC_SZ+1];
    
  //  printf("\n%d  Final Num: %d\n",changedValue,finalNum);
  //  printf("input: %d",input); 
   // printf("\nFraction for Frac Part: %f\n",frac);

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
       //assert (frac_bit == (1&ref_bits>>frac_index)); // validate your result against the reference
    }

    return(EXIT_SUCCESS);

}
