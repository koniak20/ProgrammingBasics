#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>


int* Stack__create(int size){
	int* stack = (int*) malloc((2 + size)*sizeof(int));
	if(stack == NULL){
		fprintf(stderr, "Can't create stack in that size");
		exit(EXIT_FAILURE);
	}
	stack[0] = size;
	stack[1] = 0;
	return stack;
}
void Stack__destroy(int* stack){ 
	if(stack == NULL || stack[0] == 0)
		printf("Stack doesn't exit\n");
	else{
		stack = realloc(stack, sizeof(int));
		stack[0] = 0;
	}
}
void Stack__push(int* stack, int number){
	if(stack[1] < stack[0]){
		stack[1]++;
		stack[stack[1] + 2] = number;	
	}
	else{
		printf("Stack overflow\nCan't add new number\n");
	}
}
int Stack__pop(int* stack){
	if(stack[1] != 0){
		stack[1]--;
		return stack[stack[1]+3];
	}
	printf("Can't pop from stack, stack doesn't have any element\n");
	return INT_MIN;
}
void Stack__print(int* stack){
	for(int i = stack[1]; i >= 1; --i){
		printf("%d\n",stack[i+2]);
	}
}
char* getLine(){
    char *line;
    size_t bufsize = 32;
    line = (char *)malloc(bufsize * sizeof(char));
    size_t characters = getline(&line,&bufsize,stdin);
    if(characters != -1 && line[0] == '\n')
        characters = -1;
    return characters == -1 ? NULL : line;
 }
typedef enum {FALSE,TRUE} bool;

int main(){
	int* stack = Stack__create(1000);
	bool used = FALSE;
	char c;
	char* result = (char*) malloc(sizeof(char)*1000);
	while(1){
		c = getc(stdin);
		if( c == '.')
			break;
		if( c == '\0')
			break;
		else if( c != '\n'){
			if( c == '/'){
				Stack__push(stack,c);
				if(used == TRUE){
					used = FALSE;
					int i = 0;
					while(!used){
						int s = (char)Stack__pop(stack);
						if(s == INT_MIN)
							return 0;
						c = (char) s;
						if( c == '\\'){
							used = TRUE;
						}	
						result[i++] = c;
					}	
					result[i] = (char) Stack__pop(stack);
					printf("Znaleziono zduplikowane'\\/'\n");
					while(i >=0){
						printf("%c",result[i--]);
					}
					printf("\n");
					return 0;
				}
				used = TRUE;
			}
			else{
				used = FALSE;
				Stack__push(stack,c);
			}
		}

	}
	printf("Nie znaleziono zduplikowanego '\\/'\n");
}
