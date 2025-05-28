struct tpDesc {
    int qtdDev;
    tpDev *inicio, *fim;
};

struct tpDev {
    int id;
    descTarefa tarefas;
    tpDev *prox;
};

struct descTarefa {
    int qtdTarefa, qtdTempo;
    tpTarefa *inicio, *fim;
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

int verificaPrioridade(char prioridade[10]);
void inicializarTarefa(tp &dev);
tpDev *menorCargaRemover(tpDesc desc, tpDev *devExcluir);
void redistribuirTarefa(tpDev *dev, tpTarefa *tarefa);

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
	inicializarTarefa(dev);
    return dev;
}

void inicializarDesc(tpDesc &desc, int qtdDevs) {
    desc.qtdDev = qtdDevs;
    desc.inicio = desc.fim = NULL;
}
void inicializarTarefa(tpDev &dev){
	dev.tarefas.inicio = dev.tarefas.fim = NULL;
	dev.qtdTarefa = dev.qtdTempo =  0;
}
char devsVazio(tpDesc desc) {
    return desc.inicio == NULL;
}

void inserirDev(tpDesc &desc) {
    tpDev *dev = criaDev(desc.qtdDev + 1);
    if (devsVazio(desc)) {
        desc.inicio = desc.fim = dev;
    } else {
        desc.fim->prox = dev;
        desc.fim = dev;
    }
}

int verificaPrioridade(char prioridade[10]) {
    if (stricmp(prioridade, "Importante") == 0)
        return 3;
    else if (stricmp(prioridade, "Melhoria") == 0)
        return 2;
    else
        return 1;
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
void inserirTarefa(tpTicket ticket, tpDesc &desc, int chegada) {
    tpDev *dev = devMenorCarga(desc);
    tpTarefa *tarefa = criaTarefa(ticket, chegada);
    tpTarefa *tarefaAtual = dev->tarefas.inicio;
    // Inserção de acordo com a prioridade
    if(dev->tarefas.inicio == NULL){
    	dev->tarefas.inicio = dev->tarefas.fim = tarefa;
	}
	else{
		if(dev->tarefas.inicio->tipo < tarefa->tipo){
			dev->tarefas.inicio->ant = tarefa;
			tarefa->prox = dev->tarefas.inicio;
			dev->tarefas.inicio = tarefa;
		}
		else{
			if(dev->tarefas.fim->tipo <= tarefa->tipo){
				tarefa->ant = dev->tarefas.fim;
				dev->tarefas.fim->prox = tarefa;
				dev->tarefas.fim = tarefa;
			}
			else{
				while(tarefaAtual->tipo >= tarefa->tipo)
					tarefaAtual = tarefaAtual->prox;
			
				tarefa->prox = tarefaAtual;
				tarefa->ant = tarefaAtual->ant;
				tarefa->ant->prox = tarefa;
				tarefaAtual->ant= tarefa;
			}
		}
	}
	dev->tarefas.qtdTarefa++;
    dev->tarefas.qtdTempo += tarefa->tempo;
}
tpDev *devID(dev){
	tpDev *dev = desc.inicio;
	tp *atual = desc.inicio->prox;
	//busca o dev com o devido ID
	while (atual != NULL && dev->id != idRemover){
		dev = atual;
		atual = atual->prox;
	}
	if(dev->id == idRemover)
		return dev;	
}
void redistribuirTarefa(tpDev *dev, tpTarefa *tarefa){
	tpTarefa *tarefaAtual = dev->tarefas.inicio;
	if(dev->tarefas.inicio == NULL){
    	dev->tarefas.inicio = dev->tarefas.fim = tarefa;
	}
	else{
		if(dev->tarefas.inicio->tipo < tarefa->tipo){
			dev->tarefas.inicio->ant = tarefa;
			tarefa->prox = dev->tarefas.inicio;
			dev->tarefas.inicio = tarefa;
		}
		else{
			if(dev->tarefas.fim->tipo <= tarefa->tipo){
				tarefa->ant = dev->tarefas.fim;
				dev->tarefas.fim->prox = tarefa;
				dev->tarefas.fim = tarefa;
			}
			else{
				while(tarefaAtual->tipo >= tarefa->tipo){
					tarefaAtual = tarefaAtual->prox;
				tarefa->prox = tarefaAtual;
				tarefa->ant = tarefaAtual->ant;
				tarefa->ant->prox = tarefa;
				tarefaAtual->ant= tarefa;
			}
		}
	}
	dev->tarefas.qtdTarefa++;
    dev->tarefas.qtdTempo += tarefa->tempo;
}
tpDev *menorCargaRemover(tpDesc desc, tpDev *devExcluir){
	tpDev *menor = NULL;
	tpDev *atual = desc.inicio;
	while(atual != NULL){
		if(atual == devExcluir)
			atual = atual->prox;
		else{
			if(menor == NULL)
				menor = atual;
			else 
				if(menor->tarefas.qtdTempo > atual->tarefas.qtdTempo){
					menor = atual;	
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
	else{
		//redistribuir tarefas
		// se o dev tiver tarefas, pega a tarefa atual para entregar para outro dev
		if(devID->tarefas.qtdTarefa > 0){
			//se tem apenas um dev, as tarefas podem ser perdidas
			if(desc.qtdDev == 1)
				return 2;
			else{
				tpTarefa *tarefa = devID->tarefas.inicio;
				while(tarefa != NULL){
					devID->tarefas.inicio = devID->tarefas.inicio->prox;
					//define outro ponteiro para não perder a tarefa
					tpTarefa *proximaTarefa = tarefa->prox;
					//encontrar dev com menor carga
					tpDev *menor = menorCargaRemover(desc,devID) ;
					//se o com menor não tem tarefas, ele recebe a primeira tarefa no inicio e fim do descritor
					redistribuirTarefa(menor, tarefa);
					tarefa = proximaTarefa;
				}
				if(anterior == NULL)
					desc.inicio = devID->prox;
				else
					anterior->prox = devID->prox;
				if(devID == desc.fim){
					desc.fim = anterior;
					anterior->prox = NULL;
				}
				delete(devID);
				desc.qtdDev
			}
		}
	}
}
