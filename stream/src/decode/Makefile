# Makefile

# sub directory
SUBDIRS =  pcapf eth ip tcp udp null


# src file
SRC = in_cksum.c
CFLAGS_CORE = $(CFLAGS)

# To make it visible
export CC CCPP ROOT_DIR CFLAGS LDFLAGS INCLUDE_DIR

# log parametrization for core
CFLAGS_CORE += -DLOG_COMPONENT=-1

all: subdir libdissector.a


libdissector.a: $(SRC:.c=.o)
	ar rcs $@ $(SRC:.c=.o)
	ranlib $@


subdir:
	@for dir in $(SUBDIRS) ; \
	   do $(MAKE) -C $$dir || exit 1; \
	 done \

clean:
	@for dir in $(SUBDIRS); do $(MAKE) -C $$dir clean || exit 1;  done
	rm -f *.o *.so *.a *~ include/*~ .depend *.expand


.depend: $(SRC) dis_log.c
	@for dir in $(SUBDIRS) ; do cp -a dis_log.c $$dir/dis_log.c; done
	$(CC) -M $(CFLAGS_CORE) $(SRC) > $@


# custom to use CFLAGS_CORE
.c.o:
	$(CC) -c $< -o $@ $(CFLAGS_CORE)


ifdef SRC
sinclude .depend
endif
