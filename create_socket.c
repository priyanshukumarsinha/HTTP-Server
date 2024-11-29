
// So For Now we are choosing AF_Local as domain
// TCP for domain
// and 0 for protocol

// int sockfd = createSocket(AF_INET, SOCK_STREAM, 0);
int createSocket(int domain, int type, int protocol){
    int sockfd = socket(domain, type, protocol);
    // Now we need to check for errors
    if(sockfd<0){
        perror("Socket Creation Failed");
        return -1;
    }

    printf("Socket created Successfully: %d\n", sockfd);
    return sockfd;
}
