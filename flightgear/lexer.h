// #ifndef _LEXER
// #define _LEXER
#include <iostream>
#include <fstream>
#include <string>
#include<vector>

using namespace std;

class Lexer
{
    
    public:
        Lexer(){}
        void reedFile(string filePath);
        vector<string> getNextLine();
        vector<vector<string>> getAllLines();
        vector<string> getLine(int line);
        void SplitString(string data);
        vector<vector<string>> Data;

};
// #endif //_LEXER

// void Parser::do_parser()
// {
    
//         Command* command ;

//     for (int i=0; i<all_lines.size();i++)
//     {
//         if (umap.find(all_lines[i][0])!= umap.end())
//         {
//             command = umap.at(all_lines[i][0]);
//             command->doCommand(all_lines[i]);

//         }
        
//     }
// }