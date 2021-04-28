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

#define IPV4_exec "/home/Epoch3-Shared/addIPV4rule "
#define IPV6_exec "/home/Epoch3-Shared/addIPV6rule "

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

static int(*real_sd_bus_call_method)(sd_bus *bus, const char *destination,
                              const char *path, const char *interface,
                              const char *member,
                              sd_bus_error *ret_error,
                              sd_bus_message **reply, const char *types,
                              ...);
int sd_bus_call_method(sd_bus *bus, const char *destination,
                              const char *path, const char *interface,
                              const char *member,
                              sd_bus_error *ret_error,
                              sd_bus_message **reply, const char *types,
                              ...)
{

	printf("Hello SD Bus call ?? \n");
	printf("Path %s \n",path);
	printf("Destination %s\n",destination);
	printf("Interface %s \n",interface);
	printf("Member %s \n",member);
	printf("Types %s \n",types);
	
	
	va_list valist;
   /* initialize valist for num number of arguments */
   	va_start(valist, 4);

  	int netinterface=va_arg(valist,int);
	const char* hostname=va_arg(valist,const char*);
	int family=va_arg(valist,int);
	unsigned int  flags=va_arg(valist, unsigned int);

  	printf("Arg1 %d \n",netinterface);
   	printf("Arg2 %s \n",hostname);
	   va_end(valist);
	//Pre-Filter 
	char expected[50]="ResolveHostname";
	char expected_small[50]="resolvehostname";

	char copiedmember[50]={0};
	strcpy(copiedmember,member);	
	
	
	//Direct IP Check 
	char copied[50]={0};
  strcpy(copied,hostname);
   char local_ip[100]={0};
   strcpy(local_ip,"127.0.1.1");

 if(strncmp(copied,local_ip,3)!=0)
 {
      	strcpy(copied,hostname);	 
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


	if(strcmp(copiedmember,expected)==0 || strcmp(copiedmember,expected_small)==0)
	{
		printf("HEre comes our Pre-processor since it's resolve host name time \n");
	}



	   real_sd_bus_call_method=dlsym(RTLD_NEXT,"sd_bus_call_method");

  	   int returnval=real_sd_bus_call_method(bus,destination,path,interface,member,ret_error,reply,types,netinterface,hostname,family,UINT64_C(0));//flags

	   printf("Return val %d \n",returnval);

	   real_sd_bus_call_method(bus,destination,path,interface,member,ret_error,&reply,types,netinterface,hostname,family,UINT64_C(0));
	           int r = sd_bus_message_enter_container(reply, 'a', "(iiay)");
	
	   for (;;) {
                char buf[INET6_ADDRSTRLEN];
                int ifindex, family;
                const void *data;
                size_t length;
		char command[50];
		strcpy(command,"");
                r = sd_bus_message_enter_container(reply, 'r', "iiay");
                if (r < 0)
                        printf("Custom failure");
                if (r == 0)  /* Reached end of array */
                        break;
                r = sd_bus_message_read(reply, "ii", &ifindex, &family);
                if (r < 0)
                	printf("Custom failure");
		r = sd_bus_message_read_array(reply, 'y', &data, &length);
                if (r < 0)
                        printf("Custom failure");
                r = sd_bus_message_exit_container(reply);
                if (r < 0)
                        printf("Custom failure");
		if(family==AF_INET)
		{
		strcat(command,IPV4_exec);
		}
		else if(family==AF_INET6)
		{
		strcat(command,IPV6_exec);
		}
		char *ip=inet_ntop(family, data, buf, sizeof(buf));
		strcat(command,ip);
                printf("Found IP address %s on interface %i.\n",ip, ifindex);
        	system(command);
	   }


	return returnval;
}

