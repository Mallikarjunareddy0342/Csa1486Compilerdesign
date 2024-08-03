#include <stdio.h>
#include <string.h>
#define MAX_RULES 10
#define MAX_PRODUCTION 100
typedef struct {
    char lhs;               
    char rhs[MAX_RULES][MAX_PRODUCTION]; 
    int rhs_count;       
} 
Production;
void print_grammar(Production grammar[], int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        printf("%c -> ", grammar[i].lhs);
        for (j = 0; j < grammar[i].rhs_count; j++) {
            printf("%s", grammar[i].rhs[j]);
            if (j < grammar[i].rhs_count - 1) {
                printf(" | ");
            }
        }
        printf("\n");
    }
}
void eliminate_left_recursion(Production *p) {
    char new_non_terminal = p->lhs + 1; 
    char alpha[MAX_RULES][MAX_PRODUCTION];
    char beta[MAX_RULES][MAX_PRODUCTION];
    int alpha_count = 0, beta_count = 0;
    int i;
    for (i = 0; i < p->rhs_count; i++) {
        if (p->rhs[i][0] == p->lhs) {
            strcpy(alpha[alpha_count++], p->rhs[i] + 1); 
        } else {
            strcpy(beta[beta_count++], p->rhs[i]);
        }
    }
    if (alpha_count == 0) {
        return;
    }
    printf("%c -> ", p->lhs);
    for (i = 0; i < beta_count; i++) {
        printf("%s%c'", beta[i], new_non_terminal);
        if (i < beta_count - 1) {
            printf(" | ");
        }
    }
    printf("\n");
    printf("%c' -> ", new_non_terminal);
    for (i = 0; i < alpha_count; i++) {
        printf("%s%c'", alpha[i], new_non_terminal);
        if (i < alpha_count - 1) {
            printf(" | ");
        }
    }
    printf(" | e\n");
}
int main() {
    Production grammar[MAX_RULES];
    int n;
    printf("Enter the number of production rules: ");
    scanf("%d", &n);
    int i,j;
    for (i = 0; i < n; i++) {
        printf("Enter the non-terminal for rule %d: ", i + 1);
        scanf(" %c", &grammar[i].lhs);
        printf("Enter the number of productions for %c: ", grammar[i].lhs);
        scanf("%d", &grammar[i].rhs_count);
        printf("Enter the productions for %c:\n", grammar[i].lhs);
        for (j = 0; j < grammar[i].rhs_count; j++) {
            printf("Production %d: ", j + 1);
            scanf("%s", grammar[i].rhs[j]);
        }
    }
    printf("\nGrammar before elimination:\n");
    print_grammar(grammar, n);
    for (i = 0; i < n; i++) {
        eliminate_left_recursion(&grammar[i]);
    }
    return 0;
}
