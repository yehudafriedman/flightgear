#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include<unordered_map>
#include "testcommand.h"


using namespace std;

class Parser
{
    public:
        Parser(string name_file);
        ~Parser();
        void do_parser(vector<vector<string>> *lines);
        vector<vector<string>> all_lines;
        unordered_map<string, Command*>parser_table;
  
};