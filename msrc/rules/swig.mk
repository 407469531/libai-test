######################################################
##
## Copyright 2022 SMiT. All rights reserved.
##
## This file of part of the unified DB project
##
######################################################
SRCRULESPATH = $(shell cat ../../srcpath.file)
include $(SRCRULESPATH)/src/rules/global.mk
PUBLISHINCLUDE	:= -I../../include
ifeq ("$(tcl)","1")
# Makefile of build swig
OBJ_TARGET 	:= smBase_tcl_wrap.o smDB_tcl_wrap.o
MASK_TARGET 	:= smMask_tcl_wrap.o

# static module swig targets
%.o: %.cc
	echo "  -->$(notdir $(CC)) $(OPTFLAG) $(notdir $<)"
	$(CC) -c -fpermissive $(OPTFLAG) $(CCFLAGS) -fno-strict-aliasing \
		$(PUBLISHINCLUDE) $(LIBINCLUDES) $(PERLINCLUDES) -o $@ $<

%_tcl_wrap.cc: %.i
	$(SWIG) -wall -w472 -w401 -w314 -w303 -I.. $(SWIGINCLUDES) -O -tcl -c++ -o $@ $<

all: $(OBJ_TARGET)

mask: $(MASK_TARGET)

smDB.i:  $(addprefix ../, $(addsuffix .i, $(DB_PKGS))) ../ut.tm ../dmTcl.tm ../dfTcl.tm
	echo "  -->build smDB.i"
	echo "%module smDB" > $@
	echo "%nodefaultctor;" >> $@
	echo "%nodefaultdtor;" >> $@
	echo "%feature(\"notabstract\");" >> $@
	echo "%include \"ut.tm\"" >> $@;
	echo "%include \"dmTcl.tm\"" >> $@;
	echo "%include \"dfTcl.tm\"" >> $@;
	for pkg in $(DB_PKGS); do \
		echo "%include \"$$pkg.i\"" >> $@; \
	done

smBase.i:  $(addprefix ../, $(addsuffix .i, $(BASE_PKGS))) ../pmTcl.tm ../drTcl.tm
	echo "  -->build smBase.i"
	echo "%module smBase" > $@
	echo "%nodefaultctor;" >> $@
	echo "%nodefaultdtor;" >> $@
	echo "%feature(\"notabstract\");" >> $@
	echo "%include \"pmTcl.tm\"" >> $@;
	echo "%include \"drTcl.tm\"" >> $@;
	for pkg in $(BASE_PKGS); do \
		echo "%include \"$$pkg.i\"" >> $@; \
	done

smMinimal.i:  $(addprefix ../, $(addsuffix .i, $(MINIMAL_PKGS)))
	echo "  -->build smMinimal.i"
	echo "%module smMinimal" > $@
	echo "%nodefaultctor;" >> $@
	echo "%nodefaultdtor;" >> $@
	echo "%feature(\"notabstract\");" >> $@
	for pkg in $(MINIMAL_PKGS); do \
		echo "%include \"$$pkg.i\"" >> $@; \
	done

smMask.i:  $(addprefix ../, $(addsuffix .i, $(MASK_PKGS))) ../ut.tm ../dmTcl.tm ../pmTcl.tm ../drTcl.tm
	echo "  -->build smMask.i"
	echo "%module smMask" > $@
	echo "%nodefaultctor;" >> $@
	echo "%nodefaultdtor;" >> $@
	echo "%feature(\"notabstract\");" >> $@
	echo "%include \"ut.tm\"" >> $@;
	echo "%include \"dmTcl.tm\"" >> $@;
	echo "%include \"pmTcl.tm\"" >> $@;
	echo "%include \"drTcl.tm\"" >> $@;
	for pkg in $(MASK_PKGS); do \
		echo "%include \"$$pkg.i\"" >> $@; \
	done
else
# Makefile of build swig

OBJ_TARGET 	:= smBase_perl_wrap.o smDB_perl_wrap.o
MASK_TARGET	:= smMask_perl_wrap.o

# static module swig targets
%.o: %.cc
	echo "  -->$(notdir $(CC)) $(OPTFLAG) $(notdir $<)"
	$(CC) -c -fpermissive $(OPTFLAG) $(CCFLAGS) -fno-strict-aliasing \
		$(PUBLISHINCLUDE) $(LIBINCLUDES) $(PERLINCLUDES) -o $@ $<

%_perl_wrap.cc: %.i
	$(SWIG) -wall -w472 -w401 -w314 -w303 -I.. $(SWIGINCLUDES) -O -perl5 -exportall \
		-compat -static -c++ -o $@ $<

all: $(OBJ_TARGET)

mask: $(MASK_TARGET)

smDB.i:  $(addprefix ../, $(addsuffix .i, $(DB_PKGS))) ../ut.tm ../dm.tm ../df.tm
	echo "  -->build smDB.i"
	echo "%module smDB" > $@
	echo "%nodefaultctor;" >> $@
	echo "%nodefaultdtor;" >> $@
	echo "%feature(\"notabstract\");" >> $@
	echo "%include \"ut.tm\"" >> $@;
	echo "%include \"dm.tm\"" >> $@;
	echo "%include \"df.tm\"" >> $@;
	for pkg in $(DB_PKGS); do \
		echo "%include \"$$pkg.i\"" >> $@; \
	done

smBase.i:  $(addprefix ../, $(addsuffix .i, $(BASE_PKGS))) ../pm.tm ../dr.tm
	echo "  -->build smBase.i"
	echo "%module smBase" > $@
	echo "%nodefaultctor;" >> $@
	echo "%nodefaultdtor;" >> $@
	echo "%feature(\"notabstract\");" >> $@
	echo "%include \"pm.tm\"" >> $@;
	echo "%include \"dr.tm\"" >> $@;
	for pkg in $(BASE_PKGS); do \
		echo "%include \"$$pkg.i\"" >> $@; \
	done

smMinimal.i:  $(addprefix ../, $(addsuffix .i, $(MINIMAL_PKGS)))
	echo "  -->build smMinimal.i"
	echo "%module smMinimal" > $@
	echo "%nodefaultctor;" >> $@
	echo "%nodefaultdtor;" >> $@
	echo "%feature(\"notabstract\");" >> $@
	for pkg in $(MINIMAL_PKGS); do \
		echo "%include \"$$pkg.i\"" >> $@; \
	done

smMask.i:  $(addprefix ../, $(addsuffix .i, $(MASK_PKGS))) ../ut.tm ../dm.tm ../pm.tm
	echo "  -->build smMask.i"
	echo "%module smMask" > $@
	echo "%nodefaultctor;" >> $@
	echo "%nodefaultdtor;" >> $@
	echo "%feature(\"notabstract\");" >> $@
	echo "%include \"ut.tm\"" >> $@;
	echo "%include \"dm.tm\"" >> $@;
	echo "%include \"pm.tm\"" >> $@;
	for pkg in $(MASK_PKGS); do \
		echo "%include \"$$pkg.i\"" >> $@; \
	done
endif
