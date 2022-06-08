#include "testparser.h"
#include "lexer.h"

using namespace std;


Parser::Parser(string name_file)
{
    Lexer* lexer = new Lexer;
    lexer->reedFile(name_file);
    all_lines = lexer->getAllLines();
    parser_table["openDataServer"] = new OpenServerCommand();
    parser_table["connect"] = new ConnectCommand(); 
    parser_table["var"] = new VarCommand();
    parser_table["set"] = new SetCommand();
    parser_table["if"] = new IfCommand();
    parser_table["sleep"] = new SleepCommand();
    parser_table["print"] = new PrintCommand();

}

void Parser::do_parser(vector<vector<string>> *lines)
{
    
    Command* command ;

    for (int i=0; i<lines->size();i++)
    {
        if((*lines)[i][0] != "while" && (*lines)[i][0] != "if")
        {
            if((*lines)[i][0] == "")
            {
                continue;
            }
            if (parser_table.find((*lines)[i][0])!= parser_table.end())
                {
                    command = parser_table[(*lines)[i][0]];
                    command->doCommand(&((*lines)[i]));
                }
            else if((*lines)[i][1] == "=")
                {
                    command = parser_table.at("set");
                    command->doCommand(&((*lines)[i]));
                }
                 
        }
        else // if or while
        {
            IfCommand* command_if = new IfCommand;
            command_if->doCommand(&((*lines)[i]));
            if (!command_if->if_expretion_true)
            {
                do
                {
                    i++;
                } while ((*lines)[i][0] != "}");
                i++;             
            }

            else if ((*lines)[i][0] == "while")
            {
                int j = i + 2;
                   
                if (command_if->if_expretion_true)
                {
                    vector<vector<string>> while_lines;
                    while ((*lines)[j][0] != "}")
                    {
                        while_lines.push_back((*lines)[j]);
                        j++;
                    }
                    do
                    {
                        do_parser(&while_lines);
                        command_if->doCommand(&((*lines)[i]));

                    } while (command_if->if_expretion_true);    
                    
                }
//TODO Check if it is not unnecessary, and check how it can be used without it
                int count = 0;
                while ((*lines)[i][0] !=  "}")
                {
                    count++;
                    i++;
                }
                
                
            }
        }
        
    }
      
}
