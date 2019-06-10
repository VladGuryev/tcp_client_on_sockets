#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <iostream>
#include <stdio.h> // ?
#include <stdlib.h> // ?
#include <unistd.h> // ?
#include <string.h>
#include <vector>
#include <cstdio>
#include <sys/types.h> // ?
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/types.h>
#include <winsock2.h>
#include <windows.h>
#include <pthread.h>
#include <mutex>

class TCP_clinet
{
    public:
        TCP_clinet() ;
        bool setup(std::string address, int port);
        bool Send(std::string data);
        std::string receive(int size=4096);
        std::string read();
        void exit();
    private:
        int sock;
        std::string address;
        int port;
        struct sockaddr_in server;
};
#endif // TCP_CLIENT_H
