#include <stdio.h>
#include <stdbool.h>

#define NUM_ROWS 100
#define NUM_COLS 100

bool* parse_input_day18(int num_rows, int num_cols);
void update_board(bool* board, int num_rows, int num_cols, bool pt2);
bool should_die(bool* board, int num_rows, int num_cols, int row, int col);
int count_alive(bool* board, int num_rows, int num_cols);

const char* DAY18_INPUT_FILE_PATH = "input/day18.txt";

int day18_pt1()
{
    bool* board = parse_input_day18(NUM_ROWS, NUM_COLS);

    for(int i = 0; i < 100; i++)
    {
        update_board(board, NUM_ROWS, NUM_COLS, false);
    }

    int res = count_alive(board, NUM_ROWS, NUM_COLS);

    free(board);

    return res;
}

int day18_pt2()
{
    bool* board = parse_input_day18(NUM_ROWS, NUM_COLS);

    for(int i = 0; i < 100; i++)
    {
        update_board(board, NUM_ROWS, NUM_COLS, true);
    }

    int res = count_alive(board, NUM_ROWS, NUM_COLS);

    free(board);

    return res;
}

bool* parse_input_day18(int num_rows, int num_cols)
{
    FILE* fp = fopen(DAY18_INPUT_FILE_PATH, "r");

    if(fp == NULL)
    {
        printf("File not found.\n");
        return NULL;
    }

    bool* board = malloc(num_rows * num_cols * sizeof(bool));
    int line_buffer_size = 1024;
    char* line_buffer = malloc(line_buffer_size);

    int i = 0;
    while(fgets(line_buffer, line_buffer_size, fp) != NULL)
    {
        for(int j = 0; j < NUM_COLS; j++)
        {
            if(line_buffer[j] == '#')
            {
                *((board + i * num_rows) + j) = true;
            }
            else if(line_buffer[j] == '.')
            {
                *((board + i * num_cols) + j) = false;
            }
        }
        i++;
    }

    fclose(fp);
    free(line_buffer);

    return board;
}

void update_board(bool* board, int num_rows, int num_cols, bool pt2)
{
    int board_size = num_rows * num_cols * sizeof(bool);
    bool* new_board = (bool*)malloc(num_rows * num_cols * sizeof(bool));

    if (new_board == 0) return;

    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            if(pt2 && ((i == 0 && j == 0) || (i == 0 && j == num_cols - 1) || (i == num_rows - 1 && j == 0) || (i == num_rows - 1 && j == num_cols - 1))) 
            {
                *((new_board + i * num_cols) + j) = true;
            }
            else if (should_die(board, num_rows, num_cols, i, j))
            {
                *((new_board + i * num_cols) + j) = false;
            }
            else
            {
                *((new_board + i * num_cols) + j) = true;
            }
        }
    }

    memcpy(board, new_board, board_size);
    free(new_board);
}

bool should_die(bool* board, int num_rows, int num_cols, int row, int col)
{
    int alive_neighbours = 0;
    int num_neighbours_to_stay_alive[2] = { 2, 3 };
    int num_neighbours_to_born[1] = { 3 };

    if (row > 0)
    {
        if (*((board + (row - 1) * num_cols) + col)) alive_neighbours++;
        if (col > 0 && *((board + (row - 1) * num_cols) + (col - 1))) alive_neighbours++;
        if (col < num_cols - 1 && *((board + (row - 1) * num_cols) + (col + 1))) alive_neighbours++;
    }
    if (row < num_rows - 1)
    {
        if (*((board + (row + 1) * num_cols) + col)) alive_neighbours++;
        if (col > 0 && *((board + (row + 1) * num_cols) + (col - 1))) alive_neighbours++;
        if (col < num_cols - 1 && *((board + (row + 1) * num_cols) + (col + 1))) alive_neighbours++;
    }
    if (col > 0 && *((board + row * num_cols) + (col - 1))) alive_neighbours++;
    if (col < num_cols - 1 && *((board + row * num_cols) + (col + 1))) alive_neighbours++;

    if (*((board + row * num_cols) + col)) {
        for (int i = 0; i < sizeof(num_neighbours_to_stay_alive) / sizeof(int); i++)
        {
            if (alive_neighbours == num_neighbours_to_stay_alive[i])
            {
                return false;
            }
        }
        return true;
    }

    for (int i = 0; i < sizeof(num_neighbours_to_born) / sizeof(int); i++)
    {
        if (alive_neighbours == num_neighbours_to_born[i])
        {
            return false;
        }
    }

    return true;
}

int count_alive(bool* board, int num_rows, int num_cols)
{
    int res = 0;

    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            if (*((board + i * num_cols) + j))
            {
                res += 1;
            }
        }
    }

    return res;
}