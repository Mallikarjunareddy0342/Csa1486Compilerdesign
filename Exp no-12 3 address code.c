#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100
typedef struct {
    char result[10];
    char arg1[10];
    char op[2];
    char arg2[10];
} TAC;
TAC tac[MAX]; 
int tac_index = 0; 
int temp_count = 0;
typedef struct {
    char items[MAX][10];
    int top;
} Stack;
void initStack(Stack *s) {
    s->top = -1;
}
int isEmpty(Stack *s) {
    return s->top == -1;
}
void push(Stack *s, char *item) {
    if (s->top < MAX - 1) {
        strcpy(s->items[++(s->top)], item);
    }
}
void pop(Stack *s, char *item) {
    if (!isEmpty(s)) {
        strcpy(item, s->items[(s->top)--]);
    }
}
void peek(Stack *s, char *item) {
    if (!isEmpty(s)) {
        strcpy(item, s->items[s->top]);
    }
}
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}
void infixToPostfix(char *infix, char *postfix) {
    Stack stack;
    initStack(&stack);
    int i = 0, k = 0;
    char ch;
    char temp[10];
    while ((ch = infix[i++]) != '\0') {
        if (isspace(ch)) {
            continue;
        }
        if (isalnum(ch)) {
            postfix[k++] = ch;
        } else if (ch == '(') {
            temp[0] = ch;
            temp[1] = '\0';
            push(&stack, temp);
        } else if (ch == ')') {
            while (!isEmpty(&stack) && strcmp(stack.items[stack.top], "(") != 0) {
                pop(&stack, temp);
                postfix[k++] = temp[0];
            }
            pop(&stack, temp); 
        } else if (strchr("+-*/", ch)) {
            temp[0] = ch;
            temp[1] = '\0';
            while (!isEmpty(&stack) && precedence(stack.items[stack.top][0]) >= precedence(ch)) {
                pop(&stack, temp);
                postfix[k++] = temp[0];
            }
            push(&stack, temp);
        }
    }
    while (!isEmpty(&stack)) {
        pop(&stack, temp);
        postfix[k++] = temp[0];
    }
    postfix[k] = '\0';
}
void generateTAC(char *postfix) {
    Stack stack;
    initStack(&stack);
    int i = 0;
    char ch;
    char op1[10], op2[10], result[10];
    char temp[10];
    while ((ch = postfix[i++]) != '\0') {
        if (isalnum(ch)) {
            temp[0] = ch;
            temp[1] = '\0';
            push(&stack, temp);
        } else if (strchr("+-*/", ch)) {
            pop(&stack, op2); 
            pop(&stack, op1);
            sprintf(result, "t%d", temp_count++); 
            strcpy(tac[tac_index].result, result);
            strcpy(tac[tac_index].arg1, op1);
            sprintf(tac[tac_index].op, "%c", ch);
            strcpy(tac[tac_index].arg2, op2);
            tac_index++;
            push(&stack, result); 
        }
    }
}
int main() {
    char expression[MAX];
    char postfix[MAX];
    printf("Enter an arithmetic expression: ");
    fgets(expression, sizeof(expression), stdin);
    size_t len = strlen(expression);
    if (len > 0 && expression[len-1] == '\n') {
        expression[len-1] = '\0';
    }
    infixToPostfix(expression, postfix);
    generateTAC(postfix);
    printf("Three-address code for the given expression:\n");
    int i;
    for (i = 0; i < tac_index; i++) {
        printf("%s = %s %s %s\n", tac[i].result, tac[i].arg1, tac[i].op, tac[i].arg2);
    }
    return 0;
}
