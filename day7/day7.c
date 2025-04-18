#include <stdio.h>
#include <stdbool.h>

#define NO_OP 0
#define AND 1
#define OR 2
#define LSHIFT 3
#define RSHIFT 4
#define NOT 5
#define INPUT_BUFFER_SIZE 339
#define WIRE_NAME_SIZE 256

struct Wire {
    char* wire_name;
    bool signal_set;
    int signal_value;
    char* input_1;
    char* input_2;
    int raw_input_1;
    int raw_input_2;
    int operation;
};

int resolve_signal_value(struct Wire buffer[], int buffer_size, char* wire_to_resolve);
int find_wire(struct Wire buffer[], int buffer_size, char* wire);
void parse_data(struct Wire buffer[], int buffer_size);
void print_parsed_data(struct Wire buffer[], int buffer_size);
bool is_number(char* str);

//global variable to pass pt1 result to pt2 func
int PT1_RES = 0;

int day7_pt1()
{
    struct Wire buffer[INPUT_BUFFER_SIZE] = { -1 };
    int a_signal;

    parse_data(buffer, INPUT_BUFFER_SIZE);
    a_signal = resolve_signal_value(buffer, INPUT_BUFFER_SIZE, "a");

    PT1_RES = a_signal;

    return a_signal;
}

int day7_pt2()
{
    struct Wire buffer[INPUT_BUFFER_SIZE] = { -1 };
    int a_signal;

    parse_data(buffer, INPUT_BUFFER_SIZE);
    int wire_idx = find_wire(buffer, INPUT_BUFFER_SIZE, "b");
    buffer[wire_idx].input_1 = NULL;
    buffer[wire_idx].input_2 = NULL;
    buffer[wire_idx].raw_input_1 = PT1_RES;
    buffer[wire_idx].raw_input_2 = -1;
    buffer[wire_idx].operation = NO_OP;
    a_signal = resolve_signal_value(buffer, INPUT_BUFFER_SIZE, "a");
    
    return a_signal;
}

int resolve_signal_value(struct Wire buffer[], int buffer_size, char* wire_to_resolve) 
{
    int wire_idx = find_wire(buffer, buffer_size, wire_to_resolve);

    if(wire_idx == -1)
    {
        return -1;
    } 

    struct Wire wire = buffer[wire_idx];

    if(wire.signal_set == true)
    {
        return wire.signal_value;
    }

    int arg1 = -1;
    int arg2 = -1;

    if(wire.input_1 != NULL)
    {
        arg1 = resolve_signal_value(buffer, buffer_size, wire.input_1);
    }

    if(wire.input_2 != NULL)
    {
        arg2 = resolve_signal_value(buffer, buffer_size, wire.input_2);
    }

    if(wire.input_1 == NULL && wire.raw_input_1 != -1)
    {
        arg1 = wire.raw_input_1;
    }

    if(wire.input_2 == NULL && wire.raw_input_2 != -1)
    {
        arg2 = wire.raw_input_2;
    }

    int signal = -1;

    switch(wire.operation)
    {
        case NO_OP:
            if(arg1 == -1) 
            {
                signal = arg2;
            }
            else
            {
                signal = arg1;
            }
            break;
        case AND:
            signal = arg1 & arg2;
            break;
        case OR:
            signal = arg1 | arg2;
            break;
        case LSHIFT:
            signal = arg1 << arg2;
            break;
        case RSHIFT:
            signal = arg1 >> arg2;
            break;
        case NOT:
            if(arg1 == -1)
            {
                signal = ~arg2;
            }
            else
            {
                signal = ~arg1;
            }
            break;
    }

    buffer[wire_idx].signal_set = true;
    buffer[wire_idx].signal_value = signal;

    return signal;
}

int find_wire(struct Wire buffer[], int buffer_size, char* wire)
{
    for(int i = 0; i < buffer_size; i++)
    {
        if(strcmp(buffer[i].wire_name, wire) == 0)
        {
            return i;
        }
    }

    return -1;
}

void parse_data(struct Wire buffer[], int buffer_size)
{
    FILE* fp;
    int line_count = 0;
    int word_count = 0;
    fp = fopen("input/day7.txt", "r");
    char* line_buffer = malloc(256);
    char* word_buffer = malloc(256);
    bool name_next = false;
    int arg_count = 0;

    while(fgets(line_buffer, 256, fp))
    {
        word_buffer = strtok(line_buffer, " ");
        buffer[line_count].signal_set = false;
        buffer[line_count].signal_value = -1;

        while(word_buffer != NULL)
        {
            if(strcmp(word_buffer, "AND") == 0)
            {
                buffer[line_count].operation = AND;
            }
            else if(strcmp(word_buffer, "OR") == 0)
            {
                buffer[line_count].operation = OR;
            }
            else if(strcmp(word_buffer, "LSHIFT") == 0)
            {
                buffer[line_count].operation = LSHIFT;
            }
            else if(strcmp(word_buffer, "RSHIFT") == 0)
            {
                buffer[line_count].operation = RSHIFT;
            }
            else if(strcmp(word_buffer, "NOT") == 0)
            {
                buffer[line_count].operation = NOT;
            } 
            else if(name_next)
            {
                buffer[line_count].wire_name = malloc(WIRE_NAME_SIZE);
                if(word_buffer[strlen(word_buffer) - 1] == 10)
                {
                   word_buffer[strlen(word_buffer) - 1] = 0; 
                }
                strcpy(buffer[line_count].wire_name, word_buffer);
            }
            else if(strcmp(word_buffer, "->") == 0)
            {
                name_next = true;
            }
            else 
            {
                if(arg_count == 0 && is_number(word_buffer)) 
                {
                    buffer[line_count].raw_input_1 = strtol(word_buffer, NULL, 0);
                }
                else if(arg_count == 0 && !is_number(word_buffer)) 
                {
                    buffer[line_count].input_1 = malloc(WIRE_NAME_SIZE);
                    strcpy(buffer[line_count].input_1, word_buffer);
                }
                else if(arg_count == 1 && is_number(word_buffer)) 
                {
                    buffer[line_count].raw_input_2 = strtol(word_buffer, NULL, 0);
                }
                else if(arg_count == 1 && !is_number(word_buffer)) 
                {
                    buffer[line_count].input_2 = malloc(WIRE_NAME_SIZE);
                    strcpy(buffer[line_count].input_2, word_buffer);
                }
                arg_count++;
            }

            word_buffer = strtok(NULL, " ");
            word_count++;
        }

        arg_count = 0;
        name_next = false;
        word_count = 0;
        line_count++;
    }

    free(line_buffer);
    free(word_buffer);
    fclose(fp);
}

void print_parsed_data(struct Wire buffer[], int buffer_size)
{
    for(int i = 0; i < buffer_size; i++)
    {
        printf("Wire name: %s, signal value: %d, input_1: %s, input_2: %s, input_1 (number): %d, input_2 (number): %d, operation: %d\n", 
            buffer[i].wire_name, buffer[i].signal_value, buffer[i].input_1, buffer[i].input_2, buffer[i].raw_input_1, buffer[i].raw_input_2, buffer[i].operation);
    }
}

bool is_number(char* str)
{
    int length = strlen(str);

    for(int i = 0; i < length; i++)
    {
        if(!isdigit(str[i])) return false;
    }

    return true;
}