#include <stdio.h>

int main(int argc, char* argv[]){
    if(argc ==  1){
        //No Command-Line Arguements passed
        return -1;
    }
    if(argc >= 2){
        //At least 1 Command-Line Arguement is passed
        printf("%s", argv[1]); 
    }
}