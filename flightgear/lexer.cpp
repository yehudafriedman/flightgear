#include "lexer.h"

using namespace std;

void Lexer::reedFile(string filePath)
{
   fstream newfile;
   string data;

   newfile.open(filePath,ios::in); //open a file to perform read operation using file object
   if (newfile.is_open())   //checking whether the file is open
   {
      string tp;
      while(getline(newfile, tp)) //read data from file object and put it into string.
      {
         data+=tp +"\n";
      }
      
      newfile.close(); //close the file object.
   }
   SplitString(data);

}

void Lexer::SplitString(string data)
{
    
	string temp = "";
    vector<string> v1;
	for(int i=0;i<data.length();i++)
    {
        if(data[i]=='\n')
        {
            v1.push_back(temp);
			temp = "";
            Data.push_back(v1);
            v1.clear();
        }
		else if(data[i]==' ')
        {
			v1.push_back(temp);
			temp = "";
		}
        

		else{
			temp.push_back(data[i]);
            
		}
		
	}

	v1.push_back(temp);
    Data.push_back(v1);

}

vector<vector<string>> Lexer::getAllLines()
{

    return Data;
}





