#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include "prioridade.h"
struct tpTicket{
	char 
	tipo[10],
	tarefa[50],
	responsavel[30],
	data[10];
	int tempo;
};
ticket criaTicket(FILE *arquivo){
	tpTicket ticket;
	fscanf(arquivo,"%10[^;];%d;%50[^;];%30[^;];%10[^;]\n",tarefa.tipo,tarefa.tempo,
	tarefa.tarefa,tarefa.responsavel, tarefa.data);
	return ticket;
}

char menu(){
	char opcao;
	clrscr();
	do{
	printf("[A] Inserir Devs\n");
	printf("[B] Retirar Devs\n");
	printf("[C]Parar simulacao\n");
	printf("[ESC] Retomar simulacao\n");
	}while(opcao != 27);
	
}
void inserirDev(tpDesc &desc, int &qtdDev){
	int qtdDesejada;
	printf("Deseja inserir quantos devs? Disponiveis(%d)", qtdDev);
	scanf("&d", &qtdDesejada;
	while(qtdDesejada < 0 || qtdDesejada > qtdDev)
	{
		clrscr();
		printf("Deseja inserir quantos devs? Disponiveis(%d)", qtdDev);	
		scanf("&d", &qtdDesejada;
	}
	for(int i = 0; i < qtdDesejada, i++)
		inserirDev(desc)
	qtdDev -= qtdDesejada;
}
void simulacao(){
	int qtdDev, devs, tempoSimulacao;
	tpDesc desc; 
	tpTicket ticket;
	char linha [1000];
	FILE *arquivo = fopen("tarefas.txt", "r");
	if(arquivo != NULL)
	}
		printf("Difite a quantidade de tempo para a simulacao: ");
		scanf("%d", &tempoSimulacao);
		while(tempoSimulacao < 0){
			clrscr();
			printf("Difite a quantidade de tempo para a simulacao: ");
			scanf("%d", &tempoSimulacao);
		}
		printf("Tempo de simulacao: %d", tempoSimulacao);
		printf("Digite a quantidade de desenvolvedores");
		scanf("%d", &qtdDev);
		while(qtdDev < 0){
			clrscr();
			printf("Tempo de simulacao: %d", tempoSimulacao);
			printf("Digite a quantidade de desenvolvedores");
			scanf("%d", &qtdDev);
		}
		inicializar(desc, qtdDev);
		//elimina a primeira linha com  nomenclatura
		fgets(linha, sizeof(linha), arquivo);
		while(tempoSimulacao > 0){
			menu();
			do{
					
					
			}while(!kbhit());
	
		}
	}
	else
		printf("\nArquivo nao encontrado");
}

