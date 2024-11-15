#include "2048_game.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

void print_matrix(int matrix[4][4]) {
    int i;
    for (i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", matrix[i][j]);
        }
        if (i == 0) {
            printf("\t\t w ---> up");
        }
        if (i == 1) {
            printf("\t\t a ---> left");
        }
        if (i == 2) {
            printf("\t\t s ---> down");
        }
        if (i == 3) {
            printf("\t\t d ---> right");
        }
        printf("\n");
    }
    printf("\n");
}

int check_empty_matrix(int matrix[4][4]){
    int ok = 0; //pp ca matricea e goala
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(matrix[i][j]==0) {
                ok = 0;
            }
            else{
                ok = 1;
            }
        }
    }
    return ok;
};
void generate_random(int matrix[4][4]){
    int line1, line2, column1, column2;
    line1=rand() % 4;
    column1=rand() % 4;
    while(1)
    {
        line2=rand() % 4;
        column2=rand() % 4;
        if(line2!=line1 && column2!=column1)
            break;
    }
    matrix[line1][column1]=2;
    matrix[line2][column2]=4;
}
void upmove(int matrix[4][4]){
    int li,ci; //pozitiile in care o sa ajunga celula
    for(int j=0;j<4;j++){
        li = 0, ci = j;
        for(int i=1;i<4;i++){ //pornesc de la celula [0][1] (00 nu poate urca)
            if(matrix[i][j] != 0){ //daca am cifra in celula
                if(matrix[i-1][j] == 0 || matrix[i-1][j] == matrix[i][j]){ //daca mai sus e liber sau mai sus este aceeasi cifra
                    if(matrix[li][ci] == matrix[i][j]){ //daca mai sus e aceasi cifra
                        matrix[li][ci] *= 2; //multiplic
                        matrix[i][j] = 0; //celula verificata devine 0
                    }
                    else{
                        if(matrix[li][ci] == 0){ //daca mai sus este gol
                            matrix[li][ci] = matrix[i][j]; //mut mai sus celula
                            matrix[i][j] = 0; //celula verificata devine 0
                        }
                        else{
                            li++; //mut celula cu care am comparat mai sus
                            matrix[li][ci] = matrix[i][j];
                            matrix[i][j] = 0;
                        }
                    }
                }
                else li++;
            }
        }
    }
}
void downmove(int matrix[4][4]){
    int li,ci; //line index, column index
    for(int j=0;j<4;j++){
        li=3,ci=j;
        for(int i=2;i>=0;i--){
            if(matrix[i][j]!=0){
                if(matrix[i+1][j]==0 || matrix[i+1][j]==matrix[i][j]){
                    if(matrix[li][ci]==matrix[i][j]){
                        matrix[li][ci]*=2;
                        matrix[i][j]=0;
                    }
                    else{
                        if(matrix[li][ci]==0){
                            matrix[li][ci]=matrix[i][j];
                            matrix[i][j]=0;
                        }
                        else{
                            li--;
                            matrix[li][ci]=matrix[i][j];
                            matrix[i][j]=0;
                        }
                    }
                }
                else li--;
            }
        }
    }
}
void leftmove(int matrix[4][4]){
    int li,ci;
    for(int i=0;i<4;i++){
        li=i,ci=0;
        for(int j=1;j<4;j++){
            if(matrix[i][j]!=0){
                if(matrix[i][j-1]==0 || matrix[i][j-1]==matrix[i][j]){
                    if(matrix[li][ci]==matrix[i][j]){
                        matrix[li][ci]*=2;
                        matrix[i][j]=0;
                    }
                    else{
                        if(matrix[li][ci]==0){
                            matrix[li][ci]=matrix[i][j];
                            matrix[i][j]=0;
                        }
                        else{
                            ci++;
                            matrix[li][ci]=matrix[i][j];
                            matrix[i][j]=0;
                        }
                    }
                }
                else ci++;
            }
        }
    }
}
void rightmove(int matrix[4][4]){
    int li,ci;
    for(int i=0;i<4;i++){
        li=i,ci=3;
        for(int j=2;j>=0;j--){
            if(matrix[i][j]!=0){
                if(matrix[i][j+1]==0 || matrix[i][j+1]==matrix[i][j]){
                    if(matrix[li][ci]==matrix[i][j]){
                        matrix[li][ci]*=2;
                        matrix[i][j]=0;
                    }
                    else{
                        if(matrix[li][ci]==0){
                            matrix[li][ci]=matrix[i][j];
                            matrix[i][j]=0;
                        }
                        else{
                            ci--;
                            matrix[li][ci]=matrix[i][j];
                            matrix[i][j]=0;
                        }
                    }
                }
                else ci--;
            }
        }
    }
}
void addblock(int matrix[4][4])
{
    int li,ci;
    srand(time(NULL));
    while(1)
    {
        li=rand()%4;
        ci=rand()%4;
        if(matrix[li][ci]==0)
        {
            matrix[li][ci]=pow(2,li%2 + 1);
            break;
        }
    }
}
int check(int copie[4][4],int matrix[4][4])
{
    int ok=1,i,j;
    for(i=0;i<4;i++)
        for(j=0;j<4;j++)
            if(copie[i][j]!=matrix[i][j])
            {
                ok=0;
                break;
            }
    return ok;
}
int check_game_over(int matrix[4][4])
{
    int ok=0,ok1=0,i,j;
    for(i=0;i<4;i++)
        for(j=0;j<4;j++)
            if(matrix[i][j]==0)
            {
                ok=1;
                break;
            }

    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            if(matrix[i+1][j]==matrix[i][j] || matrix[i][j+1]==matrix[i][j])
            {
                ok1=1;
                break;
            }

    if(ok || ok1)
        return 1;
    else
        return 0;
}

void comenzi(char comanda, int matrix[4][4]){
    if(comanda == 'w' || comanda == 'W'){
        upmove(matrix);
        return;
    }
    if(comanda == 'a'|| comanda == 'A'){
        leftmove(matrix);
        return;
    }
    if(comanda == 's' || comanda == 'S'){
        downmove(matrix);
        return;
    }
    if(comanda == 'd' || comanda == 'D'){
        rightmove(matrix);
        return;
    }
}