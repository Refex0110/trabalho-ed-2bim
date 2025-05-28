#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio2.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include <Windows.h>
#include "prioridade.h"

void menuConfiguracao(int qtdDev, int tempo);
void simulacao(int qtdDev, int tempo);
tpTicket criaTicket(FILE *arquivo){
	tpTicket ticket;
	fscanf(arquivo,"%10[^;];%d;%50[^;];%30[^;];%10[^;]\n",ticket.tipo,&ticket.tempo,ticket.tarefa,ticket.responsavel, ticket.data);
	return ticket;
}
void enviaTarefa(tpDesc &desc, FILE *arquivo, int tempo){
	printf("Chegou uma nova tarefa!\n");
	if(!feof(arquivo)){
		tpTicket ticket = criaTicket(arquivo);
		inserirTarefa(ticket, desc, tempo);
	}
}
void menuConfiguracao(int qtdDev, int tempo) {
    clrscr();
    printf("###### CONFIGURACAO DA SIMULACAO ######\n\n");
    printf("[A] Quantidade de Devs: ");
    if (qtdDev == -1) 
		printf(" (Nao definido)\n"); 
	else 
		printf(" %d\n", qtdDev);
		
    printf("[B] Tempo de Simulacao: ");
    if (tempo == -1) 
		printf("(Nao definido)\n"); 
	else 
		printf(" %d segundos\n", tempo);
    printf("\n-----------------------------------------\n");
    printf("[ENTER] Comecar Simulacao\n[ESC]   Sair\n\n");
    printf("Opcao: ");
}
char menuPausa() {
    clrscr();
    printf("--- SIMULACAO PAUSADA ---\n\n");
    printf("[A] Adicionar um Desenvolvedor\n");
    printf("[B] Remover um Desenvolvedor\n");
    printf("[C] FINALIZAR Simulacao Agora\n\n");
    printf("[ESC] Retomar Simulacao\n");
    printf("\nOpcao: ");
    return toupper(getch());
}
int main(void) {
    int qtdDev = -1;
    int tempoSimulacao = -1;
    char opcao;
    int configuracaoConcluida = 0; 
	//funciona enquanto 0
    while (configuracaoConcluida == 0) { 
        menuConfiguracao(qtdDev, tempoSimulacao);
        opcao = toupper(getch());
        switch (opcao) {
            case 'A':
                do {
                    clrscr();
                    printf("--- CONFIGURAR DESENVOLVEDORES ---\n\nDigite a quantidade inicial de DEVs: ");
                    scanf("%d", &qtdDev);
                } while (qtdDev <= 0);
                break;
            case 'B':
                 do {
					clrscr();
                    printf("--- CONFIGURAR TEMPO ---\n\nDigite o tempo total da simulacao (segundos): ");
                    scanf("%d", &tempoSimulacao);
                } while (tempoSimulacao <= 0);
                break;
            case 13: // Enter
                if (qtdDev > 0 && tempoSimulacao > 0) {
                    simulacao(qtdDev, tempoSimulacao);
                    configuracaoConcluida = 1; // fecha o while
                } 
				else{
				 	printf("Nenhum valor pode ser menor ou igual a 0\n"); 
					getch(); 
				}
                break;
            case 27: // ESC
                configuracaoConcluida = 1; // fecha o while
                break;
        }
    }
    printf("\nPrograma finalizado.\n");
    return 0;
}
int gerarIntervalo(int min, int max) {
    return rand() % (max - min + 1) + min;
}
void mensagemIdDev(tpDesc desc){
	clrscr();
	printf("Desenvolvedores em trabalho: \n");
	for(tpDev *dev = desc.inicio; dev != NULL; dev = dev->prox)
		printf("ID: %d | Tarefas: %d | Tempo: %d\n", dev->id, dev->tarefas.qtdTarefa,
		dev->tarefas.qtdTempo);
	printf("Digite 0 ou pressione [ESC] para sair");
	printf("Digite o ID do desenvolvedor que deseja excluir: ");	
}
void simulacao(int qtdDevInicial, int tempoTotal) {
	tpDesc desc;
	FILE *arquivo = fopen("tarefas.txt", "r");
	srand(time(NULL));
    int simulacaoAtiva = 1; //simulacao ativa
	if(arquivo == NULL){
		printf("\nArquivo nao encontrado!");
		getch();
	}
	else{
		char linha[1000];
		fgets(linha, sizeof(linha),arquivo);
		inicializarDesc(desc,qtdDevInicial);
		for(int i = 0; i < qtdDevInicial; i++){
			inserirDev(desc);
		}

		int tempoSimulacaoAtual =  0;
		int proximaTarefa = gerarIntervalo(2,4);
		
		printf("Iniciando simulacao...");
		Sleep(2000);
		int pausar = 0;
		while(tempoSimulacaoAtual < tempoTotal){
			clrscr();
			gotoxy(0,0);
			printf("--- SIMULACAO ---\n");
			printf("Tempo: %d de %d\n", tempoSimulacaoAtual, tempoTotal);
			printf("Desenvolvedores ativos: %d\n\n", desc.qtdDev);
			//adicionar tarefa na fila
			if(proximaTarefa <= 0){
				enviaTarefa(desc,arquivo,tempoSimulacaoAtual);
				proximaTarefa = gerarIntervalo(2,4);
				printf("Proxima tarefa em: %d segundos", proximaTarefa);
			}
			else{
				printf("Proxima tarefa em: %d segundos\n", proximaTarefa);
				proximaTarefa--;
			}
			tempoSimulacaoAtual++;
			printf("\nPRESSIONE QUALQUER TECLA PARA PAUSAR\n");
			if(kbhit()){
				pausar = 1;
			}
			while(pausar){
				char opcaoPausa = menuPausa();	
				switch(opcaoPausa){
					case 'A':
						inserirDev(desc);
						printf("Desenvolvedor Adicionado!");
						getch();
							pausar = 0;
						break;
					case 'B':
						if(!devsVazio(desc)){
							int id;
							mensagemIdDev(desc);
							scanf("%d", &id);
							if(id != 0 && id != 27){
								switch(removerDev(desc, id)){
									case 0:
										printf("Desenvolvedor com ID %d nao encontrado!\n", id);
										getch();
									break;
									case 1:
										printf("Desenvolvedor %d removido com sucesso!\n", id);
										getch();
									break;
									case 2:
										printf("Ultimo desenvolvedor. Adicione um desenvolvedor ou reinicie a simulacao");
						
										getch();
									break;
									default: printf("Erro desconhecido!");getch(); break;
								}
							}
						}
						else
							printf("Nao ha desenvolvedores para remover!");
						getch();
						pausar = 0;
						break;
					case 'C':
						tempoSimulacaoAtual = tempoTotal;
						printf("Simulacao finalizada!");
						getch();
							pausar = 0;
					break;
					case 27:
						break;
				}
			}
			Sleep(900);
		}
	
		getch();
	}
	fclose(arquivo);
	liberarTarefas(desc);
	liberarDevs(desc);
	getch();
}


