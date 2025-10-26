#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define ERR_USAGE 1
#define ERR_OPEN_SRC 2
#define ERR_SRS_SIZE 3
#define ERR_MALLOC 4
#define ERR_READ_SRC 5
#define ERR_OPEN_DST 6
#define ERR_WRITE_DST 7
#define ERR_CLOSE_SRC 8
#define ERR_CLOSE_DST 9
#define ERR_DELETE_SRC 10


int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s source destination\n", argv[0]);
        return ERR_USAGE;
    }

    const char *source = argv[1];
    const char *destination = argv[2];
    FILE *in = NULL;
    FILE *out = NULL;
    unsigned char *buffer = NULL;
    long filesize;
    size_t bytesRead, bytesWritten;
    int errorCode = 0;

    in = fopen(source, "rb");
    if (!in) {
        fprintf(stderr, "Error: cannot open source file '%s': %s\n", source, strerror(errno));
        return ERR_OPEN_SRC;
    }

    if (fseek(in, 0, SEEK_END) != 0) {
        fprintf(stderr, "Error: cannot seek in input file '%s': %s\n", source, strerror(errno));
        fclose(in);
        return ERR_SRS_SIZE;;
    }

    filesize = ftell(in);
    if (filesize < 0) {
        fprintf(stderr, "Error: cannot determine size of '%s': %s\n", source, strerror(errno));
        fclose(in);
        return ERR_SRS_SIZE;
    }

    rewind(in);

    buffer = (unsigned char *)malloc(filesize);
    if (buffer == NULL && filesize > 0) {
        fprintf(stderr, "Error: not enough memory to read '%s'\n", source);
        fclose(in);
        return ERR_MALLOC;
    }

    bytesRead = fread(buffer, 1, filesize, in);

    if (bytesRead != (size_t)filesize) {
        fprintf(stderr, "Error: failed to read '%s': %s\n", source, strerror(errno));
        free(buffer);
        fclose(in);
        return ERR_READ_SRC;
    }

    out = fopen(destination, "wb");
    if (out == NULL) {
        fprintf(stderr, "Error: cannot open output file '%s': %s\n", destination, strerror(errno));
        free(buffer);
        fclose(in);
        return ERR_OPEN_DST;
    }

    bytesWritten = fwrite(buffer, 1, bytesRead, out);
    if (bytesWritten != bytesRead) {
        fprintf(stderr, "Error: failed to write to '%s': %s\n", destination, strerror(errno));
        errorCode = ERR_WRITE_DST;
    }

    free(buffer);

    if (fclose(in) != 0 && errorCode == 0) {
        fprintf(stderr, "Error: closing input file '%s': %s\n", source, strerror(errno));
        errorCode = ERR_CLOSE_SRC;
    }

    if (fclose(out) != 0 && errorCode == 0) {
        fprintf(stderr, "Error: closing output file '%s': %s\n", destination, strerror(errno));
        errorCode = ERR_CLOSE_DST;
    }

    if (errorCode != 0) {
        remove(destination);
        return errorCode;
    }

    if (remove(source) != 0) {
        fprintf(stderr, "Error: could not delete '%s': %s\n", source, strerror(errno));
        return ERR_DELETE_SRC;
    }

    return 0;
}
