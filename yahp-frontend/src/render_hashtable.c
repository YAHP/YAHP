#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_functions.h"

struct node {
    char* url;
    struct node* next;
};

void insert(char* hashtable_output, struct node* hashtable, char* url) {
    
    unsigned int sdbm_value = sdbm(url);
    
    if (NULL == hashtable[sdbm_value].url && 0 == hashtable_output[sdbm_value]) {

        hashtable[sdbm_value].url = strdup(url);
        hashtable_output[sdbm_value] = 1;
        
    } else if (0 != strcmp(hashtable[sdbm_value].url, url)) {  //check if the same URL
        
        unsigned int djb2_value = djb2(url);
        if ( NULL == hashtable[djb2_value].url && 0 == hashtable_output[djb2_value] ) {
            
            hashtable[djb2_value].url = strdup(url);
            hashtable_output[djb2_value] = 1;

        } else {

                printf("Collision: %s\n", url);

                struct node* next = &hashtable[djb2_value];    
                struct node* last = next;

                while (NULL != next) {
                    if (0 == strcmp(next -> url, url)) {
                        return;
                    }
                    last = next;
                    next = next -> next;
                }
        
                last -> next = (struct node*)malloc(sizeof(struct node));
                last -> next -> url = strdup(url);
                last -> next -> next = NULL;
        
        }
    }
}

int main() {
    
    struct node hashtable[98317];
    char hashtable_output[98317];
    
    int i = 0;
     
    for (; i < 98317; i++) {
        hashtable[i].url = NULL;
        hashtable[i].next = NULL;
    }
    
    for (i = 0; i < 98317; i++) {
        hashtable_output[i] = 0;
    }

    char* line;
    size_t len = 0;
    FILE* urllist = fopen("../sample/blacklist", "r");
    
    while ((getline(&line, &len, urllist)) != -1) {
        line = strtok(line, "\n");      
        insert(hashtable_output, hashtable, line);
    }

    FILE* hashtable_store = fopen("../sample/hashtable", "wb");
    char currentbyte = 0;
    for (i = 0; i < 98317; i++) {
        currentbyte = currentbyte << 1 | hashtable_output[i];
        if (7 == i % 8) {
            fwrite(&currentbyte, sizeof(char), 1, hashtable_store);
        }
    }

    /*last byte here*/
}
