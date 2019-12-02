/*
Arthur Baumgardt & Gabriel Couto
Implementação de agar.io utilizando a biblioteca raylib.h
*/

#include "raylib.h"
#include <stdio.h>
#include <string.h>
#define NUM_BOLAS 9
int count = 0;    // Constante que nos ajuda com o loop do menu.

typedef enum TelaJogo { MENU = 0, NOVA, CARREGAR, GANHADORES, SAIR, SALVAR, SALVAGAN} TelaJogo;

typedef struct scores//estrutura dos classificados
	{
   		char nome[51];
    	int score;
	}SCORES;

typedef struct bola
	{
		float raio;
		float velocidade;
		int tipo;
		int movimento;
		Vector2 posicao;
	} BOLA, *pBOLA;

void le_dificuldade(int,pBOLA);

int main(void)
{
	// Abrimos uma janela.
    
	int contaFrames = 0, pontos = 0, pos = 0, desce = 10, sair = 0;
	const int larguraTela = 800, alturaTela = 450;	
    
	// Declaramos coisas de arquivos.
    
	FILE* arquivo;
    SCORES winners[10];
	int colis[2], saiu_voltou = 0, carregou_ganhadores = 0, naoconta = 1, k, tecla = 0, contaletra = 0;
	char nomejogador[51]={};
	float velteste = 0.4f;


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
		contaFrames++;
		if(!(contaFrames % 120))
		{
			pontos++;
		}
		switch(telaAtual)
		{
			case MENU:
			{	
				carregou_ganhadores = 0;
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
				if(!(pontos % 10) && pontos != 0)
				{
					/*Se a pontuação for divisível por 10, incrementamos a velocidade.*/
					velteste += 0.001f;	
				}
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
					pontos = 0;
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
                            bolas[j].posicao.x +=velteste;
						} break;
						case 3:
						{
						//movemos em uma direção fixa.
                            bolas[j].posicao.x -=velteste;
						} break;
						case 4:
						{
						//movemos em uma direção fixa.
                            bolas[j].posicao.x +=velteste;
                            bolas[j].posicao.y +=velteste;
						} break;
						case 5:
						{
						//movemos em uma direção fixa.
                            bolas[j].posicao.x -=velteste;
                            bolas[j].posicao.y +=velteste;
						} break;
						case 6:
						{
						//movemos em uma direção fixa.
                            bolas[j].posicao.y +=velteste;
						} break;
						case 7:
						{
						//movemos em uma direção fixa.
                            bolas[j].posicao.y -=velteste;
						} break;
						case 8:
						{
						// aproximamos algumas posicoes da posicao de clayton (nossa bola)
                            if(bolas[j].posicao.y>clayton.posicao.y)
                                bolas[j].posicao.y-=velteste;
                            if(bolas[j].posicao.y<clayton.posicao.y)
                                bolas[j].posicao.y+=velteste;
                            if(bolas[j].posicao.x>clayton.posicao.x)
                                bolas[j].posicao.x-=velteste;
                            if(bolas[j].posicao.x<clayton.posicao.x)
                                bolas[j].posicao.x+=velteste;
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
                    for(colis[0]=0; colis[0]<NUM_BOLAS-1; colis[0]++)
					{
						for(colis[1] = colis[0]+1; colis[1] < NUM_BOLAS; colis[1]++)
						{							
							if(CheckCollisionCircles(bolas[colis[0]].posicao, 20, bolas[colis[1]].posicao, 20))
							{
								bolas[colis[0]].posicao.x+=20.0f;
								bolas[colis[1]].posicao.x-=20.0f;
                            }
						}
					}

					for(colis[0]=0; colis[0]<NUM_BOLAS; colis[0]++)
					{
						clayton.raio=30;
                        if(CheckCollisionCircles(bolas[colis[0]].posicao, 20, clayton.posicao, clayton.raio))
						{
							bolas[colis[0]].posicao.x+=20.0f;
						}
					}
				}
			} break;
			case CARREGAR:
			{
				saiu_voltou = 0;
				arquivo = fopen("meu_agario.bin", "rb");
				fread(bolas, sizeof(BOLA), NUM_BOLAS, arquivo);
				fread(&pontos,sizeof(int),1,arquivo);
				fclose(arquivo);
				le_dificuldade(pontos,bolas);
				telaAtual = NOVA;
				printf("Carregar partida selecionado.\n");
				if(IsKeyPressed(KEY_TAB))
                    telaAtual = MENU;
			} break;
			case GANHADORES:
			{
				if(IsKeyPressed(KEY_TAB))
				{
					telaAtual = MENU;
				}
				if(carregou_ganhadores == 0)
				{	
					printf("Ganhadores selecionado.\n");
					arquivo=fopen("Ganhadores.bin","rb");
    				fread(winners,sizeof(SCORES),10,arquivo);
					for(j=0; j<10; j++)
					{
						printf("\n%d, %s\n", winners[j].score, winners[j].nome);
					}
					fclose(arquivo);
					carregou_ganhadores = 1;
					/* não queremos abrir o arquivo n vezes durante o periodo em que o switch GANHADORES está selecionado. Então, abrimos o arquivo apenas 1 vez por cada execução desta seção do menu.*/
				}
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
					fwrite(&pontos,sizeof(int),1,arquivo);
					fclose(arquivo);
					telaAtual = MENU;
				}
				else if(IsKeyPressed(KEY_N))
				{
					telaAtual = SALVAGAN;
				}
			} break;
			case SALVAGAN:
			{
				printf("\n%d\n",pontos);
				arquivo=fopen("Ganhadores.bin","rb");
				fread(winners,sizeof(SCORES),10,arquivo);
				for(j=0;(j<10)&&(naoconta);j++)
				{
					printf("\nScore: %d\n",winners[j].score);
   					if(pontos>winners[j].score)
    				{
     				   	for(k=9;k>j;k--)
      					{
            				strcpy(winners[k].nome,winners[k-1].nome);
            				winners[k].score=winners[k-1].score;
        				}
       			 		tecla=GetKeyPressed();
        				while(tecla>0)
        				{
            				if((tecla >= 32) && (tecla <= 125) && (contaletra < 50))
            				{
                				nomejogador[contaletra]=(char)tecla;
                				contaletra++;
            				}
            				tecla=GetKeyPressed();
        				}
        				if (IsKeyPressed(KEY_BACKSPACE))
        				{
            				contaletra--;
            				nomejogador[contaletra] = '\0';
            				if (contaletra < 0) contaletra = 0;
        				}
        				strcpy(nomejogador,winners[j].nome);
        				winners[j].score=pontos;
        				naoconta=0;
    				}
				}
				fwrite(winners,sizeof(SCORES),10,arquivo);
				fclose(arquivo);
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
						DrawText(FormatText("Pontos: %d", pontos), 10, 10, 17, BLACK);
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
				} break;
				case GANHADORES:
				{
					ClearBackground(RAYWHITE);          
					DrawText("Agar.io", 300, 10, 60, DARKGRAY);
   					DrawText("Classificação", 303, 65, 30, DARKGRAY);
					DrawText("Nome:", 230, 130, 25, DARKGRAY);
					DrawText("Pontuação:", 490, 130, 25, DARKGRAY);					
					pos = 0;
    				for(j=0;(j<10);j++)
   					{
      					DrawText(TextFormat("%s", winners[j].nome), 230, 160+pos, 20, DARKGRAY);
                        DrawText(TextFormat("%d", winners[j].score), 555, 160+pos, 20, DARKGRAY);
     					pos+=20;
   					}
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

void le_dificuldade(int pontos, BOLA* bolas)
{
	int i;
    
    if(pontos>=10)
    {
	    for(i=0;i<NUM_BOLAS;i++)
		{
        	bolas[i].velocidade+=0.4f;
            printf("bola: %d\nvelocidade: %f\n\n", i, bolas[i].velocidade);
    	}
    	le_dificuldade(pontos-10,bolas);
    }
}