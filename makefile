CC=gcc
CFLAGS=-I. -g -w
DEPS = find.h
OBJ = find.o print.o
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
find: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
