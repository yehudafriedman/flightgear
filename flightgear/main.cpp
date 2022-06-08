//#include "Client.h"
#include <unistd.h>
// #include "Client.h"
// #include "Server.h"
#include "lexer.h"
//#include "parser.h"
#include "testparser.h"
// #include "testcommand.h"
// #include "testcommand.h"


unsigned int microseconds=10000;

int main()
 {
/*
	Lexer* lexer = new Lexer();
	lexer->reedFile("file.txt");
	usleep(microseconds);
	lexer->getAllLines();
	usleep(microseconds);
	lexer->getLine(4);
	*/

//  Lexer* lexer = new Lexer;
//     lexer->reedFile("file.txt");
// 		usleep(microseconds);


	Parser* parser = new Parser("file.txt");
	// parser->get_all_lines("file.txt");
	parser->do_parser(&parser->all_lines);
	//parser->aaaa();



	
	//Client* client = Client::GetInstance("127.0.0.1", 5402);
	/*
	Server* server = Server::GetInstans("127.0.0.1", 5400);
	cout<<"yyyyyy"<<endl;

	
	server->connecting();
	cout<<"yyyyyy"<<endl;
	usleep(microseconds);
	server->reader();
*/

	/*
	client->connecting();
	usleep(microseconds);
	
	client->sending("set controls/flight/rudder 1\r\n");
	usleep(microseconds);
	server->reader();
	client->sending("set controls/flight/rudder -1\r\n");
	usleep(microseconds);
	client->sending("set controls/flight/rudder 1\r\n");
	usleep(microseconds);
	client->sending("set controls/flight/rudder -1 \r\n");
	usleep(microseconds);
	client->sending("set controls/flight/rudder 1\r\n");
	usleep(microseconds);
	client->sending("set controls/flight/rudder -1\r\n");
	usleep(microseconds);
	client->sending("set controls/flight/rudder 1\r\n");
	usleep(microseconds);
	client->sending("set controls/flight/rudder -1 \r\n");
	*/
return 0;
}



