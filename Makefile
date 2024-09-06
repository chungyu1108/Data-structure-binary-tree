CC=gcc --std=c99 -g

all: test_bst test_bst_iterator

test_bst: test_bst.c bst.o stack.o list.o
	$(CC) test_bst.c bst.o stack.o list.o -o test_bst

test_bst_iterator: test_bst_iterator.c bst.o stack.o list.o
	$(CC) test_bst_iterator.c bst.o stack.o list.o -o test_bst_iterator

bst.o: bst.c bst.h
	$(CC) -c bst.c

stack.o: stack.c stack.h
	$(CC) -c stack.c

list.o: list.c list.h
	$(CC) -c list.c

clean:
	rm -f *.o test_bst test_bst_iterator
