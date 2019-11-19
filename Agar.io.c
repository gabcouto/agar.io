#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//#include <windows.h>
//#include <conio.h>
#include "raylib.h"

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
    int score[25];
}SCORES;

void ganhadores(void)//funcao que exibe classificados // acho que deve estar funcionando mas de uma olhada só para ter certeza
{
    FILE* arquivo;
    SCORES winners[10];
    int i;

    arquivo=fopen("Ganhadores.bin","a+b");
    fread(winners,sizeof(SCORES),10,arquivo);
    for(i=0;i<10;i++){
        printf("%d. Nome: %s   Pontuacao: %d\n", i+1, winners[i].nome, winners[i].score);
    }
    fclose(arquivo);
}

int main()
{

    return 0;
}
