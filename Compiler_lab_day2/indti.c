#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>


bool isDelimiter(char ch) {
    return (ch == ' ' || ch == '+' || ch == '-' || ch == '*' || 
            ch == '/' || ch == ',' || ch == ';' || ch == '>' || 
            ch == '<' || ch == '=' || ch == '(' || ch == ')' || 
            ch == '[' || ch == ']' || ch == '{' || ch == '}');
}

bool isValidIdentifier(char* str) {
    if (!isalpha(str[0]) && str[0] != '_') return false;
    for (int i = 1; str[i]; i++) {
        if (!isalnum(str[i]) && str[i] != '_') return false;
    }
    return true;
}


bool isNumber(char* str) {
    for (int i = 0; str[i]; i++) {
        if (!isdigit(str[i])) return false;
    }
    return true;
}


char* getSubstring(char* str, int left, int right) {
    int len = right - left + 1;
    char* result = (char*)malloc(len + 1);
    strncpy(result, str + left, len);
    result[len] = '\0';
    return result;
}


void parse(char* str) {
    int left = 0, right = 0;
    int len = strlen(str);

    while (right <= len && left <= right) {
        if (!isDelimiter(str[right]))
            right++;

        if ((isDelimiter(str[right]) && left == right)) {
            right++;
            left = right;
        }
        else if ((isDelimiter(str[right]) && left != right) || (right == len && left != right)) {
            char* subStr = getSubstring(str, left, right - 1);

            if (isNumber(subStr))
                printf("Number: %s\n", subStr);
            else if (isValidIdentifier(subStr))
                printf("Identifier: %s\n", subStr);

            
            free(subStr);
            left = right;
        }
    }
}

int main() {
    FILE *file = fopen("int.txt", "r");
    if (!file) {
        printf("Failed to open file.\n");
        return 1;
    }

    char code[1000] = "";
    char line[200];

    while (fgets(line, sizeof(line), file)) {
        strcat(code, line);  
    }

    fclose(file);

    parse(code);

    return 0;
}
