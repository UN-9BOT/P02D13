#include <stdio.h>
#include <unistd.h>

#define ROW 25
#define COL 80
#define clear() printf("\033[H\033[J") 

void startBox(int[][COL], int *);               // Забираем начальный бокс и Считываем скорость
void prEpoch(int[][COL]);                       // Печать кадра
int checkArea(int [][COL], int, int);          // Чек выхода за границы
void generateEpoch(int[][COL]);                      // Генерация Эпохи
int nextState(int, int);                        // Генерация состояния элемента для следующей эпохи
int checkDie(int[][COL]);                       // Чек на гибель бокса

int main(void) {
    int box[ROW][COL], speed;  
    int countEpoch = 0;

    startBox(box, &speed);
    while (checkDie(box) && countEpoch++ < 10000) {
        generateEpoch(box);
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

    if (freopen("/dev/tty", "r", stdin) == NULL) {
        printf("ERROR");
    } else {
        printf("Введите скорость\n");
        printf("0 для стандартной (100 000)\n");
        scanf("%d", speed);
        if (*speed == 0) { *speed = 50000; }
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
            if (box[n][m] == 1) {
                printf("X");
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
    } else {
        for (int i = 1000; --i != 0; printf("\nError\n")) {
        };
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
    clear();
    prEpoch(box);
    for (int n = 0; n < ROW; n++) {
        for (int m = 0; m < COL; m++) {
            nextBox[n][m] = nextState(box[n][m], checkArea(box, n, m));
        }
    }
    copyBox(nextBox, box);
}
