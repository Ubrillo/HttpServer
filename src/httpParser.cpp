//
// Created by ubril on 7/25/2026.
//

#include "httpParser.h"
#include <sstream>

HttpParser::HttpParser(string buffer) {
    this->buffer = buffer;
}

void HttpParser::parseRequest() {

    string request(this->buffer);
    stringstream requestStream(request);
    string line;
    getline(requestStream, line);

    stringstream lineStream(line);

    string value;
    lineStream >> value;
    this->metadata["method"] = value;
    //this->headers["method"] = value;

    lineStream >> value;
    this->metadata["path"] = value;
    //this->properties.value = value;

    lineStream >> value;
    this->metadata["version"] = value;
    //this->properties.version = value;


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
            this->headers[key] = value;
        }
    }
}

unordered_map<string,string> HttpParser::getHeaders() {
    return this->headers;
}

unordered_map<string,string> HttpParser::getMetadata() {
    return this->metadata;
}

// properties getProperties() {
//     return this->properties;
// }