#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<unordered_map>
#include <chrono>
#include <thread>
using namespace std;


bool check_is_operator(string _operator);

class Command
{
    public:
        Command(){};
        virtual void doCommand(vector<string> *data)= 0;
        string search_key(string key);
        string number_value(string str);
        vector<string> expretion(vector<string> exp);        
};

class OpenServerCommand: public Command
{
    public:
        void doCommand(vector<string>*data)override ;
};

class ConnectCommand: public Command
{
    public:
        ConnectCommand(){};
        void doCommand(vector<string>*data) override;
};

class VarCommand: public Command
{
    public:
        void doCommand(vector<string> *data) override;
        void varTable(vector<string>data);
};

class SetCommand:public Command
{
    public:
        void doCommand(vector<string>*data) override;
};

class SleepCommand:public Command
{
    public:
        void doCommand(vector<string>*data) override;
};

class PrintCommand:public Command
{
    public:
        void doCommand(vector<string>*data) override;
};

class IfCommand:public Command
{
    public:
        void doCommand(vector<string>*data) override;
        bool condition_operator(int a, int b, string _operator);
        bool operator_biger(int a, int b);
        bool operator_little(int a, int b);
        bool operator_equal(int a, int b);
        int operator_plus(int a, int b);
        int operator_minus(int a, int b);
        int operator_multiplication(int a, int b);
        int operator_division(int a, int b);
        int calculate_operator(int a, int b, string _operator);

        bool if_expretion_true;


};

