#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { MON, TUE, WED, THU, FRI, SAT, SUN} Day;
typedef enum {DAY_EARLIER, DAY_LATER,TIME_EARLIER, TIME_LATER} Action;

Day StringToDay(char* text){
	Day result;
	if(!strcmp(text,"Mon")){
		result = MON;
	}
	if(!strcmp(text,"Tue")){
		result = TUE;
	}
	if(!strcmp(text,"Wed")){
		result = WED;
	}
	if(!strcmp(text,"Thu")){
		result = THU;
	}
	if(!strcmp(text,"Fri")){
		result = FRI;
	}
	if(!strcmp(text,"Sat")){
		result = SAT;
	}
	if(!strcmp(text,"Sun")){
		result = SUN;
	}
	return result;
}

char* Day_toString(Day day){
	char* result = (char*) malloc(sizeof(char)*100);
	switch(day)
	{
		case MON:
			sprintf(result,"Monday");
			break;
		case TUE:
			sprintf(result,"Tuesday");
			break;
		case WED:
			sprintf(result,"Wednesday");
			break;
		case THU:
			sprintf(result,"Thursday");
			break;
		case FRI:
			sprintf(result,"Friday");
			break;
		case SAT:
			sprintf(result,"Saturday");
			break;
		case SUN:
			sprintf(result,"Sunday");
			break;
		default:
			printf("error converting\n");
			return NULL;
	}
	return result;
}
Day Day_nextDay(Day day){
	Day result = (day + 1)%7;
	return result;	
}
Day Day_prevDay(Day day){
	Day result = (day + 6)%7;
	return result;	
}


typedef enum {FALSE, TRUE} boolean;

typedef struct {
	int hour;
	int minute;
	int duration;
	Day day;
} Term;

typedef struct {
	Term term;
	char* lesson;
} Lesson;
 
typedef struct {
	int min_h;
	int min_m;
	int max_h;
	int max_m;
} Limit;

boolean isTermOkay(Term* term){
	Limit limits[7] ={ {8,0,20,0},{8,0,20,0},{8,0,20,0},{8,0,20,0},{8,0,17,0},{0,0,0,0},{0,0,0,0}};
	int day = term->day;
	boolean start = FALSE, end = FALSE;
	if(limits[day].min_h < term->hour || (limits[day].min_h == term->hour && limits[day].min_m <= term->minute))
		start = TRUE;
	int end_h = term->hour + (term->minute+term->duration)/60;
	int end_m = (term->minute + term->duration)%60;
	if(end_h < limits[day].max_h || (limits[day].max_h == end_h &&  end_m <= limits[day].max_m))
		end = TRUE;
	if(start && end)
		return TRUE;
	return FALSE;
}
boolean Lesson_postpone(Lesson* lesson,int hour, int minute, Day day){
	Term tmp = {hour,minute,lesson->term.duration,day};
	Lesson result = {tmp,lesson->lesson};
	if(isTermOkay(&(result.term))){
		*lesson = result;
		return TRUE;
	}
	else{
		printf("Lesson \"%s\" can't be moved to date \"%s, %d:%02d\"\n",result.lesson,Day_toString(result.term.day),result.term.hour,result.term.minute);
		return FALSE;
	}
}
void Lesson_laterDay(Lesson* lesson){
	if(Lesson_postpone(lesson,lesson->term.hour,lesson->term.minute,Day_nextDay(lesson->term.day)))
		printf("Day ahead\n");
	
}
void Lesson_earlierDay(Lesson* lesson){
	if(Lesson_postpone(lesson,lesson->term.hour,lesson->term.minute,Day_prevDay(lesson->term.day)))
		printf("Day back\n");
}
void Lesson_earlierTime(Lesson* lesson){
	int minute = lesson->term.minute;
	int hour = lesson->term.hour - lesson->term.duration/60;
	int duration = lesson->term.duration%60;
	if(duration > minute){
		hour--;
		minute = 60 - duration;
	}
	else
		minute -= duration;
	if(Lesson_postpone(lesson,hour,minute,lesson->term.day))
		printf("Time back\n");
}
void Lesson_laterTime(Lesson* lesson){
	int minute = lesson->term.minute;
	int hour = lesson->term.hour + lesson->term.duration/60;
	int duration = lesson->term.duration%60;
	if(duration + minute > 59){
		hour++;
		minute = (duration+minute)%60;
	}
	else
		minute = duration + minute;
	if(Lesson_postpone(lesson,hour,minute,lesson->term.day))
		printf("Time ahead\n");
}

char* Lesson_toString(Lesson* lesson){
	char* result = (char*) malloc(sizeof(char)*200);
	sprintf(result,"%s, %s %d:%02d [%d]",lesson->lesson,Day_toString(lesson->term.day),lesson->term.hour,lesson->term.minute,lesson->term.duration);
	return result;
}
void Term_init(Term* term, int hour, int minute, int duration, Day day){
	(*term).hour = hour;
	(*term).minute = minute;
	(*term).duration = duration;
	term->day = day;
}

Term* Term_create(int hour, int minute, int duration, Day day){
	Term* result = (Term*) malloc(sizeof(Term));
	Term_init(result,hour,minute,duration,day);
	return result;
}

void Term_destroy(Term* term){
	free(term);
}

char* Term_toString(Term* term){
	char* result = (char*) malloc(sizeof(char)*50);
	sprintf(result,"%s %d:%d [%d]",Day_toString(term->day),term->hour,term->minute,term->duration);
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
	return Term_create(term1->hour, term1->minute,duration, term1->day);
}

Action* parse(int sizeTab, char** tab){
	Action* result = (Action*)malloc(sizeof(Action)*10);
	int ind = 0;
	Action curr = DAY_EARLIER;
	for(int i=1; i<sizeTab; ++i){
		if(!strcmp(tab[i],"t-"))
			curr = TIME_EARLIER;
        else if(!strcmp(tab[i],"t+"))
			curr = TIME_LATER;
        else if(!strcmp(tab[i],"d-"))
			curr = DAY_EARLIER;
        else if(!strcmp(tab[i],"d+"))
			curr = DAY_LATER;
		else {
			printf("error parsing\n");
			return NULL;
		}	
		result[ind++] = curr;
		curr = DAY_EARLIER;
	}
	return result;
}

void zad3(Action* actions,Lesson* lesson,int quantity){
	if(actions == NULL)
		return ;
	for(int i = 0; i < quantity - 2; ++i){
		switch(actions[i]){
			case DAY_EARLIER:
					Lesson_earlierDay(lesson);
					break;
			case DAY_LATER:
					Lesson_laterDay(lesson);
					break;
			case TIME_EARLIER:
					Lesson_earlierTime(lesson);
					break;
			case TIME_LATER:
					Lesson_laterTime(lesson);
					break;
			default:
					printf("ERROR\n");
					return ;
		}
	}
}
