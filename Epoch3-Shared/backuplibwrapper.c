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

int validate_number(char *str) {
   while (*str) {
      if(!isdigit(*str)){ //if the character is not a number, return
         //false
         return 0;
      }
      str++; //point to next character
   }
   return 1;
}

int validate_ip(char *ip) { //check whether the IP is valid or not
   int i, num, dots = 0;
   char *ptr;
   if (ip == NULL)
      return 0;
      ptr = strtok(ip, "."); //cut the string using dor delimiter
      if (ptr == NULL)
         return 0;
   while (ptr) {
      if (!validate_number(ptr)) //check whether the sub string is
         //holding only number or not
         return 0;
         num = atoi(ptr); //convert substring to number
         if (num >= 0 && num <= 255) {
            ptr = strtok(NULL, "."); //cut the next part of the string
            if (ptr != NULL)
               dots++; //increase the dot count
         } else
            return 0;
    }
    if (dots != 3) //if the number of dots are not 3, return false
       return 0;
      return 1;
}
char * string_copy( const char *from, char *to ) 
{
    for ( char *p = to; ( *p = *from ) != '\0'; ++p, ++from )
    {
        ;
    }

    return to;
}


static int (*real_getaddrinfo)(const char *node, const char *service,
  const struct addrinfo *hints, struct addrinfo **res);

int getaddrinfo(const char *node, const char *service,
  const struct addrinfo *hints, struct addrinfo **res)
{
	    int sock;
	    int n;
  struct addrinfo replacement_hints;
  memset(&replacement_hints, 0, sizeof(struct addrinfo));
  memcpy(&replacement_hints, hints, sizeof(struct addrinfo));
  //replacement_hints.ai_family = AF_INET; 
  //Stackoverflow
  //replacement_hints.ai_family = PF_UNSPEC;
  //replacement_hints.ai_socktype = SOCK_STREAM;
  //replacement_hints.ai_flags |= AI_CANONNAME;

  real_getaddrinfo = dlsym(RTLD_NEXT, "getaddrinfo");
  printf("Hello to the custom get address info \n");
  //char *copied=string_copy(node,copied); 
  //if(validate_ip(copied)){
  //	  printf("Get the hell outta here malware\n");
 //	  return 0;
  //	}
  //else
  int result=real_getaddrinfo(node, service, &replacement_hints,res);
  real_getaddrinfo(node, service, &replacement_hints,&res);
  //result;
  struct addrinfo *rp;
  printf("Going inside \n");
  void* ptr;
    char addrstr[100]={0};

   char command[50]={0};
   char local_ip[100]="127.0.1.1";
  for (rp = res; rp != NULL; rp = rp->ai_next) {
 	switch (rp->ai_family)
     {
     case AF_INET:
        ptr = &((struct sockaddr_in*) rp->ai_addr)->sin_addr;
        inet_ntop(rp->ai_family, ptr, addrstr, 100);
        break;
     case AF_INET6:
        ptr = &((struct sockaddr_in6*) rp->ai_addr)->sin6_addr;
        inet_ntop(rp->ai_family, ptr, addrstr, 100);
        break;          
     }
	strcat(command,"bash addrule.sh");
	printf("Address string %s \n",addrstr);
	//strcat(command,addrstr);
	printf("Issuing bash script %s \n",command);
  }
if(strcmp(addrstr,local_ip)==0)
	printf("Was local host anyways \n");
else
{
	system("./addrule.sh");
	printf("Not localhost so proceed");
}
  return result; 
}
