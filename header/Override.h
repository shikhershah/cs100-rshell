#ifndef Override_h
#define Override_h

#include <fcntl.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "Base.h"
#include <sys/stat.h> 
#include <fstream>
#include <cstring>

#define MSGSIZE 16
using namespace std;


class Override: public Base{
public:
    Override(string firstCommand, string secondCommand){
        this->firstCommand = firstCommand;
        this->secondCommand = secondCommand;
    }
    
    virtual bool run(){
	if(!firstCommand.empty() && !secondCommand.empty()){
	    // <

	    char * args[3];

	    int strlen = firstCommand.length();
            char strchar[strlen+1];
            strcpy(strchar, firstCommand.c_str());

            int i = 0;
            char *comm = strtok (strchar, " ");

            while (comm != NULL) {
                args[i++] = comm;
                comm = strtok (NULL, " ");
            }

            args[2] = NULL;

	    // get rid of leading white spaces so we don't add them to our file name
	    size_t p = secondCommand.find_first_not_of(" \t");
	    secondCommand = secondCommand.erase(0,p);
	    // 
	    int gThan;
	    const char *s = secondCommand.c_str();
	    gThan = open(secondCommand.c_str(), O_WRONLY | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	    
	    dup2(gThan,1);
	    
	    close(gThan);


	    if(strcmp(args[0], "exit") == 0 || strcmp(args[0], "Exit") == 0){
                cout << "Exit";
                exit(0);
            }
            else if(strcmp(args[1], "exit") == 0 || strcmp(args[1], "Exit") == 0){
                cout << "Exit";
                exit(0);
            }
            else if(execvp(args[0], args) ==-1){
                cout << "Error" << endl;
                exit(1);
            }

	
	    //execvp(*args, args);  







	/* 
//           int i = firstCommand.find(">")  
	    // create a char of our commands with NULL at the end
	    char * args[3];
//	     
            
// /star	    int p[2]; 
  
   	    if (pipe(p) < 0){ 
                exit(1); 
 	    }
   	    write(p[1], args[2], MSGSIZE); 
  
    
        // read pipe 
            read(p[0], args, MSGSIZE); 
  //   strar/

	cout << firstCommand << endl; // see what firstCOmmand is;
	     //int opLocation = firstCommand.find(">");
	   // string temp = firstCommand.substr(opLocation+1, firstCommand.length());
	  //  firstCommand = firstCommand.substr(0, opLocation) + temp;    
	//		cout << firstCommand<<endl ;
	    int strlen = firstCommand.length();
            char strchar[strlen+1];
            strcpy(strchar, firstCommand.c_str());

            int i = 0;
            char *comm = strtok (strchar, " ");

            while (comm != NULL) {
                args[i++] = comm;
                comm = strtok (NULL, " ");
            }
	
       	//		args[3] = args[1];                
           args[4] = NULL;  //changed from args[2] = NULL
		//test
		  for (int i = 0; i < 4 ; i++) {
        cout <<i << ":"<< args[i] <<endl;
        }
		 int p[2];

            if (pipe(p) < 0){
                exit(1);
            }
            write(p[1], args[1], MSGSIZE);
	//cout <<args[1];

        // read pipe
            read(p[0], args[3], MSGSIZE);    
	    
	//	cout << args[i];
	   
	   
	    // test: remove cout<<
            execute(args);
	    // execute the second command if the first passes
	   	 
	   

	   // *** check if our commands are valid using the forks and stuff method *****	
		
*/	    
	    return true;
	} else 
	    return false;
    }

    // test: bool?
    bool execute(char ** args){
        pid_t pid = fork();
        int status;
        
        if(pid < 0){
            cout << "Error: fork() == -1" << endl;
            exit(1);
        }
        else if(pid == 0){
            cout << "Child: " << pid << endl;
            if(strcmp(args[0], "exit") == 0 || strcmp(args[0], "Exit") == 0){
                cout << "Exit";
                exit(0);
            }
            else if(strcmp(args[1], "exit") == 0 || strcmp(args[1], "Exit") == 0){
                cout << "Exit";
                exit(0);
            }		
	    else if(execvp(args[0], args) ==-1){
                cout << "Error" << endl;
                exit(1);
            }
        }

        else if(pid > 0){
            waitpid(-1, &pid, 0);
            cout << "Parent: " << pid << endl;
	}		//test
			cout <<secondCommand;
    }

    virtual void print(string firstCommand, string secondCommand){   
        if(firstCommand.empty() && secondCommand.empty())
            cout << "Error: No Commands" << endl;
        else if(firstCommand.empty() && !secondCommand.empty())
            cout << "Error: Missing firstCommand" << endl;
        else if(!firstCommand.empty() && !secondCommand.empty())
            cout << "Error: Missing secondCommand" << endl;
        else
            cout << "First Command: " << firstCommand << " " << "Second Command: " << secondCommand << endl;
    }
};


#endif /* Override_h */
 

