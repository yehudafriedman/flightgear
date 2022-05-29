#include "testcommand.h"
// #include "Server.h"
#include "Client.h"
#include <unordered_map>
#include "testdatasimulator.h"
#include <ctype.h>
#include <numeric>
#include <algorithm>
#include <stack>
#include <bits/stdc++.h>
#include "calculator.h"

using namespace std;

unordered_map<string, string> var_table_bind;
unordered_map<string, string> var_table;

int Command::precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

// Function to perform arithmetic operations.
int Command::applyOp(int a, int b, char op)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    }
}

// Function that returns value of
// expression after evaluation.
int Command::evaluate(string tokens)
{
    int i;

    // stack to store integer values.
    stack<int> values;

    // stack to store operators.
    stack<char> ops;

    for (i = 0; i < tokens.length(); i++)
    {

        // Current token is a whitespace,
        // skip it.
        if (tokens[i] == ' ')
            continue;

        // Current token is an opening
        // brace, push it to 'ops'
        else if (tokens[i] == '(')
        {
            ops.push(tokens[i]);
        }

        // Current token is a number, push
        // it to stack for numbers.
        else if (isdigit(tokens[i]))
        {
            int val = 0;

            // There may be more than one
            // digits in number.
            while (i < tokens.length() &&
                   isdigit(tokens[i]))
            {
                val = (val * 10) + (tokens[i] - '0');
                i++;
            }

            values.push(val);

            // right now the i points to
            // the character next to the digit,
            // since the for loop also increases
            // the i, we would skip one
            // token position; we need to
            // decrease the value of i by 1 to
            // correct the offset.
            i--;
        }

        // Closing brace encountered, solve
        // entire brace.
        else if (tokens[i] == ')')
        {
            while (!ops.empty() && ops.top() != '(')
            {
                int val2 = values.top();
                values.pop();

                int val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOp(val1, val2, op));
            }

            // pop opening brace.
            if (!ops.empty())
                ops.pop();
        }

        // Current token is an operator.
        else
        {
            // While top of 'ops' has same or greater
            // precedence to current token, which
            // is an operator. Apply operator on top
            // of 'ops' to top two elements in values stack.
            while (!ops.empty() && precedence(ops.top()) >= precedence(tokens[i]))
            {
                int val2 = values.top();
                values.pop();

                int val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOp(val1, val2, op));
            }

            // Push current token to 'ops'.
            ops.push(tokens[i]);
        }
    }

    // Entire expression has been parsed at this
    // point, apply remaining ops to remaining
    // values.
    while (!ops.empty())
    {
        int val2 = values.top();
        values.pop();

        int val1 = values.top();
        values.pop();

        char op = ops.top();
        ops.pop();

        values.push(applyOp(val1, val2, op));
    }

    // Top of 'values' contains result, return it.
    return values.top();
}

vector<string> Command::expretion(vector<string> exp)
{
    vector<string> temp;
    string x = "";
    for (int i = 0; i < exp.size(); i++)
    {
        if (check_is_operator(exp[i]))
        {
            if (x != "")
            {
                string y = number_value(x);
                temp.push_back(y);
                x = "";
            }
            temp.push_back(exp[i]);
        }
        else
        {
            x += exp[i];
        }
    }
    string y = number_value(x);
    temp.push_back(y);

    return temp;
}

string Command::search_key(string key)
{
    // cout << "key=" << key << endl;
    string number = "";
    if (var_table_bind.count(key))
    {
        number = DataSimulator::getInstance(0, 0)->return_value_by_key(var_table_bind[key]);
    }
    else if (var_table.count(key))
    {
        number = var_table[key];
    }
 
    return number;
}

string Command::number_value(string str)
{
    string number;
    if (str[0] >= '0' && str[0] < '9')
    {
        return str;
    }
    if (str == "+" || str == "-" || str == "*" || str == "/")
    {
        return str;
    }
    number = search_key(str);
    if (number != "")
    {
        return number;
    }
}


void OpenServerCommand::doCommand(vector<string> data)
{

    DataSimulator::getInstance(stoi(data[1]), stoi(data[2]));

}

void ConnectCommand::doCommand(vector<string> data)
{
    Client *client = Client::GetInstance(data[1], stoi(data[2]));
    client->connecting();
    // client->sending("set controls/flight/rudder 1\r\n");
    // client->sending("set controls/flight/rudder -1\r\n");
    // cout << data[1] << ' ' << data[2] << endl;
}

