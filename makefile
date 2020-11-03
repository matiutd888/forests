CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2
LDFLAGS =

.PHONY: all clean

all: forests


forests: general_util.o input_util.o bst.o execution_util.o handle_util.o forests.o 
	$(CC) $(LDFLAGS) -o $@ $^

general_util.o: general_util.c general_util.h
	$(CC) $(CFLAGS) -c $<

input_util.o: input_util.c input_util.h general_util.o
	$(CC) $(CFLAGS) -c $<

bst.o: bst.c bst.h general_util.o
	$(CC) $(CFLAGS) -c $<

execution_util.o: execution_util.c execution_util.h bst.o
	$(CC) $(CFLAGS) -c $<

handle_util.o: handle_util.c handle_util.h execution_util.o
	$(CC) $(CFLAGS) -c $<

forests.o: forests.c input_util.h handle_util.h execution_util.h bst.h general_util.h
	gcc -Wall -Wextra -c $<

clean:
	rm -f *.o forests
