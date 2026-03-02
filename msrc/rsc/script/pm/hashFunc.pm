
use v5.10;
package hashFunc;

require Exporter;
@ISA = qw(Exporter);
@EXPORT = qw(smLayoutCopy);

use smBase;

sub smLayoutCopy {
    my %hash = ('libId', -1, 'cell', "", 'x1', 0, 'y1', 0, 'x2', -1, 'y2', -1,
                'startDepth', 0, 'endDepth', 99, 'selMod', 0, 'preserveHierarchy', 0);

    my $parameter = shift;

    for my $k (keys %{$parameter}) {
        if($hash{$k} ne $parameter->{$k}) {
            $hash{$k} = $parameter->{$k};
        }
    }

    if ($hash{'libId'} < 0) {
        print "please input right libId\n";
        return -1;
    }
    
    my $box = new utBox($hash{'x1'}, $hash{'y1'}, $hash{'x2'}, $hash{'y2'});
    my $res = edLayoutCopyApi($hash{'libId'}, $hash{'cell'}, $box, $hash{'startDepth'},
                 $hash{'endDepth'}, $hash{'selMod'}, $hash{'preserveHierarchy'});
    return $res;
} 


1;