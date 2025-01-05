#ifndef LEXER_H
#define LEXER_H
// Define token type macros
#define KEYWORD 1
#define IDENTIFIER 2
#define NUMERIC_CONSTANT 3
#define OPERATOR 4
#define SPECIAL_CHAR 5
#define CHAR_CONSTANT 6
#define LITERAL 7
#define INVALID 8



// Function declarations
int getTokenType(const char* token);
void lexicalAnalyzer(FILE* source);
int isKeyword(const char* str);

#endif // LEXER_H
