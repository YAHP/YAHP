#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
    
    FILE *origin_csv = fopen("../io/export.csv", "r");
    if (NULL == origin_csv) {
        printf("Open failed!");
        return 1;
    }

    char* line;
    ssize_t line_length;	
    size_t len = 0; 
    FILE *urllist = fopen("../io/urllist", "w");   

    while ((getline(&line, &len, origin_csv)) != -1) {
        
        char* token;
        int counter = -1;
        int no_url = 0;
        
        token = strtok(line, ",\"");

        while (NULL != token) {
            counter++;

            if (1 == counter % 3) {
                if (0 != strcmp(token, "-")) {
                    size_t len_token = strlen(token);
                    if (token[len_token-1] == '/') {
                        strncpy(token, token, len_token-1);
                        token[len_token-1] = '\0';
                    }
                    strcat(token, "\n");

                    fwrite(token, sizeof(char), strlen(token), urllist);
                } else {
                    no_url = 1;
                }
            } else if (2 == counter % 3) {
                if (no_url) {
                    size_t len_token = strlen(token);
                    if (token[len_token-1] == '/') {
                        strncpy(token, token, len_token-1);
                        token[len_token-1] = '\0';
                    }
                    strcat(token, "\n");
                    fwrite(token, sizeof(char), strlen(token), urllist);
                }
                break;
            }

            token = strtok(NULL, ",\"");
        }
    }

    fclose(origin_csv);
    fclose(urllist);
    
    return 0;
}

