#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void *print_thread(void *arg) {
    while (1) {
        printf("%p", arg);
        printf("Hello, world!\n"); // печать текста
        usleep(1000); // пауза на 1 секунду
    }
    return NULL;
}

void *input_thread(void *arg) {
    char buffer[256];
    while (1) {
        printf("%p", arg);
        printf("Hello, world!\n"); // печать текста
        printf("Enter some text: ");
        fgets(buffer, sizeof(buffer), stdin); // считывание ввода пользователя
        if (*buffer == 'q') { printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); }
        printf("You entered: %s", buffer); // вывод введенных данных
    }
    return NULL;
}

int main() {
    pthread_t print_tid, input_tid;
    int ret;

    ret = pthread_create(&print_tid, NULL, print_thread, NULL); // создание первого потока
    if (ret != 0) {
        printf("Error creating print thread\n");
        exit(EXIT_FAILURE);
    }

    ret = pthread_create(&input_tid, NULL, input_thread, NULL); // создание второго потока
    if (ret != 0) {
        printf("Error creating input thread\n");
        exit(EXIT_FAILURE);
    }

    pthread_join(print_tid, NULL); // ожидание завершения первого потока
    pthread_join(input_tid, NULL); // ожидание завершения второго потока

    return 0;
}
