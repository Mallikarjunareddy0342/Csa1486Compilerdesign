#include <stdio.h>
#include <string.h>
#define MAX_RULES 10
#define MAX_PRODUCTION 100
typedef struct {
    char lhs;               
    char rhs[MAX_RULES][MAX_PRODUCTION]; 
    int rhs_count;           
} Production;
void print_grammar(Production grammar[], int size) {
	int i,j;
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
void eliminate_left_factoring(Production *p) {
    char common_prefix[MAX_PRODUCTION];
    int prefix_length = 0;
    int i, j;
    for (i = 0; i < p->rhs_count - 1; i++) {
        for (j = i + 1; j < p->rhs_count; j++) {
            int k = 0;
            while (p->rhs[i][k] && p->rhs[j][k] && p->rhs[i][k] == p->rhs[j][k]) {
                k++;
            }
            if (k > prefix_length) {
                prefix_length = k;
                strncpy(common_prefix, p->rhs[i], k);
                common_prefix[k] = '\0';
            }
        }
    }
    if (prefix_length == 0) {
        printf("No common prefix found for %c\n", p->lhs);
        return;
    }
    char new_non_terminal = p->lhs + '1';
    printf("Eliminating left factoring for %c\n", p->lhs);
    printf("Productions for %c: ", p->lhs);
    for (i = 0; i < p->rhs_count; i++) {
        printf("%s", p->rhs[i]);
        if (i < p->rhs_count - 1) {
            printf(" | ");
        }
    }
    printf("\n");
    printf("Transformed to:\n");
    printf("%c -> %s%c\n", p->lhs, common_prefix, new_non_terminal);
    printf("%c -> ", new_non_terminal);
    for (i = 0; i < p->rhs_count; i++) {
        if (strncmp(p->rhs[i], common_prefix, prefix_length) == 0) {
            char suffix[MAX_PRODUCTION];
            strcpy(suffix, p->rhs[i] + prefix_length);
            if (suffix[0] == '\0') {
                printf("e");
            } else {
                printf("%s", suffix);
            }
            if (i < p->rhs_count - 1) {
                printf(" | ");
            }
        }
    }
    printf("\n");
}
int main() {
    Production grammar[MAX_RULES];
    int n,i,j;
    printf("Enter the number of production rules: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        printf("Enter the non-terminal for rule %d: ", i + 1);
        scanf(" %c", &grammar[i].lhs);
        printf("Enter the number of productions for %c: ", grammar[i].lhs);
        scanf("%d", &grammar[i].rhs_count);
        printf("Enter the productions for %c:\n", grammar[i].lhs);
        for ( j = 0; j < grammar[i].rhs_count; j++) {
            printf("Production %d: ", j + 1);
            scanf("%s", grammar[i].rhs[j]);
        }
    }
    printf("\nGrammar before elimination:\n");
    print_grammar(grammar, n);
    for (i = 0; i < n; i++) {
        eliminate_left_factoring(&grammar[i]);
    }
    return 0;
}
