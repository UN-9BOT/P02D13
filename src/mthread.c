#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define vertical 25
#define horizontal 80

void output(char array1[][horizontal]);
void input(char array1[][horizontal]);
int get_lives(char array[][horizontal], int vert, int horiz);
int check_live(char array[][horizontal], int vert, int horiz);
//void run(char array1[][80], char array2[][80]);
void next_epoch(char array1[][80], char array2[][80]);
void *scan_speed(void *speed);
void *print_thread(void *speed);
void start_thread(int *speed);


int main() {
    int speed = 100;
    start_thread(&speed);
    // char array1[vertical][horizontal];
    // char array2[vertical][horizontal];
    //run(array1, array2);
}

void *scan_speed(void *speed) { 
    char scan_char[256];
    freopen("/dev/tty", "r", stdin);
    while (1) {
    
    fgets(scan_char, sizeof(scan_char), stdin);
    
    if (*scan_char == 'w' || *scan_char == 'W') {
        *((int*)speed) += 10;  
    } else if (*scan_char == 's' || *scan_char == 'S'){
        *((int*)speed) -= 10;
    }
    }
    
}

void *print_thread(void *speed) {
    int set_array = 0;
    char array1[vertical][horizontal];
    char array2[vertical][horizontal];
    
    input(array1);
      while (1) {
        printf("\033[2J");
        printf("%d", *((int*)speed));
        if (set_array == 0){
            next_epoch(array1, array2);
            set_array = 1;
            output(array2);
        } else {
            next_epoch(array2, array1);
            set_array = 0;
            output(array1);
        }
        
        usleep(*((int*)speed) * 1000);
    }
}

void start_thread(int *speed) {
    pthread_t speed_tid, print_tid;
    pthread_create(&print_tid, NULL, print_thread, (void*)speed);
    sleep(3);
    pthread_create(&speed_tid, NULL, scan_speed, (void*)speed);
    
    pthread_join(speed_tid, NULL); // ожидание завершения первого потока
    pthread_join(print_tid, NULL); // ожидание завершения второго потока
}

void input(char array1[][80]) {
    for (int vert = 0; vert < vertical; vert++) { 
        for (int horiz = 0; horiz < horizontal; horiz++) {
            scanf("%c", &array1[vert][horiz]);
        }
    }
}

void output(char array1[][80]) {    
    for (int vert = 0; vert < vertical; vert++) {
        printf("|");
        for (int horiz = 0; horiz < horizontal; horiz++) {
            if (array1[vert][horiz] == 48)
                printf(" ");
            else
                printf("%c", 254);
        }
        printf("|\n");
    }
}

int check_live(char array[][80], int vert, int horiz) {
    int lives, rez = 0;
    lives = get_lives(array, vert, horiz);
    if (array[vert][horiz] == 48) {
        rez = (lives == 3) ? 1 : 0;
    } else if (array[vert][horiz == 49]) {
        rez = ((lives == 2) || (lives == 3)) ? 1 : 0;
    }
    return rez;
}

int get_lives(char array[][80], int vert, int horiz) {
    int rez = 0;
    for (int i = vert - 1; i <= vert + 1; i++) {
        for (int x = horiz - 1; x <= horiz + 1; x++){     
            if (array[(i + 25) % 25][(x + 80) % 80] == 49)
                rez += 1;
        }
    }
    if (array[vert][horiz] == 49)
        rez -= 1;
    return rez;
}

void next_epoch(char array1[][80], char array2[][80]) {
    for (int vert = 0; vert < vertical; vert++) { 
        for (int horiz = 0; horiz < horizontal; horiz++) {
            if (check_live(array1, vert, horiz) == 1)
                array2[vert][horiz] = 49;
            else
                array2[vert][horiz] = 48;
        }
    }
}
