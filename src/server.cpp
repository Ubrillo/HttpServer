#include "server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <unistd.h>
#include <limits.h>

#include <thread>
#include <chrono>


#include "httpParser.h"
#include "router.h"

#define localhost "127.0.0.1"
#define BACKLOG 5

using namespace std;

string readFile(const  string &path);
string getExecutableDir();
void routerConfig(Router &router);

Server::Server(int port) {
    this->port = port;
}

void Server::start() {
    memset(&server_addr, 0, sizeof(server_addr));

    socketTerminal = socket(AF_INET, SOCK_STREAM, 0);
    if (socketTerminal  < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;//inet_addr(localhost);

    int opt = 1;
    //realease address for quick reuse under 1 minuetes
    setsockopt(socketTerminal, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    //binds server address to port
    if (bind(socketTerminal, (sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    //server listen on this socket endpoint
    if (listen (socketTerminal, BACKLOG) < 0) {
        perror("listen");
    }
    cout << "Server listening on port: " << port << endl;

    //add filepath and  routes to router
    routerConfig(router);

    while (true) {
        sockaddr_in clientAddr;
        socklen_t clientLength = sizeof(clientAddr);

        int clientSocket = accept(socketTerminal, (sockaddr *)&clientAddr, &clientLength);
        if (clientSocket < 0) {
            perror("accept failed");
            continue;
        }
        cout << "Client Connected!" << endl;

        thread clientThread(&Server::handleClient,  this, clientSocket);
        clientThread.detach();
        //handleClient(clientSocket);
    }
}

void Server::handleClient(int clientSocket) {
    //this_thread::sleep_for(chrono::seconds(2));

    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead  <= 0) {
        close(clientSocket);
        return;
    }
    buffer[bytesRead] = '\0';

    HttpParser parser(buffer);
    parser.parseRequest();

    unordered_map<string, string> metadata = parser.getMetadata();
    string path = metadata["path"];

    string basePath = getExecutableDir();
    string filePath = basePath + "/../"+router.route(path);//returns a file path

    //string filePath =  router.route(path);

    string content = readFile(filePath);
    string status;
    string contentType;

    if (content.empty()) {
        status = "HTTP/1.1 404 Not Found\r\n";
        contentType = "text/plain";
        content = " 404 Not Found";
    } else {
        status = "HTTP/1.1 200 OK\r\n";
        contentType = "text/html";
    }

    string response = status +
        "Content-Type: " + contentType + "\r\n"
        "Content-Length: " + to_string(content.size()) + "\r\n"
        "Connection: close\r\n"
        "\r\n" + content;

    send(clientSocket, response.c_str(), response.size(), 0);
    close(clientSocket);

}

void routerConfig(Router &router) {
    router.addRoute("/", "public/index.html");
    router.addRoute("/about", "public/about.html");
    router.addRoute("/contact", "public/contact.html");
}

string readFile(const string &path) {
    ifstream file(path, ios::binary);
    if (!file.is_open()) {
        return ""; // caller checks for empty -> treat as 404
    }
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

string getExecutableDir() {
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    string exePath (result, (count > 0) ? count: 0);
    return filesystem::path(exePath).parent_path().string();
}

// /*
// struct sockaddr {
//     unsigned short sa_family;   // Address family (e.g., AF_INET)
//     char sa_data[14];           // Address data
// };
//
// struct sockaddr_in {
//     short sin_family;           // Address family (AF_INET)
//     unsigned short sin_port;    // Port number
//     struct in_addr sin_addr;    // IP address
//     char sin_zero[8];           // Padding to make the structure the same size as sockaddr
// };
//
// struct in_addr {
//     in_addr_t s_addr;  // 32-bit IPv4 address
// };
//
// */