# CS 100 Programming Project
Shikher Shah 862012248
Carlos Loeza 862154211

Intro: We are building a command shell using c++ that will be able to print a command prompt, read in a line of command(s) (and connector(s)) from standard input, and execute the appropriate commands using fork(), execvp(), and waitpid().

We will be using the composite design pattern in the development of this project. We will take user input and break it down into individual commands using a filter class that will split user input by semicolons. We will then check to see if each command is executable, if it is then, we will check to see if there is an && or ||. If there is, then we will place the two commands in its relavite class and check it is executable. If it is executable, we will return true or else false will be returned. In order to cover everything there will be a base class with a subclass that will act as a filter. This filter subclass will have three subclasses. The first subclass will simple commands; those without && or ||. The second subclass will take in commands that involve && and the third subclass will take in commands with ||. If a command has more than one && or ||, we count the number of  && and ||. We will then see if the first two commands are executable. If they are, we will put it in a vector called firstcommand. We will put the command after the second logic operator  in another vector called secondcommand and pass it through the second connector to see if it is executable. We will add secondcommand to firstcommand and make the remaining command to  secondcommand until the counter is one.     


Diagram
[Assignment1Diagram](image/Assignmen1.jpg) 
Classes:We will have a base class with one subclass. This subclass will have three subclasses. The base will serve as a common interface.Its subclass will be called filter and will separate each command based on semicolon. This will then be pushed to a vector. We will then break down each victor index to see if it has && or ||. If it does, then place in one of following subclasses. The first subclass of filter will be called simple. It will hold commands that do not have either && or ||. The second class will be called DoubleAnd which will contain all executables that have &&. The third class will be called DoubleOr. This class will contain all executables that contain ||. Each of these classes will have a run function that processes user input to see if it is executable. If it is executable the function will return true, else it will return false. If there is more than one && or || in the command then we will place the remaining in another vector that will check to see if it is executable. Once we are done processing the entire command, we will pop it so we dont process it a second time.  


Prototype and Research: create a small prototype using fork(), waitpid(), and execvp() individually and together


Fork() creates a new process that is a copy of the existing process. execvp() replaces that current process with a completely new process. waitpid() puts a hold on either the parent or child. 


Development and Testing roadmap: We will start by developing the composite pattern. We will start by creating a common interface. After, we will make that filter subclass. In this filter class we  will develop two vectors; firstcommand and secondcommand.  Later, we will develop the simple, DoubleAnd and DoubleOr subclasses. These subclasses will hold strings of the commands. For example, the simple will hold "ls -a". The DoubleAnd will hold "echo world && mkdir Test". The DoubleOr will hold "echo world || mkdir Test".  Once this is done, we will develop a run function that will check to see if each command is executable. In this run function, we will have a counter to see how many && and || there are. If there is more than 1 then we will decrement the count and make the first portion, firstcommand and the command after the second connector secondcommand.  If this does not work, then we will create a strategy to handle the filtering. 
