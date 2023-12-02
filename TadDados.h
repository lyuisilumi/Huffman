struct dados{
	struct dados *prox;
	int freq,simb;
	char cod[60],palavra[60];
};
typedef struct dados Dados;

void initDados(Dados **dados){
	*dados = NULL;
}

void ExibeConteudoListaEncadeada(Dados *dados){
	Dados *aux = dados;
	while(aux != NULL){
		printf("%s\t%d\t%d\t%s\n",aux->palavra,aux->freq,aux->simb,aux->cod);	
		aux = aux->prox;
	}
}

void criaCaixa(Dados **caixa,int simb,int frequencia, char palavra[],char cod[]){
	*caixa = (Dados*)malloc(sizeof(Dados));
	(*caixa)->prox = NULL;
	(*caixa)->freq = frequencia;
	(*caixa)->simb = simb;
	strcpy((*caixa)->palavra,palavra);
	strcpy((*caixa)->cod,cod);
}

void insereLista(Dados **dados,int simb,int frequencia, char palavra[],char cod[]){
	Dados *caixa,*aux;
	criaCaixa(&caixa,simb,frequencia,palavra,cod);
	if(*dados == NULL)
		*dados = caixa;
	else{
		aux = *dados;
		while(aux->prox != NULL)
			aux= aux->prox;
		aux->prox = caixa;
	}
}

void criadados(Dados **dados,FILE **arq)
{
	Dados reg;
	fseek(*arq,0,0);
	fread(&reg,sizeof(Dados),1,*arq);
	while(!feof(*arq))
	{
		insereLista(&*dados,reg.simb,reg.freq,reg.palavra,reg.cod);
		fread(&reg,sizeof(Dados),1,*arq);
	}
	
}
