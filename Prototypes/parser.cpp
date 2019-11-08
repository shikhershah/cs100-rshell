#include <iostream>
#include <string>
#include <vector>
using namespace std;
// This function will check the number of occurences of our connector and return it.
// Our function will take in 2 variables:
// strCommand: the string that will contain the && and || operators.
// logicOp: the operator we will be looking for.
//
// We will delete the part of the string we have
int OpOccurence(string strCommand, string logicOp){
    int opCounter = 0;
    int location = 0;
    
    while(strCommand.length() != 0){
        if(strCommand.find(logicOp) != -1){
            location = strCommand.find(logicOp);
            strCommand.erase(0,location+2);
            opCounter++;
        } else
            strCommand.erase(0,strCommand.length());
    }
    return opCounter;
}


/*
 getCommand will return an index of where our logical opeator was found.
 It will also make sure we disregard logic operators inside quotes
*/
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



int main() {

    string user_input = "ls -a;echo \"hello&&\" && echo hi; echo hello && echo hi && echo teller || echo fine || echo last; ls -m";
    int str_len = user_input.length();
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
    // else push the remaining code to our vector of commands then delete from our string

    } else {
        getCommands.push_back(user_input.substr(0,user_input.length()));
        user_input.erase(0,connectorLocation);
        user_input.erase(0,1);
      }
    }
    // test to make sure we broke down our commands correctly and print
    // Later we will push each vector[i] to the proper class && or || to execute command.
    // if there are more logic operators we will erase what have already compiled and return our next string.
    // We continue doing this until we reach the end of that command line
    int i =0;
    while(i<getCommands.size()){
        std::cout << "Command[" << i << "]: ";
        std::cout << getCommands[i] << std::endl;
        i++;
    } 

    std::cout << std::endl;
    // this tests our long command, getCommand[1], and counts the number of logic operators
    // This will tell us how many more comparisons we have.
    // If we have more than one concatanate all the comparison on the left of the logic operator 
    // and compare to the right side
    // Repeat until we reach the end of that particular getCommand[] line.
    cout << endl;

    //  **** BRUTE FORCE TEST CASE: getCommands[1] *****
    string test = getCommands[1];
    
    int indexVal = getCommandIndex(test);
    
    cout << "Command1: " << test.substr(0,indexVal) << endl;
    test = test.substr(indexVal+2, test.length());
    
    indexVal = getCommandIndex(test);
    cout << "Command2: " << test.substr(0,indexVal) << endl;




