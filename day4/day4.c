#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define A 0x67452301
#define B 0xefcdab89
#define C 0x98badcfe
#define D 0x10325476

#define F(X, Y, Z) ((X & Y) | (~X & Z))
#define G(X, Y, Z) ((X & Z) | (Y & ~Z))
#define H(X, Y, Z) (X ^ Y ^ Z)
#define I(X, Y, Z) (Y ^ (X | ~Z))

#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

#define FF(a, b, c, d, x, s, i) { \
    (a) += F((b), (c), (d)) + (x) + (i); \
    (a) = ROTATE_LEFT((a), (s)); \
    (a) += (b); \
}

#define GG(a, b, c, d, x, s, i) { \
    (a) += G((b), (c), (d)) + (x) + (i); \
    (a) = ROTATE_LEFT((a), (s)); \
    (a) += (b); \
}

#define HH(a, b, c, d, x, s, i) { \
    (a) += H((b), (c), (d)) + (x) + (i); \
    (a) = ROTATE_LEFT((a), (s)); \
    (a) += (b); \
}

#define II(a, b, c, d, x, s, i) { \
    (a) += I((b), (c), (d)) + (x) + (i); \
    (a) = ROTATE_LEFT((a), (s)); \
    (a) += (b); \
}

#define DAY4_INPUT "bgvyzdsv"

void md5(const char* original_message, unsigned char* output_buffer);
int day4_solution(const char* input, bool pt2);
int day4_pt1();
int day4_pt2();

int day4_pt1()
{
    return day4_solution(DAY4_INPUT, false);
}

int day4_pt2()
{
    return day4_solution(DAY4_INPUT, true);
}

int day4_solution(const char* input, bool pt2)
{
    int i = 0, j = 0, tmp = 0, digits_written = 0, number_buffer_size = 20, input_len = strlen(input);
    char* buffer = malloc(input_len + number_buffer_size);
    strcpy(buffer, input);
    char* number_buffer = malloc(number_buffer_size);
    unsigned char* md5_buffer = malloc(17);

    while(true)
    {
        tmp = i;

        do
        {
            number_buffer[digits_written] = (tmp % 10) + '0';
            tmp /= 10;
            digits_written++;
        } while(tmp != 0);

        while(digits_written > 0)
        {
            buffer[input_len + j] = number_buffer[digits_written - 1];
            j++;
            digits_written--;
        }

        md5(buffer, md5_buffer);
        if(md5_buffer[0] == 0 && md5_buffer[1] == 0 && ((!pt2 && md5_buffer[2] < 10) || (pt2 && md5_buffer[2] == 0))) break;

        j = 0;
        i++;
    }

    free(buffer);
    free(number_buffer);
    free(md5_buffer);

    return i;
}

