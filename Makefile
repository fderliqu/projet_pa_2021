TARGET=main
CFLAGS= -g -W -Wall -Wextra -O2
SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)

default: $(TARGET)
	
src/%.o: src/%.c
	gcc $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJ)
	gcc $^ -o $@

.PHONY: clean
clean:
	rm -f src/*.o
	rm -f $(TARGET)
