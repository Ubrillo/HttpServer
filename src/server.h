//
// Created by ubril on 7/25/2026.
//

#ifndef HTTPSERVER_SERVER_H
#define HTTPSERVER_SERVER_H


#include <iostream>
#include <netinet/in.h>
#include "router.h"

using namespace std;

class Server {

private:
    int port;
    int socketTerminal{};
    void handleClient(int clientSocket);
    struct sockaddr_in server_addr;
    Router router{};

public:
    Server(int port);
    void start();
    void  echoPage(int clientSocket, string path);
};

#endif //HTTPSERVER_SERVER_H
