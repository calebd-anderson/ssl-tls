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
}
