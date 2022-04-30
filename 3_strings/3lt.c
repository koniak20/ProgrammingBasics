#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define NEWLINE '\n'
#define IN_WORD 1

#define IN_LINE_COMMENT 1
#define IN_BLOCK_COMMENT 2

#define MAX_LINE 128

int read_line()
{
    char line[MAX_LINE];
    int n;

    fgets(line, MAX_LINE, stdin); // to get the whole line
    sscanf(line, "%d", &n);
    return n;
}
char* getLine(){
    char *line;
    size_t bufsize = 32;
    line = (char *)malloc(bufsize * sizeof(char));
    size_t characters = getline(&line,&bufsize,stdin);
    // if(characters != -1 && line[0] == NEWLINE)
    //     characters = -1;
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

// count number of lines (nl), number of words (nw) and number of characters
// (nc) in the text read from stdin
void wc(int *nl, int *nw, int *nc)
{   
    char** data = getData();
    int line;
    *nw = 0;
    *nc = 0;
    for(line = 0; data[line] != NULL; ++line){
        int chara = 0;
        do{
            (*nc)++;
            if((data[line][chara] == ' ' || data[line][chara] == NEWLINE) && chara && data[line][chara-1] != ' '){
                (*nw)++;
            }
        }while(data[line][chara++] != NEWLINE);
        // (*nc)++;
    }
    *nl = line;
}
// Count block and line comments in the text read from stdin. Set
// line_comment_counter and block_comment_counter accordingly
void find_comments(int *line_comment_counter, int *block_comment_counter)
{
    *line_comment_counter = 0; *block_comment_counter = 0;
    char** data = getData();
    int line; int begin_block = 0, begin_line = 0;
    for(line = 0; data[line] != NULL; ++line){
        int chara = 0;
        do{
            if(!begin_line && data[line][chara] == '*' && begin_block && data[line][chara +1] =='/'){
                begin_block = 0;
                (*block_comment_counter)++;
                chara++;

            }
            else if(data[line][chara] == '/' && !begin_block && !begin_line){
                if(data[line][chara+1] == '/'){
                    (*line_comment_counter)++;
                    begin_line = 1;
                }
                if(data[line][chara+1] == '*')
                    begin_block = 1;
                chara++;
            }
        }while(data[line][chara++] != NEWLINE);
        begin_line = 0;
    }
    
}
/*******************************************************/
int main(void) 
{
    int to_do;
    int nl, nw, nc;
    int line_comment_counter, block_comment_counter;

    to_do = read_line();
    switch (to_do)
    {
    case 1: // wc()
        wc(&nl, &nw, &nc);
        printf("%d %d %d\n", nl, nw, nc);
        break;
    case 4:
        find_comments(&line_comment_counter, &block_comment_counter);
        printf("%d %d\n", block_comment_counter, line_comment_counter);
        break;
    default:
        printf("NOTHING TO DO FOR %d\n", to_do);
        break;
    }
    return 0;
}