void md5(const char* original_message, unsigned char* output_buffer)
{
    long message_length = strlen(original_message);
    int bits_to_512 = (message_length * sizeof(char) * 8) % 512;
    int num_blocks = (message_length * sizeof(char) * 8) / 512;

    if (bits_to_512 < 448)
    {
        num_blocks += 1;
    }
    else {
        num_blocks += 2;
    }

    int buffer_size = num_blocks * (512 / (sizeof(char) * 8));
    unsigned char* buffer = malloc(buffer_size);
    memset(buffer + message_length, 0, buffer_size - message_length);
    strcpy(buffer, original_message);
    buffer[message_length] = 0x80;
    uint64_t bit_length = (uint64_t)message_length * 8;
    memcpy(buffer + buffer_size - 8, &bit_length, 8);

    uint32_t a = A, b = B, c = C, d = D;
    uint32_t AA = A, BB = B, CC = C, DD = D;
    uint32_t X[15] = {0};


    for (int i = 0; i < num_blocks; i++)
    {   
        for (int j = 0; j < 64; j += 4)
        {
            X[(j / 4)] = 
            (uint32_t) buffer[i * 16 + j]
            | (uint32_t) buffer[i * 16 + j + 1] << 8
            | (uint32_t) buffer[i * 16 + j + 2] << 16
            | (uint32_t) buffer[i * 16 + j + 3] << 24;
        }

        AA = a;
        BB = b;
        CC = c;
        DD = d;   
        
        FF (a, b, c, d, X[ 0], S11, 0xd76aa478); /* 1 */
        FF (d, a, b, c, X[ 1], S12, 0xe8c7b756); /* 2 */
        FF (c, d, a, b, X[ 2], S13, 0x242070db); /* 3 */
        FF (b, c, d, a, X[ 3], S14, 0xc1bdceee); /* 4 */
        FF (a, b, c, d, X[ 4], S11, 0xf57c0faf); /* 5 */
        FF (d, a, b, c, X[ 5], S12, 0x4787c62a); /* 6 */
        FF (c, d, a, b, X[ 6], S13, 0xa8304613); /* 7 */
        FF (b, c, d, a, X[ 7], S14, 0xfd469501); /* 8 */
        FF (a, b, c, d, X[ 8], S11, 0x698098d8); /* 9 */
        FF (d, a, b, c, X[ 9], S12, 0x8b44f7af); /* 10 */
        FF (c, d, a, b, X[10], S13, 0xffff5bb1); /* 11 */
        FF (b, c, d, a, X[11], S14, 0x895cd7be); /* 12 */
        FF (a, b, c, d, X[12], S11, 0x6b901122); /* 13 */
        FF (d, a, b, c, X[13], S12, 0xfd987193); /* 14 */
        FF (c, d, a, b, X[14], S13, 0xa679438e); /* 15 */
        FF (b, c, d, a, X[15], S14, 0x49b40821); /* 16 */

        /* Round 2 */
        GG (a, b, c, d, X[ 1], S21, 0xf61e2562); /* 17 */
        GG (d, a, b, c, X[ 6], S22, 0xc040b340); /* 18 */
        GG (c, d, a, b, X[11], S23, 0x265e5a51); /* 19 */
        GG (b, c, d, a, X[ 0], S24, 0xe9b6c7aa); /* 20 */
        GG (a, b, c, d, X[ 5], S21, 0xd62f105d); /* 21 */
        GG (d, a, b, c, X[10], S22,  0x2441453); /* 22 */
        GG (c, d, a, b, X[15], S23, 0xd8a1e681); /* 23 */
        GG (b, c, d, a, X[ 4], S24, 0xe7d3fbc8); /* 24 */
        GG (a, b, c, d, X[ 9], S21, 0x21e1cde6); /* 25 */
        GG (d, a, b, c, X[14], S22, 0xc33707d6); /* 26 */
        GG (c, d, a, b, X[ 3], S23, 0xf4d50d87); /* 27 */
        GG (b, c, d, a, X[ 8], S24, 0x455a14ed); /* 28 */
        GG (a, b, c, d, X[13], S21, 0xa9e3e905); /* 29 */
        GG (d, a, b, c, X[ 2], S22, 0xfcefa3f8); /* 30 */
        GG (c, d, a, b, X[ 7], S23, 0x676f02d9); /* 31 */
        GG (b, c, d, a, X[12], S24, 0x8d2a4c8a); /* 32 */

        /* Round 3 */
        HH (a, b, c, d, X[ 5], S31, 0xfffa3942); /* 33 */
        HH (d, a, b, c, X[ 8], S32, 0x8771f681); /* 34 */
        HH (c, d, a, b, X[11], S33, 0x6d9d6122); /* 35 */
        HH (b, c, d, a, X[14], S34, 0xfde5380c); /* 36 */
        HH (a, b, c, d, X[ 1], S31, 0xa4beea44); /* 37 */
        HH (d, a, b, c, X[ 4], S32, 0x4bdecfa9); /* 38 */
        HH (c, d, a, b, X[ 7], S33, 0xf6bb4b60); /* 39 */
        HH (b, c, d, a, X[10], S34, 0xbebfbc70); /* 40 */
        HH (a, b, c, d, X[13], S31, 0x289b7ec6); /* 41 */
        HH (d, a, b, c, X[ 0], S32, 0xeaa127fa); /* 42 */
        HH (c, d, a, b, X[ 3], S33, 0xd4ef3085); /* 43 */
        HH (b, c, d, a, X[ 6], S34,  0x4881d05); /* 44 */
        HH (a, b, c, d, X[ 9], S31, 0xd9d4d039); /* 45 */
        HH (d, a, b, c, X[12], S32, 0xe6db99e5); /* 46 */
        HH (c, d, a, b, X[15], S33, 0x1fa27cf8); /* 47 */
        HH (b, c, d, a, X[ 2], S34, 0xc4ac5665); /* 48 */

        /* Round 4 */
        II (a, b, c, d, X[ 0], S41, 0xf4292244); /* 49 */
        II (d, a, b, c, X[ 7], S42, 0x432aff97); /* 50 */
        II (c, d, a, b, X[14], S43, 0xab9423a7); /* 51 */
        II (b, c, d, a, X[ 5], S44, 0xfc93a039); /* 52 */
        II (a, b, c, d, X[12], S41, 0x655b59c3); /* 53 */
        II (d, a, b, c, X[ 3], S42, 0x8f0ccc92); /* 54 */
        II (c, d, a, b, X[10], S43, 0xffeff47d); /* 55 */
        II (b, c, d, a, X[ 1], S44, 0x85845dd1); /* 56 */
        II (a, b, c, d, X[ 8], S41, 0x6fa87e4f); /* 57 */
        II (d, a, b, c, X[15], S42, 0xfe2ce6e0); /* 58 */
        II (c, d, a, b, X[ 6], S43, 0xa3014314); /* 59 */
        II (b, c, d, a, X[13], S44, 0x4e0811a1); /* 60 */
        II (a, b, c, d, X[ 4], S41, 0xf7537e82); /* 61 */
        II (d, a, b, c, X[11], S42, 0xbd3af235); /* 62 */
        II (c, d, a, b, X[ 2], S43, 0x2ad7d2bb); /* 63 */
        II (b, c, d, a, X[ 9], S44, 0xeb86d391); /* 64 */

        a += AA;
        b += BB;
        c += CC;
        d += DD;
    }

    output_buffer[0] = (unsigned char) (a & 0xff);
    output_buffer[1] = (unsigned char) ((a >> 8) & 0xff);
    output_buffer[2] = (unsigned char) ((a >> 16) & 0xff);
    output_buffer[3] = (unsigned char) ((a >> 24) & 0xff);
    output_buffer[4] = (unsigned char) (b & 0xff);
    output_buffer[5] = (unsigned char) ((b >> 8) & 0xff);
    output_buffer[6] = (unsigned char) ((b >> 16) & 0xff);
    output_buffer[7] = (unsigned char) ((b >> 24) & 0xff);
    output_buffer[8] = (unsigned char) (c & 0xff);
    output_buffer[9] = (unsigned char) ((c >> 8) & 0xff);
    output_buffer[10] = (unsigned char) ((c >> 16) & 0xff);
    output_buffer[11] = (unsigned char) ((c >> 24) & 0xff);
    output_buffer[12] = (unsigned char) (d & 0xff);
    output_buffer[13] = (unsigned char) ((d >> 8) & 0xff);
    output_buffer[14] = (unsigned char) ((d >> 16) & 0xff);
    output_buffer[15] = (unsigned char) ((d >> 24) & 0xff);
    output_buffer[16] = 0;

    free(buffer);
}