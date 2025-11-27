#pragma once

#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

struct sockaddr_in* createAddres(char* ip, int port);