#include <sys/types.h>          
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    unsigned short port = 8000;
    char* server_ip = "127.0.0.1";

    int skt = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(skt, SOL_SOCKET, SO_REUSEADDR, (const void*)1, sizeof(int));
    
    struct sockaddr_in s;
    s.sin_family = AF_INET;
    s.sin_port = htons(port);
    s.sin_addr.s_addr = htons(INADDR_ANY);

    struct sockaddr_in s_client;
    
    bind(skt, (struct sockaddr*)&s, sizeof(s));
    listen(skt, 1024);

    char* buf[1024];
    int client = 0;
    int sf = sizeof(s_client);
    while(client = accept(skt, (struct sockaddr*)&s_client, &sf)){
        int rd = read(client, buf, 1024);
        write(1, buf, rd);
        char* ok = "HTTP/1.1 200 OK \n\n";
        char* page = "<html><head><title>My super mega page</title></head><body><h1>Welcome</h1></body></html>";
        write(client, ok, strlen(ok));
        write(client, page, strlen(page));
        close(client);
    }
    
    return 0;
}
