#include <stdio.h>
#include <string.h>
typedef struct scores//estrutura dos classificados
	{
   		char nome[51];
    	int score;
	}SCORES;

int main()
{
	int i;
	SCORES winners[10];
	FILE *arquivo;
	arquivo = fopen("Ganhadores.bin", "a+b");
	for(i=0; i<10; i++)
	{	
		winners[i].score = 10;
		scanf("%s", winners[i].nome);

	}

	fwrite(&winners, sizeof(SCORES), 10, arquivo);
	fclose(arquivo);

	printf("\n\n\n\n\n");

	

}
