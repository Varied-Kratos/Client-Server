#include "util.h"


typedef struct AcceptedConnection{
    int accept_sock_fd;
    struct sockaddr_in adr;
    int error;
    int success;

}AcceptedConnection;

AcceptedConnection accepted_connections[10];
int accepted_connections_count = 0;


AcceptedConnection* acceptConnection(int server_fd){
    
    struct sockaddr_in client_ad;

    socklen_t size_client_ad = sizeof(struct sockaddr_in);

    int client_fd = accept(server_fd,(struct sockaddr*)&client_ad, &size_client_ad);

    AcceptedConnection* acc_conn = malloc(sizeof(AcceptedConnection));
    acc_conn->accept_sock_fd = client_fd;
    acc_conn->adr = client_ad;
    acc_conn->success = client_fd > 0;
    if(!acc_conn->success){
        acc_conn->error = client_fd;
    }
    return acc_conn;
}
void recieve_data_to_others(char* buffer, int sock_fd){
    for(int i = 0; i < accepted_connections_count; ++i){
        if(accepted_connections[i].accept_sock_fd != sock_fd){
            send(accepted_connections[i].accept_sock_fd, buffer, strlen(buffer), 0);
        }
    }
}
void* recieve_data(void* arg){
    int sock_fd = *(int*)arg;
    char buffer[1024];
    while(1){
        
        ssize_t recieved_amount = recv(sock_fd, buffer, 1024, 0);
        if(recieved_amount > 0){
            buffer[recieved_amount] = 0;
            printf("%s\n", buffer);

            recieve_data_to_others(buffer, sock_fd);
        }
        if(recieved_amount < 0){
            break;
        }
        
    }
    close(sock_fd);
    return NULL;
}

void recieve_data_on_different_threads(AcceptedConnection *clientConnectionn){
    pthread_t thread;
    
    
    int* sock_fd_ptr = malloc(sizeof(int));
    *sock_fd_ptr = clientConnectionn->accept_sock_fd;
    
    pthread_create(&thread, NULL, recieve_data, sock_fd_ptr);
    pthread_detach(thread);
}



void start_accept_connection(int server_fd){

    
    while(1){
        AcceptedConnection* clientConnection = acceptConnection(server_fd);
        accepted_connections[accepted_connections_count++] = *clientConnection;

        recieve_data_on_different_threads(clientConnection);
        free(clientConnection);
    }


}


int main(){

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in* serv_adr = createAddres("",23823);

    int res = bind(server_fd,(struct sockaddr*) serv_adr, sizeof(*serv_adr));

    if(res == 0){
        printf("The binding was successful\n");
    }

    int listen_res = listen(server_fd, 10);

    start_accept_connection(server_fd);
    
    
    
    
    shutdown(server_fd, SHUT_RDWR);
    

}