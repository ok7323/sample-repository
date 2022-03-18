#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "float.h"
#define A 2

#define TRUE 1
#define FALSE 0
int is_special(float f)
{
    int check = 0;
    // Check all of exponent bits for Special Values.
    for(int i = 30; i > 22; i--)
                check += ((*(unsigned int*)&f>>i)&0x01);
    // True if all of exponent bits are 8, false otherwise.
    if(check == 8)
        return TRUE;
    else
        return FALSE;
}


int is_denormal(float f)
{
    int check = 0;
    // Check all of exponent bits for denormalized values.
    for(int i = 30; i > 22; i--)
                check += ((*(unsigned int*)&f>>i)&0x01);
    // True if all of exponent bits are 0, false otherwise.
    if(check)
        return FALSE;
    else
        return TRUE;
}


float get_M(float f)
{
    float M=0.0;
    // Shift all of Mantissa bits.
    for(int i = 22; i>-1; i--){
        if (((*(unsigned int*)&f>>i)&0x01)==1)
            M += pow(0.5,23-i);
    }
    if (is_denormal(f))
        return M;
    else
        return 1+M;
}


int get_s(float f)
{
    int sign;
    // shift sign value.
    sign=((*(unsigned int*)&f>>31)&0x01);
    if(sign)
        return -1;
    else
        return 1;
}


int get_E(float f)
{
    int E=0;
    // shift all of exponent bits.
    for(int i = 30; i > 22; i--){
        if (((*(unsigned int*)&f>>i)&0x01)==1)
            E += pow(2,i-23);
    }
    if(E == 0)
        return -126; // special rules for denormalized values.
    else
        return E-127; // biased representation.
}

