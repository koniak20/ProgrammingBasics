#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int MAX_PIXELS = 255;

typedef struct {
    int ***table;
    int height;
    int width;
} Table;

typedef struct{
    Table* table;
    int min;
    int max;
} rev_data;

Table* Table_init(int height, int width){
    Table* result = (Table*)malloc(sizeof(Table));
    int **table = (int**)malloc(sizeof(int*)*height);
    for(int i=0; i<height; i++){
        table[i] = (int*)malloc(sizeof(int)*width);
    }
    result->table = &table;
    result->height = height;
    result->width = width;
    
    return result;
}

void Table_delete(Table **table){
    if(table == NULL){
        printf("Table already deleted\n");
        return;
    }
    int height = (*table)->height;
    for(int i=0; i<height; i++){
        free((*((*table)->table))[i]);
    }
    free(((*table)->table));
    free(*table);
}

rev_data** threads_data_init(int number_threads, Table *table){
    rev_data **result = (rev_data**)malloc(sizeof(rev_data*)*number_threads);
    for(int i=0; i<number_threads; i++){
        result[i] = (rev_data*)malloc(sizeof(rev_data));
    }
    int interval = MAX_PIXELS/number_threads;
    int beg = 0, end = 0;
    for(int i=0; i<number_threads; i++){
        end = beg + interval -1;
        if(i == number_threads-1)
            end = 255;
        result[i]->min = beg;
        result[i]->max = end;
        result[i]->table = table;
    }
}

void threads_data_delete(rev_data *** data, int number_threads){
    if(data == NULL){
        printf("Threads data already deleted\n");
        return;
    }
    for(int i=0; i<number_threads; i++){
        free((*data)[i]);
    }
    free(*data);
    data = NULL;
}

int main(int argc, char** argv){
    if(argc != 5){
        printf("Not enough arguments!\nYou typed %d instead of 4\n",argc-1);
        return 0;
    }
    int number_threads = atoi(argv[1]);
    FILE *input;
    FILE *output;

   if ((input = fopen(argv[2],"r")) == NULL){
       printf("Error! opening file");
       return 0;
   }
   if ((output = fopen(argv[3],"w")) == NULL){
       printf("Error! opening file");
       fclose(input);
       return 0;
   }
   char *buffer = (char*)malloc(sizeof(char)*1000);
   fscanf(input, "%[^\n]", buffer);
   fscanf(input, "%[^\n]", buffer);
   int width,height;
   fscanf(input, "%d %d %d",width,height,MAX_PIXELS);
   printf("%d %d %d\n",width,height,MAX_PIXELS);

}
