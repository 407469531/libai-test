
package Form;
use smBase;

sub registerForm {
    my $fname = shift;
    my $form = pmGetForm($fname);
    ${$fname} = $form;    
}
            
1;
