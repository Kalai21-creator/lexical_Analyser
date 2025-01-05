#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

// Define status macros
#define SUCCESS 0
#define FAILURE 1
#define UNSUPPORTED 2

// List of C keywords
const char* keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double",
    "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",
    "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef",
    "union", "unsigned", "void", "volatile", "while"
};

// Function to check if a string is a keyword
int isKeyword(const char* str) {
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;  // Token is a keyword
        }
    }
    return 0;  // Token is not a keyword
}

// Function to check if a numeric token is valid
int isValidNumeric(const char* token) {
    if (strncmp(token, "0x", 2) == 0 || strncmp(token, "0X", 2) == 0) {  // Hexadecimal
        for (int i = 2; token[i] != '\0'; i++) {
            if (!isxdigit(token[i])) {
                return 0;  // Invalid hex digit
            }
        }
        return 1;
    } else if (isdigit(token[0])) {  // Decimal or float
        int hasDot = 0, hasF = 0;
        for (int i = 0; token[i] != '\0'; i++) {
            if (token[i] == '.') {
                if (hasDot) return 0;  // Multiple dots
                hasDot = 1;
            } else if (token[i] == 'f' || token[i] == 'F') {
                if (hasF) return 0;  // Multiple 'f'
                hasF = 1;
            } else if (!isdigit(token[i])) {
                return 0;  // Invalid character
            }
        }
        return 1;
    }
    return 0;
}

// Function to identify the token type
int getTokenType(const char* token) {
    if (isKeyword(token)) {
        return KEYWORD;
    }
    if (isalpha(token[0]) || token[0] == '_') {
        return IDENTIFIER;
    }
    if (isdigit(token[0]) || token[0] == '.') {
        if (isValidNumeric(token)) {
            return NUMERIC_CONSTANT;
        } else {
            return INVALID;
        }
    }
    if (strchr("+-*/%=<>!&|^", token[0]) != NULL) {
        return OPERATOR;
    }
    if (strchr("(){}[];,.", token[0]) != NULL) {
        return SPECIAL_CHAR;
    }
    if (token[0] == '\'' && token[strlen(token) - 1] == '\'') {
        return CHAR_CONSTANT;
    }
    return INVALID;
}

// Function to perform lexical analysis and validate syntax
void lexicalAnalyzer(FILE* source) {
    char token[100];
    int c, i = 0;
    int openBraces = 0, openParentheses = 0;
    int expectingSemicolon = 0;

    printf("\n\n-------------------------[[ << LEXICAL ANALYSER >> ]]-------------------------------\n\n");

    while ((c = fgetc(source)) != EOF) {
        if (c == '#') {
            while (c != '\n' && c != EOF) {
                c = fgetc(source);
            }
            continue;
        }
        if (isspace(c)) {
            continue;
        }
        if (c == '"') {
            token[i++] = c;
            while ((c = fgetc(source)) != EOF && c != '"') {
                token[i++] = c;
            }
            token[i++] = c;
            token[i] = '\0';
            printf("%-18s: %s\n", "LITERAL", token);
            i = 0;
            continue;
        }
        if (strchr("(){}[];,.", c) != NULL) {
            if (c == '{') {
                openBraces++;
            } else if (c == '}') {
                if (openBraces > 0) {
                    openBraces--;
                } else {
                    printf("ERROR           : Unmatched '}'\n");
                }
            } else if (c == '(') {
                openParentheses++;
            } else if (c == ')') {
                if (openParentheses > 0) {
                    openParentheses--;
                } else {
                    printf("ERROR           : Unmatched ')'\n");
                }
            } else if (c == ';') {
                expectingSemicolon = 0;
            }
            printf("%-18s: %c\n", "SPECIAL_CHAR", c);
            continue;
        }
        if (isalnum(c) || c == '_' || c == '\'') {
            token[i++] = c;
            while (isalnum(c = fgetc(source)) || c == '_' || c == '\'') {
                token[i++] = c;
            }
            token[i] = '\0';
            ungetc(c, source);
            int type = getTokenType(token);
            switch (type) {
                case KEYWORD:
                    printf("%-18s: %s\n", "KEYWORD", token);
                    break;
                case IDENTIFIER:
                    printf("%-18s: %s\n", "IDENTIFIER", token);
                    break;
                case NUMERIC_CONSTANT:
                    printf("%-18s: %s\n", "CONSTANT", token);
                    break;
                case INVALID:
                    printf("ERROR           : Invalid token: %s\n", token);
                    break;
                default:
                    printf("%-18s: %s\n", "LITERAL", token);
                    break;
            }
            if (strcmp(token, "printf") == 0) {
                expectingSemicolon = 1;
            }
            i = 0;
        }
    }

    if (openBraces > 0) {
        printf("ERROR           : Unmatched '{'\n");
    }
    if (openParentheses > 0) {
        printf("ERROR           : Unmatched '('\n");
    }
    if (expectingSemicolon) {
        printf("ERROR           : Missing semicolon ';'\n");
    }

    printf("\nLexical Analysis Completed.\n");
}
