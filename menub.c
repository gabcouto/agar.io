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
		float raio;
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
	int colis[2];
	int saiu_voltou = 0;

	// #################################### FORMATO TEMPORÁRIO DE COMO ESTÃO SENDO DECLARADAS AS BOLINHAS ###########################


   	int i, teste, teste2;
	int define_bola[4], j;
	BOLA bolas[NUM_BOLAS], clayton;
	for(teste = 0; teste < 9; teste++)
	    bolas[teste].movimento = teste;
	/*for(teste2 = 1; teste2 < 10; teste2++){
	    bolas[teste2-1].posicao.x = 24*teste2;
	    bolas[teste2-1].posicao.y = 24*teste2;
	}*/

	bolas[0].posicao.x = 100;
	bolas[0].posicao.y = 60;
	bolas[1].posicao.x = 200;
	bolas[1].posicao.y = 120;
	bolas[2].posicao.x = 300;
	bolas[2].posicao.y = 180;
	bolas[3].posicao.x = 400;
	bolas[3].posicao.y = 240;
	bolas[4].posicao.x = 500;
	bolas[4].posicao.y = 300;
	bolas[5].posicao.x = 600;
	bolas[5].posicao.y = 360;
	bolas[6].posicao.x = 700;
	bolas[6].posicao.y = 400;
	bolas[7].posicao.x = 800;
	bolas[7].posicao.y = 420;
	bolas[8].posicao.x = 750;
	bolas[8].posicao.y = 440;
	/*
	for(teste2 = 0; teste < 9; teste++)
	{	
	bolas[teste2].posicao.x = 400;
	bolas[teste2].posicao.y = 400;
	}*/

	bolas[1].movimento = 0;

	clayton.posicao.x = larguraTela/2;
	clayton.posicao.y = alturaTela/2;

	// #################################### FORMATO TEMPORÁRIO DE COMO ESTÃO SENDO DECLARADAS AS BOLINHAS ###########################


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
				if(saiu_voltou)
				{
					bolas[0].posicao.x = 100;
					bolas[0].posicao.y = 60;
					bolas[1].posicao.x = 200;
					bolas[1].posicao.y = 120;
					bolas[2].posicao.x = 300;
					bolas[2].posicao.y = 180;
					bolas[3].posicao.x = 400;
					bolas[3].posicao.y = 240;
					bolas[4].posicao.x = 500;
					bolas[4].posicao.y = 300;
					bolas[5].posicao.x = 600;
					bolas[5].posicao.y = 360;
					bolas[6].posicao.x = 700;
					bolas[6].posicao.y = 400;
					bolas[7].posicao.x = 800;
					bolas[7].posicao.y = 420;
					bolas[8].posicao.x = 750;
					bolas[8].posicao.y = 440;

					saiu_voltou = 0;

				
				}

				//printf("Nova partida selecionado.\n");
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
                            /*switch()
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
                            }*/
                        //usar rand(time.h%4) depois switch case para definir movimento
						} break;
						case 2:
						{
						//movemos em uma direção fixa.
						bolas[j].posicao.x +=0.4f;

						} break;
						case 3:
						{
						//movemos em uma direção fixa.
						bolas[j].posicao.x -=0.4f;
						} break;
						case 4:
						{
						//movemos em uma direção fixa.
						bolas[j].posicao.x +=0.4f;
						bolas[j].posicao.y +=0.4f;

						} break;
						case 5:
						{
						//movemos em uma direção fixa.
						bolas[j].posicao.x -=0.4f;
						bolas[j].posicao.y +=0.4f;

						} break;
						case 6:
						{
						//movemos em uma direção fixa.
						bolas[j].posicao.y +=0.4f;

						} break;
						case 7:
						{
						//movemos em uma direção fixa.
						bolas[j].posicao.y -=0.4f;

						} break;
						case 8:
						{
						// aproximamos algumas posicoes da posicao de clayton (nossa bola)
						if(bolas[j].posicao.y>clayton.posicao.y)
						    bolas[j].posicao.y-=0.4f;
						if(bolas[j].posicao.y<clayton.posicao.y)
						    bolas[j].posicao.y+=0.4f;
						if(bolas[j].posicao.x>clayton.posicao.x)
						    bolas[j].posicao.x-=0.4f;
						if(bolas[j].posicao.x<clayton.posicao.x)
						    bolas[j].posicao.x+=0.4f;

						} break;
						default: break;
					}
					

					if(IsKeyDown(KEY_RIGHT)){
						for(j=0; j<NUM_BOLAS; j++){
							bolas[j].posicao.x-=2.0f;
						}
					}
       					if(IsKeyDown(KEY_LEFT)){
						for(j=0; j<NUM_BOLAS; j++){
							bolas[j].posicao.x+=2.0f;
						}
					}
					if(IsKeyDown(KEY_UP)){
						for(j=0; j<NUM_BOLAS; j++){
							bolas[j].posicao.y+=2.0f;
						}
					}
					if(IsKeyDown(KEY_DOWN)){
						for(j=0; j<NUM_BOLAS; j++){
							bolas[j].posicao.y-=2.0f;
						}
					}


                    			/*for(colis[0]=0; colis[0]<NUM_BOLAS-1; colis[0]++)
					{
					
						for(colis[1] = colis[0]+1; colis[1] < NUM_BOLAS; colis[1]++)
						{							
							if(CheckCollisionCircles(bolas[colis[0]].posicao, bolas[colis[0]].raio, bolas[colis[1]].posicao, bolas[colis[0]].raio))
								printf("\nbolinha %d com bolinha %d\n\n", colis[0], colis[1]);
								bolas[colis[0]].posicao.x=100000;
								bolas[colis[1]].posicao.x=100000;
								
				
						}
					}
*/
					/*for(colis[0]=0; colis[0]<NUM_BOLAS; colis[0]++)
					{
						printf("\n%d, %f, %f, %f\n", colis[0], bolas[colis[0]].posicao.x, bolas[colis[0]].posicao.y, bolas[colis[0]].raio);
						if(CheckCollisionCircles(bolas[colis[0]].posicao, bolas[colis[0]].raio, clayton.posicao, clayton.raio))
						{
							printf("\nClayton achou sua presa, a bolinha %d caiu em suas garras", colis[0]);
							bolas[colis[0]].posi2cao.x+=200.0f;
						}

					}*/

				}
				
				
			} break;
			case CARREGAR:
			{
				saiu_voltou = 0;
				arquivo = fopen("meu_agario.bin", "rb");
				fread(bolas, sizeof(BOLA), NUM_BOLAS, arquivo);
				fclose(arquivo);
				telaAtual = NOVA;
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
				saiu_voltou = 1;
				//printf("Salvar selecionado.\n");
				if(IsKeyPressed(KEY_S))
				{
					//rotina de salvar (pode ser uma função).
					arquivo = fopen("meu_agario.bin", "w+b");
					fwrite(&bolas, sizeof(BOLA), NUM_BOLAS, arquivo);
					fclose(arquivo);
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

					DrawText("Utilize as setas para se mover.",10,330,15,DARKGRAY);
					DrawText("Pressione 'TAB' para voltar ao MENU e/ou salvar partida.",10,350,15,DARKGRAY);
					DrawText("Aperte 'ENTER' para selecionar uma opção.",10,370,15,DARKGRAY);
					DrawText("A cor roxa indica que uma bola é venenosa.",10,390,15,DARKGRAY);
					DrawText("Caso o jogador encoste nela, ficará roxo por alguns segundos.",25,410,15,DARKGRAY);
					DrawText("A cor vermelha indica que uma bola é explosiva.",10,430,15,DARKGRAY);
					
					
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
						
						DrawCircle(clayton.posicao.x, clayton.posicao.y, 30, BLACK);



					for(j = 0; j<NUM_BOLAS; j++)
				{
					switch(bolas[j].movimento)
					{
						case 0:
						{
						//se estática, mantemos como está.
						DrawCircle(bolas[j].posicao.x, bolas[j].posicao.y, 20, RED);
						} break;
						case 1:
						{
						// movemos em direção laeatória.
                        //usar rand(time.h%4) depois switch case para definir movimento
                        DrawCircle(bolas[j].posicao.x, bolas[j].posicao.y, 20, GREEN);
						} break;
						case 2:
						{
						//movemos em uma direção fixa.
						DrawCircle(bolas[j].posicao.x, bolas[j].posicao.y, 20, BLUE);

						} break;
						case 3:
						{
						//movemos em uma direção fixa.
						DrawCircle(bolas[j].posicao.x, bolas[j].posicao.y, 20, BLUE);
						} break;
						case 4:
						{
						//movemos em uma direção fixa.
						DrawCircle(bolas[j].posicao.x, bolas[j].posicao.y, 20, BLUE);

						} break;
						case 5:
						{
						//movemos em uma direção fixa.
						DrawCircle(bolas[j].posicao.x, bolas[j].posicao.y, 20, BLUE);

						} break;
						case 6:
						{
						//movemos em uma direção fixa.
						DrawCircle(bolas[j].posicao.x, bolas[j].posicao.y, 20, BLUE);

						} break;
						case 7:
						{
						//movemos em uma direção fixa.
						DrawCircle(bolas[j].posicao.x, bolas[j].posicao.y, 20, BLUE);

						} break;
						case 8:
						{
						// aproximamos algumas posicoes da posicao de clayton (nossa bola)
						DrawCircle(bolas[j].posicao.x, bolas[j].posicao.y, 20, PURPLE);

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

