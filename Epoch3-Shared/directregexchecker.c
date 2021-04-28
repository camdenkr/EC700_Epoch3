#include <arpa/inet.h>
#include <stdio.h>

static int
ip_version(const char *src) {
    char buf[50];
    if (inet_pton(AF_INET, src, buf)) {
        return 4;
    } else if (inet_pton(AF_INET6, src, buf)) {
        return 6;
    }
    return -1;
}

int main(){
//printf("%d \n",ip_version("2a03:2880:f12c:183:face:b00c:0:25de"));
printf("%d \n",ip_version("www.google.com"));
}


