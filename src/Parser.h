#ifndef __PARSER_H__
#define __PARSER_H__

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Parser{
private:
    string s, firstCommand, secondCommand;
    int begOp, opIndex;
public:
   /*
    *  getCommand will return an index of where our logic opeator was found.
    *  It will also make sure we disregard logic operators inside quotes
   */
    int getCommandIndex(string s);


    /*
     *  newString will take in:
     *  begOp: index of the previous operator encountered
     *  opIndex: index of the current operator encountered
     *  s: string of our current command
     *
     *  we will return a string, which will be a command
     *  Ex: ls -a
    */
    string newString(int begOp, int opIndex, string s);

    void print(string firstCommand, string secondCommand);
}; 

#endif

