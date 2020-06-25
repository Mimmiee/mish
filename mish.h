/*
 * mish.h
 * Labb 3.  
 * Systemnära programmering HT19.
 * Author: Mimmi Edholm, id18mim 
 * 
 * mish is a mini shell that can execute external commands and some internal commands 
 * such as echo and change directory.
 * mish can handle the sigint signal. 
 */ 
#include "parser.h"

/*
 * main 
 * Read commands and print prompt. 
 */ 
int main(void); 

/*
 * runComands
 * Creates pipes and fork. Executes external commands. 
 * @com: Array of comands to execute.
 * @size: The number of elements in the array.
 * Return 0 if succsess, -1 if failed. 
 */ 
int runCommands(command com[], int size); 

/*
 * runInternComands
 * Execute echo and cd. 
 * @com: Command to execute.
 * Return 0 if succsess, -1 if failed. 
 */ 
int runInternCommand(command com);