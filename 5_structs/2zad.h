#include <stdlib.h>
#include <stdio.h>

typedef enum {FALSE, TRUE} boolean;

typedef struct {
	int hour;
	int minute;
	int duration;
} Term;

void Term_init(Term* term, int hour, int minute, int duration){
	(*term).hour = hour;
	(*term).minute = minute;
	(*term).duration = duration;
}

Term* Term_create(int hour, int minute, int duration){
	Term* result = (Term*) malloc(sizeof(Term));
	Term_init(result,hour,minute,duration);
	return result;
}

void Term_destroy(Term* term){
	free(term);
}

char* Term_toString(Term* term){
	char* result = (char*) malloc(sizeof(char)*50);
	sprintf(result,"%d:%d [%d]",term->hour,term->minute,term->duration);
	return result;
}
boolean Term_earlierThan( Term* term1, Term *term2){
	if(term1->hour < term2->hour)
		return TRUE;
	else if(term1->hour > term2->hour)
		return FALSE;
	else if( term1->minute < term2->minute)
		return TRUE;
	return FALSE;
}
boolean Term_equals(Term* term1, Term* term2){
	if(term1->hour == term2->hour && term1->minute == term2->minute && term1->duration == term2->duration)
	return TRUE;
	else
		return FALSE;
}

boolean Term_laterThan(Term* term1, Term* term2){
	if(term1->hour > term2->hour)
		return TRUE;
	if(term1->hour < term2->hour)
		return FALSE;
	if(term1->minute > term2->minute)
		return TRUE;
	return FALSE;
}

Term* Term_endTerm(Term* term1, Term* term2){
	if(Term_laterThan(term1,term2))
		return NULL;
	int duration = 60*(term2->hour-term1->hour) + (term2->minute - term1->minute);
	return Term_create(term1->hour, term1->minute,duration);
}

