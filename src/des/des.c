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

// initial permutation
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

/**
 * This just inverts ip_table.
 */
static const int fp_table[] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    15, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 31, 9, 39, 17, 57, 25 };

static const int pc1_table[] = { 57, 49, 41, 33, 25, 17, 9, 1,
                                 58, 50, 42, 34, 26, 18, 10, 2,
                                 59, 51, 43, 35, 27, 19, 11, 3,
                                 60, 52, 44, 36,
                                 63, 55, 47, 39, 31, 23, 15, 7,
                                 62, 54, 46, 38, 30, 22, 14, 6,
                                 61, 53, 45, 37, 29, 21, 13, 5,
                                 28, 20, 12,  4 };

static const int pc2_table[] = { 14, 17, 11, 24,  1,  5,
                                  3, 28, 15,  6, 21, 10,
                                 23, 19, 12,  4, 26,  8,
                                 16,  7, 27, 20, 13,  2,
                                 41, 52, 31, 37, 47, 55,
                                 30, 40, 51, 45, 33, 48,
                                 44, 49, 39, 56, 34, 53,
                                 46, 42, 50, 36, 29, 32 };

// Listing 2-9: rotate left
/**
 * Perform the left rotation operation on the key. This is made fairly
 * complex by the fact that the key is split into two 28-bit halves, each
 * of which has to be rotated independently (so the second rotation operation
 * starts in the middle of byte 3).
 */
static void ro1( unsigned char *target )
{
    int carry_left, carry_right;

    carry_left = ( target[ 0 ] & 0x80 ) >> 3;

    target[0] = ( target[0] << 1 ) | ( ( target[1] & 0x80 ) >> 7 );
    target[1] = ( target[1] << 1 ) | ( ( target[2] & 0x80 ) >> 7 );
    target[2] = ( target[2] << 1 ) | ( ( target[3] & 0x80 ) >> 7 );

    // special handling for byte 3
    carry_right = ( target[ 3 ] & 0x08 ) >> 3;
    target[ 3 ] = ( ( ( target[ 3 ] << 1 ) |
    (( target[ 4 ] & 0x80 ) >> 7 ) ) & ~0x10 ) | carry_left;

    target[ 4 ] = ( target[ 4 ] << 1 ) | ((target[5] & 0x80) >> 7 );
    target[5] = (target[5] << 1) | ((target[6] & 0x80) >> 7);
    target[6] = (target[6] << 1) | carry_right;
}
