#ifndef _Parser_h
#define _Parser_h

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "Base.h"
#include "AndLogicOp.h"
#include "OrLogicOp.h"
#include "SingleCommand.h"
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
	if (user_input == "") {
     	    return false;
	}
        
	// comm: hold a vector<string> of our commands
        vector<string> comm = getAllCommands(user_input);
	int i = 0;
        while(i<comm.size()){
            cout << "Command[" << i << "]: ";
            cout << comm[i] << endl;
            i++;
        }
        cout << endl;
	
	//size_t execute_And = user_input.find("&");
	
	// breakdown each command and send to our logic operator
	size_t execute_test = user_input.find("test");
	size_t execute_brac = user_input.find("[");
        if(execute_test != string::npos) {
            test_ex(user_input);
         }
        else if(execute_brac != string::npos) {
            test_ex(user_input);
         }      	
	else {
            dissect();
	}
	execute = true;
	return execute;
     }


    vector<string> getAllCommands(string user_input){
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


    int getCommandIndex(string test) {
        int i = 0;  // iterator through string
        bool openQ = false;  // check if we have an open quote
        
      	//  iterate through string
       	while(i<test.length()){
            // if we have an open quotes check to see if s[i] == ", if so then flip the boolean answer
      	    if(openQ){
                if(test.at(i) == '"'){
              	    openQ = !openQ;
	        }
             }
             else
                 switch (test.at(i)) {
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
		     case '#':
		     {
		         if(!openQ)
			     return i;
			 break;	
		     }
                 }  
             i++;
        }
        // return the entire lenght if not logic operator found
        return test.length();
    }


    // newString will return a string which will be our first or second command. 
    // We will find this by locating a logic operator 
    string newString(int prevOpIndex, int currOpIndex, string test){
        //  Find which operator it is and return the new string after removing operators, or if none found then return back string test length
	// prevOpIndex: tells us if we have an encounted a logic operator and the index. if it equals -1, then we haven't encountered one
        if(prevOpIndex == -1){
   	    // Look for logic op, if none found return string 
            if(currOpIndex < test.length()){ 
                char letterOrOP = test.at(currOpIndex);
                if(letterOrOP == '&' && test.at(currOpIndex+1) == '&')
                    return test.substr(0, currOpIndex);
                else if(letterOrOP == '|' && test.at(currOpIndex+1) == '|')
                    return test.substr(0, currOpIndex);
		else if (test.at(currOpIndex)  == '#'    )
		    return test.substr(0,currOpIndex);
                else
                    return test.substr(prevOpIndex,test.length());
            }
	// if we have a previous logic op, find out if our next command
	// is in the middle or end of our string
        } else {
            if(currOpIndex < test.length()){
                char letterOrOP = test.at(currOpIndex);
                if(letterOrOP == '&' && test.at(currOpIndex+1) == '&')
                    return test.substr(prevOpIndex, currOpIndex-prevOpIndex);
                else if(letterOrOP == '|' && test.at(currOpIndex+1) == '|')
                    return test.substr(prevOpIndex, currOpIndex-prevOpIndex);
                else
                    return test.substr(prevOpIndex, currOpIndex-prevOpIndex);
            } else if(currOpIndex == test.length())
                return  test.substr(prevOpIndex,test.length());
            
        }
        return test.substr(prevOpIndex,test.length());
    }


    // dissect() will iterate through our vector that contains strings of our commands
    // 
    virtual void dissect(){
	// reset our variables after iteration to avoid carrying over results from a previous iteration
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
            
            // while loop will cycle through string to find first and secondCommand.
            while(currOpIndex < test.length()){
		// get the index location of the next logic operator so we can get the substring to make 
		// firstCommand or secondCommand
                currOpIndex += getCommandIndex(test);
                // If no logic op is found
                // place in firstCommand, secondCommand, or concatenate commands 
                if(currOpIndex == test.length()){
                    if(firstCommand == ""){
                        firstCommand = holdString;
                    } else if(secondCommand == ""){
                        secondCommand =  holdString;
                    } else{
                        firstCommand = test.substr(0,prevOpIndex-2);
                        secondCommand = newString(prevOpIndex, currOpIndex, test);
			}
		// if logic op is found
                }else {
                    if(firstCommand == ""){
                        firstCommand =  newString(prevOpIndex, currOpIndex, test);
                    } else if(secondCommand == ""){
                        secondCommand =  newString(prevOpIndex, currOpIndex, test);
                    } else{
                        firstCommand = test.substr(0,prevOpIndex-2);
                        secondCommand = newString(prevOpIndex, currOpIndex, test);
                    }
		    // increment currOpIndex by 2, to take into account && or ||
		    // prevOpIndex gets our currOpIndex since it can be a previous op in the next iteration
		    // holdString will get the new substring of test which is the part of the string we havent reached
                    currOpIndex+=2;
                    prevOpIndex = currOpIndex;
                    holdString = test.substr(currOpIndex,test.length());
                }
                // if we only have one command in our string, call SingleCommand to check if it will execute
          //      fork();
              /*   char** args;
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
*/
		if(secondCommand.empty() && currOpIndex == test.length()){
                    SingleCommand S(firstCommand, secondCommand);
                    S.run();
                }               
		// if we have 2 commands along with && then pass the AndLogic class both commands to check if it will execute 
		else if(test.at(prevOpIndex-2) == '&' && !secondCommand.empty()){
                    AndLogicOp A(firstCommand,secondCommand);
                    A.run();
		// else if we have 2 commands along with ||, then pass OrLogicOp class both commands to check if it will execute
                } else if(test.at(prevOpIndex-2) == '|' && !secondCommand.empty()){
                    OrLogicOp O(firstCommand,secondCommand);
                    O.run();
                }
	//	wait(11);		
            // test: this will print our current commands
            // print(firstCommand, secondCommand);
            
            }
	    
        }
    }

