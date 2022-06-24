#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int MAX_PIXELS = 255;

typedef struct {
    int **table;
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
    result->table = table;
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
        free(((*table)->table)[i]);
    }
    free(((*table)->table));
    free(*table);
}

rev_data** threads_data_init(int threads_number, Table *table){
    rev_data **result = (rev_data**)malloc(sizeof(rev_data*)*threads_number);
    for(int i=0; i<threads_number; i++){
        result[i] = (rev_data*)malloc(sizeof(rev_data));
    }
    int interval = MAX_PIXELS/threads_number;
    int beg = 0, end = -1;
    for(int i=0; i<threads_number; i++){
        beg = end + 1;
        end = beg + interval -1;
        if(i == threads_number-1)
            end = MAX_PIXELS;
        result[i]->min = beg;
        result[i]->max = end;
        result[i]->table = table;
    }
    return result;
}

void threads_data_delete(rev_data ***data, int threads_number){
    if(data == NULL){
        printf("Threads data already deleted\n");
        return;
    }
    for(int i=0; i<threads_number; i++){
        free((*data)[i]);
    }
    free(*data);
    data = NULL;
}

void* reverse_pixels(void *dat){
    rev_data *data = (rev_data*)dat;
    int height = data->table->height;
    int width = data->table->width;
    int **table = data->table->table;

    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            if(data->min <= table[i][j] && table[i][j] <= data->max){
                table[i][j] = 2*MAX_PIXELS - table[i][j];
            }
        }
    }
}

int main(int argc, char** argv){
    if(argc != 5){
        printf("Not enough arguments!\nYou typed %d instead of 4\n",argc-1);
        return 0;
    }
    int threads_number = atoi(argv[1]);
    FILE *input;
    FILE *output;

   if ((input = fopen(argv[2],"r")) == NULL){
       fprintf(stderr,"Error! opening file");
       exit(EXIT_FAILURE);
   }
   if ((output = fopen(argv[3],"w")) == NULL){
       fprintf(stderr,"Error! opening file");
       fclose(input);
       exit(EXIT_FAILURE);
   }
   char *buffer = (char*)malloc(sizeof(char)*1000);
   fscanf(input, "%[^\n]", buffer);
   fprintf(output, "%s\n",buffer);
   fscanf(input, "\n%[^\n]", buffer);
   fprintf(output, "%s\n",buffer);
   int width = 0,height = 0;
   fscanf(input, " %d %d \n %d ",&width,&height,&MAX_PIXELS);
   fprintf(output, "%d %d\n%d",width,height,MAX_PIXELS);
   Table* table = Table_init(height,width);
   for(int i=0; i<height; i++){
       for(int j=0; j<width; j++){
           fscanf(input," %d ",&(table->table)[i][j]);
       }
   }

   clock_t begin = clock();
   rev_data **threads_data = threads_data_init(threads_number,table);
   pthread_t threads[threads_number];

   for (short i = 0; i < threads_number; i++)
                {
                    short t = pthread_create(&threads[i], NULL, reverse_pixels, (void*)(threads_data[i]));

                    if (t != 0)
                    {
                        fprintf(stderr, "Error while creating thread\n");
                        exit(EXIT_FAILURE);
                    }
                }

   for(short i = 0; i < threads_number; i++)
   {
       int t = pthread_join(threads[i], NULL);
       if (t != 0)
       {
           fprintf(stderr, "Error while joing threads\n");
           exit(EXIT_FAILURE);
       }
   }

   clock_t end = clock();
   printf("Time while working on threads: %0.3f\n", (double)(end - begin) / CLOCKS_PER_SEC);

   for(int i=0; i<height; i++){
       for(int j=0; j<width; j++){
           if(j%15 == 0){
                fprintf(output,"\n");
           }
           fprintf(output,"%d ",(table->table)[i][j] - MAX_PIXELS);
       }
   }

   threads_data_delete(&threads_data,threads_number);
   Table_delete(&table);
   fclose(input); fclose(output);
   free(buffer);

}
