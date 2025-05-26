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
    dev->tarefas.qtdTarefa = dev->tarefas.qtdTempo = 0;
    dev->tarefas.inicio = dev->tarefas.fim = NULL;
    return dev;
}

void inicializarDesc(tpDesc &desc, int qtdDevs) {
    desc.qtdDev = qtdDevs;
    desc.inicio = desc.fim = NULL;
}
void inicializarTarefa(tpDev &dev){
	descTarefa.inicio = descTarefa.fim = NULL;
	descTarefa.qtdTarefa = descTarefa.qtdTempo =  0;
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

void inserirTarefa(tpTicket ticket, tpDesc &desc, int chegada) {
    tpDev *devInicio = desc.inicio;
    tpDev *atual = NULL;
    tpTarefa *tarefa = criaTarefa(ticket, chegada);
    tpTarefa *tarefaAtual = NULL;

    // Verifica até achar um desocupado
    while (devInicio != NULL && devInicio->tarefas.qtdTarefa > 0) {
        devInicio = devInicio->prox;
    }

    // Se encontrou um desocupado, recebe tarefa
    if (devInicio != NULL && devInicio->tarefas.qtdTarefa == 0) {
        devInicio->tarefas.inicio = devInicio->tarefas.fim = tarefa;
        devInicio->tarefas.qtdTarefa++;
        devInicio->tarefas.qtdTempo += tarefa->tempo;
    } 
    // Não encontrou desocupado, procura o com menor tempo
    else {
        devInicio = desc.inicio;
        atual = devInicio->prox;
        
        // Buscar menor tempo
        while (atual != NULL) {
            if (devInicio->tarefas.qtdTempo > atual->tarefas.qtdTempo) {
                devInicio = atual;
            }
            atual = atual->prox;
        }
        // Inserção de acordo com a prioridade
        if (devInicio->tarefas.inicio == NULL) {
            devInicio->tarefas.inicio = devInicio->tarefas.fim = tarefa;
        } else {
            // Por ser menor prioridade, entra no fim
            if (tarefa->tipo == 1) {
                devInicio->tarefas.fim->prox = tarefa;
                tarefa->ant = devInicio->tarefas.fim;
                devInicio->tarefas.fim = tarefa;
            } else {
                tarefaAtual = devInicio->tarefas.inicio;
                
                // Se for alta prioridade e a primeira for média, insere depois 
                if (tarefa->tipo > tarefaAtual->tipo) {
                    tarefa->prox = tarefaAtual->prox;
                    tarefa->prox->ant = tarefa;
                    tarefa->ant = tarefaAtual;
                } else {
                    // Busca a posição correta para inserir
                    while (tarefaAtual != NULL && tarefa->tipo <= tarefaAtual->tipo) {
                        tarefaAtual = tarefaAtual->prox;
                    }
                    
                    if (tarefaAtual == NULL) {
                        // Insere no final
                        devInicio->tarefas.fim->prox = tarefa;
                        tarefa->ant = devInicio->tarefas.fim;
                        devInicio->tarefas.fim = tarefa;
                    } else {
                        // Insere antes de tarefaAtual
                        tarefa->prox = tarefaAtual;
                        tarefa->ant = tarefaAtual->ant;
                        if (tarefaAtual->ant != NULL) {
                            tarefaAtual->ant->prox = tarefa;
                        } else {
                            devInicio->tarefas.inicio = tarefa;
                        }
                        tarefaAtual->ant = tarefa;
                    }
                }
            }
        }
        
        devInicio->tarefas.qtdTarefa++;
        devInicio->tarefas.qtdTempo += tarefa->tempo;
    }
}
void removerDev(tpDesc &desc){
	if(devsVazio(desc))
		printf("Nao há desenvolvedores")
	else
	{
		tpDev *ant = NULL;
		tpDev *atual = desc.inicio;
		int idRemover;
		for(atual; atual != NULL; atual = atual->prox)
			printf("ID: %d\nQuantidade Tarefas: %d\n",
			atual->id,atual->tarefas.qtdTarefa);
		printf("Informe o ID do dev que deseja remover: ");
		scanf("%d", &idRemover);
		clrscr();
		if(idRemover == 0){
			printf("\nID invalido!\n");	
			getch();
		}	
		else{
			//retorna o ponteiro depois de printar as opções
			atual = desc.inicio;
			//busca o dev com o devido ID
			while (atual != NULL && atual->id != idRemover){
				ant = atual;
				atual = atual->prox;
			}
			if(atual == NULL)
				printf("Dev nao encontrado");
			else{
				//redistribui tarefas
				if(atual->tarefas.qtdTarefa > 0)
					tpTarefa *tarefa = atual->tarefas.inicio;
				while(tarefa != NULL){
					tpTarefa *prox = tarefa->prox;
					//encontra dev com menor carga
					tpDev *menor = desc.inicio;
					tpDev *temp = desc.inicio;
					
					while(temp != NULL){
						if(temp != atual  && temp->tarefas.qtdTempo < menor->tarefas.qtdTempo)
							menor = temp;
						temp = temp->prox;
					}
					if(menor->tarefas.inicio == NULL){
						menor->tarefas.inicio = menor->tarefas.fim = tarefa;
						tarefa->prox = tarefa->ant =  NULL;
					}
					else{
						tpTarefa *t = menor->tarefas.inicio;
						tpTarefa *antT = NULL;
						while(t != NULL && t->tipo >= tarefa->tipo){
							antT = t;
							t = t->prox;
						}
						if(antT == NULL){
							//insere depois para não sobrepor tarefas já sendo executadas
							if(t->prox NULL){
								t->prox = menor->
							}
								
						}
					}
				}
			}
		}
		
	}
}
