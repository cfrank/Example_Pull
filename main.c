#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
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
                get_address_info(input_service);
        }

        exit(EXIT_SUCCESS);
}

void get_address_info(const char *input_service)
{
        struct addrinfo hints, *result, *p;
        int status;
        char pres_ip[INET6_ADDRSTRLEN];

        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC; /* ipv4 || ipv6 */
        hints.ai_socktype = SOCK_STREAM;

        if((status = getaddrinfo(input_service, "80", &hints, &result)) != 0){
                puts("Error: Could not get address info");
                exit(EXIT_FAILURE);
        }

        printf("IP Addresses for %s: \n\n", input_service);

        for(p = result; p != NULL; p = p->ai_next){
                print_address(p->ai_family, p->ai_addr);
                connect_to_host(p);
        }

        freeaddrinfo(result);
}

void print_address(int family, struct sockaddr *addr)
{
        char pres_ip[INET6_ADDRSTRLEN];
        void *address;

        /* Get the presentational value of the IP */
        if(family == AF_INET){
                struct sockaddr_in *ipv4 = (struct sockaddr_in *)addr;
                address = &(ipv4->sin_addr);
        }
        else{
                struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)addr;
                address = &(ipv6->sin6_addr);
        }

        inet_ntop(family, address, pres_ip, sizeof(pres_ip));
        printf("%s\n", pres_ip);
}