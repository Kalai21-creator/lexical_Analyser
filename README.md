# Lexical Analyzer for C Programs

## Overview
This project involves the development of a Lexical Analyzer for C programs as part of compiler design. The Lexical Analyzer is responsible for recognizing tokens such as keywords, operators, identifiers, literals, and arrays from the input source code. The goal is to tokenize the given input program, laying a strong foundation for understanding compiler architecture.

---

## Objective
The primary objectives of the lexical analyzer are to:
- Identify and categorize **keywords** in the input program.
- Detect and list **identifiers** present in the code.
- Recognize **literals**, including floating-point numbers, character literals, string literals, and decimal integers.
- Handle **array identifiers**.
- Display the tokenized output for the given input program.

---

## Key Concepts
### Tokens
Tokens are strings of characters categorized based on grammar rules. Examples of token types include:
- **Keywords:** Reserved words in the C programming language.
- **Identifiers:** User-defined variable names.
- **Operators:** Arithmetic, assignment, and logical operators.
- **Literals:** Integer, floating-point, and character/string values.
- **Special Symbols:** Parentheses, commas, semicolons, etc.
- **End of Statement:** Identified by semicolons (`;`).

### Example
Consider this sample C expression:
```c
sum = 3 + 2;
```
The tokenized output would be:
| Token | Token Type            |
|-------|------------------------|
| sum   | Identifier             |
| =     | Assignment Operator    |
| 3     | Integer Literal        |
| +     | Addition Operator      |
| 2     | Integer Literal        |
| ;     | End of Statement       |

---

## Functionalities
The lexical analyzer performs the following tasks:
1. **Keyword Detection:**
   - Identifies reserved C keywords such as `int`, `float`, `return`, etc.
2. **Identifier Recognition:**
   - Detects user-defined variable names.
3. **Literal Identification:**
   - Recognizes integer, floating-point, character, and string literals.
4. **Array Handling:**
   - Detects and categorizes array variables.
5. **Tokenized Output:**
   - Displays the tokens and their corresponding types.

---

## Requirements
- Input: A valid C program provided as a text file.
- Output: Tokenized representation of the input program.
- Programming Language: C
- Modular Code Structure: Split into `.c` and `.h` files for maintainability.

---

## Usage
1. **Compile the Lexical Analyzer:**
   ```bash
   gcc -o lexer lexer.c
   ```
2. **Run the Analyzer:**
   ```bash
   ./lexer input.c
   ```
3. **View the Tokenized Output:**
   - The output will display each token along with its type.

---

## Example Output
```plaintext
Token: sum	 Type: Identifier
Token: =	 Type: Assignment Operator
Token: 3	 Type: Integer Literal
Token: +	 Type: Addition Operator
Token: 2	 Type: Integer Literal
Token: ;	 Type: End of Statement
```

---

## Future Extensions
- **Function Detection:** Support for recognizing and tokenizing functions.
- **Pointer Handling:** Identify and categorize pointer variables.
- **User-Defined Data Types:** Handle `struct`, `enum`, and `typedef`.
- **Error Reporting:** Provide detailed error messages for invalid tokens.

---

## Conclusion
This Lexical Analyzer project provides a fundamental understanding of compiler design by implementing tokenization for C programs. By recognizing various token types and displaying tokenized output, it serves as a stepping stone for building more advanced compiler components.

