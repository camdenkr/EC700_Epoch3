#include <regex.h>       
#include <stdlib.h>
int main(){
regex_t regex;

char msgbuf[100];


int reti = regcomp(&regex, "([0-9a-fA-F]{0,4}:){1,7}[0-9a-fA-F]{0,8}", 0);


if (reti) {
    printf("Could not compile regex\n");
    exit(1);
}

reti = regexec(&regex, "2001:db8:ffff:ffff:ffff:ffff:ffff", 0, NULL, 0);

if (!reti) {
    puts("Match");
}
else if (reti == REG_NOMATCH) {
    puts("No match");
}
else {
    regerror(reti, &regex, msgbuf, sizeof(msgbuf));
    printf("Regex match failed: %s\n", msgbuf);
    exit(1);
}

regfree(&regex);



}
