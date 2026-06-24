#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mfw.h"
#include "mfw_limits.h"

int main(void) {

    char **words = alloc_words();
    int result = parse_file_words(words);
    if (result != 0) {
        printf("Erro ao carregar palavras do arquivo\n");
        return 1;
    }

    // Exibe as palavras carregadas
    // for (int i = 0; i < MAX_WORDS && words[i][0] != '\0'; i++) {
    //     printf("Word %d: %s\n", i, words[i]);
    // }

    char *_target = "nhdsfa";// Palavra a ser buscada

    int found = 0;
    for (int i = 0; i < MAX_WORDS && words[i][0] != '\0'; i++) {
        if (strcmp(words[i], _target) == 0) {
            printf("Word '%s' found in position %d!\n", _target, i);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Word '%s' not found.\n", _target);
    }

    // Libera a memória alocada
    free_words(words);

    return 0;
}