void VarCommand::doCommand(vector<string> data)
{

    if (data[3] == "bind")
    {
        // cout<<"data"<<data[4]<<endl;
        // for(int i=0;i<data[4].size();i++)
        // {
        //     cout<<i<<data[4][i]<<endl;
        // }

        var_table_bind[data[1]] = data[4];

        // VarCommand::varTable(data);
    }

    else
    {
        string number;
      
        if (data[3][0] > '0' && data[3][0] < '9')
        {
            number = data[3];
        }

        else
        {
          
                if (var_table_bind.count(data[3]))
                {
                    // string key_data_simulator = var_table_bind[data[3]];
                    string key_data_simulator = data[3];

                    number = search_key(key_data_simulator);
                    // number = DataSimulator::getInstance(0,0)->return_value_by_key(key_data_simulator);

                    // DataSimulator* number = DataSimulator::getInstance(0,0);
                    // number = number->simulator_table[key_data_simolator];

                    // number= getInstance datasimulatortable.give(key_data_simolator)
                }
            // }
        }
        var_table[data[1]] = number;
    }

    // }
}

void SetCommand::doCommand(vector<string> data)
{
    
    vector<string> num;
    vector<string> temp;
    for (int i = 2; i < data.size(); i++)
    {
        temp.push_back(data[i]);
    }
    num = expretion(temp);
    Calculator *calculat = new Calculator();
    calculat->calculate(num);
    stack<string> x = calculat->fix;
    string number = calculat->get_result();


    string string_buffer = "set ";
    string string_order = var_table_bind[data[0]];
    // TODO chnge return value, to be sent to the function of the calculator
    string set_command = string_buffer + string_order + ' ' + number + "\r\n";
    cout << "set_command = " << set_command << endl;

    int n = set_command.length();
    char char_set_command[n + 1]; // declaring character array
    // TODO: check strcopy
    strcpy(char_set_command, set_command.c_str()); // copying the contents of the string to char array

    // for (int i = 0; i < n; i++)
    // {
    //     cout << char_set_command[i];
    // }
    Client *client;
    client = client->GetInstance("0", 0);
    client->sending(char_set_command);
}

void IfCommand::doCommand(vector<string> data)
{
    if (data[2][0]==')')
    {
        vector<string> temp;
        for (int i=2;i<data.size();i++)
        {
            temp.push_back(data[i]);
        }


    }
    string a = number_value(data[1]);
    string b = number_value(data[3]);
    if (check_is_operator(data[2]))
    {
        if_expretion_true = condition_operator(stoi(a), stoi(b), data[2]);
    }
    // TODO else :if is not operator
}

bool IfCommand::condition_operator(int a, int b, string _operator)
{
    if (_operator == ">")
    {
        return operator_biger(a, b);
    }
    else if (_operator == "<")
    {
        return operator_little(a, b);
    }
    else if (_operator == "=")
    {
        return operator_equal(a, b);
    }
    else if (_operator == ">=")
    {
        return operator_biger(a, b) || operator_equal(a, b);
    }
    else if (_operator == "<=")
    {
        return operator_little(a, b) || operator_equal(a, b);
    }
}
bool IfCommand::operator_biger(int a, int b)
{
    return a > b;
}
bool IfCommand::operator_little(int a, int b)
{
    return a < b;
}
bool IfCommand::operator_equal(int a, int b)
{
    return a == b;
}

//TODO Check if you need it
int IfCommand::operator_plus(int a, int b)
{
    return a + b;
}

//TODO Check if you need it
int IfCommand::operator_minus(int a, int b)
{
    return a - b;
}

//TODO Check if you need it
int IfCommand::operator_multiplication(int a, int b)
{
    return a * b;
}

//TODO Check if you need it
int IfCommand::operator_division(int a, int b)
{
    return a / b;
}

//TODO Check if you need it
int IfCommand::calculate_operator(int a, int b, string op)
{
    if (op == "+")
    {
        return operator_plus(a, b);
    }
    if (op == "-")
    {
        return operator_minus(a, b);
    }
    if (op == "*")
    {
        return operator_multiplication(a, b);
    }
    if (op == "/")
    {
        return operator_division(a, b);
    }
}

bool check_is_operator(string _operator)
{
    return (_operator == ">") || (_operator == "<") || (_operator == "==") || (_operator == ">=") || (_operator == "<=") ||
           (_operator == "+") || (_operator == "-") || (_operator == "*") || (_operator == "/") ||
           (_operator == "+=") || (_operator == "*=") || (_operator == "/=") || (_operator == "(") || (_operator == ")");
}

void SleepCommand::doCommand(vector<string> data)
{
    this_thread::sleep_for(chrono::milliseconds(stoi(data[1])));
    // cout << "sleep commend" << data[1];
}

void PrintCommand::doCommand(vector<string> data)
{
    if (var_table_bind.count(data[1]))
    {
        int number;
        number =stoi(number_value(data[1]));
        cout<<data[1]<<"="<<number<<endl;
    }
    else
    {
        for (int i=0; i<data.size();i++)
        {
            cout<<data[i];
        }
        cout<<endl;
    }
    

}


