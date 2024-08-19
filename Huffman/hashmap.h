#include <stdio.h>
#include <math.h>
#include <malloc.h>

struct slot {
    long key;
    void *value;
} typedef slot;

long turnToInt(char *key) {
    long ret = 1;
    int i = 0 ;
    int cur = 0;
    while(key[i] !='\0') {
        cur += key[i];
        if (key[i] > 65) {
            cur -= 65;
        }
        if (key[i++] > 90) cur -= 32;
        ret *= cur;
    }
    return ret;
}

slot *sort(slot *bucketVar,int from,int to) {
    slot fromslot;
    slot toslot;
    toslot = bucketVar[to];
    fromslot = bucketVar[from];
    bucketVar[to] = fromslot;
    bucketVar[from] = toslot;
    return bucketVar;
}

int find(char *key,slot *bucket) {
    long n = *(long*)bucket[0].value;
    int i = 0;
    int ret = turnToInt(key);
    int next = 2;
    while(1) {
        if(ret > bucket[i].key) {
            i += (n-i)/2;
            next = next*2;
        }
        else if (ret < bucket[i].key) {
            i -= n/next;
            next = next*2;
        }
        if( next > 100000) {return -1;}
        if(bucket[i].key == ret || i >= n || i <= 0) {
            return i;
        }
    }
}

int findChar(int ret,slot *bucket) {
    long n = *(long*)bucket[0].value;
    int i = 0;
    int next = 2;
    while(1) {
        if(ret > bucket[i].key) {
            int f = i;
            i += (n/next);
            next = next*2;
            if (f == i) {
                i++;
            }
        }
        else if (ret < bucket[i].key) {
            int f = i;
            i -= (n/next);
            next = next*2;
            if (f == i) {
                i--;
            }
        }
        if(i >= *(int*)bucket[0].value || next > 1000000) {return -1;}
        if(bucket[i].key == ret || i >= n || i < 0) {
            return i;
        }
    }
}

slot *insertChar(slot *bucketRet,long key,void *val) {
    long n = *(long*)bucketRet[0].value;
    slot *tempBucket = (slot*) realloc(bucketRet,sizeof(slot)*(n+1));
    if(tempBucket == NULL) {
        printf("ERROR NO GOOD");
        free(bucketRet);
        return NULL;
    }
    bucketRet =tempBucket;
    for(int i = 1 ; i < n+1 ; i++) {
        if(bucketRet[i].key == key) {
            bucketRet[i].value = val;
            return bucketRet;
        }
    }
    (*(long*)bucketRet[0].value) = n+1;
    bucketRet[n].key = key;
    bucketRet[n].value = val;
    for(int i = n-1,last = n,f = 0 ; f < n-1 ; i = i-1,f++) {
        if(key >= bucketRet[i].key) {
            return bucketRet;
        }
        else {
            bucketRet = sort(bucketRet,i,last);
            last = i;
        }
    }
    return bucketRet;
}

slot *insert(slot *bucketRet,char *ins,void *val) {
    long n = *(long*)bucketRet[0].value;
    slot *tempBucket = (slot*) realloc(bucketRet,sizeof(slot)*(n+1));
    if(tempBucket == NULL) {
        printf("ERROR NO GOOD");
        free(bucketRet);
        return NULL;
    }
    bucketRet =tempBucket;
    int key = turnToInt(ins);
    for(int i = 1 ; i < n+1 ; i++) {
        if(bucketRet[i].key == key) {
            bucketRet[i].value = val;
            return bucketRet;
        }
    }
    (*(long*)bucketRet[0].value) = n+1;
    bucketRet[n].key = key;
    bucketRet[n].value = val;
    for(int i = n-1,last = n,f = 0 ; f < n-1 ; i = i-1,f++) {
        if(key > bucketRet[i].key) {
            return bucketRet;

        }
        else {
            bucketRet = sort(bucketRet,i,last);
            last = i;
        }
    }
    return bucketRet;
}

void *get(char *key,slot *bucket) {
    int place = find(key,bucket);
    if(place == -1) return NULL;
    return bucket[place].value;
}

void *getChar(int key,slot *bucket) {
    int place = findChar(key,bucket);
    if(place == -1) return NULL;
    return bucket[place].value;
}

slot *createHashmap() {
    slot *bucket = (slot*)malloc(sizeof(slot));
    long *val = (long*)malloc(sizeof(long));
    *val = 1;
    bucket[0].value = val;
    bucket[0].key = -2;
    return bucket;
}