
#include <string.h>

#include <errno.h>
#include <limits.h>

#include "changeMachine.h"


//used in printDenominations
char *stringArr[] = {"%lld $100 Bill(s)\n", "%d $50 Bill(s)\n","%d $20 Bill(s)\n","%d $10 Bill(s)\n","%d $5 Bill(s)\n",
                     "%d $1 Bill(s)\n","%d Quarter(s)\n","%d Dime(s)\n","%d Nickel(s)\n","%d Pennie(s)\n"};

//input: use unsgined long long to represent the "integer" part of the number
//       use unsigned int for fractional part of the number since we only need to represent 0 - 99
//output: output struct that contains an int* array
//        (these are for smaller denominations since they will likely stay in the int range)
//        and a unsigned long long to hold the 100s denominations since this will be a number comaprable to input
//Notes: Should use a greedy approach since we want largest to smallest denominations
denominationResult calculateDenominations(unsigned long long * left, unsigned int * right){

    int intArr[9] = {50,20,10,5,1,25,10,5,1};

    static denominationResult myResult;
    myResult.oneHundred = 0;
    myResult.denominations = malloc(sizeof(unsigned int) * 9);

    //calculate 100's
    //keep this out of the loop since we are storing to a different location
    myResult.oneHundred = *left / 100LL;
    //update current num now
    *left %= 100LL;

    //loop through intArr to calculate rest of denominations
    for(int i = 0; i < (sizeof(intArr) / sizeof(int)); i++){
        //calculate whole nums
        if(i < 5){
            myResult.denominations[i] = *left / intArr[i];
            *left %= intArr[i];
        }
        //else calculate fractional nums
        else{
            myResult.denominations[i] = *right / intArr[i];
            *right %= intArr[i];
        }
    }

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
    for(int i = 0; i < 9; i++){
        printf(stringArr[i+1], denomArr.denominations[i]);
    }
}

//Description: Function to convert strings to nums, with overflow and underflow handling
//Input: left/right are pointers so we can store converted numbers
//       leftString/rightString, contain strings of numbers left and right of decimal respectivly
//Output: updates pointers, and returns a bool based on if conversions are valid
bool convertToNums(unsigned long long * left, unsigned int * right, char leftString[], char rightString[]){
        char *posPtr;
        //check if rightString is only size of 1. indicating a zero was not added
        //if so pad an extra zero to the back
        if(strlen(rightString) == 1){
            rightString[strlen(rightString)] = '0';
            rightString[strlen(rightString)+1] = '\0';
        }
        //ensure errno is set to 0 before each strto
        errno = 0;
        //convert left side to ulong long (string to unsigned long long)
        *left = strtoull(leftString, &posPtr ,10);
        //check for overflow or underflow
        if(errno == ERANGE){
            if(*left == ULLONG_MAX){
                fprintf(stderr, "\nERROR OVERFLOW DETECTED! Input is out of range!\n");
            }else {
            //else we have underflow
            //note underflow shouldn't happen regardless because of sscanf
           fprintf(stderr,"\nERROR UNDERFLOW DETECTED! Input is out of range!\n");
            }
            return false;
        }
        //convert right side side to uint (string to unsigned long)
        *right = strtoul(rightString, &posPtr ,10);
        //check for overflow or underflow
        //note underflow and overflow shouldn't happen regardless because of sscanf
        if(errno == ERANGE){
            if(*right == UINT_MAX){
                fprintf(stderr,"\nERROR OVERFLOW DETECTED! Input is out of range!\n");
            }else{
            //else we have underflow
            fprintf(stderr,"\nERROR UNDERFLOW DETECTED! Input is out of range!\n");
            }
            return false;
        }
        //return true if we make it all the way through
        return true;
}

//used to run the program when no arguments are givien in the terminal
//will run until user decides to quit
int run1(){
    unsigned long long * left = malloc(sizeof(unsigned long long));
    unsigned int * right = malloc(sizeof(unsigned int));
    char leftString[32];
    char rightString[8];
    char buffer[64]; 
    

    while(true){
        bool inputCorrect = false;

        while(!inputCorrect){
        
            printf("\nPlease enter the dollar ammount you would like change for (Input should be in the form *.XX): ");
            //read user input
            if(fgets(buffer, sizeof(buffer), stdin) != NULL){
                //input is larger than our buffer so clear the stdin and ask user for input again
                if(buffer[strlen(buffer) - 1] != '\n'){
                    fprintf(stderr,"\nERROR! Buffer Overflow Detected!\n");
                    //clear the rest of the stdin
                    char c = 'n';
                    while(c != '\n' && c != EOF){
                        c = getchar();
                    }
                    continue;
                }   
            }else{
                //fgets failed retry
                fprintf(stderr,"\nError getting input\n");
                continue;
            }

            //break up both sides into respective strings
            int inputResult = sscanf(buffer, "%[0-9].%2[0-9]", leftString, rightString);
            //check for malformed input
            //if sscanf doesnt produce 2 this means that it was unable to match the expected input
            if(inputResult == 2){
                //convert to longs and ints, also checks for overflow/underflow
                if(!convertToNums(left, right, leftString, rightString)){
                    continue;
                }
                inputCorrect = true;
            }else{
                fprintf(stderr,"\nERROR INPUT IS MALFORMED!\nInput must be a positve number and in the form *.XX\n\n");
                continue;
            }
            
    
        }

        denominationResult result = calculateDenominations(left, right);

        printDenominations(result);

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

    int inputResult = sscanf(uInput, "%[0-9].%2[0-9]", leftString, rightString);

    //check if the input is valid
    if(inputResult != 2){
        fprintf(stderr,"\nERROR INPUT IS MALFORMED!\nInput must be a positve number and in the form *.XX\n\n");
        //free left and right
        free(left);
        free(right);
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