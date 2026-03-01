# Makefile
.SILENT:

include ../rules/global.mk

# all sub directory are target
PKGTARGETS		:= $(addprefix target_, $(subst /.,, $(wildcard */.)))
MINIMALTARGETS	:= $(addprefix minimaltgt_, $(MINIMAL_PKGS))
MASKTARGETS		:= $(addprefix masktgt_, $(MASK_PKGS))
UNIQUE_MASKTARGETS := $(sort $(MASKTARGETS))

SWIGBUILDROOT 	= $(OUTPATH2)/build/swig
NEEDDIRS		:= $(shell $(MKDIR) -p $(SWIGBUILDROOT)/obj)

SWIGAPIROOT		= ../../release_smdb

OPT_TARGETS		= publish optimize_pkgs optimize_swig
DBG_TARGETS		= publish debug_pkgs debug_swig
PRO_TARGETS		= publish profiler_pkgs optimize_swig
API_TARGETS		= publish api_pkgs optimize_swig publis_swig

ifeq ($(origin PARALLEL_JOBS), undefined)
	PARALLEL_JOBS 	= 32
endif

all: optimize

mask: maskpublish
	$(MAKE) -j $(PARALLEL_JOBS) WHAT=optimize $(MASKTARGETS)
	$(MAKE) mask -j $(PARALLEL_JOBS) OPTFLAG=-O3 -f $(SRCPATH)/rules/swig.mk -C $(SWIGBUILDROOT)/obj

maskpublish:	
	$(MAKE) -j $(PARALLEL_JOBS) WHAT=publish $(MASKTARGETS)

maskd: maskpublish
	$(MAKE) -j $(PARALLEL_JOBS) WHAT=debug $(MASKTARGETS)
	$(MAKE) mask -j $(PARALLEL_JOBS) OPTFLAG=-g -f $(SRCPATH)/rules/swig.mk -C $(SWIGBUILDROOT)/obj

help:
	echo "make (help|debug|optimize|doc|doc_all|clean|mask|maskd)"
	echo "help:			print out help message"	
	echo "debug:		compile with -g"
	echo "optimize:		compile with -O3"
	echo "pkgs:			$(PKGTARGETS)"
	echo "minimal:		$(MINIMALTARGETS)"
	echo "doc:			generate SAPI document"
	echo "doc_all:		generate all class API document"
	echo "clean:		deep clean all packages"
	echo "clean_all:	clean all build file & cache"
	echo "mask:			compile mask with -O3"
	echo "maskd:		compile mask with -g"

# rules
$(PKGTARGETS):
	echo ">>>Make $(WHAT) $(subst target_,, $@) ..."
	$(MAKE) $(WHAT) -C $(subst target_,, $@)

$(MINIMALTARGETS):
	echo ">>>Make $(WHAT) $(subst minimaltgt_,, $@) ..."
	$(MAKE) $(WHAT) -C $(subst minimaltgt_,, $@)

$(UNIQUE_MASKTARGETS):
	echo ">>>Make $(WHAT) $(subst masktgt_,, $@) ..."
	$(MAKE) $(WHAT) -C $(subst masktgt_,, $@)

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

api_pkgs:
	$(MAKE) -j $(PARALLEL_JOBS) WHAT=api $(PKGTARGETS)

debug_pkgs:
	$(MAKE) -j $(PARALLEL_JOBS) WHAT=debug $(PKGTARGETS)

optimize_swig:
	$(MAKE) -j $(PARALLEL_JOBS) OPTFLAG=-O3 -f $(SRCPATH)/rules/swig.mk -C $(SWIGBUILDROOT)/obj

debug_swig:
	$(MAKE) -j $(PARALLEL_JOBS) OPTFLAG=-g -f $(SRCPATH)/rules/swig.mk -C $(SWIGBUILDROOT)/obj

publis_swig:
	echo ">>>publish swig libs ..."
	$(CP) -f $(SWIGBUILDROOT)/obj/*.pm $(SWIGAPIROOT)/swig
	$(CP) -f $(SWIGBUILDROOT)/obj/*.tcl $(SWIGAPIROOT)/swig
	$(CP) -f $(SWIGBUILDROOT)/obj/*.o $(SWIGAPIROOT)/swig

optimize: $(OPT_TARGETS)

profiler: $(PRO_TARGETS)

debug: $(DBG_TARGETS)

api: $(API_TARGETS)

doc:
	$(MAKE) -j $(PARALLEL_JOBS) WHAT=doc $(PKGTARGETS)

doc_all:
	$(MAKE) -j $(PARALLEL_JOBS) WHAT=doc_all $(PKGTARGETS)

swigCode:
	ifeq ("$(tcl)","1")
		echo " --> make smDB_tcl_wrap.cc";
		$(MAKE) smDB_tcl_wrap.cc -f ../../../src/rules/swig.mk -C $(SWIGBUILDROOT)/obj
		echo " --> make smBase_tcl_wrap.cc";
		$(MAKE) smBase_tcl_wrap.cc -f ../../../src/rules/swig.mk -C $(SWIGBUILDROOT)/obj
	else
		echo " --> make smDB_perl_wrap.cc";
		$(MAKE) smDB_perl_wrap.cc -f ../../../src/rules/swig.mk -C $(SWIGBUILDROOT)/obj
		echo " --> make smBase_perl_wrap.cc";
		$(MAKE) smBase_perl_wrap.cc -f ../../../src/rules/swig.mk -C $(SWIGBUILDROOT)/obj
	endif

minimal_1:
	$(MAKE) -j $(PARALLEL_JOBS) WHAT=publish $(MINIMALTARGETS)
	$(MAKE) -j $(PARALLEL_JOBS) WHAT=minimal $(MINIMALTARGETS)

minimal_swig:
	$(MAKE) minimal -j $(PARALLEL_JOBS) OPTFLAG=-g -f $(SRCPATH)/rules/swig.mk -C $(SWIGBUILDROOT)/obj

minimal: minimal_1 minimal_swig
