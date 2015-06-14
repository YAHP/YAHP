#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_functions.h"

int main(int argc, char *argv[]){
    FILE* hashtable_store = fopen("../sample/hashtable", "rb"); 

    unsigned hash_value_sdbm = sdbm(argv[1]);

    if (0 != fseek(hashtable_store,  hash_value_sdbm/8, SEEK_SET)) {
        
        printf("fseek error!");
        exit(1);

    } else {

        char* test = malloc(sizeof(char));
        fread(test, sizeof(char), 1, hashtable_store);
        
        int offset = hash_value_sdbm % 8;
        int checkbit = 0;
        checkbit = *test >> (7-offset) & 1;
        
        if (checkbit == 1) {
    
            printf("In Blacklist!\n");
        
        } else {
            
            unsigned hash_value_djb2 = djb2(argv[1]);
            if(0 != fseek(hashtable_store, hash_value_djb2/8, SEEK_SET)) {
                printf("fseek error!");
                exit(1);
            }

            fread(test, sizeof(int), 1, hashtable_store);
            offset = hash_value_djb2 % 8;
            checkbit = 0;
            checkbit = *test >> (7 - offset) & 1;

            if(checkbit == 1) {

                printf("In blacklist!\n");
            
            } else {
            
                printf("Not in Blacklist!\n");
        
            }
        }
    }
    return 0;   
}
