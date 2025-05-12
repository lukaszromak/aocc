#include <stdint.h>
#include <stdbool.h>

typedef struct uint256
{
    __uint128_t high;
    __uint128_t low;
} uint256;

void increment(uint256* number);
void half(uint256* number);
void multiply(uint256* multiplicand, int multiplier);
uint256 add(uint256 op1, uint256 op2);
void print_uint256(uint256 number);
bool is_odd(uint256 number);
bool is_one(uint256 number);

void increment(uint256* number)
{
    uint256 one = { 0, 1 };
    *number = add(*number, one);
};

void half(uint256* number)
{
    number->low = number->low >> 1;
    
    if(number->high & 1) number->low |= ((__uint128_t)1 << 127);

    number->high = number->high >> 1;
}

void multiply(uint256* multiplicand, int multiplier)
{
    uint256 result = {0, 0};
    __uint128_t mult = (__uint128_t)multiplier;

    uint64_t lo_lo = (uint64_t)(multiplicand->low);
    uint64_t lo_hi = (uint64_t)(multiplicand->low >> 64);

    __uint128_t part1 = (__uint128_t)lo_lo * mult;
    __uint128_t part2 = (__uint128_t)lo_hi * mult;

    __uint128_t low_result = part1 + (part2 << 64);

    __uint128_t carry = (part2 >> 64) + (low_result < part1);

    // High part is high × multiplier + carry
    __uint128_t high_result = multiplicand->high * mult + carry;

    multiplicand->low = low_result;
    multiplicand->high = high_result;
}


uint256 add(uint256 op1, uint256 op2)
{
    uint256 res = { 0, 0 };

    __uint128_t low_sum = op1.low + op2.low;
    __uint128_t carry = (res.low > op1.low);

    res.low = low_sum;
    res.high = op1.high + op2.high + carry;

    return res;
}

void print_uint256(uint256 number)
{
    printf("%llx %llx\n", (unsigned long long)(number.high & 0xFFFFFFFFFFFFFFFF), (unsigned long long)(number.low & 0xFFFFFFFFFFFFFFFF));
}

bool is_odd(uint256 number)
{
    return number.low & 1;
}

bool is_one(uint256 number)
{
    return number.high == 0 && number.low == 1;
}