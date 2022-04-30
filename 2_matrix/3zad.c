#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void printArray(int array[], int rows, int columns){
    for(int i=0; i<rows; i++){
        printf("[");
        for(int j=0; j<columns; j++){
            printf("%d",*(array+i*rows+j));
            if(j < columns -1)
                printf(","); 
        }   
        printf("]\n");
    }
}
void printMatrix(int array[], int size){
    printArray(array,size,size);
}

void isLowerTriangular(int array[], int size){
    int result = 1;
    for(int i=0; i<size && result; ++i){
        for(int j=i+1; j<size && result; ++j){
            result = array[i*size+j] != 0 ? 0 : 1;
        }
    }
    if(result)
        printf("The matrix is lower triangular\n");
    else
        printf("The matrix is not lower triangular\n");
}
void firstPart(){
    srand(time(0));
    int n;
    scanf("%d",&n);
    int *matrix =(int*)calloc(n*n,sizeof(int));
    for (int i=0; i < n*n; ++i){
        scanf("%d",(matrix+i));
    }
    printMatrix(matrix,n);
    isLowerTriangular(matrix,n);
    free(matrix);
}
void secondPart(){
    int n,m;
    scanf("%d %d",&n,&m);
    // printf("%d %d", sizeof(int),sizeof(int*));
    int** array = (int**)calloc(n,sizeof(int*));
    for(int i=0; i<n; ++i)
        *(array+i) = (int*)calloc(m,sizeof(int));
    int lower = 0 , upper = 5;
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            array[i][j]= (rand() %(upper - lower + 1)) + lower;
        }
    }
    for(int i=0; i<n; i++){
        printf("[");
        for(int j=0; j<m; j++){
            printf("%d", *(*(array + i)+j));
            if(j < m -1)
                printf(","); 
        }   
        printf("]\n");
    }
    for(int i=0; i<n; i++){
        free(*(array+i));
    }
    free(array);
}
    // arr[i][j] <=> *(*(arr+i)+j)  arr[i] <=> *(arr + i)
int main(){
    system("clear");
    int choice = 0;
    printf("Choose which part you want to see: ");
    scanf("%d",&choice);
    if(choice == 1)
        firstPart(); 
    else if(choice == 2)
        secondPart(); 
}