#include "Error.h"

int main(){
    int fd = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(1234);
    Inet_pton(AF_INET, "127.0.0.1", &adr.sin_addr);
    Connect(fd, (struct sockaddr *) &adr, sizeof adr);
    while(1){   
        printf("Enter the message:\n");
        char bufSend[MESS_LEN] = {0};
        ssize_t input_len = Read(STDIN_FILENO, bufSend, MESS_LEN-1);
         if (input_len > 0 && bufSend[input_len - 1] == '\n') {
            bufSend[input_len - 1] = '\0';
            input_len--;
        }
        Write(fd, bufSend, input_len);
        char bufRecv[MESS_LEN + 1] = {0};
        ssize_t nread = Read(fd, bufRecv, MESS_LEN-1);
        bufRecv[nread] = '\0';
        if (strcmp(bufRecv, "pong") == 0){
            printf("Client recived message: %s\n", bufRecv);
        }
        else if(strcmp(bufRecv, "what") == 0){
            printf("Server didn't understand the message\n");
        }
        else if(strcmp(bufRecv, "bye") == 0){
            printf("Server said goodbye\n");
            break;
        }
    }
    close(fd);
}