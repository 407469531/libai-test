#include <EXTERN.h>
#include <perl.h>

extern PerlInterpreter *my_perl;

EXTERN_C void boot_DynaLoader(pTHX_ CV* cv);
EXTERN_C void boot_smBase(pTHX_ CV* cv);
EXTERN_C void boot_smDB(pTHX_ CV* cv);

void initPerl()
{
    const char *file = __FILE__;
    /* DynaLoader needed for the rest*/
    newXS("DynaLoader::boot_DynaLoader", boot_DynaLoader, file);
    newXS("smBasec::boot_smBase", boot_smBase, file);
    newXS("smDBc::boot_smDB", boot_smDB, file);
}

