#include "../../testheaders.c"

typedef struct node {
    void * data;
    struct node * next;
} LNode;

typedef struct linkedlist {
    LNode * head;
    int length;
} LList;

// manipulation methods
void LAdd(LList *, void *);
void LRemoveI(LList *, int);
void LRemove(LList *, void *);

// query methods
void * LGet(LList *, int);
void * LPop(LList *);
void * LPeek(LList *);

// allocation methods
LList * LInit();
void LFree(LList *);

// misc
void LPrint(LList *);

int main() {
    LList * l = LInit();
    int i = 4;
    int a = 3;
    int b = 2;
    int c = 1;
    LAdd(l, i);
    LAdd(l, a);
    LAdd(l, b);
    LAdd(l, c);
    LPrint(l);
    LRemoveI(l, 1);
    LPrint(l);
    LFree(l);
    return 0;
}

/**
Adds the given element to this list. If the list is currently
empty, the head is newly allocated.
*/
void LAdd(LList * list, void * data) {
    LNode * node = malloc(sizeof(LNode));
    node->data = data;
    node->next = NULL;

    LNode * next = NULL;
    if (!list->head) {
        list->head = node;
    } else {
        next = list->head;
        while (next) {
            if (!next->next) {
                next->next = node;
                break;
            }
            next = next->next;
        }
    }
    list->length++;
}

/**
Removes the element at the specified index. this also deallocates
the node associated with it.
*/
void LRemoveI(LList * list, int index) {
    if (list->length == 1) {
        free(list->head);
        list->head = NULL;
        list->length--;
        return;
    }

    LNode * prev = NULL;
    LNode * cur = list->head;
    int c = 0;
    while (cur) {
        if (c == index) {
            prev->next = cur->next;
            free(cur);
            list->length--;
            break;
        }
        prev = cur;
        cur = cur->next;
        c++;
    }
}

/**
Removes the given element, if found, from this list. this also
deallocates the node associated with it.
*/
void LRemove(LList * list, void * data) {
    LNode * next = list->head;
    int index = 0;
    while (next) {
        if (next->data == data) {
            LRemoveI(list, index);
            break;
        }
        next = next->next;
    }
}

void * LGet(LList * list, int index) {
    return NULL;
}

void * LPop(LList * list) {
    return NULL;
}

void * LPeek(LList * list) {
    return NULL;
}

/**
Allocates a block of memory for a linked list.
*/
LList * LInit() {
    LList * re = malloc(sizeof(LList));
    re->head = NULL;
    re->length = 0;
}

/**
Frees the memory allocated by LInit() and LAdd()'s nodes.
This does not include it's elements.
*/
void LFree(LList * list) {
    LNode * next = list->head;
    LNode * temp;
    while (next) {
        temp = next;
        next = next->next;
        free(temp);
    }
    free(list);
}

/**
Prints this linked list.
*/
void LPrint(LList * list) {
    printf("list length: %d\n[", list->length);
    LNode * next = list->head;
    while (next) {
        if (!next->next)
            printf("%p", next->data);
        else
            printf("%p, ", next->data);
        next = next->next;
    }
    printf("]\n");
}


