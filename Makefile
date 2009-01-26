#	Makefile for Phigs examples

APPS = terkep
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

terkep.o: /usr/include/GL/glut.h /usr/include/GL/freeglut_std.h
terkep.o: /usr/include/GL/gl.h /usr/include/GL/glext.h
terkep.o: /usr/lib/gcc/i686-pc-cygwin/3.4.4/include/stddef.h
terkep.o: /usr/include/GL/glu.h /usr/include/math.h /usr/include/sys/reent.h
terkep.o: /usr/include/_ansi.h /usr/include/newlib.h
terkep.o: /usr/include/sys/config.h /usr/include/machine/ieeefp.h
terkep.o: /usr/include/sys/_types.h /usr/include/sys/lock.h
terkep.o: /usr/include/stdio.h
terkep.o: /usr/lib/gcc/i686-pc-cygwin/3.4.4/include/stdarg.h
terkep.o: /usr/include/sys/types.h /usr/include/machine/_types.h
terkep.o: /usr/include/limits.h /usr/include/features.h
terkep.o: /usr/include/sys/cdefs.h /usr/include/sys/features.h
terkep.o: /usr/include/machine/types.h /usr/include/sys/stdio.h
terkep.o: /usr/include/stdlib.h /usr/include/machine/stdlib.h
terkep.o: /usr/include/alloca.h /usr/include/string.h
terkep.o: /usr/include/sys/string.h datastructure.h stringhandling.h
terkep.o: polishfm.h
datastructure.o: /usr/include/stdio.h /usr/include/_ansi.h
datastructure.o: /usr/include/newlib.h /usr/include/sys/config.h
datastructure.o: /usr/include/machine/ieeefp.h
datastructure.o: /usr/lib/gcc/i686-pc-cygwin/3.4.4/include/stddef.h
datastructure.o: /usr/lib/gcc/i686-pc-cygwin/3.4.4/include/stdarg.h
datastructure.o: /usr/include/sys/reent.h /usr/include/sys/_types.h
datastructure.o: /usr/include/sys/lock.h /usr/include/sys/types.h
datastructure.o: /usr/include/machine/_types.h /usr/include/limits.h
datastructure.o: /usr/include/features.h /usr/include/sys/cdefs.h
datastructure.o: /usr/include/sys/features.h /usr/include/machine/types.h
datastructure.o: /usr/include/sys/stdio.h datastructure.h
stringhandling.o: /usr/include/stdio.h /usr/include/_ansi.h
stringhandling.o: /usr/include/newlib.h /usr/include/sys/config.h
stringhandling.o: /usr/include/machine/ieeefp.h
stringhandling.o: /usr/lib/gcc/i686-pc-cygwin/3.4.4/include/stddef.h
stringhandling.o: /usr/lib/gcc/i686-pc-cygwin/3.4.4/include/stdarg.h
stringhandling.o: /usr/include/sys/reent.h /usr/include/sys/_types.h
stringhandling.o: /usr/include/sys/lock.h /usr/include/sys/types.h
stringhandling.o: /usr/include/machine/_types.h /usr/include/limits.h
stringhandling.o: /usr/include/features.h /usr/include/sys/cdefs.h
stringhandling.o: /usr/include/sys/features.h /usr/include/machine/types.h
stringhandling.o: /usr/include/sys/stdio.h /usr/include/string.h
stringhandling.o: /usr/include/sys/string.h /usr/include/stdlib.h
stringhandling.o: /usr/include/machine/stdlib.h /usr/include/alloca.h
polishfm.o: /usr/include/stdio.h /usr/include/_ansi.h /usr/include/newlib.h
polishfm.o: /usr/include/sys/config.h /usr/include/machine/ieeefp.h
polishfm.o: /usr/lib/gcc/i686-pc-cygwin/3.4.4/include/stddef.h
polishfm.o: /usr/lib/gcc/i686-pc-cygwin/3.4.4/include/stdarg.h
polishfm.o: /usr/include/sys/reent.h /usr/include/sys/_types.h
polishfm.o: /usr/include/sys/lock.h /usr/include/sys/types.h
polishfm.o: /usr/include/machine/_types.h /usr/include/limits.h
polishfm.o: /usr/include/features.h /usr/include/sys/cdefs.h
polishfm.o: /usr/include/sys/features.h /usr/include/machine/types.h
polishfm.o: /usr/include/sys/stdio.h /usr/include/string.h
polishfm.o: /usr/include/sys/string.h stringhandling.h datastructure.h
polishfm.o: polishfm.h
