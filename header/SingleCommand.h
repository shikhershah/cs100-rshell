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
        if(firstCommand.empty())
            return false;
	else{
	    // test to make sure it works using the forks or execs
	    char * args[3];
            string one = "ls";
            string two = "-a";
            args[0] = (char*)one.c_str();
            args[1] = (char*)two.c_str();
            args[2] = NULL;
            
            execute(args);

        }   
        return true;
    }
    

    void execute(char ** args){
        pid_t pid = fork();
        int status;

        if(pid < 0){
            cout << "Error: fork() == -1" << endl;
            exit(1);
        }
        if(pid == 0){
            cout << "Child: " << pid << endl;
            if(execvp(args[0], args) ==-1){
                cout << "Error" << endl;
                exit(1);
            }
        }

        if(pid > 0)
            waitpid(-1, &pid, 0);
        cout << "Parent: " << pid << endl;


    }



    virtual void print(string firstCommand, string secondCommand){
        if(firstCommand.empty())
            cout << "Error: Missing firstCommand" << endl;
        else
            cout << "First Command: " << firstCommand << endl;
    }
};


#endif /* SingleCommand_h */
