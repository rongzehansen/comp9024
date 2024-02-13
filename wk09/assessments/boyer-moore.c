#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALPHAPAT_LENGTH 128
#define MAX_TEXT_LENGTH 1024
#define TEXT_FORMAT_STRING "%[^\n]%*c"

#define min(a, b) (((a) < (b)) ? (a) : (b))

int *lastOccurrence(char *pattern, char *alphabet) {
    int alphalen = strlen(alphabet);
    int patlen = strlen(pattern);
    int *L = malloc(sizeof(int) * MAX_ALPHAPAT_LENGTH);
    memset(L, -1, sizeof(int) * MAX_ALPHAPAT_LENGTH);
    for (int i = 0; i < alphalen; i++) {
        for (int j = 0; j < patlen; j++) {
            if (alphabet[i] == pattern[j]) {
                L[(int)alphabet[i]] = j;
            }
        }
    }
    return L;
}

int BoyerMooreMatch(char *T, char *P, int *L) {
    int textlen = strlen(T);
    int patlen = strlen(P);
    int i = patlen - 1;
    int j = patlen - 1;
    while (i < textlen) {
        if (T[i] == P[j]) {
            if (j == 0) {
                return i;
            }
            else {
                i--;
                j--;
            }
        }
        else {
            i += (patlen - min(j, 1 + L[(int)T[i]]));
            j = patlen - 1;
        }
    }
    return -1;
}

int main(void) {
    char A[MAX_ALPHAPAT_LENGTH];
    char T[MAX_TEXT_LENGTH];
    char P[MAX_ALPHAPAT_LENGTH];
    printf("Enter alphabet: ");
    scanf(TEXT_FORMAT_STRING, A);
    printf("Enter text: ");
    scanf(TEXT_FORMAT_STRING, T);
    printf("Enter pattern: ");
    scanf(TEXT_FORMAT_STRING, P);
    printf("\n");
    int *L = lastOccurrence(P, A);
    for (int i = 0; i < MAX_ALPHAPAT_LENGTH; i++) {
        for (int j = 0; j < strlen(A); j++) {
            if (i == (int)A[j]) {
                printf("L[%c] = %d\n", i, L[i]);
            }
        }   
    }
    printf("\n");
    int pos = BoyerMooreMatch(T, P, L);
    if (pos == -1) {
        printf("No match.\n");
    }
    else {
        printf("Match found at position %d.\n", pos);
    }
    free(L);
    return 0;
}
