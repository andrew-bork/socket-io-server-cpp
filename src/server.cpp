// #ifdef A
#include <server.h>
#include <netinet/in.h>
#include <errno.h>

#include <unistd.h>

#include <poll.h>

#define MAX_RECV_BUF 512

std::string SocketServer::address() {
    return "";
}

void SocketServer::close() {
    std::printf("Closing");
}

int SocketServer::getAmountOfConnections() {
    return 0;
}

#define checkFlag(flags,flag) ((flags & flag) == flag)
// void listen();
void SocketServer::listen(int port) {
    // std::printf("Setting up server.\n");
    _socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(_socket < 0) {
        perror("Failed to create socket()");
        return;
    }
    
    // std::printf("Created Socket %d\n", _socket);

    sockaddr_in addrinfo;
    addrinfo.sin_family = AF_INET;
    addrinfo.sin_addr.s_addr = INADDR_ANY;
    addrinfo.sin_port = htons(port);

    int res = bind(_socket, (sockaddr*)(&addrinfo), sizeof(addrinfo));
    if(res < 0) {
        perror("Failed to bind()");
        return;
    }

    std::printf("Listening...\n");
    res = ::listen(_socket, 10);
    if(res < 0) {
        perror("Failed to listen()");
    }
    
    char recvBuf[MAX_RECV_BUF+1];
    // std::vector<char> recvBuf;
    // recvBuf.resize(MAX_RECV_BUF);

    std::vector<pollfd> pollStructs;
    pollfd pollStruct;
    pollStruct.fd = _socket;
    pollStruct.events = POLLIN|POLLHUP;
    pollStructs.push_back(pollStruct);
    listening = true;

    sockaddr clientAddrInfo;
    socklen_t socketLength;


    while(listening) { // | POLLHUP;
        res = poll(&(pollStructs[0]), pollStructs.size(), 100);
        // std::printf("Heartbeat: %d, %d\n", pollStructs[0].events,pollStructs[0].revents);
        if(res < 0) {
            std::printf("Failed to poll(): %d\n", errno);
            return;
        }
        

        if(checkFlag(pollStructs[0].revents, POLLIN)) {
            // std::printf("Connection to accept\n");

            socklen_t socketLength = -1;
            Socket client;
            client._socket = accept(_socket, NULL, NULL);
            // printf("%d\n", client._socket);
            if(client._socket < 0) {
                perror("Failed to accept()");
                return;
            }
            // std::printf("Connection accepted\n");

            onConnect((*this), client);
            client.onConnect(client);
            connections.push_back(client);
            pollStruct.fd = client._socket;
            pollStructs.push_back(pollStruct);
        }
        for(int i = 0; i < connections.size(); i ++) {
            if(checkFlag(pollStructs[i+1].revents, POLLHUP)) {
                
                connections[i].onDisconnect(connections[i]);
                onDisconnect((*this), connections[i]);

                ::close(connections[i]._socket);

                connections.erase(connections.begin() + i);
                pollStructs.erase(pollStructs.begin() + i + 1);
                i--;
            }else if(checkFlag(pollStructs[i+1].revents, POLLIN)) {
                // std::printf("Data to read\n");
                int length = recv(connections[i]._socket, recvBuf, MAX_RECV_BUF, 0);
                if(length < 0) {
                    std::printf("Failed to recv(): %d\n", errno);
                    return;
                }
                if(length == 0) {
                    connections[i].onDisconnect(connections[i]);
                    onDisconnect((*this), connections[i]);

                    ::close(connections[i]._socket);

                    connections.erase(connections.begin() + i);
                    pollStructs.erase(pollStructs.begin() + i + 1);
                    i--;
                    continue;
                }
                recvBuf[length] = '\0';
                // std::printf("Message: %s", recvBuf);
                connections[i].onData(connections[i], recvBuf, length);
            }
        }

    }
}

SocketServer::~SocketServer() {
    close();
}



void SocketServer::defaultOnConnect(SocketServer& server, Socket& socket){

}
void SocketServer::defaultOnDisonnect(SocketServer& server, Socket& socket){

}
void SocketServer::defaultOnListen(SocketServer& server){

}

// #endif