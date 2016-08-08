#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main()
{
        struct in_addr addr;
        const char *ip_addr = "192dddh.1.1";

        if(inet_aton(ip_addr, &addr) == 0){
                puts("Error: Invalid address");
                exit(EXIT_FAILURE);
        }

        printf("%s\n", inet_ntoa(addr));
        exit(EXIT_SUCCESS);
}
