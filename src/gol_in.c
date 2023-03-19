#include <stdio.h>
#include <unistd.h>

#define ROW 25
#define COL 80
#define clear() printf("\033[H\033[J") 

void startBox(int[][COL], int *);
void prEpoch(int[][COL]);        // рендер кадра
void checkLimit();               // чек выхода за границы
void genEpoch(int[][COL]);  // 1 Эпоха
int nextEpoch(int, int);
int checkLocal(int[][COL], int, int);
void prDebug(int[][COL]);
void nullBox(int[][COL]);
int checkDie(int[][COL]);

int main(void) {
    int speed;
    int countEpoch = 0;
    int box[ROW][COL];  
    startBox(box, &speed);
    while (checkDie(box) && countEpoch++ < 10000) {
        genEpoch(box);
        usleep(speed);
    }
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
    if (*speed == 0) { *speed = 50000; }
    
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

int relativeM(int m) { return ((m + COL) % COL); }
int relativeN(int n) { return ((n + ROW) % ROW); }

int checkLocal(int box[][COL], int n, int m) {
    int counter = 0;

    /* if (n == ROW - 1) { */
    /*     if (box[n][m]) nextBox[n][m] = 1; */
    /* } */
    /* if (n == 0) { */
    /*     if (box[n][m]) nextBox[n][m] = 1; */
    /* } */
    /* if (m == COL - 1) { */
    /*     if (box[n][m]) nextBox[n][m] = 1; */
    /* } */
    /* if (m == 0) { */
    /*     if (box[n][m]) nextBox[n][m] = 1; */
    /* } */
    /* if (n == ROW - 1) { */ 
    /*     if (box[0][m] == 0)  } */
    /* if (n == 0) { n = ROW - 1; } */
    
    counter += box[relativeN(n - 1)][relativeM(m - 1)];
    counter += box[relativeN(n - 1)][relativeM(m)];
    counter += box[relativeN(n - 1)][relativeM(m + 1)];
    counter += box[relativeN(n)][relativeM(m - 1)];
    counter += box[relativeN(n)][relativeM(m + 1)];
    counter += box[relativeN(n + 1)][relativeM(m - 1)];
    counter += box[relativeN(n + 1)][relativeM(m)];
    counter += box[relativeN(n + 1)][relativeM(m + 1)];
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

void copyBox(int outBox[][COL], int inBox[][COL]) {
    for (int n = 0; n < ROW; n++) {
        for (int m = 0; m < COL; m++) {
            inBox[n][m] = outBox[n][m];
        }
    }
}

void genEpoch(int box[][COL]) {
    int nextBox[ROW][COL];
    clear();
    /* prDebug(box); */
    /* nullBox(nextBox); */
    prEpoch(box);
    for (int n = 0; n < ROW; n++) {
        for (int m = 0; m < COL; m++) {
            nextBox[n][m] = nextEpoch(box[n][m], checkLocal(box, n, m));
        }
    }
    copyBox(nextBox, box);
}
