#include <stdlib.h>

typedef struct node_s {
    int value;
    struct node_s* next;
} node;

node* build_list(int length) {
    node* head = NULL;

    for (int i = length; i >= 0; i--) {
        node* new_node = (node*) malloc(sizeof(node));
        new_node->value = i;
        new_node->next = head;
        head = new_node;
    }

    return head;
}

node* remove_node(node** head, int search_value) {
    node** dp = head;

    while(*dp && (**dp).value != search_value) {
        dp = &(*dp)->next;
    }

    if (*dp == NULL) {
        return NULL;
    }

    node* deleted_node = *dp;
    *dp = deleted_node->next;
    deleted_node->next = NULL;

    return deleted_node;
}

int main() {
    node* head = build_list(5);

    node* removed_node = remove_node(&head, 3);

    return 0;
}