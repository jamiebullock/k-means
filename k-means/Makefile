# Declaration of variables
CC = gcc
CC_FLAGS = -w  -D_LARGEFILE_SOURCE -D_ANSI_SOURCE -std=c99 -Wall -Wextra -pedantic -O3 -DNDEBUG # -O0 -g -DDEBUG # -O3 -DNDEBUG
LD_FLAGS = -lm

# File names
EXEC = km_test
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC) $(LD_FLAGS)


# To obtain object files
%.o: %.c
	$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)
	rm -f OUTPUT.TXT
