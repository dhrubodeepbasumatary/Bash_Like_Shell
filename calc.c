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
    various global variables and arrays(for storing the characters of the expression) 
*/
int values[100];
char ops[100];
int top1 = -1, top2 = -1;


/*
    func:find the precedence of the operator
    params:op(operator)
    return:precendence value(0,1,2) of input operator
*/
int precedence(char op){
    if(op == '+'||op == '-')
    return 1;
    if(op == '*'||op == '/')
    return 2;
    return 0;
}


/*
    func:apply the input operator on given operands
    params:a(first operand),b(second operand),op(operator)
    return:return the result of the mathematical expression where a & b are operand and op is operator 
*/
int applyOp(int a, int b, char op){
    switch(op){
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
}


/*
    func:check whether a chacter is digit or  not
    params:c(a character)
    return:return if given chacter is a digit
*/
int Isdigit(char c)
{
    if(c>='0' && c<='9') 
        return 1;

    return 0;
}


/*
    func:evaluate the mathematical expression
    params:tokens(character array representing a mathematical expression),len(length of the expression)
    return:return the result of the mathematical expression
*/
int evaluate(char* tokens,int len){
    int i;

    // stack to store integer values.
    //stack <int> values;

    // stack to store operators.
    //stack <char> ops;

    for(i = 0; i < len; i++){

        // Current token is a whitespace,
        // skip it.
        if(tokens[i] == ' ')
            continue;

        // Current token is an opening
        // brace, push it to 'ops'
        else if(tokens[i] == '('){
            //ops.push(tokens[i]);
            ops[++top2]=tokens[i];
        }

        // Current token is a number, push
        // it to stack for numbers.
        else if(Isdigit(tokens[i])){
            int val = 0;

            // There may be more than one
            // digits in number.
            while(i < len &&
                        Isdigit(tokens[i]))
            {
                val = (val*10) + (tokens[i]-'0');
                i++;
            }

            //values.push(val);
            values[++top1]=val;
        }

        // Closing brace encountered, solve
        // entire brace.
        else if(tokens[i] == ')')
        {
            //while(!ops.empty() && ops.top() != '(')
            while(top2>=0 && ops[top2] != '(')
            {
                //int val2 = values.top();
                //values.pop();
                int val2 = values[top1];
                top1--;

                //int val1 = values.top();
                //values.pop();
                int val1 = values[top1];
                top1--;

                //char op = ops.top();
                //ops.pop();
                char op = ops[top2];
                top2--;

                //values.push(applyOp(val1, val2, op));
                values[++top1] = applyOp(val1, val2, op);
            }

            // pop opening brace.
            //ops.pop();
            top2--;
        }

        // Current token is an operator.
        else
        {
            // While top of 'ops' has same or greater
            // precedence to current token, which
            // is an operator. Apply operator on top
            // of 'ops' to top two elements in values stack.
          /*  while(!ops.empty() && precedence(ops.top())
                                >= precedence(tokens[i])){*/
            while(top2>=0 && precedence(ops[top2]) >= precedence(tokens[i]))
            {
                //int val2 = values.top();
                //values.pop();
                int val2 = values[top1];
                top1--;

                //int val1 = values.top();
                //values.pop();
                int val1 = values[top1];
                top1--;

                //char op = ops.top();
                //ops.pop();
                char op = ops[top2];
                top2--;

                //values.push(applyOp(val1, val2, op));
                values[++top1] = applyOp(val1, val2, op);
            }

            // Push current token to 'ops'.
            //ops.push(tokens[i]);
            ops[++top2]=tokens[i];
        }
    }

    // Entire expression has been parsed at this
    // point, apply remaining ops to remaining
    // values.
    //while(!ops.empty()){
    while(top2>=0)
    {
        //int val2 = values.top();
        //values.pop();
        int val2 = values[top1];
        top1--;

        //int val1 = values.top();
        //values.pop();
        int val1 = values[top1];
        top1--;

        //char op = ops.top();
        //ops.pop();
        char op = ops[top2];
        top2--;

        //values.push(applyOp(val1, val2, op));
        values[++top1]=applyOp(val1, val2, op);
    }

    // Top of 'values' contains result, return it.
    return values[top1];
}

/******************************End of Calculator******************************************/