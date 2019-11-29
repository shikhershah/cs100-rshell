# CS 100 Programming Project
Shikher Shah 862012248
Carlos Loeza 862154211

Intro: We are building a command shell using c++ that will be able to print a command prompt, read in a line of command(s) (and connector(s)) from standard input, and execute the appropriate commands using fork(), execvp(), and waitpid().

We will be using the composite design pattern in the development of this project. We will take user input and break it down into individual commands using a parser class that will split user input by semicolons. The parser class will then split the commands further if it contains connectors. If the command contains && it wil go to a DoubleAnd class which will check if both commands are executable. However, if the command contains || connectors, it will go to the DoubleOr class which will check if one or the other command is executable. If it is executable, a true will be returned. If neither command is executable, a false will be returned. In order to cover everything there will be a base class that will  act as a common interface.  The first subclass will simple commands; those without && or ||. The second subclass will take in commands that involve && and t in commands with ||. If a command has more than one && or ||, we count the number of  && and ||. We will then see if the first two commands are executable. If they are, we will put it in a vector called firstcommand. We will put the command after the second logic operator  in another vector called secondcommand and pass it through the second connector to see if it is executable. We will append  secondcommand to firstcommand and push the remaining command to the secondcommand vector. This will continue untill there are no more connectors.    
We will have test and precendence functions that will check if files exise and how to execute them based on priority.

Diagram
[Assignment1Diagram](image/Assignmen1.jpg) 
Classes:We will have a base class with four subclasses. The base will serve as a common interface. The first subclass will be a parser that takes in the length of the string and finds the locations of all the connectors. The second subclass will be called DoubleAnd. It will take in commands that have && connectors and see they are executable. The second class will be called DoubleOr which will check if commands connected by || connectors are executable. The third class will be called NonAndNonOr. This class will check if commands that do not have any connectors are executable. Each of these classes will have a run function that processes user input to see if it is executable. If it is executable the function will return true, else it will return false. If there is more than one && or || in the command then we will place the remaining in another vector that will check to see if it is executable. Once we are done processing the entire command, we will pop it so we dont process it a second time.  


Prototype and Research: create a small prototype using fork(), waitpid(), and execvp() individually and together

Fork() creates a new process that is a copy of the existing process. execvp() replaces that current process with a completely new process. waitpid() puts a hold on either the parent or child. 

#include <iostream>
int main() {
const int num_process = 32;   
pid pids[128];

for (int i = 0; i < num_process;i ++) {
   pids[i] = fork();
   if (!pids[i]) {  
       char* cmd = "echo"
	int* argv[i] = i;
	execvp(cmd,argv);

       exit(0);
   }
}

for (int i = 0; i < num_process; i++){
    waitpid(-1, NULL, 0);
}
return 0;
}


Development and Testing roadmap: We will begin by developing a parser formula that will process a list of commnds. We wil then make a base class that will serve as the common interface for the composite pattern. We will use lab 4 as a guide in developing the composite pattern. After, we will make a parser subclass called CheckCommand that uses the parser formula developed earlier.In this parser subclass look at the length of the command and  we will have a counter to see where the && or || connector is  loacted. Then it will check if the is a command after. If there is, the two commands will go to its respective clss.The count and make the first portion, firstcommand and the command after the second connector secondcommand.  Later, we will develop the DoubleAnd, DoubleOr and NonAndNonOr subclasses. The DoubleAnd and DoubleOr subclasses will take two strings: the command before the && or || and the command after. For example, the DoubleAnd will hold echo world in the first string and mkdir Test in string two. The DoubleOr will hold echo world in string 1 and  mkdir Test in string 2.  Once this is done, we will develop a run function that will check to see if each command is executable. In this run function, we will have a counter to see where to && or || is loacted. If this does not work, then we will create a strategy to handle the filtering.After, we will implement a test function that checks to see if files exist and the type of file. We will then implement a precedence function that outputs based on priority. 
