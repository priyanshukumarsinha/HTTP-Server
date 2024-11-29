// Step 1 includes including necessary headers
#include <sys/socket.h>  // For socket(), connect(), bind(), listen(), accept()
#include <stdio.h>       // For printf(), perror()

// So For Now we are choosing AF_Local as domain
// TCP for domain
// and 0 for protocol

// int sockfd = createSocket(AF_LOCAL, SOCK_STREAM, 0);
int createSocket(int domain, int type, int protocol){
    int sockfd = socket(domain, type, protocol);
    // Now we need to check for errors
    if(sockfd<0){
        perror("Socket Creation Failed");
        return -1;
    }
    return sockfd;feat: add createSocket function for socket creation with error handling

- Implemented a reusable `createSocket` function to simplify socket creation.
- Added error handling with `perror` to log socket creation failures.
- Improved documentation for parameters, return values, and functionality.

}
