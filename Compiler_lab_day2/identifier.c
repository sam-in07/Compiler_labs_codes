#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

// Check if character is a delimiter
bool isDelimiter(char ch) {
    return (ch == ' ' || ch == '+' || ch == '-' || ch == '*' || 
            ch == '/' || ch == ',' || ch == ';' || ch == '>' || 
            ch == '<' || ch == '=' || ch == '(' || ch == ')' || 
            ch == '[' || ch == ']' || ch == '{' || ch == '}');
}

// Check if the string is a valid identifier
bool isValidIdentifier(char* str) {
    if (!isalpha(str[0]) && str[0] != '_')
        return false;
    for (int i = 1; str[i]; i++) {
        if (!isalnum(str[i]) && str[i] != '_')
            return false;
    }
    return true;
}

// Check if the string is a number
bool isNumber(char* str) {
    int i = 0;
    if (str[0] == '\0') return false;
    for (; str[i]; i++) {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}

// Get substring
char* getSubstring(char* str, int left, int right) {
    int len = right - left + 1;
    char* result = (char*)malloc(len + 1);
    strncpy(result, str + left, len);
    result[len] = '\0';
    return result;
}

// Parse function
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

            // ignore invalid tokens like 1c
            free(subStr);
            left = right;
        }
    }
}

// Main function
int main() {
    char str[100] = "Int main() { Int a,b,c,d; a=10+5; b=8; c=a+b; }";
    parse(str);
    return 0;
}
