#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
typedef enum {
    TOKEN_NUMBER, TOKEN_PLUS, TOKEN_MINUS, TOKEN_STAR, TOKEN_SLASH, TOKEN_END, TOKEN_INVALID
} TokenType;
typedef struct {
    TokenType type;
    int value;
} Token;
char *input;
size_t pos = 0;
Token getNextToken() {
    while (input[pos] != '\0') {
        if (isspace(input[pos])) {
            pos++;
            continue;
        }
        if (isdigit(input[pos])) {
            int value = 0;
            while (isdigit(input[pos])) {
                value = value * 10 + (input[pos] - '0');
                pos++;
            }
            Token token = { TOKEN_NUMBER, value };
            return token;
        }
        switch (input[pos]) {
            case '+': pos++; return (Token){ TOKEN_PLUS, 0 };
            case '-': pos++; return (Token){ TOKEN_MINUS, 0 };
            case '*': pos++; return (Token){ TOKEN_STAR, 0 };
            case '/': pos++; return (Token){ TOKEN_SLASH, 0 };
            default: return (Token){ TOKEN_INVALID, 0 };
        }
    }
    return (Token){ TOKEN_END, 0 };
}
void parseFactor() {
    Token token = getNextToken();
    if (token.type == TOKEN_NUMBER) {
        printf("PUSH %d\n", token.value);
    } else {
        printf("Error: Expected number\n");
        exit(1);
    }
}
void parseTerm() {
    parseFactor();  
    Token token = getNextToken();
    while (token.type == TOKEN_STAR || token.type == TOKEN_SLASH) {
        if (token.type == TOKEN_STAR) {
            printf("MUL\n");
        } else {
            printf("DIV\n");
        }
        parseFactor(); 
        token = getNextToken();
    }
    pos--;  
}
void parseExpression() {
    parseTerm();  
    Token token = getNextToken();
    while (token.type == TOKEN_PLUS || token.type == TOKEN_MINUS) {
        if (token.type == TOKEN_PLUS) {
            printf("ADD\n");
        } else {
            printf("SUB\n");
        }
        parseTerm();  
        token = getNextToken();
    }
    pos--;  
}
int main() {
    printf("Enter an arithmetic expression: ");
    char buffer[256];
    fgets(buffer, sizeof(buffer), stdin);
    input = buffer;
    parseExpression();
    Token token = getNextToken();
    if (token.type != TOKEN_END) {
        printf("Error: Unexpected input after end of expression\n");
        return 1;
    }
    printf("END\n");
    return 0;
}
