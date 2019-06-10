#include "tcp_client.h"

TCP_clinet::TCP_clinet()
{
    sock = -1;
    port = 0;
    address = "";
}

bool TCP_clinet::setup(std::string address, int port) {
    // открываем сокет, -1 это значение по умолчанию
    WSADATA wsdata;
    WSAStartup(0x0101,&wsdata);

    if (sock == -1) {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1) {
            std::cout << "Could not create socket" << std::endl;
        }
    }
    if (inet_addr(address.c_str()) == -1) {
        struct hostent *he = nullptr;

        struct in_addr **addr_list;
        if ( (he==gethostbyname(address.c_str() ) ) == NULL) {
           // herror("gethostbyname");
            std::cout << "Failed to resolve hostname\n";
            return false;
        }
        addr_list = (struct in_addr **) he->h_addr_list;
        for(int i=0; addr_list[i] != NULL; i++) {
            server.sin_addr = *addr_list[i];
            break;
        }
    }
    else {
        server.sin_addr.s_addr = inet_addr( address.c_str() );
    }
    server.sin_family = AF_INET;
    server.sin_port = htons( port );
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror(("connect failed. Error"));;
        return false;
    }
    return true;
}
bool TCP_clinet::Send(std::string data) {
    if(sock != -1 ) {
        if( send(sock, data.c_str() , strlen(data.c_str() ) , 0) < 0) {
            std::cout << "Send failed: " << data << std::endl;
            return false;
        }
    }
    else {
        return false;
    }
    return true;
}

std::string TCP_clinet::receive(int size) {
    char buffer[size];
    memset(&buffer[0], 0, sizeof(buffer));
    std::string reply;
    if ( recv(sock, buffer, size, 0) < 0 ) {
        std::cout << "receive failed" << std::endl;
        return nullptr;
    }
    buffer[size-1] ='\0';
    reply = buffer;
    return reply;
}
// не использую
std::string TCP_clinet::read() {
    char buffer[1] = {};
    std::string reply;
    while (buffer[0] != '\n' ) {
        if (recv(sock, buffer, sizeof(buffer), 0 ) < 0) {
            std::cout << "receive failed" << std::endl;
            return nullptr;
        }
        reply +=buffer[0];
    }
    return reply;
}
void TCP_clinet::exit() {
    // закрываем сокет
    close(sock);
}
