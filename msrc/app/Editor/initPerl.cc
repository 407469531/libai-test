/******************************************************
**
** Copyright 2022 SMIT. All rights reserved.
**
** This file of part of the unified DB project
**
******************************************************/
#ifdef TCL
#include <tcl.h>
#include <string>
#include "libpl_api.h"

using namespace std;
extern Tcl_Interp *my_tcl;
extern string  peResourcePath(const char* path);
extern "C" int Smbase_Init(Tcl_Interp* interp);
extern "C" int Smdb_Init(Tcl_Interp* interp);
void initPerl()
{
    Tcl_Init(my_tcl);
    if (Smdb_Init(my_tcl) != TCL_OK) {
        const char* error = Tcl_GetStringResult(my_tcl);
        fprintf(stderr, "Init script error: %s\n", error);
        Tcl_DeleteInterp(my_tcl);
        exit(EXIT_FAILURE);
    }
    if (Smbase_Init(my_tcl) != TCL_OK) {
        const char* error = Tcl_GetStringResult(my_tcl);
        fprintf(stderr, "Init script error: %s\n", error);
        Tcl_DeleteInterp(my_tcl);
        exit(EXIT_FAILURE);
    }
    string path = "source " + peResourcePath("/etc/rc/pm/initTcl.tcl"); 
    plEval(path.c_str());
    
}
#else
#include <EXTERN.h>
#include <perl.h>

// init perl related, call by plApi.cc

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
#endif
