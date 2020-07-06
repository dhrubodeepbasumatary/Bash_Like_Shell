/*
    task:implementation of I/O redirection
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
#include <assert.h>
#include <fcntl.h>
#include <ctype.h>
#include <errno.h>


/*
    func:check which(< or > or both) redirection is  present in the input command
    params:command(input command)
    return: return an integer based on which redirection is present
*/ 
int redirectionCheck(char *command);


/*
    func:count the number of white spcaces in input command
    params:in(input command),len(length of command)
    return: number of white spaces present in input command
*/ 
int whitespaceCount(char *in, int len);


/*
    func:trims the leading and trailing spaces from the input string
    params:str( pointer to character string)
    return: doesn't  return 
*/ 
void trim(char *str);


/*
    func:this will tokenise the input string based on space and store tokens in other string
    params:in(pointe to character array),out(doubel pointer to characterb array)
    return: doesnt return 
*/ 
int stitch(char *in, char **out);


/*
    func:implements the I/O redirection
    params:intput(pointer to a character array conating the command),state(1:input redirection,
    2:output redirection,3:for both redirection,-1:no redirection)
    return: return -5
*/ 
int redirection(char *input, int state);