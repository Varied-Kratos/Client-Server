#include "util.h"

struct sockaddr_in* createAddres(char* ip, int port){
    struct sockaddr_in* addres = malloc(sizeof(struct sockaddr_in));
    addres->sin_family = AF_INET;
    addres->sin_port = htons(port);
    if(strlen(ip) == 0){
        addres->sin_addr.s_addr = INADDR_ANY;
    }else{
        inet_pton(AF_INET, ip, &addres->sin_addr.s_addr);
    }
    return addres;

}