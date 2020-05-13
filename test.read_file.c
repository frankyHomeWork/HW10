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

Node* createNodePtr(num, x_power) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->num = num;
    new_node->x_power = x_power;
    return new_node;
}






int main() {
    FILE *fp;
    char ch;
    if ((fp = fopen("Poly1.txt", "r")) == NULL) {
        printf("open file error!!\n");
        exit(0);
    }

    while ((ch = getc(fp)) != EOF) {
        printf("%c ", ch);
    }

    fclose(fp);
    return 0;
}