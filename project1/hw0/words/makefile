# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Target program name
TARGET = program

# Source files
SRCS = main.c wc.c map.c
OBJS = $(SRCS:.c=.o)

# Default target: build the program
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile .c to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up binaries
clean:
	rm -f $(TARGET) $(OBJS)
