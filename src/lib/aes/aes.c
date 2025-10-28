#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <hex.h>

static void rot_word(unsigned char *w) {
    unsigned char tmp;

    tmp = w[0];
    w[0] = w[1];
    w[1] = w[2];
    w[2] = w[3];
    w[3] = tmp;
}
