#include <stdio.h>
#include <malloc.h>

struct intList {
    unsigned char *array;
    int length;
    int bytes;
} typedef ints;

ints *intsAdd(ints* list,char a) {
    list->array = (char*) realloc(list->array,sizeof(char)*(list->length+1));
    list->array[list->length] = a;
    list->length++;
    list->bytes = list->length*4;
    return list;
}

ints *orginizeList(ints* list) {
    for(int i = 1 ; i < list->length ; i++) {
        if(list->array[i-1] == -1) {
            list->array[i-1] = list->array[i];
            list->array[i] = -1;
        }
    }
    list->length--;
    return list;
}

ints *removeNode(ints *list,int p) {
    list->array[p] = -1;
    list = orginizeList(list);
    return list;
}

ints *removeNodeNS(ints *list,int p) {
    list->array[p] = -1;
    return list;
}

ints *intsMake() {
    ints *ret = (ints*)malloc(sizeof(ints));
    ret->array = (int*)malloc(sizeof(int));
    ret->length = 0;
    ret->bytes = 4;
    return ret;
}

void printList(ints* list) {
    printf("-----------------\n");
    for(int i = 0 ; i < list->length ; i++) {
        printf("%d\n",list->array[i]);
    }
    printf("-----------------\n");
}
