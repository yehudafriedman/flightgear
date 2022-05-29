#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>


using namespace std;

class Client
{
    private:
        Client(string ip ,int port);
        static Client* client;
        string ip;
        int port;
        int sock = 0, valread;
        
    public:
        static Client* GetInstance(string ip, int port);
        char buffer[1024] = {0};
	    void connecting();
	    void sending(char* my_message);

};

