#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

const int BOSS_HP = 58;
const int BOSS_DMG = 9;
const int PLAYER_HP = 50;
const int PLAYER_MANA = 500;

typedef enum EffectType
{
    ARMOUR_BUFF,
    DAMAGE,
    MANA_REGEN
} EffectType;

typedef struct Effect
{
    int effect_duration;
    EffectType effect_type;
    int effect_value;
    int is_buff;
} Effect;

typedef struct Skill
{
    int mana_cost;
    int instant_dmg;
    int instant_heal;
    Effect effect;
} Skill;

typedef struct Player
{
    int mana;
    int hp;
    int armour;
    Effect* effects;
    int effects_size;
    int num_effects;
} Player;

typedef struct Boss
{
    int hp;
    int dmg;
    Effect* effects;
    int effects_size;
    int num_effects;
} Boss;

int day22_game(bool auto_play, int rounds_to_play, bool pt2);
int day22_pt1();
int day22_pt2();
void initialize_player(Player* player);
void initialize_boss(Boss* boss);
void my_printf(const char *format, ...);

bool DAY22_PRINT_ENABLED = true;

int day22_pt1()
{
    DAY22_PRINT_ENABLED = false;
    int min_mana_spent = day22_game(true, 1000000, false);

    return min_mana_spent;
}

int day22_pt2()
{
    DAY22_PRINT_ENABLED = false;
    int min_mana_spent = day22_game(true, 1000000, true);

    return min_mana_spent;
}


