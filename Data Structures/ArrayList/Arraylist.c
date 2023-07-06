#include "../../testheaders.c"

int DEFAULT_ALIST_SIZE = 100;
typedef struct arraylist {
    void ** list;
    int length;
    int max_size;
} AList;

// manipulation methods
void AAdd(AList *, void *);
void ARemoveI(AList *, int);
void ARemove(const AList *, void *);

// query methods
void * AGet(const AList *, int);
void * APop(AList *);
void * APeek(const AList *);

// allocation methods
AList * AInit();
void AFree(const AList *);

// misc.
void APrint(const AList * list);

int main() {
    int i = 4;
    char * str = "I am the first string";
    char * str2 = "I am the second string";
    int * num = 24;

    AList * list = AInit();
    AAdd(list, str);
    AAdd(list, str2);
    AAdd(list, num);

    void * d = AGet(list, 0);
    void * e = AGet(list, 1);
    void * f = AGet(list, 2);

    printf("the value of stf is %s\n", (char *) d);
    printf("the value of stf2 is %s\n", (char *) e);
    printf("the value of num is %d\n", (int *) f);

    printf("the length of the list is %d\n", list->length);

    APrint(list);
    ARemove(list, str2);
    APrint(list);

    AFree(list);
    return 0;
}

/**
Adds the element to this list. If the addition of the given element
exceeds the maximum number of elements it's array can currently hold,
then more memory is allocated.
*/
void AAdd(AList * list, void * data) {
    int index = list->length;

    if (index == list->max_size) {
        // allocate more memory
        list->max_size *= 2;
        void ** new_list = (void **) malloc(sizeof(void *) * list->max_size);
        int i;
        for (i = 0; i < list->length; i++)
            new_list[i] = list->list[i];
        free(list->list);
        list->list = new_list;
    }

    list->list[index] = data;
    list->length++;
}

/**
Removes the element at the specified index.
*/
void ARemoveI(AList * list, int index) {
    int shift_num = list->length - (index + 1);

    while (shift_num) {
        list->list[index] = list->list[index + 1];
        shift_num--;
        index++;
    }

    list->length--;
}

/**
Removes the element specified, If it exists within the given list.
*/
void ARemove(const AList * list, void * data) {
    int l = list->length;
    int index = 0;
    while (l) {
        if (list->list[index] == data) {
            ARemoveI(list, index);
            break;
        }
        l--;
        index++;
    }
}

/**
Returns the element at the specified index.
*/
void * AGet(const AList * list, int index) {
    return list->list[index];
}

/**
Pops and returns the top element of this list, removing it from
the list.
*/
void * APop(AList * list) {
    list->length--;
    return list->list[list->length];
}

/**
Peeks at the top element of this list. This does not remove it
from the list.
*/
void * APeek(const AList * list) {
    return list->list[list->length - 1];
}

/**
Allocates a block of memory for an array list.
*/
AList * AInit() {
    AList * list = (AList *) malloc(sizeof(AList));
    list->list = (void **) malloc(sizeof(void *) * DEFAULT_ALIST_SIZE);
    list->length = 0;
    list->max_size = DEFAULT_ALIST_SIZE;
    return list;
}

/**
Frees the block of memory allocated by AInit. This does not include it's
elements.
*/
void AFree(const AList * list) {
    free(list->list);
    free(list);
}

/**
Prints the given array list.
*/
void APrint(const AList * list) {
    printf("[");
    int i;
    for (i = 0; i < list->length; i++) {
        if (i == list->length - 1)
            printf("%p", list->list[i]);
        else
            printf("%p, ", list->list[i]);
    }
    printf("]\n");
}




