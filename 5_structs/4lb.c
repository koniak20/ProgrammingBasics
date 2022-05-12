#include <stdlib.h>
#include <stdio.h>

#include "3zad.h"

void printTerm(Term* term, char* lesson){
	printf("%d:%02d-%d:%02d %s\n",term->hour,term->minute,(term->hour + (term->minute + term->duration)/60),(term->minute + term->duration)%60,lesson);
}

void Timetable_show(Lesson* table, Term* term){
	int hour = term->hour;
	int min = term->minute;
	Day day = term->day;
	boolean first = FALSE;
	boolean second = FALSE;
	Term* end = Term_create(term->hour + (term->minute + term->duration)/60,(term->minute+term->duration)%60,0,term->day);
	if(Term_laterThan(&table[0].term,term) && Term_laterThan(end,&table[0].term) && table[1].term.day == term->day)
		first = TRUE;
	if(Term_laterThan(&table[1].term,term) && Term_laterThan(end,&table[1].term) && table[1].term.day == term->day)
		second = TRUE;
	if(Term_earlierThan(&table->term, &table[1].term)){
		if(first)
			printTerm(&table[0].term, table[0].lesson);
		if(second)
			printTerm(&table[1].term, table[1].lesson);	
	}	
	else{
		if(second)
			printTerm(&table[1].term, table[1].lesson);	
		if(first)
			printTerm(&table[0].term, table[0].lesson);
	}
}
int main(int argc, char** argv){
	Lesson* Lessons = (Lesson*) malloc(sizeof(Lesson)*10);
	Term* t = Term_create(9,30,90,WED); 
	Lesson lesson = {*t,"Podstawy Programowania"};
	t = Term_create(11,0,90,MON); 
	Lessons[0] = lesson;
	Lesson lesson1 = {*t,"Angielski"};
	Lessons[1] = lesson1;
	t = Term_create(9,29,80,WED);
	Timetable_show(Lessons,t);
}
