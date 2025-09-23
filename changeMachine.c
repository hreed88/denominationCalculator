#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <errno.h>
#include <limits.h>

#include "changeMachine.h"

char *stringArr[] = {"%lld $100 Bill(s)\n", "%d $50 Bill(s)\n","%d $20 Bill(s)\n","%d $10 Bill(s)\n","%d $5 Bill(s)\n","%d $2 Bill(s)\n",
                     "%d $1 Bill(s)\n","%d Quarter(s)\n","%d Dime(s)\n","%d Nickel(s)\n","%d Pennie(s)\n"};

// input: use unsgined long long to represent the "integer" part of the number
//       use unsigned int for fractional part of the number since we only need to represent 0 - 99
//output: output struct that contains an int* array
//                  (these are for smaller denominations since they will likely stay in the int range)
//        and a unsigned long long to hold the 100s denominations since this will a number comaprable to input
//Should use a greedy approach since we want largest to smallest denominations
denominationResult calculateDenominations(unsigned long long * left, unsigned int * right){

    static denominationResult myResult;
    myResult.oneHundred = 0;
    myResult.denominations = malloc(sizeof(unsigned int) * 10);

    //calculate 100's
    myResult.oneHundred = *left / 100LL;
    //update current num now
    *left %= 100LL;
    
    //calculate 50's 
    myResult.denominations[0] = *left / 50;
    //update current num
    *left %= 50;

    //calculate 20's
    myResult.denominations[1] = *left / 20;
    //update current num
    *left %= 20;

    //calculate 10's
    myResult.denominations[2] = *left / 10;
    //update current num
    *left %= 10;

    //calculate 5's
    myResult.denominations[3] = *left / 5;
    //update current num
    *left %= 5;

    //calculate 2's
    myResult.denominations[4] = *left / 2;
    //update current num
    *left %= 2;

    //finaly 1's
    //no division should be necessary at this point
    myResult.denominations[5] = *left;

    //now for fractional part
    //calculate 0.25's
    myResult.denominations[6] = *right / 25;
    //update current num
    *right %= 25;

    //calculate 10's
    myResult.denominations[7] = *right / 10;
    //update current num
    *right %= 10;

    //calculate 5's
    myResult.denominations[8] = *right / 5;
    //upadte current num
    *right %= 5;

    //same thing as before with ones, no calculation necessary
    myResult.denominations[9] = *right;



    return myResult;

}

//Name: printDenominiations
//Input: denominationResult
//Output: None
//Description: Prints out the calculated denominations in a readable format
void printDenominations(denominationResult denomArr){
    printf("Your change is:\n");
    //print the 100s
    printf(stringArr[0], denomArr.oneHundred);
    for(int i = 0; i < 10; i++){
        printf(stringArr[i+1], denomArr.denominations[i]);
    }
}

//Description: Function to convert strings to nums, with overflow and underflow handling
bool convertToNums(unsigned long long * left, unsigned int * right, char leftString[], char rightString[]){
        char *posPtr;
        //ensure errno is set to 0 before each strto
        errno = 0;
        //convert left side to ulong long (string to unsigned long long)
        *left = strtoull(leftString, &posPtr ,10);
        //check for overflow or underflow
        if(errno == ERANGE){
            if(*left == ULLONG_MAX){
                printf("\nERROR OVERFLOW DETECTED! Input is out of range!\n");
            }else {
            //else we have underflow
            //note underflow shouldn't happen regardless because of sscanf
            printf("\nERROR UNDERFLOW DETECTED! Input is out of range!\n");
            }
            return false;
        }
        //convert right side side to uint (string to unsigned long)
        *right = strtoul(rightString, &posPtr ,10);
        //check for overflow or underflow
        //note underflow and overflow shouldn't happen regardless because of sscanf
        if(errno == ERANGE){
            if(*right == UINT_MAX){
                printf("\nERROR OVERFLOW DETECTED! Input is out of range!\n");
            }else{
            //else we have underflow
            printf("\nERROR UNDERFLOW DETECTED! Input is out of range!\n");
            }
            return false;
        }
        return true;
}

//used to run the program when no arguments are givien in the terminal
//will run until user decides to quit
int run1(){
    unsigned long long * left = malloc(sizeof(unsigned long long));
    unsigned int * right = malloc(sizeof(unsigned int));
    char leftString[64];
    char rightString[8];
    char buffer[64]; 
    

    while(true){
        //*left, *right = 0;
        bool inputCorrect = false;

        while(!inputCorrect){
        
            printf("\nPlease enter the dollar ammount you would like change for (Input should be in the form *.XX): ");
            //read user input
            if(fgets(buffer, sizeof(buffer), stdin) != NULL){
                //input is larger than our buffer so clear the stdin and ask user for input again
                if(buffer[strlen(buffer) - 1] != '\n'){
                    printf("\nERROR! Buffer Overflow Detected!\n");
                    //clear the rest of the stdin
                    char c = 'n';
                    while(c != '\n' && c != EOF){
                        c = getchar();
                    }
                    continue;
                }   
            }else{
                //fgets failed retry
                printf("\nError getting input\n");
                continue;
            }

            //break up both sides into respective strings
            int inputResult = sscanf(buffer, "%[0-9].%2[0-9]", leftString, rightString);
            // printf("\nLeft %s\n", leftString);
            // printf("\nRight %s\n", rightString);
            // printf("\nInput Result %d\n", inputResult);
            //check for malformed input
            //if sscanf doesnt produce 2 this means that it was unable to match the expected input
            if(inputResult == 2){
                //convert to longs and ints, also checks for overflow/underflow
                if(!convertToNums(left, right, leftString, rightString)){
                    continue;
                }
                inputCorrect = true;
            }else{
                printf("\nERROR INPUT IS MALFORMED!\nInput must be a positve number and in the form *.XX\n\n");
                continue;
            }

            printf("\nleft side = %lld\n", *left);
            printf("\nright side = %d\n", *right);
            printf("\nBuffer result %s \n", buffer);
            //int inputResult = sscanf(buffer, " %lld.%2d", left, right);
            
    
        }

        //check how long calculation takes
        //get new time
        clock_t before = clock();
        denominationResult result = calculateDenominations(left, right);
        clock_t result2_time = clock() - before;

        printDenominations(result);

        printf("Time taken for solution 1: %ld\n", result2_time);

        //free denominations
        free(result.denominations);

        //check if user wants to calculate another number
        printf("\nWould you like to calculate another number? (Y/N | y/n)");
        fgets(buffer, sizeof(buffer), stdin);
        if(buffer[0] == 'n' || buffer[0] == 'N'){
            break;
        }

    }
    //free malloced memory
    free(left);
    free(right);
    return 0;
}

//used to run the calculator when user give argument when running the program
int run2(char* uInput){

    unsigned long long * left = malloc(sizeof(unsigned long long));
    unsigned int * right = malloc(sizeof(unsigned int));
    char leftString[64];
    char rightString[8];
    printf("\n%s\n", uInput);
    int inputResult = sscanf(uInput, "%[0-9].%2[0-9]", leftString, rightString);

    //check if the input is valid
    if(inputResult != 2){
        printf("\nERROR INPUT IS MALFORMED!\nInput must be a positve number and in the form *.XX\n\n");
        return 2;
    }else{
    
    if(!convertToNums(left, right, leftString, rightString)){
       free(left);
       free(right);
       return 1;
    }
    
    denominationResult result = calculateDenominations(left, right);

    printDenominations(result);

    //free malloced memory
    free(result.denominations);
    }
    //free these outside of the if/else since they will always be malloced
    free(left);
    free(right);
    return 0;
}