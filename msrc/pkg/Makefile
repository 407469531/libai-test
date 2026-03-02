# Makefile
# .SILENT:

include ../rules/global.mk

# all sub directory are target
PKGTARGETS		:= $(addprefix target_, $(subst /.,, $(wildcard */.)))

SWIGBUILDROOT 	= $(OUTPATH2)/build/swig
NEEDDIRS		:= $(shell $(MKDIR) -p $(SWIGBUILDROOT)/obj)

OPT_TARGETS		= publish optimize_pkgs optimize_swig
DBG_TARGETS		= publish debug_pkgs debug_swig
PRO_TARGETS		= publish profiler_pkgs optimize_swig

ifeq ($(origin PARALLEL_JOBS), undefined)
	PARALLEL_JOBS 	= 32
endif

all: optimize

help:
	echo "make (help|debug|optimize|clean)"
	echo "help:			print out help message"	
	echo "debug:		compile with -g"
	echo "optimize:		compile with -O3"
	echo "pkgs:			$(PKGTARGETS)"
	echo "clean:		deep clean all packages"
	echo "clean_all:	clean all build file & cache"

# rules
$(PKGTARGETS):
	echo ">>>Make $(WHAT) $(subst target_,, $@) ..."
	$(MAKE) $(WHAT) -C $(subst target_,, $@)

clean: 
	$(MAKE) WHAT=deep_clean $(PKGTARGETS)
	$(RM) -rf $(SWIGBUILDROOT)

clean_all: clean
	$(CCACHE) -C

publish: 
	$(MAKE) -j $(PARALLEL_JOBS) WHAT=publish $(PKGTARGETS)


optimize_pkgs:
	$(MAKE) -j $(PARALLEL_JOBS) WHAT=optimize $(PKGTARGETS)

profiler_pkgs:
	$(MAKE) -j $(PARALLEL_JOBS) WHAT=profiler $(PKGTARGETS)

debug_pkgs:
	$(MAKE) -j $(PARALLEL_JOBS) WHAT=debug $(PKGTARGETS)


optimize_swig:
	$(MAKE) -j $(PARALLEL_JOBS) OPTFLAG=-O3 -f $(SRCPATH)/rules/swig.mk -C $(SWIGBUILDROOT)/obj

debug_swig:
	$(MAKE) -j $(PARALLEL_JOBS) OPTFLAG=-g -f $(SRCPATH)/rules/swig.mk -C $(SWIGBUILDROOT)/obj


optimize: $(OPT_TARGETS)

profiler: $(PRO_TARGETS)

debug: $(DBG_TARGETS)
