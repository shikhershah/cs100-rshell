#ifndef OrLogicOp_h
#define OrLogicOp_h

#include <iostream>
#include <string>
#include "Base.h"
using namespace std;


class OrLogicOp: public Base{
public:
    OrLogicOp(string firstCommand, string secondCommand){
        this->firstCommand = firstCommand;
        this->secondCommand = secondCommand;
    }
    
    virtual bool run(){
        if(firstCommand.empty() || secondCommand.empty())
            return false;
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



#endif /* OrLogicOp_h */

