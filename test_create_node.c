#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int num;
    int x_power;
    struct node *next;
} Node;

typedef struct {
    Node *first;
} Polynomial;

Polynomial polynomialCreate() {
    Polynomial polynomial;
    polynomial.first = NULL;
    return polynomial;
}

Node *createNodePtr(int num, int x_power) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->num = num;
    new_node->x_power = x_power;
    new_node->next = NULL;
    return new_node;
}

void show(Polynomial polynomial) {
    printf("TEST SHOW\n");
    Node *current = polynomial.first;
    while (current != NULL) {
        printf("TEST: num: %d, x_power:%d\n", current->num, current->x_power);
        current = current->next;
    }
}

Polynomial addNewItem(Polynomial polynomial, int num, int x_power) {
    Node *node = createNodePtr(num, x_power);
    if (polynomial.first == NULL) {
        polynomial.first = node;
        return polynomial;
    }

    Node *current = polynomial.first;
    while (current != NULL) {
        if (current->next == NULL) {
            break;
        } else {
            current = current->next;
        }
    }
    Node *lastNode = current;
    lastNode->next = node;
    return polynomial;
}

Polynomial getPolynomialFromFile(char *filePath) {
    FILE *fp;
    if ((fp = fopen(filePath, "r")) == NULL) {
        printf("open file error!!\n");
        exit(0);
    }
    int coefficient;
    int power;

    Polynomial polynomial = polynomialCreate();
    Node *preNode;
    int first = 1;
    while (fscanf(fp, "%dx^%d", &coefficient, &power) != EOF) {
        Node *node = createNodePtr(coefficient, power);
        if (first) {
            polynomial.first = node;
            first = 0;
        } else {
            preNode->next = node;
        }
        preNode = node;
    }
    return polynomial;
}

Polynomial addTwoPolynomial(Polynomial polynomial_1, Polynomial polynomial_2) {
    Polynomial output_polynomial = polynomialCreate();
    Node *p1_current = polynomial_1.first;
    Node *p2_current = polynomial_2.first;
    if (p1_current == NULL && p2_current == NULL) {
        return output_polynomial;
    } else if (p1_current != NULL && p2_current == NULL) {
        return polynomial_1;
    } else if (p1_current == NULL && p2_current != NULL) {
        return polynomial_2;
    }

    int is_p1_not_to_NULL = 1;
    int is_p2_not_to_NULL = 1;

    while (is_p1_not_to_NULL || is_p2_not_to_NULL) {
        int p1_coefficient = 0;
        int p1_power = p1_current->x_power;

        int p2_coefficient = 0;
        int p2_power = p2_current->x_power;

        if (p1_power == p2_power) {
            int add_coefficient = p1_current->num + p2_current->num;
            output_polynomial =
                addNewItem(output_polynomial, add_coefficient, p1_power);

            p1_current = p1_current->next;
            p2_current = p2_current->next;
            if(p1_current == NULL) {
                is_p1_not_to_NULL = 0;
            }
            
            if(p2_current == NULL) {
                is_p2_not_to_NULL = 0;
            }

        }





    }
}

int main() {
    Polynomial polynomial_1 = getPolynomialFromFile("Poly1.txt");
    Polynomial polynomial_2 = getPolynomialFromFile("Poly2.txt");

    show(polynomial_1);
    show(polynomial_2);

    polynomial_1 = addNewItem(polynomial_1, 6, 7);
    show(polynomial_1);

    return 0;
}