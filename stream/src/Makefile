# root directory
ROOT_DIR = $(shell pwd)

# sub directory
SUBDIRS = capture common decode

#library
LIB = 

# src file
SRC = 

# compilation
INCLUDE_DIR = -I$(ROOT_DIR)/capture/include -I$(ROOT_DIR)/common/include
LDFLAGS = -L$(ROOT_DIR) 
CFLAGS = -rdynamic $(INCLUDE_DIR) -Wall -fPIC

# optmimization
ifdef O3
CFLAGS += -O3
 ifndef CHECKOFF
 CHECKOFF = 1
 endif
else
#CFLAGS += -g -ggdb -dr
CFLAGS += -g -ggdb -O0
endif

# performance
ifdef GPROF
CFLAGS += -pg
endif

# architeture type
ifdef CROSS_COMPILE
CC = $(CROSS_COMPILE)gcc
STRIP = $(CROSS_COMPILE)strip
else
STRIP = strip
CFLAGS += -DXPL_X86=1
endif

# To make it visible
export CC CCPP ROOT_DIR CFLAGS LDFLAGS INCLUDE_DIR INSTALL_DIR LIB

all: subdir mdl

help:
	@echo "Flags:"
	@echo "    VER=<string>      --> string is the release name, otherwise the date is the name"
	@echo "    GPROF=1           --> enable gprof compilation"
	@echo "    FTBL_NOSORT=1     --> disable sort in flows manager"
	@echo "    O3=1              --> enable optimization"
	@echo " "
	@echo "Comands:"
	@echo "    help    --> this help"
	@echo "    reset   --> delete default tmp data"
	@echo "    clean   --> clean"
	@echo "    tgz     --> project snapshot"
	@echo "    install --> install in $(INSTALL_DIR)"
	@echo "    check_version --> check version"
	@echo " "

# version name
ifndef VER
VER = $(shell date +%Y_%m_%d)
endif

subdir:
	@for dir in $(SUBDIRS) ; \
	   do $(MAKE) -C $$dir || exit 1; \
	 done

clean: reset
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir clean; done
	rm -f *.o *~ *.log .depend val.* *.expand
	rm -rf $(MODULE_PATH)

installcp: all 

# install and permission
ifndef DESTDIR
install: installcp

else
install: installcp

endif


.PHONY: check_version
check_version:

.PHONY: reset
reset:

tgz: clean


%.o: %.c
	$(CC) $(MCFLAGS) -c -o $@ $< 


.depend: $(SRC)
	$(CC) -M $(MCFLAGS) $(SRC) > $@


sinclude .depend
