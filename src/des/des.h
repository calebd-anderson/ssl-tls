#ifndef DES_H
#define DES_H

void xor(unsigned char *target, const unsigned char *src, int len);

void permute(unsigned char target[],
                    const unsigned char src[],
                    const int permute_table[],
                    int len);

void ro1( unsigned char *target );

#endif
