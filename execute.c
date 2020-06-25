#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h> 
#include <fcntl.h>
#include <sys/stat.h> 

#include "execute.h"

/*
 * execute.c 
 * Labb 3.  
 * Systemnära programmering HT19.
 * Implemented by: Mimmi Edholm id18mim 
 * 
 */ 

int dupPipe(int pip[2], int end, int destfd){
    //Pipes are closed by the caller of the function.
    int inspect = dup2(pip[end], destfd); 

    if(inspect != destfd){
        perror("Canẗ dup pipe");
        return -1; 
    }
    return destfd;  
} 

int redirect(char *filename, int flags, int destfd){
    
    int file = open(filename, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);  
    if(file == -1){
        perror(filename);
        return -1; 
    }
    int inspect = dup2(file, destfd); 
    close(file); 
    
    if(inspect != destfd){
        perror(filename);
        return -1; 
    }
    return destfd;    
}

