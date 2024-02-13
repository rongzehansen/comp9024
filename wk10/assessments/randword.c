#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int wordlen = atoi(argv[1]);
    int wordseed = atoi(argv[2]);
    char *randword = malloc(wordlen + 1);
    srand(wordseed);
    int i = 0;
    for (i = 0; i < wordlen; i++) {
        randword[i] = 'a' + rand() % 26;
    }
    randword[i] = '\0';
    printf("%s\n", randword);
    free(randword);
    return 0;
}
