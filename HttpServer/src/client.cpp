//
// Created by ubril on 7/25/2026.
//
#include <iostream>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 1234
using namespace std;


int main()
{
    int sockfd;
    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    //initailize socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    //connect oto serrver
    connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    char buff[1024];

    //send message
    while (1) {
        cout << "\nEnter message: ";
        fgets(buff, 1024, stdin);
        send(sockfd, buff, sizeof buff + 1, 0);
        cout << "Data sent successfully." << endl;
    }
    close(sockfd);
}