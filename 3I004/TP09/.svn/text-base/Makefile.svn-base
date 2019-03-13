
APP_OBJS = stdio.o main0.o main1.o main2.o main3.o

SRC = main_sequential.c

GIET ?= ../../giet

include $(GIET)/../common/Makefile.common

main%.o: main%.c
	$(CC) $(APP_CFLAGS) -c -o $@ $<

