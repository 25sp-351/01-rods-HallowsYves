CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11
OUTPUT = rod_cut

SOURCES = rod_cut.c rod_input.c rod_logic.c rod_parse.c

# Convert .c files to .o files
OBJECTS = $(SOURCES:.c=.o)

all: $(OUTPUT)

# Link object files into final executable
$(OUTPUT): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

# Compile each source file into an object file
%.o: %.c rod_cut.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OUTPUT) $(OBJECTS)
