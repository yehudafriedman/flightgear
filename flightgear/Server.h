#include <unistd.h> // 
#include <stdio.h>
#include <sys/socket.h> //for socket functions
#include <stdlib.h> 
#include <netinet/in.h> //for sockadder_in
#include <string.h>
#include <string> // for string
#include <iostream>
#include <queue>



using namespace std;

class Server
{
    private:

        int port;
        int sock = 0;
        
        int new_socket;

        
    public:
        int samples_second;
        Server(int port ,int samples_second);
        char buffer[1024] = {0};
        int size_buff;
	    void connecting();
	    void reader();

};