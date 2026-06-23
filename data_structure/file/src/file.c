#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_file_words(int max, int len, char** words) {

    FILE *_file = NULL;
    const char *paths[] = {"src/words.txt", "words.txt", "../src/words.txt", NULL};

    for (int i = 0; paths[i] != NULL; i++) {
        _file = fopen(paths[i], "r");
        if (_file != NULL) {
            break;
        }
    }

    if (_file == NULL) {
        return 1;
    }

    int i = 0;

    while (fgets(words[i], len, _file) != NULL && i < max) {
        words[i][strcspn(words[i], "\n")] = 0;
        i++;
    }

    fclose(_file);

    printf("Words loaded: %d\n", i);

    for(int j = 0; j < 10000; j++)
        printf("%s\n", words[j]);

    return 0;
}