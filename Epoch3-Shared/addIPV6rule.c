#include <unistd.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char * argv[]) 
{ 
	if (argc < 2 || argc > 2){
		printf("No argument provided or too many");
	}else if (sizeof(argv[1])/sizeof(argv[1][0]) > 15){ 
		printf("Argument too long");
	}else if (sizeof(argv[1])/sizeof(argv[1][0]) < 4){
		printf("Argument too short");
	}else{
        	setuid(0);
		//total length should be no greater than 47
		char first[96] = "ip6tables -I OUTPUT -d ";
		//char second[] = argv[1];
		char third[] = " -j ACCEPT";
		strcat(first, argv[1]);
		strcat(first, third);
        	system(first); 
		setuid(2);
	}
} 
