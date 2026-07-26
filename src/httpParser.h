//
// Created by ubril on 7/25/2026.
//

#ifndef HTTPSERVER_HTTPPARSER_H
#define HTTPSERVER_HTTPPARSER_H
#include <iostream>

class HttpParser {
private:
    struct properties {
        string method;
        string version;
        string path;
    };
    unordered_map<string, string> metadata;
    unordered_map<string,string> headers;
    char buffer;

public:
    HttpParser(char buffer[]);
    unordered_map<string, string> getMetadata();
    unordered_map<string, string> headers();

    struct properties getProperties();
    void parseRequest();

};
#endif //HTTPSERVER_HTTPPARSER_H
