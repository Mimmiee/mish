#ifndef _SIGHANT_H_
#define _SIGHANT_H_

#include <signal.h>

/*
 * sighant.h
 * Labb 3.  
 * Systemnära programmering HT19.
 * Author: Mimmi Edholm id18mim 
 * 
 * sighant handle SIGINT.
 * The child processes are killed and a new propmt are printed.  
 */

/*
 * sigKill
 * Kills each running process. 
 * @sigNum: Signal
 */
void sigKill(int sigNum); 

/*
 * _sighandler_t 
 * @signo: Signal to handle.
 * @func: Function to run. 
 */
__sighandler_t sig(int signo, __sighandler_t func);

#endif // _SIGHANT_H_