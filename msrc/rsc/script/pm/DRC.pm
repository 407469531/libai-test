
package DRC;
use smBase;

sub registerDrcRule {
    my $fname = shift;
    my $rule = drGetRule($fname);
    ${$fname} = $rule;
}

1;
