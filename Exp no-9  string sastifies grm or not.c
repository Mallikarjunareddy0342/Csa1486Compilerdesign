#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
bool checkGrammar(const char *str) {
    int length = strlen(str);
    if (length == 0) {
        return false;
    }
    if (!isupper(str[0])) {
        return false;
    }
    if (str[length - 1] != '.') {
        return false;
    }
    int i;
    for (i = 1; i < length - 1; i++) {
        if (!isalpha(str[i]) && str[i] != ' ') {
            return false;
        }
    }
    return true;
}
int main() {
    char input[100];
    printf("Enter a sentence: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    if (checkGrammar(input)) {
        printf("The sentence satisfies the grammar rules.\n");
    } else {
        printf("The sentence does not satisfy the grammar rules.\n");
    }
}
