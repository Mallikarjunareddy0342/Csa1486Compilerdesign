#include <stdio.h>
int main() {
    char ch;
    int whitespace_count = 0;
    int newline_count = 0;
    printf("Enter text (Ctrl+D to end):\n");
    while ((ch = getchar()) != EOF) {
        if (ch == ' ' || ch == '\t') {
            whitespace_count++;
        } else if (ch == '\n') {
            newline_count++;
        }
    }
    printf("Number of whitespace characters: %d\n", whitespace_count);
    printf("Number of newline characters: %d\n", newline_count);
    return 0;
}
