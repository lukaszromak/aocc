#include <stdio.h>
#include "../utils/utils.h"

const char* DAY14_INPUT_FILE_PATH = "input/day14.txt";
const int RACE_TIME = 2503;

struct Reindeer {
    int flyingSpeed;
    int flyingTime;
    int cycleTime;
    int restingTime;
};

struct Reindeer* parse_input_day14(int num_reindeers);

int day14_pt1()
{
    int num_reindeers = count_lines_in_file(DAY14_INPUT_FILE_PATH);
    struct Reindeer* reindeers = parse_input_day14(num_reindeers);
    return day14_pt1_internal(reindeers, num_reindeers);
}

int day14_pt2()
{
    int num_reindeers = count_lines_in_file(DAY14_INPUT_FILE_PATH);
    struct Reindeer* reindeers = parse_input_day14(num_reindeers);
    return day14_pt2_internal(reindeers, num_reindeers);
}

int day14_pt1_internal(struct Reindeer* reindeers, int num_reindeers)
{
    int max_dist_travelled = 0;
    int curr_dist_travelled = 0;
    int time_passed = 0;

    for(int i = 0; i < num_reindeers; i++)
    {
        while(time_passed <= RACE_TIME)
        {
            curr_dist_travelled += reindeers[i].flyingSpeed * reindeers[i].flyingTime;
            time_passed += reindeers[i].flyingTime;

            if(time_passed > RACE_TIME)
            {
                curr_dist_travelled -= reindeers[i].flyingSpeed * (time_passed - RACE_TIME);
                break;
            }

            time_passed += reindeers[i].restingTime;
        }

        if(curr_dist_travelled > max_dist_travelled)
        {
            max_dist_travelled = curr_dist_travelled;
        }

        curr_dist_travelled = 0;
        time_passed = 0;
    }

    return max_dist_travelled;
}

int day14_pt2_internal(struct Reindeer* reindeers, int num_reindeers)
{
    int* curr_dist_travelled = malloc(sizeof(int) * num_reindeers);
    int* curr_points = malloc(sizeof(int) * num_reindeers);
    memset(curr_dist_travelled, 0, num_reindeers * sizeof(int));
    memset(curr_points, 0, num_reindeers * sizeof(int));
    int curr_max_dist = 0;

    for(int i = 0; i < RACE_TIME; i++)
    {
        for(int j = 0; j < num_reindeers; j++)
        {
            if(i % reindeers[j].cycleTime < reindeers[j].flyingTime)
            {
                curr_dist_travelled[j] += reindeers[j].flyingSpeed;
            }

            if(curr_dist_travelled[j] > curr_max_dist)
            {
                curr_max_dist = curr_dist_travelled[j];
            }
        }

        for(int j = 0; j < num_reindeers; j++)
        {
            if(curr_dist_travelled[j] == curr_max_dist) curr_points[j]++;
        }

        curr_max_dist = 0;
    }

    int max_num_points = 0;
    for(int i = 0; i < num_reindeers; i++) if(curr_points[i] > max_num_points) max_num_points = curr_points[i];

    free(curr_dist_travelled);
    free(curr_points);

    return max_num_points;
}

struct Reindeer* parse_input_day14(int num_reindeers)
{
    FILE* fp = fopen(DAY14_INPUT_FILE_PATH, "r");
    char* line_buffer = malloc(1024);
    char** line_split;
    struct Reindeer* reindeers = malloc(sizeof(struct Reindeer) * num_reindeers);
    int curr_reindeer = 0;

    while(fgets(line_buffer, 1024, fp) != NULL)
    {
        line_split = str_split(line_buffer, ' ');
        reindeers[curr_reindeer].flyingSpeed = atoi(line_split[3]);
        reindeers[curr_reindeer].flyingTime = atoi(line_split[6]);
        reindeers[curr_reindeer].restingTime = atoi(line_split[13]);
        reindeers[curr_reindeer].cycleTime = reindeers[curr_reindeer].flyingTime + reindeers[curr_reindeer].restingTime;
        for(int i = 0; *(line_split + i); i++) free(*(line_split + i)); 
        free(line_split);
        curr_reindeer++;
    }

    free(line_buffer);
    fclose(fp);

    return reindeers;
}