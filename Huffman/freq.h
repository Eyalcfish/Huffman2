#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct ching {
    char val;
    int freq;
} typedef ching;

int cmp(ching *a ,ching *b) {
    if(a->freq > b->freq) {
        return -1;
    }
    if(a->freq < b->freq) {
        return 1;
    }
    return 0;
}

ching *getFreqs(char* original) {
    slot* map = createHashmap();
    int length = (int)strlen(original);
    for(int i = 0 ; i < length ; i++) {
        if(findChar(original[i],map) == -1) {
            int *val = malloc(4);
            val[0] = 1;
            map = insertChar(map,original[i],val);
        }
        else {
            int* point = (int*)getChar(original[i],map);
            (*point)++;
        }
    }
    length = (*(int*)map[0].value);
    ching *ret = (ching*)calloc(length+1,sizeof(ching));
    for(int i = 1 ; i < length ; i++) {
        ret[i-1].freq = *(int*)map[i].value;
        ret[i-1].val = (char)map[i].key;
        free(map[i].value);
    }
    free(map);
    qsort(ret, length-1, sizeof(ching), (int (*)(const void *, const void *)) cmp);
    ret[length].freq = -1;
    ret[length].val = -1;
    return ret;
}

void printArrFreq(ching *l) {
    int i = 0;
    while(l[i].val != 0) {
        printf("Char: %c, Freq: %d\n", l[i].val,l[i].freq);
        i++;
    }
}