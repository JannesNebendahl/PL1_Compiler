enum symbolType{function,predicate,variable};

struct entry{
    char *identifier;
    char *value;
    enum symbolType type; 
};

void addSymbolEntry(char *identifier_, char *value_, enum symbolType type_);

struct entry *getSymbolEntry(char *identifier);