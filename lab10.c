#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Trie {
    struct Trie *children[26];
    int flag; // num of times the word exist
} Trie;

//Print the tree for testing purposes
void printAll(struct Trie* tree, char cur[]) {
    // Stop!
    if (tree == NULL)
    {
        return;
    } 
    // Print this node, if it's a word.
    if (tree->flag)
    {
        printf("%s\n", cur);
    }
    // Safer if we store this.
    int len = strlen(cur);
    // Recursively print all words in each subtree,
    // in alpha order.
    int i;
    for (i=0; i<26; i++) {
    cur[len] = (char)('a'+i);
    cur[len+1] = '\0';
    printAll(tree->children[i], cur);
    }
}

void insert(struct Trie **ppTrie, char *word)
{
    //insert word into the trie
    Trie *tree = *ppTrie;

    while(*word)
    {
        if(tree->children[*word - 'a'] == NULL)
        {
            tree->children[*word - 'a'] = (Trie*) malloc(sizeof(Trie));
            tree->children[*word - 'a']->flag = 0;
            for(int i = 0; i < 26;i++)
                tree->children[*word - 'a']->children[i] = NULL;
        }
        tree = tree->children[*word - 'a'];
        word++;
    }
    //everytime you locate the word, add 1 to the flag
    tree->flag+= 1;
}
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    //traverse trie and find the word. Than return the num of Occurances
    if(pTrie == NULL)
    {
        return 0;
    }
    Trie *tree = pTrie;
    while(*word)
    {
        tree = tree->children[*word - 'a'];
        if(tree == NULL)
        {
            return 0;
        }

        word++;
    }
    return tree->flag;
}
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if(pTrie == NULL)
        return pTrie;
    //recursuvly call deallocateTrie to free children
    for(int i = 0; i < 26; i++)
        deallocateTrie(pTrie->children[i]);
    free(pTrie);
}
int main(void)
{
      Trie *trie = malloc(sizeof(Trie));
      trie->flag = 0;
      for(int x = 0; x<26;x++)
        trie->children[x] = NULL;
      int num;
      //read the number of the words in the dictionary
      FILE *fp = fopen("dictionary.txt","r");
      if(fp == NULL)
      {
        printf("Error...file could not be read.");
        exit(EXIT_FAILURE);
      }
      fscanf(fp, "%d",&num);
      // parse line  by line, and insert each word to the trie data structure
      for(int i=0;i<num;i++){
        char word[100];
        fscanf(fp,"%s", word);
        insert(&trie,word);
      }
      char word[100];
      word[0] = '\0';
      //printAll(trie,word);
      fclose(fp);
      char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
      for (int i=0;i<5;i++)
      {
          printf("\t%s : %d\n",pWords[i], numberOfOccurances(trie, pWords[i]));
     }
    trie = deallocateTrie(trie);
    if (trie != NULL)
       printf("There is an error in this program\n");
    return 0;
}