#include "changeMachine.h"

int main(int argc, char* argv[]){

        int result = 0;

        //switch statement is used to check wether user gave input on the cmd line or not
        switch (argc){
            //no argument
            case 1:
                result = run1();
                break;
            //have argument
            case 2:
                //check if noguibranch only terminal
                result = run2(argv[1]);


                break;
            //if the user gives more the one argument nothing is ran and program exits
            default:
                fprintf(stderr,"ERROR provide either one(Dollar ammount in the form *.XX) \nor no arguments\n");
                break;
            }
    //return code
    return result;
}