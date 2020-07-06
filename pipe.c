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
int parsePipe(char* str, char** strpiped) 
{ 
    int i;
    //printf("in parsedpipes\n"); 
    for (i = 0; i < 2; i++) { 
        //printf("in parsedpipes loop\n");
        strpiped[i] = strsep(&str, "|"); 
        //printf("pip");

        if (strpiped[i] == NULL) 
            break; 
    } 
  
    if (strpiped[1] == NULL) 
        return 0; // returns zero if no pipe is found. 
    else {
        //printf("pip=[%s]",strpiped[0]);
        return 1; 
    } 
} 


/*          
https://www.quora.com/How-can-I-write-a-code-for-PIPE-in-C-shell-script-python
below code is written referenced to above website
*/
/*
    func:execute the piped commands
    params:parsed(1st command),parsedpipe(second command)
    return: return 1
*/
int execArgsPiped(char** parsed, char** parsedpipe) {
   pid_t pid1, pid2;
   int pipefd[2];
   // The two commands we'll execute.  In this simple example, we will pipe
   // the output of `ls` into `wc`, and count the number of lines present.
   // char *parsed[] = {"ls", "-l", "-h", NULL};
   // char *parsedpipe[] = {"wc", "-l", NULL};
   // // Create a pipe.
   pipe(pipefd);
   // Create our first process.
   pid1 = fork();
   if (pid1 == 0) {
      // Hook stdout up to the write end of the pipe and close the read end of
      // the pipe which is no longer needed by this process.
      dup2(pipefd[1], STDOUT_FILENO);
      close(pipefd[0]);
      // Exec `ls -l -h`.  If the exec fails, notify the user and exit.  Note
      // that the execvp variant first searches the $PATH before calling execve.
      execvp(parsed[0], parsed);
      perror("exec");
      return 1;
   }
   // Create our second process.
   pid2 = fork();
   if (pid2 == 0) {
      // Hook stdin up to the read end of the pipe and close the write end of
      // the pipe which is no longer needed by this process.
      dup2(pipefd[0], STDIN_FILENO);
      close(pipefd[1]);
      // Similarly, exec `wc -l`.
      execvp(parsedpipe[0], parsedpipe);
      perror("exec");
      return 1;
   }
   // Close both ends of the pipe.  The respective read/write ends of the pipe
   // persist in the two processes created above (and happen to be tying stdout
   // of the first processes to stdin of the second).
   close(pipefd[0]);
   close(pipefd[1]);
   // Wait for everything to finish and exit.
   waitpid(pid1,NULL,0);
   waitpid(pid2,NULL,0);
   return 0;
}