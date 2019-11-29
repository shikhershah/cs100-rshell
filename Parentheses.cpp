#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

int main() {
    // Stack will hold the portion our string we will save for later
    // Ex: (ls -a(.... -> ls -a will be saved until we reach the closing parentheses
    stack<string> leftStack;
    stack<string> rightStack;
    // prevOp will hold the last type of parentheses we encountered
    string prevOp = "";
    // This will be our test string for now
    string s = "(echo tester(echo middle echo third))";
    // temp will hold our current string 
    string temp = "";
    // this will hold a vector of our commands in order of precedence
    vector<string> commands;
   
    cout << s << endl;
 
    // Loop through our string until checking each character looking for '(' and ')' to determine 
    // what our parentheses contain and order of precedence
    for(int i =0; i<s.length(); i++){
        // if we find an open paren, check if we have encountered another one and save it as the prevOp
        if(s[i] == '('){
            if(prevOp == ""){
                prevOp = s[i];
            }
	    // Check if we have two parentheses in a row, then push the word clear to our leftStack. The string "Clear
	    // will work as a placeholder to let us know we pushed a blank space. I will cover more on this later. 
            else if(s[i] == '(' && s[i-1] == '('){
		prevOp = s[i];
                leftStack.push("Clear");
                temp = "";
	    // If not two in a row, then we must have something like (ls -a(echo hello)). We will push ls -a to our leftStack
 	    // and save it for later. 
            }else if(s[i] == '('){
		prevOp = s[i];
                cout << "LeftStack: " << temp << endl;
                leftStack.push(temp);
                temp = "";
            // else we have ')('. Nothing really happens so we just save '(' as our prevOp     
            }else{
                prevOp = s[i];
		temp = "";
 	    }
        }
        
        // if we encounter a ')'   
        else if(s[i] == ')'){
            if(prevOp == ""){
                cout << "Error: no left paren";
                return 0;
            }
            else if(prevOp == "("){
                prevOp = s[i];
                cout << "New Command: " << temp << endl;
                commands.push_back(temp);
                temp = "";
            }else if(s[i] == ')' && s[i-1] == ')') {
                rightStack.push("Clear");
		// if our leftStack is not empty then we push the command we passed earlier
		// ex: (--push this--(-----))
                if(!leftStack.empty()){
                    commands.push_back(leftStack.top());
                    leftStack.pop();
		    prevOp = s[i];
		}else{
		    prevOp = s[i];
                    rightStack.push("Clear");
                }
	    }else if(s[i] == ')'){
		    prevOp = s[i];
                    rightStack.push(temp);
            } else{
                temp += s[i];
            }   
        }else
            temp += s[i];       
    }
    
 
    
    // This will check we have any commands left in our stacks that we need to finish pushing 
    // to our command vector
    // Run while our stacks are not empty
    while(!leftStack.empty() || !rightStack.empty()){
	// if leftStack not empty and rightStack is, then make sure we don't push "Clear" to our stack
        if(!leftStack.empty() && rightStack.empty()){
            if(leftStack.top() == "Clear")
                leftStack.pop();
            else{
                commands.push_back(leftStack.top());
                leftStack.pop();
            }
	// if leftStack empty and rightStack is not, then make sure we don't push "Clear" to our stack
        } else if(leftStack.empty() && !rightStack.empty()){
            if(rightStack.top() == "Clear")
                rightStack.pop();
            else{
                commands.push_back(rightStack.top());
                rightStack.pop();
            }
        // else both of our stacks are not empty
        } else{
	    // if both our stack tops hold "Clear" then pop both
            if(leftStack.top() == "Clear" && rightStack.top() == "Clear"){
                leftStack.pop();
                rightStack.pop();
	    // if our leftStack.top holds clear and rightStack doesn't, then pop left and push right to our vector command
            }else if(leftStack.top() == "Clear" && rightStack.top() != "Clear"){
                temp = rightStack.top();
                commands.push_back(temp);
                leftStack.pop();
                rightStack.pop();
	    //  if our leftStack.top does not hold "Clear" and rightStack does, then push left to our command vector and pop rightStack
            } else if(leftStack.top() != "Clear" && rightStack.top() == "Clear"){
                temp = leftStack.top();
                commands.push_back(temp);
                leftStack.pop();
                rightStack.pop();
	    // else both stacks do not contain "Clear"
	    // Ex: (--leftStack--(...)--rightStack--)
            } else{
                temp = leftStack.top() + rightStack.top();
                commands.push_back(temp);
                leftStack.pop();
                rightStack.pop();
                
            }
        }
    }
    
    // Print out our commands in order of precedence
    vector<string>::iterator i;
    for(i = commands.begin(); i != commands.end(); i++){
        cout << *i << endl;   
    }
    
        
    return 0;
}

   
