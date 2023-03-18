#include <stdio.h>
#include <unistd.h>

#define ROW 25
#define COL 80
#define TMSLEEP 1

/* void rulesBox(); // старт поле с правилами */
void prEpoch(int [][COL]); // рендер кадра
void checkLimit(); // чек выхода за границы
/* int getCounter(int [][COL], int, int); // чек полей вокруг клетки и возврат счёта */
void genEpoch(int [][COL]); // 1 Эпоха
void nextEpoch(int, int, int, int, int [][COL]);
void getTestBox(int [][COL]);
int checkLocal(int [][COL], int, int);

int main(void) {
    int box[ROW][COL]; // тестовый бокс с нач состоянием
    /* rulesBox(); */
    getTestBox(box);
    genEpoch(box);
    
    return (0);
}

void getTestBox(int box[][COL]) {
    for (int n = 0; n < ROW; n++) {
        for (int m = 0; m < COL; m++) {
            if (m % 2 == 0 || n % 3 == 0) { 
                box[n][m] = 1;
            } else {
                box[n][m] = 0;
            }
        }
    }
}

void prEpoch(int box[][COL]) {
    for (int n = 0; n < ROW; n++) {
        for (int m = 0; m < COL; m++) {
            if (box[n][m] == 1) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int checkLocal(int box[][COL], int n, int m) {
    int counter = 0;
    for (int i = -1; i <= 1 && i != 0; i++) {
        for (int j = -1; j <= 1 && j != 0; j++) {
            counter += box[n + i][m + j];
        }
    }
    return (counter);
}

/* int getCounter(int box[][COL], int n, int m) { */
/*     int x = 0; */
/*     int y = 0; */
/*     int counter = 0; */
/*     for (int jn = 0; jn < ROW; jn++) { */
/*         for (int jm = 0; jm < COL; jm++) { */
/*             counter += checkLocal(box, jn, jm); */
/*         } */
/*     } */
/*     return (counter); */
/* } */

void nextEpoch(int n, int m, int state, int counter, int nextBox[][COL]) {
    switch (state) {
        case (0) :
            nextBox[n][m] = (counter == 3) ? 1 : 0;
            break;
        case (1) :
            nextBox[n][m] = ((counter == 2) || (counter == 3)) ? 1 : 0;
            break;
        default :
            for (int i = 1000; --i != 0; printf("\nError\n")) {};
    }
}


void genEpoch(int box[][COL]) {
    int counter;
    int state;
    int nextBox[ROW][COL];
    prEpoch(box);
    for (int n = 0; n < ROW; n++) {
        for (int m = 0; m < COL; m++) {
            state = box[n][m];
            counter = checkLocal(box, n, m);
            nextEpoch(n, m, state, counter, nextBox);
        }
    }
    sleep(TMSLEEP);
    genEpoch(nextBox);
}
    


