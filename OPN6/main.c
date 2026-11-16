#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void CleanBuffer(void);

float MaxDelta(int size, float delta[size]);

int main(void) {

    char err,cont,nextSymb;
    int systemSize;
    int bottomBorder = 2;
    int topBorder = 100;
    float epsilon,prop;


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

        float B [systemSize];
        float X [systemSize];

        //coefficients

        for (int i = 0; i < systemSize; i++) {
            for (int j = 0; j < systemSize; j++) {
                float coefficient;

                printf("A%d%d:",i+1,j+1);

                if (!scanf("%f",&coefficient)) {
                    printf("\nInvalid input. Coefficient must be an integer\n");
                    j--;
                    CleanBuffer();
                    continue;
                }

                if (i == j && coefficient == 0) {
                    printf("\nInvalid input. Diagonal coefficient can't equals zero\n");
                    j--;
                }
                else {
                    A[i][j] = coefficient;
                }
            }
        }

        //free index
        for (int i = 0; i < systemSize; i++) {
            float freeIndex;
            printf("B%d:",i+1);
            if (!scanf("%f",&freeIndex)) {
                printf("\nInvalid input. Coefficient must be an integer\n");
                i--;
                CleanBuffer();
            }
            else {
                B[i] = freeIndex;
            }
        }

        printf("\n");
        // for (int i = 0; i < systemSize; i++) {
        //     for (int j = 0; j < systemSize; j++) {
        //         printf("A%d%d = %d\n",i+1,j+1, A[i][j]);
        //     }
        // }

        float xp[systemSize];

        for (int i = 0; i < systemSize; i++) {
            xp[i] = B[i]/A[i][i];
        }

        do {
            float delta[systemSize];

            for (int i = 0; i < systemSize; i++) {

                float sum = 0;

                for (int j = 0; j < systemSize; j++) {

                    if (i!=j) {
                        sum += A[i][j]* xp[j];
                    }
                }
                X[i] = (B[i] - sum) / A[i][i];
                delta[i] = fabs(X[i] - xp[i]);
            }
            for (int i = 0; i < systemSize; i++) {
                xp[i] = X[i];
            }
            prop = MaxDelta(systemSize,delta);
        }while (prop>epsilon);

        for (int i = 0; i < systemSize; i++) {
            printf("X%d: %f\n",i+1, X[i]);
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

float MaxDelta(int size, float delta[size]) {
    float maxDelta = delta[0];
    for (int i = 0; i < size; i++) {
        if (delta[i] > maxDelta) {
            maxDelta = delta[i];
        }
    }
    return maxDelta;
}