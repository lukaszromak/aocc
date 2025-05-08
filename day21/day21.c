#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

const char* DAY21_INPUT_FILE_BOSS_PATH = "input/day21_boss.txt";
const char* DAY21_INPUT_FILE_SHOP_PATH = "input/day21_shop.txt";
const uint32_t DAMAGE_OFFSET = 1;
const uint32_t ARMOUR_OFFSET = 2;
const uint32_t NUM_WEAPONS = 5;
const uint32_t NUM_ARMOURS = 5;
const uint32_t NUM_RINGS = 6;

uint32_t day21_pt1();
uint32_t day21_pt2();
uint32_t* day21_parse_input(const char* file_path, int numbers_to_read);
uint32_t* day21_solution(uint32_t max_val[4], uint32_t* shop, int* boss);

uint32_t day21_pt1()
{
    uint32_t* shop = day21_parse_input(DAY21_INPUT_FILE_SHOP_PATH, (NUM_ARMOURS + NUM_RINGS + NUM_WEAPONS) * 3);
    int* boss = day21_parse_input(DAY21_INPUT_FILE_BOSS_PATH, 3);
    uint32_t max_val[4] = { 4, 4, 5, 5 };

    uint32_t* res = day21_solution(max_val, shop, boss);

    return res[0];
}

uint32_t day21_pt2()
{
    uint32_t* shop = day21_parse_input(DAY21_INPUT_FILE_SHOP_PATH, (NUM_ARMOURS + NUM_RINGS + NUM_WEAPONS) * 3);
    int* boss = day21_parse_input(DAY21_INPUT_FILE_BOSS_PATH, 3);
    uint32_t max_val[4] = { 4, 4, 5, 5 };

    uint32_t* res = day21_solution(max_val, shop, boss);

    return res[1];
}

uint32_t* day21_solution(uint32_t max_val[4], uint32_t* shop, int* boss)
{
    int curr_val[4] = { 0, -1, -1, -1 };
    uint32_t min_gold_spent = UINT32_MAX;
    uint32_t max_gold_spend = 0;
    uint32_t gold_spent = 0;
    int player[3] = { 100, 0, 0 };
    uint32_t boss_hitpoints = boss[0];

    while (curr_val[0] != max_val[0] || curr_val[1] != max_val[1] || curr_val[2] != max_val[2] || curr_val[3] != max_val[3])
    {
        if (curr_val[0] >= 0) {
            // Weapon
            player[DAMAGE_OFFSET] += shop[curr_val[0] * 3 + DAMAGE_OFFSET];
            player[ARMOUR_OFFSET] += shop[curr_val[0] * 3 + ARMOUR_OFFSET];
            gold_spent += shop[curr_val[0] * 3];
        }

        if (curr_val[1] >= 0) {
            // Armour
            player[DAMAGE_OFFSET] += shop[NUM_WEAPONS * 3 + curr_val[1] * 3 + DAMAGE_OFFSET];
            player[ARMOUR_OFFSET] += shop[NUM_WEAPONS * 3 + curr_val[1] * 3 + ARMOUR_OFFSET];
            gold_spent += shop[NUM_WEAPONS * 3 + curr_val[1] * 3];
        }

        if (curr_val[2] >= 0) {
            // Ring 1
            player[DAMAGE_OFFSET] += shop[(NUM_WEAPONS + NUM_ARMOURS) * 3 + curr_val[2] * 3 + DAMAGE_OFFSET];
            player[ARMOUR_OFFSET] += shop[(NUM_WEAPONS + NUM_ARMOURS) * 3 + curr_val[2] * 3 + ARMOUR_OFFSET];
            gold_spent += shop[(NUM_WEAPONS + NUM_ARMOURS) * 3 + curr_val[2] * 3];
        }

        if (curr_val[3] >= 0) {
            // Ring 2
            player[DAMAGE_OFFSET] += shop[(NUM_WEAPONS + NUM_ARMOURS) * 3 + curr_val[3] * 3 + DAMAGE_OFFSET];
            player[ARMOUR_OFFSET] += shop[(NUM_WEAPONS + NUM_ARMOURS) * 3 + curr_val[3] * 3 + ARMOUR_OFFSET];
            gold_spent += shop[(NUM_WEAPONS + NUM_ARMOURS) * 3 + curr_val[3] * 3];
        }

        int player_dmg = 1;
        int boss_dmg = 1;
        bool player_turn = true;

        if((player[DAMAGE_OFFSET] - boss[ARMOUR_OFFSET]) > 1)
        {
            player_dmg = player[DAMAGE_OFFSET] - boss[ARMOUR_OFFSET];
        }

        if((boss[DAMAGE_OFFSET] - player[ARMOUR_OFFSET]) > 1)
        {
            boss_dmg = boss[DAMAGE_OFFSET] - player[ARMOUR_OFFSET];
        }

        while (boss[0] >= 0 && player[0] >= 0)
        {
            if (player_turn) {
                boss[0] -= player_dmg;
            }
            else {
                player[0] -= boss_dmg;
            }

            player_turn = !player_turn;
        }

        if(player[0] > 0 && gold_spent < min_gold_spent)
        {
            min_gold_spent = gold_spent;
        }

        if(boss[0] > 0 && gold_spent > max_gold_spend && curr_val[2] != curr_val[3])
        {
            max_gold_spend = gold_spent;
        }

        player[0] = 100;
        player[1] = 0;
        player[2] = 0;
        boss[0] = boss_hitpoints;
        gold_spent = 0;

        for(int i = 4; i >= 0; i--)
        {
            curr_val[i]++;
            if(curr_val[i] > max_val[i]) {
                curr_val[i] = 0;
            }
            else {
                break;
            }
        }
    }

    uint32_t* res = malloc(2 * sizeof(uint32_t));
    res[0] = min_gold_spent;
    res[1] = max_gold_spend;

    return res;
}

uint32_t* day21_parse_input(const char* file_path, int numbers_to_read)
{
    FILE* fp = fopen(file_path, "r");

    if(fp == NULL)
    {
        printf("Input file not found.");
        return NULL;
    }

    uint32_t* result = malloc(numbers_to_read * sizeof(uint32_t));
    char* number_buff = malloc(100);
    uint32_t numbers_read = 0;
    uint32_t digits_read = 0;
    char ch = 0;

    while(ch != EOF)
    {   
        ch = fgetc(fp);

        if((ch >= '0' && ch <= '9') || ch == '+')
        {
            number_buff[digits_read] = ch;
            digits_read++;
        }
        if((ch < '0' || ch > '9') && digits_read > 0 && ch != '+')
        {
            number_buff[digits_read] = 0;
            if(number_buff[0] != '+')
            {
                result[numbers_read] = strtol(number_buff, NULL, 10);
                numbers_read++;
            }
            
            digits_read = 0;
        }
    }

    return result;
}