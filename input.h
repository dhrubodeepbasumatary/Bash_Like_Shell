/*
    task:implementation function for taking input and function for redirecting to our terminal
    Author:Dilip kumar chauhan
*/

/*
    libraries: include required libraries
*/
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <readline/readline.h> 
#include <readline/history.h> 


/*
    func:this will redirect to our terminal
    params:no params
    return: doesnt return 
*/  
void init_shell();  


/*
    func:fuction to take input command from terminal
    params:str(input command)
    return: return the input command 
*/ 
int takeInput(char* str) ;