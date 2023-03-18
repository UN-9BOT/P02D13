#include <stdio.h>
#include <unistd.h>

#define ROW 25
#define COL 80
#define TMSLEEP 300000

void startBox(int[][COL], int *);
void prEpoch(int[][COL]);        // рендер кадра
void checkLimit();               // чек выхода за границы
void genEpoch(int[][COL], int);  // 1 Эпоха
int nextEpoch(int, int);
void getDivBox(int[][COL], int *);
int checkLocal(int[][COL], int[][COL], int, int);
void prDebug(int[][COL]);
void nullBox(int[][COL]);
int checkDie(int[][COL]);

int main(void) {
    int flag, box[ROW][COL];  // тестовый бокс с нач состоянием
    startBox(box, &flag);
    genEpoch(box, 0);
    return (0);
}

void startBox(int box[][COL], int *flag) {
    int choise, trash, c;
    FILE *fp;

    printf("%40s", "\n\n\nИгра <<ЖИЗНЬ>>\n");
    printf("%4s", "Введите номер генерации\n");
    printf("%4s", "1. Устойчивые фигуры\n");
    printf("%4s", "2. Периодические фигуры\n");
    printf("%4s", "3. Долгожители\n");
    printf("%4s", "4. Ружьё\n");
    printf("%4s", "5. Корабль\n");
    printf("%4s", "21. bonus. Генерация на остатке от деления\n");
    if (scanf("%d.%d", &choise, &trash) != 1) { 
        printf("Ошибка ввода\n"); 
        *flag = 1;
    } else {
        switch (choise) {
            case (1) :
                fp = fopen("files/ust.txt", "r");
                for (int n = 0; n < ROW; n++) {
                    for (int m = 0; m <= COL; m++) {
                        c = fgetc(fp);
                        box[n][m] = (c == '1') ? 1 : 0;
                    }
                }
                fclose(fp);
                break;
            case (2) :
                fp = fopen("files/period.txt", "r");
                for (int n = 0; n < ROW; n++) {
                    for (int m = 0; m <= COL; m++) {
                        c = fgetc(fp);
                        box[n][m] = (c == '1') ? 1 : 0;
                    }
                }
                fclose(fp);
                break;
            case (3) :
                fp = fopen("files/dolg.txt", "r");
                for (int n = 0; n < ROW; n++) {
                    for (int m = 0; m <= COL; m++) {
                        c = fgetc(fp);
                        box[n][m] = (c == '1') ? 1 : 0;
                    }
                }
                fclose(fp);
                break;
            case (4) :
                fp = fopen("files/weapon.txt", "r");
                for (int n = 0; n < ROW; n++) {
                    for (int m = 0; m <= COL; m++) {
                        c = fgetc(fp);
                        box[n][m] = (c == '1') ? 1 : 0;
                    }
                }
                fclose(fp);
                break;
            case (5) :
                fp = fopen("files/muve.txt", "r");
                for (int n = 0; n < ROW; n++) {
                    for (int m = 0; m <= COL; m++) {
                        c = fgetc(fp);
                        box[n][m] = (c == '1') ? 1 : 0;
                    }
                }
                fclose(fp);
                break;
            case (21) :
                getDivBox(box, flag);
                break;
        }
    }
}

void getDivBox(int box[][COL], int *flag) {
    int trash, cn, cm;
    printf("%4s", "Введите 2 числа для генерации (например 4 22) (max 24 79)");
    if (scanf("%d %d.%d", &cn, &cm, &trash) != 2) { 
        printf("Ошибка ввода\n");
        *flag = 1;
    } else {
        for (int n = 0; n < ROW; n++) {
            for (int m = 0; m < COL; m++) {
                if (n % cn == 0 || m % cm == 0) {
                    box[n][m] = 1;
                } else {
                    box[n][m] = 0;
                }
            }
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

void genEpoch(int box[][COL], int countEpoch) {
    int nextBox[ROW][COL];
    prDebug(box);
    nullBox(nextBox);
    if (checkDie(box) && countEpoch < 100) {
        prEpoch(box);
        for (int n = 0; n < ROW; n++) {
            for (int m = 0; m < COL; m++) {
                nextBox[n][m] = nextEpoch(box[n][m], checkLocal(box, nextBox, n, m));
            }
        }
        usleep(TMSLEEP);
        genEpoch(nextBox, ++countEpoch);
    }
}
