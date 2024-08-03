#include <stdio.h>
#include <string.h>
#define MAX_LINE_LENGTH 1024
int is_line_comment(char *line) {
    char *start = strstr(line, "//");
    if (start != NULL && start == line) {
        return 1;
    }
    start = strstr(line, "/*");
    char end = strstr(line, "/");
    if (start != NULL && end != NULL && start == line) {
        return 1;
    }
    return 0;
}
int main() {
    char line[MAX_LINE_LENGTH];
    printf("Enter a line of code: ");
    fgets(line, MAX_LINE_LENGTH, stdin);
    line[strcspn(line, "\n")] = 0;
    if (is_line_comment(line)) {
        printf("This line is a comment.\n");
    } else {
        printf("This line is not a comment.\n");
    }
    return 0;
}
