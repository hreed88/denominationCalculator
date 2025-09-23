int* calculateDenominations2(float * input){

    static int denominations[10] = {0,0,0,0,0,0,0,0,0,0};

    //calculate 100's
    denominations[0] = *input / 100;
    //update current num now
    *input %= 100;
    
    //calculate 50's 
    denominations[1] = *input / 50;
    //update current num
    *input %= 50;

    //calculate 20's
    denominations[2] = *input / 20;
    //update current num
    *input %= 20;

    //calculate 10's
    denominations[3] = *input / 10;
    //update current num
    *input %= 10;

    //calculate 5's
    denominations[4] = *input / 5;
    //update current num
    *input %= 5;

    //finaly 1's
    //no division should be necessary at this point
    denominations[5] = *input;

    //now for fractional part
    //calculate 0.25's
    denominations[6] = *input / 0.25;
    //update current num
    *input %= 25;

    //calculate 10's
    denominations[7] = *input / 0.10;
    //update current num
    *input %= 10;

    //calculate 5's
    denominations[8] = *input / 0.5;
    //upadte current num
    *input %= 5;

    //same thing as before with ones, no calculation necessary
    denominations[9] = *input * 100;



    return denominations;

}

//input: float pointer, used to reference the ammount of money given to the change machine
//output: output an arry(size 10) carrying the ammounts of denominations that the input can be broken up into
//Should use a greedy approach since we want largest to smallest denominations
//use an two ints instead of float for future.
int* calculateDenominations(int * left, int * right){

    static int denominations[10] = {0,0,0,0,0,0,0,0,0,0};

    while(*left != 0){


        if(*left >= 100){
            denominations[0]++;
            *left -= 100;
            continue;
        }

        if(*left >= 50){
            denominations[1]++;
            *left -= 50;
            continue;
        }

        if(*left >= 20){
            denominations[2]++;
            *left -= 20;
            continue;
        }

        if(*left >= 10){
            denominations[3]++;
            *left -= 10;
            continue;
        }

        if(*left >= 5){
            denominations[4]++;
            *left -= 5;
            continue;
        }

        if(*left >= 1){
            denominations[5]++;
            *left -= 1;
            continue;
        }
    }

    while(*right != 0){

        if(*right >= 25){
            denominations[6]++;
            *right -= 25;
            continue;
        }

        if(*right >= 10){
            denominations[7]++;
            *right -= 10;
            continue;
        }

        if(*right >= 5){
            denominations[8]++;
            *right -= 5;
            continue;
        }

        if(*right >= 1){
            denominations[9]++;
            *right -= 1;
            continue;
        }
    }

    return denominations;

}



#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include "changeMachine.h"

#define STDIN_FILENO 0

int kbhit(){
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}

void nonblock(int state){
    struct termios ttystate;
    tcgetattr(STDIN_FILENO, &ttystate);

    if(state == 1){
        ttystate.c_lflag &= (~ICANON);
        ttystate.c_cc[VMIN] = 1;
    }
    else if(state == 0){
        ttystate.c_lflag |= ICANON | ECHO;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

bool keyState(int key){
    int i = kbhit();
    if(i != 0){
        char c = fgetc(stdin);
        printf("\nkey state %d\n", c);
        if(c == key){
            return true;
        }else{
            return false;
        }
    }
}


int main(){

    int * left = malloc(sizeof(int));
    int * right = malloc(sizeof(int));
    int * left2 = malloc(sizeof(int));
    int * right2 = malloc(sizeof(int));

    bool exit = false;
    //printf("Division %d", (1234323 % 100) / 50);
    //printf("Division %d", 1234323 / 100);
    
    while(true){
        *left, *right = -1;
        printf("\ncharInput = %d\n", exit);
        
        bool inputCorrect = false;

        while(!inputCorrect){
        
        printf("\nHit ESC to quit");
        printf("\nPlease enter the dollar ammount you would like change for (Input should be in the form *.XX): ");
        //check if user has hit escape to exit
        // nonblock(1);
        // //wait for user to start typing
        // while(kbhit() == 0){
        //     //check if escape key has been hit
        //     bool keyStateResult = keyState(27);
        //     if(keyStateResult){
        //         printf("ESC KEY HIT! EXITING.");
        //         exit = true;
        //     }
        // }
        // nonblock(0);
        // if(exit){
        //     break;
        // }
        //the right side should only be a number in the 10's 
        scanf("%d.%2d",left, right);
        
        //check if input stream contains a char(used to quit the program)
        //check for malformed input
        if(*right >= 0 && *left >= 0){
            inputCorrect = true;
        }else{
            printf("\nERROR INPUT IS MALFORMED!\nInput must be positve and in the form *.XX\n\n");
        }
        
        //clear input buffer
        fflush(stdin);

        printf("%d %d\n", *left, *right);
        }

        if(exit){
            break;
        }
        
        *left2 = *left;
        *right2 = *right;


        //check how long each result takes to calculate
        clock_t before = clock();
        int * result1 = calculateDenominations(left, right);
        clock_t result1_time = clock() - before;

        //get new time
        before = clock();
        int * result2 = calculateDenominations2(left2, right2);
        clock_t result2_time = clock() - before;

        printDenominations(result1);
        printDenominations(result2);

        printf("Time taken for solution 1: %ld\nTime taken for solution 2: %ld\n", result1_time, result2_time);
    }
    //free malloced memory
    free(left);
    free(right);
    free(left2);
    free(right2);


    return 0;
}