# EC700_Epoch3 malWALL


## Important Programs

Source code is found in Epoch3-Shared

### libwrapper-bind9getaddresses.c/.so   &   libwrapper-getaddrinfo.c/.so
Programs to preloaded by LD_PRELOAD or ld.so.preload

### firewallflush.sh
Script to flush all the rules from iptables and ip6tables, resetting the system

### firewallconfig.sh
Script that should be run with sudo to configure the firewall rules to block all outbound traffic as by default except those going through port 53 or port 22 (to allow for DNS queries and SSH)

### goodprogram.py / badprogram.py
Programs to test python socket methods using a hostname or IP address respectively

### addIPV4rule.c / addIPV6rule.c
Programs that run as root that adds an IPv4 address or IPv6 address taken through command line arguments to iptables/ip6tables respectively.  


### goodprogram.c / badprogram.c
Programs that call ResolveHostname() through sd_bus_call_method() by using a hostname and an IP address respectively.
