#include <stdio.h>


void CleanBuffer(void);

int main(void) {

    char err,cont;
    do{




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