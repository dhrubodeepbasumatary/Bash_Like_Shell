/*
    task:implementation of our own command
    Author:Dilip kumar chauhan
*/

/*
    libraries: include required libraries
*/
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <sys/wait.h> 
#include <readline/readline.h> 
#include <readline/history.h> 
#include <assert.h>

/*
    func:open the help option on the terminal
    params:no params
    return: doesnt return 
*/
void openHelp() ;


/*
    func:print the current directory
    params:no params
    return: doesnt return 
*/
void printDir() ;


/*
    func:print the history of command
    params:no params
    return: doesnt return 
*/ 
void history();


/*
    func:store the history of command
    params:str(string containing the command)
    return: doesnt return 
*/
void store_history(char *str);


/*
    func:search those commands in history having given string as substring 
    params:str(a string to be searched)
    return: doesnt return 
*/
void search(char *str);
