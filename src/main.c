/* Harmless framework fixture, not a security vulnerability. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv) {
    unsigned char data[2048]; size_t n = 0;
    if (argc < 2) return 3;
    if (!strcmp(argv[1], "argv")) {
        if (argc != 3 || strlen(argv[2]) > sizeof(data)) return 3;
        n = strlen(argv[2]); memcpy(data, argv[2], n);
    } else {
        FILE *f = stdin;
        if (!strcmp(argv[1], "file")) {
            if (argc != 3 || !(f = fopen(argv[2], "rb"))) return 3;
        } else if (strcmp(argv[1], "stdin")) return 3;
        n = fread(data, 1, sizeof(data), f);
        if (f != stdin) fclose(f);
    }
    if (n > 1024 || (n && data[0] == '!')) { fputs("invalid\n", stderr); return 2; }
    for (size_t i = 0; i + 5 <= n; i++) {
        if (!memcmp(data + i, "OTHER", 5)) {
            fputs("FIXTURE_FAILURE:OTHER:other-check\n", stderr); return 8;
        }
    }
    for (size_t i = 0; i + 4 <= n; i++) {
        if (!memcmp(data + i, "MARK", 4)) {
            fputs("FIXTURE_FAILURE:MARK:marker-check\n", stderr); return 7;
        }
    }
    fputs("OK\n", stdout); return 0;
}
