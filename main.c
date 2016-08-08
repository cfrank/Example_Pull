#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "check.h"

int main()
{
        struct in_addr addr;
        const char *ip_addr = "127.0.0.1";

        /* Send dot notation addr to binary */
        if(inet_pton(AF_INET, ip_addr, &addr) == 0){
                puts("Error: Invalid address");
                exit(EXIT_FAILURE);
        }

        connect_to_host(addr);

        exit(EXIT_SUCCESS);
}
