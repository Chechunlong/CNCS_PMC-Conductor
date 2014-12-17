include ../../../vxworks/config/config-cygwin-vxworks-x86
CFLAGS+=-I../../../vxWorks -Wall

CFLAGS+=-D HAVE_STDIO

all : $(DIST_ROOT)/f8_fix.o

$(DIST_ROOT)/f8_fix.o : f8_fix.o
	cp $^ $@