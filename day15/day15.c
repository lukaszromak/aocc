#include <stdio.h>

#define PT2_DESIRED_CALORIES 500

typedef struct Ingridient {
    int capacity;
    int durability;
    int flavor;
    int texture;
    int calories;
} Ingridient;

Ingridient* parse_input_day15(int num_ingridients);
void search_combinations(Ingridient* ingridients, int* curr_combination, int combination_size, int n, int units);

const char* DAY15_INPUT_FILE_PATH = "input/day15.txt";
int DAY15_MAX_SCORE = 0;
int DAY15_PT2_MAX_SCORE = 0;

int day15_pt1()
{
    int num_ingridients = 0;
    Ingridient* ingridients = parse_input_day15(&num_ingridients);

    int curr_combination[4] = {0, 0, 0, 0};

    search_combinations(ingridients, curr_combination, 4, 0, 100);

    free(ingridients);

    return DAY15_MAX_SCORE;
}

int day15_pt2()
{
    return DAY15_PT2_MAX_SCORE;
}

void search_combinations(Ingridient* ingridients, int* curr_combination, int combination_size, int n, int units)
{
    if(curr_combination[n] + units < 100) return;

    if (n == combination_size)
    {
        int sum = 0;
        for (int i = 0; i < combination_size; i++)
        {
            sum += curr_combination[i];
        }

        if (sum == 100)
        {
            int calories = sum_calories(ingridients, curr_combination, combination_size);
            int score = ingridients_combination_score(ingridients, curr_combination, combination_size);

            if(score > DAY15_MAX_SCORE)
            {
                DAY15_MAX_SCORE = score;
            }

            if(calories == PT2_DESIRED_CALORIES && score > DAY15_PT2_MAX_SCORE)
            {
                DAY15_PT2_MAX_SCORE = score;
            }
        }

        return;
    }

    for (int i = 0; i <= units ; i++)
    {
        curr_combination[n] = i;
        search_combinations(ingridients, curr_combination, combination_size, n + 1, units - i);
    }
}

int ingridients_combination_score(Ingridient* ingridients, int* curr_combination, int combination_size)
{
    int capacity_sum = 0;
    int durability_sum = 0;
    int flavor_sum = 0;
    int texture_sum = 0;

    for(int i = 0; i < combination_size; i++)
    {
        capacity_sum += curr_combination[i] * ingridients[i].capacity;
        durability_sum += curr_combination[i] * ingridients[i].durability;
        flavor_sum += curr_combination[i] * ingridients[i].flavor;
        texture_sum += curr_combination[i] * ingridients[i].texture;
    }

    if(capacity_sum <= 0 || durability_sum <= 0 || flavor_sum <= 0 || texture_sum <= 0) return 0;

    return capacity_sum * durability_sum * flavor_sum * texture_sum;
}

int sum_calories(Ingridient* ingridients, int* curr_combination, int combination_size)
{
    int calories_sum = 0;

    for (int i = 0; i < combination_size; i++)
    {
        calories_sum += curr_combination[i] * ingridients[i].calories;
    }

    return calories_sum;
}

Ingridient* parse_input_day15(int* num_ingridients)
{
    FILE* fp = fopen(DAY15_INPUT_FILE_PATH, "r");
    int line_buffer_size = 1024;
    char* line_buffer = malloc(line_buffer_size);
    char* tmp;
    Ingridient* ingridients = malloc(sizeof(Ingridient) * 10);
    int curr_token = 0;

    (*num_ingridients) = 0;

    while (fgets(line_buffer, line_buffer_size, fp) != NULL)
    {
        tmp = strtok(line_buffer, " ");
        while (tmp != NULL)
        {
            if (curr_token == 2)
            {
                ingridients[*num_ingridients].capacity = strtol(tmp, NULL, 10);
            }
            else if (curr_token == 4)
            {
                ingridients[*num_ingridients].durability = strtol(tmp, NULL, 10);
            }
            else if (curr_token == 6)
            {
                ingridients[*num_ingridients].flavor = strtol(tmp, NULL, 10);
            }
            else if (curr_token == 8)
            {
                ingridients[*num_ingridients].texture = strtol(tmp, NULL, 10);
            }
            else if (curr_token == 10)
            {
                ingridients[*num_ingridients].calories = strtol(tmp, NULL, 10);
            }

            tmp = strtok(NULL, " ");
            curr_token++;
        }
        
        (*num_ingridients)++;
        curr_token = 0;
    }

    fclose(fp);
    free(line_buffer);

    return ingridients;
}