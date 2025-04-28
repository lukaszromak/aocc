#include <stdio.h>
#include <stdbool.h>

#define NUM_REPLACEMENTS 43
#define REPLACEMENT_MAXIMUM_FROM_SIZE 2

typedef struct Replacement {
    char* from;
    char* to;
} Replacement;

typedef struct OccuredReplacement {
    int length;
} OccuredReplacement;

Replacement* parse_input_replacement_day19(int* num_replacements);
char* parse_input_molecule_day19();

const char* DAY19_INPUT_FILE_PATH = "../input/day19.txt";

int main()
{
    int num_replacements = 0;
    Replacement* replacements = parse_input_replacement_day19(&num_replacements);
    char* molecule = parse_input_molecule_day19();
    int molecule_len = strlen(molecule);
    OccuredReplacement* occured_replacements = malloc(molecule_len * sizeof(OccuredReplacement) * REPLACEMENT_MAXIMUM_FROM_SIZE);
    memset(occured_replacements, 0, molecule_len * sizeof(OccuredReplacement) * REPLACEMENT_MAXIMUM_FROM_SIZE);
    bool replacement_match = true;
    int tmp = 0;
    int replacement_count = 0;

    for(int i = 0; molecule[i]; i++)
    {
        for(int j = 0; j < num_replacements; j++)
        {
            replacement_match = true;
            tmp = i;

            //printf("Checking replacement %s\n", replacements[j]);

            for(int k = 0; replacements[j].from[k]; k++)
            {
                //printf("%c %c\n", molecule[tmp], replacements[j].from[k]);
                if(molecule[tmp] != replacements[j].from[k])
                {
                    replacement_match = false;
                    break;
                }
                tmp++;
            }
            
            if(replacement_match)
            {
                int replacement_length = strlen(replacement[j]);

                if(replacement_length == 1)
                {
                    occured_replacements[i * 2].length = replacement_length;
                }
                else if(replacement_length == 2)
                {
                    occured_replacements[i * 2 + 1].length = replacement_length;
                }

                for(int l = 0; l < molecule_len * 2; l++)
                {
                    if(occured_replacements[l].length != 0 && check_is_duplicate())
                }

                replacement_count++;
            }

            replacement_match = true;
        }
    }
    printf("%d\n", replacement_count);
    // printf("%s\n", molecule);

    // printf("%d\n", num_replacements);

    // for(int i = 0; i < num_replacements; i++)
    // {
    //     printf("%s => %s\n", replacements[i].from, replacements[i].to);
    // }
}

Replacement* parse_input_replacement_day19(int* num_replacements)
{
    FILE* fp = fopen(DAY19_INPUT_FILE_PATH, "r");
    int line_buffer_size = 1024;
    char* line_buffer = malloc(line_buffer_size);
    char* token_buffer;
    Replacement* replacements = malloc(NUM_REPLACEMENTS * sizeof(Replacement));
    int curr_token = 0;

    *num_replacements = 0;

    while(fgets(line_buffer, line_buffer_size, fp) != NULL)
    {
        if(strcmp(line_buffer, "\n") == 0) break;

        token_buffer = strtok(line_buffer, " ");
        while(token_buffer != NULL)
        {
            if(curr_token == 0)
            {
                replacements[*num_replacements].from = malloc(strlen(token_buffer) + 1);
                strcpy(replacements[*num_replacements].from, token_buffer);
            }
            else if(curr_token == 2)
            {
                token_buffer[strcspn(line_buffer, "\n")] = 0;
                replacements[*num_replacements].to = malloc(strlen(token_buffer) + 1);
                strcpy(replacements[*num_replacements].to, token_buffer);
            }

            token_buffer = strtok(NULL, " ");
            curr_token++;
        }
        
        (*num_replacements)++;
        curr_token = 0;
    }

    free(line_buffer);
    fclose(fp);

    return replacements;
}

char* parse_input_molecule_day19()
{
    FILE* fp = fopen(DAY19_INPUT_FILE_PATH, "r");
    int line_buffer_size = 1024;
    char* line_buffer = malloc(line_buffer_size);
    bool molecule = false;

    while(fgets(line_buffer, line_buffer_size, fp))
    {
        if(strcmp(line_buffer, "\n") == 0)
        {
            molecule = true;
        }
        else
        {
            if(molecule)
            {
                fclose(fp);
                return line_buffer;
            }
        }
    }

    return NULL;
}