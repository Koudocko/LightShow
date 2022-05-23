# LightShow - A simple Arduino library for managing LEDs

## Overview
A simple library designed to help you manage the execution flow of your LEDs. 
It is a state based library, with simulated non-blocking execution. 
States can be as complex as using numerous operations while relying on a changing lvalue state. 

## Usage
To get started, create a new LightShow object with no constructor params. 
Next, use the push(pin, length, expr, mode) to add a new instruction to be executed. 
The pin is the pin number of the LED. 
The length is the length the pin will run in milliseconds. 
The expression is an expression object (more on that later), essentially the deciding condition whether it should execute. 
The mode tells the program whether you want to run analog or digital mode, ANALOG and DIGITAL macros defined. 

Now in some loop statement or in your arduino loop entry point, call the refresh() method. 
This will update the state of the light. 

## Expressions
To allow the usage of complex states involving prvalues, a wrapper class called Expr must be used. 
A complex state is any expression involving a state which returns a prvalue, e.g. the opposite of a global variable !varGlobal. 
Expressions are passed to the push() method of LightShow, thus you must know how to create an expression. 
There are several static methods from the Expr which you must use to create a complex expression: 
addF(ExprA, ExprB); 
subF(ExprA, ExprB); 
mulF(ExprA, ExprB); 
divF(ExprA, ExprB); 
modF(ExprA, ExprB); 
andF(ExprA, ExprB); 
orF(ExprA, ExprB); 
notF(ExprA); 

1. Creating a basic expression from literal(A) or variable(B) 
A) 
LightShow ls; 
ls.push(8, 1000, Expr::makeExpr(true), DIGITAL); 

B) 
int state = 1; 
LightShow ls; 
ls.push(8, 1000, Expr::makeExpr(state), Digital); 

2. Creating a complex expression using an operation 
LightShow ls; 
ls.push(8, 1000, Expr::notF(Expr::makeExpr(true))); 


## Example
int states[2]{}; 

LightShow ls; 
ls.push(7, 1000, Expr::andF(Expr::makeExpr(states[0]), Expr::makeExpr(states[1])), DIGITAL); 
// The LED at pin 7 will turn on for 1000ms at max brightness, if both states[0] and states[1] are not equal to 0 