#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>

int connect_to_host(struct in_addr addr_value)
{
        const unsigned short PORT = 80;
        const unsigned int REPLY_SIZE = 6000;

        int socket_endp;
        struct sockaddr_in server;
        char pres_ip[INET_ADDRSTRLEN];
        char *message;
        char server_reply[REPLY_SIZE];
        int buf_size;

        /* Build the socket end point */
        socket_endp = socket(AF_INET, SOCK_STREAM, 0);
        if(socket_endp == -1){
                puts("Error: Could not create socket");
                return -1;
        }

        /* Build up the address */
        server.sin_addr.s_addr = addr_value.s_addr;
        server.sin_family = AF_INET;
        server.sin_port = htons(PORT);
        memset(&server.sin_zero, 0, sizeof(server.sin_zero));

        /* Get the presentation version of the ip */
        inet_ntop(AF_INET, &(server.sin_addr.s_addr), pres_ip, INET_ADDRSTRLEN);

        printf("Connecting to %s...\n", pres_ip);

        /* Connect to the remote server */
        if(connect(socket_endp, (struct sockaddr *)&server, sizeof(server)) > 0){
                puts("Error: Connection error");
                return -1;
        }

        puts("Connected.\n");

        /* Send data */
        message = "GET /check/ HTTP/1.1\r\nHost: xor.build\r\n\r\n";
        if(send(socket_endp, message, strlen(message), 0) < 0){
                puts("Error: Sending data failed");
                return -1;
        }

        puts("Data Sent\n");

        /* Receive the data */
        if((buf_size = recv(socket_endp, server_reply, REPLY_SIZE, 0)) < 0){
                puts("Error: Receiving data failed");
                return -1;
        }

        server_reply[buf_size] = '\n';
        
        printf("Received %d bytes of data\n", buf_size);

        close(socket_endp);

        return 0;
}
