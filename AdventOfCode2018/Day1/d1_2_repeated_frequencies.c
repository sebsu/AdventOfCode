#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *next;
} node;

/* Leaving this here for fun. Changed to atoi(). */
/* #include <string.h> */
/* int stoi(char* str) { */
/*     /\* Find a better way than strlen(). *\/ */
/*     size_t len = strlen(str)-1; */
/*     int sign = (str[0]=='+') ? 1 : -1; */
/*     int out = 0; */
/*     for (int i = 1; i < len; ++i) { */
/*         out = out*10 + str[i] - 48; */
/*     } */
/*     return sign*out; */
/* } */

int insert(node* root, int val) {
    node* prev = NULL;
    node* curr = root;
    while (curr->next != NULL &&
           curr->data < val &&
           curr->data != val) {
        prev = curr;
        curr = curr->next;
    }
    if (val == curr->data) {
        return 1;
    }
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = val;
    if (val < curr->data) {
        if (prev != NULL) {
            prev->next = new_node;
        } else {
            root = new_node;
        }
        new_node->next = curr;
    } else {
        new_node->next = curr->next;
        curr->next = new_node;
    }
    return 0;
}

void print_list(node* root) {
    printf("\nList: ");
    node* curr = root;
    while(curr != NULL) {
        printf("%i ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

int main(int argc, char** argv){
    assert(argc>1);

    FILE* f;
    int size = 32;    /* Could be smaller. */
    char num[size];
    int freq = 0;

    node root;        /* Is this correct? */
    root.data = freq;
    root.next = NULL;
    
    int found = 0;
    while (!found) {
        /* Could save all locally, but wanna be dynamic. */
        f = fopen(argv[1], "r");
        while (fgets(num, size, f) != NULL) {
            freq += atoi(num);
            if (insert(&root, freq)) {
                printf("\nFOUND!\n");
                found = 1;
                break;
            }
        }
        /* printf("%i\n", freq); */
        fclose(f);
    }

    /* print_list(&root); */
    printf("\nResult: %i\n", freq);
    return 0;
}
