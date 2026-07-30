// //
// // Created by ubril on 7/25/2026.
// //
// // #include <iostream>
// // #include <string>
// // #include <cstring>
// // #include <sys/types.h>
// // #include <sys/socket.h>
// // #include <arpa/inet.h>
// // #include <netinet/in.h>
// // #include <unistd.h>
//
// #include <sstream>
// #include <unordered_map>
//
// using namespace std;
// #include "server.h"
//
// // #define PORT 1234
// // #define BACKLOG 5
//
//
//
// int main()
// {
//
//     // int sockfd;
//     // sockfd = socket(AF_INET, SOCK_STREAM, 0);
//     //
//     // struct sockaddr_in server_addr;
//     // server_addr.sin_family = AF_INET;
//     // server_addr.sin_port = htons(PORT);
//     // server_addr.sin_addr.s_addr = INADDR_ANY;
//     //
//     // // server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
//     // server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
//     //
//     // // Bind socket to local port
//     // bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
//     //
//     // // Start listening on opened port
//     // listen(sockfd, BACKLOG);
//     // cout << "Listening on " << PORT << "..." << endl;
//
//
//
//     // int clientfd;
//     // struct sockaddr_in client_addr;
//     // socklen_t client_len;
//     // client_len = sizeof client_len;
//     //
//     // // //Accept connection request from client
//     // clientfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);
//     //
//     // char buffer[1024], ipstr[INET6_ADDRSTRLEN];
//     //
//     // inet_ntop(AF_INET, &client_addr.sin_addr, ipstr, sizeof ipstr);
//     //
//     //
//     // //recieve messages from server
//     // while (1) {
//     //     unordered_map<string,string> headers;
//     //     memset(buffer, 0, sizeof(buffer));
//     //
//     //     //clientfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);
//     //
//     //     cout << "Client connected from "
//     //          << ipstr
//     //          << endl;
//     //
//     //
//     //     int bytes_received = recv(clientfd, buffer, sizeof buffer, 0);
//     //
//     //     cout << "Received "
//     //      << bytes_received
//     //      << " bytes"
//     //      << endl;
//     //
//     //     if (bytes_received <= 0) {
//     //         break;
//     //     }
//     //
//     //     cout << "message received: " << buffer << endl;
//
//
//         // string request(buffer);
//         // stringstream requestStream(request);
//         // string line;
//         // getline(requestStream, line);
//         //
//         // stringstream lineStream(line);
//         //
//         // string method;
//         // string path;
//         // string version;
//         //
//         // lineStream >> method;
//         // lineStream >> path;
//         // lineStream >> version;
//         //
//         // cout << "method: " << method << endl;
//         // cout << "path: " << path << endl;
//         // cout << "version: " << version << endl;
//         //
//         // while (getline(requestStream, line)) {
//         //     if (!line.empty() && line.back() == '\r') {
//         //         line.pop_back();
//         //     }
//         //     if (line.empty()) {
//         //         break;
//         //     }
//         //
//         //     size_t colon = line.find(':');
//         //
//         //     if (colon != string::npos) {
//         //         string key = line.substr(0, colon);
//         //         string value = line.substr(colon + 1);
//         //
//         //
//         //         if (!value.empty()  && value[0] == ' '){
//         //             value.erase(0, 1);
//         //         }
//         //         headers[key] = value;
//         //     }
//         // }
//         // cout <<"Host: " << headers["Host"] << endl;
//         // cout <<"User-Agent: "<< headers["User-Agent"] << endl;
//     //
//     //     string body;
//     //     string status = "HTTP/1.1 200 OK\r\n";
//     //
//     //     if(path == "/")
//     //     {
//     //         status = "HTTP/1.1 200 OK\r\n";
//     //         body = "Welcome to my C++ server";
//     //     }
//     //     else if(path == "/about")
//     //     {
//     //         body = "About page";
//     //     }
//     //     else if(path == "/hello")
//     //     {
//     //         body = "Hello World!";
//     //     }
//     //     else
//     //     {
//     //         status = "HTTP/1.1 404 Not Found\r\n";
//     //         body = "404 Not Found";
//     //     }
//     //
//     //     string response = status +
//     //     "Content-Type: text/plain\r\n"
//     //     "connection: close\r\n"
//     //     "\r\n"+
//     //     body+"\n";
//     //     //cout << response;
//     //     send(clientfd, response.c_str(), response.size(), 0);
//     //     close(clientfd);
//     //
//     //     break;
//     // }
//
// }
//
// //
// // string router(string path) {
// //     string body = "";
// //
// //     if (path == "/") {
// //         status
// //         body = "Welcome to my C++ server";
// //     }
// //     else if(path == "/about")
// //     {
// //         body = "About page";
// //     }
// //     else if(path == "/hello")
// //     {
// //         body = "Hello World!";
// //     }
// //     else
// //     {
// //         body = "404 Not Found";
// //     }
// //     return body;
// // }
//
//
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