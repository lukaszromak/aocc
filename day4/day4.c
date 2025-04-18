#include <stdio.h>

char* md5(const char* original_message);

#define A 0x01234567
#define B 0x89abcdef
#define C 0xfedcba98
#define D 0x76543210

#define F(X, Y, Z) ((X & Y) | (~X & Z))
#define G(X, Y, Z) ((X & Z) | (Y & ~Z))
#define H(X, Y, Z) (X ^ Y ^ Z)
#define I(X, Y, Z) (Y ^ (X | ~Z))

int main()
{
    const char* input = "bgvyzdsv";

    char* digest = md5(input);

    return 0;
}

char* md5(const char* original_message)
{
    int state[] = { A, B, C, D };
    int temp_state[] = { A, B, C, D };
    int X[15] = {0};
    char* buffer;
    int message_length = strlen(original_message);
    int buffer_size = 0;
    int bits_to_512 = 0;
    int num_blocks = 0;

    bits_to_512 = (message_length * sizeof(char) * 8) % 512;
    num_blocks = (message_length * sizeof(char) * 8) / 512;

    if (bits_to_512 < 448)
    {
        num_blocks += 1;
    }
    else {
        num_blocks += 2;
    }

    buffer_size = num_blocks * (512 / (sizeof(char) * 8)) + 1;
    buffer = malloc(buffer_size);
    memset(buffer + message_length, 0, buffer_size - message_length);
    strcpy(buffer, original_message);
    buffer[message_length] = 0x80;
    buffer[buffer_size - 2] = message_length;

    for (int i = 0; i < buffer_size; i++)
    {
        printf("%c", buffer[i]);
    }

    for (int i = 0; i < num_blocks; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            X[j] = (buffer[i * 15 + j] << 24) | (buffer[i * 15 + j + 1] << 16) | (buffer[i *  15 + j + 2] << 8) | buffer[i * 15 + j + 3];
        }

        temp_state[0] = state[0];
        temp_state[1] = state[1];
        temp_state[2] = state[2];
        temp_state[3] = state[3];
    }

    free(buffer);
}