# Compiler and Flags
CC = gcc
CFLAGS = -Iinclude
DEPS = HTTP_Server.h Response.h Routes.h
exec = server
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g -Wall -lm -ldl -fPIC -rdynamic -pthread -I./include

# Build the executable
$(exec): $(objects)
	$(CC) $(objects) $(flags) -o $(exec)

# Rule to compile .c files into .o files
%.o: %.c $(DEPS)
	$(CC) -c $(flags) $< -o $@

# Clean up generated files
clean:
	-rm -f *.out
	-rm -f *.o
	-rm -f *.a
	-rm -f src/*.a
	-rm -f src/*.o
	-rm -f $(exec)
