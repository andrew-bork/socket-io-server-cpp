#include <cstdio>
#include <server.h>
#include <string>
// #pragma comment(lib, "Ws2_32.lib")
#include <vector>
#include <cstring>

// void socketOnData(Socket& socket, char * buf, int len) {
//     printf("Echo: %s", buf);
//     socket.write(buf, len);
// }

// void socketOnDisconnect(Socket& socket) {
//     printf("Socket disconnected\n");
// }

// void serverOnConnect(SocketServer& server, Socket& socket){
//     printf("CONENCNITENONIOFDNAAFDSNOIFDSAFAs\n");
//     socket.onData = socketOnData;
//     socket.onDisconnect = socketOnDisconnect;
// }

// void defaulta() {
//     printf("default");
// }
// void newone() {
//     printf("new");
// }
// struct test {
//     std::function<void(void)> call=defaulta;
// };


class Request {
    public:
        std::unordered_map<std::string, std::string> cookies;
        bool fresh;
        std::string method;
        std::string originalUrl;
        std::string protocol;
};

struct tokenizer {
    std::string s;
    std::string delim;
    size_t i = 0;
    bool nextToken(std::string& out) {
        if(i == std::string::npos) {
            out = "";
            return false;
        }
        size_t j = s.find(delim, i);
        out = s.substr(i, j-i);
        if(j == std::string::npos){
            i = j;
        }else {
            i = j+delim.size();
        }
        // return result;
        return true;
    }
};

bool validHeader(std::string& s) {
    
    for(int i = 0; i < s.length(); i ++) {
        char c = s[i];
        if(!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '-')) {
            return false;
        }
    }
    return true;
}

void lowercase(std::string& s) {
    for(int i = 0; i < s.length(); i ++) {
        char c = s[i];
        if((c >= 'A' && c <= 'Z')) {
            s[i] = s[i]-'A'+'a';
        }
    }

}

void parseHTTP(char * buf, int length, Request& request) {
    tokenizer lines;
    lines.s = std::string(buf, length);
    lines.delim = "\r\n";

    std::string line;
    if(!lines.nextToken(line)) {
        std::printf("Unexpected end of HTTP Request data\n");
        return;
    }
    // printf("%s\n", line.c_str());

    std::string method, url, version;

    tokenizer lineTokenizer;
    lineTokenizer.s = line;
    lineTokenizer.delim = " ";
    if(!lineTokenizer.nextToken(request.method)) {
        std::printf("No method (\"GET\", \"POST\") was found: \"%s\"", buf);
        return;
    }
    lowercase(request.method);
    //     OPTIONS GET HEAD POST PUT DELETE TRACE CONNECT PATCH
    if(request.method != "get" && request.method != "post" && request.method != "options" && request.method !=  "put" && request.method != "delete" &&  request.method != "trace" &&  request.method != "connect" && request.method != "patch") {
        std::printf("Unknown method \"%s\"", request.method.c_str());
        return;
    }

    if(!lineTokenizer.nextToken(url)) {
        std::printf("No url (\"/foo/bar\") was found: \"%s\"", buf);
        return;
    }
    

    if(!lineTokenizer.nextToken(version)) {
        std::printf("No method (\"HTTP/1.1\") was found: \"%s\"", buf);
        return;
    }

    printf("%s\n%s\n%s\n", method.c_str(), url.c_str(), version.c_str());

    std::string header, value;
    lineTokenizer.delim = ": ";
    // printf("fadskalfj;sdlaj %s \nfdskfdsjakljfdskl %d\n", lines.s.c_str(), lines.i);
    while(lines.nextToken(lineTokenizer.s)) {
        if(lineTokenizer.s.length() == 0){ 
            break;
        }
        lineTokenizer.i = 0;
        // printf("%d f \"%s\"\n", lines.i, lineTokenizer.s.c_str());
        lineTokenizer.nextToken(header);
        
        if(header.length() == 0) {
            std::printf("Header is empty: \"%s\"\n", lineTokenizer.s.c_str());
            continue;
        }
        if(!validHeader(header)) {
            std::printf("Header contains invalid characters: \"%s\"\n", lineTokenizer.s.c_str());
            continue;
        }
        lowercase(header);
        lineTokenizer.nextToken(value);
        std::printf("%s - %s\n", header.c_str(), value.c_str());
    }

}

int main() {
    std::string test = "GET /abc?atr=213 HTTP/1.1\r\nHost: localhost:3000\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:109.0) Gecko/20100101 Firefox/111.0\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, deflate, br\r\nConnection: keep-alive\r\nUpgrade-Insecure-Requests: 1\r\nSec-Fetch-Dest: document\r\nSec-Fetch-Mode: navigate\r\nSec-Fetch-Site: none\r\nSec-Fetch-User: ?1";
    // std::string test = "";
    parseHTTP(&test[0], test.size());

    // std::string a = "a b c d e f g h i j k";
    // tokenizer t;
    // t.s = a;
    // t.delim = " ";
    // std::string b;
    // while(t.nextToken(b)) {
    //     printf("%s\n", b.c_str());
    // }

    // test s;
    // s.call();
    // s.call = newone;
    // s.call();
    // s.call = defaulta;
    // s.call();
    // SocketServer server;
    // server.onConnect = serverOnConnect;
    // server.listen(3000);
}
