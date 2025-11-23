#include "Error.h"



int main(){
    int server = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(1234);
    Bind(server, (struct sockaddr*)&adr,sizeof(adr));
    Listen(server,5);
    while(1){
        socklen_t adrlen = sizeof(adr);
        int new_socket = Accept(server, (struct sockaddr*)&adr,&adrlen);
        char buf[MESS_LEN+1] = {0};
        ssize_t n_read = Read(new_socket, buf, MESS_LEN);
        buf[n_read] = '\0';
        if(strncmp(buf, "ping", 4) == 0){
            Write(new_socket, "pong", MESS_LEN);
            printf("Send: pong\n");
        }
        else if(strncmp(buf, "exit", 4) == 0){
            printf("Received exit command\n");
            Write(new_socket, "bye", MESS_LEN);
            close(new_socket);
            close(server);
            return 0;
        }
        else{
            printf("Unknown message\n");
            Write(new_socket, "what", MESS_LEN);
        }
        close(new_socket);

    }
}