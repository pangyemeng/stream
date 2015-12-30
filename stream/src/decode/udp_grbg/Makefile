# Makefile
#
#

# dissector name
DIS_NAME = dis_udp_grb


# dissector library (.so)
DIS_SO = $(DIS_NAME).so

# sub directory
SUBDIRS = 

# src file
SRC = dis_log.c udp_garbage.c

# C flags specific to the dissector
CFLAGS += -I$(ROOT_DIR)/../nDPI/src/include -I$(ROOT_DIR)/../nDPI/src/lib

# library specific to the dissector
LDFLAGS = $(ROOT_DIR)/../nDPI/src/lib/.libs/libndpi.a

# To make it visible
export CC CCPP ROOT_DIR CFLAGS LDFLAGS INCLUDE_DIR


all: subdir $(DIS_SO)


$(DIS_SO): $(SRC:.c=.o) $(ROOT_DIR)/../nDPI/src/lib/.libs/libndpi.a
	$(CC) $(CFLAGS) -shared -Wl,-soname,$@ -o $@ $(SRC:.c=.o) $(LDFLAGS)


subdir:
	@for dir in $(SUBDIRS) ; \
	   do $(MAKE) -C $$dir || exit 1; \
	 done \

clean:
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir clean || exit 1; done
	rm -f *.o *.so *~ include/*~ .depend *.expand


.depend: $(SRC)
	$(CC) -M $(CFLAGS) $(SRC) > $@


include ../Makefilelog
sinclude .depend
