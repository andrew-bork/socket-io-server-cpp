// #ifdef A
#include <socket.h>
#include <sys/socket.h>
// #include <stdexcept>
void Socket::defaultOnConnect(Socket& socket){

}
void Socket::defaultOnData(Socket& socket, char * buf, int len){
    
}
void Socket::defaultOnError(Socket& socket){

}
void Socket::defaultOnLookup(Socket& socket){

}
void Socket::defaultOnReady(Socket& socket){

}
void Socket::defaultOnTimeout(Socket& socket){

}
void Socket::defaultOnDisconnect(Socket& socket){

}

void Socket::write(const char * data, int len){
    int res = send(_socket, data, len, 0);
    if(res < len) {
        std::printf("Warning! Sent less bytes than requested\n");
    }else if(res < 0) {
        // throw std::runtime_error("Error at send(): " + std::to_string(WSAGetLastError()));
    }
}

void Socket::write(const std::vector<char> data){
    write(&data[0], data.size());
}

void Socket::write(const std::string data){
    write(data.c_str(), data.length());
}
// #endif