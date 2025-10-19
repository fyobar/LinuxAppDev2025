#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_GR 10
#define ERR_BUF_SIZE 256


int main(int argc, char *argv[]) {

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <regexp> <substitution> <string>\n", argv[0]);
        return 1;
    }

    const char *pattern = argv[1];
    const char *substitution = argv[2];
    const char *input = argv[3];

    regex_t regex;
    char errbuf[ERR_BUF_SIZE];

    int code = regcomp(&regex, pattern, REG_EXTENDED);

    if (code != 0) {
        regerror(code, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Error: regex compilation error: %s\n", errbuf);
        return 1;
    }

    regmatch_t matches[MAX_GR];
    code = regexec(&regex, input, MAX_GR, matches, 0);

    if (code == REG_NOMATCH) {
        printf("%s\n", input);
        regfree(&regex);
        return 0;
    } else if (code != 0) {
        regerror(code, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Error: regex match error: %s\n", errbuf);
        regfree(&regex);
        return 1;
    }

    size_t buffer_size = strlen(input) + strlen(substitution);
    char *substituted= malloc(buffer_size);

    if (!substituted) {
        fprintf(stderr, "Error: failed to allocate %zu bytes.\n", buffer_size);
        return 1;
    }

    substituted[0] = '\0';
    const char *ch = substitution;

    while (*ch) {
        if (*ch == '\\') {
            char next = *(ch + 1);

            if (next >= '0' && next <= '9') {
                int group_number = atoi(ch + 1);

                 if (group_number >= MAX_GR || matches[group_number].rm_so == -1) {
                    fprintf(stderr, "Error: invalid capture group \\%d\n", group_number);
                    free(substituted);
                    return 1;
                }

                int start = matches[group_number].rm_so;
                int end = matches[group_number].rm_eo;
                strncat(substituted, input + start, end - start);
                ch += 2;
             } else if (next == '\\') {  // literal backslash
                strcat(substituted, "\\");
                ch += 2;
            } else if (next != '\0') { // other escaped characters (\/, \<, \>, etc.)
                size_t len = strlen(substituted);
                substituted[len] = next;
                substituted[len + 1] = '\0';
                ch += 2;
            } else { // trailing backslash
                strcat(substituted, "\\");
                ch++;
            }
        } else {
            size_t len = strlen(substituted);
            substituted[len] = *ch;
            substituted[len + 1] = '\0';
            ch++;
        }
    }

    char *result = malloc(buffer_size);

    if (!result) {
        fprintf(stderr, "Error: failed to allocate %zu bytes.\n", buffer_size);
        regfree(&regex);
        return 1;
    }

    result[0] = '\0';

    strncat(result, input, matches[0].rm_so); // before match
    strcat(result, substituted); // matched part with substitution
    strcat(result, input + matches[0].rm_eo); // after match

    printf("%s\n", result);

    regfree(&regex);
    free(substituted);
    free(result);

    return 0;
}