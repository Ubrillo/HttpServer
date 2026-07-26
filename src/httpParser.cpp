//
// Created by ubril on 7/25/2026.
//

#include "httpParser.h"
#include <sstream>

HttpParser::HttpParser(char buffer[]) {
    this->buffer = std::move(buffer);
}

unordered_map<string,string> HttpParser::getMetadata() {
    return metadata;
}
void HttpParser::parseRequest() {

    string request(this->buffer);
    stringstream requestStream(request);
    string line;
    getline(requestStream, line);

    stringstream lineStream(line);

    string value;
    this->metadata["method"] = lineStream >> value;
    this->properties.method = value;

    this->metadata["path"] = lineStream >> value;
    this->properties.value = value;

    this->metadata["version"] = lineStream >> value;
    this->properties.version = value;

    // cout << "method: " << method << endl;
    // cout << "path: " << path << endl;
    // cout << "version: " << version << endl;


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

unordered_map<string,string> HttpParser::headers() {
    return this->headers;
}

unordered_map<string,string> HttpParser::metadata() {
    return this->metadata;
}

properties getProperties() {
    return this->properties;
}