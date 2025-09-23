#ifndef CHANGE_MACHINE_H
#define CHANGE_MACHINE_H

#ifdef __cplusplus
extern "C"{
#endif
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
    #ifdef __cplusplus
}
#endif

#endif // CHANGE_MACHINE_H