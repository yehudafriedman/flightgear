#include "calculator.h"

Calculator* Calculator::calculator = NULL;
Calculator* Calculator::GetInstance()
{
    if(calculator == NULL)
    {
        calculator = new Calculator();
    }
    return calculator;
}

void Calculator::calculate(vector<string>exp)
{
    
    expression = exp;
    remove_unary();
    postfix();
    result = solver();
    
}

void Calculator::postfix()
{
    stack<string> temp;
    for (auto i=expression.begin();i!=expression.end();i++)
    {
        string check = *i;
        

        if (precedence(check))
        {
            while (!temp.empty() && precedence(check) <= precedence(temp.top()))
            {

                string top = temp.top();
                temp.pop();
                fix.push(top);
            }
            temp.push(check);
        }

        else if (check == "(")
            temp.push(check);

        else if (check == ")")
        {
            while (temp.top() != "(")
            {
                fix.push(temp.top());
                temp.pop();
            }
            temp.pop();
        }
        else
            fix.push(check);
       
    }
    while (!temp.empty())
    {
        fix.push(temp.top());
       temp.pop();
    }
}

int Calculator::precedence(string op)
{
    if (op == "+" || op == "-")
        return 1;
    if (op == "*" || op == "/")
        return 2;
    return 0;
}

void Calculator::remove_unary()
{
    for (int i = 0; i < expression.size(); i++)
        if (is_unary(i))
        {
            if (expression[i+1].c_str()[0] == '-')
                expression[i+1].erase(0,1);
            else
            {
                string str = "-";
                str += expression[i+1];
                expression[i+1]=str;
            }
            expression.erase(expression.begin() + i);
            i = 0;
        }       
}

bool Calculator::is_unary(int i)
{
    if (expression[i] == "-")
        if (i == 0 || precedence(expression[i - 1]) > 0 ||
            expression[i - 1] == "(" )
            return true;
    return false;
}


double Calculator::applyOp(double a, double b, string op)
{
    char r = op[0];
    switch(r)
    {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

string Calculator::solver()
{
    stack<string> _operator;
    stack<string> _operand;
    
    
    while (!fix.empty())
    {
        if (! precedence(fix.front()))
        {
            _operand.push(fix.front());
            fix.pop();
        }
        else
        {
            string op = fix.front();
            double a = stod(_operand.top());
            _operand.pop();
            double b = stod(_operand.top());
            _operand.pop();
           double x = applyOp(b,a,op);
         _operand.push(to_string(x));
            fix.pop();
        }
    }
    
    while(!_operator.empty())
    {
        string op = _operator.top();
        double a = stod(_operand.top());
        _operand.pop();
        double b = stod(_operand.top());
        
        _operand.pop();
        _operator.pop();
        double x = applyOp(a,b,op);
        _operand.push(to_string(x));
        
    }
    
    return _operand.top();
}



