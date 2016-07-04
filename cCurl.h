/*
    2016 BTCDDev, based on Code from Come-from-Beyond
*/
#ifndef _C_CURL_H_
#define _C_CURL_H_

struct Curl {
    int HASH_SIZE;
    int STATE_SIZE;
    int T[11]; // {1, 0, -1, 1, -1, 0, -1, 1, 0};
    int INDICES[729 + 1];
    int state[729];
    int stateCopy[729];
};

void setup_Curl(struct Curl *_c);
void absorb(struct Curl *_c, int *input, int offset, int size);
void reset(struct Curl *_c);
void squeeze(struct Curl *_c, int *output, const int offset);
void transform(struct Curl *_c);

#endif
