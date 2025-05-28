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
int main(){
	tpDesc desc;
	FILE *arquivo = fopen("tarefas.txt", "r");
	char linha[1000];
	fgets(linha, sizeof(linha),arquivo);
	printf("OI");
	inicializarDesc(desc, 1);
	printf("DEv 1");
	inserirDev(desc);
	enviaTarefa(desc,arquivo,10);
	fgets(linha, sizeof(linha),arquivo);
	printf("ID  %d \nTarefas %d\n ", desc.inicio->id, desc.inicio->tarefas.qtdTempo);
	printf("Tarefa: %s", desc.inicio->tarefas.inicio->nome_tarefa);
	liberarDevs(desc);
	printf("ID  %d Tarefas %d ", desc.inicio->id, desc.inicio->tarefas.qtdTempo);

}
