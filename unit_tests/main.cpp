#include <iostream>
#include <string>
#include "Base.h"
#include "Parser.h"

using namespace std;

int main() {
   
    string user_input;
    cout << "$ ";
    getline(cin, user_input);
    
    cout << endl;
    
    Base* p = new Parser(user_input);
    p->run();
	
    return 0;
}
