#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../utils/utils.h"

typedef struct Aunt {
    int children;
    int cats;
    int samoyeds;
    int pomeranians;
    int akitas;
    int vizslas;
    int goldfish;
    int trees;
    int cars;
    int perfumes;
} Aunt;

int day16_pt1();
int day16_pt2();
Aunt* parse_input_day16(int* num_aunts);
Aunt parse_mfcsam();
Aunt parse_aunt_str();

const char* DAY16_MFCSAM_FILE_PATH = "input/day16_mfcsam.txt";
const char* DAY16_FILE_INPUT_PATH = "input/day16.txt";
int DAY16_PT1_RES = 0;
int DAY16_PT2_RES = 0;

int day16_pt1()
{
    Aunt sample_aunt = parse_mfcsam();
    int num_aunts;
    Aunt* aunts = parse_input_day16(&num_aunts);

    for(int i = 0; i < num_aunts; i++)
    {
        if((aunts[i].children != -1 && aunts[i].children != sample_aunt.children) ||
        (aunts[i].cats != -1 && aunts[i].cats != sample_aunt.cats) ||
        (aunts[i].samoyeds != -1 && aunts[i].samoyeds != sample_aunt.samoyeds) ||
        (aunts[i].pomeranians != -1 && aunts[i].pomeranians != sample_aunt.pomeranians) ||
        (aunts[i].akitas != -1 && aunts[i].akitas != sample_aunt.akitas) ||
        (aunts[i].vizslas != -1 && aunts[i].vizslas != sample_aunt.vizslas) ||
        (aunts[i].goldfish != -1 && aunts[i].goldfish != sample_aunt.goldfish) ||
        (aunts[i].trees != -1 && aunts[i].trees != sample_aunt.trees) ||
        (aunts[i].cars != -1 && aunts[i].cars != sample_aunt.cars) ||
        (aunts[i].perfumes != -1 && aunts[i].perfumes != sample_aunt.perfumes)) continue;
        DAY16_PT1_RES = i + 1;
        break;
    }

    for(int i = 0; i < num_aunts; i++)
    {
        if((aunts[i].children != -1 && aunts[i].children != sample_aunt.children) ||
        (aunts[i].cats != -1 && aunts[i].cats <= sample_aunt.cats) ||
        (aunts[i].samoyeds != -1 && aunts[i].samoyeds != sample_aunt.samoyeds) ||
        (aunts[i].pomeranians != -1 && aunts[i].pomeranians >= sample_aunt.pomeranians) ||
        (aunts[i].akitas != -1 && aunts[i].akitas != sample_aunt.akitas) ||
        (aunts[i].vizslas != -1 && aunts[i].vizslas != sample_aunt.vizslas) ||
        (aunts[i].goldfish != -1 && aunts[i].goldfish >= sample_aunt.goldfish) ||
        (aunts[i].trees != -1 && aunts[i].trees <= sample_aunt.trees) ||
        (aunts[i].cars != -1 && aunts[i].cars != sample_aunt.cars) ||
        (aunts[i].perfumes != -1 && aunts[i].perfumes != sample_aunt.perfumes)) continue;

        DAY16_PT2_RES = i + 1;

        break;
    }

    free(aunts);

    return DAY16_PT1_RES;
}

int day16_pt2()
{
    return DAY16_PT2_RES;
}

Aunt* parse_input_day16(int* num_aunts)
{
    FILE* fp = fopen(DAY16_FILE_INPUT_PATH, "r");
    int line_buffer_size = 1024;
    char* line_buffer = malloc(line_buffer_size);
    char* token_buffer;
    int curr_token = 0;
    Aunt* aunts = malloc(500 * sizeof(Aunt));
    *num_aunts = 0;

    while(fgets(line_buffer, line_buffer_size, fp))
    {
        token_buffer = strtok(line_buffer, " ");
        while(token_buffer != NULL)
        {
            if(curr_token == 2)
            {
                int i = 0;
                while(1 == 1)
                {
                    if(token_buffer[i] == 0)
                    {
                        token_buffer[i] = ' ';
                        break;
                    }
                    i++;
                }
                aunts[*num_aunts] = parse_aunt_str(token_buffer);
                
                break;
            }
            token_buffer = strtok(NULL, " ");
            curr_token++;
        }

        (*num_aunts)++;
        curr_token = 0;
    }

    free(line_buffer);
    fclose(fp);

    return aunts;
}

Aunt parse_mfcsam()
{
    FILE* fp = fopen(DAY16_MFCSAM_FILE_PATH, "r");
    int line_buffer_size = 1024;
    char* line_buffer = malloc(line_buffer_size);
    char* aunt_str = malloc(1024);
    aunt_str[0] = '\0';
    char* tmp = aunt_str;

    while(fgets(line_buffer, line_buffer_size, fp) != NULL)
    {
        line_buffer[strcspn(line_buffer, "\n")] = '\0';
        strcat(line_buffer, ", ");
        strcat(aunt_str, line_buffer);
        aunt_str += strlen(line_buffer);
    }

    aunt_str = tmp;

    return parse_aunt_str(aunt_str);
}

Aunt parse_aunt_str(char* str)
{
    Aunt aunt = {
        .children = -1,
        .cats = -1,
        .samoyeds = -1,
        .pomeranians = -1,
        .akitas = -1,
        .vizslas = -1,
        .goldfish = -1,
        .trees = -1,
        .cars = -1,
        .perfumes = -1
    };
    char** compounds = str_split(str, ' ');
    char** compound_splitted;
    char* compound;
    int compound_count;

    if (compounds)
    {
        for (int i = 0; *(compounds + i); i++)
        {
            if(i % 2 == 0)
            {
                compound = *(compounds + i);
            } 
            else if(i % 2 == 1)
            {
                compound_count = strtol(*(compounds + i), NULL, 10);
                if (strcmp(compound, "children:") == 0)
                {
                    aunt.children = compound_count;
                }
                else if (strcmp(compound, "cats:") == 0)
                {
                    aunt.cats = compound_count;
                }
                else if (strcmp(compound, "samoyeds:") == 0)
                {
                    aunt.samoyeds = compound_count;
                }
                else if (strcmp(compound, "pomeranians:") == 0)
                {
                    aunt.pomeranians = compound_count;
                }
                else if (strcmp(compound, "akitas:") == 0)
                {
                    aunt.akitas = compound_count;
                }
                else if (strcmp(compound, "vizslas:") == 0)
                {
                    aunt.vizslas = compound_count;
                }
                else if (strcmp(compound, "goldfish:") == 0)
                {
                    aunt.goldfish = compound_count;
                }
                else if (strcmp(compound, "trees:") == 0)
                {
                    aunt.trees = compound_count;
                }
                else if (strcmp(compound, "cars:") == 0)
                {
                    aunt.cars = compound_count;
                }
                else if (strcmp(compound, "perfumes:") == 0)
                {
                    aunt.perfumes = compound_count;
                }
            }
        }

        for (int i = 0; *(compounds + i); i++) free(*(compounds + i));
        free(compounds);
    }

    return aunt;
}



