#include <stdio.h>
#include <stdbool.h>

#define BUFFER_SIZE 1000
#define NUM_VOWELS 5
#define NUM_FORBINDEN_SUBSTR 4

int day5_pt1();
int day5_pt2();
int count_vowels(char* word);
bool contains_forbidden_substr(char* word);
bool contains_letter_twice(char* word);
bool two_pair(char* word);
bool letter_repeats(char* word);
void parse_data_5(char* buffer[], int buffer_size);

const char vowels[] = { 'a', 'e', 'i', 'o', 'u' };
const char forbidden[4][2] = { "ab", "cd", "pq", "xy" };

int day5_pt1()
{
    char* buffer[BUFFER_SIZE] = { 0 };
    int sum = 0;
    parse_data_5(buffer, BUFFER_SIZE);

    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        if (contains_forbidden_substr(buffer[i])) continue;
        if (count_vowels(buffer[i]) >= 3 && contains_letter_twice(buffer[i])) sum++;
        free(buffer[i]);
    }

    return sum;
}


int day5_pt2()
{
    char* buffer[BUFFER_SIZE] = { 0 };
    int sum = 0;
    parse_data_5(buffer, BUFFER_SIZE);

    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        if (two_pair(buffer[i]) && letter_repeats(buffer[i])) sum++;
        free(buffer[i]);
    }

    return sum;
}

bool two_pair(char* word)
{
    if (word[0] == 0) return false;

    for (int i = 1; word[i] != 0 && word[i + 1] != 0 && word[i + 2] != 0; i++)
    {
        for (int j = i + 2; word[j] != 0; j++)
        {
            if (word[i] == word[j] && word[i - 1] == word[j - 1]) return true;
        }
    }

    return false;
}

bool letter_repeats(char* word)
{
    if (word[0] == 0) return false;

    for (int i = 1; word[i] != 0 && word[i + 1] != 0; i++)
    {
        if (word[i - 1] == word[i + 1]) return true;
    }

    return false;
}

int count_vowels(char* word)
{
    int num_vowels = 0;

    for (int i = 0; word[i] != 0; i++)
    {
        for (int j = 0; j < NUM_VOWELS; j++)
        {
            if (word[i] == vowels[j])
            {
                num_vowels++;
                break;
            }
        }
    }

    return num_vowels;
}

bool contains_forbidden_substr(char* word)
{
    if (word[0] == 0) return false;

    for (int i = 1; word[i] != 0; i++)
    {
        for (int j = 0; j < NUM_FORBINDEN_SUBSTR; j++)
        {
            if (word[i] == forbidden[j][1] && word[i - 1] == forbidden[j][0]) return true;
        }
    }

    return false;
}

bool contains_letter_twice(char* word)
{
    if (word[0] == 0) return false;

    for (int i = 1; word[i] != 0; i++)
    {
        if (word[i] == word[i - 1]) return true;
    }

    return false;
}

void parse_data_5(char* buffer[], int buffer_size)
{
    FILE* fp;
    int line_count = 0;
    char* line_buffer = malloc(1024);
    fp = fopen("input/day5.txt", "r");

    while (fgets(line_buffer, 1024, fp))
    {
        buffer[line_count] = malloc(strlen(line_buffer) + sizeof(char));
        strcpy(buffer[line_count], line_buffer);
        line_count++;
    }

    free(line_buffer);
}
