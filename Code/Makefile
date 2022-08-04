#=========================================
# "Cane Pofuente" command for Linux Shell. 
# Inspired by "sl" command of  mtoyoda / sl. 
# All right reserved to mtoyoda.
#
# Alteration by Rombo
#=========================================

CC=gcc
CFLAGS=-O -Wall

all: cane

cane: cane.c cane.h
	$(CC) $(CFLAGS) -o cane cane.c -lncurses

clean:
	rm -f cane

distclean: clean