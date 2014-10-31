INSTALL_PREFIX=/usr

all: checkjpg
	
checkjpg: Makefile main.c
	gcc main.c -O3 -std=c11 -o checkjpg

install:
	install checkjpg ${INSTALL_PREFIX}/bin
