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

// static void des_operate(const unsigned char *input,
//                         int input_len,
//                         unsigned char *output,
//                         const unsigned char *iv,
//                         const unsigned char *key,
//                         op_type operation);

void des_dectypt(const unsigned char *ciphertext,
                 const int ciphertext_len,
                 unsigned char *plaintext,
                 const unsigned char *iv,
                 const unsigned char *key);

void des_encrypt(const unsigned char *plaintext,
                 const int plaintext_len,
                 unsigned char *ciphertext,
                 const unsigned char *iv,
                 const unsigned char *key);

#endif
