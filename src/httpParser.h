//
// Created by ubril on 7/25/2026.
//

#ifndef HTTPSERVER_HTTPPARSER_H
#define HTTPSERVER_HTTPPARSER_H
#include <iostream>
#include <unordered_map>

using namespace std;

class HttpParser {
private:
    struct properties {
        string method;
        string version;
        string path;
    };
    unordered_map<string, string> metadata;
    unordered_map<string,string> headers;
    string buffer;

public:
    HttpParser(string buffer);
    unordered_map<string, string> getHeaders();
    unordered_map<string, string> getMetadata();

    //struct properties getProperties();
    void parseRequest();

};
#endif //HTTPSERVER_HTTPPARSER_H