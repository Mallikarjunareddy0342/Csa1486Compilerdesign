#include <stdio.h>
void countCharactersWordsLines(int *charCount, int *wordCount, int *lineCount) {
    char ch;
    int inWord = 0;
    *charCount = *wordCount = *lineCount = 0;
    while ((ch = getchar()) != EOF) {
        (*charCount)++;
        if (ch == '\n') {
            (*lineCount)++;
        }
        if (isspace(ch)) {
            if (inWord) {
                inWord = 0;
                (*wordCount)++;
            }
        } else {
            inWord = 1;
        }
    }
    if (inWord) {
        (*wordCount)++;
    }
}
int main() {
    int charCount, wordCount, lineCount;
    printf("Enter text (Ctrl+D to end input on Unix, Ctrl+Z on Windows):\n");
    countCharactersWordsLines(&charCount, &wordCount, &lineCount);
    printf("Characters: %d\n", charCount);
    printf("Words: %d\n", wordCount);
    printf("Lines: %d\n", lineCount);
    return 0;
}
