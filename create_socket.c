// Step 1 includes including necessary headers
#include <sys/socket.h>  // For socket(), connect(), bind(), listen(), accept()
#include <stdio.h>       // For printf(), perror()

// So For Now we are choosing AF_Local as domain
// TCP for domain
// and 0 for protocol

// int sockfd = createSocket(AF_INET, SOCK_STREAM, 0);
int createSocket(int domain = AF_INET, int type = SOCK_STREAM, int protocol= 0){
    int sockfd = socket(domain, type, protocol);
    // Now we need to check for errors
    if(sockfd<0){
        perror("Socket Creation Failed");
        return -1;
    }
    return sockfd;
}
