#include <string.h>
struct tpTicket{
	char 
	tipo[10],
	tarefa[50],
	responsavel[30],
	data[10];
	int tempo;
};
struct tpTarefa {
    int tipo;
    int tempo;
    int tempo_chegada;
    char nome_tarefa[50];
    char responsavel[50];
    char data[11];
    tpTarefa *prox, *ant;
};

struct descTarefa {
    int qtdTarefa, qtdTempo;
    tpTarefa *inicio, *fim;
};
struct tpDev {
    int id;
    descTarefa tarefas;
    tpDev *prox;
};
struct tpDesc {
    int qtdDev, qtdID;
    tpDev *inicio, *fim;
};
tpDev *menorCargaRemover(tpDesc &desc, tpDev *devExcluir);
void redistribuirTarefa(tpDev *dev, tpTarefa *tarefa);
int verificaPrioridade(char prioridade[10]) {
    if (stricmp(prioridade, "Importante") == 0)
        return 3;
    else if (stricmp(prioridade, "Melhoria") == 0)
        return 2;
    else
        return 1;
}
tpTarefa *criaTarefa(tpTicket ticket, int chegada) {
    tpTarefa *tarefa = new tpTarefa;
    tarefa->tipo = verificaPrioridade(ticket.tipo);
    tarefa->tempo = ticket.tempo;
    tarefa->tempo_chegada = chegada;
    strcpy(tarefa->responsavel, ticket.responsavel);
    strcpy(tarefa->data, ticket.data);
    strcpy(tarefa->nome_tarefa, ticket.tarefa);
    tarefa->prox = tarefa->ant = NULL;
    return tarefa;
}

tpDev *criaDev(int id) {
    tpDev *dev = new tpDev;
    dev->id = id;
    dev->prox = NULL;
    dev->tarefas.fim = dev->tarefas.fim = NULL; 
    dev->tarefas.qtdTarefa = dev->tarefas.qtdTempo = 0;
    return dev;
}

void inicializarDesc(tpDesc &desc, int qtdDevs) {
    desc.qtdDev  = qtdDevs;
    desc.qtdID = 0;
    desc.inicio = desc.fim = NULL;
}

char devsVazio(tpDesc desc) {
    return desc.inicio == NULL;
}
char tarefasVazio(descTarefa tarefas){
	return tarefas.inicio == NULL;
}
void inserirDev(tpDesc &desc) {
    tpDev *dev = criaDev(desc.qtdID+1);
    if (devsVazio(desc)) {
        desc.inicio = desc.fim = dev;
    } else {
        desc.fim->prox = dev;
        desc.fim = dev;
    }
    desc.qtdID++;
}

tpDev *devMenorCarga(tpDesc &desc) {
   tpDev *temporario = desc.inicio->prox;
   tpDev *devMenor = desc.inicio;
	
    // Verifica até achar um desocupado
    while(temporario != NULL){
		if(temporario->tarefas.qtdTempo < devMenor->tarefas.qtdTempo)
			devMenor = temporario;
		temporario = temporario->prox;
	}
	return devMenor;
}
void inserirTarefaOrdenada(tpDev *dev, tpTarefa *tarefa) {
    tarefa->prox = tarefa->ant = NULL; 

    if (tarefasVazio(dev->tarefas)) {
        dev->tarefas.inicio = dev->tarefas.fim = tarefa;
    }
    else if (tarefa->tipo > dev->tarefas.inicio->tipo) {
        tarefa->prox = dev->tarefas.inicio;
        dev->tarefas.inicio->ant = tarefa;
        dev->tarefas.inicio = tarefa;
    }
    else if (tarefa->tipo <= dev->tarefas.fim->tipo) {
        tarefa->ant = dev->tarefas.fim;
        dev->tarefas.fim->prox = tarefa;
        dev->tarefas.fim = tarefa;
    }
    else {
        tpTarefa *posicao = dev->tarefas.inicio;
        while (posicao != NULL && posicao->tipo >= tarefa->tipo) {
            posicao = posicao->prox;
        }
        tarefa->prox = posicao;
        tarefa->ant = posicao->ant;
        posicao->ant->prox = tarefa;
        posicao->ant = tarefa;
    }

    dev->tarefas.qtdTarefa++;
    dev->tarefas.qtdTempo += tarefa->tempo;
}
void inserirTarefa(tpTicket ticket, tpDesc &desc, int chegada) {
    tpDev *dev = devMenorCarga(desc);
    tpTarefa *tarefa = criaTarefa(ticket, chegada);
    inserirTarefaOrdenada(dev, tarefa);
}

