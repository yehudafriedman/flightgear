#include "Client.h"

using namespace std;

Client* Client::client = NULL;

Client::Client(string ip, int port)
{
	this->ip = ip;
    this->port = port;
}

Client* Client::GetInstance(string ip, int port)
{
	if (client == NULL) {
		client = new Client(ip, port);
	}
	return client;
}

void Client::connecting()
{
	struct sockaddr_in serv_addr;
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	
	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return;
	}
    
}
void Client::sending(char* my_message)
{
    send(sock, my_message , strlen(my_message) , 0 );
	valread = read( sock , buffer, 1024);
	printf("%s\n",buffer );

}