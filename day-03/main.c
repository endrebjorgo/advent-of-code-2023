#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int char_is_digit(char c)
{
    return (48 <= c && c <= 57);
}

int char_is_symbol(char c)
{
    // Lazy check
    return (c == '@' || c == '*' || c == '/' || c == '#' || c == '&' ||
            c == '=' || c == '%' || c == '$' || c == '+' || c == '-' ||
            c == '$');
}

size_t part_one(char *file_path)
{
    FILE* fp = fopen(file_path, "r");

    if (fp == NULL) {
        fprintf(stderr, "ERROR: Could not open file %s", file_path);
        exit(1);
    }

    size_t sum = 0;
    size_t cursor = 0;
    size_t curr_number = 0;
    size_t curr_num_len = 0;
    char curr_char;

    char prev_line[256] = "";
    char curr_line[256] = "";
    char next_line[256] = "";
    fgets(next_line, 256, fp);

    int end_not_reached = 1;
    while (end_not_reached) {
        memcpy(prev_line, curr_line, 256);
        memcpy(curr_line, next_line, 256);
        end_not_reached = (fgets(next_line, 256, fp) != NULL);
        
        if (!end_not_reached) { // Not not not not
            memset(next_line, '\0', 256);
        }

        while ((curr_char = curr_line[cursor++]) != '\0') {
            if (char_is_digit(curr_char)) {
               curr_number = 10 * curr_number + curr_char - 48; 
               curr_num_len++;
            } else if (curr_number) {
                int search_idx;
                for (int i = 0; i < curr_num_len + 2; ++i) {
                    search_idx = cursor - curr_num_len - 2 + i;
                    if (char_is_symbol(prev_line[search_idx]) ||
                        char_is_symbol(curr_line[search_idx]) ||
                        char_is_symbol(next_line[search_idx])) 
                    {
                        sum += curr_number;
                        break;
                    }
                }
                curr_number = 0; 
                curr_num_len = 0;
            }
        }
        cursor = 0; 
    }
    return sum;
}
size_t part_two(char *file_path)
{
    return 0;
}

int main(void)
{
    char *file_path = "./schematic.txt";

    size_t result1 = part_one(file_path);
    printf("Part One => %zu\n", result1);

    size_t result2 = part_two(file_path);
    printf("Part Two=> %zu\n", result2);

    return 0;
}
