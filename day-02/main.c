#include <stdlib.h>
#include <stdio.h>

#define TOTAL_REDS 12
#define TOTAL_GREENS 13
#define TOTAL_BLUES 14

typedef struct {
    size_t game_no;
    size_t max_set[3]; // Max number of each cube in the game
} Game;

int char_is_int(char c)
{
    return (48 <= c && c <= 57);
}

void parse_game(char *str, Game *result)
{
    size_t cursor = 0;
    char curr_char;
    size_t curr_number = 0;

    while ((curr_char = str[cursor++]) != '\0') {
        if (char_is_int(curr_char)) {
            curr_number = 10 * curr_number + curr_char - 48;
            continue;
        } else if (curr_char == ':') {
            result->game_no = curr_number;
            curr_number = 0;
        } else if (curr_char == 'r') {
            if (curr_number > result->max_set[0]) {
                result->max_set[0] = curr_number;
            }
            curr_number = 0;
        } else if (curr_char == 'g') {
            if (curr_number > result->max_set[1]) {
                result->max_set[1] = curr_number;
            }
            curr_number = 0;
        } else if (curr_char == 'b') {
            if (curr_number > result->max_set[2]) {
                result->max_set[2] = curr_number;
            }
            curr_number = 0;
        }
    }
}

int game_valid(Game *game)
{
    int red_valid = game->max_set[0] <= TOTAL_REDS;
    int green_valid = game->max_set[1] <= TOTAL_GREENS;
    int blue_valid = game->max_set[2] <= TOTAL_BLUES;
    return (red_valid && green_valid && blue_valid);
}

void reset_game(Game *game)
{
    game->game_no = 0;
    game->max_set[0] = 0;
    game->max_set[1] = 0;
    game->max_set[2] = 0;
}

size_t part_one(char *file_path)
{
    FILE *fp = fopen(file_path, "r");

    if (fp == NULL) {
        fprintf(stderr, "ERROR: Could not open file %s", file_path);
        exit(1);
    }
    
    char curr_line[256];
    Game curr_game = {0};
    size_t sum = 0;

    while (fgets(curr_line, 256, fp) != NULL) {
        reset_game(&curr_game);
        parse_game(curr_line, &curr_game);
        if (game_valid(&curr_game)) {
            sum += curr_game.game_no;
        }
    }
    return sum;
}

size_t game_power(Game *game)
{
    size_t res = 1;
    res *= game->max_set[0];
    res *= game->max_set[1];
    res *= game->max_set[2];
    return res;
}

size_t part_two(char *file_path)
{
    FILE *fp = fopen(file_path, "r");

    if (fp == NULL) {
        fprintf(stderr, "ERROR: Could not open file %s", file_path);
        exit(1);
    }
    
    char curr_line[256];
    Game curr_game = {0};
    size_t sum = 0;

    while (fgets(curr_line, 256, fp) != NULL) {
        reset_game(&curr_game);
        parse_game(curr_line, &curr_game);
        sum += game_power(&curr_game);
    }
    return sum;
}

int main(void)
{
    char *file_path = "./games.txt";

    size_t result1 = part_one(file_path);
    printf("Part One => %zu\n", result1);

    size_t result2 = part_two(file_path);
    printf("Part Two => %zu\n", result2);

    return 0;
}
