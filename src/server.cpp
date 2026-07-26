#include "server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "httpParser.h"
#include "router.h"

#define localhost "127.0.0.1"
#define BACKLOG 5
using namespace std;

Server::Server(int port) {
    this->port = port;
}



void Server::start() {
    memset(&socketAddr, 0, sizeof(socketAddr));
    socketTerminal = socket(AF_INET, SOCK_STREAM, 0);
    socket_addr.sin_family = AF_INET;
    socket_addr.sin_port = htons(port);
    socket_addr.sin_addr.s_addr = inet_addr(localhost);

    bind(socketTerminal, (sockaddr *)&socket_addr, sizeof(socketAddr));
    listen(socketTerminal, BACKLOG);

    cout << "Server listening on port: " << port << endl;

    Router router();
    router.addRoute("/", "Home Page");
    router.addRoute("/about", "About Page");

    while (true) {
        sockaddr_in clientAddr;
        socketlen_t clientLength = sizeof(clientAddr);

        int clientSocket = accept(
            socketTerminal,
            (sockaddr *)&clientAddr,
            &clientLength
        );
        cout << "Client Connected!" << endl;
        handleClient(clientSocket);
    }
}

void Server::handleClient(int clientSocket) {
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    int bytesRead = recv(
        clientSocket,
        buffer,
        sizeof(buffer),
        0
    );
    if (bytesRead > 0) {
        cout << buffer << endl;
    }
    HttpParser parser(buffer);
    parser.parseRequest();

    unordered_map<string, string> metadatta = parser.getMetadata();
    string path = metadatta["path"];
    

    close(clientSocket);
}