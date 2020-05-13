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
    Polynomial polynomial = polynomialCreate();
    while (1) {
        int coefficient;
        int power;
        int readNum = fscanf(fp, "%dx^%d", &coefficient, &power);
        if (readNum == EOF || readNum == 0) {
            break;
        }
        printf("TEST: readNum: %d\n", readNum);
        if (readNum == 1) {
            printf("1 coefficient: %d\n", coefficient);
            polynomial = addNewItem(polynomial, coefficient, 0);
        } else {
            polynomial = addNewItem(polynomial, coefficient, power);
        }
    }
    return polynomial;

}

int hasNextNode(Node *node) {
    if (node == NULL) {
        return 0;
    }
    if (node->next == NULL) {
        return 0;
    } else {
        return 1;
    }
}

Node *updataToNextNode(Node *node) {
    if (hasNextNode(node)) {
        return node->next;
    } else {
        return NULL;
    }
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

    int is_p1_to_NULL = 0;
    int is_p2_to_NULL = 0;

    while (is_p1_to_NULL == 0 && is_p2_to_NULL == 0) {
        int p1_power = p1_current->x_power;
        int p2_power = p2_current->x_power;

        if (p1_power < p2_power) {
            int p2_num = p2_current->num;
            output_polynomial = addNewItem(output_polynomial, p2_num, p2_power);

            if (hasNextNode(p2_current)) {
                p2_current = updataToNextNode(p2_current);
            } else {
                is_p2_to_NULL = 1;
            }

        } else if (p1_power > p2_power) {
            int p1_num = p1_current->num;
            output_polynomial = addNewItem(output_polynomial, p1_num, p1_power);

            if (hasNextNode(p1_current)) {
                p1_current = updataToNextNode(p1_current);
            } else {
                is_p1_to_NULL = 1;
            }

        } else {
            int add_coefficient = p1_current->num + p2_current->num;
            output_polynomial =
                addNewItem(output_polynomial, add_coefficient, p1_power);

            if (hasNextNode(p1_current)) {
                p1_current = updataToNextNode(p1_current);
            } else {
                is_p1_to_NULL = 1;
            }
            if (hasNextNode(p2_current)) {
                p2_current = updataToNextNode(p2_current);
            } else {
                is_p2_to_NULL = 1;
            }
        }
    }
    if (is_p1_to_NULL == 0 && is_p2_to_NULL == 1) {
        while (hasNextNode(p1_current)) {
            output_polynomial = addNewItem(output_polynomial, p1_current->num,
                                           p1_current->x_power);
            p1_current = updataToNextNode(p1_current);
        }

    } else if (is_p1_to_NULL == 1 && is_p2_to_NULL == 0) {
        while (hasNextNode(p2_current)) {
            output_polynomial = addNewItem(output_polynomial, p2_current->num,
                                           p2_current->x_power);
            p2_current = updataToNextNode(p2_current);
        }
    }
    return output_polynomial;
}

void *writePolynomialToFile(char *filePath, Polynomial polynomial) {
    FILE *fout = fopen(filePath, "w+t");

    if (fout == NULL) {
        printf("Fail To Open File out1.txt!!");
        fclose(fout);
        return;
    }
    Node *current = polynomial.first;
    int first_write = 1;
    while (current != NULL) {
        int coefficient = current->num;
        int power = current->x_power;
        if (first_write) {
            if (coefficient > 0 || coefficient < 0) {
                fprintf(fout, "%dx^%d", coefficient, power);
            }
            first_write = 0;
        } else {  // not first write
            if (coefficient > 0) {
                fprintf(fout, "+%dx^%d", coefficient, power);
            } else if (coefficient < 0) {
                fprintf(fout, "%dx^%d", coefficient, power);
            }  // if (coefficient == 0) do nothing
        }

        current = updataToNextNode(current);
    }
    fclose(fout);
}

int main() {
    Polynomial polynomial_1 = getPolynomialFromFile("Poly1.txt");
    Polynomial polynomial_2 = getPolynomialFromFile("Poly2.txt");

    show(polynomial_1);
    show(polynomial_2);

    Polynomial ansPolynomial = addTwoPolynomial(polynomial_1, polynomial_2);
    show(ansPolynomial);
    writePolynomialToFile("test.txt", ansPolynomial);

    return 0;
}
