CC=gcc
AR=ar
FLAGS= -Wall -g
MT=myTrie.o

all: frequency
frequency: $(MT)
	$(CC) $(FLAGS) -o frequency $(MT) 
myTrie.o: myTrie.c
	$(CC) $(FLAGS) -c myTrie.c

.PHONY: clean all
clean:
	rm -f *.o *.so frequency

