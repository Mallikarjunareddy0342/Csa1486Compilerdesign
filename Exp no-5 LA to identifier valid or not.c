#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#define MAX_IDENTIFIER_LENGTH 100
bool is_valid_identifier(const char *str) {
    int len = strlen(str);
    if (len == 0) {
        return false;
    }
    if (!isalpha(str[0]) && str[0] != '_') {
        return false;
    }
    int i;
    for (i = 1; i < len; i++) {
        if (!isalnum(str[i]) && str[i] != '_') {
            return false;
        }
    }
    return true;
}
int main() {
    char identifier[MAX_IDENTIFIER_LENGTH];
    printf("Enter an identifier to check if it is valid: ");
    scanf("%s", identifier);
    if (is_valid_identifier(identifier)) {
        printf("'%s' is a valid identifier.\n", identifier);
    } else {
        printf("'%s' is not a valid identifier.\n", identifier);
    }
    return 0;
}
