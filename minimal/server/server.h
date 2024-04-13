/*
A copy of the license to this software is located 
in the working directory of the repository
*/


#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <stdexcept>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/socket.h>

class Server {
private:
    static std::string IP;
    static int PORT;
    static int BUFF_SIZE;
    static std::string QUALITY;

    int SERVER; // The server socket
    sockaddr_in ADDRESS; // Server address
    
public:
    Server();

    // Methods that return the private variables
    const std::string& ip() const { return IP; }
    const int& port() const { return PORT; }
    const std::string& quality() const { return QUALITY; }

    // Methods for interacting with the server
    
};

#endif // SERVER_H