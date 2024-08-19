#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashmap.h"
#include "intlist.h"
#include "freq.h"

int main() {
    ching* freqs = getFreqs("go go gopasdjkasn dkjashdiuagsdiyga puyhav sudpvupa augpsdvupg vaugpsdv ugpvaspugdv upga sdpjgvapsjgd hers");
    printArrFreq(freqs);
    free(freqs);
    return 0;
}
