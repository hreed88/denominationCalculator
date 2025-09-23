#ifndef CHANGE_MACHINE_H
#define CHANGE_MACHINE_H

#include <stdbool.h>

typedef struct {
    unsigned long long oneHundred;
    unsigned int * denominations;
}denominationResult; 

denominationResult calculateDenominations(unsigned long long * left , unsigned int * right);
void printDenominations(denominationResult denomArr);
bool convertToNums(unsigned long long * left, unsigned int * right, char leftString[], char rightString[]);
int run1();
int run2(char* uInput);
#endif // CHANGE_MACHINE_H