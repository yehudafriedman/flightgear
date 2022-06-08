#include <iostream>
#include <fstream>
#include <string>
#include<vector>

using namespace std;

class Lexer
{
            vector<vector<string>> Data;

    public:
        Lexer(){}
        void reedFile(string filePath);
        vector<vector<string>> getAllLines();
        void SplitString(string data);

};
