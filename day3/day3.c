#include <stdio.h>
#include <stdbool.h>
#include <time.h>

struct point {
    int x;
    int y;
};

char* parse_data();
int day3_pt1();
int day3_pt2();
char* parse_data_3();
bool point_exists(struct point* buffer, int num_of_points, struct point point_to_check);

int day3_pt1()
{
    char* directions = parse_data_3();
    int buffer_size = 1024 * 16;
    struct point* buffer = malloc(sizeof(struct point) * buffer_size);
    int num_of_points = 0;
    struct point curr_point = { 0, 0 };

    for(int i = 0; directions[i] != 0; i++)
    {
        if(!point_exists(buffer, num_of_points, curr_point))
        {
            buffer[num_of_points].x = curr_point.x;
            buffer[num_of_points].y = curr_point.y;
            num_of_points++;
        }

        switch(directions[i])
        {
            case '<':
                curr_point.x--;
                break;
            case '>':
                curr_point.x++;
                break;
            case 'v':
                curr_point.y--;
                break;
            case '^':
                curr_point.y++;
                break;
            default:
                break;
        }

        if(!point_exists(buffer, num_of_points, curr_point))
        {
            buffer[num_of_points].x = curr_point.x;
            buffer[num_of_points].y = curr_point.y;
            num_of_points++;
        }
    }

    free(directions);

    return num_of_points;
}

int day3_pt2()
{
    char* directions = parse_data_3();
    int buffer_size = 1024 * 16;
    struct point* buffer = malloc(sizeof(struct point) * buffer_size);
    int num_of_points = 0;
    struct point curr_santa = { 0, 0 };
    struct point curr_robo_santa = { 0, 0 };
    struct point curr_point = { 0, 0 };
    bool santa_turn = true;

    for(int i = 0; directions[i] != 0; i++)
    {
        if(santa_turn)
        {
            curr_point = curr_santa;
        } else {
            curr_point = curr_robo_santa;
        }

        if(!point_exists(buffer, num_of_points, curr_point))
        {
            buffer[num_of_points].x = curr_point.x;
            buffer[num_of_points].y = curr_point.y;
            num_of_points++;
        }

        switch(directions[i])
        {
            case '<':
                curr_point.x--;
                break;
            case '>':
                curr_point.x++;
                break;
            case 'v':
                curr_point.y--;
                break;
            case '^':
                curr_point.y++;
                break;
            default:
                break;
        }

        if(!point_exists(buffer, num_of_points, curr_point))
        {
            buffer[num_of_points].x = curr_point.x;
            buffer[num_of_points].y = curr_point.y;
            num_of_points++;
        }

        if(santa_turn)
        {
            curr_santa = curr_point;
        } else {
            curr_robo_santa = curr_point;
        }

        santa_turn = !santa_turn;
    }

    free(directions);

    return num_of_points;
}

bool point_exists(struct point* buffer, int num_of_points, struct point point_to_check)
{
    for(int i = 0; i < num_of_points; i++)
    {
        if(buffer[i].x == point_to_check.x && buffer[i].y == point_to_check.y)
        {
            return true;
        }
    }

    return false;
}

char* parse_data_3()
{
    FILE* fp;
    fp = fopen("input/day03.txt", "r");
    int buffer_size = 1024 * 16;
    char* buffer = malloc(sizeof(char) * buffer_size);

    fgets(buffer, buffer_size, fp);
    
    fclose(fp);

    return buffer;
}