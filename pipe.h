/*
    task:implementation of I/O redirection
    Author:Dilip kumar chauhan
*/

/*
    libraries: include required libraries
*/
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h> 


/*
    func:check whether pipe is present or not
    params:str(pointer to input command),strpiped(store both commands separated by pipe)
    return: return an integer based on which redirection is present
*/  
int parsePipe(char* str, char** strpiped);

/*          
https://www.quora.com/How-can-I-write-a-code-for-PIPE-in-C-shell-script-python
below code is written referenced to above website
*/

/*
    func:execute the piped commands
    params:parsed(1st command),parsedpipe(second command)
    return: return 1
*/  
int execArgsPiped(char** parsed, char** parsedpipe);