void test_ex(string& user_input) {
	string a = "test";
    size_t test = user_input.find("test");
    if(test != string::npos){
        user_input.erase(test,a.size());
    }

    size_t brac_open = user_input.find("[");
    if(brac_open != string::npos){
        user_input.erase(brac_open,1);

    size_t brac_close = user_input.find("]");
    if(brac_close != string::npos){
        user_input.erase(brac_close,1);
    }
    else {
      cout << "command invalid";
      }
    }
flags(user_input);
}

void flags(string& user_input) {

bool flag_e = false;
bool flag_f = false;
bool flag_d = false;

size_t e = user_input.find("-e");
size_t f = user_input.find("-f");
size_t d = user_input.find("-d");

struct stat flg;


if (e != string::npos) {
user_input.erase(e,2);
flag_e = !flag_e;
//cout << "(" <<flag_e<<")";
 }
else if (f != string::npos) {
user_input.erase(f,2);
flag_f = !flag_f;
//cout << "(" <<flag_f<<")";
 }
else if(d != string::npos) {
user_input.erase(d,2);
flag_d = !flag_d;
//cout << "(" <<flag_d<<")";
 }
else {
flag_e = !flag_e;
//cout << "(" <<flag_e<<")";
 }

if ((flag_e && flag_f) || (flag_e && flag_d) || (flag_f && flag_d) ) {
cout << "too many flags";
}


char * writable = new char[user_input.size() + 1];
std::copy(user_input.begin(), user_input.end(), writable);
writable[user_input.size()] = '\0';



if(flag_e) {
    if(stat(writable,&flg) == 0 ) {
        cout << "(TRUE)" ;
        }
    else {
        cout << "(False)" ;
    }
}
else if (flag_f) {
    if(stat(writable,&flg) == 0 && S_ISREG(flg.st_mode)) {
        cout << "(" <<flag_f << ")" ;
        }
    else {
        cout << "(False)" ;
        }
    }
else if (flag_d) {
    if(stat(writable, & flg) == 0 && S_ISDIR(flg.st_mode)){
        cout << "(" <<flag_d << ")" ;
        }
    else {
        cout << "(False)" ;
        }
    }
}




    // void print() will print out the status of first and secondCommand
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


















//size_t comment = user_input.find("#");
   // if(comment != string::npos){
   //       user_input.erase(comment,user_input.size()-1);
   // }







































