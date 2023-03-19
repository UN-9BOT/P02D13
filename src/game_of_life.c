#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define ROW 25
#define COL 80
#define SPEEDSTART 100000
#define cclear() printf("\033[H\033[J")

void startBox(int[][COL]);  // Забираем начальный бокс и Считываем скорость
void generateEpoch(int[][COL]);  // Генерация Эпохи
void prEpoch(int[][COL]);        // Печать кадра
int nextState(int, int);  // Генерация состояния элемента для следующей эпохи
int checkArea(int[][COL], int, int);  // Чек выхода за границы
int checkDie(int[][COL]);             // Чек на гибель бокса
void *epochThread(void *);
void *spThread(void *);

int main(void) {
    pthread_t print_tid, input_tid;
    int speed = SPEEDSTART;
    pthread_create(&print_tid, NULL, epochThread, (void *)&speed);  // создание первого потока
    sleep(3);
    pthread_create(&input_tid, NULL, spThread, (void *)&speed);  // создание второго потока

    pthread_join(print_tid, NULL);  // ожидание завершения первого потока
    pthread_join(input_tid, NULL);  // ожидание завершения второго потока
    return (0);
}

void *epochThread(void *speed) {
    int box[ROW][COL];
    startBox(box);
    while (checkDie(box) && *((int *)speed) != 1) {
        prEpoch(box);
        usleep(*((int *)speed));
        generateEpoch(box);
    }
    return (NULL);
}

void *spThread(void *speed) {
    char buffer[2];
    if (freopen("/dev/tty", "r", stdin) == NULL) {
        printf("ERROR");
    }
    while (*((int *)(speed)) != 1) {
        fgets(buffer, sizeof(buffer), stdin);  // считывание ввода пользователя
        if (*buffer == 'q') {
            *((int *)(speed)) = 1;
        }
        if (*buffer == '+' && *((int *)(speed)) >= 5000) {
            *((int *)(speed)) -= 5000;
        }
        if (*buffer == '-' && *((int *)(speed)) <= 200000) {
            *((int *)(speed)) += 5000;
        }
    }
    return (NULL);
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
void startBox(int box[][COL]) {
    for (int n = 0; n < ROW; n++) {
        for (int m = 0; m <= COL; m++) {
            int c = getchar();
            box[n][m] = (c == '1') ? 1 : 0;
        }
    }
}
void prEpoch(int box[][COL]) {
    for (int n = 0; n < ROW; n++) {
        for (int m = 0; m < COL; m++) {
            if (box[n][m] == 1) {
                printf("@");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int relN(int n) { return ((n + ROW) % ROW); }  // чек выхода за границы относительно 1 координаты N
int relM(int m) { return ((m + COL) % COL); }  // чек выхода за границы относительно 1 координаты M

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

void copyBox(int outBox[][COL], int inBox[][COL]) {
    for (int n = 0; n < ROW; n++) {
        for (int m = 0; m < COL; m++) {
            inBox[n][m] = outBox[n][m];
        }
    }
}

void generateEpoch(int box[][COL]) {
    int nextBox[ROW][COL];
    cclear();
    for (int n = 0; n < ROW; n++) {
        for (int m = 0; m < COL; m++) {
            nextBox[n][m] = nextState(box[n][m], checkArea(box, n, m));
        }
    }
    copyBox(nextBox, box);
}
