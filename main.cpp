#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <stdio.h>


int main() {
	//create socket
	int listening = socket(AF_INET, SOCK_STREAM, 0);
	if(listening == -1) {
		std::cerr << "Can't create socket\n";
		return -1;
	}

	//bind socket to IP/port
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(8000);
	inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

	//mark socket for listening
	//accpet call
	//close listening socket
	//while recieving, display message
	//close socket

	return 0;
}