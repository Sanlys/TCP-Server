#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

int main() {
	int sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock == -1) {
		return 1;
	}

	int port = 8000;
	std::string ip = "127.0.0.1";

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &hint.sin_addr);

	int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connectRes == -1) {
		return 2;
	}

	char buf[4096];
	std::string message;
	
	do {
		std::cout << "> ";
		std::getline(std::cin, message);

		int sendRes = send(sock, message.c_str(), message.size() + 1, 0);
		if(sendRes == -1) {
			std::cout << "Could not send to server\n";
		}

		memset(buf, 0, 4096);
		int bytesRecieved = recv(sock, buf, 4096, 0);
		if (bytesRecieved == -1) {
			std::cout << "No response from server\n";
		} else {
			std::cout << "Res > " << std::string(buf, bytesRecieved) << "\n";
		}

	} while(true);

	close(sock);

	return 0;
}