int day22_game(bool auto_play, int rounds_to_play, bool pt2)
{
    const Skill skills[5] = 
    {
        { 53, 4, -1, { -1, -1, -1, -1 } }, // Magic missile
        { 73, 2, 2, { -1, -1, -1, -1 }}, // Drain
        { 113, -1, -1, { 6, ARMOUR_BUFF, 7, 1} }, // Shield
        { 173, -1, -1, { 6, DAMAGE, 3, 0 }}, // Poison
        { 229, -1, -1, { 5, MANA_REGEN, 101, 1 } } // Recharge
    };

    Player* player = malloc(sizeof(Player));
    Boss* boss = malloc(sizeof(Boss));
    Effect effect;

    initialize_player(player);
    initialize_boss(boss);

    bool player_turn = true;
    bool can_use_skill = true;
    bool l_to_mana;
    int min_mana_used = INT32_MAX;
    int total_mana_used = 0;
    bool available_skills[5] = { 0, 0, 0, 0, 0 };
    int choosen_skill = -1;
    int boss_dmg = 1;
    int effects_next_size = 10;
    Effect* effects_next_p = malloc(effects_next_size * sizeof(Effect));
    int num_effects_next_p = 0;
    Effect* effects_next_b = malloc(effects_next_size * sizeof(Effect));
    int num_effects_next_b = 0;
    const int LINE_BUFF_SIZE = 1024;
    char line_buff[LINE_BUFF_SIZE];
    int round = 1;

    if(auto_play)
    {
        srand(time(NULL));
    }

    do {
        while(player->hp > 0 && boss->hp > 0) {
            //my_printf("Round %d.\n", round);
            //my_printf("Player: %d hp, %d mana, %d armour,\n", player->hp, player->mana, player->armour);

            if(pt2)
            {
                player->hp--;
                //my_printf("Player loses 1 hp point and now has %d hp.\n", player->hp);

                if(player->hp <= 0) break;
            }

            /* Applying effects to player */
            for(int i = 0; i < player->num_effects; i++)
            {
                effect = player->effects[i];

                if(effect.effect_type == ARMOUR_BUFF)
                {
                    //my_printf("Applying %d pts armour buff to the player, remaining duration: %d\n.", effect.effect_value, effect.effect_duration - 1);
                    player->armour += effect.effect_value;
                }
                else if(effect.effect_type == MANA_REGEN)
                {
                    //my_printf("%d mana regenerated: remaining mana regeneration duration: %d\n.", effect.effect_value, effect.effect_duration - 1);
                    player->mana += effect.effect_value;
                }
                else if(effect.effect_type == DAMAGE)
                {
                    //my_printf("Player takes %d damage from damage debuff, remaining debuff duration:%d.\n", effect.effect_value, effect.effect_duration - 1);
                    player->hp -= effect.effect_value;
                }

                effect.effect_duration--;

                if(effect.effect_duration > 0 && num_effects_next_p < effects_next_size)
                {
                    effects_next_p[num_effects_next_p] = effect;
                    num_effects_next_p++;
                }
            }

            //my_printf("\n");

            //my_printf("Boss: %d hp\n", boss->hp);
            /* Applying effects to boss */
            for(int i = 0; i < boss->num_effects; i++)
            {
                effect = boss->effects[i];

                if(effect.effect_type == DAMAGE)
                {
                    //my_printf("Boss takes %d damage from debuff, remaining debuff duration:%d.\n", effect.effect_value, effect.effect_duration - 1);
                    boss->hp -= effect.effect_value;
                }

                effect.effect_duration--;

                if(effect.effect_duration > 0 && num_effects_next_b < effects_next_size)
                {
                    effects_next_b[num_effects_next_b] = effect;
                    num_effects_next_b++;
                }
            }

            if(boss->hp <= 0) break;

            //my_printf("\n");

            if(player_turn)
            {
                //my_printf("%s", "Your turn, choose skill: \n");
                for(int i = 0; i < 5; i++)
                {
                    can_use_skill = true;

                    if(skills[i].effect.effect_type != -1)
                    {
                        for(int j = 0; j < num_effects_next_b; j++)
                        {
                            if(effects_next_b[j].effect_type == skills[i].effect.effect_type) 
                            {
                                can_use_skill = false;
                            }
                        }
                        for(int j = 0; j < num_effects_next_p; j++)
                        {
                            if(effects_next_p[j].effect_type == skills[i].effect.effect_type)
                            {
                                can_use_skill = false;
                            }
                        }
                    }

                    if(skills[i].mana_cost > player->mana) can_use_skill = false;

                    if(can_use_skill)
                    {
                        available_skills[i] = 1;
                        // my_printf("%d. dmg: %d, heal: %d, mana cost: %d, effect: {type: %d, duration: %d, value:%d}\n", 
                        //     i + 1, 
                        //     skills[i].instant_dmg, 
                        //     skills[i].instant_heal, 
                        //     skills[i].mana_cost,
                        //     skills[i].effect.effect_type,
                        //     skills[i].effect.effect_duration,
                        //     skills[i].effect.effect_value);
                    }
                    else 
                    {
                        available_skills[i] = 0;
                    }
                }

                l_to_mana = true;

                for(int i = 0; i < 5; i++)
                {
                    if(available_skills[i] == 1) l_to_mana = false;
                }

                if(l_to_mana)
                {
                    //my_printf("No mana to use any skill, you lost.\n");
                    break;
                }

                //my_printf("\n");

                if(auto_play)
                {
                    /* we favour skills 3, 4, 5 */
                    if(available_skills[2] || available_skills[3] || available_skills[4])
                    {
                        choosen_skill = 2 + rand() % 3;
                        while(available_skills[choosen_skill] == 0)
                        {
                            choosen_skill = rand() % 5;
                        }

                    }
                    else
                    {
                        choosen_skill = rand() % 5;
                        while(available_skills[choosen_skill] == 0)
                        {
                            choosen_skill = rand() % 5;
                        }
                    }
                }
                else
                {
                    fgets(line_buff, LINE_BUFF_SIZE, stdin);
                }

                while(!auto_play)
                {
                    line_buff[strlen(line_buff) - 1] = 0;
                    choosen_skill = strtol(line_buff, NULL, 10);
                    choosen_skill--;

                    if(choosen_skill >= 0 && choosen_skill <= 5)
                    {
                        break;
                    }
                    else
                    {
                        //my_printf("You cannot use that skill.\n");
                        fgets(line_buff, LINE_BUFF_SIZE, stdin);
                    }
                }

                //my_printf("\n");

                player->mana -= skills[choosen_skill].mana_cost;
                total_mana_used += skills[choosen_skill].mana_cost;
                //my_printf("Using %d skill, -%d mana.\n", choosen_skill, skills[choosen_skill].mana_cost);

                if(skills[choosen_skill].instant_heal != -1)
                {
                    player->hp += skills[choosen_skill].instant_heal;
                    //my_printf("Player heals for %d hp and has now %d hp.\n", skills[choosen_skill].instant_heal, player->hp);
                }
                if(skills[choosen_skill].instant_dmg != -1)
                {
                    boss->hp -= skills[choosen_skill].instant_dmg;
                    //my_printf("Player hits boss for %d hp, boss has now %d hp left.\n", skills[choosen_skill].instant_dmg, boss->hp);
                }
                if(skills[choosen_skill].effect.effect_type != -1)
                {
                    if(skills[choosen_skill].effect.is_buff == 1)
                    {
                        //my_printf("Effect %d applied to the player.\n", skills[choosen_skill].effect.effect_type);
                        effects_next_p[num_effects_next_p] = skills[choosen_skill].effect;
                        num_effects_next_p++;
                    }
                    else
                    {
                        //my_printf("Effect %d applied to the boss.\n", skills[choosen_skill].effect.effect_type);
                        effects_next_b[num_effects_next_b] = skills[choosen_skill].effect;
                        num_effects_next_b++;
                    }
                }
            }
            else 
            {
                boss_dmg = 1;

                if((boss->dmg - player->armour) > 1)
                {
                    boss_dmg = boss->dmg - player->armour;
                }

                player->hp -= boss_dmg;
                //my_printf("Boss hits with %d, you have now %d hp.\n", boss_dmg, player->hp);
            }

            player_turn = !player_turn;
            round++;

            /* Cleanup effects to stats don't stack */
            for(int i = 0; i < player->num_effects; i++)
            {
                effect = player->effects[i];
                if(effect.effect_type == ARMOUR_BUFF)
                {
                    player->armour -= effect.effect_value;
                }
            }

            memcpy(player->effects, effects_next_p, num_effects_next_p * sizeof(Effect));
            player->num_effects = num_effects_next_p;
            num_effects_next_p = 0;

            memcpy(boss->effects, effects_next_b, num_effects_next_b * sizeof(Effect));
            boss->num_effects = num_effects_next_b;
            num_effects_next_b = 0;

            //my_printf("----------------------------------------\n");
        }

        // if(player->hp <= 0 || l_to_mana)
        // {
        //     my_printf("You lost and used %d mana.\n", total_mana_used);
        // }
        // else
        // {
        //     my_printf("You won and used %d mana.\n", total_mana_used);
        // }

        if(auto_play && player->hp > 0 && !l_to_mana && total_mana_used < min_mana_used)
        {
            min_mana_used = total_mana_used;
        }

        player->mana = 500;
        player->hp = 50;
        player->armour = 0;
        player->effects_size = 10;
        player->num_effects = 0;  

        boss->hp = BOSS_HP;
        boss->dmg = BOSS_DMG;
        boss->effects_size = 10;
        boss->num_effects = 0;
        num_effects_next_b = 0;
        num_effects_next_p = 0;

        player_turn = true;
        total_mana_used = 0;
        rounds_to_play--;
        round = 0;
        if(rounds_to_play < 0) break;
    } while(auto_play);
    
    free(player->effects);
    free(boss->effects);
    free(player);
    free(boss);
    free(effects_next_b);
    free(effects_next_p);

    return min_mana_used;
}

void initialize_player(Player* player)
{
    player->mana = 500;
    player->hp = 50;
    player->armour = 0;
    player->effects = malloc(10 * sizeof(Effect));
    player->effects_size = 10;
    player->num_effects = 0;
}

void initialize_boss(Boss* boss)
{
    boss->hp = BOSS_HP;
    boss->dmg = BOSS_DMG;
    boss->effects = malloc(10 * sizeof(Effect));
    boss->effects_size = 10;
    boss->num_effects = 0;
}

void my_printf(const char *format, ...) {
    if (!DAY22_PRINT_ENABLED) return;

    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}