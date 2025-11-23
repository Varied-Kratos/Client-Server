#include "Error.h"

int Socket(int domain, int type, int protocol){
    int result = socket(domain, type, protocol);
    if(result == -1){
        perror("The socket can't be created");
        exit(EXIT_FAILURE);
    }
    return result;
}


void Bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen){
    int result = bind(sockfd, addr, addrlen);
    if(result == -1){
        perror("Binding cannot be performed");
        exit(EXIT_FAILURE);
    }
}

void Listen(int sockfd, int backlog){
    int result = listen(sockfd, backlog);
    if(result == -1){
        perror("Listening can't be perfomed");
        exit(EXIT_FAILURE);
    }
}

int Accept(int sockfd, struct sockaddr* adr, socklen_t* adrlen){
    int res = accept(sockfd, adr, adrlen);
    if(res == -1){
        perror("Accepting can't be perfomed");
        exit(EXIT_FAILURE);
    }
    return res;
}

ssize_t Read(int fd, char* str, size_t len_mess){
    ssize_t result = read(fd, str, len_mess) ;
    if(result == -1){
        perror("Reading can't be perfomed");
        exit(EXIT_FAILURE);
    }
    if(result == 0){
        printf("end of file\n");
    }
    return result;
}


void Write(int fd,const char* str, int strlen){
    ssize_t result = write(fd, str, strlen);
    if(result == -1){
        perror("Writing can't be perfomed");
        exit(EXIT_FAILURE);
    }
}

void Connect(int socket, const struct sockaddr *address, socklen_t address_len){
    int res = connect(socket, address, address_len);
    if (res == -1){
        perror("Connection can't be perfomed");
        exit(EXIT_FAILURE);
    }
}

void Inet_pton(int af, const char *src, void *dst){
    int res = inet_pton(af, src, dst);

    if (res == 0){
        printf("inet_pton failed: the address was not parseable in the"
        " specified address family\n");
        exit(EXIT_FAILURE);
    }
    if (res == -1){
        perror("inet_pton failed");
        exit(EXIT_FAILURE);
    }
}