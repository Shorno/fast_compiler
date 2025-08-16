CC = gcc
CFLAGS = -Wall -g

# Try to detect flex/bison automatically, fallback to win_flex/win_bison
FLEX = $(shell where flex 2>nul || echo win_flex)
BISON = $(shell where bison 2>nul || echo win_bison)

# Alternative: Set explicit paths if tools are in non-standard locations
# FLEX = C:\tools\winflexbison\win_flex.exe
# BISON = C:\tools\winflexbison\win_bison.exe

SOURCES = main.c ast.c parser.tab.c lex.yy.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = compiler.exe

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
	-del /f *.o $(TARGET) parser.tab.c parser.tab.h lex.yy.c 2>nul
	@echo Clean completed

test: $(TARGET)
	@echo Testing basic expressions...
	@echo 4 + 2 | $(TARGET)
	@echo x = 10 | $(TARGET)
	@echo (2 + 3) * 4 | $(TARGET)

# Interactive mode for testing
run: $(TARGET)
	@echo Starting compiler REPL...
	$(TARGET)

# Show tool versions for debugging
info:
	@echo Compiler: $(CC)
	@echo Flex: $(FLEX)
	@echo Bison: $(BISON)
	@$(CC) --version | head -1
	@$(FLEX) --version 2>nul || echo Flex not found
	@$(BISON) --version | head -1 2>nul || echo Bison not found

.PHONY: all clean test run info
