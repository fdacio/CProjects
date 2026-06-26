/**
 * gcc tree.c ..\tree\src\tree.c ..\tree\src\t_utils.c ..\mfw\src\mfw.c -I..\tree\include -I..\mfw\include -o .\build\tree.exe; .\build\tree.exe
 */
#include <stdio.h>
#include <stdlib.h>
#include "mfw.h"
#include "mfw_limits.h"
#include "tree.h"
#include "t_utils.h"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Usage: %s <word_search>\n", argv[0]);
        return 1;
    }

    //Allocate memory for words and parse them from the file
    char **words = alloc_words();
    int result = parse_file_words(words);
    if (result != 0) {
        printf("Error! Could not parse words from the file.\n");
        return 1;
    }

    TNode *root = NULL;
    printf("Adding words to the tree...\n");
    for (int i = 0; i < MAX_WORDS && words[i][0] != '\0'; i++) {
        insert_node(&root, words[i]);
    }

    char *_target = argv[1];
    TNode *_found = search_node(root, _target);
    if (_found != NULL) {
        printf("Found node '%s'\n", _target);
    } else {
        printf("Node '%s' not found.\n", _target);
    }

    // Free allocated memory
    free_words(words);
    free_tree(root);

    return 0;
}
