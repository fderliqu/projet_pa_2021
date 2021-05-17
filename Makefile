TARGET=project
CFLAGS=-g -W -Wall -Wextra -MMD -02
LDFLAGS=-lm
SRC=./src/$(wildcard *.c)
DEPS=$(SRC:.c=.d)
OBJ=./lib/$(SRC:.c=.o)
	
default: $(TARGET)
	
.c.o:
    gcc $(CFLAGS) -c $<
	
$(TARGET): $(OBJ)
    gcc $(LDFLAGS) $^ -o $@
	
-include $(DEPS)
	
.PHONY: clean
	
clean:
	
    rm -f *.o
	
    rm -f $(TARGET)
