#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix_operations.h"



int main(int argc, char** argv){
    srand(time(0));
    if(argc != 3){
        printf("Not enough arguments.");
    }
    else{
        Generate(atoi(argv[1]),atoi(argv[2]));
    }
}