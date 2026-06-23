
#include "file.h"
#include <stdio.h>
#include <stdlib.h>


int main(void) {
    int max = 10000;
    int len = 100;
    char **words = malloc(max * sizeof(char*));
    for (int i = 0; i < max; i++) {
        words[i] = malloc(len * sizeof(char));
    }

    int result = parse_file_words(max, len, words);
    if (result != 0) {
        printf("Erro ao carregar palavras do arquivo\n");
        return 1;
    }

    // Libera a memória alocada
    for (int i = 0; i < max; i++) {
        free(words[i]);
    }
    free(words);

    return 0;
}