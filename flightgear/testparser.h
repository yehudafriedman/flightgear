#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include<unordered_map>

using namespace std;

class Parser
{
    public:
        Parser(string name_file);
        void do_parser(vector<vector<string>>  lines);
        vector<vector<string>> all_lines;
       
};