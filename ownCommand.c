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
//#include <sys/types.h> 
//#include <signal.h>
//#include <setjmp.h>
//#include <time.h>
//#include <fcntl.h>
//#include <ctype.h>
//#include <errno.h>


/*
    func:open the help option on the terminal
    params:no params
    return: doesnt return 
*/
void openHelp() 
{ 
    puts("\n***WELCOME TO MY SHELL HELP***"
        "\nCopyright @ Suprotik Dey"
        "\n-Use the bash like  shell"
        "\nList of Commands supported:"
        "\n>cd"
        "\n>ls"
        "\n>exit"
        "\n>history"
        "\n>search"
        "\n>calc"
        "\n>all other general commands available in UNIX shell"
        "\n>pipe handling"
        "\n>signal handling"
        "\n>i/o redirection"
        "\n>improper space handling"
        "\n>"); 
  
    return; 
}


/*
    func:print the current directory
    params:no params
    return: doesnt return 
*/ 
void printDir() 
{ 
    char cwd[1024]; 
    getcwd(cwd, sizeof(cwd)); 
    printf("%s", cwd); 
} 


/*
    func:print the history of command
    params:no params
    return: doesnt return 
*/ 
void history()
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int i=1;

    fp = fopen("history.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("%d  %s",i,line);
        i+=1;
    }

    fclose(fp);
} 


/*
    func:store the history of command
    params:str(string containing the command)
    return: doesnt return 
*/
void store_history(char *str)
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char s[64];
    assert(strftime(s, sizeof(s), "%c", tm));
   // printf("%s\n", s);  


   FILE *fp;
   int len=strlen(str);
   //dstr[len]='\n';
   fp = fopen("history.txt", "a+");
   fprintf(fp,"%s  %s\n",s,str);
   //fprintf(fp, "\n");
   fclose(fp);
  // printf("history=%s\n",str);
   return;
}


/*
    func:search those commands in history having given string as substring 
    params:str(a string to be searched)
    return: doesnt return 
*/
void search(char *str)
{

	FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int i=1;
    char *s;

    fp = fopen("history.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
    		int lenstr=strlen(line),k=0,j=0;
    		//printf("%d  %s",i,line);

			for(k=0;k<lenstr;k++)
			{
				if(line[k]==' ' && line[k+1]==' ')
					break;
			}
			char str1[lenstr-(k+2)];
			k+=2;
			while(k<lenstr)
			{
				str1[j]=line[k];
				j++;k++;
				//printf("%c",str[j-1]);
			}
			str1[j]='\0';
			if (strstr(str1, str) != NULL)
        		printf("%s\n",str1);

        i+=1;
    }

    fclose(fp);
}

