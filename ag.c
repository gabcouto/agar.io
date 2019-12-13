/*
Arthur Baumgardt & Gabriel Couto
Implementação de agar.io utilizando a biblioteca raylib.h
*/
// OBS: quando clicamos nova partida não está randomizando.!!!!
#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define NUM_BOLAS 150
int count = 0;    // Constante que nos ajuda com o loop do menu.

typedef enum TelaJogo { MENU = 0, NOVA, CARREGAR, GANHADORES, SAIR, SALVAR, SALVAGAN} TelaJogo; //enumeradores de tela do menu

typedef struct scores//estrutura dos classificados
	{
   		char nome[51];
    	int score;
	}SCORES;

typedef struct bola//estrutura para as bolinhas
	{
		float raio;
		float velocidade;
		int tipo;
		int movimento;
		Vector2 posicao;
	} BOLA, *pBOLA;

void le_dificuldade(int,pBOLA);//prototipos
void move_bolas(pBOLA,pBOLA);
void reseta_bolas(pBOLA,int);
void rdm_pstn_rds(pBOLA);
void zoom(pBOLA,pBOLA);

int main(void)
{
	// Abrimos uma janela.
    
	int contaFrames = 0, pontos = 0, pos = 0, desce = 10, sair = 0;
	const int larguraTela = 800, alturaTela = 450;	
    
	// Declaramos coisas de arquivos.
    
	FILE* arquivo;
    SCORES winners[10];
    
    //Declaramos variaveis de jogabilidade
    
	int colis[2], saiu_voltou = 0, carregou_ganhadores = 0, naoconta = 1, k, tecla = 0, contaletra = 0, j, tempoSemComer = 0, come = 1;
	char nomejogador[51]={};
	BOLA bolas[NUM_BOLAS], clayton;
	
    srand(time(NULL));

	reseta_bolas(bolas, NUM_BOLAS);
	clayton.posicao.x = larguraTela/2;
	clayton.posicao.y = alturaTela/2;
	clayton.raio=30;

	// Esta função abre uma janela com um nome dado por uma string.
	InitWindow(larguraTela, alturaTela, "Agar.io");
	
	// Definimos a quantidade de FPS.
	SetTargetFPS(60);
	
	// Escolhemos a posição inicial 
	TelaJogo telaAtual = MENU;

	while(!WindowShouldClose() && sair == 0)// enquanto nao for detectado o 'ESC', 'X' da janela ou o botao sair nao for apertado
	{
		contaFrames++;// conta frames para podermos contar os pontos
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
					for(j = 0; j < NUM_BOLAS; j++)
						bolas[j].velocidade += 0.001f;
				}	
                
				zoom(bolas,&clayton);
				/*Esta checagem de condição tem como objetivo zerar as posições das bolas e a pontuação caso o jogador tenha decidido jogar novamente em uma mesma execução no programa.*/
				if(saiu_voltou)
				{
					reseta_bolas(bolas, NUM_BOLAS);
					clayton.raio = 30; // Raio da nossa bola principal é sempre 30 no início da partida.
					pontos = 0;
					tempoSemComer = 0;
					saiu_voltou = 0;
				}
				if(IsKeyPressed(KEY_TAB))
				{
					telaAtual = SALVAR;
					//telaAtual = MENU;
				}
                move_bolas(bolas,&clayton);
				for(j = 0; j<NUM_BOLAS; j++)
				{
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

					if(tempoSemComer <= pontos)
						come = 1;

			
                    for(colis[0]=0; colis[0]<NUM_BOLAS-1; colis[0]++)
					{
						for(colis[1] = colis[0]+1; colis[1] < NUM_BOLAS; colis[1]++)
						{							
							if(CheckCollisionCircles(bolas[colis[0]].posicao, bolas[colis[0]].raio, bolas[colis[1]].posicao, bolas[colis[1]].raio))
							{
								if((bolas[colis[0]].tipo==0)&&(bolas[colis[1]].tipo==0))
                                {
                                    rdm_pstn_rds(&bolas[colis[0]]);
                                    rdm_pstn_rds(&bolas[colis[1]]);
                                }
                                if((bolas[colis[0]].raio>bolas[colis[1]].raio)||(bolas[colis[0]].tipo==0))
								{
                                    if((bolas[colis[0]].tipo!=0)&&(bolas[colis[0]].raio<70))
                                        bolas[colis[0]].raio+=(bolas[colis[1]].raio)/10;
                                    if(bolas[colis[1]].tipo!=0)
                                    {
                                        rdm_pstn_rds(&bolas[colis[1]]);
                                    }
								}

								if((bolas[colis[0]].raio<bolas[colis[1]].raio)||(bolas[colis[1]].tipo==0))
								{
                                    if((bolas[colis[1]].tipo!=0)&&(bolas[colis[1]].raio<70))
                                        bolas[colis[1]].raio+=(bolas[colis[1]].raio)/10;
                                    if(bolas[colis[0]].tipo!=0)
                                    {
                                        rdm_pstn_rds(&bolas[colis[0]]);
                                    }
								}

                           	}
						}
					}

					for(colis[0]=0; colis[0]<NUM_BOLAS; colis[0]++)
					{
                        if(CheckCollisionCircles(bolas[colis[0]].posicao, bolas[colis[0]].raio, clayton.posicao, clayton.raio))
						{
							if((bolas[colis[0]].raio>clayton.raio)||(bolas[colis[0]].tipo==0))
								{
									telaAtual = MENU;
									//clayton dies +
								}
							
	
							if(come)
							{
								if((bolas[colis[0]].raio<clayton.raio)&&(bolas[colis[0]].tipo!=0))
								{
									rdm_pstn_rds(&bolas[colis[0]]);
									clayton.raio+=(bolas[colis[0]].raio)/10;
									if(bolas[colis[0]].tipo==2)
									{
										tempoSemComer = pontos + 5;
										come = 0;
										//pintar clayto e n deixa come bola
										
									}
								}
							}						
						}
					}
				}
			} break;
			case CARREGAR:
			{
				saiu_voltou = 0;
				arquivo = fopen("meu_agario.bin", "rb");
				fread(bolas, sizeof(BOLA), NUM_BOLAS, arquivo);
				fread(&clayton, sizeof(BOLA), 1, arquivo);
				fread(&pontos,sizeof(int),1,arquivo);
				fclose(arquivo);
				le_dificuldade(pontos,bolas);
				telaAtual = NOVA;
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
					arquivo=fopen("Ganhadores.bin","rb");
    				fread(winners,sizeof(SCORES),10,arquivo);
					fclose(arquivo);
					carregou_ganhadores = 1;
					/* não queremos abrir o arquivo n vezes durante o periodo em que o switch GANHADORES está selecionado. Então, abrimos o arquivo apenas 1 vez por cada execução desta seção do menu.*/
				}
			} break;
			case SAIR:
			{
				sair = 1; 
			} break;
			case SALVAR:
			{
				saiu_voltou = 1;
				if(IsKeyPressed(KEY_S))
				{
					//rotina de salvar (pode ser uma função).
					arquivo = fopen("meu_agario.bin", "w+b");
					fwrite(&bolas, sizeof(BOLA), NUM_BOLAS, arquivo);
					fwrite(&clayton, sizeof(BOLA), 1, arquivo);
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
				arquivo=fopen("Ganhadores.bin","a+b");
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
				if(IsKeyPressed(KEY_TAB))
				{
					telaAtual = MENU;
				}

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
						if(come == 0)
							DrawCircle(clayton.posicao.x, clayton.posicao.y, clayton.raio, DARKPURPLE);
						else
							DrawCircle(clayton.posicao.x, clayton.posicao.y, clayton.raio, BLACK);
					
					for(j = 0; j<NUM_BOLAS; j++)
                    {
                        switch(bolas[j].tipo)
                        {
                            case 0:
                            {
                                DrawCircle(bolas[j].posicao.x, bolas[j].posicao.y, bolas[j].raio, RED);
                            } break;
                            case 1:
                            {
                                DrawCircle(bolas[j].posicao.x, bolas[j].posicao.y, bolas[j].raio, GREEN);
                            } break;
                            case 2:
                            {
                                DrawCircle(bolas[j].posicao.x, bolas[j].posicao.y, bolas[j].raio, PURPLE);
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
				} break; 
				case SALVAGAN:
				{
					ClearBackground(RAYWHITE);
					DrawText("Tu morreu", 150, desce+100, 30, DARKGRAY);

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
        	bolas[i].velocidade+=0.001f;
            printf("bola: %d\nvelocidade: %f\n\n", i, bolas[i].velocidade);
    	}
    	le_dificuldade(pontos-10,bolas);
    }
}

void move_bolas(pBOLA bolas,pBOLA clayton)
{
    int j;
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
    
    for(j = 0; j<NUM_BOLAS; j++)
	{
        switch(bolas[j].movimento)
		{
			case 1:
			{
			// movemos em direção laeatória.
                switch(rand()%4)
               	{
                    case 0:
						bolas[j].posicao.y-=bolas[j].velocidade;
						break;
					case 1:
						bolas[j].posicao.y+=bolas[j].velocidade;
						break;
					case 2:
						bolas[j].posicao.x-=bolas[j].velocidade;
						break;
					case 3:
						bolas[j].posicao.x+=bolas[j].velocidade;
                }
            } break;
			case 2:
			{
			//movemos em uma direção fixa.
                bolas[j].posicao.x +=bolas[j].velocidade;
			} break;
			case 3:
			{
            //movemos em uma direção fixa.
                bolas[j].posicao.x -=bolas[j].velocidade;
			} break;
			case 4:
			{
             //movemos em uma direção fixa.
                bolas[j].posicao.x +=bolas[j].velocidade;
               	bolas[j].posicao.y +=bolas[j].velocidade;
			} break;
			case 5:
			{
			//movemos em uma direção fixa.
                bolas[j].posicao.x -=bolas[j].velocidade;
                bolas[j].posicao.y +=bolas[j].velocidade;
			} break;
            case 6:
			{
			//movemos em uma direção fixa.
                bolas[j].posicao.y +=bolas[j].velocidade;
			} break;
			case 7:
			{
			//movemos em uma direção fixa.
                bolas[j].posicao.y -=bolas[j].velocidade;
			} break;
			case 8:
			{
			// aproximamos algumas posicoes da posicao de clayton (nossa bola)
                if(bolas[j].posicao.y>clayton->posicao.y)
                    bolas[j].posicao.y-=bolas[j].velocidade;
                if(bolas[j].posicao.y<clayton->posicao.y)
                    bolas[j].posicao.y+=bolas[j].velocidade;
                if(bolas[j].posicao.x>clayton->posicao.x)
                    bolas[j].posicao.x-=bolas[j].velocidade;
                if(bolas[j].posicao.x<clayton->posicao.x)
                    bolas[j].posicao.x+=bolas[j].velocidade;
			} break;
			default: break;
		}
    }
}

void reseta_bolas(pBOLA bolas, int n)
{
    int j, maxred=0;
    
    srand(time(NULL));
    
    for(j=0;j<n;j++)//ramdomizamos o raio, 
    {
        bolas[j].movimento = rand()%9;
        bolas[j].velocidade = ((float)(rand()%10))/10;
        bolas[j].tipo = rand()%3;
        if(bolas[j].tipo ==0)
        {
            maxred++;
            if(maxred==35)
            {
                bolas[j].tipo = (rand()%2)+1;
                maxred--;
            }
        }
        rdm_pstn_rds(&bolas[j]);
    }
}

void rdm_pstn_rds(pBOLA bola)
{
    
    bola->posicao.x=rand()%2500;//mudamos a posicao x e y da bola 
	bola->posicao.y=rand()%2500;
	bola->raio=(rand()%30)+10;//ramdomizamos o raio entre 10 e 40
}

void zoom(pBOLA bolas, pBOLA clayton)
{
    int j;
    
    if(clayton->raio>70)
	{
        clayton->raio-=30;
        for(j=0;j<NUM_BOLAS;j++)
        {
            bolas[j].raio-=30;
            if(bolas[j].raio<=0)
            {
                rdm_pstn_rds(&bolas[j]);
            }
        }	         
	}
}
