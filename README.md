# mathematical-methods-for-finding-roots-of-polynomial-bisection-newton-ralphson-regula-falsi-secant-m
Write a menu driven program in C  to implement & compare following methods for finding real root of a given polynomial expression on X.
Bisection Method.
Newton-Ralphson Method.
Regula Falsi Method.
Secant Method.

The menu must be as follows:
1. Set expression
2. Set Tolerance
3. Compute
4. Exit
Explanation of the menu:
In the Set Expression section,user must be able to provide the polynomial expression on which all the four methods will be executed.
In the Set Tolerance  section,user must be able to provide the tolerance for the accuracy of the results.
In the 	Compute section all the four methids will be computed on the given expression as per given tolerance.Output must be shown through five different tabular formats follows.

Table 1:
 Heading -Result of Bisection Method
columns-
Itr: Iteration Number
X0&X1: Two initial guess
Mid: The value after bisection
f(X0),f(X1)&f(Mid)
Error                            

Table 2:
 Heading -Result of Newton-Ralphson Method
columns-
Itr: Iteration Number
X0: Initial guess
X1: Calculated approximate root.
f(X0),f(X1)
Error                            

Table 3:
 Heading -Result of Rgula-Falsi Method
columns-
Itr: Iteration Number
X0&X1: Two initial guess
X2: Calculated approximate root.
f(X0),f(X1)&f(X2)
Error       

Table 4:
 Heading -Result of Secant Method
columns-
Itr: Iteration Number
X0&X1: Two initial guess
X2: Calculated approximate root.
f(X0),f(X1)&f(X2)
Error       

Table 5:
 Heading -Comparisions
columns-
Method
Number of Iterations


In the program ,the user must be enabled to compute thew root of a given exprerssion for different tolerance without required to compile & run again and agian .

None of the four functions should hold any instructionrelated to input /output from the user.Store the result whenever required so that it can be displayed after returning from the function.
