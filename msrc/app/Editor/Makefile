# Makefile to make DBScope
.SILENT:

include ../../rules/global.mk

PROD 			:= dbscope

BUILDROOT		:= $(OUTPATH3)/build
OBJDIR			:= $(BUILDROOT)/app/$(PROD)

PUBLISHINCLUDE 	:= -I$(BUILDROOT)/include

RELEASEROOT		:= $(OUTPATH3)/$(PRODROOT)
LIBRARYROOT		:= $(RELEASEROOT)/etc/library
PRODROOT		:= ../../rsc/launch

RELEASEBIN		:= $(RELEASEROOT)/bin

# 	needed directories
ifeq ("$(common)", "1")
LAUNCHPATH	:= common
NEEDDIRS		:= $(shell $(MKDIR) -p $(BUILDROOT)/app/$(PROD) $(RELEASEBIN) \
					$(RELEASEROOT)/etc/public $(RELEASEROOT)/etc/rc \
					$(LIBRARYROOT)/lib64/plugins $(LIBRARYROOT)/sys_lib \
					$(LIBRARYROOT)/libcr6 $(LIBRARYROOT)/libcr7 \
					$(LIBRARYROOT)/libr89)
else
LAUNCHPATH	:= base
NEEDDIRS		:= $(shell $(MKDIR) -p $(BUILDROOT)/app/$(PROD) $(RELEASEBIN) \
					$(RELEASEROOT)/etc/public $(RELEASEROOT)/etc/rc \
					$(LIBRARYROOT)/lib64/plugins $(LIBRARYROOT)/sys_lib)
endif

OSRELEASE           := $(shell lsb_release -is | tr 'A-Z' 'a-z')
ifeq ("$(OSRELEASE)", "ubuntu")
NEEDDIRS += $(shell $(MKDIR) -p $(LIBRARYROOT)/libu)
endif

CCFILES			:= $(wildcard *.cc)
OBJS			:= $(addprefix $(OBJDIR)/, $(subst .cc,.o, $(CCFILES)))

# which packages are needed
PKGS 			= $(BASE_PKGS) $(DB_PKGS)

PKGLIBS			:= $(addsuffix .a, $(addprefix $(BUILDROOT)/lib/lib, $(PKGS)))

SWIGS			:= smBase smDB

# which perl package needed
ifeq ("$(tcl)","1")
	SWIGLIBS		:=  $(addsuffix _tcl_wrap.o, $(addprefix $(BUILDROOT)/swig/obj/, $(SWIGS)))
else
	SWIGLIBS		:=  $(addsuffix _perl_wrap.o, $(addprefix $(BUILDROOT)/swig/obj/, $(SWIGS)))
endif
all:    optimize

help:
	echo "make (help|debug|optimize|clean)"
	echo "help:         print out help message"
	echo "debug:        compile with -g"
	echo "optimize:     compile with -O3"
	echo "clean:        clean"
	echo "PERLLIBS $(LIBS)"

build_symbolic_obj:
	if [ ! -h obj ]; then \
		echo "  -->make symbolic link obj"; \
		$(LN) -s $(BUILDROOT)/app/$(PROD) obj; \
	fi

build_symbolic_exe:
	if [ ! -e $(RELEASEBIN)/dbscope_exe ]; then \
		echo "  -->make symbolic link dbscope_exe"; \
		$(LN) -s $(abspath $(OBJDIR)/dbscope_exe) $(RELEASEBIN)/dbscope_exe; \
	fi

$(RELEASEBIN)/dbscope: $(PRODROOT)/$(LAUNCHPATH)/dbscope
	echo "  -->copy $(LAUNCHPATH) DBScope"
	$(CP) -f $< $@
$(RELEASEBIN)/essemdc: $(PRODROOT)/$(LAUNCHPATH)/essemdc
	echo "  -->copy $(LAUNCHPATH) essemdc"
	$(CP) -f $< $@

