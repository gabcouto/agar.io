#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct posicao
{
    int x;
    int y;
}POSICAO;

typedef struct bola
{
    int tipo;//entre 0 e 2 // ex: normal=0, explosiva=1, venenosa=2
    int mov;//entre 0 e 3 // ex: estatica=0, aleatoria=1, direcionada=2, perseguidora=3
    POSICAO position;
    int raio;
}BOLA;
/*Como precisamos representar as "comidas" que tambem sao bolas, podemos definir um tamanho minimo para o raio que o jogador terá e um tamanho TAM
para representá-las assim: if(comida.raio<TAM){comida.mov=0}, pois a comida nao pode se mover*/

typedef struct scores//estrutura dos classificados
{
    char nome[51];
    int score;
}SCORES;

void ganhadores(void)//funcao que exibe classificados // acho que deve estar funcionando mas de uma olhada só para ter certeza
{
    FILE* arquivo;
    SCORES winners[10];
    int i;

    BeginDrawing();
    ClearBackground(RAYWHITE);
    arquivo=fopen("Ganhadores.bin","a+b");
    fread(winners,sizeof(SCORES),10,arquivo);
    for(i=0;i<10;i++){
        DrawText(i+1, 323, 100+(i*30), 11, DARKGRAY);
        DrawText(". Nome:", 324, 100+(i*30), 11, DARKGRAY);
        DrawText(winners[i].nome, 326, 101+(i*30), 11, DARKGRAY);
        DrawText(" Pontuacao: ", 326, 102+(i*30), 11, DARKGRAY);
        DrawText(winners[i].score, 326, 103+(i*30), 11, DARKGRAY);
        DrawText("\n", 323, 104+(i*30), 11, DARKGRAY);
    }
    fclose(arquivo);
}

int main()
{
    FILE* arquivo;
    SCORES winners[10];
    int i;

    arquivo=fopen("Ganhadores.bin","a+b");
    for(i=0;i<10;i++){
        printf("Entre nome do jg %d:\n", i+1);
        fflush(stdin);
        fgets(winners[i].nome,51,stdin);
        printf("Entre score do jog %d:\n", i+1);
        scanf("%d", &winners[i].score);
    }
    for(i=0;i<10;i++){
        fwrite(&winners[i],sizeof(SCORES),1,arquivo);
    }
    fclose(arquivo);
    InitWindow(800,450,"NIGGER");
    ganhadores();
    return 0;
}
    SCORES winners[10];
    int i;

    arquivo=fopen("Ganhadores.bin","a+b");
    for(i=0;i<10;i++){
        printf("Entre nome do jg %d:\n", i+1);
        fflush(stdin);
        gets(winners[i].nome);
        printf("Entre score do jog %d:\n", i+1);
        scanf("%d", &winners[i].score);
    }
    for(i=0;i<10;i++){
        fwrite(&winners[i],sizeof(SCORES),1,arquivo);
    }
    fclose(arquivo);
    ganhadores();
    return 0;
}
