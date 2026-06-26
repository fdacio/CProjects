/**
 * gcc list.c ..\list\src\list.c ..\list\src\l_utils.c ..\mfw\src\mfw.c -I..\list\include -I..\mfw\include -o .\build\list.exe; .\build\list.exe
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mfw.h"
#include "mfw_limits.h"
#include "list.h"
#include "l_utils.h"

int main(int argc, char *argv[]) {  
    
    if (argc < 2) {
        printf("Usage: %s <word_search>\n", argv[0]);
        return 1;
    }

    char **words = alloc_words();
    int result = parse_file_words(words);
    if (result != 0) {
        printf("Error! Could not parse words from the file.\n");
        return 1;
    }

    TItemList *list = NULL;
    // Exibe as palavras carregadas
    printf("Adding words to the list...\n");
    srand(time(NULL));
    for (int i = 0; i < MAX_WORDS && words[i][0] != '\0'; i++) {
        int pontos = (rand() % 99) + 1;
        char *nome = words[i];
        int id = get_next_id();
        TItemList *a = new_item_list(id, nome, pontos); // Adiciona a palavra à lista com pontos aleatórios
        add_start_sing_linked(a, &list);
    }

    char *_target = argv[1];
    TItemList *_found = find_item_by_name(_target, list);
    if (_found != NULL) {
        printf("Found item '%s' ID: %d\n", _target, _found->data->id);
    } else {
        printf("Item '%s' not found.\n", _target);
    }

    // Libera a memória alocada
    free_words(words);
    free_list(&list);

    return 0;
}

