#include "Error.h"



int main(){
    int server = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(1234);
    Bind(server, (struct sockaddr*)&adr,sizeof(adr));
    Listen(server,5);
    socklen_t adrlen = sizeof(adr);
    int new_socket = Accept(server, (struct sockaddr*)&adr,&adrlen);
    while(1){
        char buf[MESS_LEN] = {0};
        ssize_t n_read = Read(new_socket, buf, MESS_LEN-1);
        buf[n_read] = '\0';
        if(n_read > 0 && buf[n_read-1] == '\n'){
            buf[n_read-1] = '\0';
            n_read--;
        }
        if(strcmp(buf, "ping") == 0){
            Write(new_socket, "pong", 4);
            printf("Send: pong\n");
        }
        else if(strcmp(buf, "exit") == 0){
            printf("Received exit command\n");
            Write(new_socket, "bye", 3);
            break;                        
        }
        else{
            printf("Unknown message\n");
            Write(new_socket, "what", 4);
        }
    }
    close(new_socket);
    close(server);
    printf("Server stopped\n");
}