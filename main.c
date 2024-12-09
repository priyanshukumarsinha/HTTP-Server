#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>


#include "HTTP_Server.h"

int main() {
	// initiate HTTP_Server
	HTTP_Server http_server;
	init_server(&http_server, 6969);

    return 0;
}