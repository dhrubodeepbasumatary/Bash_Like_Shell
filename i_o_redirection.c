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
//#include <sys/types.h> 
//#include <readline/readline.h> 
//#include <readline/history.h> 
//#include <signal.h>
//#include <setjmp.h>
//#include <time.h>

/*
https://github.com/pranav93y/myshell/blob/master/lib/myshell.c?fbclid=IwAR0R5NqBho0OATSLlMJOzr0xHIhOMW23FZ5jGwburF48-bx153omE8K4YZI
The below code is taken from above website and modified
*/

/*
    func:check which(< or > or both) redirection is  present in the input command
    params:command(input command)
    return: return an integer based on which redirection is present
*/ 
int redirectionCheck(char *command){
  char *out = strstr(command, ">");
  char *in = strstr(command, "<");

  if((out != NULL) && (in != NULL)){
    //both inut and output redirection
    return 3;
  }else if(out != NULL){
    //output redirection only
    return 2;
  }else if(in != NULL){
    //input redirection only
    return 1;
  }else{
    return -1;
  }
}


/*
    func:count the number of white spcaces in input command
    params:in(input command),len(length of command)
    return: number of white spaces present in input command
*/ 
int whitespaceCount(char *in, int len){
  int i = 0;
  int count = 0;
  for(i = 0; i < len; i++){
    if(in[i] == ' '){
      count++;
    }
  }
  return count;
}


/*
    func:trims the leading and trailing spaces from the input string
    params:str( pointer to character string)
    return: doesn't  return 
*/ 
void trim(char *str)
{

        int i;
    int begin = 0;

    int end = strlen(str) - 1;

    while (isspace((unsigned char) str[begin]))
        begin++;

    while ((end >= begin) && isspace((unsigned char) str[end]))
        end--;

    // Shift all characters back to the start of the string array.
    for (i = begin; i <= end; i++)
        str[i - begin] = str[i];

    str[i - begin] = '\0'; // Null terminate string.
}


/*
    func:this will tokenise the input string based on space and store tokens in other string
    params:in(pointe to character array),out(doubel pointer to characterb array)
    return: doesnt return 
*/ 
int stitch(char *in, char **out){
  int i = 1;
  char *temp, cpy[100];

  sprintf(cpy, "%s", in);
  
  temp = strtok(in, " ");
  sprintf(out[0], "%s", temp);

  while((temp = strtok( NULL, " ")) != NULL){
    sprintf(out[i], "%s", temp);
    i++;
  }
  out[i] = NULL;
  return i;
}


/*
    func:implements the I/O redirection
    params:intput(pointer to a character array conating the command),state(1:input redirection,
    2:output redirection,3:for both redirection,-1:no redirection)
    return: return -5
*/
int redirection(char *input, int state){

  char cpy[1000], path[1000], command[1000], filename[1000], **args, *temp;
  int spacecount, i = 0, fd;

  sprintf(cpy, "%s", input);

  temp = strtok(cpy, " ");
  sprintf(path, "%s", temp);

  sprintf(cpy, "%s", input);
  //printf("in >>>>>>>>>>>\n");

  if(state == 1){
    //printf("in before1\n");

    temp = strtok(cpy, "<");
    sprintf(command, "%s", temp);
    command[strlen(command) - 1] = '\0';
    temp[strlen(temp) - 1] = '\0';

    temp = strtok(NULL, "\0");
    sprintf(filename, "%s", temp);
    trim(filename);
    //printf("in before1\n");

    spacecount = whitespaceCount(command, strlen(command));

    args = calloc((spacecount)+2, sizeof(char *));
    for(i = 0; i < spacecount + 1; i ++){
      args[i] = calloc(strlen(command)+10, sizeof(char));
    }
    //printf("in before2\n");
    i = stitch(command, args);

    if((fd = open(filename, O_RDONLY, 0644)) < 0){
      //perror("open error");
      //return -1;
    }

    pid_t pid = fork();  
  
    if (pid == -1) { 
        printf("\nFailed forking child.."); 
        return -5 ; 
    } else if (pid == 0) { 
            dup2(fd, 0);
            close(fd);
        if (execvp(path, (char *const *)args) < 0) { 
            printf("\nCould not execute command.."); 
        } 
        exit(0); 
    } else { 
        // waiting for child to terminate 
        //printf("HP: hello from parent\n"); 
        wait(NULL); 
        //printf("CT: child has terminated\n"); 
        //wait(NULL);
        //exit(0);
        return -5; 
    } 


  }else if(state == 2){
    temp = strtok(cpy, ">");
    sprintf(command, "%s", temp);
    command[strlen(command) - 1] = '\0';
    temp[strlen(temp) - 1] = '\0';

    temp = strtok(NULL, "\0");
    sprintf(filename, "%s", temp);
    trim(filename);

    //printf("in before>>0\n");
    spacecount = whitespaceCount(command, strlen(command));

    args = calloc((spacecount)+2, sizeof(char *));

    for(i = 0; i < spacecount + 1; i ++){
      args[i] = calloc(strlen(command)+10, sizeof(char));
    }
      // printf("in before>>1\n");
    i = stitch(command, args);

    if((fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0){
      perror("open error");
      return -1;
    }

    pid_t pid = fork();  
  
    if (pid == -1) { 
        printf("\nFailed forking child.."); 
        return -5 ; 
    } else if (pid == 0) { 
            dup2(fd, 1);
            close(fd);
        if (execvp(path, (char *const *)args) < 0) { 
            printf("\nCould not execute command.."); 
        } 
        exit(0); 
    } else { 
        // waiting for child to terminate 
        //printf("HP: hello from parent\n"); 
        wait(NULL); 
        //printf("CT: child has terminated\n"); 
        //wait(NULL);
        //exit(0);
        return -5; 
    } 

  }else if(state == 3){
    char filename2[1000];
    int fd2;

    temp = strtok(cpy, "<");
    sprintf(command, "%s", temp);
    command[strlen(command) - 1] = '\0';
    temp[strlen(temp) - 1] = '\0';

    temp = strtok(NULL, ">");
    sprintf(filename, "%s", temp);
    filename[strlen(filename) - 1] = '\0';
    temp[strlen(temp) - 1] = '\0';
    trim(filename);

    temp = strtok(NULL, "\0");
    sprintf(filename2, "%s", temp);
    trim(filename2);

    spacecount = whitespaceCount(command, strlen(command));

    args = calloc((spacecount)+2, sizeof(char *));
    for(i = 0; i < spacecount + 1; i ++){
      args[i] = calloc(strlen(command)+10, sizeof(char));
    }

    i = stitch(command, args);

    if((fd = open(filename, O_RDONLY, 0644)) < 0){
      perror("open error");
      return -1;
    }

    if((fd2 = open(filename2, O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0){
      perror("open error");
      return -1;
    }

    dup2(fd, 0);
    close(fd);


    dup2(fd2, 1);
    close(fd2);

    execvp(path, (char *const *)args);
    perror("execvp error");
    //_exit(EXIT_FAILURE);

  }
  return -5;
}
