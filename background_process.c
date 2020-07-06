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

int statusw ;

/*
    func:run the command in background
    params:parsed(pointer to command)
    return:doesn't return
*/
// void execArgsBack(char** parsed,int is_background) 
// { 
//     // Forking a child 
//     pid_t pid = fork();  
//     pid_t wpid;
//     int status;
//     if (pid == -1) { 
//         printf("\nFailed forking child.."); 
//         return; 
//     } else if (pid == 0) { 
//         status = execvp(parsed[0], parsed);
//         if (status < 0) { 
//             printf("\nCould not execute command.."); 
//         } 
//         exit(0); 
//     } else {                                                
        
//         //
//             printf("pid:%d",pid);
//             if(is_background){
//                         wpid=fork();
//                         if(wpid==0){
//                                 //record(cmd,pid,-1);
//                                 wait(&statusw);
//                                 if(WIFEXITED(statusw))
//                                    printf("\nnot success of the execution");    
//                             }   
//                         }
//                         else 
//                             waitpid(pid,&status,0);
    
//         // waiting for child to terminate 
//         //wait(NULL);  
//         return; 
//     } 
// }


/*
https://stackoverflow.com/questions/20432595/creating-a-background-process-for-shell-in-c
*/
void execArgsBack(char** parsed,int is_background) 
{
pid_t cpid;
int i;
//printf("cmd is %s\n", cmd);
cpid = fork();
if(cpid == 0) {
    i = execvp(parsed[0], parsed);
    if(i < 0) {
        printf("%s: %s\n", parsed[0], "command not found");
        exit(1);        
    }   
} 
}