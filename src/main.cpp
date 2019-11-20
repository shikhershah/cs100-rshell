#include <string.h>
#include "Parser.h"
using namespace std;

int main() {
/*
 *  user_input: string of commands we will parse
 *  connectorLocation: the location of ";" so we can parse that command
 *  getCommands: this will hold our commands after we parse our string
*/
    Parser p;
    string user_input;
    int connectorLocation;
    vector<string> getCommands;
   

    cout << "$ ";
    getline(cin, user_input);

    cout << user_input << endl;
    cout << endl;


     // Make a while loop that breaks commands based on ; and pushes it to command vector
     // Find the location of ; if present in our string.
     // This will tell us where a new command begins.
     
     while(user_input.length() != 0){
	 connectorLocation = user_input.find(";");

	 // if ; found: get the location of ; then parse and push to our vector command.
	 // Then, delete it from our string
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
    //  We continue doing this until we reach the end of that command line 
    for(int i=0;i<getCommands.size(); i++){
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
            currOpIndex += p.getCommandIndex(holdString);

            if(currOpIndex == test.length()){
                if(firstCommand == " "){
                    firstCommand = holdString;
                    p.print(firstCommand, secondCommand);
                    holdString = " ";
                } else if(secondCommand == " "){
                    secondCommand =  holdString;
                    p.print(firstCommand, secondCommand);
                }
            }else {
                if(firstCommand == " "){
                    firstCommand =  p.newString(prevOpIndex, currOpIndex, test);
                    prevOpIndex = currOpIndex+2;

                } else if(secondCommand == " "){
                    secondCommand =  p.newString(prevOpIndex,currOpIndex, test);
                    prevOpIndex = currOpIndex+2;
                } else{
                    firstCommand = test.substr(0,prevOpIndex-2);
                    secondCommand = p.newString(prevOpIndex, currOpIndex, test);
                    prevOpIndex = currOpIndex+2;

                }
                p.print(firstCommand, secondCommand);
                cout << endl;
                currOpIndex+=2;
                holdString = test.substr(currOpIndex,test.length());
            }
        }

	if(currOpIndex == test.length()){
            firstCommand = test.substr(0,prevOpIndex-2);
            secondCommand = p.newString(prevOpIndex, currOpIndex, test);
        }

    cout << endl;

    }
    return 0;
}













