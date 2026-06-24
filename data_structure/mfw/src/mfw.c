#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mfw_limits.h"

int parse_file_words(char** words) {
    int _max = MAX_WORDS;
    int _len = MAX_WORD_LENGTH;
    FILE *_file = NULL;

    // Abre o arquivo para leitura    
    _file = fopen("../mfw/words.txt", "r");

    if (_file == NULL) {
        return 1;
    }
    int i = 0;
    while (fgets(words[i], _len, _file) != NULL && i < _max) {
        words[i][strcspn(words[i], "\n")] = 0;
        i++;
    }
    fclose(_file);
    return 0;
}

char **alloc_words() {
    int _max = MAX_WORDS;
    int _len = MAX_WORD_LENGTH;
    char **words = malloc(_max * sizeof(char*));
    for (int i = 0; i < _max; i++) {
        words[i] = malloc(_len * sizeof(char));
    }
    return words;
}

void free_words(char **words) {
    int _max = MAX_WORDS;
    for (int i = 0; i < _max; i++) {
        free(words[i]);
    }
    free(words);
}
