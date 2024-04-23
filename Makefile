main : src/main.c fdrive.a
	gcc $(CFLAGS) -Iinclude src/main.c -Llib -lfdrive -o bin/main$(CFLAGS)

fdrive.a : command.o tools.o validation.o object.o
	ar rcs lib/libfdrive.a lib/command.o lib/tools.o lib/validation.o lib/object.o

command.o : src/command.c tools.o
	gcc $(CFLAGS) -c -Iinclude src/command.c -o lib/command.o

tools.o : src/tools.c object.o
	gcc $(CFLAGS) -c -Iinclude src/tools.c -o lib/tools.o

object.o : src/object.c validation.o
	gcc $(CFLAGS) -c -Iinclude src/object.c -o lib/object.o

validation.o : src/validation.c init 
	gcc $(CFLAGS) -c -Iinclude src/validation.c -o lib/validation.o

init:
	mkdir -p bin
	mkdir -p lib
