#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "../utils/utils.h"

char* day24_pt1();
char* day24_pt2();
int* parse_input_day24(int* num_weights);
uint64_t traverse(int* arr, int n, int k, int start, int* combo, int depth, int num_groups);
bool can_split_even(int* arr, int arr_size, int* arr2, int arr2_size, int num_groups);

const char* DAY24_INPUT_FILE_PATH = "input/day24.txt";

char* day24_pt1()
{
    int num_weights = 0;
    int* weights = parse_input_day24(&num_weights);
    char* buff = malloc(21);

    for(int k = 1; k <= num_weights; k++)
    {
        int* combo = malloc(sizeof(int) * k);
        uint64_t res = traverse(weights, num_weights, k, 0, combo, 0, 2);
        free(combo);

        if(res != 0)
        {
            snprintf(buff, 21, "%lu", res);
            return buff;
        }
    }

    return "";
}

char* day24_pt2()
{
    int num_weights = 0;
    int* weights = parse_input_day24(&num_weights);
    char* buff = malloc(21);

    for(int k = 1; k <= num_weights; k++)
    {
        int* combo = malloc(sizeof(int) * k);
        uint64_t res = traverse(weights, num_weights, k, 0, combo, 0, 3);
        free(combo);

        if(res != 0)
        {
            snprintf(buff, 21, "%lu", res);
            return buff;
        }
    }

    return "";
}

uint64_t traverse(int* arr, int n, int k, int start, int* combo, int depth, int num_groups)
{
    uint64_t res = 1;

    if(depth == k)
    {
        int combo_sum = 0;
        int rest_sum = 0;

        for(int i = 0; i < k; i++)
        {
            combo_sum += combo[i];
        }

        int contains = 0;

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < k; j++)
            {
                if(arr[i] == combo[j])
                {
                    contains = 1;
                    break;
                }
            }

            if(!contains)
            {
                rest_sum += arr[i];
            }

            contains = 0;
        }

        if(combo_sum * num_groups == rest_sum)
        {
            if(can_split_even(arr, n, combo, k, num_groups))
            {
                res = 1;

                for(int i = 0; i < k; i++)
                {
                    res *= combo[i];
                }

                return res;
            }
        }

        return 0;
    }

    for(int i = start; i < n; i++)
    {
        combo[depth] = arr[i];
        res = traverse(arr, n, k, i + 1, combo, depth + 1, num_groups);

        if(res != 0)
        {
            return res;
        }
    }

    return 0;
}

bool can_split_even(int* arr, int arr_size, int* arr2, int arr2_size, int num_groups)
{
    int* filtered_arr = malloc((arr_size - arr2_size) * sizeof(int));
    int num_filtered = 0;
    int filtered_sum = 0;

    for(int i = 0; i < arr_size; i++)
    {
        bool contains = false;

        for(int j = 0; j < arr2_size; j++)
        {
            if(arr[i] == arr2[j])
            {
                contains = true;
                break;
            }
        }

        if(!contains)
        {
            filtered_arr[num_filtered] = arr[i];
            filtered_sum += arr[i];
            num_filtered++;
        }
    }

    if(filtered_sum % num_groups != 0)
    {
        free(filtered_arr);
        return false;
    }

    int target = filtered_sum / num_groups;
    bool* dp = malloc((target + 1) * sizeof(bool));
    memset(dp, false, (target + 1) * sizeof(bool));
    dp[0] = true;

    for(int i = 0; i < num_filtered; i++)
    {
        for(int j = target; j >= filtered_arr[i]; j--)
        {
            dp[j] = dp[j] || dp[j - filtered_arr[i]];
        }
    }

    bool res = dp[target];
    free(filtered_arr);
    free(dp);

    return res;
}

int* parse_input_day24(int* num_weights)
{
    int weights_size = count_lines_in_file(DAY24_INPUT_FILE_PATH);
    int* weights = malloc(weights_size * sizeof(int));
    FILE* fp = fopen(DAY24_INPUT_FILE_PATH, "r");
    char line[1024];

    while(fgets(line, 1024, fp))
    {
        weights[*num_weights] = strtol(line, NULL, 10);
        (*num_weights)++;
    }

    return weights;
}
