#ifndef _MY_TRIE_
#define _MY_TRIE_
#define NUM_LETTERS ((int)26)
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <math.h>
typedef enum
{ FALSE = 0, TRUE = 1 } boolean;
int num_heads = 0;
char *word;

typedef struct node
{ 
    char letter; 
    long unsigned int count;  
    int is_end; 
    int num_child; 
    struct node *children[NUM_LETTERS];
} node;

 
int getletter (char c) 
{  
    int numletter = -1;
    if (c <= 'z' && c >= 'a') 
        numletter = c - 'a';
    else if (c <= 'Z' && c >= 'A')    
        numletter = c - 'A';
    else if (c == '\t' || c == '\n' || c == '\r' || c == ' ' || c=='\0' ) 
        return -1; 
    else if(c==EOF)
        return -3;
    else  
        return -2;
    return numletter;

}


node ** build_trie (node **first, int(*index)(char)) 
{
    
    while (TRUE)
        {
            int c = (*index)(getchar());
            if (c == -1 || c==-2){
                continue;
            }
            else if(c==-3)
                return first;
            if (first[c] == NULL)
            {
                first[c] = (node *) calloc (1,sizeof (node));
                first[c]->letter ='a'+c;
                first[c]->num_child = 0;
                first[c]->is_end = FALSE;
                num_heads++;
            }
            node * temp = &(*(first[c]));
            int c2 = (*index)(getchar());
            while (c2 != -1)
            {
                if (c2 == -2) {
                        char let = getchar();
                        c2 = (*index)(let);
                        continue;
                    }
                else if (c2==-3)
                    break;
                
                 if (temp->children[c2] == NULL)
                {
                    temp->num_child++;
                    temp->children[c2] = (node *) calloc (1,sizeof (node));
                    temp->children[c2]->is_end = FALSE;
                    temp->children[c2]->letter = 'a'+c2;
                }
                temp = &(*(temp->children[c2]));
                char let = getchar();           
                c2 = (*index)(let);
            } 
            temp->count += 1;
            temp->is_end = TRUE;
    }
    return first;
}


void printTrieUp (node ** head, int l, int childs) 
{
    int rest_child = childs;
    for (int i = 0; i < NUM_LETTERS && rest_child > 0; i++)
    {
        if (head[i] != NULL)
	    {
            if (childs-rest_child>0)
                l--;	  
            char c = head[i]->letter;
            word=(char*)realloc(word,(l+1)*sizeof(char));
            if(word==NULL)
                exit(1);
            word[l] = c;  
            l++;  
            rest_child--;
            if (head[i]->is_end == TRUE)
                printf ("%.*s %lu\n", l, word, head[i]->count);
	  
            if (head[i]->num_child > 0)
                printTrieUp ((head[i]->children), l, head[i]->num_child);
            free(head[i]);
        }
    }
}

void printTrieDown (node ** head, int l, int childs) 
{
  
    int rest_child = childs;
    for (int i = NUM_LETTERS - 1; i >= 0 && rest_child > 0; i--)
        {
            if (head[i] != NULL)
            	{
                    if (childs - rest_child > 0)
                        l--;
                    char c = head[i]->letter;
                    word=(char*)realloc(word,(l+1)*sizeof(char));
                    if(word==NULL)
                        exit(1);
                    word[l] = c;
                    l++;
                    rest_child--;
                    
                        
                    if (head[i]->num_child > 0)
                        printTrieDown ((head[i]->children), l,head[i]->num_child);
                     if (head[i]->is_end == TRUE)
                            printf ("%.*s %lu\n", l, word, head[i]->count); 
                   free(head[i]);
                }
        }
}  
 
int main (int argc, char* argv[]) 
{

    node ** first = (node **) calloc (NUM_LETTERS, sizeof (node *));
    if (first == NULL )
        {
          printf ("error");
            exit (1);
        }
    build_trie (first,&getletter);
    word = (char *) malloc (sizeof(char));
    if(word==NULL)
        exit(1);
    if(argc==1 )
        printTrieUp (first, 0, num_heads);
    else if(argc==2)
        {  
            if(strcmp (argv[1], "r")==0)
                printTrieDown(first, 0, num_heads);
        }
    free(word);
    free (first);
} 
#endif

