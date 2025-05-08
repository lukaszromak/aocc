#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

const int DAY20_INPUT = 29000000;

int day20_pt1();
int day20_pt2();

int day20_pt1()
{
    int num_houses = DAY20_INPUT / 10;
    int buff_size = (num_houses + 1) * sizeof(uint32_t);
    int* buff = malloc(buff_size);
    memset(buff, 0, buff_size);

    for(int i = 1; i <= num_houses; i++)
    {
        for(int j = i; j <= num_houses; j += i)
        {
            buff[j] += i * 10;
        }
    }

    for(int i = 1; i <= num_houses; i++)
    {
        if(buff[i] >= DAY20_INPUT)
        {
            free(buff);
            return i;
        }
    }

    free(buff);

    return -1;
}

int day20_pt2()
{
    int num_houses = DAY20_INPUT / 10;
    int buff_size = (num_houses + 1) * sizeof(uint32_t);
    int* buff = malloc(buff_size);
    memset(buff, 0, buff_size);

    for(int i = 1; i <= num_houses; i++)
    {
        for(int j = i; j <= num_houses && j / i <= 50; j += i)
        {
            buff[j] += i * 11;
        }
    }

    for(int i = 1; i <= num_houses; i++)
    {
        if(buff[i] >= DAY20_INPUT)
        {
            free(buff);
            return i;
        }
    }

    free(buff);

    return -1;
}