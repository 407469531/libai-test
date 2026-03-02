# silent or not
.SILENT:

include ../../rules/global.mk
PKG				:= $(notdir $(basename $(shell pwd)))
BUILDROOT		:= $(OUTPATH3)/build

OBJDIR			:= $(BUILDROOT)/pkg/$(PKG)
PUBLISHINCLUDE	:= -I$(BUILDROOT)/include

DOXYGENINCLUDE	:= $(BUILDROOT)/doc/headers

TMFILES			:= $(wildcard *.tm)
CCFILES 		:= $(wildcard *.cc)
HEADERS			:= $(wildcard *.h)
PUBLICHEADERS	:= $(wildcard lib$(PKG)_*.h)
#lex/yacc
YACCFILES		:= $(wildcard *.y)
LEXFILES		:= $(wildcard *.l)
GPERFFILES		:= $(wildcard *.gperf)

YACCS			:= $(addprefix $(OBJDIR)/yacc_, $(subst .y,.cc, $(YACCFILES)))
LEXS			:= $(addprefix $(OBJDIR)/lex_, $(subst .l,.cc, $(LEXFILES)))
GPERFS			:= $(addprefix $(OBJDIR)/gperf_, $(subst .gperf,.cc, $(GPERFFILES)))

MOCHEADERS		:= $(shell $(GREP) -l Q_OBJECT $(HEADERS))
MOCCCS			:= $(addprefix $(OBJDIR)/moc_, $(subst .h,.cc, $(MOCHEADERS)))

OBJS 			:= $(addprefix $(OBJDIR)/, $(subst .cc,.o, $(CCFILES))) \
					$(subst .cc,.o, $(MOCCCS)) $(subst .cc,.o, $(YACCS)) $(subst .cc,.o, $(LEXS)) \
					$(subst .cc,.o, $(GPERFS))

SWIGHEADERS		:= $(shell $(GREP) -l "\(SAPI\|SWPY\|SWPL\|SWTL\)" $(HEADERS))


# 	needed directories
NEEDDIRS		:= $(shell $(MKDIR) -p $(BUILDROOT)/include $(BUILDROOT)/lib $(OBJDIR) \
					$(BUILDROOT)/swig)

# final target:
LIBTARGET		:= $(BUILDROOT)/lib/lib$(PKG).a
SWIGTARGET		:= $(BUILDROOT)/swig/$(PKG).i 
TMTARGETS		:= $(addprefix $(BUILDROOT)/swig/, $(TMFILES))

# publis target
PUBLISHTARGETS	:= $(addprefix $(BUILDROOT)/include/, $(PUBLICHEADERS))

# Define number of parallel jobs in this level
ifeq ($(MAKELEVEL), 0)
PKG_LVL_JOBS	:= -j32
endif

ifeq ($(findstring $(PKG), $(PERL_PKG)), $(PKG))
LIBINCLUDES		+= $(PERLINCLUDES)
endif

START_TIME := $(shell cat /proc/uptime | awk -F "." '{print $$1}')

# general rules
$(OBJDIR)/%.o: %.cc
	echo "  -->$(notdir $(CC)) $(OPTFLAG) $<"
	$(CC) -c $(OPTFLAG) $(CCFLAGS) $(PUBLISHINCLUDE) $(LIBINCLUDES) \
	-DBUILDARCH=\"$(CODENAME)\" -o $@ $<

$(OBJDIR)/moc_%.o: $(OBJDIR)/moc_%.cc
	echo "  -->$(notdir $(CC)) $(OPTFLAG) $<"
	$(CC) -c $(OPTFLAG)  $(CCFLAGS) $(PUBLISHINCLUDE) $(LIBINCLUDES) -o $@ $<

$(OBJDIR)/moc_%.cc: %.h
	echo "  -->moc $<"
	$(MOC) -o $@ $<

all: optimize compile_time

help:
	echo "make (help|publish|debug|optimize|doc|doc_all|clean|deep_clean)"
	echo "help:			print out help message"	
	echo "publish:		propagate header files"
	echo "debug:		compile with -g"
	echo "optimize:		compile with -O3"
	echo "doc:			generate SAPI document"
	echo "doc_all:		generate all class API document"
	echo "clean:		clean obj directory and lib$(PKG).a"
	echo "deep_clean:	clean obj directory, lib$(PKG).a, published headers and swig files"

compile_time: optimize
	current_time=`cat /proc/uptime | awk -F "." '{print $$1}'`; \
	time_interval=`expr $${current_time} - $(START_TIME)`; \
	runtime=`date -u -d @$${time_interval} +%Hh:%Mm:%Ss`; \
	echo ">>> make $(PKG) time: $${runtime}"

$(BUILDROOT)/include/%.h: %.h
	echo "  -->publish $<"
	$(CP) -f $< $@

$(BUILDROOT)/swig/%.tm: %.tm
	echo "  -->publish $<"
	$(CP) -f $< $@

