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
	static Calculator* calculator;
	vector<string> expression;
	string result;

public:
	static Calculator* GetInstance();
	void calculate(vector<string>exp);
	void remove_unary();
	void postfix();
	int precedence(string op);
	bool is_unary(int i);
	string get_result() { return result; }
    queue<string> fix;
	string solver();
	double applyOp(double a, double b, string op);

};