#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX_IDENTIFIER_LENGTH 31
void skipWhitespaceAndComments(FILE *file) {
    int c;
    while ((c = fgetc(file)) != EOF) {
        if (isspace(c)) {
            continue;
        } else if (c == '/') {
            if ((c = fgetc(file)) == '/') {
                while ((c = fgetc(file)) != EOF && c != '\n');
            } else if (c == '*') {
                while ((c = fgetc(file)) != EOF) {
                    if (c == '*') {
                        if ((c = fgetc(file)) == '/') break;
                    }
                }
            } else {
                ungetc(c, file);
                return;
            }
        } else {
            ungetc(c, file);
            return;
        }
    }
}
int isOperator(char c) {
    char operators[] = "+-*/%=";
    int i;
    for (i = 0; i < strlen(operators); i++) {
        if (c == operators[i]) return 1;
    }
    return 0;
}
void printToken(const char *token) {
    if (isdigit(token[0])) {
        printf("Constant: %s\n", token);
    } else {
        printf("Identifier: %s\n", token);
    }
}
void lexicalAnalyzer(FILE *file) {
    int c;
    char buffer[MAX_IDENTIFIER_LENGTH + 1];
    int index = 0;
    while ((c = fgetc(file)) != EOF) {
        if (isspace(c)) {
            continue;
        } else if (isalpha(c) || c == '_') {
            buffer[index++] = c;
            while ((c = fgetc(file)) != EOF && (isalnum(c) || c == '_')) {
                if (index < MAX_IDENTIFIER_LENGTH) {
                    buffer[index++] = c;
                }
            }
            buffer[index] = '\0';
            printToken(buffer);
            index = 0;
            if (c != EOF) ungetc(c, file);
        } else if (isdigit(c)) {
            buffer[index++] = c;
            while ((c = fgetc(file)) != EOF && isdigit(c)) {
                if (index < MAX_IDENTIFIER_LENGTH) {
                    buffer[index++] = c;
                }
            }
            buffer[index] = '\0';
            printToken(buffer);
            index = 0;
            if (c != EOF) ungetc(c, file);
        } else if (isOperator(c)) {
            printf("Operator: %c\n", c);
        } else {
            skipWhitespaceAndComments(file);
        }
    }
}
int main() {
    printf("Enter the code (end input with Ctrl+D):\n");
    lexicalAnalyzer(stdin);
    return 0;
}
