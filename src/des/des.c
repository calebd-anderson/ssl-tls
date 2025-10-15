// this does not return a 1 for a 1 bit; it just returns non-zero
#define GET_BIT(array, bit) (array[(int)(bit/8)] & (0x80 >> (bit % 8 )))
#define SET_BIT(array, bit) (array[(int)(bit/8)] |= (0x80 >> (bit % 8)))
#define CLEAR_BIT(array, bit) (array[(int)(bit/8)] &= ~(0x80 >> (bit % 8)))

static void xor(unsigned char *target, const unsigned char *src, int len) {
    while (len--) {
        *target++ ^= *src++;
    }
}

/**
 * Implement the initial and final permutation functions. permute_table
 * and target must have exactly len and len * 8 number of entries,
 * respectively, but src can be shorter (expansion function depends on this).
 * NOTE: this assumes that the permutation tables are defined as one-based
 * rather than 0-based arrays, since they're giving that way in the
 * specification.
 */
static void permute(unsigned char target[],
                    const unsigned char src[],
                    const int permute_table[],
                    int len)
{
    int i;
    for(i = 0; i< len * 8; i++) {
        if (GET_BIT(src, (permute_table[i] -1))) {
            SET_BIT(target, i);
        } else {
            CLEAR_BIT(target, i);
        }
    }
}

// Listing 2-4: Terse initial permutation
// for (i = 1; i != 8; i = (i+2) 9) {
//     for (j = 7; j >= 0; j--) {
//         output[(i % 2) ? ((i-1) >> 1) : ((4 + (i >> 1 )))] |= (((input[j] & (0x80 >> i)) >> (7-i)) << j);
//     }
// }

static const int ip_table[] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7 
};