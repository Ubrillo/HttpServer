//
// Created by ubril on 7/25/2026.
//

#include <iostream>
#include <sstream>
using namespace std;
#include <unordered_map>

int  main()
{

    string request = "GET /hello HTTP/1.1\r\n"
    "Host: localhost\r\n"
    "User-Agent: Chrome\r\n"
    "Accept: text/html\r\n"
    "\r\n";

    stringstream requestStream(request);

    string line;
    getline(requestStream, line);

    stringstream lineStream(line);

    string method;
    string path;
    string version;

    lineStream >> method;
    lineStream >> path;
    lineStream >> version;

    cout << "method: " << method << endl;
    cout << "path: " << path << endl;
    cout << "version: " << version << endl;

    unordered_map<string,string> headers;

    while (getline(requestStream, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (line.empty()) {
            break;
        }

        size_t colon = line.find(':');

        if (colon != string::npos) {
            string key = line.substr(0, colon);
            string value = line.substr(colon + 1);


            if (!value.empty()  && value[0] == ' '){
                value.erase(0, 1);
            }
            headers[key] = value;
        }
    }
    cout << headers["Host"] << endl;
    cout << headers["User-Agent"] << endl;

    string response = "HTTP/1.0 200 OK\r\n"
    "Content-Type: text/plain\r\n"
    "\r\n";
    "Hello from C++ server";
    send(cli)

}

//int main(){}