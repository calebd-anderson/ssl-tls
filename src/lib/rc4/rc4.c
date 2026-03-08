#include <hex.h>

// Listing 2-46: rc4_operate
static void rc4_operate(const unsigned char *plaintext,
    int plaintext_len,
    unsigned char *ciphertext,
    const unsigned char *key,
    int key_len)
{
    int i, j;
    unsigned char S[256];
    unsigned char tmp;

    // KSA (key scheduling algorithm)
    for (i = 0; i < 256; i++)
    {
        S[i] = i;
    }

    j = 0;
    for (i = 0; i < 256; i++)
    {
        j = (j + S[i] + key[i % key_len]) % 256;
        tmp = S[i];
        S[i] = S[j];
        S[j] = tmp;
    }

    i = 0;
    j = 0;
    while (plaintext_len--)
    {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        tmp = S[i];
        S[i] = S[j];
        S[j] = tmp;
        *(ciphertext++) = S[(S[i] + S[j]) % 256] ^ *(plaintext++);
    }

    // Listing 2-47: main routine for testing
    #ifdef TEST_RC4
    int main(int argc, char *argv[]) {
        unsinged char *key;
        unsinged char *input;
        unsigned char *output;
        int key_len;
        int input_len;

        if (argc < 4)
        {
            fprintf(stderr, "Usage: %s [-e|-d] <key> <input>\n", argv[0]);
            exit(0);
        }

        key_len = hex_decode(argv[2], &key);
        input_len = hex_decode(argv[3], &input);

        output = malloc(input_len);
        rc4_operate(input, input_len, output, key, key_len);
        printf("Results: ");
        show_hex(output, input_len);

        free(key);
        free(input);

        return 0;
    }
    #endif
}