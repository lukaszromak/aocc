#include <stdio.h>

int day9_pt1();
int day9_pt2();
void find_shortest_path(int buffer[][8], int vertices[], int vertices_size, int idx);
int calculate_path_length(int buffer[][8], int vertices, int vertices_size);
void parse_data_9(int buffer[][8]);

unsigned int SHORTEST_PATH = 0xffffffff;
unsigned int LONGEST_PATH = 0;

int day9_pt1()
{
    int buffer[8][8] = { 0 };
    int vertices[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    parse_data_9(buffer);
    find_shortest_path(buffer, vertices, 8, 0);

    return SHORTEST_PATH;
}

int day9_pt2()
{
    return LONGEST_PATH;
}

void find_shortest_path(int buffer[][8], int vertices[], int vertices_size, int idx)
{   
    if(idx == vertices_size - 1) 
    {
        int path_len = calculate_path_length(buffer, vertices, vertices_size);

        if(path_len < SHORTEST_PATH)
        {
            SHORTEST_PATH = path_len;
        }

        if(path_len > LONGEST_PATH)
        {
            LONGEST_PATH = path_len;
        }
    }

    for(int i = idx; i < vertices_size; i++)
    {
        int tmp = vertices[idx];
        vertices[idx] = vertices[i];
        vertices[i] = tmp;

        find_shortest_path(buffer, vertices, vertices_size, idx + 1);

        vertices[i] = vertices[idx];
        vertices[idx] = tmp;
    }
}

int calculate_path_length(int buffer[][8], int vertices[], int vertices_size)
{
    int path_length = 0;

    for(int i = 1; i < vertices_size; i++)
    {
        path_length += buffer[vertices[i - 1]][vertices[i]];
    }

    return path_length;
}

void parse_data_9(int buffer[][8])
{
    FILE* fp;
    int from_city = -1;
    int to_city = -1;
    int word_count = 0;
    char* current_city = malloc(1024);
    char* line_buffer = malloc(1024);
    char* word_buffer = malloc(1024);
    fp = fopen("input/day9.txt", "r");

    while(fgets(line_buffer, 1024, fp))
    {
        word_buffer = strtok(line_buffer, " ");

        while(word_buffer != NULL)
        {
            if(word_count == 0 && strcmp(current_city, word_buffer) != 0)
            {
                from_city++;
                to_city = from_city + 1;
                strcpy(current_city, word_buffer);
            }
            
            if(word_count == 4)
            {
                long distance = strtol(word_buffer, NULL, 0);
                buffer[from_city][to_city] = distance;
                buffer[to_city][from_city] = distance;
            }

            word_buffer = strtok(NULL, " ");
            word_count++;
        }
        
        word_count = 0;
        to_city++;
    }

    free(line_buffer);
    free(word_buffer);
}