#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void naiveStringMatch(char *text, char *pattern) {
    int textLength = strlen(text);
    int patternLength = strlen(pattern);

    for (int i = 0; i <= textLength - patternLength; i++) {
        int j;
        for (j = 0; j < patternLength; j++) {
            if (text[i + j] != pattern[j])
                break;
        }
        if (j == patternLength)
            printf("Pattern found at shift %d\n", i);
    }
}

int main() {
    char text[1000], pattern[100];

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // Removing trailing newline character

    printf("Enter the pattern: ");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = '\0'; // Removing trailing newline character

    printf("Text: %s\n", text);
    printf("Pattern: %s\n", pattern);
    printf("Naive String Matching Algorithm:\n");
    naiveStringMatch(text, pattern);

    return 0;
}
