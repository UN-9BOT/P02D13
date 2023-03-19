#include <stdio.h>
#include <unistd.h>
#define ROW 25
#define COL 80
#define cclear() printf("\033[H\033[J")

void startBox(int[][COL], int *);  // Забираем начальный бокс и Считываем скорость
void generateEpoch(int[][COL]);  // Генерация Эпохи
void prEpoch(int[][COL]);        // Печать кадра
int nextState(int, int);  // Генерация состояния элемента для следующей эпохи
int checkArea(int[][COL], int, int);  // Чек выхода за границы
int checkDie(int[][COL]);             // Чек на гибель бокса

int main(void) {
    int box[ROW][COL], speed;
    int countEpoch = 0;
    startBox(box, &speed);
    while (checkDie(box) && countEpoch++ < 1000) {
        generateEpoch(box);
        usleep(speed);
    }
    return (0);
}

void startBox(int box[][COL], int *speed) {
    for (int n = 0; n < ROW; n++) {
        for (int m = 0; m <= COL; m++) {
            box[n][m] = (getchar() == '1') ? 1 : 0;
        }
    }

    if (freopen("/dev/tty", "r", stdin) == NULL) {
        printf("ERROR");
    } else {
        printf("Введите скорость\n");
        printf("0 для стандартной (50 000)\n");
        scanf("%d", speed);
        if (*speed == 0) {
            *speed = 50000;
        }
    }
}

int checkDie(int box[][COL]) {
    int counter = 0;
    for (int n = 0; n < ROW; n++) {
        for (int m = 0; m < COL; m++) {
            counter += box[n][m];
        }
    }
    return (counter);
}

void prEpoch(int box[][COL]) {
    for (int n = 0; n < ROW; n++) {
        for (int m = 0; m < COL; m++) {
            (box[n][m] == 1) ? printf("@") : printf(" ");
        }
        printf("\n");
    }
}

int relN(int n) { return ((n + ROW) % ROW); }  // чек выхода за границы относительно координаты N
int relM(int m) { return ((m + COL) % COL); }  // чек выхода за границы относительно координаты M

int checkArea(int box[][COL], int n, int m) {
    int counter = 0;

    counter += box[relN(n - 1)][relM(m - 1)];
    counter += box[relN(n - 1)][relM(m)];
    counter += box[relN(n - 1)][relM(m + 1)];
    counter += box[relN(n)][relM(m - 1)];
    counter += box[relN(n)][relM(m + 1)];
    counter += box[relN(n + 1)][relM(m - 1)];
    counter += box[relN(n + 1)][relM(m)];
    counter += box[relN(n + 1)][relM(m + 1)];
    return (counter);
}

int nextState(int state, int counter) {
    int res = 0;

    if (state == 0) {
        res = (counter == 3) ? 1 : 0;
    } else if (state == 1) {
        res = ((counter == 2) || (counter == 3)) ? 1 : 0;
    }
    return (res);
}

/* void prDebug(int box[][COL]) { */
/*     for (int n = 0; n < ROW; n++) { */
/*         for (int m = 0; m < COL; m++) { */
/*             printf("%d", box[n][m]); */
/*         } */
/*         printf("\n"); */
/*     } */
/* } */

void copyBox(int nextBox[][COL], int box[][COL]) {
    for (int n = 0; n < ROW; n++) {
        for (int m = 0; m < COL; m++) {
            nextBox[n][m] = box[n][m];
        }
    }
}
void generateEpoch(int box[][COL]) {
    int nextBox[ROW][COL];
    cclear();
    prEpoch(box);
    for (int n = 0; n < ROW; n++) {
        for (int m = 0; m < COL; m++) {
            nextBox[n][m] = nextState(box[n][m], checkArea(box, n, m));
            // для каждой клетки возвращаем состояние и при этом проверяем границы
        }
    }
    copyBox(nextBox, box);
}
