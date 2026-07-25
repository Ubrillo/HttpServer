//
// Created by ubril on 7/25/2026.
//

#include <iostream>

string getBody(string &path){
    string body = "";

    if (path == "/") {
        body = "Welcome to my C++ server";
    }
    else if(path == "/about")
    {
        body = "About page";
    }
    else if(path == "/hello")
    {
        body = "Hello World!";
    }
    else
    {
        body = "404 Not Found";
    }
    return body;
}
