/*
Arthur Baumgardt & Gabriel Couto
Implementação de agar.io utilizando a biblioteca raylib.h
*/


#include "raylib.h"

#include <stdio.h>

// Constante que nos ajuda com o loop do menu.
int count = 0;

typedef enum TelaJogo { MENU = 0, NOVA, CARREGAR, GANHADORES, SAIR, SALVAR} TelaJogo;

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
	
	// Escolhemos a posição inicial 
	TelaJogo telaAtual = MENU;

	while(!WindowShouldClose() && sair == 0)
	{
		switch(telaAtual)
		{
			case MENU:
			{
				if(IsKeyPressed(KEY_DOWN))
					count++;
				if(IsKeyPressed(KEY_UP))
			         	count--;				
				if(count > 3)
					count = 0;
				if(count < 0)
					count = 3;
				if(IsKeyPressed(KEY_ENTER))
					telaAtual = count +1;

			} break;
			case NOVA:
			{	
				printf("Nova partida selecionado.\n");
				if(IsKeyPressed(KEY_TAB))
				{
					telaAtual = SALVAR;
					//telaAtual = MENU;
				}
			} break;
			case CARREGAR:
			{
				printf("Carregar partida selecionado.\n");
				if(IsKeyPressed(KEY_TAB))
					telaAtual = MENU;


			} break;
			case GANHADORES:
			{
				printf("Ganhadores selecionado.\n");
				if(IsKeyPressed(KEY_TAB))
					telaAtual = MENU;


			} break;
			case SAIR:
			{
				printf("Sair selecionado.\n");
					sair = 1; 



			} break;
			case SALVAR:
			{
				printf("Salvar selecionado.\n");
				if(IsKeyPressed(KEY_S))
				{
					//rotina de salvar (pode ser uma função).
					telaAtual = MENU;
				}
				else if(IsKeyPressed(KEY_N))
					telaAtual = MENU;
			}
			default: break;		
			
		}
		
		//Somente no trecho abaixo lidamos com desenhos
		BeginDrawing();
			
			switch(telaAtual)
			{
				case MENU:
				{
					ClearBackground(RAYWHITE);
					DrawText("Agar.io", 300, 10, 60, DARKGRAY);
					DrawText("Nova partida", 323, desce+100, 20, DARKGRAY);
					DrawText("Carregar partida", 300, desce+130, 20, DARKGRAY);
					DrawText("Exibir ganhadores", 300, desce+160, 20, DARKGRAY);
					DrawText("Sair", 369, desce+190, 20, DARKGRAY);
					
					switch(count)
					{
						case 0:
							DrawText("Nova partida", 323, desce+100, 20, LIGHTGRAY);
							break;
						case 1:
							DrawText("Carregar partida", 300, desce+130, 20, LIGHTGRAY);
							break;
						case 2:
							DrawText("Exibir ganhadores", 300, desce+160, 20, LIGHTGRAY);
							break;
						case 3:
							DrawText("Sair", 369, desce+190, 20, LIGHTGRAY);

					}
				} break;
				case NOVA:
				{	
					ClearBackground(MAGENTA);


				} break;
				case CARREGAR:
				{
					ClearBackground(SKYBLUE);



				} break;
				case GANHADORES:
				{
					ClearBackground(BLACK);



				} break;
				case SAIR:
				{
					



				} break;
				case SALVAR:
				{
					ClearBackground(RAYWHITE);
					DrawText("Deseja salvar a partida? [S/N]", 150, desce+100, 30, DARKGRAY);					
				

				}
				default: break;		
			
			}
			
		// Terminamos a escrita na tela
		EndDrawing();
	}		

	return 0;

}

