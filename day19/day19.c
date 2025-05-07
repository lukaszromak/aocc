#include <stdio.h>
#include <stdbool.h>

#define NUM_REPLACEMENTS 43
#define REPLACEMENT_MAXIMUM_FROM_SIZE 2

typedef struct Replacement {
    char* from;
    char* to;
} Replacement;

typedef struct OccuredReplacement {
    int position;
    char* from;
    char* to;
} OccuredReplacement;

bool check_is_duplicate(char* molecule, int molecule_len, Replacement replacement, int position, OccuredReplacement occured_replacement);
Replacement* parse_input_replacement_day19(int* num_replacements);
char* parse_input_molecule_day19();

const char* DAY19_INPUT_FILE_PATH = "../input/day19s.txt";

// int main()
// {
//     int num_replacements = 0;
//     Replacement* replacements = parse_input_replacement_day19(&num_replacements);
//     char* molecule = parse_input_molecule_day19();
//     int molecule_len = strlen(molecule) + 20;
//     OccuredReplacement* occured_replacements = malloc(molecule_len * sizeof(OccuredReplacement) * REPLACEMENT_MAXIMUM_FROM_SIZE);
//     memset(occured_replacements, -1, molecule_len * sizeof(OccuredReplacement) * REPLACEMENT_MAXIMUM_FROM_SIZE);
//     bool replacement_match = true;
//     bool replacement_duplicate = false;
//     int tmp = 0;
//     int replacement_count = 0;

//     for(int i = 0; molecule[i]; i++)
//     {
//         for(int j = 0; j < num_replacements; j++)
//         {
//             replacement_match = true;
//             tmp = i;

//             //printf("Checking replacement %s\n", replacements[j]);

//             for(int k = 0; replacements[j].from[k]; k++)
//             {
//                 //printf("%c %c\n", molecule[tmp], replacements[j].from[k]);
//                 if(molecule[tmp] != replacements[j].from[k])
//                 {
//                     replacement_match = false;
//                     break;
//                 }
//                 tmp++;
//             }
            
//             if(replacement_match)
//             {
//                 replacement_duplicate = false;
//                 printf("POS: %d, %s => %s\n", i, replacements[j].from, replacements[j].to);

//                 for(int l = 0; l < molecule_len * 2; l++)
//                 {
//                     printf("%d\n", occured_replacements[l].position != -1);
//                     if(occured_replacements[l].position != -1 && check_is_duplicate(molecule, molecule_len, replacements[j], i, occured_replacements[l])) 
//                     {
//                         replacement_duplicate = true;
//                         break;
//                     }
//                 }

//                 if(!replacement_duplicate) replacement_count++;

//                 replacement_duplicate = false;

//                 // save it as occured
//                 int replacement_length = strlen(replacements[j].from);

//                 if(replacement_length == 1)
//                 {
//                     occured_replacements[i * 2].position = i;
//                     occured_replacements[i * 2].from = replacements[j].from;
//                     occured_replacements[i * 2].to = replacements[j].to;
//                 }
//                 else if(replacement_length == 2)
//                 {
//                     occured_replacements[i * 2 + 1].position = i;
//                     occured_replacements[i * 2 + 1].from = replacements[j].from;
//                     occured_replacements[i * 2 + 1].to = replacements[j].to;
//                 }
//             }

//             replacement_match = true;
//         }
//     }
//     printf("%d\n", replacement_count);
// }

