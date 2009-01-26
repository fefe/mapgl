#	Makefile for Phigs examples

APPS = mapgl
OBJ = $(APPS).o datastructure.o stringhandling.o polishfm.o
SRC = $(APPS).c datastructure.c stringhandling.c polishfm.c

CFLAGS = $(C_OPTS) -I/usr/include
LIBS = -L/usr/X11R6/lib -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm -lpthread
  
application:$(APPS)

stringhandling.o: stringhandling.c stringhandling.h
datastructure.o: datastructure.c datastructure.h
polishfm.o: polishfm.c polishfm.h datastructure.h stringhandling.h

clean:
	rm -f $(APPS) *.raw *.o core a.out

realclean:	clean
	rm -f *~ *.bak *.BAK

.SUFFIXES: c o
.c.o:
	$(CC) -c $(CFLAGS) $<

$(APPS): $(OBJ) 
	$(CC) -o $(APPS) $(CFLAGS) $(OBJ) $(LIBS)

depend:
	makedepend -- $(CFLAGS) $(SRC)

# DO NOT DELETE

