
package UserForm;
require Exporter;
@ISA = qw(Exporter);
@EXPORT = qw(smCreateAllUserForm smUserApply smAddControls);
use smBase;

sub smCreateAllUserForm {
    my $form = pmCreateUserForm('test');
    # $form->addCell('cell', 0, 0);
    # $form->addLayer('layer', 1, 0);
    # $Form::test->show();
    $data{'test'} = $form;
}

sub smUserApply {
    my $name = shift;
    my $lib = shift;
    my $cv = $data{$name}->controlValue('cell');
    printf("%s,%u,%s\n", $name, $lib, $cv);
}

sub smAddControls {
    my $name = shift;
    $data{$name}->addCellSelection('cell', 0, 0);
    $data{$name}->addLayerSelection('layer', 1, 0);
}

1;