#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SYMBOLS 100
#define MAX_NAME_LEN 50
typedef struct {
    char name[MAX_NAME_LEN];
    char type[MAX_NAME_LEN];
    int scope;
} Symbol;
typedef struct {
    Symbol symbols[MAX_SYMBOLS];
    int count;
} SymbolTable;
void initialize(SymbolTable *table) {
    table->count = 0;
}
void insert(SymbolTable *table, const char *name, const char *type, int scope) {
    if (table->count >= MAX_SYMBOLS) {
        printf("Symbol table is full.\n");
        return;
    }
    int i;
    for (i = 0; i < table->count; i++) {
        if (strcmp(table->symbols[i].name, name) == 0 && table->symbols[i].scope == scope) {
            printf("Duplicate symbol found in the same scope.\n");
            return;
        }
    }
    strcpy(table->symbols[table->count].name, name);
    strcpy(table->symbols[table->count].type, type);
    table->symbols[table->count].scope = scope;
    table->count++;
}
int lookup(SymbolTable *table, const char *name, int scope) {
	int i;
    for (i = 0; i < table->count; i++) {
        if (strcmp(table->symbols[i].name, name) == 0 && table->symbols[i].scope == scope) {
            return i;
        }
    }
    return -1;
}
void display(SymbolTable *table) {
    printf("Symbol Table:\n");
    printf("Name\tType\tScope\n");
    int i;
    for (i = 0; i < table->count; i++) {
        printf("%s\t%s\t%d\n", table->symbols[i].name, table->symbols[i].type, table->symbols[i].scope);
    }
}
int main() {
    SymbolTable table;
    initialize(&table);
    int choice;
    char name[MAX_NAME_LEN];
    char type[MAX_NAME_LEN];
    int scope;
    while (1) {
        printf("\nSymbol Table Operations:\n");
        printf("1. Insert\n");
        printf("2. Lookup\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter symbol name: ");
                scanf("%s", name);
                printf("Enter symbol type: ");
                scanf("%s", type);
                printf("Enter symbol scope: ");
                scanf("%d", &scope);
                insert(&table, name, type, scope);
                break;
            case 2:
                printf("Enter symbol name: ");
                scanf("%s", name);
                printf("Enter symbol scope: ");
                scanf("%d", &scope);
                int index = lookup(&table, name, scope);
                if (index != -1) {
                    printf("Symbol found: %s\t%s\t%d\n", table.symbols[index].name, table.symbols[index].type, table.symbols[index].scope);
                } else {
                    printf("Symbol not found.\n");
                }
                break;
            case 3:
                display(&table);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}





Symbol Table Operations:
1. Insert
2. Lookup
3. Display
4. Exit
Enter your choice: 1
Enter symbol name: x
Enter symbol type: int
Enter symbol scope: 1

Symbol Table Operations:
1. Insert
2. Lookup
3. Display
4. Exit
Enter your choice: 1
Enter symbol name: y
Enter symbol type: float
Enter symbol scope: 1

Symbol Table Operations:
1. Insert
2. Lookup
3. Display
4. Exit
Enter your choice: 1
Enter symbol name: x
Enter symbol type: int
Enter symbol scope: 2

Symbol Table Operations:
1. Insert
2. Lookup
3. Display
4. Exit
Enter your choice: 2
Enter symbol name: x
Enter symbol scope: 1
Symbol found: x int     1

Symbol Table Operations:
1. Insert
2. Lookup
3. Display
4. Exit
Enter your choice: 2
Enter symbol name: z
Enter symbol scope: 1
Symbol not found.

Symbol Table Operations:
1. Insert
2. Lookup
3. Display
4. Exit
Enter your choice: 3
Symbol Table:
Name    Type    Scope
x       int     1
y       float   1
x       int     2

Symbol Table Operations:
1. Insert
2. Lookup
3. Display
4. Exit
Enter your choice: 4

