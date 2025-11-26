#include "util.h"


void* print_messages(void* arg){
    int sock_fd = *(int*) arg;
    char buffer[1024];
    while(1){
        
        ssize_t recieved_amount = recv(sock_fd, buffer, 1024, 0);
        if(recieved_amount > 0){
            buffer[recieved_amount] = 0;
            printf("%s\n", buffer);

            
        }
        if(recieved_amount < 0){
            break;
        }
        
    }
    close(sock_fd);
    free(arg);
    return NULL;
}

void start_listening_on_thread(int sock_fd){
   
    pthread_t thread;

    int* sock_fd_ptr = malloc(sizeof(int));
    *sock_fd_ptr = sock_fd;
    
    pthread_create(&thread,NULL, print_messages, sock_fd_ptr);
    

    
}

int main(){
    char* ip = "127.0.0.1";
    int socket_db = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in* addres = createAddres(ip, 23823);


    

    int res = connect(socket_db,(struct sockaddr*) addres, sizeof(*addres));
    if(res == 0){
        printf("Connection was successful\n");
    }


    char* name = NULL;
    size_t name_size = 0;

    printf("Enter your name:\n");
    ssize_t name_count = getline(&name, &name_size, stdin);
    name[name_count-1] = 0;
    char* line = NULL;
    size_t line_size = 0;

    printf("Type your message(type stop to exit): \n");


    

    start_listening_on_thread(socket_db);

    char buffer[1024];
    while(1){

        
        ssize_t char_count = getline(&line, &line_size, stdin);
        line[char_count-1]=0;
        sprintf(buffer,"%s: %s", name, line);
        if(char_count > 0){
            if(strcmp(line, "stop") == 0){
                break;
            }
            ssize_t amount_was_sent = send(socket_db, buffer, strlen(buffer), 0);
        }

        
    }
    free(name);
    free(line);
    free(addres);
    

    close(socket_db);
    
    
    
    
}