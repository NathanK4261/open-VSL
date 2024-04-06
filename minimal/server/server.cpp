/*
                    GNU GENERAL PUBLIC LICENSE
                       Version 3, 29 June 2007

 Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
 Everyone is permitted to copy and distribute verbatim copies
 of this license document, but changing it is not allowed.
*/

// Raw video streaming server (no encoding/decoding)
#include "server.h"


// Function to parse configuration file
std::map<std::string, std::string> parseConfigFile(const std::string& filename) {
    std::map<std::string, std::string> configValues;

    std::ifstream configFile(filename);
    if (!configFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return configValues;
    }

    std::string line;
    while (std::getline(configFile, line)) {
        // Skip empty lines or lines starting with #
        if (line.empty() || line[0] == '#')
            continue;

        // Split the line into key and value
        size_t delimiterPos = line.find('=');
        if (delimiterPos != std::string::npos) {
            std::string key = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);
            configValues[key] = value;
        }
    }

    configFile.close();
    return configValues;
}

Server::Server() {
    // Load configuration file and parse it
    std::string filename = "config";
    std::map<std::string, std::string> configValues = parseConfigFile(filename);

    // Set configuration variables from configuration file
    for (const auto& pair : configValues) {
        if (pair.first == "TYPE") {
            TYPE = pair.second;
        }
        else if (pair.first == "IP") {
            IP = pair.second;
        } 
        else if (pair.first == "PORT") {
            PORT = std::stoi(pair.second);
        }
        else if (pair.first == "FPS") {
            FPS = std::stoi(pair.second);
        }
        else if (pair.first == "QUALITY") {
            QUALITY = pair.second;
        }
    }

    // Boot the server
    std::cout << "Server (Boot): " << "[" << IP << " @ " << PORT << "]" << std::endl;

    SERVER = socket(AF_INET, SOCK_STREAM, 0); // The server socket

    // Confirm socket was constructed cleanly
    if (SERVER == -1) {
        throw std::runtime_error("Error creating socket");
    }

    // Allow reusing the address and port
    int opt = 1;
    if (setsockopt(SERVER, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1) {
        close(SERVER);
        throw std::runtime_error("Error setting socket options");
    }
}