#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { MON, TUE, WED, THU, FRI, SAT, SUN}Day;
typedef enum {DAY_EARLIER, DAY_LATER,TIME_EARLIER, TIME_LATER}Action;

Action StringToDay(char* text){
	Action result;
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
Action* parse(int sizeTab, char** tab){
	Action* result = (Action*)malloc(sizeof(Action)*10);
	int ind = 0;
	Action tmp = 0;
	for(int i=2; i<sizeTab; ++i){
		if(tab[i][0] == 't')
			tmp += 2;
		else if(tab[i][0] != 'd'){
			printf("error\n");
			return NULL;
		}	
		if(tab[i][1] == '+')
				tmp += 1;
		
		result[ind++] = tmp;
		tmp = 0;
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
			printf("error\n");
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
int main(int argc, char** argv){
	Action* actions = parse(argc,argv);
	if(actions == NULL)
		return 0;
	Action day = StringToDay(argv[1]);
	for(int i = 0; i < argc - 2; ++i){
		switch(actions[i]){
			case DAY_EARLIER:
					day = Day_prevDay(day);
					printf("Day back\n");
					break;
			case DAY_LATER:
					printf("Day forward\n");
					day = Day_nextDay(day);
					break;
			case TIME_EARLIER:
					printf("Time back\n");
					break;
			case TIME_LATER:
					printf("Time forward\n");
					break;
			default:
					printf("ERROR\n");
					return 0;
		}
	}
	printf("Result of moving is: \"%s\"\n",Day_toString(day));
}
