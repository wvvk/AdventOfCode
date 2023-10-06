#include <stdio.h>
#include <stdlib.h>
/*write a singly linked list library
1. create a list, destroy a list
2. traverse the list
3. insert a node (in front, and after an element)
4. delete a node with specific value
*/

// define a node
typedef struct node
{
    int data;
    struct node *next;
} node_t;

int int_comp(const void *a, const void *b)
{
    return (*(const int *)b) - *(const int *)a;
}

node_t *create_node(const int data, node_t *next)
{
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->next = next;
    new_node->data = data;
    return new_node;
}

int prepend_node(node_t **head, const int data)
{
    node_t *new_node = create_node(data, *head);
    *head = new_node;
    return 0;
}

node_t *create_list(int *a, size_t a_size)
{
    node_t *head = NULL;
    qsort(a, a_size, sizeof(int), int_comp);
    for (int i = 0; i < a_size; i++)
    {
        prepend_node(&head, *(a + i));
    }
    return head;
}

int destroy_list(node_t **head)
{
    node_t *cur = *head;
    node_t *tmp = NULL;
    while (cur != NULL)
    {
        tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    *head = NULL; // NOTE: prevent dangling pointer
    return 0;
}

void traverse_list(const node_t *head)
{
    const node_t *cur = head;
    printf("linked list\n");

    while (cur != NULL)
    {
        printf("cur:%d\n", cur->data);
        cur = cur->next;
    }
}

int insert_node(node_t **head, const int data)
{
    node_t *cur = *head;
    node_t *prev = NULL;

    node_t *new_node = create_node(data, NULL);

    if (*head == NULL)
    {
        *head = new_node;
        return 0;
    }
    while (cur != NULL)
    {
        if (cur->data > data)
        {
            // insert new node
            new_node->next = cur;
            if (prev == NULL)
            {
                *head = new_node;
            }
            else
            {
                prev->next = new_node;
            }
            return 0;
        }
        prev = cur;
        cur = cur->next;
    }
    // postpend
    prev->next = new_node;
    return 0;
}

int delete_node(node_t **head, const int data)
{
    node_t *cur = *head;
    node_t *prev = NULL;

    while (cur != NULL)
    {
        if (cur->data == data)
        {
            // delete node
            if (prev == NULL)
            {
                *head = cur->next;
            }
            else
            {
                prev->next = cur->next;
            }
            free(cur);
            return 0;
        }
        prev = cur;
        cur = cur->next;
    }
    return 0;
}

int main(void)
{
    int a[] = {1, 2, 3, 4, 5, 10};
    size_t a_sz = sizeof(a) / sizeof(int);
    node_t *ll_head = create_list(a, a_sz);
    traverse_list(ll_head);
    insert_node(&ll_head, 0);
    insert_node(&ll_head, 8);
    insert_node(&ll_head, 11);
    traverse_list(ll_head);
    delete_node(&ll_head, 0);
    delete_node(&ll_head, 111);
    delete_node(&ll_head, 11);
    traverse_list(ll_head);
    destroy_list(&ll_head);
    traverse_list(ll_head);
    return 0;
}
