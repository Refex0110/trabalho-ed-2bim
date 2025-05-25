
struct tpTarefa{
	int tipo;
	int tempo;
	int tempo_chegada;
	char nome_tarefa[50];
	char responsavel[50];
	char data[11];
	tpTarefa *prox, *ant;
};
struct tpDev{
	int id;
	int qtdTarefa[4];
	int qtdTempo;
	int ocupado;
	tpTarefa *inicio, *fim;
	tpDev *prox;
};	
struct tpDesc{
	int qtdDev, tarefasConcluidas, tarefas;
	tpDev *inicio, *fim;
};
tpTarefa *criaTarefa(tpTicket ticket, int chegada){
	tpTarefa *tarefa = new tpTarefa;
	strcpy(tarefa->tipo,ticket.tipo);
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
void inicializar(tpDesc &desc, int qtdDevs){
	desc.qtdDev = qtdDevs;
	desc.inicio  = desc.fim = NULL;
}
char devsVazio(tpDesc desc){
	return desc.inicio == NULL;
}
void inserirDev(tpDesc &desc){
		tpDev *dev = criaDev(desc.qtdDev+1);
	if(devsVazio(desc))
		desc.inicio = desc.fim = dev;
	else{
		desc.fim->prox = dev;
		desc.fim = dev;
	}
}

void inserirTarefa(tpTicket ticket, tpDesc &desc,){
	tpDev *devInicio = new tpDev;
	tpDev *devFim = new tpDev;
	devInicio = desc.inicio;
	devFim = desc.fim;
	//verificar se tem tarefa
	if(!devInicio->ocupado){
		
		devInicio->inicio = devInicio->fim = criaTarefa(ticket,);
		devInicio->qtdTarefa[4]++;
		switch()
		desc.qtdDev++;
		dev = NULL;
	}
	while(!dev->ocupado && dev != NULL)
	{
		dev->inicio = dev->fim = criaTarefa(ticket,);
		dev = dev->prox;
	}
	//contar tempo e quantidade de tarefas
	while(dev->qtdTempo > dev->prox.qtdTempo){
		if(dev->qtdTarefa[4] > dev->prox.qtdTarefa)
			dev
		
	}
}


