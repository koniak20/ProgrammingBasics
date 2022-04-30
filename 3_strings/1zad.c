#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void removeStringTrailingNewline(char *str) {
  if (str == NULL)
    return;
  int length = strlen(str);
  if (str[length-1] == '\n')
    str[length-1]  = '\0';
}
int lengthFirstWord(char line[]){
    int result = 0;
    while(1){
        if(line[result] == ' ' || line[result] == '\0')
            return result;
        result++;
    }   
}
char* encryptCaesar(char line[]){
    int s = lengthFirstWord(line);
    int size_of_letter = 0;
    for(int i=0; line[i] != '\0'; i++){
        if(line[i] != ' '){
            size_of_letter = line[i] < 92 ? 'A' : 'a';
            line[i] = size_of_letter + ((line[i] + s)%size_of_letter)%26;
            }
    }
    // printf("Encrypted: %s\n",line);
    return line;
}
char* getEncryptedLine(){
    char *line;
    size_t bufsize = 32;
    line = (char *)malloc(bufsize * sizeof(char));
    size_t characters = getline(&line,&bufsize,stdin);
    if(characters != -1 && line[0] == '\n')
        characters = -1;
    removeStringTrailingNewline(line);
    return characters == -1 ? NULL : encryptCaesar(line);
}

int main(){
    char *begin;
    
    while(begin=getEncryptedLine()){
        printf("%s \n",begin);
    }
    
    getEncryptedLine();
    
    
}