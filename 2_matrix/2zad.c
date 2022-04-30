#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 6

void print_array(int tab[][SIZE]){
    for(int i=0; i<SIZE; i++){
        printf("[");
        for(int j=0; j<SIZE; j++){
            printf("%d",tab[i][j]);
            if(j < SIZE -1)
                printf(","); 
        }   
        printf("]\n");
    }
}
void random_arrays(int tab[][SIZE]){
    int lower = 0, upper = 1;
        for(int i=0; i<SIZE; i++){
            for(int j=0; j<SIZE; j++){
                tab[i][j]= lower + (rand()%(upper-lower+1)); 
            }  
        }
}

void print_diagonal(int tab[][SIZE]){
    int result = 0;
    for(int i=0; i<SIZE; i++)
        result += tab[i][i];
    printf("Sum on the diagonal is: %d\n",result);
}

void print_columns(int tab[][SIZE]){
    int whole = 0, column = 0;
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            column += tab[j][i];
        }
        printf("Sum of %d column is %d\n",i+1,column);
        whole += column;
        column = 0;
    }
    printf("Whole sum is %d\n", whole);
}

void multipling_matrixes(int tab1[][SIZE], int tab2[][SIZE]){
    printf("First array is:\n");
    print_array(tab1);
    printf("Second array:\n");
    print_array(tab2);
    int tab3[SIZE][SIZE] = {0};
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            for(int k=0; k<SIZE; k++){
                tab3[i][j] += tab1[i][k] * tab2[k][j];
            }
        }
    }
    printf("New Array:\n");
    print_array(tab3);
}

int main(){
    system("clear");
    srand(time(0));
    int t1[SIZE][SIZE], t2[SIZE][SIZE];
    random_arrays(t1); 
    random_arrays(t2);
    // print_array(t1); 
    // print_array(t2);
    
    // print_diagonal(t1);
    // print_columns(t1);

    multipling_matrixes(t1,t2);
}