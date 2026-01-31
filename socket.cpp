#include<stdio.h>
#include <string.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <netinet/in.h>

static void do_something(int d) {
    char read_buf[64] = {};
    ssize_t n = read(d, read_buf, sizeof(read_buf) - 1);
    if(n < 0) {
        printf(" read() error");
        return;
    }
    printf("client says: %s\n", read_buf);

    char wbuf[] = "world";
    write(d, wbuf, strlen(wbuf));
}

int main() {
    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5555);
    addr.sin_addr.s_addr = htonl(0);

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    
    int b = bind(fd, (const sockaddr *) &addr, sizeof(addr));
    b = listen(fd, 10);
    if(b) { printf("listen()");}

    while(1) {
        struct sockaddr_in client_addr = {};
        socklen_t addrlen = sizeof(client_addr);
        int d = accept(fd, (struct sockaddr *)&client_addr, &addrlen);
        if(d < 0 ) continue;

        do_something(d);
    }

    printf("%d %d",fd, b);
    
}