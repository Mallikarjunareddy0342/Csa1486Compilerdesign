#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
double parseExpression(const char **str);
double parseTerm(const char **str);
double parseFactor(const char **str);
double parsePrimary(const char **str);
double parseExpression(const char **str) {
    double result = parseTerm(str);
    while (**str == '+' || **str == '-') {
        char op = **str;
        (*str)++;
        double term = parseTerm(str);

        if (op == '+') {
            result += term;
        } else if (op == '-') {
            result -= term;
        }
    }
    return result;
}
double parseTerm(const char **str) {
    double result = parseFactor(str);
    while (**str == '*' || **str == '/') {
        char op = **str;
        (*str)++;
        double factor = parseFactor(str);
        if (op == '*') {
            result *= factor;
        } else if (op == '/') {
            result /= factor;
        }
    }
    return result;
}
double parseFactor(const char **str) {
    double result = parsePrimary(str);
    while (**str == '^') {
        (*str)++;
        double exponent = parsePrimary(str);
        result = pow(result, exponent);
    }
    return result;
}
double parsePrimary(const char **str) {
    double result;
    if (**str == '(') {
        (*str)++;
        result = parseExpression(str);
        if (**str == ')') {
            (*str)++;
        }
    } else if (isdigit(**str) || **str == '.') {
        result = strtod(*str, (char **)str);
    } else {
        printf("Error: invalid character\n");
        exit(1);
    }
    return result;
}
double evaluate(const char *expression) {
    return parseExpression(&expression);
}
int main() {
    char expression[100];
    printf("Enter an expression: ");
    fgets(expression, sizeof(expression), stdin);
    char *newline = strchr(expression, '\n');
    if (newline) {
        *newline = '\0';
    }
    printf("Result: %f\n", evaluate(expression));
    return 0;
}
