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
#include <unistd.h>

#define IPV4_exec "/home/Epoch3-Shared/addIPV4rule "
#define IPV6_exec "/home/Epoch3-Shared/addIPV6rule "
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

static int (*real_getaddrinfo)(const char *node, const char *service,
  const struct addrinfo *hints, struct addrinfo **res);

int getaddrinfo(const char *node, const char *service,
  const struct addrinfo *hints, struct addrinfo **res)
{
	printf("Node %s \n",node);
	printf("Service %s \n",service);
	printf("setting");
	//setuid(0);
//system("./wrapper");
	//setuid(0);
	    int sock;
	    int n;
  struct addrinfo replacement_hints;
  memset(&replacement_hints, 0, sizeof(struct addrinfo));
  memcpy(&replacement_hints, hints, sizeof(struct addrinfo));
  replacement_hints.ai_family = PF_UNSPEC; 
  //Stackoverflow
  //replacement_hints.ai_family = PF_UNSPEC;
  //replacement_hints.ai_socktype = SOCK_STREAM;
  //replacement_hints.ai_flags |= AI_CANONNAME;

  real_getaddrinfo = dlsym(RTLD_NEXT, "getaddrinfo");
  //printf("Hello to the custom get address info \n");
  char copied[50]={0};
  strcpy(copied,node); 
   char digitalocean_ip[100]={0};
   strcpy(digitalocean_ip,"167.99.0.42");
   char local_ip[100]={0};
   strcpy(local_ip,"127.0.1.1");
 int was_direct_ip=0;  
 if(strncmp(copied,local_ip,3)!=0)
 {
  	strcpy(copied,node); 
	 int version;
	 version=ip_version(copied);
  	if(version==4 || version==6)
	{
	     	printf("Get the hell outta here malware %s\n",copied);
 	return EBADE;
 	}
  else{
	printf("Not a direct IP %s \n",copied);
  }
 }
     	int result=real_getaddrinfo(node, service, &replacement_hints,res);
  
  //if(strncmp(addrstr,local_ip,3)==0)
  //	  return result;
  real_getaddrinfo(node, service, &replacement_hints,&res);
  //result;
  struct addrinfo *rp;
  printf("Going inside \n");
  void* ptr;
    char addrstr[100];
   char command[50];
  for (rp = res; rp != NULL; rp = rp->ai_next) {
 	switch (rp->ai_family)
     {
     case AF_INET:
	     strcpy(addrstr,"");
	     strcpy(command,"");
        ptr = &((struct sockaddr_in*) rp->ai_addr)->sin_addr;
        inet_ntop(rp->ai_family, ptr, addrstr, 100);
	strcat(command,IPV4_exec);
	printf("Address string%s\n",addrstr);
	strcat(command,addrstr);
        break;
     case AF_INET6:
         strcpy(addrstr,"");
         strcpy(command,"");
	strcpy(addrstr,"");
	ptr = &((struct sockaddr_in6*) rp->ai_addr)->sin6_addr;
        inet_ntop(rp->ai_family, ptr, addrstr, 100);
	strcat(command,IPV6_exec);
	printf("Hmm IPV6?? %s\n",addrstr);
	strcat(command,addrstr);
	break;          
     }

	if(strncmp(addrstr,local_ip,3)==0){
	printf("\nWas local host anyways \n");
}
else{
	printf("\nCmp rslt %d",strncmp(addrstr,local_ip,3));
	printf("\nNot local host so we going in");
	printf("\nIssuing bash script %s \n",command);
       	system(command);
}
}
//Issuing bash script ./addrule.sh 127.0.1.1./addrule.sh 127.0.1.1./addrule.sh 127.0.1.1
  return result; 
}
