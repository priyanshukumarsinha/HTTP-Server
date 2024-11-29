#include <netinet/in.h>  // For struct sockaddr_in, htons, INADDR_ANY
#include <string.h>       // For memset
#include <arpa/inet.h>    // For INADDR_ANY

/**
 * @brief Creates and initializes a sockaddr_in structure with specified parameters.
 * 
 * This function sets up a socket address structure for IPv4 (or any other specified 
 * address family), with a given port number and IP address (default is INADDR_ANY).
 * The resulting structure can then be used for binding a socket.
 * 
 * @param addr_family   The address family (default: AF_INET for IPv4).
 * @param PORT          The port number (default: 8080).
 * @param any_address   The IP address (default: INADDR_ANY, which means binding to all interfaces).
 * 
 * @return struct sockaddr_in  The initialized sockaddr_in structure.
 */

struct sockaddr_in defineAddress(int addr_family = AF_INET, int PORT = 8080, in_addr_t any_address = INADDR_ANY){
    struct sockaddr_in server_addr;

    memset(&server_addr, 0, sizeof(server_addr)); //This clears the structure

    server_addr.sin_family = addr_family;           
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = any_address; 

    printf("Adresses Structure defined successfully \n");

    return server_addr;
}

