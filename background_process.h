/*
    task:run the command in background process
    Author:Dilip kumar chauhan
*/

/*
    libraries: include required libraries
*/
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 


/*
    func:run the command in background
    params:parsed(pointer to command)
    return:doesn't return
*/
void execArgsBack(char** parsed,int is_background);