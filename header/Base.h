#ifndef Base_h
#define Base_h

#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <sys/wait.h> 
#include <iostream> 
#include <vector> 
#include <string>
using namespace std;

class Base{
public:
    string user_input;
    string firstCommand;
    string secondCommand;
    
    Base() {};
    
    virtual bool run() = 0;
    //virtual void dissect() = 0;
    virtual void print(string firstCommand, string secondCommand)=0;
};

#endif /* Base_h */