$(RELEASEBIN)/dbxor: $(PRODROOT)/$(LAUNCHPATH)/dbxor
	echo "  -->copy $(LAUNCHPATH) dbxor"
	$(CP) -f $< $@

$(RELEASEBIN)/smBatch: $(PRODROOT)/$(LAUNCHPATH)/smBatch
	echo "  -->copy $(LAUNCHPATH) smBatch"
	$(CP) -f $< $@

$(RELEASEBIN)/check_dbscope: $(PRODROOT)/$(LAUNCHPATH)/check_dbscope
	echo "  -->copy $(LAUNCHPATH) check_dbscope"
	$(CP) -f $< $@

$(RELEASEBIN)/essepdk: $(PRODROOT)/$(LAUNCHPATH)/essepdk
	echo "  -->copy $(LAUNCHPATH) essepdk"
	$(CP) -f $< $@

$(RELEASEBIN)/essemask: $(PRODROOT)/$(LAUNCHPATH)/essemask
	echo "  -->copy $(LAUNCHPATH) essemask"
	$(CP) -f $< $@

$(OBJDIR)/%.o: %.cc
	echo "  -->$(notdir $(CC)) $(OPTFLAG) $<"
	$(CC) -c $(OPTFLAG) $(CCFLAGS) $(PUBLISHINCLUDE) $(LIBINCLUDES) $(PERLINCLUDES) $(TCLINCLUDES) -o $@ $<

redhat6:
	if [ -n "${REDHAT6.4}" ] ; then \
		echo "REDHAT6.4"; \
		$(CP) -f $(LIBRARYROOT)/sys_lib/libEGL.so.1 $(LIBRARYROOT)/lib64 ; \
		$(CP) -f $(LIBRARYROOT)/sys_lib/libgbm.so.1 $(LIBRARYROOT)/lib64 ; \
		$(CP) -f $(LIBRARYROOT)/sys_lib/libxcb-icccm.so.4 $(LIBRARYROOT)/lib64 ; \
		$(CP) -f $(LIBRARYROOT)/sys_lib/libxcb-xkb.so.1 $(LIBRARYROOT)/lib64 ; \
		$(CP) -f $(LIBRARYROOT)/sys_lib/libxkbcommon.so.0 $(LIBRARYROOT)/lib64 ; \
		$(CP) -f $(LIBRARYROOT)/sys_lib/libxkbcommon-x11.so.0 $(LIBRARYROOT)/lib64 ; \
	fi;
	if [ -n "${REDHAT6.8}" ] ; then \
		echo "REDHAT6.8"; \
		$(CP) -f $(LIBRARYROOT)/sys_lib/libEGL.so.1 $(LIBRARYROOT)/lib64 ; \
		$(CP) -f $(LIBRARYROOT)/sys_lib/libgbm.so.1 $(LIBRARYROOT)/lib64 ; \
		$(CP) -f $(LIBRARYROOT)/sys_lib/libxcb-icccm.so.4 $(LIBRARYROOT)/lib64 ; \
		$(CP) -f $(LIBRARYROOT)/sys_lib/libxcb-xkb.so.1 $(LIBRARYROOT)/lib64 ; \
		$(CP) -f $(LIBRARYROOT)/sys_lib/libxkbcommon.so.0 $(LIBRARYROOT)/lib64 ; \
		$(CP) -f $(LIBRARYROOT)/sys_lib/libxkbcommon-x11.so.0 $(LIBRARYROOT)/lib64 ; \
		$(CP) -f $(LIBRARYROOT)/sys_lib/libxcb-image.so.0 $(LIBRARYROOT)/lib64 ; \
		$(CP) -f $(LIBRARYROOT)/sys_lib/libxcb-keysyms.so.1 $(LIBRARYROOT)/lib64 ; \
		$(CP) -f $(LIBRARYROOT)/sys_lib/libxcb-render-util.so.0 $(LIBRARYROOT)/lib64 ; \
	fi;

