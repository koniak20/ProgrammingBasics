#include <stdio.h>
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

int main(void)
{
    int *stack = NULL;

    Stack__destroy(stack); // Wypisuje: "Stos nie istnieje"
    stack = Stack__create(3); // Utworzenie stosu o rozmiarze 3
    Stack__push(stack, 3); // Dodanie liczby 3 na stos
    Stack__push(stack, 5);
    Stack__push(stack, 2);
    Stack__push(stack, 4); // Przekraczamy rozmiar stosu — funkcja nie powinna na to pozwolić
    Stack__print(stack); // Funkcja powinna wypisać:
                         // 2
                         // 5
                         // 3
    printf("%d\n", Stack__pop(stack)); // Wypisuje 2
    Stack__print(stack); // Funkcja powinna wypisać:
                         // 5
                         // 3
    printf("%d\n", Stack__pop(stack)); // Wypisuje 5
    printf("%d\n", Stack__pop(stack)); // Wypisuje 3

    int liczba = Stack__pop(stack); // Próbujemy zdjąć wartość z pustego stosu  — funkcja nie powinna na to pozwolić — powinna zwrócić wartość specjalną, na przykład INT_MIN
    Stack__destroy(stack); // Likwidacja stosu
    Stack__destroy(stack); // Wypisuje: "Stos nie istnieje"
    return 0;
}
