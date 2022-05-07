#include <stdio.h>

typedef struct Limits{
	int min_minute;
	int max_hour;
} Limit ;

int main(){
	Limit MON_limit;
	printf("%d %d\n",MON_limit.min_minute,MON_limit.max_hour);	
}