common:
	if [ -n "${common}" ] ; then \
		echo " common $(OSPLATFORM)"; \
		\
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libxcb-xkb.so.1 $(LIBRARYROOT)/libcr6 ; \
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libxcb-icccm.so.4 $(LIBRARYROOT)/libcr6 ; \
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libxcb-image.so.0 $(LIBRARYROOT)/libcr6 ; \
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libxcb-keysyms.so.1 $(LIBRARYROOT)/libcr6 ; \
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libxcb-render-util.so.0 $(LIBRARYROOT)/libcr6 ; \
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libxcb-util.so.1 $(LIBRARYROOT)/libcr6 ; \
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libxkbcommon.so.0 $(LIBRARYROOT)/libcr6 ; \
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libxkbcommon-x11.so.0 $(LIBRARYROOT)/libcr6 ; \
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libEGL.so.1 $(LIBRARYROOT)/libcr6 ; \
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libgbm.so.1 $(LIBRARYROOT)/libcr6 ; \
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libz.so.1 $(LIBRARYROOT)/libcr6 ; \
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libjpeg.so.62 $(LIBRARYROOT)/libcr6 ; \
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libGL.so.1 $(LIBRARYROOT)/libcr6 ; \
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libglapi.so.0 $(LIBRARYROOT)/libcr6 ; \
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libXxf86vm.so.1 $(LIBRARYROOT)/libcr6 ; \
		\
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libxcb-xkb.so.1 $(LIBRARYROOT)/libcr7 ; \
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libxcb-icccm.so.4 $(LIBRARYROOT)/libcr7 ; \
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libxcb-image.so.0 $(LIBRARYROOT)/libcr7 ; \
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libxcb-keysyms.so.1 $(LIBRARYROOT)/libcr7 ; \
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libxcb-render-util.so.0 $(LIBRARYROOT)/libcr7 ; \
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libxcb-util.so.1 $(LIBRARYROOT)/libcr7 ; \
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libxkbcommon.so.0 $(LIBRARYROOT)/libcr7 ; \
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libxkbcommon-x11.so.0 $(LIBRARYROOT)/libcr7 ; \
		\
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libxcb-icccm.so.4 $(LIBRARYROOT)/libr89 ; \
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libxcb-image.so.0 $(LIBRARYROOT)/libr89 ; \
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libncurses.so.5 $(LIBRARYROOT)/libr89 ; \
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libtinfo.so.5 $(LIBRARYROOT)/libr89 ; \
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libxcb-keysyms.so.1 $(LIBRARYROOT)/libr89 ; \
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libxcb-render-util.so.0 $(LIBRARYROOT)/libr89 ; \
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libpng12.so.0 $(LIBRARYROOT)/libr89 ; \
	fi;

libu:
	if [ "${OSRELEASE}" = "ubuntu" ] ; then \
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libGL.so.1 $(LIBRARYROOT)/libu ; \
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libX11-xcb.so.1 $(LIBRARYROOT)/libu ; \
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libfontconfig.so.1 $(LIBRARYROOT)/libu ; \
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libEGL.so.1 $(LIBRARYROOT)/libu ; \
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libGLdispatch.so.0 $(LIBRARYROOT)/libu ; \
		$(LN) -fs $(LIBRARYROOT)/sys_lib/libGLX.so.0 $(LIBRARYROOT)/libu ; \
	fi;

install:
	$(LDD) $(OBJDIR)/dbscope_exe | awk '/\/.*\// {print($$3)}' |grep "$(BUILD_HOME)" | $(XARGS) -I '{}' $(CP) -f '{}' $(LIBRARYROOT)/lib64
	$(LDD) $(OBJDIR)/dbscope_exe | awk '/\/.*\// {print($$3)}' |grep -v "$(BUILD_HOME)" | $(XARGS) -I '{}' $(CP) -f '{}' $(LIBRARYROOT)/sys_lib
	$(MAKE) redhat6
	$(MAKE) common
	$(MAKE) libu
	chmod -R 755 $(LIBRARYROOT)/lib64
	chmod -R 755 $(RELEASEBIN)

