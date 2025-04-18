#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// https://stackoverflow.com/questions/9210528/split-string-with-delimiters-in-c/9210560#9210560
char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        *(result + idx) = 0;
    }

    return result;
}

int count_lines_in_file(const char* file_path)
{
    FILE* fp = fopen(file_path, "r");

    if(fp == NULL)
    {
        return -1;
    }

    char* line_buffer = malloc(1024);
    int count = 0;

    while(fgets(line_buffer, 1024, fp) != NULL)
    {
        count++;
    }

    free(line_buffer);
    fclose(fp);

    return count;
}