#include <stdio.h>
#include <stdlib.h>
#include "matrix_operations.h"


int main(int argc,char** argv){
    if(argc != 4){
        printf("Not enough argument\n");
        return 1;
    }
    else{
        multiplyMatrixes(argv[1], argv[2], argv[3]);
    }
}