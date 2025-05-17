#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <String.h>

//rounding machine ---> to minimize the problem of "calculating error"
double rounding (double input, int digits) {
    long long cur = (long long) (input * pow(10, digits)) * 10; 

    input = input * pow(10, digits + 1); 
    long long i = (long long) input; 

    if(i - cur <= 4) {
        return (double) cur / pow(10, digits + 1);  
    }
    else {
        cur = cur / 10; 
        cur++; 
        return (double) cur / pow(10, digits); 
    }
}

