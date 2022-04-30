#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

int randint(int lower, int upper){
    return (rand() % (upper - lower + 1)) + lower;
}

void generate(char* type, char* name_file, int N){
    FILE *location_file;
    location_file = fopen(name_file,"wb");
    if(!location_file){
        printf("Unable to open file!");
        exit(0);
    }
    if(!strcmp(type,"char")){
        char result;
        for(int i=0; i<N; i++){
            result = randint(0,CHAR_MAX-1);
            fwrite(&result,sizeof(char),1,location_file);
        }
    }
    else{
        int result;
        for(int i=0; i<N; i++){
            result = randint(0,INT_MAX/10000);
            fwrite(&result,sizeof(int),1,location_file);
        }
    }
    // int result;
    // rewind(location_file);
    // // printf("%d ",fread(&result,sizeof(int),1,location_file));
    // while(fread(&result,sizeof(int),1,location_file) == 1){
    //     printf("git\n");
    // }
    fclose(location_file);
}

void sort(char* type, char* name_file, int N){
    FILE* location_file;
    location_file = fopen(name_file,"r+b");
    if(!strcmp(type,"char")){
        char min,cur;
        for(int i=0 ; i<N; ++i){
            fseek(location_file,sizeof(char)*(i),SEEK_SET);
            fread(&cur,sizeof(char),1,location_file);
            min = cur;
            for(int j=i+1; j<N; ++j){
                fseek(location_file,sizeof(char)*j,SEEK_SET);
                fread(&cur,sizeof(char),1,location_file);
                if(cur < min){
                    fseek(location_file,sizeof(char)*i,SEEK_SET);
                    fwrite(&cur,sizeof(char),1,location_file);
                    fseek(location_file,sizeof(char)*j,SEEK_SET);
                    fwrite(&min,sizeof(char),1,location_file);
                    min = cur;
                }
            }
        }
    }
    else{
        int min,cur;
        for(int i=0 ; i<N; ++i){
            fseek(location_file,sizeof(int)*(i),SEEK_SET);
            fread(&cur,sizeof(int),1,location_file);
            min = cur;
            for(int j=i+1; j<N; ++j){
                fseek(location_file,sizeof(int)*j,SEEK_SET);
                fread(&cur,sizeof(int),1,location_file);
                if(cur < min){
                    fseek(location_file,sizeof(int)*i,SEEK_SET);
                    fwrite(&cur,sizeof(int),1,location_file);
                    fseek(location_file,sizeof(int)*j,SEEK_SET);
                    fwrite(&min,sizeof(int),1,location_file);
                    min = cur;
                }
            }
        }
    }
    printf("\n      Sorted!\n");
    fclose(location_file);

}

void list(char* type, char* name_file, int N){
    FILE* location_file;
    location_file = fopen(name_file,"rb");
    if(!location_file){
        printf("Unable to open file!");
        exit(0);
    }
    if(!strcmp(type,"char")){
        char val;
        for(int i = 0; i<N; ++i){
            fread(&val,sizeof(char),1,location_file);
            printf("%d is %d (char -> %c)\n",i+1,val,val);
        }
    }
    else{
        int val;    
        for(int i = 0; i<N; ++i){
            fread(&val,sizeof(int),1,location_file);
            printf("%d is %d\n",i+1,val);
        }
    }
    fclose(location_file);
}

void (*func)(char* ,char*, int);

int main(int argc, char** argv){  //name of file  N  char/int
    srand(time(0));
    if(argc != 4){
        printf("Not enough arguments to start working\n");
    }
    else{
        int N = atoi(argv[2]);
        char* name_file = (char*) malloc(sizeof(char)*100);
        char* type = (char*) malloc(sizeof(char)*4);
        strcpy(name_file,argv[1]); strcpy(type,argv[3]);
        printf(" What do you want to do?\n(g) generate\n(s) sort\n(l) list\n>");
        char choice;
        while(scanf(" %c",&choice)){
            if(choice == 'g'){
                func = generate;
            }
            else if(choice == 'l'){
                func = list;
            }
            else{
                func = sort;
            }
            func(type,name_file,N);
        }
    }
}