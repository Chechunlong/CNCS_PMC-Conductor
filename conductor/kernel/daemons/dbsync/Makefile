include ../../../vxworks/config/config-cygwin-vxworks-x86
CFLAGS+=-I../../../vxWorks -Wall

CFLAGS+=-D HAVE_STDIO

all : $(DIST_ROOT)/dbsync.o

$(DIST_ROOT)/dbsync.o : dbsync.o
	cp $^ $@