void redistribuirTarefa(tpDev *dev, tpTarefa *tarefa){
	inserirTarefaOrdenada(dev, tarefa);
}


tpDev *menorCargaRemover(tpDesc &desc, tpDev *devExcluir){
	tpDev *menor = NULL;
	tpDev *atual = desc.inicio;
	while(atual != NULL){
		if(atual == devExcluir)
			atual = atual->prox;
		else{
			if(menor == NULL){
				menor = atual;
			}
			else
				if(menor->tarefas.qtdTempo > atual->tarefas.qtdTempo){
					menor = atual;	
				}
			atual = atual->prox;
		}
	}	
	return menor;
}
int removerDev(tpDesc &desc, int idRemover){
	//busca o dev com o devido ID
	tpDev *devID = desc.inicio;
	tpDev *anterior = NULL;
	//busca o dev com o devido ID
	while (devID != NULL && devID->id != idRemover){
		anterior = devID;
		devID = devID->prox;
	}
	//se o dev apontar para NULL, o id não foi encontrado
	if(devID == NULL)
		return 0;
	//redistribuir tarefas
	// se o dev tiver tarefas, pega a tarefa atual para entregar para outro dev
	if(!tarefasVazio(devID->tarefas)){
		//se tem apenas um dev, as tarefas não podem ser perdidas
		if(desc.qtdDev == 1)
			return 2;
		else{
			while(!tarefasVazio(devID->tarefas)){
				tpTarefa *tarefa = devID->tarefas.inicio;
				//define outro ponteiro para não perder a tarefa
				devID->tarefas.inicio = devID->tarefas.inicio->prox;
				devID->tarefas.qtdTarefa--;
				devID->tarefas.qtdTempo -= tarefa->tempo;
				//encontrar dev com menor carga
				tpDev *menor = menorCargaRemover(desc,devID) ;
				//se o com menor não tem tarefas, ele recebe a primeira tarefa no inicio e fim do descritor
				if(menor != NULL)
					redistribuirTarefa(menor, tarefa);
			}
			//remove o dev
			if(anterior == NULL)
				desc.inicio = devID->prox;
			else
				anterior->prox = devID->prox;
			if(devID == desc.fim)
				desc.fim = anterior;
			delete devID;
			desc.qtdDev--;
			desc.qtdID--;
			return 1;
		}
	}

}
void removerTarefa(descTarefa &tarefas){
	tpTarefa *tarefa = tarefas.inicio;
	if(tarefas.inicio == tarefas.fim)
		delete tarefa;
	else{
		tpTarefa *atual = tarefa->prox;
		tarefa = atual;
		atual->ant->prox = NULL;
		delete atual->ant;
		atual->ant = NULL;
	}

}
void liberarTarefas(tpDesc &desc){
	tpTarefa *tarefas = desc.inicio->tarefas.inicio;
	tpDev *dev = desc.inicio;
	while(dev != NULL){
		while(!tarefasVazio(desc.inicio->tarefas)){
			removerTarefa(desc.inicio->tarefas);
		}
		dev = dev->prox;
	}	
	
}
void liberarDevs(tpDesc &desc){
	tpDev *dev = desc.inicio;
	tpDev *atual = dev->prox;
	liberarTarefas(desc);
	while(dev !=NULL){
		if(dev == desc.fim)
			delete dev;
		else{
			delete dev;
			desc.inicio = atual;
			dev = atual;
			atual = atual->prox;
		}
	}
	
}
