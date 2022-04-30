#include "matrix_operations.h"
#include <string.h>
#include <sys/file.h>
#include <unistd.h>

void copyFile(char* old_file ,char* new_file){
    FILE *ptr_old=fopen(old_file,"rb"), *ptr_new = fopen(new_file,"wb");
    if(ptr_old == NULL){
        return;
    }
    if(ptr_new == NULL){
        fclose(ptr_old);
        return;
    }
    flock(fileno(ptr_old),LOCK_EX);
    flock(fileno(ptr_new),LOCK_EX);
    int a;
	while(1){
        a = fgetc(ptr_old);
        if(!feof(ptr_old))
            fputc(a,ptr_new);
        else 
            break;
	}	
    fclose(ptr_new);
    fclose(ptr_old);
    flock(fileno(ptr_old),LOCK_UN);
    flock(fileno(ptr_new),LOCK_UN);
    return;
}

void multiplyPartOfMatrixes(char* A, char* B, char* C, int part){
    FILE* A_file = fopen(A,"r");
    FILE* B_file = fopen(B,"r");
    copyFile(C,"tmp.txt");
    FILE* C_file = fopen(C,"w");    
    flock(fileno(C_file),LOCK_EX);
    FILE* tmp = fopen("tmp.txt","r");
    if(!C_file || !tmp || !B_file  || !A_file )
        return;
    flock(fileno(tmp),LOCK_EX);
    int ax = 0,ay; setSizeMatrix(A_file,&ax,&ay);
    int bx = 0,by; setSizeMatrix(B_file,&bx,&by);

    // printf("%d %d\n%d %d\n", ax,ay,bx,by);
    int cx = ax , cy = by;
    char* number = malloc(sizeof(char)*20);
    for(int i=1; i<=cx; i++){
        int beg = (part == 1 ? 1:cy/2 +1);
        int end = (part == 1 ? cy/2:cy);
        // printf("%d %d\n",beg,end);
        for(int j=1; j<= cy; j++){
            int result = 0;
            if(beg <= j && j <= end){
                for(int k=1; k<=ay; k++){
                    result += getElementMatrix(A_file,i,k,ay)*getElementMatrix(B_file,k,j,by);
                }
                fprintf(C_file,"%d",result);
                fscanf(tmp," %s",number);
                }
            else{
                fscanf(tmp," %s",number);
                if(feof(tmp))
                    strcpy(number,"-");
                if(!strcmp(number,"-")){
                    fprintf(C_file,"-");
                }
                else{
                    fprintf(C_file,"%s",number);
                }

            }
            if(j != cy)
            	fputc(' ',C_file);
        }
        fputc('\n',C_file);
        // printf("%c\n",fgektc(tmp));

    }
    fclose(A_file); fclose(B_file); fclose(C_file); fclose(tmp);
    flock(fileno(C_file),LOCK_UN);
    flock(fileno(tmp),LOCK_UN);
    remove("tmp.txt");
}

int main(int argc, char **argv){
    if(argc != 3){
        printf("Not enough arguments\nYou have to give me: list.txt number\nlist.txt -> give there matrixes which are to be multiplied\nnumber -> which part of second matrix have to be used (1 first , 2 second)\n");
    }
    else{
        FILE* lista = fopen(argv[1],"r");
        char* A = (char*) malloc(sizeof(char)*50);
        char* B = (char*) malloc(sizeof(char)*50);
        char* C = (char*) malloc(sizeof(char)*50);
        while(!feof(lista)){
            fscanf(lista,"%s %s %s\n",A,B,C);
            multiplyPartOfMatrixes(A,B,C,atoi(argv[2]));
        }

    }
}
