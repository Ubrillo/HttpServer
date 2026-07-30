//
// Created by ubril on 7/25/2026.
//

#include "router.h"
#include <iostream>
using namespace std;

void Router::addRoute(std::string path, std::string response) {
    routes[path] = response;
}

string Router::route(string path) {

    if (routes.find(path) != routes.end()) {
        return routes[path];
    }
    return "404 Not Found";
}
