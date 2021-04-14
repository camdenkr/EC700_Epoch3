_#!/bin/bash


system_stap="/usr/bin/stap"

_getaddrInfo () {
  /usr/bin/stap -e 'probe process("/usr/lib/libc.so.6").function("getaddrinfo")
{
  printf("| %-15s| %-7d| %-35s |\n", execname(), pid(), kernel_string(pointer_arg(1)))
}'
}

echo ""
printf "| %-15s| %-7s| %-35s |\n" "Process" "PID" "Destination Name"
echo "|----------------|--------|-------------------------------------|"


while true ; do
  _getaddrInfo
done
