/*
Arthur Baumgardt & Gabriel Couto
Implementação de agar.io utilizando a biblioteca raylib.h
*/


#include "raylib.h"

#include <stdio.h>

// Defini o número de bolas como 10.
#define NUM_BOLAS 9

// Constante que nos ajuda com o loop do menu.
int count = 0;

typedef enum TelaJogo { MENU = 0, NOVA, CARREGAR, GANHADORES, SAIR, SALVAR} TelaJogo;

typedef struct scores//estrutura dos classificados
	{
   		char nome[51];
    	int score;
	}SCORES;

typedef struct bola
	{
		float raio=20;
		int velocidade;
		int tipo;
		int movimento;
		Vector2 posicao;

	} BOLA;

int main(void)
{
	// Abrimos uma janela.
	const int larguraTela = 800;
	const int alturaTela = 450;	
	int desce = 10;
	int sair = 0;
	// Declaramos coisas de arquivos.
	FILE* arquivo;
    SCORES winners[10];
   	int i, teste, teste2;
	int define_bola[4], j;
	BOLA bolas[NUM_BOLAS], clayton;
	for(teste = 0; teste < 9; teste++)
	    bolas[teste].movimento = teste;
	for(teste2 = 1; teste2 < 10; teste2++){
	    bolas[teste2-1].posicao.x = 24*teste2;
	    bolas[teste2-1].posicao.y = 24*teste2;
	}
	/*
	0: estática
	1: aleatória
	2: direcionada(horizontal djrejta)
	3: direcionada(horizontal esquerda)
	4: direcioanda (diagonald)
	5: direcionada (diagonale)
	6: direcionada (vertical cima)
	7: direcionada (vertical baixo)
	8: perseguidoras.
	
	*/
	
	
	/*define_bola[0] = GetRandomValue(1, NUM_BOLAS/2);
	printf("\n\n\n%d\n\n\n", define_bola[0]);
	for(j = 0; j<define_bola[0]; j++)
		bolas[j].movimento = 0;
	printf("\n\n%d\n\n\n", NUM_BOLAS - define_bola[0] - 2);
	define_bola[1] = GetRandomValue(1, (NUM_BOLAS - define_bola[0]-2));
	printf("\n\n\n%d\n\n\n", define_bola[1]);
	for(j = define_bola[0]; j<define_bola[1]; j++)
		{
		printf("\nBola1, %d\n", j);
		bolas[j].movimento = 1;				
		}
	define_bola[2] = GetRandomValue(1, (NUM_BOLAS - (define_bola[0] + define_bola[1])-1));	

	for(j = define_bola[1]; j<define_bola[2]; j++)
		bolas[j].movimento = 2;

	for(j = define_bola[2]; j<NUM_BOLAS; j++)
		bolas[j].movimento = 3;


	for(j = 0; j<NUM_BOLAS; j++)
		printf("%d\n", bolas[j].movimento);
    */

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
				
				for(j = 0; j<NUM_BOLAS; j++)
				{
					switch(bolas[j].movimento)
					{
						case 0:
						{
						//se estática, mantemos como está.
						} break;
						case 1:
						{
						// movemos em direção laeatória.
                            switch(/*resultado do rand()*/)
                            {
                                case 0:
						        bolas[j].posicao.y-=1.0f;
						        break;
						        case 1:
						        bolas[j].posicao.y+=1.0f;
						        break;
						        case 2:
						        bolas[j].posicao.x-=1.0f;
						        break;
						        case 3:
						        bolas[j].posicao.x+=1.0f;// no lugar de 1.0f somar a bolhas[j].velocidade na posicao   
                            }
                        //usar rand(time.h%4) depois switch case para definir movimento
						} break;
						case 2:
						{
						//movemos em uma direção fixa.
						bolas[j].posicao.x +=1.0f;

						} break;
						case 3:
						{
						//movemos em uma direção fixa.
						bolas[j].posicao.x -=1.0f;
						} break;
						case 4:
						{
						//movemos em uma direção fixa.
						bolas[j].posicao.x +=1.0f;
						bolas[j].posicao.y +=1.0f;

						} break;
						case 5:
						{
						//movemos em uma direção fixa.
						bolas[j].posicao.x -=1.0f;
						bolas[j].posicao.y +=1.0f;

						} break;
						case 6:
						{
						//movemos em uma direção fixa.
						bolas[j].posicao.y +=1.0f;

						} break;
						case 7:
						{
						//movemos em uma direção fixa.
						bolas[j].posicao.y -=1.0f;

						} break;
						case 8:
						{
						// aproximamos algumas posicoes da posicao de clayton (nossa bola)
						if(bolas[j].posicao.y>clayton.posicao.y)
						    bolas[j].posicao.y-=1.0f;
						if(bolas[j].posicao.y<clayton.posicao.y)
						    bolas[j].posicao.y+=1.0f;
						if(bolas[j].posicao.x>clayton.posicao.x)
						    bolas[j].posicao.x-=1.0f;
						if(bolas[j].posicao.x<clayton.posicao.x)
						    bolas[j].posicao.x+=1.0f;

						} break;
						default: break;
					}

                    



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
				if(!(arquivo=fopen("Ganhadores.bin","rb")))
					printf("Arquivo não encontrado.\n");
				else
					printf("Arquivo encontrado.");
				
    				//fread(winners,sizeof(SCORES),10,arquivo);
				


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
					ClearBackground(RAYWHITE);
					for(j = 0; j<NUM_BOLAS; j++)
				{
					switch(bolas[j].movimento)
					{
						case 0:
						{
						//se estática, mantemos como está.
						DrawCircle(bolas[j].posicao.x, boalas[j].posicao.y, bolas[j].raio, RED);
						} break;
						case 1:
						{
						// movemos em direção laeatória.
                        //usar rand(time.h%4) depois switch case para definir movimento
                        DrawCircle(bolas[j].posicao.x, boalas[j].posicao.y, bolas[j].raio, GREEN);
						} break;
						case 2:
						{
						//movemos em uma direção fixa.
						DrawCircle(bolas[j].posicao.x, boalas[j].posicao.y, bolas[j].raio, BLUE);

						} break;
						case 3:
						{
						//movemos em uma direção fixa.
						DrawCircle(bolas[j].posicao.x, boalas[j].posicao.y, bolas[j].raio, BLUE);
						} break;
						case 4:
						{
						//movemos em uma direção fixa.
						DrawCircle(bolas[j].posicao.x, boalas[j].posicao.y, bolas[j].raio, BLUE);

						} break;
						case 5:
						{
						//movemos em uma direção fixa.
						DrawCircle(bolas[j].posicao.x, boalas[j].posicao.y, bolas[j].raio, BLUE);

						} break;
						case 6:
						{
						//movemos em uma direção fixa.
						DrawCircle(bolas[j].posicao.x, boalas[j].posicao.y, bolas[j].raio, BLUE);

						} break;
						case 7:
						{
						//movemos em uma direção fixa.
						DrawCircle(bolas[j].posicao.x, boalas[j].posicao.y, bolas[j].raio, BLUE);

						} break;
						case 8:
						{
						// aproximamos algumas posicoes da posicao de clayton (nossa bola)
						DrawCircle(bolas[j].posicao.x, boalas[j].posicao.y, bolas[j].raio, PURPLE);

						} break;
						default: break;
					}





				}

				} break;
				case CARREGAR:
				{
					ClearBackground(SKYBLUE);



				} break;
				case GANHADORES:
				{
					ClearBackground(RAYWHITE);
					for(i=0;i<10;i++)
					{
						printf("%s, %d", winners[i].nome, winners[i].score);
       						//DrawText(i+1, 323, 100+(i*30), 11, DARKGRAY);
        					DrawText(". Nome:", 324, 100+(i*30), 11, DARKGRAY);
        					DrawText("Tadeu", 326, 101+(i*30), 11, DARKGRAY);
        					//DrawText(" Pontuacao: ", 326, 102+(i*30), 11, DARKGRAY);
       						//DrawText("Tchong4", 326, 103+(i*30), 11, DARKGRAY);
        					//DrawText("\n", 323, 104+(i*30), 11, DARKGRAY);
   					}
    					//fclose(arquivo);


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

