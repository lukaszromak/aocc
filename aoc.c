#include <stdio.h>
#include "day1/day1.h"
#include "day2/day2.h"
#include "day3/day3.h"
#include "day4/day4.h"
#include "day5/day5.h"
#include "day6/day6.h"
#include "day7/day7.h"
#include "day8/day8.h"
#include "day9/day9.h"
#include "day10/day10.h"
#include "day11/day11.h"
#include "day12/day12.h"
#include "day13/day13.h"
#include "day14/day14.h"
#include "day15/day15.h"
#include "day16/day16.h"
#include "day17/day17.h"
#include "day18/day18.h"
#include "day20/day20.h"
#include "day21/day21.h"
#include "day22/day22.h"
#include "day23/day23.h"
#include "day24/day24.h"
#include "day25/day25.h"
#include <time.h>

int (*pt1[25]) () = 
{
    day1_pt1,
    day2_pt1,
    day3_pt1,
    day4_pt1,
    day5_pt1,
    day6_pt1,
    day7_pt1,
    day8_pt1,
    day9_pt1,
    day10_pt1,
    NULL,
    day12_pt1,
    day13_pt1,
    day14_pt1,
    day15_pt1,
    day16_pt1,
    day17_pt1,
    day18_pt1,
    NULL,
    day20_pt1,
    day21_pt1,
    day22_pt1,
    day23_pt1,
    NULL,
    day25_pt1
};

int (*pt2[25]) () = 
{
    day1_pt2,
    day2_pt2,
    day3_pt2,
    day4_pt2,
    day5_pt2,
    day6_pt2,
    day7_pt2,
    day8_pt2,
    day9_pt2,
    day10_pt2,
    NULL,
    day12_pt2,
    day13_pt2,
    day14_pt2,
    day15_pt2,
    day16_pt2,
    day17_pt2,
    day18_pt2,
    NULL,
    day20_pt2,
    day21_pt2,
    day22_pt2,
    day23_pt2,
    NULL,
};

char* (*pt1_str[25]) () = 
{
};

char* (*pt2_str[25]) () =
{
};

int main() {
    pt1_str[10] = day11_pt1;
    pt2_str[10] = day11_pt2;
    pt1_str[23] = day24_pt1;
    pt2_str[23] = day24_pt2;

    char* result_str;
    int result;
    clock_t begin;
    clock_t end;
    double time_spent;
    double total_time_spent = 0;

    for(int i = 0; i < 24; i++)
    {
        if(pt1[i] != NULL)
        {
            begin = clock();
            result = pt1[i]();
            end = clock();
            time_spent = (double)(end - begin) / (CLOCKS_PER_SEC / 1000);
            printf("Day %d, part 1: %d, time to run: %f ms\n", i + 1, result, time_spent);
            total_time_spent += time_spent;
        }

        if(pt1_str[i] != NULL)
        {
            begin = clock();
            result_str = pt1_str[i]();
            end = clock();
            time_spent = (double)(end - begin) / (CLOCKS_PER_SEC / 1000);
            printf("Day %d, part 1: %s, time to run: %f ms\n", i + 1, result_str, time_spent);
            total_time_spent += time_spent;
        }  

        if(pt2[i] != NULL)
        {
            begin = clock();
            result = pt2[i]();
            end = clock();
            time_spent = (double)(end - begin) / (CLOCKS_PER_SEC / 1000);
            printf("Day %d, part 2: %d, time to run: %f ms\n", i + 1, result, time_spent);
            total_time_spent += time_spent;
        }

        if(pt2_str[i] != NULL)
        {
            begin = clock();
            result_str = pt2_str[i]();
            end = clock();
            time_spent = (double)(end - begin) / (CLOCKS_PER_SEC / 1000);
            printf("Day %d, part 2: %s, time to run: %f ms\n", i + 1, result_str, time_spent);
            total_time_spent += time_spent;
        }
    }

    printf("Total runtime: %f ms\n", total_time_spent);

    return 0;
}