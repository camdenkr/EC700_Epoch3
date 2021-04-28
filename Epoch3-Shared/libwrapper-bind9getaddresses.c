#ifndef BIND9_GETADDRESSES_H
#define BIND9_GETADDRESSES_H 1
#define _GNU_SOURCE

#include <dlfcn.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <arpa/inet.h>
#include <systemd/sd-bus.h>
#include <isc/types.h>
#include <isc/net.h>

static isc_result_t(*real_getaddresses_method)(const char *hostname, in_port_t port,
		isc_sockaddr_t *addrs, int addrsize, int *addrcount);

isc_result_t bind9_getaddresses(const char *hostname, in_port_t port,isc_sockaddr_t *addrs, int addrsize, int *addrcount)
{
printf("Hello Get Addresses \n");

real_getaddresses_method=dlsym(RTLD_NEXT,"sd_bus_call_method");
return real_getaddresses_method(hostname,port,addrs,addrsize,addrcount);
}

#endif /* BIND9_GETADDRESSES_H */
