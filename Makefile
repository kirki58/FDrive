main : src/main.c command.o
	gcc $(CFLAGS) -Iinclude src/main.c lib/command.o -o bin/main

command.o : src/command.c
	gcc $(CFLAGS) -c -Iinclude src/command.c -o lib/command.o