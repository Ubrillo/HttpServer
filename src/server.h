//
// Created by ubril on 7/25/2026.
//

#ifndef HTTPSERVER_SERVER_H
#define HTTPSERVER_SERVER_H

class Server {
private:
    int port;
    int socketTerminal;
    void handleClient(int clientSocket);
    sockaddr_in socketAddr;

public:
    Server(int port);
    void start();
};

#endif //HTTPSERVER_SERVER_H
