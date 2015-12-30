# Makefile
#
#

# dissector name
DIS_NAME = dis_udp
DIS_NAME_NOCHECK = $(DIS_NAME)_nocheck

# dissector library (.so)
DIS_SO = $(DIS_NAME).so
DIS_SO_NC = $(DIS_NAME_NOCHECK).so

# sub directory
SUBDIRS = 

# src file
SRC = dis_log.c udp.c


# To make it visible
export CC CCPP ROOT_DIR CFLAGS LDFLAGS INCLUDE_DIR


all: subdir $(DIS_SO) $(DIS_GRB_SO) $(DIS_SO_NC)


$(DIS_SO): $(SRC:.c=.o)
	$(CC) $(CFLAGS) -shared -Wl,-soname,$@ -o $@ $(SRC:.c=.o) $(LDFLAGS)

$(DIS_SO_NC): dis_log.o udp_nc.o
	$(CC) $(CFLAGS) -shared -Wl,-soname,$@ -o $@ dis_log.o udp_nc.o $(LDFLAGS)


subdir:
	@for dir in $(SUBDIRS) ; \
	   do $(MAKE) -C $$dir || exit 1; \
	 done \

clean:
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir clean || exit 1; done
	rm -f *.o *.so *~ include/*~ .depend *.expand


.depend: $(SRC)
	$(CC) -M $(CFLAGS) $(SRC) > $@

udp_nc.o: udp.o
	$(CC) $(CFLAGS) -DXPL_DIS_IP_CHECKSUM=1 -c -o $@ udp.c


include ../Makefilelog
sinclude .depend
