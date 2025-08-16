CC = gcc
CFLAGS = -Wall -g
FLEX = flex
BISON = bison

SOURCES = main.c ast.c parser.tab.c lex.yy.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = compiler

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

parser.tab.c parser.tab.h: parser.y
	$(BISON) -d parser.y

lex.yy.c: lexer.l parser.tab.h
	$(FLEX) lexer.l

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) $(TARGET) parser.tab.c parser.tab.h lex.yy.c

test: $(TARGET)
	@echo "Testing basic expressions..."
	@echo "2 + 3" | ./$(TARGET)
	@echo "5 * 4 - 2" | ./$(TARGET)
	@echo "10 / 2 + 1" | ./$(TARGET)

.PHONY: all clean test
