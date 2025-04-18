#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>

#define LAST_PASSWORD "cqjxjnds"

char* day11_pt1();
char* day11_pt2();
bool check_combinations(char* password, int password_len);
//bool check_combinations(char* password, int password_len, int start_offset);
bool is_password_valid(char* password);
bool contains_three_increasing(char* password);
bool contains_forbidden_char(char* password);
bool contains_two_pairs(char* password);

char* DAY11_PT1_RESULT = NULL;

char* day11_pt1()
{
    char* buff = malloc(1024);
    strcpy(buff, LAST_PASSWORD);
    check_combinations(buff, 8);
    DAY11_PT1_RESULT = malloc(strlen(buff) + 1);
    strcpy(DAY11_PT1_RESULT, buff);
    free(buff);
    return buff;
}

char* day11_pt2()
{
    check_combinations(DAY11_PT1_RESULT, 8);

    return DAY11_PT1_RESULT;
}

// char* day11_pt1()
// {
//     char* last_password = LAST_PASSWORD;
//     int last_password_len = strlen(last_password);
//     int start_offset = last_password_len - 3;
//     char* temp_buffer = malloc(1024);

//     while(start_offset >= 0)
//     {
//         char first = last_password[start_offset];
//         char second = last_password[start_offset + 1];
//         char third = last_password[start_offset + 2];

//         strcpy(temp_buffer, last_password);

//         if(second > first + 1)
//         {
//             first++;
//             second = first + 1;
//             third = second + 1;
//         } else {
//             second = first + 1;
//             third = second + 1;
//         }

//         while(true)
//         {
//             temp_buffer[start_offset] = first;
//             temp_buffer[start_offset + 1] = second;
//             temp_buffer[start_offset + 2] = third;

//             if(is_password_valid(temp_buffer))
//             {
//                 return temp_buffer;
//             }

//             if(start_offset < last_password_len - 3)
//             {
//                 if(check_combinations(temp_buffer, last_password_len, start_offset))
//                 {
//                     return temp_buffer;   
//                 }
//             }

//             first++;
//             second++;
//             third++;

//             if(third > 'z')
//             {
//                 start_offset--;
//                 break;
//             }
//         }

//     }

//     free(temp_buffer);

//     return NULL;
// }

bool check_combinations(char* password, int password_len)
{
    int i = password_len - 1;

    while(password[0] <= 'z')
    {
        password[password_len - 1]++;

        if(password[password_len - 1] > 'z')
        {
            password[password_len - 1] = 'a';

            while(password[i] == 'a' && i >= 1)
            {
                password[i - 1]++;

                if(i - 1 == 0 && password[i - 1] > 'z')
                {
                    password[i - 1] = 'z';
                    break;
                }

                if(password[i - 1] > 'z')
                {
                    password[i - 1] = 'a';
                }

                i--;
            }

            i = password_len - 1;
        }

        if(is_password_valid(password))
        {
            return true;
        }
    }

    return false;
}

// bool check_combinations(char* password, int password_len, int start_offset)
// {
//     char c = password[start_offset + 3 - 1];
//     int i = password_len - 1;

//     while(password[start_offset + 3 - 1] == c)
//     {
//         password[password_len - 1]++;

//         if(password[password_len - 1] > 'z')
//         {
//             password[password_len - 1] = 'a';

//             while(password[i] == 'a' && i >= 1)
//             {
//                 password[i - 1]++;

//                 if(password[i - 1] > 'z')
//                 {
//                     password[i - 1] = 'a';
//                 }

//                 i--;
//             }

//             i = password_len - 1;
//         }

//         if(is_password_valid(password))
//         {
//             return true;
//         }
//     }

//     return false;
// }

bool is_password_valid(char* password)
{
    return contains_three_increasing(password) && !contains_forbidden_char(password) && contains_two_pairs(password);
}

bool contains_three_increasing(char* password)
{
    for(int i = 0; password[i + 2] != 0; i++)
    {
        if(password[i] == password[i + 1] - 1 && password[i + 1] == password[i + 2] - 1) return true;
    }

    return false;
}

bool contains_forbidden_char(char* password)
{
    for(int i = 0; password[i] != 0; i++)
    {
        if(password[i] == 'i' || password[i] == 'o' || password[i] == 'l') return true;
    }

    return false;
}

bool contains_two_pairs(char* password)
{
    char pair_char = 0;

    for(int i = 0; password[i] != 0 && password[i + 1] != 0; i++)
    {
        if(password[i] == password[i + 1])
        {
            if(pair_char != 0) return true;
            pair_char = password[i];
            i++;
        }
    }

    return false;
}