#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include "check.h"

int main(int argc, char *argv[])
{
        struct in_addr addr;
        const char *input_service;

        /* Get service from stdin */
        if(argc != 2){
                /* XXX: Just ask for it again */
                puts("Error: Invalid input - See -usage");
                printf("Argc = %d", argc);
                exit(EXIT_FAILURE);
        }
        else if(strcmp(argv[1], "-u") == 0 || strcmp(argv[1], "-usage") == 0)
        {
                puts("Usage function here");
                exit(EXIT_FAILURE);
        }
        else{
                /* Get the value */
                input_service = argv[1];
                get_address(input_service);
        }

        /* Send dot notation addr to binary
        if(inet_pton(AF_INET, ip_addr, &addr) == 0){
                puts("Error: Invalid address");
                exit(EXIT_FAILURE);
        }

        connect_to_host(addr);

        */

        exit(EXIT_SUCCESS);
}

void get_address(const char *input_service)
{
        struct addrinfo hints, *result, *p;
        int status;
        char pres_ip[INET6_ADDRSTRLEN];

        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC; /* ipv4 || ipv6 */
        hints.ai_socktype = SOCK_STREAM;

        if((status = getaddrinfo(input_service, NULL, &hints, &result)) != 0){
                puts("Error: Could not get address info");
                exit(EXIT_FAILURE);
        }

        printf("IP Addresses for %s: \n\n", input_service);

        for(p = result; p != NULL; p = p->ai_next){
                char *ipver;
                void *address;

                /* Get the address */
                if(p->ai_family == AF_INET){
                        /* ipv4 */
                        struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
                        address = &(ipv4->sin_addr);
                        connect_to_host(address, p->ai_family);
                }
                else{
                        /* ipv6 */
                        struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
                        address = &(ipv6->sin6_addr);
                        connect_to_host(address, p->ai_family);
                }
        }

        freeaddrinfo(result);
}
