#include <string.h>
#include "../header/Parser.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

void test(string& user_input) {
size_t test = user_input.find("test");
if(test != string::npos){
    user_input.erase(test,4);
}

size_t brac_open = user_input.find("[");
if(brac_open != string::npos){
    user_input.erase(brac_open,1);

size_t brac_close = user_input.find("]");
if(brac_close != string::npos){
    user_input.erase(brac_close,1);
}
else {
cout << "command invalid";
  }
 }


}

void flags(string& user_input) {

bool flag_e = false;
bool flag_f = false;
bool flag_d = false;

size_t e = user_input.find("-e");
size_t f = user_input.find("-f");
size_t d = user_input.find("-d");

struct stat fg; 


if (e != string::npos) {
user_input.erase(e,2);
flag_e = !flag_e;
//cout << "(" <<flag_e<<")";
 }
else if (f != string::npos) {
user_input.erase(f,2);
flag_f = !flag_f;
//cout << "(" <<flag_f<<")";
 }
else if(d != string::npos) {
user_input.erase(d,2);
flag_d = !flag_d;
//cout << "(" <<flag_d<<")";
 }
else {
flag_e = !flag_e;
//cout << "(" <<flag_e<<")";
 }

if ((flag_e && flag_f) || (flag_e && flag_d) || (flag_f && flag_d) ) {
cout << "too many flags";
}


char * writable = new char[user_input.size() + 1];
std::copy(user_input.begin(), user_input.end(), writable);
writable[user_input.size()] = '\0';



if(flag_e) {
    if(stat(writable,&fg) == 0 ) {
        cout << "(" <<flag_e <<")";
    }
   else {
        cout << "(" << false << ")";
    } 
}
}


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
 size_t comment = user_input.find("#");
     if(comment != string::npos){
        user_input.erase(comment,user_input.size()-1);
  }
 test(user_input);
 flags(user_input);
Base* p =new  Parser (user_input);
	cout <<p->run();  
   
    return 0;
}













