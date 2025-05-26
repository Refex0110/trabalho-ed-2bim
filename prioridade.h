struct tpDesc{
	int qtdDev;
	tpDev *inicio, *fim;
};
struct tpDev{
	int id;
	descTarefa tarefas;
	tpDev *prox;
};
struct descTarefa{
	int qtdTarefa, qtdTempo;
	tpTarefa *inicio, *fim;
};
struct tpTarefa{
	int tipo;
	int tempo;
	int tempo_chegada;
	char nome_tarefa[50];
	char responsavel[50];
	char data[11];
	tpTarefa *prox, *ant;
};
verificaPrioridade(char prioridade[10]);
tpTarefa *criaTarefa(tpTicket ticket, int chegada){
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
tpDev *criaDev(int id){
	tpDev *dev = new tpDev;
	dev->id = id;
	dev->prox = NULL;
	dev->qtdTempo = dev->qtdTarefa = 0;
	dev->ocupado = 0;
	return dev;
}
void inicializarDesc(tpDesc &desc, int qtdDevs){
	desc.qtdDev = qtdDevs;
	desc.inicio  = desc.fim = NULL;
}
void inicializarTarefa(tpDev &dev){
	descTarefa.inicio = descTarefa.fim = NULL;
	descTarefa.qtdTarefa = descTarefa.qtdTempo =  0;
}
char devsVazio(tpDesc desc){
	return desc.inicio == NULL;
}
void inserirDev(tpDesc &desc){
	tpDev *dev = criaDev(desc.qtdDev+1);
	inicializarTarefa(dev);
	if(devsVazio(desc)){
		desc.inicio = desc.fim = dev;
	}
	else{
		desc.fim->prox = dev;
		desc.fim = dev;	
	}
}
int verificaPrioridade(char prioridade[10]){
	if(stricmp(prioridade,"Importante") == 0)
		return 3;
	else
		if(stricmp(prioridade,"Melhoria") == 0))
			return 2;
		else
			return 1;
}
void inserirTarefa(tpTicket ticket, tpDesc &desc,){
	tpDev *devInicio = new tpDev;
	devInicio = desc.inicio;
	tpDev *atual = new tpDev;
	tpTarefa tarefa = criaTarefa(ticket, );
	tpTarefa *tarefaAtual;
	//verifica até achar um decoupado
	while(!devInicio->ocupado && devInicio != NULL)
		devInicio = dev->prox;
	//se encontrou um ocupado, recebe tarefa
	if(!devInicio->ocupado){
		devInicio->inicio = devInicio->fim = tarefa;
		devInicio->qtdTarefa[4]++;
		devInicio->qtdTarefa[5]++;
		devInicio->ocupado = 1;
		devInicio->qtdTempo+= tarefa.tempo;
		desc.qtdDev--;
	}
	// Não encontrou desocupado, retorna para encontrar menor tempo
	else{
		devInicio = desc.inicio;
		atual = devInicio->prox;
		//buscar menor tempo e quantidade de tarefas
		while(atual != NULL){
			if(devInicio->qtdTempo > atual->qtdTempo)
			{
				devInicio = atual;
				atual = atual->prox;
			}
			else
				if(devInicio->qtdTempo > atual->prox->qtdTempo &&
				atual->prox->prox != NULL)
				{
					devInicio = atual;
					atual = atual->prox;
				}
		}
		//inserção de acordo com a prioridade
		tarefaAtual = devInicio->inicio;
		//por ser menor prioridade e chegar depois, entra no fim
		if(tarefa->tipo == 1)
		{
			devInicio->fim->prox = tarefa;
			tarefa->ant = devInicio->fim;
			devInicio->fim = tarefa;
		}
		else{
			if(tarefa->tipo == 3 && devInicio->inicio->tipo == 2)
			{
				tarefa->prox = devInicio->inicio;
				devInicio->inicio->ant = tarefa;			
				devInicio->inicio = tarefa;
			}
			else
			{
				//busca o primeiro de menor prioridade
				while(tarefa->tipo < tarefaAtual->tipo)
					tarefaAtual = tarefaAtual->prox;
				//quando encontrar, coloca tarefa antes
				if(tarefaAtual->ant->tipo > tarefa->tipo){
					tarefa->prox = tarefaAtual;
					tarefa->ant-> = tarefaAtual->ant;
					tarefaAtual->ant->prox = tarefaAtual->ant = tarefa;
				}
			}
		}
					
		devInicio->fim = tarefa;
		devInicio->qtdTarefa[4]++;
		devInicio->qtdTarefa[5]++;
		desc.qtdDev--;
		//dev recebe NULL e finaliza função
		devInicio = NULL;
	}
}
