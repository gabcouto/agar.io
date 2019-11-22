/*
Arthur Baumgardt & Gabriel Couto

Implementação de agar.io utilizando a biblioteca raylib.h

*/


#include "raylib.h"
#include <time.h>
#include <stdio.h>


int count = 0;
void print_menu(void);
typedef struct cronometro
{
	time_t inicio, fim;
	int andando;
}CRONOMETRO,*pCRONOMETRO;

void nova_partida(void);
void carrega_partida(void);
void mostra_ganhadores(void);
void inicia(pCRONOMETRO);
void para(pCRONOMETRO); 
void continua(pCRONOMETRO);

int main(void)
{

	// Abrimos uma janela.
	const int larguraTela = 800;
	const int alturaTela = 450;
	int desce = 10;
	int sair = 0;
	// Esta função abre uma janela com um nome dado por uma string.
	InitWindow(larguraTela, alturaTela, "Agar.io");
	
	// Definimos a quantidade de FPS.
	SetTargetFPS(60);

	// Enquanto não for detectada a tecla ESC, repete este while.
	while(!(IsKeyPressed(KEY_ENTER) && count == 3))
	{
	
		
		


		BeginDrawing();



	
		// Indica que vamos começar a desenhar na tela.
		print_menu();
			
		if(IsKeyPressed(KEY_DOWN))
			count++;
		if(IsKeyPressed(KEY_UP))
			count--;
						
		if(count > 3)
			count = 0;
		if(count < 0)
			count = 3;
		
		


		switch(count)
		{
		case 0:
			DrawText("Nova partida", 323, desce+100, 20, LIGHTGRAY);
			if(IsKeyPressed(KEY_ENTER))
				nova_partida();
			break;
		case 1:
			DrawText("Carregar partida", 300, desce+130, 20, LIGHTGRAY);
			if(IsKeyPressed(KEY_ENTER))
				carrega_partida();			
			break;
		case 2:
			DrawText("Exibir ganhadores", 300, desce+160, 20, LIGHTGRAY);
			if(IsKeyPressed(KEY_ENTER))
				mostra_ganhadores();
			break;
		case 3:
			DrawText("Sair", 369, desce+190, 20, LIGHTGRAY);
			if(IsKeyPressed(KEY_ENTER))
			{
					
			}

		}
		
		EndDrawing();			
	}

	CloseWindow();


	return 0;


}
	
void print_menu(void)
{
		
		int desce = 10;
		// Limpa o plano de fundo com uma cor selecionada.
		ClearBackground(RAYWHITE);
			DrawText("Agar.io", 300, 10, 60, DARKGRAY);
			DrawText("Nova partida", 323, desce+100, 20, DARKGRAY);
			DrawText("Carregar partida", 300, desce+130, 20, DARKGRAY);
			DrawText("Exibir ganhadores", 300, desce+160, 20, DARKGRAY);
			DrawText("Sair", 369, desce+190, 20, DARKGRAY);


}


void nova_partida(void)
{
	while(!IsKeyDown(KEY_Q))
		ClearBackground(MAGENTA);
	



}

void carrega_partida(void)
{
	int i=0;
	ClearBackground(SKYBLUE);
	printf("TESTE\n\n\n\n\n\n\n\n\n\n\n");

}

void mostra_ganhadores(void)
{
	while(!IsKeyDown(KEY_Q))
		ClearBackground(BLACK);




}

void inicia(pCRONOMETRO c) {
    c->andando = 1;
    c->inicio = clock();
}

void para(pCRONOMETRO c) {
    if(c->andando) {
        c->andando = 0;
        c->fim = clock();
    }
}

void continua(pCRONOMETRO c) {
    if(!c->andando) {
        c->andando = 1;
        c->inicio += clock() - c->fim;
    }
}








