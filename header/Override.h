#ifndef Override_h
#define Override_h

#include <stdio.h>
#include <iostream>
#include <string>
#include "Base.h"
using namespace std;


class Override: public Base{
public:
    Override(string firstCommand, string secondCommand){
        this->firstCommand = firstCommand;
        this->secondCommand = secondCommand;
    }
    
    virtual bool run(){
	if(!firstCommand.empty() || !secondCommand.empty())
            
	    // create a char of our commands with NULL at the end
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

            

//           if (pipe(args) < 0  ){
//		  exit(1);
//        	} 
//             write(args[1],strchar, strlen);
//             read(args[0], comm, strlen);



	    // test: remove cout<<
            cout << execute(args);
	    // execute the second command if the first passes
	   	 
	   // write(args[0], 
	    // write(args[1], comm, strlen);
        /* read pipe */
       	    // read(p[0], strchar, strlen); 
            // printf("% s\n", inbuf); 
     

	   // *** check if our commands are valid using the forks and stuff method *****	
		
	 if (pipe(args) < 0  ){
                  exit(1);
                } 
             write(args[1], comm, strlen);
             read(args[0], strchar, strlen);

	    
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
	}

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
 

