# top level, both package and app
# .SILENT:

include rules/global.mk

# generate api document
BUILDROOT		:= $(OUTPATH1)/build
OSVERSION       := $(shell lsb_release -rs  | awk -F'[.]' '{print $$1"."$$2}')

# generate app
APPS			:= $(addprefix app/, app1)

START_TIME := $(shell cat /proc/uptime | awk -F "." '{print $$1}')

all: 	optimize

help:
	echo "make (help|debug|optimize|doc|doc_all|clean|mask|maskd)"
	echo "debug:			compile with -g"
	echo "optimize:			compile with -O3"
	echo "doc:				generate SAPI document"
	echo "doc_all:			generate all class API document"
	echo "clean:			clean all build file"
	echo "clean_all:		clean all build file & cache"
	echo "mask:				compile mask with -O3"
	echo "maskd:			compile mask with -g"

compile_time: 
	current_time=`cat /proc/uptime | awk -F "." '{print $$1}'`; \
	time_interval=`expr $${current_time} - $(START_TIME)`; \
	runtime=`date -u -d @$${time_interval} +%Hh:%Mm:%Ss`; \
	echo ">>> make src time: $${runtime}";\
	date 

clean:
	echo "  -->remove build and release directory"
	$(RM) -rf $(OUTPATH1)/release $(OUTPATH1)/build
	$(RM) -f pkg/*/obj app/*/obj
	$(FIND) pkg/* -type d -empty -delete

srcfile:
	$(shell $(MKDIR) -p $(BUILDROOT))
	echo "$(SRCPATH)" > $(BUILDROOT)/srcpath.file

clean_all: clean
	$(CCACHE) -C

# pkg
optimize_pkgs:
	$(MAKE) srcfile
	$(MAKE) optimize -C pkg

profiler_pkgs:
	$(MAKE) srcfile
	$(MAKE) profiler -C pkg

debug_pkgs:
	$(MAKE) srcfile
	$(MAKE) debug -C pkg

# app
optimize_apps:
	for app in $(APPS); do \
		$(MAKE) optimize -C $$app || exit 1;\
	done

profiler_apps:
	for app in $(APPS); do \
		$(MAKE) profiler -C $$app || exit 1;\
	done

debug_apps:
	for app in $(APPS); do \
		$(MAKE) debug -C $$app || exit 1;\
	done


optimize: optimize_pkgs optimize_apps compile_time

debug: debug_pkgs debug_apps compile_time

profiler: profiler_pkgs profiler_apps compile_time

