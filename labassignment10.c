/*
Catalina Ocampo
COP3502C-0004
Dr. Neslisah Torosdagli
Lab 10 Assignment
April 21, 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define aplphaSIZE 26

struct Trie{
    int count;
    struct Trie *children[26];
};

void insert(struct Trie **trieTree, char *word)
{
    struct Trie *oneTrie = *trieTree;

    if (!oneTrie) {
        oneTrie = (struct Trie *) calloc(1, sizeof(struct Trie));
        *trieTree = oneTrie;
    }
    for (int i = 0; word[i] != '\0'; i++) {
        char c = word[i];
        if (c >= 'a' && c <= 'z') {
            c -= 'a';
            if (!oneTrie->children[c]) {
                oneTrie->children[c] = (struct Trie *) calloc(1, sizeof(struct Trie));
            }
            oneTrie = oneTrie->children[c];
        }
    }
    oneTrie->count++;
}

int numberOfOccurances(struct Trie *trie, char *word)
{
    if (!trie) {
        return 0;
    }
    for (int i = 0; word[i] != '\0'; i++) {
        char c = word[i];
        if (c >= 'a' && c <= 'z') {
            c -= 'a';
            trie = trie->children[c];
            if (!trie) {
                return 0;
            }
        }
    }
    return trie->count;
}

struct Trie *deallocateTrie(struct Trie *trie)
{
    if (!trie) {
        return NULL;
    }
    for (int i = 0; i < aplphaSIZE; i++) {
        trie->children[i] = deallocateTrie(trie->children[i]);
    }
    free(trie);
    return NULL;
}


int main(void)
{
    //read the number of the words in the dictionary
    // parse line  by line, and insert each word to the trie data structure
    struct Trie *trie = NULL;
    char *words[] = {"notaword", "ucf", "no", "note", "corg"};

    for (int i = 0; i < 5; i++) {
        insert(&trie, words[i]);
        printf("%s : %d\n", words[i], numberOfOccurances(trie, words[i]));
    }

    trie = deallocateTrie(trie);

    if (trie != NULL) {
        printf("There is an error in this program\n");
    }
    return 0;
}
