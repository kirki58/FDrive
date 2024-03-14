main : src/main.c command.o
	gcc $(CFLAGS) -Iinclude src/main.c lib/command.o lib/tools.o -o bin/main

command.o : src/command.c tools.o
	gcc $(CFLAGS) -c -Iinclude src/command.c -o lib/command.o

tools.o : src/tools.c
	gcc $(CFLAGS) -c -Iinclude src/tools.c -o lib/tools.o