bool check_is_duplicate(char* molecule, int molecule_len, Replacement replacement, int position, OccuredReplacement occured_replacement)
{
    char* molecule_a = malloc((molecule_len + 1));
    char* molecule_b = malloc((molecule_len + 1));
    int a_ch_w = 0;
    int b_ch_w = 0;
    int rfsz = strlen(replacement.from);
    int orfsz = strlen(occured_replacement.from);

    // printf("CHECKING POSITION %d WITH POSITION %d\n", position, occured_replacement.position);
    // printf("%d: %s => %s\n", position, replacement.from, replacement.to);
    // printf("%d: %s => %s\n", occured_replacement.position, occured_replacement.from, occured_replacement.to);

    // just copy all chars until replacement occured
    for(a_ch_w; a_ch_w < position; a_ch_w++)
    {
        molecule_a[a_ch_w] = molecule[a_ch_w];
    }
    // same here
    for(b_ch_w; b_ch_w < occured_replacement.position; b_ch_w++)
    {
        molecule_b[b_ch_w] = molecule[b_ch_w];
    }
    // copy all transform chars
    int j = 0;
    for(a_ch_w; replacement.to[j]; a_ch_w++)
    {
        molecule_a[a_ch_w] = replacement.to[j];
        j++;
    }
    // same here
    j = 0;
    for(b_ch_w; occured_replacement.to[j]; b_ch_w++)
    {
        molecule_b[b_ch_w] = occured_replacement.to[j];
        j++;
    }
    // copy remaining
    for(int i = position + rfsz; molecule[i]; i++)
    {
        molecule_a[a_ch_w] = molecule[i];
        a_ch_w++;
    }
    for(int i = occured_replacement.position + orfsz; molecule[i]; i++)
    {
        molecule_b[b_ch_w] = molecule[i];
        b_ch_w++;
    }

    molecule_a[a_ch_w] = 0;
    molecule_b[b_ch_w] = 0;

    printf("%s\n", molecule_b);

    bool res = strcmp(molecule_a, molecule_b) == 0;
    
    free(molecule_a);
    free(molecule_b);

    return res;
}

// bool check_is_duplicate(char* molecule, int molecule_len, Replacement replacement, int position, OccuredReplacement occured_replacement)
// {
//     char* molecule_a = malloc((molecule_len + 1) * sizeof(char));
//     char* molecule_b = malloc((molecule_len + 1) * sizeof(char));
//     int replacement_from_size = strlen(replacement.from);
//     int occured_replacement_from_size = strlen(occured_replacement.from);
//     int molecule_a_chars_written = 0;
//     int molecule_b_chars_written = 0;

//     printf("CHECKING DUPLICATE\n");

//     printf("COPYING INTO MOLECULE A...\n");
//     for(int i = 0; i < position; i++) { molecule_a[i] = molecule[i]; molecule_a_chars_written++; printf("%c", molecule_a[i]); }
//     printf("\n");
//     printf("COPYING INTO MOLECULE B...\n");
//     for(int i = 0; i < occured_replacement.position; i++) { molecule_b[i] = molecule[i]; molecule_b_chars_written++; printf("%c", molecule_b[i]); }
//     printf("\n");

//     printf("COPYING INTO MOLECULE A...\n");
//     int j = 0;
//     for(int i = position; replacement.to[j]; i++) { molecule_a[i] = replacement.to[++j]; molecule_a_chars_written++; printf("%c", replacement.to[j]); }
//     printf("\n");
//     printf("COPYING INTO MOLECULE B...\n");
//     j = 0;
//     for(int i = occured_replacement.position; occured_replacement.to[j]; i++) { molecule_b[i] = occured_replacement.to[++j]; molecule_b_chars_written++; printf("%c", molecule_b[i]); }
//     printf("\n");

//     printf("COPYING INTO MOLECULE A...\n");
//     for(int i = molecule_a_chars_written; molecule[i]; i++) { molecule_a[i] = molecule[i]; molecule_a_chars_written++; printf("%c", molecule[i]); }
//     printf("\n");
//     printf("COPYING INTO MOLECULE B...\n");
//     for(int i = molecule_b_chars_written; molecule[i]; i++) { molecule_b[i] = molecule[i]; molecule_b_chars_written++; printf("%c", molecule_b[i]); }
//     printf("\n");
//     printf("\n");
//     // int molecule_a_len = 0;
//     // while(molecule[++molecule_a_len] != 0) {}
//     // int molecule_b_len = 0;
//     // while(molecule[++molecule_b_len] != 0) {}

//     molecule_a[molecule_a_chars_written] = 0;
//     molecule_b[molecule_b_chars_written] = 0;

//     // for(int i = 0; molecule_a[i]; i++)
//     // {
//     //     printf("%d ", molecule_a[i]);
//     // }
//     // printf("\n");

//     printf("%s\n", molecule_a);
//     printf("%s\n", molecule_b);
//     printf("\n");

//     return true;
// }

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
                token_buffer[strcspn(line_buffer, "\n") + 1] = 0;
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