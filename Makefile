CC=gcc
CFLAGS=-Wall -g

OBJ=main.o tree_functions.o queue_functions.o

all: build

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

tema2: $(OBJ)
	$(CC) $^ -o $@

build: $(OBJ)
	$(CC) $^ -o out

clean:
	rm -f $(OBJ) out
