#include <stdio.h>
#include <stdlib.h>


void CleanBuffer(void);

int main(void) {

    char err,cont,nextSymb;
    int systemSize;
    int bottomBorder = 2;
    int topBorder = 100;
    float epsilon;

    do{
        printf("Program for solving SLEs\n");
        printf("A11X1 + A12X2 + ... + A1nXn = B1\n");
        printf("A21X1 + A22X2 + ... + A2nXn = B2\n");
        printf("................................\n");
        printf("An1X1 + An2X2 + ... + AnnXn = Bn\n");

    printf("\n");

        //system size
        do {
            err = 0;
            nextSymb = '0';
            printf("Enter size -->\n");

            if (!scanf("%d%c",&systemSize,&nextSymb) || nextSymb != '\n' || systemSize < bottomBorder || systemSize > topBorder) {
                printf("\nInvalid input. Try again\n");
                err = 1;
                // CleanBuffer();
            }
            if (nextSymb != '\n'){
                CleanBuffer();
            }
        }while (err != 0);

        //epsilon
        do {
            err = 0;
            printf("Enter epsilon in standard form (max 0.00001)-->\n");

            if (!scanf("%f%c",&epsilon,&nextSymb) || nextSymb != '\n') {
                printf("\nInvalid input. Try again\n");
                err = 1;
                CleanBuffer();
            }
        }while (err != 0);

        //memory allocation
        float **A = (float **)calloc(systemSize,  sizeof(float *));
        if (A == NULL) {
            printf("Memory allocation failed\n");
            err = 1;
        }
        else {
            for (int i = 0; i < systemSize; i++) {
                A[i] = (float *)calloc(systemSize, sizeof(float));
                if (A[i] == NULL) {
                    free(A);
                    printf("Memory allocation failed\n");
                    err = 1;
                    break;
                }
            }
        }

        //coefficients

        for (int i = 0; i < systemSize; i++) {
            for (int j = 0; j < systemSize; j++) {
                printf("");
            }
        }


        do {
            err = 0;
            printf("Do you want to continue? (Press ENTER to continue or S to stop)\n");
            cont = (char) getchar();

            if (cont != '\n' && cont != 'S' && cont != 's') {
                printf("Invalid input. Try again\n");
                err = 1;
                CleanBuffer();
            }
        }while(err != 0);
    }while(cont == '\n');
    return 0;
}

void CleanBuffer(void) {
    while (getchar() != '\n');
}