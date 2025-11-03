#include <stdlib.h>
#include <errno.h>
#include <rhash.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h> 
#include "config.h"

#if READLINE_ENABLED
#  include <readline/readline.h>
#  include <readline/history.h>
#endif


char *get_input(int interactive) {
#if READLINE_ENABLED
if (interactive) {
    char *line = readline("rhasher> ");
    if (line && *line)
        add_history(line);
    return line;
} else {
    static char *line = NULL;
    static size_t len = 0;
        if (getline(&line, &len, stdin) == -1)
            return NULL;
        line[strcspn(line, "\n")] = '\0';
        return line;
}
#else
    static char *line = NULL;
    static size_t len = 0;

    if (interactive)
        printf("rhasher> ");

    fflush(stdout);

    ssize_t nread = getline(&line, &len, stdin);

    if (nread == -1) 
        return NULL;

    line[strcspn(line, "\n")] = '\0';
    return line;
#endif
}

int get_hash_id(const char *algorithm) {
    if (strcasecmp(algorithm, "MD5") == 0) return RHASH_MD5;
    if (strcasecmp(algorithm, "SHA1") == 0) return RHASH_SHA1;
    if (strcasecmp(algorithm, "TTH") == 0) return RHASH_TTH;
    return -1;
}

int computes_digest(char *input, int hash_id, unsigned char *digest) {
    if (input[0] == '"') { // string case
        char *str = input + 1;
        size_t slen = strlen(str);
        if (slen > 0 && str[slen - 1] == '"')
            str[slen - 1] = '\0';
        return rhash_msg(hash_id, str, strlen(str), digest);
    } else { // file case
        return rhash_file(hash_id, input, digest);
    }
}

void print_digest(unsigned char *digest, int hash_id, const char *algorithm) {
    char output[64];
    size_t digest_size = rhash_get_digest_size(hash_id);
    int format = (isupper((unsigned char)algorithm[0])) ? RHPR_HEX : RHPR_BASE32;
    rhash_print_bytes(output, digest, digest_size, format);
    printf("%s\n", output);
}


int main() {
    rhash_library_init(); 
    int interactive = isatty(fileno(stdin));

    if (interactive)
        fprintf(stderr, "Supported algorithmrithms: MD5, SHA1, TTH. Use Ctrl+D to quit)\n");

    for (;;) {
        char *line = get_input(interactive);
        if (!line) break;

        const char *delimiters = " \t";
        char *algorithm = strtok(line, delimiters);
        char *input  = strtok(NULL, delimiters);

        if (!algorithm || !input) {
            fprintf(stderr, "Invalid command. Format: <algorithmrithm> <file|\"string\">\n");

#if READLINE_ENABLED
            free(line);
#endif
            continue;
        }

        int hash_id = get_hash_id(algorithm);

        if (hash_id < 0) {
            fprintf(stderr, "Unsupported algorithm: %s\n", algorithm);
#if READLINE_ENABLED
            free(line);
#endif
            continue;
        }

        unsigned char digest[64];
        int result = computes_digest(input, hash_id, digest);

        if (result < 0) {
            fprintf(stderr, "Error processing %s: %s\n", input, strerror(errno));
#if READLINE_ENABLED
            free(line);
#endif
            continue;
        }

        print_digest(digest, hash_id, algorithm);

#if READLINE_ENABLED
        free(line);
#endif
    }

#if READLINE_ENABLED
    printf("\n");
#endif

    return 0;
}
