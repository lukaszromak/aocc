#include <stdlib.h>
#include <stdio.h>

int* parse_data_day17(int* num_containers);
int count_combinations(int* containers, int num_containers, int n);

const char* DAY17_INPUT_FILE_PATH = "../input/day17.txt";
const int SUM_TO_FIND = 150;

// int main()
// {
//     int num_containers = 0;
//     int* containers = parse_data_day17(&num_containers);

//     printf("%d\n", num_containers);

//     for(int i = 0; i < num_containers; i++)
//     {
//         printf("%d\n", containers[i]);
//     }

//     return 0;
// }

int count_combinations(int* containers, int num_containers, int n)
{
    int window_start = 0;
    int window_end = n;

    return 0;
}

int* parse_data_day17(int* num_containers)
{
    FILE* fp = fopen(DAY17_INPUT_FILE_PATH, "r");
    int line_buffer_size = 1024;
    char* line_buffer = malloc(line_buffer_size);
    int containers_size = 50;
    int* containers = malloc(containers_size * sizeof(int));

    while(fgets(line_buffer, line_buffer_size, fp) != NULL)
    {
        containers[*num_containers] = atoi(line_buffer);
        (*num_containers)++;
    }

    free(line_buffer);

    return containers;
}

