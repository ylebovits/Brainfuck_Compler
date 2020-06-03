#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUM_CELLS 30000

char *read_file(char *file_path, int *file_size);
int valid_char(char c);
int valid_brackets(const char *contents, int size);
int valid_syntax(const char *content, int size);
void interpret(const char *contents, int size);

int main(int argv, char *args[]) {

//    if (argv < 2) {
//        printf("Usage: ./fuck source_file\n");
//        return 1;
//    }

//    char *source_path = args[1];
//    int file_size;
//    char *file_contents = read_file(source_path, &file_size);

//    printf("%s\n%d\n", file_contents, file_size);

//    free(file_contents);

    char *s = "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.";

    interpret(s, strlen(s));

    return 0;
}

char *read_file(char *file_path, int *file_size) {

    FILE *fptr = fopen(file_path, "r");

    if ( fptr == NULL ) {
        fprintf(stderr, "Error opening source file\n");
        return NULL;
    }

    if ( fseek(fptr, 0, SEEK_END) != 0 ) {
        fprintf(stderr, "Error reading source file size\n");
        return NULL;
    }

    *file_size = (int)ftell(fptr);
    rewind(fptr);

    char *contents = malloc(sizeof(char) * (*file_size + 1));

    fread(contents, sizeof(char), *file_size, fptr);
    if ( ferror(fptr) != 0 ) {
        fprintf(stderr, "Error reading source file\n");
        return NULL;
    }

    return contents;
}

int valid_char(char c) {
    return (c == '.' || c == ',' || c == '-' || c == '+' ||
            c == '[' || c == ']' || c == '<' || c == '>' ||
            c == ' ' || c == '\t' || c == '\n');
}

int valid_brackets(const char *contents, int size) {
    
    char stack[size];
    int top = 0;

    for (int i = 0; i < size; ++i) {

        if (contents[i] == '[') {
            stack[top++] = '[';
        }
        else if (contents[i] == ']') {
            if (stack[--top] != '[')
                return 0;
        }
    }

    return top == 0;
}

int valid_syntax(const char *contents, int size) {

    for (int i = 0; i < size; ++i) {
        if (!valid_char(contents[i]))
            return 0;
    }

    return valid_brackets(contents, size);
}

void interpret(const char *contents, int size) {

    unsigned char memory[NUM_CELLS];

    unsigned char *ptr = memory;

    for (int i = 0; i < size; ++i) {

        switch (contents[i]) {
            case '+':
                ++*ptr;
                break;

            case '-':
                --*ptr;
                break;

            case '>':
                ++ptr;
                break;

            case '<':
                --ptr;
                break;

            case '.':
                putchar(*ptr);
                break;

            case ',':
                *ptr = getchar();
                break;

            // TODO:
            // add loop handling
        }
    }
}



