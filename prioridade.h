struct tpTarefa{
	int prioridade;
	int tempo;
	char nome_tarefa [50];
	tpPont *prox, *ant;
};
struct tpDesc{
	tpDev *inicio, *fim;
};
struct tpDev{
	char nome[30];
	tpTarefa *inicio, *fim;
	tpDev *prox;
};	
tpTarefa *node(int prioridade, int tempo,char tarefa[50]){
	tpTarefa *node = new tpTarefa;
	node->prioridade = prioridade;
	node->tempo = tempo;
	node->prox = node->ant = NULL;
	strcpy(node->nome_tarefa, tarefa);
	return node;
}
tpDev *criaDev(char nome[30]){
	tpDev *dev = new tpDev;
	dev->prox = NULL;
	strcpy(dev->nome, nome);
	return dev;
}
void inicilizar(tpDecs &desc){
	desc.inicio  = desc.fim = NULL;
}
char vazia(tpDesc desc){
	return desc.inicio == NULL;
}
void inserirDev(tpDesc &desc,char nome[30]){
	tpDev *dev = criaDev(nome);
	if(vazia(desc))
		desc.inicio = desc.fim = dev;
	else{
		desc.fim->prox = dev;
		desc.fim = dev;
	}
}
void qtdprioridade(tpDesc desc, )
