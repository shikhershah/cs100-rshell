#ifndef Pipe_h
#define Pipe_h

#include <iostream>
#include <string>
#include "Base.h"
using namespace std;


class Pipe: public Base{
public:
    Pipe(string firstCommand, string secondCommand){
        this->firstCommand = firstCommand;
        this->secondCommand = secondCommand;
    }
    
    virtual bool run(){

	int pipefd[2];
        int pid; 

	// create the pipes to write and read input
	// pid is for our fork	
	
	pipe(pipefd);
	pid = fork();

	if(!firstCommand.empty() || !secondCommand.empty()){
            
	    // create a char of our commands with NULL at the end
	    char * args[3];
	    char * args1[3];

	    // put args in executable form
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
            
	    // put args1 in executable form
	    int strlen1 = firstCommand.length();
            char strchar1[strlen1+1];
            strcpy(strchar1, secondCommand.c_str());

            i = 0;
            char *comm1 = strtok (strchar1, " ");

            while (comm1 != NULL) {
                args1[i++] = comm1;
                comm1 = strtok (NULL, " ");
            }
            args1[2] = NULL;

	   // check if this is a child
           if(pid ==0){
	 	// first execute the second command, args1
	        dup2(pipefd[0], 0);
	        close(pipefd[1]);
	        execvp(*args1,args1);
	   } else {
		// now execute first command, args
		dup2(pipefd[1], 1);
	 	close(pipefd[0]);
		execvp(*args, args);
	   }

	      // execute the second command if the first passes
	   


	       // *** check if our commands are valid using the forks and stuff method *****	
	       
	    return true;
	}
	return false;
    }

    
    void execute(char ** args, char ** args1){
        pid_t pid = fork();
        int status;
        
        if(pid < 0){
            cout << "Error: fork() == -1" << endl;
            exit(1);
        }
        else if(pid == 0){
            cout << "Child: " << pid << endl;
            if(strcmp(args[0], "exit") == 0 || strcmp(args[0], "Exit") == 0){
                cout << "Exit";
                exit(0);
            }
            else if(strcmp(args[1], "exit") == 0 || strcmp(args[1], "Exit") == 0){
                cout << "Exit";
                exit(0);
            }		
	    else if(execvp(args[0], args) ==-1){
                cout << "Error" << endl;
                exit(1);
            }
        }

        else if(pid > 0){
            waitpid(-1, &pid, 0);
            cout << "Parent: " << pid << endl;
	}

    }

    virtual void print(string firstCommand, string secondCommand){   
        if(firstCommand.empty() && secondCommand.empty())
            cout << "Error: No Commands" << endl;
        else if(firstCommand.empty() && !secondCommand.empty())
            cout << "Error: Missing firstCommand" << endl;
        else if(!firstCommand.empty() && !secondCommand.empty())
            cout << "Error: Missing secondCommand" << endl;
        else
            cout << "First Command: " << firstCommand << " " << "Second Command: " << secondCommand << endl;
    }
};


#endif /* AndLogicOp_h */