$(OBJDIR)/dbscope_exe: $(OBJS) $(SWIGLIBS) $(PKGLIBS)
	echo "  -->make dbscope_exe"
	$(CC) -o $@ $(CCFLAGS) -fPIC -rdynamic -fopenmp -Wl,--start-group $^ $(LIBS) -Wl,--end-group
	$(RM) -f $(OBJDIR)/main.o

clean:
	echo "  -->clean $(PROD)/obj"
	$(RM) -f $(OBJDIR)/*

allscript:
	$(MAKE) $(RELEASEBIN)/dbscope
	$(MAKE) $(RELEASEBIN)/smBatch
	$(MAKE) $(RELEASEBIN)/essemdc
	$(MAKE) $(RELEASEBIN)/check_dbscope
	$(MAKE) $(RELEASEBIN)/essepdk
	$(MAKE) $(RELEASEBIN)/essemask
	$(MAKE) $(RELEASEBIN)/dbxor

optimize: build_symbolic_obj 3rdParty PerlPm SwigPm Rsc
	echo ">>>Make optimize DBScope..."
	$(MAKE) OPTFLAG="-O3 -DNDEBUG" $(OBJDIR)/dbscope_exe
	strip $(OBJDIR)/dbscope_exe
	$(MAKE) build_symbolic_exe
	$(MAKE) allscript
	$(MAKE) install

profiler: build_symbolic_obj 3rdParty PerlPm SwigPm Rsc
	echo ">>>Make optimize DBScope..."
	$(MAKE) OPTFLAG="-fno-omit-frame-pointer -ggdb -O3 -g -D _DEBUG" $(OBJDIR)/dbscope_exe
	$(MAKE) build_symbolic_exe
	$(MAKE) allscript
	$(MAKE) install

debug: build_symbolic_obj 3rdParty PerlPm SwigPm Rsc
	echo ">>>Make debug DBScope..."
	$(MAKE) OPTFLAG=-g $(OBJDIR)/dbscope_exe
	$(MAKE) build_symbolic_exe
	$(MAKE) allscript
	$(MAKE) install

# static 3rd party, perl, psh
3rdParty:
	if [ ! -h $(RELEASEROOT)/etc/public/perl ]; then \
		echo "  -->make symbolic link $(RELEASEROOT)/etc/public/perl"; \
		$(LN) -s $(PERLDIR) $(RELEASEROOT)/etc/public/perl; \
	fi;
ifeq ("$(tcl)","1")
	if [ ! -h $(RELEASEROOT)/etc/public/tcl ]; then \
		echo "  -->make symbolic link $(RELEASEROOT)/etc/public/tcl"; \
		$(LN) -s $(TCLDIR) $(RELEASEROOT)/etc/public/tcl; \
	fi;
endif
	if [ ! -h $(RELEASEROOT)/etc/public/psh-1.9.01 ]; then \
		echo "  -->make symbolic link $(RELEASEROOT)/etc/public/psh-1.9.01"; \
		$(LN) -s $(PSHDIR)/blib/lib $(RELEASEROOT)/etc/public/psh-1.9.01; \
	fi;
	if [ ! -h $(LIBRARYROOT)/lib64/plugins/platforms ]; then \
		echo "  -->make symbolic link $(LIBRARYROOT)/lib64/plugins/platforms"; \
		$(LN) -s $(QTDIR)/plugins/platforms $(LIBRARYROOT)/lib64/plugins/platforms; \
	fi;
	if [ ! -h $(LIBRARYROOT)/lib64/plugins/iconengines ]; then \
		echo "  -->make symbolic link $(LIBRARYROOT)/lib64/plugins/iconengines"; \
		$(LN) -s $(QTDIR)/plugins/iconengines $(LIBRARYROOT)/lib64/plugins/iconengines; \
	fi;
	if [ ! -h $(LIBRARYROOT)/lib64/plugins/imageformats ]; then \
		echo "  -->make symbolic link $(LIBRARYROOT)/lib64/plugins/imageformats"; \
		$(LN) -s $(QTDIR)/plugins/imageformats $(LIBRARYROOT)/lib64/plugins/imageformats; \
	fi;
	if [ ! -h $(LIBRARYROOT)/lib64/plugins/sqldrivers ]; then \
		echo "  -->make symbolic link $(LIBRARYROOT)/lib64/plugins/sqldrivers"; \
		$(LN) -s $(QTDIR)/plugins/sqldrivers $(LIBRARYROOT)/lib64/plugins/sqldrivers; \
	fi;

# Menu.json, Form.pm, initPerl.pl, initPsh.pl saveAs.pm
PerlPm:
	if [ ! -h $(RELEASEROOT)/etc/rc/pm ]; then \
		echo "  -->cp $(abspath ../../rsc/script/pm)"; \
		$(CP) -rf $(abspath ../../rsc/script/pm) $(RELEASEROOT)/etc/rc; \
	fi; 
	if [ ! -h $(RELEASEROOT)/etc/rc/perl ]; then \
		echo "  -->make symbolic link $(RELEASEROOT)/etc/rc/perl"; \
		$(LN) -s $(abspath ../../rsc/script/perl) $(RELEASEROOT)/etc/rc/perl; \
	fi;

# pm from swig
SwigPm:
ifeq ("$(tcl)","1")
else
	for pkg in $(SWIGS); do \
		if [ ! -h $(RELEASEROOT)/etc/rc/pm/$$pkg.pm ]; then \
			echo "  -->copy $(BUILDROOT)/swig/obj/$$pkg.pm"; \
			$(CP) -f $(abspath $(BUILDROOT)/swig/obj/$$pkg.pm) $(RELEASEROOT)/etc/rc/pm/$$pkg.pm; \
		fi; \
	done
endif
	

# resource for app
Rsc:
	if [ ! -h $(RELEASEROOT)/etc/rc/icons ]; then \
		echo "  -->make symbolic link $(RELEASEROOT)/etc/rc/icons"; \
		$(LN) -s $(abspath ../../rsc/icons) $(RELEASEROOT)/etc/rc/icons; \
	fi; 
	if [ ! -h $(RELEASEROOT)/etc/rc/fonts ]; then \
		echo "  -->make symbolic link $(RELEASEROOT)/etc/rc/fonts"; \
		$(LN) -s $(abspath ../../rsc/fonts) $(RELEASEROOT)/etc/rc/fonts; \
	fi;
	if [ ! -h $(RELEASEROOT)/etc/rc/qss ]; then \
		echo "  -->make symbolic link $(RELEASEROOT)/etc/rc/qss"; \
		$(LN) -s $(abspath ../../rsc/qss) $(RELEASEROOT)/etc/rc/qss; \
	fi;
	if [ ! -h $(RELEASEROOT)/etc/rc/helpDoc ]; then \
		echo "  -->make symbolic link $(RELEASEROOT)/etc/rc/helpDoc"; \
		$(LN) -s $(abspath ../../rsc/helpDoc) $(RELEASEROOT)/etc/rc/helpDoc; \
	fi;
	if [ ! -h $(RELEASEROOT)/etc/rc/drcRule ]; then \
		echo "  -->make symbolic link $(RELEASEROOT)/etc/rc/drcRule"; \
		$(LN) -s $(abspath ../../rsc/script/drcRule) $(RELEASEROOT)/etc/rc/drcRule; \
	fi;
	if [ ! -h $(RELEASEROOT)/etc/rc/setting ]; then \
		echo "  -->copy setting"; \
		$(CP) -rf $(abspath ../../rsc/setting) $(RELEASEROOT)/etc/rc/setting; \
	fi;
	if [ ! -h $(RELEASEROOT)/tools ]; then \
		echo "  -->copy tools"; \
		$(CP) -rf $(abspath ../../rsc/tools) $(RELEASEROOT); \
	fi;

