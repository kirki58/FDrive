main : src/main.c command.o
	gcc $(CFLAGS) -Iinclude src/main.c lib/command.o lib/tools.o lib/validation.o -o bin/main$(CFLAGS)

command.o : src/command.c tools.o
	gcc $(CFLAGS) -c -Iinclude src/command.c -o lib/command.o

tools.o : src/tools.c validation.o
	gcc $(CFLAGS) -c -Iinclude src/tools.c -o lib/tools.o
	
validation.o : src/validation.c
	gcc $(CFLAGS) -c -Iinclude src/validation.c -o lib/validation.o