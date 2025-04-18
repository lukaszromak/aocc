#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct cuboid* parse_data_2(FILE* fp, int* dstSize);
struct cuboid {
    long l;
    long w;
    long h;
};

int day2_pt1()
{
    FILE* fp;
    struct cuboid* cubes;
    int cubesSize = 0;
    int sum = 0;
    long l = 0;
    long w = 0;
    long h = 0;

    fp = fopen("input/day2.txt", "r");
    cubes = parse_data_2(fp, &cubesSize);
    fclose(fp);

    for (int i = 0; i < cubesSize; i++)
    {
        //2*l*w + 2*w*h + 2*h*l + smallestSide
        // sum += 2 * l * w + 2 * w * h + 2 * h * l;
        l = cubes[i].l;
        w = cubes[i].w;
        h = cubes[i].h;

        sum += 2 * l * w + 2 * w * h + 2 * h * l;

        if ((l * w <= w * h) && (l * w <= h * l))
        {
            sum += l * w;
        }
        else if ((w * h <= l * w) && (w * h <= h * l))
        {
            sum += w * h;
        }
        else if ((h * l <= l * w) && (h * w))
        {
            sum += h * l;
        }
    }

    free(cubes);
    
    return sum;
}

int day2_pt2() {
    FILE* fp;
    struct cuboid* cubes;
    int cubesSize = 0;
    int sum = 0;
    long l = 0;
    long w = 0;
    long h = 0;

    fp = fopen("input/day2.txt", "r");
    cubes = parse_data_2(fp, &cubesSize);
    fclose(fp);

    for (int i = 0; i < cubesSize; i++)
    {
        //2*l*w + 2*w*h + 2*h*l + smallestSide
        // sum += 2 * l * w + 2 * w * h + 2 * h * l;
        l = cubes[i].l;
        w = cubes[i].w;
        h = cubes[i].h;

        sum += l * w * h;

        if ((l * w <= w * h) && (l * w <= h * l))
        {
            sum += l * 2 + w * 2;
        }
        else if ((w * h <= l * w) && (w * h <= h * l))
        {
            sum += w * 2 + h * 2;
        }
        else if ((h * l <= l * w) && (h * w))
        {
            sum += h * 2 + l * 2;
        }
    }

    free(cubes);

    return sum;
}

struct cuboid* parse_data_2(FILE* fp, int* dstSize)
{
#define bufferLength 255
    struct cuboid* cubes = malloc(sizeof(struct cuboid) * 1000);
    char lineBuffer[bufferLength];
    char* wordBuffer;
    int currentWord = 0;

    while (fgets(lineBuffer, bufferLength, fp))
    {
        size_t len = strlen(lineBuffer);

        if (len > 0 && lineBuffer[len - 1] == '\n') {
            lineBuffer[len - 1] = '\0';
        }

        wordBuffer = strtok(lineBuffer, "x");

        while (wordBuffer != NULL)
        {
            *((long*)((cubes)+*dstSize) + currentWord) = strtol(wordBuffer, NULL, 0);
            currentWord++;
            wordBuffer = strtok(NULL, "x");
        }
        (*dstSize)++;
        currentWord = 0;
    }

    return cubes;
}

