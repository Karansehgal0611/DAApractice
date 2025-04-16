#include <stdio.h>
#include <string.h>

#define d 256 // Number of characters in the input alphabet

void rabinKarp(char *text, char *pattern, int q) {
    int textLength = strlen(text);
    int patternLength = strlen(pattern);
    int i, j;
    int p = 0; // Hash value for pattern
    int t = 0; // Hash value for text
    int h = 1;

    // Calculate hash value of pattern and first window of text
    for (i = 0; i < patternLength - 1; i++)
        h = (h * d) % q;

    for (i = 0; i < patternLength; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= textLength - patternLength; i++) {
        // Check hash values of current window of text and pattern
        if (p == t) {
            // Check for match character by character
            for (j = 0; j < patternLength; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }
            if (j == patternLength)
                printf("Pattern found at shifts %d\n", i);
        }

        // Calculate hash value for next window of text: Remove leading digit, add trailing digit
        if (i < textLength - patternLength) {
            t = (d * (t - text[i] * h) + text[i + patternLength]) % q;

            // Handle negative hash value
            if (t < 0)
                t = (t + q);
        }
    }
}

int main() {
    char text[1000];
    char pattern[1000];
    int q;

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // Remove newline character

    printf("Enter the pattern: ");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = '\0'; // Remove newline character

    printf("Enter the prime number for hashing: ");
    scanf("%d", &q);

    printf("Text: %s\n", text);
    printf("Pattern: %s\n", pattern);
    printf("Rabin-Karp String Matching Algorithm:\n");
    rabinKarp(text, pattern, q);

    return 0;
}
