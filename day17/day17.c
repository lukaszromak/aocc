#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

int day17_pt1();
int day17_pt2();
int* parse_data_day17(int* num_containers);
void day17_solution(int* containers, int num_containers);

const char* DAY17_INPUT_FILE_PATH = "input/day17.txt";
const int SUM_TO_FIND = 150;
int DAY17_PT1_SOLUTION = -1;
int DAY17_PT2_SOLUTION = -1;

int day17_pt1()
{
    int num_containers = 0;
    int* containers = parse_data_day17(&num_containers);
    day17_solution(containers, num_containers);
    free(containers);

    return DAY17_PT1_SOLUTION;
}

int day17_pt2()
{
    if(DAY17_PT2_SOLUTION == -1)
    {
        int num_containers = 0;
        int* containers = parse_data_day17(&num_containers);
        day17_solution(containers, num_containers);
        free(containers);
    }

    return DAY17_PT2_SOLUTION;
}

void day17_solution(int* containers, int num_containers)
{
    int current_combination = 0;
    int* masks = malloc(num_containers * sizeof(int));
    int** valid_combinations = malloc((num_containers + 1) * sizeof(int*));
    int* num_valid_combinations = malloc((num_containers + 1) * sizeof(int));
    memset(num_valid_combinations, 0, (num_containers + 1) * sizeof(int));
    int min_ones = INT32_MAX;
    int ones = 0;
    int res_pt1 = 0;
    int sum = 0;

    int curr_mask = 1;

    for(int i = 0; i < num_containers; i++)
    {
        masks[i] = curr_mask;
        curr_mask = curr_mask << 1;
    }

    for(int i = 0; i <= num_containers; i++)
    {
        valid_combinations[i] = malloc(((1 << (num_containers)) / 20) * sizeof(int*));
        memset(valid_combinations[i], 0, ((1 << (num_containers)) / 20) * sizeof(int*));
    }

    while(current_combination < (1 << (num_containers)))
    {
        for(int i = 0; i < num_containers; i++)
        {
            if((current_combination & masks[i]) > 0)
            {
                sum += containers[i];
                ones++;
            }
        }
        if(sum == SUM_TO_FIND)
        {
            res_pt1++;

            if(ones < min_ones)
            {
                min_ones = ones;
            }

            valid_combinations[ones][num_valid_combinations[ones]] = current_combination;
            num_valid_combinations[ones]++;
        }

        sum = 0;
        ones = 0;
        current_combination++;
    }

    int* valid_combinations_values = malloc(((1 << (num_containers)) / 20) * sizeof(int) * min_ones);
    int* curr = malloc(min_ones * sizeof(int));
    int num_valid_combinations_values = 0;

    for(int i = 0; i < num_valid_combinations[min_ones]; i++)
    {
        int curr_one = 0;
        for(int j = 0; j < num_containers; j++)
        {
            if(valid_combinations[min_ones][i] & masks[j])
            {
                curr[curr_one] = containers[j];
                curr_one++;
            }
        }

        bool duplicate = false;
        bool has_element = false;

        for(int j = 0; i < num_valid_combinations_values; j++)
        {
            duplicate = false;

            for(int k = 0; k < min_ones; k++)
            {
                for(int l = 0; l < min_ones; l++)
                {
                    if(curr[k] == valid_combinations_values[j * min_ones + l])
                    {
                        has_element = true;
                    }
                }

                if(!has_element)
                {
                    duplicate = false;
                    break;
                }

                has_element = false;
            }

            if(duplicate) break;
        }

        if(!duplicate)
        {
            memcpy(&valid_combinations_values[num_valid_combinations_values], curr, min_ones);
            num_valid_combinations_values++;
        }

        curr_one = 0;
    }

    free(masks);
    for(int i = 0; i <= num_containers; i++) free(valid_combinations[i]);
    free(valid_combinations);
    free(num_valid_combinations);
    free(valid_combinations_values);
    free(curr);

    DAY17_PT1_SOLUTION = res_pt1;
    DAY17_PT2_SOLUTION = num_valid_combinations_values;
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

