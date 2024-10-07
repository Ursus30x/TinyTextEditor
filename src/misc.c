#include <math.h>
#include <stdlib.h>


int getNumOfDigits(const int number){
    return floor(log10(abs(number + 1))) + 1;
}