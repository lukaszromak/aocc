#include <stdio.h>
#include <stdbool.h>

#define INPUT_BUFFER_SIZE 300

void parse_data_8(char* buffer[], int buffer_size);

int day8_pt1()
{
    int total_chars_mem = 0;
    int chars_in_line_mem = 0;
    int total_chars_code = 0;
    int chars_in_line_code = 0;
    bool prev_backslash = false;
    char* buffer[INPUT_BUFFER_SIZE] = { NULL };
    parse_data_8(buffer, INPUT_BUFFER_SIZE);

    for (int i = 0; i < INPUT_BUFFER_SIZE; i++)
    {
        for (int j = 0; buffer[i][j] != 0; j++)
        {
            if (prev_backslash && buffer[i][j] == '\\')
            {
                chars_in_line_mem--;
            }

            if (prev_backslash && buffer[i][j] == '\"')
            {
                chars_in_line_mem--;
            }

            if (prev_backslash && buffer[i][j] == 'x')
            {
                chars_in_line_mem -= 3;
            }

            if (buffer[i][j] == '\\' && !prev_backslash)
            {
                prev_backslash = true;
            }
            else {
                prev_backslash = false;
            }

            chars_in_line_mem++;
            chars_in_line_code++;
        }

        total_chars_code += chars_in_line_code;
        total_chars_mem += chars_in_line_mem;
        total_chars_mem -= 2;
        chars_in_line_code = 0;
        chars_in_line_mem = 0;
        prev_backslash = false;
    }

    return total_chars_code - total_chars_mem;
}

int day8_pt2()
{
    int total_chars_weird = 0;
    int total_chars_code = 0;
    bool prev_backslash = false;
    char* buffer[INPUT_BUFFER_SIZE] = { NULL };
    parse_data_8(buffer, INPUT_BUFFER_SIZE);

    for(int i = 0; i < INPUT_BUFFER_SIZE; i++)
    {
        for(int j = 0; buffer[i][j] != 0; j++)
        {
            if(buffer[i][j] == '\"')
            {
                total_chars_weird++;
            }

            if(buffer[i][j] == '\\')
            {
                total_chars_weird++;
            }

            total_chars_code++;
            total_chars_weird++;
        }
        total_chars_weird += 2;
    }

    return total_chars_weird - total_chars_code;
}

void parse_data_8(char* buffer[], int buffer_size)
{
    FILE* fp;
    fp = fopen("input/day8.txt", "r");
    char* line_buffer = malloc(1024);
    int line_count = 0;

    while (fgets(line_buffer, 1024, fp))
    {
        buffer[line_count] = malloc(1024);
        strcpy(buffer[line_count], line_buffer);

        line_count++;
    }

    free(line_buffer);
    fclose(fp);
}