clean_previous_publish:
	for file in $(notdir $(wildcard $(BUILDROOT)/include/lib$(PKG)_*.h)); do \
		if [ ! -f $$file ]; then \
			echo "  -->rm $$file from publish"; \
			$(RM) $(BUILDROOT)/include/$$file; \
		fi \
	done

publish: clean_previous_publish $(PUBLISHTARGETS) $(TMTARGETS)


build_symbolic_obj: publish
	if [ ! -h obj ]; then \
		echo "  -->make symbolic link $(PKG)/obj"; \
		$(LN) -s $(BUILDROOT)/pkg/$(PKG) obj; \
	fi

# centos7.9 redhat7.4 redhat8.9 ubuntu22.04 ubuntu20.04
# need to perform every time
# Step1: Check the .cc is not newer than its depends file.
# Step2: Check the existing depends headers' date is not newer than depends file
# Step3: Update .cc depends if any condition is false.
# Step4: Merge the individual depends file to one package depends file.
depends: build_symbolic_obj
	rm -f $(OBJDIR)/depends;
	for CCFILE in $(CCFILES); do\
		if [ $${CCFILE} -nt $(OBJDIR)/depends.$${CCFILE} ] || [ ! -f $(OBJDIR)/depends.$${CCFILE}  ]; then\
			echo "  -->g++ -MM $${CCFILE}";\
			$(CC) -MM -I. $(OLDGCCINCLUDE) -I$(BUILDROOT)/include $$CCFILE -std=c++11 | sed 's%\(.*\.o\:\)%$(OBJDIR)\/\1%' > $(OBJDIR)/depends.$${CCFILE}&\
		else\
			for l in $$(cat $(OBJDIR)/depends.$${CCFILE}); do\
				if [ -f $$l ] && [ $$l -nt $(OBJDIR)/depends.$${CCFILE} ]; then\
					echo "  -->g++ -MM $${CCFILE} ($$l update)";\
						$(CC) -MM -I. $(OLDGCCINCLUDE) -I$(BUILDROOT)/include $$CCFILE -std=c++11 | sed 's%\(.*\.o\:\)%$(OBJDIR)\/\1%' > $(OBJDIR)/depends.$${CCFILE}&\
					break;\
				fi;\
			done\
		fi;\
	done;\
	wait;\
	for CCFILE in $(CCFILES); do\
		cat $(OBJDIR)/depends.$${CCFILE} >> $(OBJDIR)/depends;\
	done;


optimize: depends
	$(MAKE) $(PKG_LVL_JOBS) OPTFLAG="-O3 -DNDEBUG" $(LIBTARGET)
	$(MAKE) $(SWIGTARGET)

profiler: depends
	$(MAKE) $(PKG_LVL_JOBS) OPTFLAG="-fno-omit-frame-pointer -ggdb -O3 -g -D _DEBUG" $(LIBTARGET)
	$(MAKE) $(SWIGTARGET)

debug: depends
	$(MAKE) $(PKG_LVL_JOBS) OPTFLAG="-g -D _DEBUG" $(LIBTARGET)
	$(MAKE) $(SWIGTARGET)

api: depends $(SAMPLETARGETS) $(APIPUBTARGETS)
	$(MAKE) $(PKG_LVL_JOBS) OPTFLAG="-O3 -DNDEBUG" $(APITARGET)
	$(MAKE) $(SWIGTARGET)

$(LIBTARGET): $(OBJS)
	echo "  -->$(AR) $(notdir $(LIBTARGET))"
	$(AR) cr $@ $^

$(APITARGET): $(LIBTARGET)
	echo "  -->publish $<"
	$(CP) -f $^ $@

$(SWIGTARGET): $(OBJDIR)/$(PKG).i
	if ! diff $@ $< > /dev/null 2>&1 ; then \
		echo "  -->preswig $(PKG).i"; \
		$(CP) -f $< $@; \
	fi

$(OBJDIR)/$(PKG).i: $(SWIGHEADERS)
	$(PRESWIG) $(SWIGHEADERS) > $@

doc: 
	for header in $(SWIGHEADERS); do \
		echo "  -->publish $$header"; \
		$(CP) -f $$header $(DOXYGENINCLUDE); \
	done

doc_all:
	$(shell $(MKDIR) -p $(DOXYGENINCLUDE)/pkg/$(PKG))
	for header in $(HEADERS); do \
		echo "  -->publish $$header"; \
		$(CP) -f $$header $(DOXYGENINCLUDE)/pkg/$(PKG); \
	done	

clean:
	echo "  -->clean $(OBJDIR)/ $(notdir $(LIBTARGET))"
	$(RM) -f $(OBJDIR)/*
	$(RM) -f $(LIBTARGET)

deep_clean:
	echo "  -->deep clean $(OBJDIR)/ $(notdir $(LIBTARGET))"
	$(RM) -f $(OBJDIR)/*
	$(RM) -f $(LIBTARGET)
	$(RM) -f $(BUILDROOT)/include/lib$(PKG)_*.h

# This must be the last line!!
sinclude $(OBJDIR)/depends
