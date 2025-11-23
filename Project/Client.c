#include "Error.h"

int main(){
    int fd = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(1234);
    Inet_pton(AF_INET, "127.0.0.1", &adr.sin_addr);
    Connect(fd, (struct sockaddr *) &adr, sizeof adr);
    printf("Enter the message:\n");
    char bufSend[MESS_LEN] = {0};
    read(STDIN_FILENO, bufSend, MESS_LEN);
    Write(fd, bufSend, MESS_LEN);
    char bufRecv[MESS_LEN + 1] = {0};
    ssize_t nread = Read(fd, bufRecv, MESS_LEN);
    if (strncmp(bufRecv, "pong", 4) == 0){
    printf("Client recived message: %s\n", bufRecv);
    }
    else if(strncmp(bufRecv, "what", 4) == 0){
        printf("Server didn't understand the message\n");
    }
    else if(strncmp(bufRecv, "bye", 3) == 0){
        printf("Server said goodbye\n");
    }

    close(fd);
}