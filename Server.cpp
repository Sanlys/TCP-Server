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

	if (bind(listening, (sockaddr*)&hint, sizeof(hint)) == -1) {
		std::cerr << "Can't bind to IP/port\n";
		return -2;
	}

	//mark socket for listening
	if (listen(listening, SOMAXCONN) == -1) {
		std::cerr << "Can't Listen\n";
		return -3;
	}

	//accpet call
	sockaddr_in client;
	socklen_t clientSize = sizeof(client);
	char host[NI_MAXHOST];
	char svc[NI_MAXSERV];


	int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

	if (clientSocket == -1) {
		std::cerr << "Client couldn't connect\n";
		return -4;
	}

	//close listening socket
	close(listening);

	memset(host, 0, NI_MAXHOST);
	memset(svc, 0, NI_MAXSERV);

	int result = getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, svc, NI_MAXSERV, 0);

	if (result) {
		std::cout << host << " connected on " << svc << "\n";
	}
	else {
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		std::cout << host << " connected on " << ntohs(client.sin_port) << "\n";
	}

	//while recieving, display message, send same message back
	char buf[4096];
	while (true) {
		//Clear buffer
		memset(buf, 0, 4096);

		//Wait for message
		int bytesRecv = recv(clientSocket, buf, 4096, 0);
		if (bytesRecv == -1) {
			std::cerr << "Could not connect\n";
			break;
		}

		if (bytesRecv == 0) {
			std::cout << "The client disconnected\n";
			break;
		}

		//Display message
		std::cout << "Recieved: " << std::string(buf, 0, bytesRecv) << "\n";

		//Resend message
		send(clientSocket, buf, bytesRecv + 1, 0);
	}

	//close socket
	close(clientSocket);

	return 0;
}