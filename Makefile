TARGET=main
CFLAGS= -g -W -Wall -Wextra -MMD -02
SRC=(wildcard src/*.c)
OBJ=lib/$(SRC:.c=.o)

$(shell mkdir -p lib)
	
default: $(TARGET)
	
.c.o:
    gcc $(CFLAGS) -c $<
	
$(TARGET): $(OBJ)
    gcc $^ -o $@
	
.PHONY: clean
	
clean:
    rm -f lib/*.o
    rm -f $(TARGET)
