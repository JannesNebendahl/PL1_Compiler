#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbolTable.h"

struct entry symbolTable[100];
int symbolTableIndex = 0;

void addSymbolEntry(char *identifier_, char *value_, enum symbolType type_){
    struct entry symbol;
    symbol.identifier = identifier_;
    symbol.value = value_;
    symbol.type = type_;

    symbolTable[symbolTableIndex] = symbol;
    printf("SYT: Created Entry: identifier=%s, value=%s, type=%s\n", symbolTable[symbolTableIndex].identifier, symbolTable[symbolTableIndex].value, symbolTable[symbolTableIndex].type);

    symbolTableIndex++;
}

struct entry *getSymbolEntry(const *identifier);

