#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "1zad.h"


int main(int argc, char** argv){
	printf("%d\n",argc);
	zad1(parse(argc,argv),StringToDay(argv[1]),argc);
}
