#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
    FILE *file = fopen("int.txt", "r");
    if (!file) {
        printf("Failed to open file.\n");
        return 1;
    }

    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (isspace(ch)) {
            continue;
        }
        else if (ch == '(' || ch == ')' || ch == '{' || ch == '}' ||
                 ch == ',' || ch == ';' || ch == '+' || ch == '=') {
            putchar(ch);
            putchar('\n');
        }
        else if (isalpha(ch) || ch == '_') {
            putchar(ch);
            while (1) {
                int next = fgetc(file);
                if (next == EOF) break;
                if (isalnum(next) || next == '_') {
                    putchar(next);
                } else {
                    ungetc(next, file);
                    break;
                }
            }
            putchar('\n');
        }
        else if (isdigit(ch)) {
            putchar(ch);
            while (1) {
                int next = fgetc(file);
                if (next == EOF) break;
                if (isdigit(next)) {
                    putchar(next);
                } else {
                    ungetc(next, file);
                    break;
                }
            }
            putchar('\n');
        }
        else {
            putchar(ch);
            putchar('\n');
        }
    }

    fclose(file);
    return 0;
}
