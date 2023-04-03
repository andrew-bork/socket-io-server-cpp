#pragma once

#pragma once

#include <string>
#include <server.h>
#include <functional>

#include <vector>
#include <regex>
#include <unordered_map>

class HTTPServer;

class Request {
    std::unordered_map<std::string, std::string> cookies;
    bool fresh;
    std::string method;
    std::string originalUrl;
    std::string protocol;
};

class Response {
    HTTPServer * server;
    Socket * socket;
    void send(std::string response);
    void sendFile(std::string filename);
};

/**
 * @brief Simple HTTP Server.
 * 
 */
class HTTPServer {
    private:

    public: 
        SocketServer _server;
        HTTPServer();
        std::unordered_map<std::string, std::string> cachedFiles;

        /**
         * @brief Close the server
         * 
         */
        void close();
        
        /**
         * @brief Listen on the attached port.
         * @attention This call will block.
         * 
         */
        void listen();
        /**
         * @brief Listen on a given port.
         * @attention This call will block.
         * 
         * @param port port to listen on.
         */
        void listen(int port);

        void use(std::string route, std::function<void(Request&, Response&)> callback);

        std::vector<std::pair<std::regex, std::function<void(Request&, Response&)>>> routes;
};  