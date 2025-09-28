CFLAGS = -fPIC -Wall
TRASH = prog prog-a prog-so a.out *.o *.a *.so *outfile*


%.o:    %.c
	cc $< -c -o $@


all:    prog prog-a prog-so


prog:   const.c fun.c prog.c
	cc const.c fun.c prog.c -o prog

prog-a: prog.c liboutput_static.a
	cc -L. prog.c liboutput_static.a -o  prog-a

prog-so:  prog.c liboutput.so
	LD_LIBRARY_PATH='pwd'
	cc -L. prog.c liboutput.so -o prog-so


liboutput_static.a: const.o fun.o
	ar -rcs liboutput_static.a const.o fun.o

liboutput.so: const.o fun.o
	cc -shared fun.o const.o -o liboutput.so


test: prog prog-a prog-so
	./prog > run1-outfile 2>&1
	./prog-a > run1-outfile-a 2>&1
	./prog-so > run1-outfile-so 2>&1
	cmp run1-outfile run1-outfile-a && cmp run1-outfile run1-outfile-so

	./prog 123 > run2-outfile 2>&1
	./prog-a 123 > run2-outfile-a 2>&1
	./prog-so 123 > run2-outfile-so 2>&1
	cmp run2-outfile run2-outfile-a && cmp run2-outfile run2-outfile-so

	./prog 1 2 3 > run3-outfile 2>&1
	./prog-a 1 2 3 > run3-outfile-a 2>&1
	./prog-so 1 2 3 > run3-outfile-so 2>&1
	cmp run3-outfile run3-outfile-a && cmp run3-outfile run3-outfile-so


clean:
	rm -f $(TRASH)