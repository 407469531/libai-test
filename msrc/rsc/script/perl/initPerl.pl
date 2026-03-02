# initialize perl searching path
# use lib "$ENV{SM_HOME}/3rdParty/perl5.10.1";
use lib "$ENV{SM_HOME}/etc/public/psh-1.9.01";
use lib "$ENV{SM_HOME}/etc/rc/perl";
use lib "$ENV{SM_HOME}/etc/rc/pm";

# initialize perl shell
require "initPsh.pl";

# recover original shell setting, for launch xterm
$ENV{'SHELL'} = $Psh::old_shell;

