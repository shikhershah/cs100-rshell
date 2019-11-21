#include "Parser.h"
using namespace std;

 
int Parser::getCommandIndex(string s){
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
		case '#':
		{
			//Make sure if # the ignore 
			if(!openQ)
			       return -1;
			break;
		} 
            }
        i++;
    }
    // return the entire lenght if not logic operator found
    return s.length();  
}



string Parser::newString(int begOp, int opIndex, string s){
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
void Parser::print(string s1, string s2){
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

