# Makefile

# dissector name
DIS1_NAME = dis_tcp
DIS2_NAME = dis_tcp_soft
DIS1_NAME_NOCHECK = $(DIS1_NAME)_nocheck
DIS2_NAME_NOCHECK = $(DIS2_NAME)_nocheck

# dissector library (.so)
DIS1_SO = $(DIS1_NAME).so
DIS2_SO = $(DIS2_NAME).so
DIS1_SO_NC = $(DIS1_NAME_NOCHECK).so
DIS2_SO_NC = $(DIS2_NAME_NOCHECK).so

# sub directory
SUBDIRS = 

# src file
SRC1 = dis_log.c tcp.c
SRC2 = dis_log.c tcp_soft.c

# To make it visible
export CC CCPP ROOT_DIR CFLAGS LDFLAGS INCLUDE_DIR


all: subdir $(DIS1_SO) $(DIS2_SO) $(DIS1_SO_NC)  $(DIS2_SO_NC)


$(DIS1_SO): $(SRC1:.c=.o)
	$(CC) $(CFLAGS) -shared -Wl,-soname,$@ -o $@ $(SRC1:.c=.o) $(LDFLAGS)

$(DIS2_SO): $(SRC2:.c=.o)
	$(CC) $(CFLAGS) -shared -Wl,-soname,$@ -o $@ $(SRC2:.c=.o) $(LDFLAGS)

$(DIS1_SO_NC): dis_log.o tcp_nc.o
	$(CC) $(CFLAGS) -shared -Wl,-soname,$@ -o $@ dis_log.o tcp_nc.o $(LDFLAGS)

$(DIS2_SO_NC): dis_log.o tcp_soft_nc.o
	$(CC) $(CFLAGS) -shared -Wl,-soname,$@ -o $@ dis_log.o tcp_soft_nc.o $(LDFLAGS)


subdir:
	@for dir in $(SUBDIRS) ; \
	   do $(MAKE) -C $$dir || exit 1; \
	 done \

clean:
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir clean || exit 1; done
	rm -f *.o *.so *~ include/*~ .depend *.expand


.depend: $(SRC1) $(SRC2) 
	$(CC) -M $(CFLAGS) $(SRC1) $(SRC2) > $@

tcp_nc.o: tcp.o
	$(CC) $(CFLAGS) -DXPL_DIS_IP_CHECKSUM=1 -c -o $@ tcp.c

tcp_soft_nc.o: tcp_soft.o
	$(CC) $(CFLAGS) -DXPL_DIS_IP_CHECKSUM=1 -c -o $@ tcp_soft.c


include ../Makefilelog
sinclude .depend
