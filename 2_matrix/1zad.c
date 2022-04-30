#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int statistic[21]={0};

void RandomArrayMaker (int lower, int upper, int tab[], int quantity){
    for(int i=0; i<quantity; i++){
        tab[i] = lower + rand() % (upper-lower+1);
        if(lower == -10 && upper == 10)
            statistic[tab[i]+10]++;
    }
}

void reverse (int tab[],int length){
    for(int i=0; i<length/2; i++){
        int tmp = tab[i];
        tab[i] = tab[length - i - 1];
        tab[length - 1 - i] = tmp;
    }
}

void printArray (int tab[], int length){
    printf("\n[");
    for(int i=0; i < length; i++)
        printf("%d,",tab[i]);
    printf("]");
}
int one_two(int tab1[], int length1, int tab2[], int length2){
    int index1 = 0, index2 = 0;
    int result = 1;
    int tmp = tab1[0] < tab2[0] ? tab1[index1++] : tab2[index2++];
    while ( index1 < length1 && index2 < length2){
        if(tab1[index1] < tab2[index2] && tab1[index1] != tmp){
            result++;
            tmp = tab1[index1++];
        }
        else if(tab2[index2] != tmp){
            result++;
            tmp =tab2[index2++];
        }
        else{
            index1++; index2++;
        }
    }
    while( index2 != length2){  
            if(tmp < tab2[index2]){
                result++;
                tmp = tab2[index2];
            }
            index2++;
        }   
    while(index1 != length1){
            if( tmp < tab1[index1]){
                result++;
                tmp = tab1[index1];
            }
            index1++;
        }
    printf("len: %d\n", result);
    return result;
}

int main(){
    srand(time(0));
    int n = 1000000;
    int tab[n];
    // RandomArrayMaker(-10,10,tab,n);
    // // printArray(tab,n);
    // printArray(statistic,21);






    int t1[4]={1,1,7,21} , t2[1]={0};
    int a = one_two(t1,4,t2,1);
    // RandomArrayMaker(0,4,tab,n);
    // printArray(tab,n);
    // reverse(tab,n);
    // printArray(tab,n);
}