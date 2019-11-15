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
	else
	    // test to make sure it works using the forks or execs
        return true;
    }
    
    virtual void print(string firstCommand, string secondCommand){
        if(firstCommand.empty())
            cout << "Error: Missing firstCommand" << endl;
        else
            cout << "First Command: " << firstCommand << endl;
    }
};


#endif /* SingleCommand_h */
