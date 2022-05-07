#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "3zad.h"

int main(int argc, char** argv){
	Term* test = Term_create(12,50,90,WED); 
	Lesson lesson = {*test,"Podstawy"};
	printf("Before moving\n");
	puts(Lesson_toString(&lesson));
	zad3(parse(argc,argv),&lesson,argc);
	printf("After moving\n");
	puts(Lesson_toString(&lesson));
}

