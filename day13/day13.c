#include <stdio.h>
#include <string.h>

const char* DAY13_INPUT_FILE_PATH = "input/day13.txt";
int DAY13_LONGEST_PATH = 0;

int* parse_data_13(int num_nodes);
void find_longest_path(int* buffer, int vertices[], int vertices_size, int idx);
int* array_n_consecutive_numbers(int n);

int day13_pt1()
{
    int vertices_size = calculate_num_nodes();
    int* vertices_dist = parse_data_13(vertices_size);
    int* vertices = array_n_consecutive_numbers(vertices_size);

    find_longest_path(vertices_dist, vertices, vertices_size, 0);

    free(vertices_dist);
    free(vertices);

    return DAY13_LONGEST_PATH;
}

int day13_pt2()
{
    int vertices_size = calculate_num_nodes() + 1;
    int* vertices_dist = parse_data_13(vertices_size);
    int* vertices = array_n_consecutive_numbers(vertices_size);

    DAY13_LONGEST_PATH = 0;

    find_longest_path(vertices_dist, vertices, vertices_size, 0);

    free(vertices_dist);
    free(vertices);

    return DAY13_LONGEST_PATH;
}

void find_longest_path(int* buffer, int vertices[], int vertices_size, int idx)
{   
    if(idx == vertices_size - 1) 
    {
        int path_len = DAY13_calculate_path_length(buffer, vertices, vertices_size);

        if(path_len > DAY13_LONGEST_PATH)
        {
            DAY13_LONGEST_PATH = path_len;
        }
    }

    for(int i = idx; i < vertices_size; i++)
    {
        int tmp = vertices[idx];
        vertices[idx] = vertices[i];
        vertices[i] = tmp;

        find_longest_path(buffer, vertices, vertices_size, idx + 1);

        vertices[i] = vertices[idx];
        vertices[idx] = tmp;
    }
}

int DAY13_calculate_path_length(int* buffer, int vertices[], int vertices_size) {
    int sum = 0;

    for(int i = 0; i < vertices_size - 1; i++)
    {
        sum += *(buffer + vertices[i] * vertices_size + vertices[i + 1]);
        sum += *(buffer + vertices[i + 1] * vertices_size + vertices[i]);
    }

    sum += *(buffer + vertices[0] * vertices_size + vertices[vertices_size - 1]);
    sum += *(buffer + vertices[vertices_size - 1] * vertices_size + vertices[0]);

    return sum;
}


int* parse_data_13(int num_nodes)
{
    int vertices_buffer_size = sizeof(int) * num_nodes * num_nodes;
    int* vertices_buffer = malloc(vertices_buffer_size);
    memset(vertices_buffer, 0, vertices_buffer_size);
    FILE* fp;
    fp = fopen(DAY13_INPUT_FILE_PATH, "r");
    char* line_buffer = malloc(1024);
    char* tmp;
    int current_node = 0;
    int current_neighbour_node = 1;
    int current_value = 1;
    char* current_node_name = malloc(1024);

    fgets(line_buffer, 1024, fp);
    tmp = strtok(line_buffer, " ");
    strcpy(current_node_name, tmp);
    rewind(fp);

    while (fgets(line_buffer, 1024, fp))
    {
        tmp = strtok(line_buffer, " ");
        if (strcmp(current_node_name, tmp) != 0)
        {
            current_node++;
            current_neighbour_node = 0;
            strcpy(current_node_name, tmp);
        }

        if(current_node == current_neighbour_node)
        {
            current_neighbour_node++;
        }

        // skip would
        strtok(NULL, " ");

        //figure out the sign
        if (strcmp("lose", strtok(NULL, " ")) == 0)
        {
            current_value = -1;
        }
        else
        {
            current_value = 1;
        }

        current_value *= strtol(strtok(NULL, " "), NULL, 0);

        vertices_buffer[current_node * num_nodes + current_neighbour_node] = current_value;

        current_neighbour_node++;
    }

    free(current_node_name);
    free(line_buffer);
    fclose(fp);

    return vertices_buffer;
}

int calculate_num_nodes()
{
    FILE* fp;
    fp = fopen(DAY13_INPUT_FILE_PATH, "r");
    char* line_buffer = malloc(1024);
    char* first_node_name;
    char* current_node_name;
    int num_nodes = 1;

    fgets(line_buffer, 1024, fp);
    current_node_name = strtok(line_buffer, " ");
    first_node_name = malloc(strlen(current_node_name) + 1);
    strcpy(first_node_name, current_node_name);
    rewind(fp);

    while (fgets(line_buffer, 1024, fp))
    {
        current_node_name = strtok(line_buffer, " ");
        if (strcmp(first_node_name, current_node_name) != 0) {
            break;
        }

        num_nodes += 1;
    }

    free(line_buffer);
    free(first_node_name);
    fclose(fp);
    
    return num_nodes;
}

int* array_n_consecutive_numbers(int n)
{
    int* arr = malloc(sizeof(int) * n);

    for(int i = 0; i < n; i++)
    {
        arr[i] = i;
    }

    return arr;
}