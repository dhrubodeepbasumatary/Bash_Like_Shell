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

//#include <time.h> 
// #include <sys/types.h> 
//#include <sys/wait.h> 
// #include <signal.h>
// #include <setjmp.h>
// #include <assert.h>
// #include <fcntl.h>
// #include <ctype.h>
// #include <errno.h>
  
#define clear() printf("\033[H\033[J") 


/*
    func:this will redirect to our terminal
    params:no params
    return: doesnt return 
*/  
void init_shell()   
{ 
    clear(); 
    printf("\n\n\n\n******************"
        "************************"); 
    printf("\n\n\n\t****MY SHELL****"); 
    printf("\n\n\n\n*******************"
        "***********************"); 
    char* username = getenv("USER"); 
    printf("\n\n\nUSER is: @%s", username); 
    printf("\n"); 
    sleep(1); 
    clear(); 
} 
  

/*
    func:fuction to take input command from terminal
    params:str(input command)
    return: return the input command 
*/ 
int takeInput(char* str) 
{ 
    char* buf; 
  
    buf = readline(">>"); 
    if(buf==NULL)
        exit(0);

    if (strlen(buf) != 0) { 
        add_history(buf); 
        strcpy(str, buf); 
        return 0; 
    } else {
        return 1; 
    } 
} 
 
