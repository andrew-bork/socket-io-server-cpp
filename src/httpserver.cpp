#include <http/server.h>

#include <fstream>

void Response::send(std::string response) {
    socket->write(response);
}

void Response::sendFile(std::string filename) {
    if(server->cachedFiles.count(filename) > 0) {
        send(server->cachedFiles[filename]);
    }else{
        std::ifstream t(filename);
        t.seekg(0, std::ios::end);
        size_t size = t.tellg();
        server->cachedFiles[filename] = std::string(size, ' ');
        t.seekg(0);
        t.read(&(server->cachedFiles[filename][0]), size); 
        
        send(server->cachedFiles[filename]);
    }
}

void HTTPServer::close() {

}
void HTTPServer::listen() {

}
void HTTPServer::listen(int port) {
    _server.listen(port);
}
void HTTPServer::use(std::string route, std::function<void(Request&, Response&)> callback) {

}

// static void socketOnData(Socket& socket, char * buf, int length) {
//     for(int i = 0; i < routes)
// }

static void serverOnConnect(SocketServer& server, Socket& socket) {
    std::printf("Client connected");
    // socket.onData = socketOnData;
}

HTTPServer::HTTPServer() {
    _server.onConnect = [this] (SocketServer& server, Socket& socket) -> void {
        socket.onData = [this] (Socket& socket, char * buf, int length) -> void {
            // this->routes.size()
            // std::cmatch matches;
            // for(int i = 0; i < this->routes.size(); i ++) {
            //     // this->routes.first
            //     std::regex_match()
            // }

            // for(int i = 0; i < 10;)
            int i = 0;
            while(true) {
                if(buf[i] == ' ') break;
                if(buf[i] == '\n') {
                    std::printf("Malformed HTTP request, unexpected newline: %d: \"%s\"", i, buf);
                }
                if(i == length)  {
                    std::printf("Malformed HTTP request, unexpected buffer end: \"%s\"", buf);
                    return;
                }

                i++;
            }


            socket.write("No hablo espanol");
        };
    };
}
 