/*
A copy of the license to this software is located 
in the working directory of the repository
*/

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
        if (pair.first == "IP") {
            IP = pair.second;
        } 
        else if (pair.first == "PORT") {
            PORT = std::stoi(pair.second);
        }
        else if (pair.first == "BUFF_SIZE") {
            BUFF_SIZE = stoi(pair.second);
        }
        else if (pair.first == "QUALITY") {
            if (pair.first == "low" || pair.first == "med" || pair.first == "high") {
                QUALITY = pair.second;
            }
            else {
                throw std::runtime_error("[open-VSL] - Error in configuration, check config file");
            }
        }
    }

    // Boot the server
    std::cout << "[open-VSL] - Booting Server: " << "[" << IP << " @ " << PORT << "]" << std::endl;

    SERVER = socket(AF_INET, SOCK_DGRAM, 0); // The server socket

    // Confirm socket was constructed cleanly
    if (SERVER == -1) {
        throw std::runtime_error("[open-VSL] - Error in creating socket");
    }

    // Allow reusing the address and port
    int opt = 1;
    if (setsockopt(SERVER, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1) {
        close(SERVER);
        throw std::runtime_error("[open-VSL] - Error setting socket options");
    }

    // Define socket address
    ADDRESS.sin_family = AF_INET;
    ADDRESS.sin_port = htons(PORT);
    ADDRESS.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket
    bind(SERVER, (struct sockaddr*)&ADDRESS, sizeof(ADDRESS));

}