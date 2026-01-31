#include<stdio.h>
#include <string.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <netinet/in.h>

int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0) {
        printf("socket()");
    }

    struct sockaddr_in addr = {};

    addr.sin_family = AF_INET;
    addr.sin_port = ntohs(5555);
    addr.sin_addr.s_addr = ntohl(INADDR_LOOPBACK);
    int d = connect(fd, (const sockaddr *)&addr, sizeof(addr));

    if(d) printf("connect");

    char msg[] = "hello";
    write(fd, msg, strlen(msg));

    char read_buf[64] = {};
    ssize_t n  = read(fd, read_buf, sizeof(read_buf));
    if(n < 0) {
        printf("read");
    }
    printf("server says: %s\n", read_buf);
    close(fd);
}