#include <stdio.h>
#include <stdlib.h>


struct Node
{
    int value;
    struct Node *next;
};




int main() {
    int len1, len2;
    scanf("%d %d", &len1, &len2);
    struct Node *head1 = NULL;
    struct Node *head2 = NULL;
    read_list(len1, &head1);
    read_list(len2, &head2);
    int attachable;
    int base;
    scanf("%d %d", &attachable, &base);
    if (attachable == 1) {
        connect_list(&head1, &head2);
    } else {
        connect_list(&head2, &head1);
    }
    print_list(head1);
    print_list(head2);
    struct Node *current = attachable == 1 ? head2 : head1;
    struct Node *next;
    while (current) {
        next = current -> next;
        free(current);
        current = next; 
    }
    return 0;
}
