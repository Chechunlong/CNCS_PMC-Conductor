MODULE_NAME=libdbsync
MODULE_TYPE=shared_library
CFLAGS=-I../include
FileDescription="Site data maintenance"
NEED_LIBS=fbd cobj f8mm f8res rtk utils vbus zlib_shared
WIN32_LIBS=ws2_32.lib
LINUX_LIBS=
SOURCES:=$(wildcard *.c)

include $(TOPDIR)/Rules.mk
