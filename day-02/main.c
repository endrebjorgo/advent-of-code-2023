#include <stdlib.h>
#include <stdio.h>

#define TOTAL_REDS 12
#define TOTAL_GREENS 13
#define TOTAL_BLUES 14

int char_is_int(char c)
{
    return (48 <= c && c <= 57);
}

int check_set(int set[])
{
    return (set[0] > TOTAL_REDS || set[1] > TOTAL_GREENS || set[2] > TOTAL_BLUES);
}

void reset_set(int set[])
{
    set[0] = 0;
    set[1] = 0;
    set[2] = 0;
}

int part_one(const char *file_path)
{
    FILE *fp = fopen(file_path, "r");

    if (fp == NULL) {
        fprintf(stderr, "ERROR: Could not open the file %s", file_path);
        exit(1);
    }
    char curr_line[256];
    char ch;
    int game_number = 0;
    int curr_int = 0;
    int curr_set[3] = {0, 0, 0};
    int sum = 0;

    while ((ch = fgetc(fp)) != EOF) {
        if (char_is_int(ch)) {
            curr_int = 10 * curr_int + ch - 48;
            continue;
        } else if (ch == ';' || ch == '\n') {
            if (curr_set[0] > TOTAL_REDS || curr_set[1] > TOTAL_GREENS || curr_set[2] > TOTAL_BLUES) {
                game_number = 0;
            }
            curr_set[0] = 0;
            curr_set[1] = 0;
            curr_set[2] = 0;
            curr_int = 0;
            if (ch == '\n') sum += game_number;
            break;
        }

        switch (ch) {
            case ':':
                game_number = curr_int;
                printf("Game number %d\n", game_number);
                curr_int = 0;
                break;
            case 'r':
                curr_set[0] = curr_int;
                curr_int = 0;
                break;
            case 'g':
                curr_set[1] = curr_int;
                curr_int = 0;
                break;
            case 'b':
                curr_set[2] = curr_int;
                curr_int = 0;
                break;
        }
    }
    return sum;
}

int main(void)
{
    const char *file_path = "./games.txt";

    int result1 = part_one(file_path);
    printf("Part One => %d\n", result1);

    //int result2 = part_two(file_path);
    //printf("Part Two => %d\n", result2);

    return 0;
}
