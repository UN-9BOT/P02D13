#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define HIGH 25
#define WIDTH 80

void input(int next_matrix[HIGH][WIDTH], int i, int j, int ret);
void output(int matrix[][WIDTH]);
void game(int matrix[HIGH][WIDTH]);
int check_alive(int matrix[HIGH][WIDTH], int i, int j);
int check_dead(int matrix[HIGH][WIDTH], int i, int j);

int main()
{
    //int next_matrix[HIGH][WIDTH] = {0};
    int matrix[HIGH][WIDTH] = {0};
    FILE*file;
    file = fopen("ship.txt", "r");
    char c;
    for(int i = 0; i <HIGH; i++)
    {
        for(int j = 0; j<=WIDTH; j++){
            c = fgetc(file);
            //printf("%c", c);
            if(c == '1'){
                matrix[i][j] = 1;
            }
        }
    }
    printf("\n");
    output(matrix);
    usleep(50000);
    printf("\n");
    game(matrix);
    
    
    //output(matrix);
    //fclose(file);
    return 0;
}

void output(int matrix[HIGH][WIDTH])
{
    for(int i = 0; i<80; i++)
        printf("-");
    printf("\n");
    for (int i = 0; i < HIGH; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if(matrix[i][j] == 1)
                printf("#");
            else if(matrix[i][j] == 0)
                printf(" ");
            
        }printf("\n");
    }
    for(int i = 0; i<80; i++)
        printf("-");
    //for(int i = 0; i<80; i++)
     //   printf("-");
    printf("\n");
}

void game(int matrix[HIGH][WIDTH])
{
    int next_matrix[HIGH][WIDTH] = {0};
    for (int i = 0; i < HIGH; i++){
        for (int j = 0; j < WIDTH; j++)
        {
            if(matrix[i][j] == 0 && check_alive(matrix, i, j) == 3){
                //printf("\n!\n");
                //next_matrix[i][j] = 1;
                input(next_matrix, i, j, 1);
            }
            else if (matrix[i][j] == 1 && (check_alive(matrix, i, j)<2 || check_alive(matrix, i, j)>3))
            {
                //printf("\n?\n");
                //next_matrix[i][j] = 0;
                input(next_matrix, i, j, 0);
            }
            else if (matrix[i][j] == 1 && (check_alive(matrix, i, j)==2 || check_alive(matrix, i, j)==3))
            {
                //printf("\n?\n");
                //next_matrix[i][j] = 0;
                input(next_matrix, i, j, 1);
            }
            
            
        }
    }
    output(next_matrix);
    printf("\n");
    usleep(50000);
    game(next_matrix);
    //input(next_matrix);
}

//проверка... нужно ли спамнить новую клетку
int check_alive(int matrix[HIGH][WIDTH], int a, int b)
{
    int check = 0;
    int line, col;
    for (int i = a-1; i<=a+1; i++){
        if (i>=25){
            line = 0;
        }
        else if (i<0){
            line = 24;
        }
        else
            line = i;
        for (int j = b-1; j<=b+1; j++)
        {
            
            if(j>=80){
                col = 0;
            }
            else if(j<0){
                col = 79;
            }
            else
                col = j;
                
            
            check += matrix[line][col];
                
            
        }
    }
    check -= matrix[a][b];
    /*
    if(check == 3)
    {
        return 1;
    }
     */
    return check;
}

//проверка... нужно ли убирать клетку return 1 если можно
/*
int check_dead(int matrix[HIGH][WIDTH], int a, int b)
{
    int check = 0;
    int line, col;
    
    check+=matrix[a-1][b-1];
    check+=matrix[a-1][b];
    check+=matrix[a-1][b+1];
    check+=matrix[a][b-1];
    check+=matrix[a][b+1];
    check+=matrix[a+1][b-1];
    check+=matrix[a+1][b];
    check+=matrix[a+1][b+1];
    
    for (int i = a-1; i<=a+1; i++){
        for (int j = b-1; j<=b+1; j++)
        {
            if (i>25)
                line = 0;
            else if (i<0)
                line = 25;
            else if(j>80)
                col = 0;
            else if(j<0)
                col = 80;
            else{
                line = i;
                col = j;
            }
            
                
            check += matrix[line][col];
        }
    }
    check -= matrix[a][b];
    if(check != 3 && check != 2)
    {
        return 1;
    }
    else
        return 0;
    return 0;
}
*/

void input(int next_matrix[HIGH][WIDTH], int a, int b, int ret)
{
    for (int i = 0; i < HIGH; i++)
        for (int j = 0; j < WIDTH; j++){
            if(i == a && j == b)
                next_matrix[i][j] = ret;
        }
     

}
