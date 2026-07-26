//
// Created by ubril on 7/25/2026.
//

#ifndef HTTPSERVER_ROUTER_H
#define HTTPSERVER_ROUTER_H

class Router {
private:
    std::unordered_map<std::string, std::string> routes;

public:
    void addRoute(std::string path, std::string response);

    std::string handleRequest(std::string path);

};

#endif //HTTPSERVER_ROUTER_H
