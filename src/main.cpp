#include <string.h>
#include "../header/Parser.h"
#include <unistd.h>
using namespace std;

int main() {
/*
 *  user_input: string of commands we will parse
 *  connectorLocation: the location of ";" so we can parse that command
 *  getCommands: this will hold our commands after we parse our string
*/
    //Parser p;
    string user_input;
  
    cout << "$ ";
    getline(cin, user_input);
    
    Base *p = new Parser(user_input);
    cout << p->run();    

    return 0;
}













