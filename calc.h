/*
    task:implement various mathematical calculation like +,-,*,/,%
    Author:Hemant Kumar
*/

/*
    libraries: include required libraries
*/
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 


/*
    func:find the precedence of the operator
    params:op(operator)
    return:precendence value(0,1,2) of input operator
*/
int precedence(char op);


/*
    func:apply the input operator on given operands
    params:a(first operand),b(second operand),op(operator)
    return:return the result of the mathematical expression where a & b are operand and op is operator 
*/
int applyOp(int a, int b, char op);


/*
    func:check whether a chacter is digit or  not
    params:c(a character)
    return:return if given chacter is a digit
*/
int Isdigit(char c);


/*
    func:evaluate the mathematical expression
    params:tokens(character array representing a mathematical expression),len(length of the expression)
    return:return the result of the mathematical expression
*/
int evaluate(char* tokens,int len);



