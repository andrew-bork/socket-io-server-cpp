#pragma once

#include <string>
#include <socket.h>
#include <functional>

#include <sys/socket.h>

#include <vector>

/**
 * @brief Simple TCP Socket Server.
 * 
 */
class SocketServer {
    private:
    public: 

        /**
         * @brief Get the current address of the server
         * 
         * @return The current address of the server
         */
        std::string address();

        /**
         * @brief Close the server
         * 
         */
        void close();

        /**
         * @brief Get the amount of connections
         * 
         * @return number of connections
         */
        int getAmountOfConnections();
        
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

        /**
         * @brief true if the server is accepting connections.
         * 
         */
        bool listening = false;
        /**
         * @brief Maximum connections this socket server can handle.
         * 
         */
        int maxConnections = 10;

        std::vector<Socket> connections;


        int _socket = -1;
        // SOCKET _socket = INVALID_SOCKET;

        static void defaultOnConnect(SocketServer& server, Socket& socket);
        static void defaultOnDisonnect(SocketServer& server, Socket& socket);
        static void defaultOnListen(SocketServer& server);

        /**
         * @brief Called on Socket connection.
         * 
         */
        std::function<void(SocketServer&, Socket&)> onConnect = defaultOnConnect;
        /**
         * @brief Called on Socket 
         * 
         */
        std::function<void(SocketServer&, Socket&)> onDisconnect = defaultOnDisonnect;
        std::function<void(SocketServer&)> onListen = defaultOnListen;

        ~SocketServer();
};