/*
 * sighant.c 
 * Labb 3.  
 * Systemnära programmering HT19.
 * Author: Mimmi Edholm, id18mim 
 */ 
#define _XOPEN_SOURCE

#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>  
#include <unistd.h> 

#include "sighant.h"
#include "parser.h" 


extern pid_t globPids[MAXCOMMANDS]; 
extern int forks; 

/*
 * SigKill
 */
void sigKill(int sigNum){

    int status; 
    for(int i = 0;i < forks ; i++){
        kill(globPids[i], sigNum); 
        globPids[i] = waitpid(globPids[i], &status, 0);
        printf("\n"); 
    }
}

/*
 * _sighandler_t 
 */
__sighandler_t sig(int signo, __sighandler_t func){
    
    struct sigaction act, oact;
    
    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    if (signo == SIGALRM) {
        #ifdef SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT;
        #endif
    } 
    else {
        #ifdef SA_RESTART
        act.sa_flags |= SA_RESTART;
        #endif
    }
    if (sigaction(signo, &act, &oact) < 0)
        return(SIG_ERR);
    return(oact.sa_handler);
}