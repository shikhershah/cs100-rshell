#include <iostream>
#include <string>
#include <vector>
// This function will check the number of occurences of our connector and return it.
// Our function will take in 2 variables:
// strCommand: the string that will contain the && and || operators.
// logicOp: the operator we will be looking for.
//
// We will delete the part of the string we have
int OpOccurence(std::string strCommand, std::string logicOp){
    int opCounter = 0;
    int location = 0;
    
    while(strCommand.length() != 0){
        if(strCommand.find(logicOp) != std::string::npos){
            location = strCommand.find(logicOp);
            strCommand.erase(0,location+2);
            opCounter++;
        } else
            strCommand.erase(0,strCommand.length());
    }
    return opCounter;
}


int main() {

    std::string user_input = "ls -a;echo hello && echo hi && echo teller || echo fine; ls -m";
    int str_len = user_input.length();
    int connectorLocation;
    int connectorCounter = 0;
    std::vector<std::string> getCommands;
    
    
    std::cout << user_input << std::endl;
    std::cout << std::endl        

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
    int i =0;
    while(i<getCommands.size()){
        std::cout << "Command[" << i << "]: ";
        std::cout << getCommands[i] << std::endl;
        i++;
    } 

    std::cout << std::endl;
    // this tests or long command, getCommand[1], and counts the number of logic operators 
    i =0;
    int andCounter = 0;
    int orCounter = 0;

    std::cout << getCommands[1] << std::endl;
    andCounter = OpOccurence(getCommands[1], "&&");
    orCounter = OpOccurence(getCommands[1], "||");
    
    std::cout << "And counter: " << andCounter << std::endl;
    std::cout << "Or counter: " << orCounter << std::endl;


