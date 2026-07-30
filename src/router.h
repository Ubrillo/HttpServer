//
// Created by ubril on 7/25/2026.
//

#ifndef HTTPSERVER_ROUTER_H
#define HTTPSERVER_ROUTER_H
#include <iostream>
#include <unordered_map>
using namespace std;

class Router {
private:
    unordered_map<std::string, std::string> routes;

public:
    void addRoute(std::string path, std::string response);
    string route(std::string path);
};

#endif //HTTPSERVER_ROUTER_H
