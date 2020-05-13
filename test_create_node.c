#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int num;
    int x_power;
    struct node *next;
}Node;

typedef struct {
    Node *first;
}Polynomial;

Polynomial polynomialCreate() {
    Polynomial polynomial;
    polynomial.first = NULL;
    return polynomial;
}

Node* createNodePtr(int num, int x_power) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->num = num;
    new_node->x_power = x_power;
    new_node->next = NULL;
    return new_node;
}

void show(Polynomial polynomial) {
    Node *current = polynomial.first;
    while(current != NULL) {
        printf("TEST: num: %d, x_power:%d\n", current->num, current->x_power);
        current = current->next;
    }
}


int main() {
    Polynomial polynomial = polynomialCreate();
    Node *node1 = createNodePtr(3, 5);
    Node *node2 = createNodePtr(2, 6);
    node1->next = node2;
    Node *node3 = createNodePtr(1, 7);
    node2->next = node3;

    polynomial.first = node1;
    show(polynomial);
    
    return 0;
}