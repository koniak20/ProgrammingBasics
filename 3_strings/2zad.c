#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* getLine(){
    char *line;
    size_t bufsize = 32;
    line = (char *)malloc(bufsize * sizeof(char));
    size_t characters = getline(&line,&bufsize,stdin);
    if(characters != -1 && line[0] == '\n')
        characters = -1;
    return characters == -1 ? NULL : line;
}

char** getData(){
    char** result = (char **)malloc(4*sizeof(char*));
    char* begin;
    int i = 0;
    for(; begin = getLine(); ++i){
        if( i > 2){
            char** newresult = (char**) realloc(result,(i+2)*sizeof(char*));
            if( newresult == NULL){
                printf("Error while allocating more space\n");
                break;
            }
            result = newresult;
        }
        result[i] = begin;
        result[i+1] = NULL;
    }
    return result;
}

void swap(char* a, char* b){
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

char* reverseString(char* begin,int length){
    for(int j=0, i=length; j<i; ++j, --i){
        swap(begin+j,begin+i);
    }
    return begin;
}

char* integerToString(int number){
    char *result = ( char *)calloc(10,sizeof(char));
    int index = -1;
    while(number > 0){
        result[++index] = '0' + number%10;
        number /= 10;
    }
    result[++index] = '\0';
    return reverseString(result,index-1);
}

char* getHexAscii(char character){
    char* result = (char*) malloc(3*sizeof(char));
    static char hex[] = "0123456789ABCDEF";
    unsigned ascii = character;
    result[0] = hex[ascii / 16];
    result[1] = hex[ascii % 16];
    result[2] = '\0';
    return result;
}

int specialChar(char a){
    if(a == ')' || a == '(' || a == '%')
        return 1;
    else
        return 0;
}

char* compress(char** text){
    char* result = (char*) malloc(1000);
    int index = 0, quantity = 0;
    for(int line = 0; text[line] != NULL; ++line){
        for(int character = 0; text[line][character] != '\n'; ++character){
            if(text[line][character] != text[line][character+1]){
                if(++quantity > 4 || specialChar(text[line][character])){
                    if(specialChar(text[line][character]) ){
                        char* begin = (char*) malloc(3);
                        begin = getHexAscii(text[line][character]);
                        result[index++] = '%';
                        while( *begin != '\0'){
                            result[index++] = *begin;
                            begin++;
                        }
                    }
                    else{
                        result[index++] = text[line][character];
                    }
                    result[index++] = '(';
                    for(char* digit = integerToString(quantity); *digit != '\0'; digit++){
                        result[index++] = *digit;
                    }
                    result[index++] = ')';
                }
                else{
                    for(int i = 0; i < quantity; ++i){
                        result[index++] = text[line][character];
                    }
                }
                quantity = 0;
            }
            else
                quantity++;
        }
        result[index++] = '\n';
    }
    int i = 0;
    while(text[i] != NULL || i < 3){
        free(text[i++]);
    }
    free(text);
    result[index] = '\0';
    return result;
}

int getNumFromString(char* start, int* chara){
    char integer[5];
    int i = 0;
    char end;
    if(start[(*chara)] == '%')
        end = '(';
    else
        end = ')';
    while(start[*chara] != end){
        integer[i++] = start[++(*chara)];
    }
    if( end == '(')
        --*chara;
    return atoi(integer);
}

char* decompress(char** text){
    char* result = (char*) malloc(1000);
    int index = 0;
    char curr;
    for(int line = 0; text[line] != NULL; ++line){
        for(int character = 0; text[line][character] != '\n'; ++character){
            if(text[line][character] == '('){
                int i = getNumFromString(text[line],&character);
                for(int j = 1; j<i; ++j){
                    result[index++] = curr;
                }
            }
            else if(text[line][character] == '%'){
                int i = getNumFromString(text[line],&character);
                if(i == 28){
                    curr = '(';
                }
                else if ( i == 25){
                    curr = '%';
                }
                else{
                    curr = ')';
                }
                result[index++] = curr;
            }
            else{
                curr = text[line][character];
                result[index++] = curr;

            }
        }
        result[index++] = '\n';
    }

    return result;

}

int main(int argc, char** argv){
    // printf("Nazwa %s \n Ilosc %d ",argv[0],argc);
    // printf("%s",argv[1]);
    char** data = getData();
    if(argc == 1 || strcmp(argv[1] , "--compress") == 0){
        char* text = compress(data);
        printf("%s\n" , text);
    }
    else{
        char* text = decompress(data);
        printf("%s" , text);
    }

}