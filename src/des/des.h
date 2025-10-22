#ifndef DES_H
#define DES_H

void permute(unsigned char target[],
                    const unsigned char src[],
                    const int permute_table[],
                    int len);
void ro1( unsigned char *target );

#endif
