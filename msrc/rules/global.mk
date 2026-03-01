BUILD_HOME          := /home/libai/code/resourceHome
KERNAL_RELEASE      := $(shell uname -r | awk -F'[.-]' '{print $$1"."$$2"."$$3}')
PLATFORM			:= $(shell uname -m)
OSRELEASE           := $(shell lsb_release -is | tr 'A-Z' 'a-z')
OSVERSION           := $(shell lsb_release -rs  | awk -F'[.]' '{print $$1"."$$2}')
CODENAME            := $(shell lsb_release -c | awk '{print $$2}')
OSPLATFORM          := $(OSRELEASE)$(OSVERSION)
CENTRAL             := $(BUILD_HOME)/$(OSPLATFORM)
CENTRAL7_9          := $(BUILD_HOME)/centos7.9
PRODROOT            := release

ifdef OUTPATH
    OUTPATH1	= $(OUTPATH)
	OUTPATH2	= $(OUTPATH)
    OUTPATH3	= $(OUTPATH)
else
    OUTPATH1	= $(CURDIR)/..
	OUTPATH2	= $(CURDIR)/../..
    OUTPATH3	= $(CURDIR)/../../..
endif
SRCPATH = $(CURDIR)/..

# # readline
# READLINEDIR         := $(CENTRAL)/readline/6.2.0
# READLINEINC         := -I$(READLINEDIR)/include
# READLINELIBS        := -L$(READLINEDIR)/lib -Wl,-Bstatic -lreadline -lhistory -Wl,-Bdynamic -Wl,-rpath=$(READLINEDIR)/lib
# # Boost
# BOOSTDIR            := $(CENTRAL)/boost/1.78.0
# BOOSTINCLUDES       := -I$(BOOSTDIR)/include/boost -I$(BOOSTDIR)/include
# BOOSTLIBS			:= -L$(BOOSTDIR)/lib -Wl,-Bstatic -lboost_system -lboost_thread -lboost_iostreams \
#                         -lboost_filesystem -lboost_json -lboost_program_options -Wl,-Bdynamic -Wl,-rpath=$(BOOSTDIR)/lib

# # qt qwt
# QTDIR               := $(CENTRAL)/qt/5.6.3/5.6.3/gcc_64
# QWTDIR              := $(CENTRAL)/qt/5.6.3/qwt/6.2.0
# # zlib
# ZDIR                := $(CENTRAL)/zlib/1.3.1

OPENBLASDEPENDLIBS  = -lgfortran

# GCC 9.4
GLIBCDIR		    := $(CENTRAL)/gcc/9.4.0
GLIBCINCLUDES       := -I$(GLIBCDIR)/include/c++/9.4.0
GLIBCLIBS		    := -L$(GLIBCDIR)/lib64 -lstdc++ -Wl,-rpath=$(GLIBCDIR)/lib64
CC  			    := $(GLIBCDIR)/bin/g++

ifeq ("$(OSRELEASE)", "ubuntu")
    # Perl
    PERLDIR 			:= $(CENTRAL)/perl/5.34.0/lib/5.34.0
    # GCC 9.4
    export LD_LIBRARY_PATH	:= $(GLIBCDIR)/lib64:$(LD_LIBRARY_PATH)
    # qt
    QTINCLUDES 		    := -I$(QTDIR)/include -I$(QTDIR)/include/QtCore -I$(QTDIR)/include/QtGui -I$(QWTDIR)/include \
                            -I$(QTDIR)/include/QtNetwork -I$(QTDIR)/include/QtSql -I$(QTDIR)/include/QtWidgets \
                            -I$(QTDIR)/include/QtConcurrent  -I$(QTDIR)/include/QtPrintSupport -I$(QTDIR)/include/QtXml
    QTLIBS   			:= -L$(QTDIR)/lib -lQt5Gui -lQt5Widgets -lQt5Core -lQt5Sql -lQt5Network -lQt5XcbQpa -lQt5Concurrent \
                            -lQt5Svg -lQt5DBus -lQt5PrintSupport -lQt5Xml -Wl,-rpath=$(QTDIR)/lib \
                            -L$(QWTDIR)/lib -lqwt -Wl,-rpath=$(QWTDIR)/lib
    # Boost
    BOOSTLIBS			:= -L$(BOOSTDIR)/lib -lboost_atomic -lboost_container -lboost_system -lboost_thread -lboost_iostreams \
                            -lboost_filesystem -lboost_json -lboost_program_options -Wl,-rpath=$(BOOSTDIR)/lib

    ifeq ("$(OSVERSION)", "20.04")
        OSFLAG              += -DUBUNTU20
        X11RELLIBS		    := -ldl
    endif
