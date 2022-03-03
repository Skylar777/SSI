#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>
#include "ssi_list.h"

int main(){
	int bail=0;
    
	while (!bail){
        
        char buffer1[80];
        char host[1024];
	    char *user;
        struct passwd *thepassword;
	    thepassword = getpwuid(getuid());
        user=thepassword->pw_name;
        char user2[1024];
        //printf("%s\n",user);
        
        strcpy(user2,user);
        //printf("1\n");
	    gethostname(host, 1024);
        //printf("2\n");
        getcwd(buffer1, sizeof(buffer1));
        //printf("%s,%s,%s,\n", user,host,buffer1);
	    const char* prompt=strcat(strcat(strcat(user,"@"),strcat(host,": ")),strcat(buffer1," > "));
		char* reply = readline(prompt);
        char* buffedam="a";
        pid_t pid;
        //printf("%s\n",reply);
        if(strcmp(reply,"")==0){
            continue;
        }
		if(strcmp(reply, "exit")==0){
			bail = 1;
		} else {
            char replycp2[3];
            char replycp4[0];
            strcpy(replycp2,reply);
            replycp2[2]='\0';
            if(strcmp(reply,"bglist")==0){
                replycp2[0]='\0';
                buffedam="b";
            }
            if(strcmp(replycp2,"bg")==0){
                char replycp3[strlen(reply)];
                strcpy(replycp3,reply);
                buffedam = strtok(replycp3, " ");
                
                int i=0;
                int c=strlen(buffedam)+1;
                replycp4[strlen(reply)];
                //printf("%s\n",(reply));
                
                while (c < strlen(reply)){
                    replycp4[i]=reply[c];
                    //printf("%c\n",reply[c]);
                    i++;
                    c++;
                }
                replycp4[i]='\0';
                //printf("%s,%s,%d\n",buffedam,replycp4,pid);
                strcpy(reply,replycp4);
                if(strlen(reply)==0){
                    strcpy(reply, "lss");
                    buffedam="a";
                }
                

                // if(pid == 0){
                //     if(execvp(argv[0], argv) < 0){
                //         perror("Error on execvp");
                //     }
                //     exit(EXIT_SUCCESS);}
                // else if(pid > 0) {
                //     // store information of the background child process in the linked list 
                //     insertEnd(pid, file);
                // }
                // else {
                //     perror("fork failed");
                //     exit(EXIT_FAILURE);
                // }
            }
            
            strcpy(replycp2,reply);
            replycp2[2]='\0';
            char ** tokedarray=0;
            //printf("%s\n",getenv("HOME"));
            replycp4[strlen(reply)];


            
            if(strcmp(replycp2,"cd")==0){
                int c=3;
                int i=0;
                replycp4[strlen(reply)];
                //printf("%ld\n",strlen(reply));
                
                while (c < strlen(reply)){
                    replycp4[i]=reply[c];
                    //printf("%c\n",reply[c]);
                    i++;
                    c++;
                }
                replycp4[i]='\0';
                if(strcmp(replycp4,"~")==0){
                    strcpy(replycp4,getenv("HOME"));
                }
                //printf("k %s\n", replycp4);
                chdir(replycp4);
                //printf("k %s\n", reply);
            }else{
            //printf("%s\n",reply);
                char* location=0;
                size_t count=0;
                //printf("%s\n",reply);
                char* tempreply=reply;
                char splitter[2];
                splitter[0]=' ';
                splitter[1]=0;
                while (*tempreply){
                    if (' '==*tempreply){
                        count++;
                        location=tempreply;
                    }
                    tempreply++;
                }
                count+=location<(reply+strlen(reply)-1);
                count++;
                tokedarray=malloc(sizeof(char*)*count);
                if (tokedarray){
                    size_t indexspot=0;
                    char* temptok=strtok(reply,splitter);
                    while(temptok){
                        assert(indexspot<count);
                        *(tokedarray+indexspot++)=strdup(temptok);
                        temptok=strtok(0,splitter);
                    }
                    
                    
                    assert(indexspot==count-1);
                    
                    *(tokedarray+indexspot)=0;  
                }
            }
            
            pid=fork();
            if(pid){
                
                int status;
                pid_t checker=-1;
                if(strcmp(buffedam,"a")==0||strcmp(buffedam,"b")==0){
                    checker=waitpid(pid, &status, 0);
                    
                }else{
                    
                    checker=waitpid(pid, &status, 1);
                    
                    
                }
                
                    
                    
                
            }else{
                
                pid_t status;
                //printf("%s\n",buffedam);
                if(strcmp(buffedam,"a")!=0 && strcmp(buffedam,"b")!=0){
                    //printf("insert\n");
                    insertEnd(pid, reply);
                    //printList();
                }
                if(strcmp(buffedam,"b")==0){
                    printList();
                    exit(1);
                }
                execvp(tokedarray[0], tokedarray);
                printf("Not a valid command\n");
                exit(1);
                
            }
            
        }
		free(reply);
	}	
}