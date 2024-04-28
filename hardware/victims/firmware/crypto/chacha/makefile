CC = gcc
CFLAGS = -Wall
LDFLAGS =

# List of source files
SRCS = chacha.c openssl_chacha.c openssl_ctype.c
OBJS = $(SRCS:.c=.o)

# The main target
chacha: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

# Rule for compiling C files
%.o: %.c
	$(CC) $(CFLAGS) -DPC_DEBUG -c -o $@ $<