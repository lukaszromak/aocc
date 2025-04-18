#include <stdio.h>

#define SEED "1321131112"

int day10_pt1();
int day10_pt2();
int look_and_say();
int chars_in_str(char* str);

int day10_pt1()
{
    return look_and_say(SEED, 40);
}

int day10_pt2()
{
    return look_and_say(SEED, 50);
}

int look_and_say(char* seed, int rounds)
{
    char* buffer = malloc(1024 * 1024 * 16);
    char* temp_buffer = malloc(1024 * 1024 * 16);
    char* temp_buffer_pos = temp_buffer;
    char curr_char = 0;
    int char_count = 0;
    strcpy(buffer, seed);

    for (int i = 0; i < rounds; i++)
    {
        for (int j = 0; buffer[j] != 0; j++)
        {
            if (buffer[j] != curr_char)
            {
                if (curr_char != 0)
                {
                    temp_buffer_pos += sprintf(temp_buffer_pos, "%d", char_count);
                    *temp_buffer_pos = curr_char;
                    temp_buffer_pos++;
                    *temp_buffer_pos = 0;
                }
                curr_char = buffer[j];
                char_count = 0;
            }

            char_count++;
        }

        temp_buffer_pos += sprintf(temp_buffer_pos, "%d", char_count);
        *temp_buffer_pos = curr_char;
        temp_buffer_pos++;
        *temp_buffer_pos = 0;
        char_count = 0;
        curr_char = 0;
        strcpy(buffer, temp_buffer);
        temp_buffer_pos = temp_buffer;
    }

    return chars_in_str(buffer);
}

int chars_in_str(char* str)
{
    int chars = 0;

    for(int i = 0; str[i] != 0; i++) chars++;

    return chars;
}


