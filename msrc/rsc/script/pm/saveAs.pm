
package saveAs;
require Exporter;
@ISA = qw(Exporter);
@EXPORT = qw(smSaveAs);
use smBase;

sub smSaveAs {
    #inital perl hash
    my %hash = ("libId", 0, "path", "", "format", "", "cell", "", "layerMap", "", "visibleOnly", 0, "emptyCell", 0, "unboundInstance", 1, "showHole", 0, "dbUU", 0, "scalingFactor", 1.0, "strictMode", 0);

    my $lookup = shift;

    for my $k (keys %{$lookup}) {
        if($hash{$k} ne $lookup->{$k}) {
            $hash{$k} = $lookup->{$k};
        }
    }

    edSaveAs($hash{'libId'}, $hash{'path'}, $hash{'format'}, $hash{'cell'}, $hash{'layerMap'}, $hash{'visibleOnly'}, $hash{'emptyCell'}, $hash{'unboundInstance'}, $hash{'showHole'}, $hash{'dbUU'}, $hash{'scalingFactor'}, $hash{'strictMode'});
}


1;
