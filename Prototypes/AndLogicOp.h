#ifndef AndLogicOp_h
#define AndLogicOp_h

#include <iostream>
#include <string>
#include "Base.h"
using namespace std;


class AndLogicOp: public Base{
public:
    AndLogicOp(string firstCommand, string secondCommand){
        this->firstCommand = firstCommand;
        this->secondCommand = secondCommand;
    }
    
    virtual bool run(){
	if(firstCommand.empty() || secondCommand.empty())
            return false;
        else{
	    // *** check if our commands are valid using the forks and stuff method *****
 	
	}
	return true;
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

