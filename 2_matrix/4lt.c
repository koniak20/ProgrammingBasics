#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

void printArray(int tab[][SIZE]){
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

void scanInput(int tab[][SIZE]){
    for(int i=0; i<SIZE; ++i)
        for(int j=0; j<SIZE; ++j)
            scanf("%d",&tab[i][j]);
}

int findMaxArea(int tab[][SIZE]){
    int result = 0 , area = 0;
    for(int x=0; x<SIZE; ++x){
        for(int y=0; y<SIZE; ++y){
            int first_above = SIZE;
            int j=y;
            for(int i=x; i<SIZE; i++){
                j=y;
                if(tab[i][j] == 1)
                    break;
                for(j= y ; j<SIZE && j < first_above; j++){
                    if(tab[i][j] == 1 && j != 0){
                        first_above = j;
                        break;
                    }
                }   j--;
                area = (i-x+1)*(j-y+1);
                if(result < area)
                    result = area;
            }
        }
    }
    return result;
}
int main(){
    system("clear");
    int tab[SIZE][SIZE];
    scanInput(tab);
    printf("%d\n",findMaxArea(tab));
}



// printf("(x,y)=(%d,%d) (i,j)=(%d,%d)\n",x,y,i,j);