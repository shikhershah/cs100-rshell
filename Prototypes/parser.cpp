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

    string user_input = "ls -a;echo hello && echo hi && echo teller || echo fine; ls -m";
    int str_len = user_input.length();
    int connectorLocation;
   // int quoteLocation;
    int connectorCounter = 0;

    vector<string> getCommands;
    
    
    cout << user_input << endl;
    cout << endl;        

    //Make a while loop that breaks commands based on ; and pushes it to command vector
    while(str_len != 0){
    // find the location of ; if present in our string.
    // this will tell us were a new command begins
        connectorLocation = user_input.find(";");

    // if ; found: get the location of ; then parse and push to our vector command.
    // After delete it from our string
    if(user_input.find(";") != string::npos){
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
        cout << "Command[" << i << "]: ";
        cout << getCommands[i] << endl;
        i++;
    } 

    cout << endl;
    // this tests our long command, getCommand[1], and counts the number of logic operators
    // This will tell us how many more comparisons we have.
    // If we have more than one concatanate all the comparison on the left of the logic operator 
    // and compare to the right side
    // Repeat until we reach the end of that particular getCommand[] line.
    i =0;
   
    int andCounter = 0;
    int orCounter = 0;
    int total;
    cout << getCommands[i] << endl;
    andCounter = OpOccurence(getCommands[i], "&&");
    orCounter = OpOccurence(getCommands[i], "||");
    total = andCounter + orCounter;

    cout << "And counter: " << andCounter << endl;
    cout << "Or counter: " << orCounter << endl;
    cout << "Total: " << total << endl;
	}