endif
# X11
X11RELLIBS		    += -lncurses -ltinfo
# Swig
SWIGDIR				:= $(CENTRAL)/swig/4.0.2
SWIGINCLUDES		= -I$(SWIGDIR)/share/swig/4.0.2 -I$(SWIGDIR)/share/swig/4.0.2/perl5 -I$(SWIGDIR)/share/swig/4.0.2/tcl

# Perl shell (PSH)
PSHDIR				= $(CENTRAL7_9)/psh/1.9.01
# Perl
PERLINCLUDES        = -I$(PERLDIR)/$(PLATFORM)-linux/CORE
PERLLIBS 			= -fstack-protector -Wl,-E -lcrypt -lutil -lc \
                      -L$(PERLDIR)/$(PLATFORM)-linux/CORE -lperl

# compile options
CCFLAGS 			+= -std=c++17 -DSAPI= -DSWPL= -DSWTL= -DSWPY= -DQT_NO_DBUS=1 -pipe -fPIC -fopenmp -Wall \
                        -Wno-register -Wno-literal-suffix -Wno-unused-local-typedefs -Wno-unused-result $(OSFLAG) $(MEMFLAG)

RM  				:= rm
LN  				:= ln
CP  				:= cp
MV                  := mv
MKDIR				:= mkdir
GREP				:= grep
FIND				:= find
AR   				:= ar
MOC       	        := $(QTDIR)/bin/moc $(OSFLAG)
SWIG				:= $(SWIGDIR)/bin/swig
PRESWIG				:= $(CENTRAL)/preSwig
DOXYGEN             := doxygen
LDD                 := ldd
XARGS               := xargs
BISON               := bison
FLEX                := flex

#
# include and library
#
LIBINCLUDES         += $(QTINCLUDES) $(BOOSTINCLUDES) $(SWIGINCLUDES) $(READLINEINC) $(LICINCLUDES) \
                         $(ZSTDINC) $(ZLIBINC) $(JEMALLOCINC) $(OPENCVINC) $(ARMADILLOINCLUDES) \
                         $(EIGENINCLUDES) $(FFTWINCLUDES) $(GSLINCLUDES) $(OPENBLASINCLUDES) $(GLIBCINCLUDES) $(NLOPTINCLUDES)

LIBS                += $(QTLIBS) $(PERLLIBS) $(X11LIBS) $(READLINELIBS) $(BOOSTLIBS) $(X11RELLIBS) \
	                 	$(LICLIBS) $(ZSTDLIBS) $(ZLIBS) $(JEMALLOCLIBS) $(OPENCVLIBS) $(ARMADILLOLIBS) \
                        $(FFTWLIBS) $(GSLLIBS) $(OPENBLASLIBS) $(OPENBLASDEPENDLIBS) $(GLIBCLIBS) $(NLOPTLIBS)

# packages
# all the base package
BASE_PKGS		+= gp

# will convert to scripting db, BASE_PKGS and DB_PKGS are require for every product
DB_PKGS			= db bp ds df dm du rb fb ut mm
TCC_PKGS        = lm opc tcc

# minimum pkgs lib link
CLIENT_PKGS     = $(DB_PKGS) pe gp pd pl io nb bp dr xo
# pkg need include perl
PERL_PKG        = dr pm gm pl

#minimal PKGS
MINIMAL_PKGS    = pe dm mm ut io sq du pd gu gm dr ed pm db gp oa jdv lm ds pl rb fb md jfz ca jeol vsb mbs gds oas

MASK_PKGS       = $(DB_PKGS) $(BASE_PKGS) mgu mask base
