TARGET=build/main
CFLAGS= -g -W -Wall -Wextra -O2
SRC=$(wildcard src/*.c)
OBJ=$(patsubst src/%.c, build/%.o, $(SRC))

default: $(TARGET)

$(shell mkdir -p build)

build/%.o: src/%.c
	gcc $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJ)
	gcc $^ -o $@

.PHONY: clean
clean:
	rm -f build/*.o
	rm -f $(TARGET)
