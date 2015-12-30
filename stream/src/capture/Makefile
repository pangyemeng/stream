# sub directory
SUBDIRS = pcap

# capture name
CAP_NAME = capture

# decode library (.so)
CAP_SO = $(CAP_NAME).so

# log captures flags
CFLAGS += -DLOG_COMPONENT=-2

# sec file
SRC = capture.c

# To make it visible
export CC CCPP ROOT_DIR CFLAGS LDFLAGS INCLUDE_DIR

all: subdir $(CAP_SO)

$(CAP_SO): $(SRC:.c=.o)
	$(CC) $(CFLAGS) -shared -Wl,-soname,$@ -o $@ $(SRC:.c=.o) $(LDFLAGS)

subdir:
	@for dir in $(SUBDIRS) ; \
	   do $(MAKE) -C $$dir || exit 1; \
	 done \

clean:
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir clean || exit 1; done
	rm -f *.o *.so *.a *~ include/*~ .depend *.expand


.depend: $(SRC)
	$(CC) -M $(CFLAGS) $(SRC) > $@

sinclude .depend
