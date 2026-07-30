#include "server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "httpParser.h"
#include "router.h"

#define localhost "127.0.0.1"
#define BACKLOG 5
#include<iostream>
#include <cstring>

using namespace std;

Server::Server(int port) {
    this->port = port;
}

void Server::start() {
    memset(&server_addr, 0, sizeof(server_addr));
    socketTerminal = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;//inet_addr(localhost);

    bind(socketTerminal, (sockaddr *)&server_addr, sizeof(server_addr));
    listen(socketTerminal, BACKLOG);

    cout << "Server listening on port: " << port << endl;

    router.addRoute("/", "This is Home Page");
    router.addRoute("/about", "This is About Page");

    while (true) {
        sockaddr_in clientAddr;
        socklen_t clientLength = sizeof(clientAddr);

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

    unordered_map<string, string> metadata = parser.getMetadata();
    string path = metadata["path"];

    string content =  router.route(path);

    //echoPage(clientSocket, response);

    string status = "HTTP/1.1 200 OK\r\n";
    string response = status +
    "Content-Type: text/plain\r\n"
    "connection: close\r\n"
    "\r\n"+
    content+"\n";
    cout << response;
    send(clientSocket, response.c_str(), response.size(), 0);
    close(clientSocket);
}

// void Server::echoPage(int clientSocket, string response) {
//     string body;
//     string status = "HTTP/1.1 200 OK\r\n";
//
//     if (path == "/") {
//         body = "Welcome to my C++ server";
//     }
//     else if (path == "/about") {
//         body = "About page";
//     }
//     else if (path == "/hello") {
//         body = "Hello World!";
//     }
//     else {
//         status = "HTTP/1.1 404 Not Found\r\n";
//         body = "404 Not Found";
//     }
//
//     string response = status +
//     "Content-Type: text/plain\r\n"
//     "connection: close\r\n"
//     "\r\n"+
//     body+"\n";
//     //cout << response;
//     send(clientSocket, response.c_str(), response.size(), 0);
// }

int main() {
    Server server(1234);
    server.start();
}