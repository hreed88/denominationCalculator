#include "gui.h"

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
                //check if gui is selected
                if((std::string)argv[1] != "-g"){
                result = run2(argv[1]);
                }else{
                result = startGUIApplication();
                }

                break;
            //if the user gives more the one argument nothing is ran and program exits
            default:
                perror("ERROR provide either one(Dollar ammount in the form *.XX) \nor no arguments\n");
                break;
            }
    //return code
    return result;
}