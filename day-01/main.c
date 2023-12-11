#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int char_is_int(char c)
{
    return (48 <= c && c <= 57);
}

int char_is_lowercase(char c)
{
    return (97 <= c && c <= 122);
}

int char_arr_len(char *arr)
{
    int length = 0;
    for (;;) {
        char curr = arr[length];
        if (curr == '\0') break;
        length++;
    }
    return length;
}


int part_one(const char *file_path)
{
    FILE* fp = fopen(file_path, "r");

    if (fp == NULL) {
        fprintf(stderr, "ERROR: Could not open the file %s", file_path);
        exit(1);
    }
    char c;
    int curr_int = -1;
    int sum = 0;

    while ((c = fgetc(fp)) != EOF) {
        if (char_is_int(c)) {
            if (curr_int == -1) {
                curr_int = c - 48;
                sum += 10 * curr_int;
            }
            curr_int = c - 48;
        } else if (c == '\n') {
            sum += curr_int;
            curr_int = -1;
        }
    }
    fclose(fp);
    return sum;
}


int part_two(const char *file_path)
{
    FILE* fp = fopen(file_path, "r");

    if (fp == NULL) {
        fprintf(stderr, "ERROR: Could not open the file %s", file_path);
        exit(1);
    }
    char *digits[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    char c;
    int curr_int = -1;
    int sum = 0;

    while ((c = fgetc(fp)) != EOF) {
        if (char_is_int(c)) {
            if (curr_int == -1) {
                curr_int = c - 48;
                sum += 10 * curr_int;
            }
            curr_int = c - 48;
        } else if (char_is_lowercase(c)) {
            for (int i = 0; i < 10; ++i) {
                for (int j = 0; j < char_arr_len(digits[i]); ++j) {
                    if (c != digits[i][j]) {
                        fseek(fp, -j - 1, SEEK_CUR);
                        c = fgetc(fp);
                        goto skip_label;
                    }
                    c = fgetc(fp);
                }
                fseek(fp, -char_arr_len(digits[i]), SEEK_CUR);
                if (curr_int == -1) {
                    curr_int = i;
                    sum += 10 * curr_int;
                }
                curr_int = i;
                i = 9;
skip_label:
                continue;
            }
        } else if (c == '\n') {
            sum += curr_int;
            curr_int = -1;
        }
    }
    fclose(fp);
    return sum;
}

int main(void)
{
    const char *file_path = "calibration-values.txt";

    int result1 = part_one(file_path);
    printf("Part One => %d\n", result1);

    int result2 = part_two(file_path);
    printf("Part Two => %d\n", result2);
    
    return 0;
}
