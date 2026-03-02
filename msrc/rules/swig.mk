SRCRULESPATH = $(shell cat ../../srcpath.file)
include $(SRCRULESPATH)/msrc/rules/global.mk
PUBLISHINCLUDE	:= -I../../include

# Makefile of build swig
OBJ_TARGET 	:= smBase_perl_wrap.o

# static module swig targets
%.o: %.cc
	echo "  -->$(notdir $(CC)) $(OPTFLAG) $(notdir $<)"
	$(CC) -c -fpermissive $(OPTFLAG) $(CCFLAGS) -fno-strict-aliasing \
		$(PUBLISHINCLUDE) $(LIBINCLUDES) $(PERLINCLUDES) -o $@ $<

%_perl_wrap.cc: %.i
	$(SWIG) -wall -w472 -w401 -w314 -w303 -I.. $(SWIGINCLUDES) -O -perl5 -exportall \
		-compat -static -c++ -o $@ $<

all: $(OBJ_TARGET)

smBase.i:  $(addprefix ../, $(addsuffix .i, $(BASE_PKGS)))
	echo "  -->build smBase.i"
	echo "%module smBase" > $@
	echo "%nodefaultctor;" >> $@
	echo "%nodefaultdtor;" >> $@
	echo "%feature(\"notabstract\");" >> $@
	for pkg in $(BASE_PKGS); do \
		echo "%include \"$$pkg.i\"" >> $@; \
	done
