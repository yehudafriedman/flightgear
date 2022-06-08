#include <unordered_map>
#include <ctype.h>
#include <numeric>
#include <algorithm>
#include <stack>
#include <bits/stdc++.h>
#include "calculator.h"
#include "testcommand.h"
#include "Client.h"
#include "testdatasimulator.h"

using namespace std;
unordered_map<string, string> var_table_bind;
unordered_map<string, string> var_table;

//Gets an expression with variables and returns a mathematical expression with the correct values
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
    return 0;
}

void OpenServerCommand::doCommand(vector<string> *data)
{

    DataSimulator::getInstance(stoi((*data)[1]), stoi((*data)[2]));

}

void ConnectCommand::doCommand(vector<string> *data)
{
    Client *client = Client::GetInstance((*data)[1], stoi((*data)[2]));
    client->connecting();
}

void VarCommand::doCommand(vector<string> *data)
{

    if ((*data)[3] == "bind")
    {
        var_table_bind[(*data)[1]] = (*data)[4];
    }

    else
    {
        string number;
      
        if ((*data)[3][0] > '0' && (*data)[3][0] < '9')
        {
            number = (*data)[3];
        }
        else
        {     
                if (var_table_bind.count((*data)[3]))
                {
                    string key_data_simulator = (*data)[3];

                    number = search_key(key_data_simulator);
                  
                }
        }
        var_table[(*data)[1]] = number;
    }

}
    
void SetCommand::doCommand(vector<string>* data)
{
    
    vector<string> num;
    vector<string> temp;
    for (int i = 2; i < data->size(); i++)
    {
        temp.push_back((*data)[i]);
    }
    num = expretion(temp);

    Calculator* calculator = Calculator::GetInstance();
    calculator->calculate(num);
    string number = calculator->get_result();

    string string_buffer = "set ";
    string string_order = var_table_bind[(*data)[0]];
    // TODO chnge return value, to be sent to the function of the calculator
    string set_command = string_buffer + string_order + ' ' + number + "\r\n";

    int n = set_command.length();
    char char_set_command[n + 1]; // declaring character array
    // TODO: check strcopy
    strcpy(char_set_command, set_command.c_str()); // copying the contents of the string to char array

    Client *client;
    client = client->GetInstance("0", 0);
    client->sending(char_set_command);
    
}

void IfCommand::doCommand(vector<string>* data)
{
    string a = number_value((*data)[1]);
    string b = number_value((*data)[3]);
    if (check_is_operator((*data)[2]))
    {
        if_expretion_true = condition_operator(stoi(a), stoi(b), (*data)[2]);
    }
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
    return false;
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
    return 0;
}
int IfCommand::operator_plus(int a, int b)
{
    return a + b;
}
int IfCommand::operator_minus(int a, int b)
{
    return a - b;
}
int IfCommand::operator_multiplication(int a, int b)
{
    return a * b;
}
int IfCommand::operator_division(int a, int b)
{
    return a / b;
}

bool check_is_operator(string _operator)
{
    return (_operator == ">") || (_operator == "<") || (_operator == "==") || (_operator == ">=") || (_operator == "<=") ||
           (_operator == "+") || (_operator == "-") || (_operator == "*") || (_operator == "/") ||
           (_operator == "+=") || (_operator == "*=") || (_operator == "/=") || (_operator == "(") || (_operator == ")");
}

void SleepCommand::doCommand(vector<string>* data)
{
    this_thread::sleep_for(chrono::milliseconds(stoi((*data)[1])));
}

void PrintCommand::doCommand(vector<string>* data)
{
    if (var_table_bind.count((*data)[1]))
    {
        int number;
        number =stoi(number_value((*data)[1]));
        cout<<(*data)[1]<<"="<<number<<endl;
    }
    else
    {
        for (int i=0; i<data->size();i++)
        {
            cout<<(*data)[i];
        }
        cout<<endl;
    }
    

}


