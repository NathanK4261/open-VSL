/*
                    GNU GENERAL PUBLIC LICENSE
                       Version 3, 29 June 2007

 Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
 Everyone is permitted to copy and distribute verbatim copies
 of this license document, but changing it is not allowed.
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
    static std::string TYPE;
    static std::string IP;
    static int PORT;
    static int FPS;
    static std::string QUALITY;

    
public:
    Server();
    int SERVER; // The server socket

    // Methods that return the private variables
    const std::string& type() const { return TYPE; }
    const std::string& ip() const { return IP; }
    const int& port() const { return PORT; }
    const int& fps() const { return FPS; }
    const std::string& quality() const { return QUALITY; }

    // 
};

#endif // SERVER_H