/*
    2016 BTCDDev, based on Code from Come-from-Beyond
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cCurl.h"
void setup_Curl(struct Curl *_c)
{
    _c->HASH_SIZE = 243;
    _c->STATE_SIZE = 3 * _c->HASH_SIZE;
    _c->T[0] = 1;
    _c->T[1] = 0;
    _c->T[2] = -1;
    _c->T[3] = 0;
    _c->T[4] = 1;
    _c->T[5] = -1;
    _c->T[6] = 0;
    _c->T[7] = 0;
    _c->T[8] = -1;
    _c->T[9] = 1;
    _c->T[10] = 0;
    int i;
    memset(_c->INDICES, 0, 730*sizeof(int));
    for (i = 0; i < _c->STATE_SIZE; i++) {
        _c->INDICES[i + 1] = _c->INDICES[i] + (_c->INDICES[i] < 365 ? 364 : -365);
    }
    for(i=0; i<729; i++){
        _c->state[i] = 0;
        _c->stateCopy[i] = 0;
    }
}

void transform(struct Curl *_c)
{
    int i, r, j;
    for (r = 27; r-- > 0;) {
        for(j=0; j<729; j++){
            _c->stateCopy[j] = _c->state[j];
        }
        for (i = 0; i < _c->STATE_SIZE;) {
            _c->state[i] = (_c->T[  _c->stateCopy[_c->INDICES[i]] +
                                    (_c->stateCopy[_c->INDICES[i+1]] << 2) +
                                    5 ]);
            i++;
        }
    }
}

void absorb(struct Curl *_c, int *input, int offset, int size)
{
    do {
        //            System.arraycopy(input, offset, state, 0, size < HASH_SIZE ? size : HASH_SIZE);
        memcpy(_c->state, input + offset, size < _c->HASH_SIZE ? size*sizeof(int) : _c->HASH_SIZE * sizeof(int));
        transform(_c);
        offset += _c->HASH_SIZE;
    } while ((size -= _c->HASH_SIZE) > 0);
}


void reset(struct Curl *_c)
{
    memset(_c->state, 0, _c->STATE_SIZE*sizeof(int));
}


void squeeze(struct Curl *_c, int *output, const int offset)
{
    memcpy(output+offset, _c->state, _c->HASH_SIZE*sizeof(int));
    transform(_c);
}

//Tests
/*
    To run:
    javac CurlReference.java
    uncomment from here on and run
*/
/*
int run_test(int);

int main()
{

    printf("Running Test on [-1]: %s %d\n", run_test(-1) ==0 ? "PASS": "FAIL", run_test(-1));
    printf("Running Test on [0]: %s %d\n", run_test (0)  ==0 ? "PASS": "FAIL", run_test(0));
    printf("Running Test on [1]: %s %d\n", run_test (1)  ==0 ? "PASS": "FAIL", run_test(1));

    return 0;
}


int run_test(int in)
{
    if (in !=0 && in!=-1 && in != 1){
        fprintf(stderr, "Invalid input\n");
        return -1;
    }
    int retVal = 1;
    struct Curl c;
    setup_Curl(&c);
    int input[243] ;
    int i, j;
    for(j=0; j<243; j++){
        input[j] = in;
    }
    int output[256];
    char final_output[512];
    memset(final_output, 0 , 512);
    for(j=0; j<256; j++){
        output[j] = 0;
    }
    absorb(&c, input, 0, 243);
    squeeze(&c, output, 0);

    char temp[16];
    strcpy(final_output, "[");
    for(i=0; i<c.HASH_SIZE-1; i++){
        sprintf(temp, "%d, ", output[i]);
        strcat(final_output, temp);
    }
    sprintf(temp, "%d]", output[c.HASH_SIZE-1]);
    strcat(final_output, temp);

    //Test
    FILE *fp;
    char ref[1024];
    memset(ref, 0, 1024);
    char sysCall[64];
    sprintf(sysCall, "java CurlReference %d", in);
    fp = popen(sysCall, "r");
    if(fp==NULL){
        fprintf(stderr, "Failed to run Reference Java Code\n");
        exit(1);
    }
    while(fgets(ref, sizeof(ref)-1, fp) != NULL)
        ;
    ref[strlen(ref)-1] = 0; //trailing \n from java
    pclose(fp);
    retVal = strcmp(final_output, ref);

    return retVal;
}
*/
