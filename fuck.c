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
int next_loop_close(const char *contents, int curr_pos, int size);

int main(int argv, char *args[]) {

    if (argv < 2) {
        printf("Usage: ./fuck source_file\n");
        return 1;
    }

    char *source_path = args[1];
    int file_size;
    char *file_contents = read_file(source_path, &file_size);

    if ( valid_syntax(file_contents, file_size) )
        interpret(file_contents, file_size);
    else
        printf("Syntax error!\n");

    free(file_contents);

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
    
    char stack[size]; // not super memory efficient
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

    for (int i = 0; i < size; ++i)
        if (!valid_char(contents[i]))
            return 0;

    return valid_brackets(contents, size);
}

/*
 * precondition: there exists a ] between contents[curr_pos] and contents[size-1]
 */
int next_loop_close(const char *contents, int curr_pos, int size) {

    for (int i = curr_pos; i < size; ++i)
        if ( contents[i] == ']' )
            return i;
    return -1; // won't ever return -1 if used properly
}


void interpret(const char *contents, int size) {

    unsigned char memory[NUM_CELLS];

    unsigned char *ptr = memory;

    int loop_start_index;

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

            case '[':
                if ( *ptr )
                    loop_start_index = i;
                else
                    i = next_loop_close(contents, i, size) + 1;
                break;

            case ']':
                i = loop_start_index;
                break;
        }
    }
}



