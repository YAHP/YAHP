#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"hash_function.h"

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
    
    struct node hashtable[slot_num];
    char hashtable_output[slot_num];
    
    int i = 0;
     
    for (; i < slot_num; i++) {
        hashtable[i].url = NULL;
        hashtable[i].next = NULL;
    }
    
    for (i = 0; i < slot_num; i++) {
        hashtable_output[i] = 0;
    }

    char* line;
    size_t len = 0;
    FILE* urllist = fopen("../io/urllist", "r");
    
    while ((getline(&line, &len, urllist)) != -1) {
        line = strtok(line, "\n");      
        insert(hashtable_output, hashtable, line);
    }

    FILE* hashtable_store = fopen("../io/hashtable_store", "wb");
    char currentbyte = 0;
    for (i = 0; i < slot_num; i++) {
        currentbyte = currentbyte << 1 | hashtable_output[i];
        if (7 == i % 8) {
            fwrite(&currentbyte, sizeof(char), 1, hashtable_store);
        }
    }

    FILE* hashtable_js = fopen("../io/hashtable.js", "w");
    fwrite ("var hashtable = \"", sizeof(char), 17, hashtable_js);
    for (i = 0; i < slot_num; i++) {
        if (hashtable_output[i]) {
            fwrite("1", sizeof(char), 1, hashtable_js);
        } else {
            fwrite("0", sizeof(char), 1, hashtable_js);
        }
    }
    fwrite ("\";", sizeof(char), 2, hashtable_js);

    /*last byte here*/
}
