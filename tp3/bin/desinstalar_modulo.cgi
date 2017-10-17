#!/usr/bin/perl -wT

use strict;
use CGI;
use CGI::Carp qw ( fatalsToBrowser );

my $cmd = "../desinstalar.sh";
system($cmd);

print "Location: modulos.cgi\n\n";