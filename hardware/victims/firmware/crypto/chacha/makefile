SRC = chacha.c main.c debug-print.c
OBJ = $(SRC:.c=.o)
TARGET = chacha_example

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TARGET)