#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UL "<ul>"
#define OL "<ol>"
#define endUL "</ul>"
#define endOL "</ol>"
#define LI "<li>"

void showElement(char* text, int type ,int* number){
    int boolik = 0;
    int ind = -1;
    if(type == 1){
        printf("* ");
    }
    else if (type == 2){
        printf("%d.",*number);
        (*number)++;
    }
    while(text[++ind] != '\0'){
        if(text[ind] == '>'){
            boolik = 1;
        }
        else if(text[ind] == '<' && boolik){
            break;
        }
        else if(boolik == 1){
            printf("%c",text[ind]);
        }
    }
    printf("\n");

}

void htmlList(){
    FILE* html = fopen("dane.html","r");
    if(!html){
        printf("error\n");
        return;
    }
    char* text = malloc(sizeof(char)*40);
    char* part = malloc(sizeof(char)*5);
    int started = 0; int type = 0; int number = 1;
    fscanf(html,"%s",text);
    while(!feof(html)){
        part = strncpy(part,text,4);
        if(!strcmp(text,UL)){
            started = 1;
            type = 1;
        }
        if(!strcmp(text,OL)){
            started = 1;
            type = 2;
        }
        if(!strcmp(part,LI) && started){
            showElement(text,type,&number);
        }
        if(!strcmp(text,endOL) || !strcmp(text,endUL)){
            started = 0;
            type = 0;
            number = 1;
        }
        // printf("%s\n",part);
        fscanf(html,"%s",text);
    }
}

void swap(int* a, int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void justyfing(){
    FILE* data = fopen("dane4","r");
    int max_char = 0;
    int tmp = 0; int space = 0; int first = 1;
    char curr = fgetc(data);
    while(!feof(data)){
        if(curr !=' ' && curr != '\n')
            tmp++;
        if(first){
            first = 0;
        }
        else if(curr == ' '){
            tmp++;
        }
        else if(curr == '\n'){
            if(tmp > max_char){
                swap(&tmp,&max_char);
                first = 1;
                space = 0;
                tmp = 0;
            }
        }
        curr = fgetc(data);
    }
    rewind(data);
    size_t buffsize = 70;
    char* row = malloc(sizeof(char)*70);
    tmp = getline(&row,&buffsize,data);
    while(!feof(data)){
        for(int i = 1; i <= tmp; ++i){
            if(i <= max_char - tmp)
                printf(" ");
            else{
                printf("%c",row[tmp-i]);
            }
        }
        tmp = getline(&row,&buffsize,data);
    }
    printf("max : %d\n",max_char);
}

int main(int argc, char** argv){
    if(argc != 2){
        printf("Wrong number of arguments\n");
    }
    else{
        int mode = atoi(argv[1]);
        if(mode == 1){
            justyfing();
        }
        else if(mode ==2){
            htmlList();
        }

    }
}