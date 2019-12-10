#include <string.h>
#include "../header/Parser.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;



int main() {
/*
 *  user_input: string of commands we will parse
 *  connectorLocation: the location of ";" so we can parse that command
 *  getCommands: this will hold our commands after we parse our string
*/
   // Parser p;
    string user_input;
  
    cout << "$ ";
    getline(cin, user_input);
   // test for # 
   

   // Base *p = new Parser(user_input);
   //     cout << p->run(); 
 /*size_t comment = user_input.find("#");
     if(comment != string::npos){
        user_input.erase(comment,user_input.size()-1);
  }
*/
Base* p =new  Parser (user_input);
	cout <<p->run();  
   
    return 0;
}













