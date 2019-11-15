#ifndef Base_h
#define Base_h

#include <string>
using namespace std;

class Base{
public:
    string user_input;
    string firstCommand;
    string secondCommand;
    
    Base() {};
    
    virtual bool run() = 0;
    virtual void print(string firstCommand, string secondCommand)=0;
};

#endif /* Base_h */

