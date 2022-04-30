#include <stdlib.h>
#include <stdio.h>

#define MIN 0
#define MAX 1

int randint(int lower, int upper){
    return (rand() % (upper - lower + 1)) + lower;
}

void CreateMatrix(FILE* file,int x, int y){
    for(int i=0; i<x; i++){
        for(int j=0; j<y; j++){
            fprintf(file,"%d",randint(MIN,MAX));
            if(j < y-1)
                fputc(' ',file);
        }
        fputc('\n',file);
    }
}

void Generate(int min, int max){
    FILE* A = fopen("A.txt","w");
    FILE* B = fopen("B.txt","w");
    int x = randint(min,max), y = randint(min,max);
    CreateMatrix(A,x,y);
    int z = randint(min,max);
    CreateMatrix(B,y,z);
}

void setSizeMatrix(FILE* file, int* x, int* y){
    int boolik = 1;
    char c;
    while(!feof(file)){
        c = fgetc(file);
        // printf("%c",c);
        if(c == '\n' && boolik){
            (*x)++;
            *y = *x;
            boolik = 0;
        }
        else if(c == ' ' || c == 10){
            (*x)++;
        }
    }
    *x /= *y;
}
int getElementMatrix(FILE* file, int x ,int y, int columns){
    rewind(file);
    char* random = (char*) malloc(sizeof(char)*10);
    for(int i=1 ; i<=x; ++i){
        for(int j=1; j<=columns && !(i == x && j == y); ++j){
            fscanf(file,"%s",random);
        }
    }
    fscanf(file," %s",random);
    int result = atoi(random);
    free(random);
    // printf("x %d y %d %d\n",x,y,result);
    return result;
}
void multiplyMatrixes(char* A, char* B, char* C){
    FILE* A_file = fopen(A,"r");
    FILE* B_file = fopen(B,"r");
    FILE* C_file = fopen(C,"w");
    int ax = 0,ay; setSizeMatrix(A_file,&ax,&ay);
    int bx = 0,by; setSizeMatrix(B_file,&bx,&by);
    // printf("%d %d\n%d %d\n", ax,ay,bx,by);
    int cx = ax , cy = by;
    for(int i=1; i<=cx; i++){
        for(int j=1; j<=cy; j++){
            int result = 0;
            for(int k=1; k<=ay; k++){
                result += getElementMatrix(A_file,i,k,ay)*getElementMatrix(B_file,k,j,by);
            }
            fprintf(C_file,"%d",result);
            if(j != cy)
            fputc(' ',C_file);
        }
        fputc('\n',C_file);
    }

    fclose(A_file); fclose(B_file); fclose(C_file);
}