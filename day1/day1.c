#include <stdio.h>

int day1_pt1()
{
    FILE* fp = fopen("input/day1.txt", "r");

    if(fp == NULL)
    {
        printf("No input.txt file\n");
        return -1;
    }

    int floor = 0;
    char c;

    while(c != EOF)
    {
        c = fgetc(fp);
        if(c == '(')
        {
            floor++;
        } 
        else if(c == ')')
        {
            floor--;
        }
    }

    return floor;
}

int day1_pt2()
{
    FILE* fp = fopen("input/day1.txt", "r");

    if(fp == NULL)
    {
        printf("No input.txt file\n");
        return -1;
    }


    int cc = 1;
    int floor = 0;
    char c;

    while(c != EOF)
    {
        c = fgetc(fp);
        if(c == '(')
        {
            floor++;
        } 
        else if(c == ')')
        {
            floor--;
        }
        if(floor == -1)
        {
            return cc;
        }
        cc++;
    }

    return -1;
}