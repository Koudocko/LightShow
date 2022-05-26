# **LightShow - A simple Arduino library for managing LEDs**


## **Overview**
A simple library designed to help you manage the execution flow of your LEDs. It is a state based library, with simulated non-blocking execution. States can be as complex as using numerous operations while relying on a changing lvalue state. 


## **Usage**
To get started, create a new LightShow object with no constructor params to loop infinitely or pass an integer for the number of cycles. Next, use the push(pin, length, expr, mode) to add a new instruction to be executed. The pin is the pin number of the LED. The length is the length the pin will run in milliseconds. The expression is an expression object (more on that later), essentially the deciding condition whether it should execute. The mode tells the program whether you want to run analog or digital mode, ANALOG and DIGITAL macros defined. Now in some loop statement or in your arduino loop entry point, call the refresh() method, as this will update the state of the light. However, make sure to call the begin() method right before you begin executing, as this will initialize the first node. 


## **Expressions**
- To allow the usage of complex states involving prvalues, a wrapper class called Expr must be used. 
- A complex state is any expression involving a state which returns a prvalue, e.g. the opposite of a global variable !varGlobal. 
- Expressions are passed to the push() method of LightShow, thus you must know how to create an expression. 
- To create an expression, call the make() static method and pass any integer (any value category); 
- Expression objects support several operators: +, -, *, /, %, &&, ||, !. 


## **Methods**
### **Expr Class**
- static Expr& make(int& valE) : creates a new expression object from an lvalue
- static Expr& make(const int& valE) : creates a new expression object from an rvalue
- int getData() : retrieve the data stored in an expression object
- operators +, -, *, /, %, &&, ||, !

### **LightShow class**
- void refreshAll() : immediately refreshes all the lights stored in the LightShow object
- void onSwitch(void (*func)()) : set the functionality of the event when a new light instruction is swapped to in the LightShow object
- bool active() : returns whether the LightShow object has finished executing (only valid if finite number of iterations is set)
- void reset() : resets the LightShow object to its original state (also resumes executing if previously finished)
- void refreshLight() : refreshes the state of the current light executing in the LightShow object
- void push(unsigned long pin, unsigned long length, Expr& expr, int mode) : add a new light/instruction to the LightShow object


### **Creating a basic expression from literal(A) or variable(B)**
#### **A)**

    LightShow ls; 
    ls.push(8, 1000, Expr::make(true), DIGITAL); 

#### **B)** 

    int state = 1; 
    LightShow ls; 
    ls.push(8, 1000, Expr::make(state), DIGITAL); 

### **Creating a complex expression using an operation** 

    LightShow ls; 
    ls.push(8, 1000, !Expr::make(true), DIGITAL); 

## **Example**
    int state{1}; 
    LightShow ls(3);

    void setup(){
        pinMode(7, 1);
        pinMode(8, 1);

        ls.push(7, 1000, Expr::make(state), DIGITAL); 
        ls.push(7, 1, Expr::make(false), DIGITAL);

        ls.push(8, 1000, Expr::make(state), DIGITAL); 
        ls.push(8, 1, Expr::make(false), DIGITAL);

        // Loops indefinitely: LED at pin 7 turns on for 1000ms, then off, then LED at pin 8 turns on for 1000ms, then off
    }

    void loop(){
        ls.refresh();
        delay(1); //Tip if experiencing performance issues, add 1ms or greater delay to end of runtime loop
    }
    //This LED pattern I have created here will not block the execution
 