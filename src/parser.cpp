#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
 *  getCommand will return an index of where our logical opeator was found.
 *   It will also make sure we disregard logic operators inside quotes
 *   */
int getCommandIndex(string s){
    int i = 0; // iterator through string
    bool openQ = false; // check if we have an open quote
    
    // iterate through string
    while(i<s.length()){
        // if we have an open quotes check to see if s[i] == ", if so then flip the boolean answer
        if(openQ){
            if(s.at(i) == '"'){
                openQ = !openQ;
            }
        }  
        else
            switch (s.at(i)) { 
                // if s[i] == " , flip the boolean answer
                case '"':
                {
                    openQ = !openQ;
                }
                // if s[i] == &
                case '&':
                {
                    // Make sure it's not inside open quotes, if not then return index i
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
    return s.length();  
}

/*
 *  newString will take in:
 *  begOp: index of the previous operator encountered
 *  opIndex: index of the current operator encountered
 *  s: string of our current command
 *
 *  we will return a string, which will be a command
 *  Ex: ls -a
 */
string newString(int begOp, int opIndex, string s){
    // if begOp == -1 then we don't have a previous operator
    if(begOp == -1){
	// if opIndex < s.length() then there must be more commands in our string
        if(opIndex < s.length()){
	    // get the character of our logic operator using opIndex
	    char letterOrOP = s.at(opIndex);
	    // Check to see if we have two consecutive  & or |. This will tell us if we have a valid logic operator
            // If so, return the string,  beginning to logic index
            if(letterOrOP == '&' && s.at(opIndex+1) == '&')
                return s.substr(0, opIndex);
            else if(letterOrOP == '|' && s.at(opIndex+1) == '|')
                return s.substr(0, opIndex);
            else
		// if no logic operator found return the entire string
                return s.substr(begOp,s.length());
        }
    // if we do have a previous logic operator
    } else {
        if(opIndex < s.length()){
            char letterOrOP = s.at(opIndex);
            if(letterOrOP == '&' && s.at(opIndex+1) == '&')
                return s.substr(begOp, opIndex-begOp);
            else if(letterOrOP == '|' && s.at(opIndex+1) == '|')
                return s.substr(begOp, opIndex-begOp);
            else
                return s.substr(begOp, opIndex-begOp);
        } else if (opIndex == s.length())
            return  s.substr(begOp,s.length());
        
    }
    return s.substr(opIndex,s.length());
}


/*  print will take in:
 *  s1: string of command1 
 *  s2: string of command2
 *
 *  we will print command1 and command2
 */
void print(string s1, string s2){
    // Check if both are empty   
    if(s1 == " " && s2 == " ")
        cout << "Both strings are empty" << endl;
    // Check if s1 and s2 have a string
    else if (s1 != " " && s2 != " "){
        cout << "Command 1: " << s1 << endl;
        cout << "Command 2: " << s2 << endl;
    }
    // Check if s1 has a string and s2 is empty 
    else if(s1 != " " && s2 == " "){
        cout << "Command 1: " << s1 << endl;
        cout << "Command 2: None" << endl;
    }
    // Check if both s1 and s2 are empty 
    else if (s1 == " " && s1 != " "){
        cout << "Command 1: None" << endl;
        cout << "Command 2: " << s2 << endl;
    }
}

int main() {
/*
 *  user_input: string of commands we will parse
 *  connectorLocation: the location of ";" so we can parse that command
 *  getCommands: this will hold our commands after we parse our string
 */

cout << "$ " ;

 string user_input;
getline(cin, user_input);
//string user_input = "ls -a;echo \"hello&&\" && echo hi; echo hello && echo hi && echo teller || echo fine || echo last; ls -m";
    int connectorLocation;
    vector<string> getCommands;
    
    cout << user_input << endl;
    cout << endl;        

    //Make a while loop that breaks commands based on ; and pushes it to command vector
    while(user_input.length() != 0){
    // find the location of ; if present in our string.
    // this will tell us were a new command begins
        connectorLocation = user_input.find(";");

    // if ; found: get the location of ; then parse and push to our vector command.
    // After delete it from our string
        if(user_input.find(";") != std::string::npos){
            connectorLocation = user_input.find(";");
            getCommands.push_back(user_input.substr(0,connectorLocation));
     	    user_input.erase(0,connectorLocation+1);
    // else push the remaining code to our vector of commands then delete from our string
        } else {
            getCommands.push_back(user_input.substr(0,user_input.length()));
            user_input.erase(0,connectorLocation);
        }

    }
  
   // test to make sure we broke down our commands correctly and print
   // Later we will push each vector[i] to the proper class && or || to execute command.
   // if there are more logic operators we will erase what have already compiled and return our next string.
   // We continue doing this until we reach the end of that command line 
    int i =0;
    while(i<getCommands.size()){
        cout << "Command[" << i << "]: ";
        cout << getCommands[i] << std::endl;
        i++;
    } 



    cout << endl;
    
    /*  Our for-loop will iterate through each of our parse commands in getCommands
     *  test: this will hold our current command
     *  
     */
    for(int i = 0; i<getCommands.size(); i++){
    string  test = getCommands[i];
        string holdString = test;
        string firstCommand = " ";
        string secondCommand = " ";
        int currOpIndex = 0;
        int prevOpIndex = -1;
        
        cout << "*******[" << i <<"]*******" << endl;
        cout << "Current Command: " << test << endl;
        
        while(currOpIndex < test.length()){
            currOpIndex += getCommandIndex(holdString);
            
            if(currOpIndex == test.length()){
                if(firstCommand == " "){
                    firstCommand = holdString;
                    print(firstCommand, secondCommand);
                    holdString = " ";
                } else if(secondCommand == " "){
                    secondCommand =  holdString;
                    print(firstCommand, secondCommand);
                }
            }else {
                if(firstCommand == " "){
                    firstCommand =  newString(prevOpIndex, currOpIndex, test);
                    prevOpIndex = currOpIndex+2;
 
                } else if(secondCommand == " "){
                    secondCommand =  newString(prevOpIndex,currOpIndex, test);
                    prevOpIndex = currOpIndex+2;
                } else{
                    firstCommand = test.substr(0,prevOpIndex-2);
                    secondCommand = newString(prevOpIndex, currOpIndex, test);
                    prevOpIndex = currOpIndex+2;
                    
                }
                print(firstCommand, secondCommand);
                cout << endl;
                currOpIndex+=2;
                holdString = test.substr(currOpIndex,test.length());
            }
        }
        if(currOpIndex == test.length()){
            firstCommand = test.substr(0,prevOpIndex-2);
            secondCommand = newString(prevOpIndex, currOpIndex, test);           
        }

    cout << endl;
        
    }
    return 0;
}

