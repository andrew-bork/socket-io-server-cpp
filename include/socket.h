#pragma once
#include <functional>
// // #include <exception>

#include <vector>
#include <string>

class Socket {
    public:
        // SOCKET _socket;
        int _socket = -1;

        static void defaultOnConnect(Socket& socket);
        static void defaultOnData(Socket& socket, char * buf, int len);
        static void defaultOnError(Socket& socket);
        static void defaultOnLookup(Socket& socket);
        static void defaultOnReady(Socket& socket);
        static void defaultOnTimeout(Socket& socket);
        static void defaultOnDisconnect(Socket& socket);

        std::function<void(Socket&)> onConnect = defaultOnConnect;
        std::function<void(Socket&, char * buf, int len)> onData = defaultOnData;
        std::function<void(Socket&)> onError = defaultOnError;
        std::function<void(Socket&)> onLookup = defaultOnLookup;
        std::function<void(Socket&)> onReady = defaultOnReady;
        std::function<void(Socket&)> onTimeout = defaultOnTimeout;
        std::function<void(Socket&)> onDisconnect = defaultOnDisconnect;

        void write(const char * data, int len);
        void write(const std::vector<char> data);
        void write(const std::string data);
        // static Socket accept(Socket)
};