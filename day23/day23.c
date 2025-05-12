#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "../utils/utils.h"

typedef enum InstructionType
{
    HLF,
    TPL,
    INC,
    JMP,
    JIE,
    JIO
} InstructionType;

typedef struct Instruction
{
    int target_register;
    InstructionType instruction_type;
    int offset;
} Instruction;

int day23_solution(int initial_a);
int day23_pt1();
int day23_pt2();

Instruction* parse_input_day23(int* num_instructions);

const char* DAY23_INPUT_FILE_PATH = "input/day23.txt";

int day23_solution(int initial_a)
{
    int num_instructions = 0;
    Instruction* instructions = parse_input_day23(&num_instructions);

    uint64_t registers[2] = { initial_a, 0 };
    int ip = 0;
    Instruction instr;

    char buff[1024];

    while(ip >= 0 && ip < num_instructions)
    {
        instr = instructions[ip];

        switch(instr.instruction_type)
        {
            case HLF:
                registers[instr.target_register] /= 2;
                ip++;
                break;
            case TPL:
                registers[instr.target_register] *= 3;
                ip++;
                break;
            case INC:
                registers[instr.target_register]++;
                ip++;
                break;
            case JMP:
                ip += instr.offset;
                break;
            case JIE:
                if(registers[instr.target_register] % 2 == 0)
                {
                    ip += instr.offset;
                }
                else
                {
                    ip++;
                }
                break;
            case JIO:
                if(registers[instr.target_register] == 1)
                {
                    ip += instr.offset;
                }
                else
                {
                    ip++;
                }
                break;
        }
    }

    return (int) registers[1];
}

int day23_pt1()
{
    return day23_solution(0);
}

int day23_pt2()
{
    return day23_solution(1);
}

Instruction* parse_input_day23(int* num_instructions)
{
    int num_lines = count_lines_in_file(DAY23_INPUT_FILE_PATH);
    FILE* fp = fopen(DAY23_INPUT_FILE_PATH, "r");
    Instruction* instructions = malloc(num_lines * sizeof(Instruction));
    int curr_instruction = 0;
    int line_size = 1024;
    char* line = malloc(1024);
    char* token;

    while(fgets(line, line_size, fp))
    {
        Instruction instruction = {0};
        token = strtok(line, " ");

        if(strcmp(token, "hlf") == 0) instruction.instruction_type = HLF;
        if(strcmp(token, "tpl") == 0) instruction.instruction_type = TPL;
        if(strcmp(token, "inc") == 0) instruction.instruction_type = INC;
        if(strcmp(token, "jmp") == 0) instruction.instruction_type = JMP;
        if(strcmp(token, "jie") == 0) instruction.instruction_type = JIE;
        if(strcmp(token, "jio") == 0) instruction.instruction_type = JIO;
        

        token = strtok(NULL, " ");

        if(instruction.instruction_type == JMP)
        {
            instruction.offset = strtol(token + 1, NULL, 10);
            instruction.target_register = -1;

            if(token[0] == '-')
            {
                instruction.offset *= -1;
            }
        }
        else
        {
            if(strcmp(token, "a\n") == 0 || strcmp(token, "a,\n") == 0) instruction.target_register = 0;
            if(strcmp(token, "b\n") == 0 || strcmp(token, "b,\n") == 0) instruction.target_register = 1;

            if(instruction.instruction_type == JIE || instruction.instruction_type == JIO)
            {
                token = strtok(NULL, "\n");

                instruction.offset = strtol(token + 1, NULL, 10);
    
                if(token[0] == '-')
                {
                    instruction.offset *= -1;
                }
            }
        }

        instructions[*num_instructions] = instruction;
        (*num_instructions)++;
    }

    free(line);
    fclose(fp);

    return instructions;
}