#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>   
#include <unistd.h> 
#include <signal.h>
#include <fcntl.h>

#include "mish.h"
#include "parser.h"
#include "sighant.h"
#include "execute.h"

/*
 * mish.c
 * Labb 3.  
 * Systemnära programmering HT19.
 * Author: Mimmi Edholm, id18mim.
 * Mini shell 
 */ 

//Global in order to be handled by sighant.c 
pid_t globPids[MAXCOMMANDS]; 
int forks = 0; 

/*
 * main 
 */
int main(void){

    int status; 
    int comNum; 
    char buf[MAXCOMMANDS]; 
    command coms[MAXCOMMANDS];

    sig(SIGINT, sigKill); 

    //Print prompt 
    if (isatty(STDOUT_FILENO) && isatty(STDIN_FILENO)){
        fprintf(stdout, "mish%% ");
        fflush(stdout);
    }
    while(fgets(buf, MAXCOMMANDS, stdin) != NULL){

        if(buf[strlen(buf) - 1] == '\n') {
            buf[strlen(buf) - 1] = 0; 
        }
        //Parse commands 
        comNum = parse(buf,coms);
        if(comNum != 0){
            //Check for internal commands 
            if((strcmp(coms[0].argv[0], "echo") == 0)||(strcmp(coms[0].argv[0], "cd")== 0)) {
                status = runInternCommand(coms[0]);
            } 
            else {
            status = runCommands(coms, comNum); 
            }  
        }

        if(status == -1){
            fprintf(stderr,"Couldn't run command.\n");
        }
        status = 0;
        //Print prompt 
        if (isatty(STDOUT_FILENO) && isatty(STDIN_FILENO)) {
            fprintf(stdout, "mish%% ");
            fflush(stdout);
        }
    }
    return 0; 
}

/*
 * runCommands 
 */
int runCommands(command com[], int size){
    int status = 0; 
    int pidStatus; 
    int pipes[MAXCOMMANDS][2];
    pid_t pid;
    forks = 0; 

    //Loop to create pipes.
    for(int i = 0; i < size-1; i++){
        
        if(pipe(pipes[i]) == -1){
            perror("Pipe error"); 
            exit(EXIT_FAILURE);
        } 
    }
    
    //Loop to create needed processes. 
    for(int i = 0; i < size; i++){
      
        pid = fork(); 
        if(pid < 0 ){
            fprintf(stderr, "fork error\n"); 
        }
        //Child. 
        else if(pid == 0){
            //Check for redirects.
            if(com[i].outfile != NULL){
                redirect(com[i].outfile, O_WRONLY | O_CREAT | O_EXCL, STDOUT_FILENO);
            }
            if(com[i].infile != NULL){
                redirect(com[i].infile, O_RDONLY, STDIN_FILENO);
            }
            
            if(i != 0){
                dupPipe(pipes[i-1], READ_END, STDIN_FILENO); 
            }
            if(i+1 != size){
                dupPipe(pipes[i], WRITE_END, STDOUT_FILENO); 
            }

            //Close all pipes.
            for(int j = 0; j < size - 1; j++){

                close(pipes[j][0]);
                close(pipes[j][1]);      
            }

            execvp(com[i].argv[0], com[i].argv);
            perror(com[i].argv[0]); 
            exit(127); 
        }
        globPids[i] = pid;
        forks ++; 
    }
    for(int i=0; i<size-1; i++){

        close(pipes[i][0]);
        close(pipes[i][1]);
    } 

    //Loop over all child processes and wait for them
    for(int j=0; j<forks; j++){
 
        globPids[j] = waitpid(globPids[j], &pidStatus, 0);

        if(pidStatus == -1){
            perror("Wait"); 
            status = -1; 
        }
        if((pidStatus != 0 )){ 
            status = -1; 
        }
    }
    forks = 0; 
    return status; 
}

/*
 * runInternCommands 
 */
int runInternCommand(command com){

    int status = 0;

    if(strcmp(com.argv[0], "echo") == 0){

        for(int i = 1; i < com.argc -1; i++){
            printf("%s ", com.argv[i]);
        } 
        printf("%s\n",com.argv[com.argc -1]);    
    }
    else{

        if(com.argc == 1){
            //Find enviorment variable 
            char *home = getenv("HOME");

            if(home == NULL){
                fprintf(stderr, "Couldn't find home-directory"); 
                return -1; 
            }
            status = chdir(home); 

            if(status == -1){
                perror(com.argv[0]);
            }
        }
        else{
            status = chdir(com.argv[1]);

            if(status == -1){
                perror(com.argv[0]);
            }
        }
    }
    return status; 
}