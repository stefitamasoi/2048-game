#include <stdio.h>
#include <stdlib.h>
#include "2048_game.h"
#include <time.h>
int main() {
    int matrix[4][4] = {
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0
    };
    int copie[4][4] = {
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0
    };
    char comanda;
    srand(time(NULL));
    printf("2048 GAME\t\t\n\n");
    int game = check_empty_matrix(matrix);
    if(game == 0){
        //tablita este goala si o initializam 2 casute
        generate_random(matrix);
    }
    print_matrix(matrix);
    while(1){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                copie[i][j]=matrix[i][j];
            }
        }
        scanf("%c", &comanda);
        comenzi(comanda, matrix);
        if(!check(copie,matrix))
            addblock(matrix);
        print_matrix(matrix);

        if(!check_game_over(matrix))
        {
            printf("\n\nGAME OVER!!");
            break;
        }
    }
    return 0;
}
