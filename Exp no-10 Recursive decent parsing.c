#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
typedef enum {
    NUM, PLUS, MINUS, MULT, DIV, LPAREN, RPAREN, END
} Token;
Token currentToken;
int number; 
void nextToken(const char **input) {
    while (isspace(**input)) (*input)++; 
    if (isdigit(**input)) {
        number = 0;
        while (isdigit(**input)) {
            number = number * 10 + (**input - '0');
            (*input)++;
        }
        currentToken = NUM;
    } else {
        switch (**input) {
            case '+': currentToken = PLUS; break;
            case '-': currentToken = MINUS; break;
            case '*': currentToken = MULT; break;
            case '/': currentToken = DIV; break;
            case '(': currentToken = LPAREN; break;
            case ')': currentToken = RPAREN; break;
            case '\0': currentToken = END; break;
            default: printf("Error: invalid character\n"); exit(1);
        }
        if (currentToken != END) (*input)++;
    }
}
void match(Token expected, const char **input) {
    if (currentToken == expected) {
        nextToken(input);
    } else {
        printf("Error: unexpected token\n");
        exit(1);
    }
}
void E(const char **input);
void E_prime(const char **input);
void T(const char **input);
void T_prime(const char **input);
void F(const char **input);
void E(const char **input) {
    T(input);
    E_prime(input);
}
void E_prime(const char **input) {
    if (currentToken == PLUS) {
        match(PLUS, input);
        T(input);
        E_prime(input);
    } else if (currentToken == MINUS) {
        match(MINUS, input);
        T(input);
        E_prime(input);
    }
}
void T(const char **input) {
    F(input);
    T_prime(input);
}
void T_prime(const char **input) {
    if (currentToken == MULT) {
        match(MULT, input);
        F(input);
        T_prime(input);
    } else if (currentToken == DIV) {
        match(DIV, input);
        F(input);
        T_prime(input);
    }
}
void F(const char **input) {
    if (currentToken == LPAREN) {
        match(LPAREN, input);
        E(input);
        match(RPAREN, input);
    } else if (currentToken == NUM) {
        match(NUM, input);
    } else {
        printf("Error: unexpected token in factor\n");
        exit(1);
    }
}
int main() {
    const char *input = "3 + 5 * ( 10 - 2 )";
    nextToken(&input);
    E(&input);

    if (currentToken == END) {
        printf("Parsing successful\n");
    } else {
        printf("Error: unexpected token at the end\n");
    }
    return 0;
}
