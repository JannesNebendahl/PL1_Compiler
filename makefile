objects = parser.o scanner.o 
CC = gcc
LEX = flex
YACC = bison

all: pl1c
pl1c: $(objects)
		$(CC) -o $@ $^
parser.c: parser.y
		$(YACC) -d $< -o parser.c
scanner.c: scanner.l
		$(LEX) -t $< > $@

scanner.o : parser.h

parser.h : parser.y