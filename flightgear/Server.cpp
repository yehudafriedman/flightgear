#include "Server.h"
#include <arpa/inet.h>


using namespace std;

Server::Server(int port, int samples_second)
{
	this->samples_second = samples_second;
	this->port = port;
	// cout << port << " = port" << endl;
}

void Server::connecting()
{
	int server_fd, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	char *hello;

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
				   &opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons(port);		 
	// cout << "server_fd=" << server_fd << endl;
	// cout << "sin_family=" << address.sin_family << endl;
	// cout << "sin_addr=" << address.sin_addr.s_addr << endl;
	// cout << "sin_port=" << address.sin_port << endl;

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr *)&address,
			 sizeof(address)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	cout<<"turn on flightgear"<<endl;
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
							 (socklen_t *)&addrlen)) < 0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}

}

void Server::reader()
{
		memset(buffer, 0, 1024);
		size_buff = read(new_socket, buffer, 1024);
}

