#ifndef SingleCommand_h
#define SingleCommand_h

#include <iostream>
#include <string>
#include "Base.h"

class SingleCommand: public Base{
public:
    SingleCommand(string firstCommand, string secondCommand){
        this->firstCommand = firstCommand;
        this->secondCommand = secondCommand;
    }
    
    virtual bool run(){
        if(!firstCommand.empty()){

	    // test to make sure it works using the forks or execs
	    char * args[3];
	
	
	    int strlen = firstCommand.length();
	    char strchar[strlen+1];
   	    strcpy(strchar, firstCommand.c_str());

	    int i = 0;
    	    char *comm = strtok (strchar, " ");
	    
    	    while (comm != NULL) {
        	args[i++] = comm;
        	comm = strtok (NULL, " ");
    	    }

	    args[2] = NULL;
            
            
            execute(args);

	    return true;

        } else    
            return false;
    }
    

    void execute(char ** args){
        pid_t parent_pid;
	pid_t pid = fork();
        
	

        if(pid < 0){
            cout << "Error: fork() == -1" << endl;
            exit(1);
        }
        else if(pid == 0){
    	    if((strcmp(args[0], "exit") == 0) || (strcmp(args[0], "Exit") == 0)){
        	cout << "Exit";
        	exit(1);
    	    }
	    else if((strcmp(args[0], "exit") == 0) || (strcmp(args[0], "Exit") == 0)){
                cout << "Exit";
                exit(1);
            }
            else if(execvp(args[0], args) ==-1){
                cout << "Error" << endl;
                exit(1);
            }
        }

        else if(parent_pid > 0){
            waitpid(-1, &pid, 0);
            
	}

    }



    virtual void print(string firstCommand, string secondCommand){
        if(firstCommand.empty())
            cout << "Error: Missing firstCommand" << endl;
        else
            cout << "First Command: " << firstCommand << endl;
    }
};


#endif /* SingleCommand_h */
