#ifndef CHECK_H_
#define CHECK_H_

int connect_to_host(struct addrinfo *addr_i);
void get_address_info(const char *input_service);
void print_address(int family, struct sockaddr *addr);

#endif // CHECK_H_
