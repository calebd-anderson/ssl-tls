/**
* this test utility does simple (non-encrypted) HTTP.
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#else
#include <netdb.h>
#include <sys/socket.h>
#include <netlinet/in.h>
#include <unistd.h>
#endif // WIN32

/**
* Accept a well-formed URL (e.g. http://www.company.com/index.html) and return
* pointers to the host part and the path part. Note that this function
* modifies the uri itself as well. It returns 0 on success, -1 if the URL is
* found to be malformed in any way.
*/
int parse_url(char *uri, char **host, char **path) {
    char *pos;
    pos = strstr(uri, "//");
    if(!pos) {
        return -1;
    }
    *host = pos + 2;
    pos = strchr(*host, '/');
    if(!pos) {
        *path = NULL;
    } else {
        *pos = '\0';
        *path = pos + 1;
    }
    return 0;
}

#define HTTP_PORT   80

/**
* Simple command-line HTTP client.
*/
int main(int argc, char * argv[]) {
    int client_connection;
    char *host, *path;
    struct hostent *host_name;
    struct sockaddr_in host_address;
#ifdef WIN32
    WSADATA wsaData;
#endif // WIN32

    if(argc < 2) {
        fprintf(stderr, "Usage: %s: <URL>\n", argv[0]);
        return 1;
    }
    if(parse_url(argv[1], &host, &path) == -1) {
        fprintf(stderr, "Error - malformed URL '%s'.\n", argv[1]);
        return 1;
    }
    printf("Connecting to host '%s'\n", host);

    // Step 1: open a socket connection on http port with the destination host.
    #ifdef WIN32
        if(WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) {
            fprintf(stderr, "Error, unable to initialize winsock.\n");
            return 2;
        }
    #endif // WIN32

    client_connection = socket(PF_INET, SOCK_STREAM, 0);
    if(!client_connection) {
        perror("Unable to create local socket");
        return 2;
    }

    host_name = gethostbyname(host);
    if(!host_name) {
        perror("Error in name resolution");
        return 3;
    }

    host_address.sin_family = AF_INET;
    host_address.sin_port = htons(HTTP_PORT);
    memcpy(&host_address.sin_addr, host_name->h_addr_list[0], sizeof(struct in_addr));

    if(connect(client_connection, (struct sockaddr *) &host_address, sizeof(host_address)) == -1) {
        perror("Unable to connect to host");
        return 4;
    }

    printf("Retrieving document: '%s'\n", path);

    http_get(client_connection, path, host);

    display_result(client_connection);

    printf("shutting down.\n");

#ifdef WIN32
    if(closesocket(client_connection) == -1)
#else
    if(close(client_connection) == -1)
#endif // WIN32
    {
        perror("Error closing client connection");
        return 5;
    }
#ifdef WIN32
    WSACleanup();
#endif // WIN32
    return 0;
}
