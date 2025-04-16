#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to compute the LPS (Longest Proper Prefix which is also a Suffix) array
void computeLPSArray(char *pattern, int M, int *lps) {
    int len = 0; // Length of the previous longest prefix suffix

    lps[0] = 0; // lps[0] is always 0

    int i = 1;
    while (i < M) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Function to perform string matching using KMP algorithm
void KMPSearch(char *pattern, char *text) {
    int M = strlen(pattern);
    int N = strlen(text);

    int *lps = (int *)malloc(sizeof(int) * M);
    if (lps == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    computeLPSArray(pattern, M, lps);

    int i = 0; // Index for text[]
    int j = 0; // Index for pattern[]

    while (i < N) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }

        if (j == M) {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];
        } else if (i < N && pattern[j] != text[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }

    free(lps);
}

int main() {
    char text[1000], pattern[1000];

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // Remove newline character

    printf("Enter the pattern: ");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = '\0'; // Remove newline character

    printf("Text: %s\n", text);
    printf("Pattern: %s\n", pattern);
    printf("KMP String Matching Algorithm:\n");
    KMPSearch(pattern, text);

    return 0;
}
