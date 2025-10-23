#ifndef DES_H
#define DES_H

void xor(unsigned char *target, const unsigned char *src, int len);

void permute(unsigned char target[],
                    const unsigned char src[],
                    const int permute_table[],
                    int len);

void rol( unsigned char *target );

void ror(unsigned char *target);

// void des_block_operate(const unsigned char plaintext[],
//                               unsigned char ciphertext[],
//                               const unsigned char key[],
//                               op_type operation);

#endif
