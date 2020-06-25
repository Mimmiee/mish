CFLAGS =-std=gnu11 -Wall -Wextra -Werror -Wmissing-declarations -Wmissing-prototypes -Werror-implicit-function-declaration -Wreturn-type -Wparentheses -Wunused -Wold-style-definition -Wundef -Wshadow -Wstrict-prototypes -Wswitch-default -Wunreachable-code

CC = gcc

all: mish

mish: mish.o execute.o parser.o sighant.o
	$(CC) -o mish mish.o execute.o parser.o sighant.o

mish.o: mish.c mish.h execute.h parser.h sighant.h 
	$(CC) $(CFLAGS) -c mish.c 

execute.o: execute.c execute.h 
	$(CC) $(CFLAGS) -c execute.c 

parser.o: parser.c parser.h 
	$(CC) $(CFLAGS) -c parser.c 

sighant.o: sighant.c sighant.h
	$(CC) $(CFLAGS) -c sighant.c 

clean:
	rm -fr mish core *.o
