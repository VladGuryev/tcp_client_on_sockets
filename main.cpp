#include <iostream>
#include <signal.h>
#include <thread>
#include <iostream>
#include <stdio.h> // ?
#include <stdlib.h> // ?
#include <unistd.h> // ?
#include <string.h>
#include <vector>
#include <sys/types.h> // ?
#include "tcp_client.h"

using namespace std;


TCP_clinet tcp;
void sig_exit(int s) {
    tcp.exit();
    exit(0);
}
int main(int argc, char **argv)
{
    setlocale(LC_ALL, "ru");
    //WSADATA wsdata;
    //WSAStartup(0x0101,&wsdata);

    std::cout << "Start client. ID thread " << this_thread::get_id() << std::endl;
    signal(SIGINT, sig_exit);
    tcp.setup("127.0.0.1", 11999);
    while(1) {
        srand(time(NULL));
        auto num = rand()%1000;
        // отправляем на сервер
        std::string text = "value " + std::to_string(num) ;
        tcp.Send(text);
        std::cout << "send to server: " << text << std::endl;
        // получаем ответ сервера
        auto rec = tcp.receive();
        //auto rec = tcp.read();
        if (rec=="") {
            std::cout << "Server done."<< std::endl;
        }
        else {
            std::cout << "answer server: " << rec << std::endl;
        }
        std::cout << "Wait 10 seconds..." << std::endl;
        //sleep(10);
        this_thread::sleep_for(chrono::milliseconds(10000));
    }
    return 0;
}
