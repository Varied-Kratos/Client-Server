#ifndef ERROR_H
#define ERROR_H
#include <sys/socket.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define MESS_LEN 4

int Socket(int domain, int type, int protocol);
void Bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen);
void Listen(int sockfd, int backlog);
int Accept(int sockfd, struct sockaddr* adr, socklen_t* adrlen);
ssize_t Read(int fd, char* str, size_t len_mess);
void Write(int fd,const char* str, int strlen);
void Connect(int socket, const struct sockaddr *address, socklen_t address_len);
void Inet_pton(int af, const char *src, void *dst);
#endif 