#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

// Declare states
typedef enum {
    START,
    COMMENT,
    SINGLE_COMMENT,
    MULTI_COMMENT,
    KEYWORD_ID,
    STRING,
    CHAR,
    NUM
} State;

// List of keywords for simple keyword recognition
const char *keywords[] = {
    "int", "float", "if", "else", "while", "return", "for", "char", "double", "void", NULL
};

// Function to check if a token is a keyword
int is_keyword(const char *token) {
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(token, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    FILE *file = fopen("source.c", "r");

    State state = START;
    int c;
    char buffer[BUFFER_SIZE];
    int idx = 0;

    while ((c = fgetc(file)) != EOF) {
        switch (state) {
            case COMMENT:
                if (c == '/') {
                    state = SINGLE_COMMENT;
                } else if (c == '*') {
                    state = MULTI_COMMENT;
                } else {
                    ungetc(c, file); // Not a comment, rewind
                    state = START;
                }
                break;

            case SINGLE_COMMENT:
                if (c == '\n') {
                    state = START;
                }
                break;

            case MULTI_COMMENT:
                if (c == '*' && (c = fgetc(file)) == '/') {
                    state = START;
                } else if (c == EOF) {
                    break; // End of file inside a comment
                }
                break;

            case CHAR:
                if (c != '\'') {
                    printf("LITERAL(CHR): \t\t%c\n", c);
                }
                state = START;
                break;

            case STRING:
                if (c == '\"') {
                    buffer[idx] = '\0';
                    printf("LITERAL(STR): \t\t\"%s\"\n", buffer);
                    idx = 0;
                    state = START;
                } else {
                    buffer[idx++] = c;
                }
                break;

            case NUM:
                if (isdigit(c)) {
                    buffer[idx++] = c;
                } else {
                    buffer[idx] = '\0';
                    printf("LITERAL(NUM): \t\t%d\n", atoi(buffer));
                    idx = 0;
                    ungetc(c, file); // Reprocess this character
                    state = START;
                }
                break;

            case KEYWORD_ID:
                if (isalnum(c) || c == '_') {
                    buffer[idx++] = c;
                } else {
                    buffer[idx] = '\0';
                    if (is_keyword(buffer)) {
                        printf("KEYWORD: \t\t%s\n", buffer);
                    } else {
                        printf("IDENTIFIER: \t\t%s\n", buffer);
                    }
                    idx = 0;
                    ungetc(c, file); // Reprocess this character
                    state = START;
                }
                break;

            case START:
                if (isspace(c)) {
                    continue; // Ignore whitespace
                } else if (c == '/') {
                    state = COMMENT;
                } else if (c == '#') {  // hacky way to ignore preprocessor directives
                    state = SINGLE_COMMENT;
                } else if (isdigit(c)) {
                    buffer[idx++] = c;
                    state = NUM;
                } else if (isalpha(c) || c == '_') {
                    buffer[idx++] = c;
                    state = KEYWORD_ID;
                } else if (c == '\'') {
                    state = CHAR;
                } else if (c == '\"') {
                    state = STRING;
                } else if (strchr(",+-*/%=", c)) {
                    printf("OPERATOR: \t\t%c\n", c);
                } else if (strchr("{}()[];", c)) {
                    printf("SYMBOL: \t\t%c\n", c);
                }
                break;
        }
    }

    fclose(file);
    return 0;
}
