CC = mipsel-unknown-elf-gcc
AS = mipsel-unknown-elf-as
LD = mipsel-unknown-elf-ld
DU = mipsel-unknown-elf-objdump

SYS_OBJS = reset.o \
		   giet.o \
		   common.o \
		   ctx_handler.o \
		   drivers.o \
		   exc_handler.o \
		   irq_handler.o \
		   sys_handler.o

APP_OBJS = stdio.o main.o

GIET ?= ../../giet

SYS_PATH = $(GIET)/sys
APP_PATH = $(GIET)/app

SYS_CFLAGS = -Wall -ffreestanding -mno-gpopt -mips32 -I$(SYS_PATH) -I.
APP_CFLAGS = -Wall -ffreestanding -mno-gpopt -mips32 -I$(APP_PATH) -I.

all: sys.bin app.bin

## system compilation

### A COMPLETER
# les fichiers à générer sont :
# * sys.bin
# * reset.o et giet.o
# * les autres fichiers .o de $(SYS_OBJS) issus de fichiers .c
#  * pour la génération des ces fichiers, utilisez la variable $(SYS_CLAGS).

## app compilation

### A COMPLETER
# les fichiers à générer sont :
# * app.bin
# * stdio.o et main.o
#  * pour la génération des ces fichiers, utilisez la variable $(APP_CLAGS).

### special rules

clean:
	rm -f *.o *.bin proc0*

