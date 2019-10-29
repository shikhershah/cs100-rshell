# CS 100 Programming Project
Shikher Shah 862012248 
Carlos Loeza 862154211

Intro: We are building a command shell using c++ that will be able to print a command prompt, read in a line of command(s) (and connector(s)) from standard input, and execute the appropriate commands using fork(), execvp(), and waitpid().

We will be using the composite design pattern in the development of this project.We will take user input and break it down into individual commands using a filter class.We will then check to see if each command is executable, if it is then, we will check to see if there is an && or ||. If there is, then we will place the two commands in its relavite class and check it is executable.If it is executable, wewill return true else false will be returned. In order to cover everything there will be a base class with a subclass that will act as a filter. This filter subclass will have three subclasses. The first subclass will simple commands; those without && or ||. The second subclass will take in commands that involve && and the third subclass will take in commands with ||.  

Diagram: 

Classes:We will have a base class with one subclass. This subclass will have three subclasses. The base will serve as a common interface.Its subclass will be called filter and will separate each command based on semicolon. This will then be pushed to a vector. We will then break down each victor index to see if it has && or ||. If it does, then place in one of following subclasses. The first subclass of filter will be called simple. It will hold commands that do not have either && or ||. The second class will be called DoubleAnd which will contain all executables that have &&. The third class will be called DoubleOr. This class will contain all executables that contain ||. Each of these classes will have a run function that processes user input to see if it is executable. If it is executable the function will return true, else it will return false. If there is more than one && or || in the command then we will place the remaining in another vector that will check to see if it is executable.   

Prototype and Research: create a small prototype using fork(), waitpid(), and execvp() individually and together

Development and Testing roadmap: We will start by developing the composite pattern. We will start by creating a common interface. After, we will make that filter subclass. Later, we will develop the simple, DoubleAnd and DoubleOr subclasses.Once this is done, we will develop a run function that will check to see if each command is executable. If this does not work, then we will create a strategy to handle the filtering. 
