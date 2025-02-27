/* execute.h   
 * 
 * Headerfile for a shell command interpreter and executer
 *
 * Author: Peter Jacobson
 * Date:   950706
 *
 * Modified by: Tomas Halvarsson
 * Date:	1998-07-14
 * What?	Removed static from both function declarations
 *
 * Date:	1998-12-06
 * What?	Changed some comments
 *
 * Date:	1999-09-01
 * What?	Added return types to the functions (finally!) and updated the
 * 		comments accordingly
 *
 * Modified by: Dennis Olsson
 * Date:	2007-10-18
 * What?	Added the constants READ_END and WRITE_END
 */

#ifndef _EXECUTE_
#define _EXECUTE_

/* Constants for adressing pipes without using numbers */
#ifndef READ_END
#define READ_END 0
#endif
#ifndef WRITE_END
#define WRITE_END 1
#endif


/* Duplicate a pipe to a standard I/O file descriptor
 * Arguments:	pip	the pipe
 *		end	tells which end of the pipe shold be dup'ed; it can be
 *			one of READ_END or WRITE_END
 *		destfd	the standard I/O file descriptor to be replaced
 * Returns:	-1 on error, else destfd
 */
int dupPipe(int pip[2], int end, int destfd);


/* Redirect a standard I/O file descriptor to a file
 * Arguments:	filename	the file to/from which the standard I/O file
 * 				descriptor should be redirected
 * 		flags	indicates whether the file should be opened for reading
 * 			or writing
 * 		destfd	the standard I/O file descriptor which shall be
 *			redirected
 * Returns:	-1 on error, else destfd
 */
int redirect(char *filename, int flags, int destfd);

#endif