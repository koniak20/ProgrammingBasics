#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

// You should check while reading or writing if error happen (== -1), but I'm lazy!

int main(int argc, char** argv){
    int fd[2];
    // fd stands for file descriptor
    // fd[0] -read 
    // fd[1] - write
    if(pipe(fd) == -1){
        printf("Error while opening the pipe\n");
        return 1;
    }
    int id = fork();
    if( id == -1){
        printf("Error while forking\n");
        return 2;
    }

    if(id == 0){        // 0 means that is child process
        close(fd[0]);   // fd are inheritanced from parent process
        int x;
        printf("Input a number: ");
        scanf("%d", &x);
        write(fd[1], &x, sizeof(int));
        close(fd[1]);
    } else {
        close(fd[1]);
        int y;
        read(fd[0],&y, sizeof(int));
        printf("Child process got half of %d \n", 2*y);
        close(fd[0]);
    }
    return 0;

}
