# CS 100 Programming Project
Shikher Shah 862012248 
Carlos Loeza 862154211

Intro: We are building a command shell using c++ that will be able to Print a command prompt, read in a line of command(s) (and connector(s)) from standard input, and execute the appropriate commands using fork(), execvp(), and waitpid()

We will be using the composite design pattern in the development of this project.We will take user input and check to see if it is executable, if it is then, we will check to see if there is a double and or double or. We will then check to see if there is a semicolon.There will be a base class with three subclasses. The first subclass will take in double and. The second subclass will take in double or, and the third subclass will take in the semicolon.  

Diagram: 

Classes:We will have a base class with one subclass. This subclass will have four subclasses. The base will serve as a common interface.Its subclass will be called filter and will separate each command based on semicolon.This will then be pushed to a vector. We will then break down each victor index to see if it has && or ||. If it does, then place in one of following subclasses. The first subclass of filter will be called simple. It will check if the command has either && or ||. If it does not have either then it will put in the simple class. The second class will be called DoubleAnd which will contain all executables that have &&. The third class will be called DoubleOr. This class will contain all executables that contain ||. The third class will be called DoubleAndOR . This class will check if has more than one && or || . Each of these classes will have a run function that processes user input to see if it is executable. If it is executable the function will return true, else it will return false.  

Prototype and Research: create a small prototype using fork(), waitpid(), and execvp() individually and together

Development and Testing roadmap: We will start by developing a composite pattern. 
