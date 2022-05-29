#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include<iostream>
#include <queue>
#include <stack>

using namespace std;

class Calculator 
{
	vector<string> expression;
	string result;
public:
	void calculate(vector<string>exp);
	void remove_unary();
	void postfix();
	int precedence(string op);
	bool is_unary(int i);
	string get_result() { return result; }
    stack<string> fix;
	string solver();
	bool is_operator(string op);
	double applyOp(double a, double b, string op);

};