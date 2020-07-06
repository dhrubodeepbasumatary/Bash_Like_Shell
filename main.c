/*
	Project Title:Bash Like shell

*/

/**************including required libraries *********************************************/
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <readline/readline.h> 
#include <readline/history.h> 
#include <signal.h>
#include <setjmp.h>
#include <time.h>
#include <assert.h>
#include <fcntl.h>
#include <ctype.h>
#include <errno.h>

#include "calc.h"
#include "i_o_redirection.h"
#include "ownCommand.h"
#include "pipe.h"
#include "input.h"
#include "background_process.h"
  
/***************** defining the Macros  and global variables*****************************************/ 
#define MAXCOM 1000 // max number of letters to be supported 
#define MAXLIST 100 // max number of commands to be supported 

static sigjmp_buf env;



/******************************Executing the System Command**********************************/  

//******** Function where the system command is executed******* 
void execArgs(char** parsed) 
{ 
    // Forking a child 
    pid_t pid = fork();  
  
    if (pid == -1) { 
        printf("\nFailed forking child.."); 
        return; 
    } else if (pid == 0) { 
        if (execvp(parsed[0], parsed) < 0) { 
            printf("\nCould not execute command.."); 
        } 
        exit(0); 
    } else { 
        // waiting for child to terminate 
        wait(NULL);  
        return; 
    } 
} 


//**************************** Ececution of ownCommand *****************************************/

// Function to execute builtin commands 
int ownCmdHandler(char** parsed,char *str) 
{ 
    int NoOfOwnCmds = 7, i, switchOwnArg = 0; 
    char* ListOfOwnCmds[NoOfOwnCmds]; 
    char* username;
    //printf("parsed=%s\n",str);
    int len=strlen(str),j=0; 
    char exp[len-4];
  
    ListOfOwnCmds[0] = "exit"; 
    ListOfOwnCmds[1] = "cd"; 
    ListOfOwnCmds[2] = "help"; 
    ListOfOwnCmds[3] = "history"; 
    ListOfOwnCmds[4] = "calc"; 
    ListOfOwnCmds[5] = "search";
    ListOfOwnCmds[6] = "hello"; 

  
    for (i = 0; i < NoOfOwnCmds; i++) { 
        if (strcmp(parsed[0], ListOfOwnCmds[i]) == 0) { 
            switchOwnArg = i + 1; 
            break; 
        } 
    } 
    //printf("command %s%s",parsed[0],parsed[1]); 
    switch (switchOwnArg) { 
    case 1: 
        printf("\nGoodbye\n"); 
        exit(0); 
    case 2: 
        chdir(parsed[1]); 
        return 1; 
    case 3: 
        openHelp(); 
        return 1;
    case 4:
        history(); 
        return(1);
    case 5:
         for(j=5;j<len;j++)
         {
            exp[j-5]=str[j];
         }
         exp[j-5]='\0';

         printf("%s=%d\n",exp,evaluate(exp,strlen(exp)));   
         return 1;
    case 6: 
    	search(parsed[1]);
        return 1; 
    case 7:
        username = getenv("USER"); 
        printf("\nHello %s.\nMind that this is "
            "not a place to play around."
            "\nUse help to know more..\n", 
            username); 
        return 1; 
    default: 
        break; 
    } 
  
    return 0; 
} 
//**************************** END-OF COMMAND *****************************************/




/**************************** Preprocessing of the command  ****************************/  

/*
taken help from: https://www.geeksforgeeks.org/making-linux-shell-c/
*/

// function for parsing command words 
void parseSpace(char* str, char** parsed) 
{ 
    int i; 
    //printf("inputparse=%s",str);
    for (i = 0; i < MAXLIST; i++) { 
        parsed[i] = strsep(&str, " "); 
  
        if (parsed[i] == NULL) 
            break; 
        if (strlen(parsed[i]) == 0) 
            i--;    
    } 
}

//processing the input string
int processString(char* str, char** parsed, char** parsedpipe,int *is_background) 
{ 
  
    char* strpiped[2]; 
    int piped = 0,x,len1=strlen(str),i=0;
    //char str1[len+1];
    char strt[len1];

    //printf("input=%s",str);
     
    if(str[len1-1]=='&')
    {
        *is_background= 1;
        for(i=0;i<len1-1;++i)
        {
            strt[i] = str[i];
        } 
        strt[i]='\0';
        str[len1-1]='\0';
    }
    else
    {
        *is_background = 0;
    }
    
    int len=strlen(str);
    char str1[len+1];


    for(i=0;i<len;i++)
    {
       str1[i]=str[i];
    }
    str1[i]='\0';

    //printf("input=%s",str);
    if((x=redirectionCheck(str))!=-1)
    {

        redirection(str, x); 
        return -5;    
    }
    else
    {    
     
        piped = parsePipe(str, strpiped);
        //printf("pip1=[%s] pip2=[%s] piped=[%d]",strpiped[0],strpiped[1],piped); 
        if (piped) {
            parseSpace(strpiped[0], parsed); 
            parseSpace(strpiped[1], parsedpipe); 
      
        } else { 
            parseSpace(str, parsed); 
        }  
         
        if (ownCmdHandler(parsed,str1)) 
           return 0; 
        else
            return 1 + piped;
    }
    //sprintf("not terminated\n");
} 


/*****************************End of Preprocessing the command ***********************************/


//signal handler
void sigint_handler(int signo) {
    siglongjmp(env, 1);
}



/*************************main function to handle all the command ***************************/  
int main() 
{ 
    char inputString[MAXCOM], *parsedArgs[MAXLIST]; 
    char* parsedArgsPiped[MAXLIST]; 
    int execFlag = 0,flag=0,is_background=0;
    char* username; 
    username = getenv("USER");
    //cmd= malloc(sizeof(parseInfo));
    char cwd[256];
    init_shell(); 


    signal(SIGINT, sigint_handler);
    signal(SIGTSTP, SIG_IGN);
    while (1) { 

        // print shell line 
         if (sigsetjmp(env,1) == 1) {
            printf("\n");
        }

        printf("%s@bash",username); 
        printDir(); 
        // take input 
        if (takeInput(inputString))
            continue; 
        // process ;

        store_history(inputString);
        execFlag = processString(inputString, 
        parsedArgs, parsedArgsPiped,&is_background);


         if (execFlag == 1) 
        {
            //printf("\nBanana\n");
            if(is_background == 0)  
                execArgs(parsedArgs); 
            else
            {
                printf("Pine_apple=%s=\n",parsedArgs[0]);
                execArgsBack(parsedArgs,1);
            }
        }
  
        if (execFlag == 2)
            execArgsPiped(parsedArgs, parsedArgsPiped);
            //execArgs(parsedArgs); 

        //store_history(inputString);
    } 
    return 0; 
}

/********************************End of main**************************************************/ 