#include <stdio.h>
#include <string.h>
int main() {
	const char* a_domainName = "google.com";
struct addrinfo hints, * res;
  int errcode;
  char addrstr[100];
  void* ptr;


  errcode = getaddrinfo(a_domainName, NULL, &hints, &res);
  if (errcode != 0)
  {
     cout("getaddrinfo failed with error: " << errcode);
     WSACleanup();
     return "";
  }

  cout("Host: " << a_domainName);

  while (res)
  {
     switch (res->ai_family)
     {
     case AF_INET:
        ptr = &((struct sockaddr_in*) res->ai_addr)->sin_addr;
        inet_ntop(res->ai_family, ptr, addrstr, 100);
        break;
     case AF_INET6:
        ptr = &((struct sockaddr_in6*) res->ai_addr)->sin6_addr;
        inet_ntop(res->ai_family, ptr, addrstr, 100);
        break;          
     }

     // domain name IP is the 5th 
     cout("IPv" << (res->ai_family == PF_INET6 ? "6" : "4") << " address = " << addrstr)    

     res = res->ai_next;
  }

  printf("%s", addrstr); / / retuns wrong address as it interates past the domain name to the gateway ip
}
