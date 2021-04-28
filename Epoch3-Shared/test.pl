#!/usr/bin/setuidperl
use strict;
use warnings;
$ENV{"PATH"} = "/bin/";
system("iptables -L");
