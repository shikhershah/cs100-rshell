#ifndef Parser_h
#define Parser_h

#include <iostream>
#include <string>
#include <vector>
#include "Base.h"
#include "AndLogicOp.h"
#include "OrLogicOp.h"
using namespace std;


class Parser: public Base{
private:
    int connectorLocation;
    string holdString;
    string test;
    string command;
    
public:
    int currOpIndex = 0;
    int prevOpIndex = -1;
    string firstCommand, secondCommand;
    vector<string> commands;
    
    // constructor
    Parser(string s) {
        this->user_input = s;
    }
    
    // Make sure we can execute run() successfully
    virtual bool run(){
	// returns our result
	bool execute = false;

	// comm: hold a vector<string> of our commands
        vector<string> comm = getAllCommands();
	int i = 0;
        while(i<comm.size()){
            cout << "Command[" << i << "]: ";
            cout << comm[i] << endl;
            i++;
        }
        cout << endl;
	// breakdown each command and send to our logic operator
	dissect();
	
	execute = true;
	return execute;
     }


    vector<string> getAllCommands(){
        // Make a while loop that breaks commands based on ; and pushes it to command vector
        while(user_input.length() != 0){
             // find the location of ; if present in our string.
             // this will tell us were a new command begins
            connectorLocation = user_input.find(";");
            // if ";" found: get the location of ";" then parse and push to our vector command.
            // After delete it from our string
            if(user_input.find(";") != -1){
                connectorLocation = user_input.find(";");
                commands.push_back(user_input.substr(0,connectorLocation));
                user_input.erase(0,connectorLocation+1);
                //  else push the remaining code to our vector of commands then delete from our string
            } else {
                commands.push_back(user_input.substr(0,user_input.length()));
                user_input.erase(0,connectorLocation);
            }
        }
        return commands;
    }


    int getCommandIndex() {
        int i = 0;  // iterator through string
        bool openQ = false;  // check if we have an open quote
        
      	//  iterate through string
       	while(i<holdString.length()){
            // if we have an open quotes check to see if s[i] == ", if so then flip the boolean answer
      	    if(openQ){
                if(holdString.at(i) == '"'){
              	    openQ = !openQ;
	        }
             }
             else
                 switch (holdString.at(i)) {
                     //if s[i] == " , flip the boolean answer
                     case '"':
                     {
                         openQ = !openQ;
                     }
                     // ifs[i] == &
                     case '&':
                     { 
                         //  Make sure it's not inside open quotes, if not then return index i
                         if(!openQ)
                             return i;
                         break;
                     } 
                     // if s[i] == |
                     case '|':
                     {
                         // Make sure it's not inside open quotes, if not then return index i
                         if(!openQ)
                             return i;
                         break;
                     }
                 }  
             i++;
        }
        // return the entire lenght if not logic operator found
        return holdString.length();
    }


    // newString will return a string which will be our first or second command. 
    // We will find this by locating a logic operator 
    string newString(){
        //  Find which operator it is and return the new string after removing operators, or if none found then return back s
        string s = test;
	// prevOpIndex: tells us if we have an encounted a logic operator and the index. if it equals -1, then we haven't encountered one
        if(prevOpIndex == -1){
   	    // 
            if(currOpIndex < s.length()){
                char letterOrOP = s.at(currOpIndex);
                if(letterOrOP == '&' && s.at(currOpIndex+1) == '&')
                    return s.substr(0, currOpIndex);
                else if(letterOrOP == '|' && s.at(currOpIndex+1) == '|')
                    return s.substr(0, currOpIndex);
                else
                    return s.substr(prevOpIndex,s.length());
            }
        } else {
            if(currOpIndex < s.length()){
                char letterOrOP = s.at(currOpIndex);
                if(letterOrOP == '&' && s.at(currOpIndex+1) == '&')
                    return s.substr(prevOpIndex, currOpIndex-prevOpIndex);
                else if(letterOrOP == '|' && s.at(currOpIndex+1) == '|')
                    return s.substr(prevOpIndex, currOpIndex-prevOpIndex);
                else
                    return s.substr(prevOpIndex, currOpIndex-prevOpIndex);
            } else if(currOpIndex == s.length())
                return  s.substr(prevOpIndex,s.length());
            
        }
        return s.substr(prevOpIndex,s.length());
    }



    virtual void dissect(){
        for(int i=0;i<commands.size(); i++){
            test = commands[i];
            holdString = test;
            string firstCommand = "";
            string secondCommand = "";
            currOpIndex = 0;
            prevOpIndex = -1;
            
            // test: this tell use our current commands[i]
            //cout << "*******[" << i <<"]*******" << endl;
            //cout << "Current Command: " << test << endl;
            
         
            while(currOpIndex < test.length()){
                currOpIndex += getCommandIndex();
                
                if(currOpIndex == test.length()){
                    if(firstCommand == ""){
                        firstCommand = holdString;
                    } else if(secondCommand == ""){
                        secondCommand =  holdString;
                    } else
                        firstCommand = test.substr(0,prevOpIndex-2);
                        secondCommand = newString();
                }else {
                    if(firstCommand == ""){
                        firstCommand =  newString();
                    } else if(secondCommand == ""){
                        secondCommand =  newString();
                    } else{
                        firstCommand = test.substr(0,prevOpIndex-2);
                        secondCommand = newString();
                    }
                    currOpIndex+=2;
                    prevOpIndex = currOpIndex;
                    holdString = test.substr(currOpIndex,test.length());
                }
                
               
		if(test.at(prevOpIndex-2) == '&' && !secondCommand.empty()){
                    AndLogicOp A(firstCommand,secondCommand);
                    A.run();
                } else if(test.at(prevOpIndex-2) == '|' && !secondCommand.empty()){
                    OrLogicOp O(firstCommand,secondCommand);
                    O.run();
                }
            // test: this will print our current commands
            // print(firstCommand, secondCommand);
            
            }
	    cout << endl;
        }
    }



    virtual void print(string firstCommand, string secondCommand){

        if(firstCommand == " " && secondCommand == " ")
            cout << "Both strings are empty" << endl;
        else if(firstCommand != " " && secondCommand == ""){
            cout << "Command 1: " << firstCommand << endl;
            cout << "Command 2: None" << endl;
        }
        else if (firstCommand == " " && secondCommand != " "){
            cout << "Command 1: None" << endl;
            cout << "Command 2: " << secondCommand << endl;
        }
        else if (firstCommand != " " && secondCommand != " "){
            cout << "Command 1: " << firstCommand << endl;
            cout << "Command 2: " << secondCommand << endl;
        }
    }
    
};
#endif /* Parser_h */

























































