#include <stdio.h>
#include <time.h>
#include <stdlib.h> 
#include <math.h>
#include <string.h>
#include "cCurl.h"

int main(int argc, char *argv[])
{
	int numHashes = 1;
	if(argc > 1 && atoi(argv[1]) != 0)
		numHashes = strtod(argv[1], NULL);

	struct Curl c;
    setup_Curl(&c);
    int input[243], output[256];
    memset(output, 0, 256*sizeof(int));
    int i, j;
    for(j=0; j<243; j++){
        input[j] = j%2==0 ? -1 : (j%3==0 ? 0 : 1); //some input
    }

	struct timespec start, end;

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start); // get initial time-stamp

    for(i=0; i<numHashes; i++){
    	absorb(&c, input, 0, 243);
    	squeeze(&c, output, 0);
    }

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);   // get final time-stamp

	double t_ns = (double)(end.tv_sec - start.tv_sec) * 1.0e9 +
              	  (double)(end.tv_nsec - start.tv_nsec);
                                                 // subtract time-stamps and
                                                 // multiply to get elapsed
                                                 // time in ns

    printf("\n\n Completed <%d> Hashes in (%f) seconds => %f H/s\n", numHashes, (t_ns/(1000*1000*1000)), (double)numHashes / (t_ns/(1000*1000*1000)));


	return 0;
}