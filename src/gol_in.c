#include <stdio.h>
#include <unistd.h>

#define ROW 25
#define COL 80
#define clear() printf("\033[H\033[J") 

void startBox(int[][COL], int *);
void prEpoch(int[][COL]);        // рендер кадра
void checkLimit();               // чек выхода за границы
void genEpoch(int[][COL], int, int);  // 1 Эпоха
int nextEpoch(int, int);
int checkLocal(int[][COL], int[][COL], int, int);
void prDebug(int[][COL]);
void nullBox(int[][COL]);
int checkDie(int[][COL]);

int main(void) {
    int speed;
    int box[ROW][COL];  // тестовый бокс с нач состоянием
    startBox(box, &speed);
    genEpoch(box, 0, speed);
    return (0);
}

void startBox(int box[][COL], int *speed) {
    int c = 0;
    for (int n = 0; n < ROW; n++) {
        for (int m = 0; m <= COL; m++) {
            c = getchar();
             box[n][m] = (c == '1') ? 1 : 0;
        }
    }

    freopen("/dev/tty", "r", stdin);
    printf("Введите скорость\n");
    printf("0 для стандартной (100 000)\n");
    scanf("%d", speed);
    if (*speed == 0) { *speed = 100000; }
    
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
            if (box[n][m] == 1) {
                printf("X");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void nullBox(int box[][COL]) {
    for (int n = 0; n < ROW; n++) {
        for (int m = 0; m < COL; m++) {
            box[n][m] = 0;
        }
    }
}

int checkLocal(int box[][COL], int nextBox[][COL], int n, int m) {
    int counter = 0;

    if (n == ROW - 1) {
        if (box[n][m]) nextBox[n][m] = 1;
    }
    if (n == 0) {
        if (box[n][m]) nextBox[n][m] = 1;
    }
    if (m == COL - 1) {
        if (box[n][m]) nextBox[n][m] = 1;
    }
    if (m == 0) {
        if (box[n][m]) nextBox[n][m] = 1;
    }
    counter += box[n - 1][m - 1];
    counter += box[n - 1][m];
    counter += box[n - 1][m + 1];
    counter += box[n][m - 1];
    counter += box[n][m + 1];
    counter += box[n + 1][m - 1];
    counter += box[n + 1][m];
    counter += box[n + 1][m + 1];
    return (counter);
}

int nextEpoch(int state, int counter) {
    int res = 0;
    if (state == 0) {
        res = (counter == 3) ? 1 : 0;
    } else if (state == 1) {
        res = ((counter == 2) || (counter == 3)) ? 1 : 0;
    } else {
        for (int i = 1000; --i != 0; printf("\nError\n")) {
        };
    }
    return (res);
}

void prDebug(int box[][COL]) {
    for (int n = 0; n < ROW; n++) {
        for (int m = 0; m < COL; m++) {
            printf("%d", box[n][m]);
        }
        printf("\n");
    }
}

void genEpoch(int box[][COL], int countEpoch, int speed) {
    int nextBox[ROW][COL];
    /* prDebug(box); */
    nullBox(nextBox);
    if (checkDie(box) && countEpoch < 10000) {
        clear();
        prEpoch(box);
        for (int n = 0; n < ROW; n++) {
            for (int m = 0; m < COL; m++) {
                nextBox[n][m] = nextEpoch(box[n][m], checkLocal(box, nextBox, n, m));
            }
        }
        usleep(speed);
        genEpoch(nextBox, ++countEpoch, speed);
    }
}
