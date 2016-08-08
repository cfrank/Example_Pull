#include <arpa/inet.h>
#include <stdio.h>

int connect_to_host(struct in_addr addr_value)
{
        printf("%s\n", inet_ntoa(addr_value));
        return 1;
}
