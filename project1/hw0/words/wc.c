/* wc.c - tiny wc clone: counts lines, words, and characters (bytes) */
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long u64;

static void count_stream(FILE *fp, const char *label) {
    int ch;
    u64 lines = 0, words = 0, chars = 0;
    int in_word = 0;

    while ((ch = fgetc(fp)) != EOF) {
        chars++;
        if (ch == '\n') lines++;
        
        if (isspace((unsigned char)ch)) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            words++;
        }
    }

    if (label)
        printf("%7llu %7llu %7llu %s\n", lines, words, chars, label);
    else
        printf("%7llu %7llu %7llu\n", lines, words, chars);
}

int main(int argc, char **argv) {
    if (argc == 1) {
        /* No args: read from stdin */
        count_stream(stdin, NULL);
        return 0;
    }
    if (argc == 2) {
        const char *path = argv[1];
        FILE *fp = fopen(path, "rb");
        if (!fp) {
            fprintf(stderr, "wc: cannot open '%s': %s\n", path, strerror(errno));
            return 1;
        }
        count_stream(fp, path);
        fclose(fp);
        return 0;
    }
    fprintf(stderr, "Usage:\n  %s [FILE]\n", argv[0]);
    return 1;
}
