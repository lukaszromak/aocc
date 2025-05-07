#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE 300
#define WHICH_OP_IDX 0
#define TURN_OFF 0
#define TURN_ON 1
#define TOGGLE 2
#define ALL_ONES 0xffffffff

struct point {
    int x;
    int y;
};

struct operation {
    struct point from;
    struct point to;
    int op_type;
};

void parse_data_6(struct operation buffer[], int buffer_size);
int num_lights_turned_on_bool(bool buffer[][1000], int buffer_size);
int num_lights_turned_on_int(int buffer[][1000], int buffer_size);

int day6_pt1()
{
    int buffer_size = BUFFER_SIZE;
    struct operation buffer[BUFFER_SIZE] = { 0 };
    parse_data_6(buffer, BUFFER_SIZE);
    
    bool lights_state[1000][1000] = { false };

    for (int i = 0; i < buffer_size; i++)
    {
        switch (buffer[i].op_type)
        {
        case TURN_ON:
            for (int j = buffer[i].from.x; j <= buffer[i].to.x; j++)
            {
                for (int k = buffer[i].from.y; k <= buffer[i].to.y; k++)
                {
                    lights_state[j][k] = true;
                }
            }
            break;
        case TURN_OFF:
            for (int j = buffer[i].from.x; j <= buffer[i].to.x; j++)
            {
                for (int k = buffer[i].from.y; k <= buffer[i].to.y; k++)
                {
                    lights_state[j][k] = false;
                }
            }
            break;
        case TOGGLE:
            for (int j = buffer[i].from.x; j <= buffer[i].to.x; j++)
            {
                for (int k = buffer[i].from.y; k <= buffer[i].to.y; k++)
                {
                    lights_state[j][k] = !lights_state[j][k];
                }
            }
            break;
        }
    }

    return num_lights_turned_on_bool(lights_state, 1000);
}


int day6_pt2()
{
    int buffer_size = BUFFER_SIZE;
    struct operation buffer[BUFFER_SIZE] = { 0 };
    parse_data_6(buffer, BUFFER_SIZE);

    int (*lights_state)[1000] = malloc(sizeof(int[1000][1000]));

    for (int i = 0; i < buffer_size; i++)
    {
        switch (buffer[i].op_type)
        {
        case TURN_ON:
            for (int j = buffer[i].from.x; j <= buffer[i].to.x; j++)
            {
                for (int k = buffer[i].from.y; k <= buffer[i].to.y; k++)
                {
                    lights_state[j][k]++;
                }
            }
            break;
        case TURN_OFF:
            for (int j = buffer[i].from.x; j <= buffer[i].to.x; j++)
            {
                for (int k = buffer[i].from.y; k <= buffer[i].to.y; k++)
                {
                    if(lights_state[j][k] >= 1) lights_state[j][k]--;
                }
            }
            break;
        case TOGGLE:
            for (int j = buffer[i].from.x; j <= buffer[i].to.x; j++)
            {
                for (int k = buffer[i].from.y; k <= buffer[i].to.y; k++)
                {
                    lights_state[j][k] += 2;
                }
            }
            break;
        }
    }

    return num_lights_turned_on_int(lights_state, 1000);
}

int num_lights_turned_on_bool(bool buffer[][1000], int buffer_size)
{
    int sum = 0;

    for (int i = 0; i < buffer_size; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            if (buffer[i][j]) sum++;
        }
    }

    return sum;
}

int num_lights_turned_on_int(int buffer[][1000], int buffer_size)
{
    int sum = 0;

    for (int i = 0; i < buffer_size; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            sum += buffer[i][j];
        }
    }

    return sum;
}


void parse_data_6(struct operation buffer[], int buffer_size)
{
    FILE* fp;
    int word_count = 0;
    int line_count = 0;
    bool is_toggle = false;
    int from_idx = -1;
    int to_idx = -1;
    char* comma_p = NULL;
    char* line_buffer = malloc(1024);
    char* word_buffer = malloc(1024);
    fp = fopen("input/day06.txt", "r");

    while (fgets(line_buffer, 1024, fp))
    {
        word_buffer = strtok(line_buffer, " ");

        while (word_buffer != NULL)
        {
            if (word_count == WHICH_OP_IDX)
            {
                if (strcmp(word_buffer, "toggle") == 0)
                {
                    buffer[line_count].op_type = TOGGLE;
                    is_toggle = true;
                    from_idx = 1;
                    to_idx = 3;
                }
                else {
                    is_toggle = false;
                    from_idx = 2;
                    to_idx = 4;
                }
            }
            else if (!is_toggle && word_count == from_idx - 1)
            {
                if (strcmp(word_buffer, "on") == 0)
                {
                    buffer[line_count].op_type = TURN_ON;
                }
                else
                {
                    buffer[line_count].op_type = TURN_OFF;
                }
            }
            else if (word_count == from_idx)
            {
                comma_p = strchr(word_buffer, ',');
                *comma_p = 0;
                buffer[line_count].from.x = strtol(word_buffer, NULL, 0);
                buffer[line_count].from.y = strtol(comma_p + 1, NULL, 0);
            }
            else if (word_count == to_idx)
            {
                comma_p = strchr(word_buffer, ',');
                *comma_p = 0;
                buffer[line_count].to.x = strtol(word_buffer, NULL, 0);
                buffer[line_count].to.y = strtol(comma_p + 1, NULL, 0);
            }

            word_buffer = strtok(NULL, " ");
            word_count++;
        }

        word_count = 0;
        line_count++;
    }

    free(line_buffer);
    free(word_buffer);
}