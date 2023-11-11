struct dados{
	struct dados *prox;
	int freq,simb;
	char cod[60],palavra[60];
};
typedef struct dados Dados;

void initDados(Dados **dados){
	*dados = NULL;
}

void insereLista(Dados **dados,int simb,int frequencia, char palavra[],char cod[]){
	Dados *caixa = (Dados*)malloc(sizeof(Dados)),*aux;
	caixa->prox = NULL;
	caixa->freq = frequencia;
	caixa->simb = simb;
	strcpy(caixa->palavra,palavra);
	strcpy(caixa->cod,"a");
	if(*dados == NULL)
		*dados = caixa;
	else{
		aux = *dados;
		while(aux->prox != NULL)
			aux= aux->prox;
		aux->prox = caixa;
	}
}
