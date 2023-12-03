struct tree{
	int frq,simb;
	struct tree *dir,*esq;
};
typedef struct tree Tree;

struct lista{
	struct tree *no;
	struct lista *prox;
};
typedef struct lista Lista;

struct dados{
	struct dados *prox;
	int freq,simb;
	char cod[60],palavra[60];
};
typedef struct dados Dados;

void telacheia() {
	keybd_event ( VK_MENU, 0x38, 0, 0 );
	keybd_event ( VK_SPACE, 0x39, 0, 0 );
	keybd_event(0x58,0,0,0);
	keybd_event ( VK_MENU, 0x38, KEYEVENTF_KEYUP, 0 );
	keybd_event ( VK_SPACE, 0x39, KEYEVENTF_KEYUP, 0 );
	keybd_event(0x58,0,KEYEVENTF_KEYUP,0);
}

void initDados(Dados **dados){
	*dados = NULL;
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

void initLista(Lista **Lista){
	*Lista = NULL;
}

Tree *cria_No(int simb, int frequencia){
	Tree *no = (Tree*)malloc(sizeof(Tree));
	no->dir = no->esq = NULL;
	no->simb = simb;
	no->frq = frequencia;
	return no;
}

void exibeH(Tree *tree){
	static int n = -1,i;
	if(tree != NULL){
		n++;
		exibeH(tree->dir);
		for(i=0; i<5*n; i++)
			printf(" ");
		printf("(%d, %d)\n",tree->simb,tree->frq);
		exibeH(tree->esq);
		n--;
	}
}

void fazNo(Lista **lista, Lista **segundo, Lista **primeiro, int simb, int soma){
	Lista *ant,*aux, *novo = (Lista*)malloc(sizeof(Lista));
	novo->prox = NULL; 
	novo->no = cria_No(simb,soma);
	novo->no->esq = (*primeiro)->no;
	novo->no->dir = (*segundo)->no;
	if((*lista) == NULL){
		*lista = novo;
	}
	else{
		ant = aux = *lista;
		while(aux != NULL && aux->no->frq <= soma){
			ant = aux;
			aux = aux->prox;
		}
		if(aux == NULL)
			ant->prox = novo;
		else{
			if(aux == ant){
				novo->prox = aux;
				*lista = novo;
			}
			else{
				novo->prox = aux;
				ant->prox = novo;
			}
		}
	}
}

void excluir(Lista **lista, int simb){
	Lista *ant, *aux;
	ant = aux = *lista;
	while(aux != NULL && aux->no->simb != simb){
		ant = aux;
		aux = aux->prox;
	}
	if(ant == aux)
		*lista = aux->prox;
	else
		ant->prox = aux->prox;
	free(aux);
}

void criaListaArvore(Dados *dado, Lista **lista){
	Lista *novo,*aux;
	while(dado != NULL){
		novo = (Lista*)malloc(sizeof(Lista));
		novo->no = cria_No(dado->simb,dado->freq);
		novo->prox = NULL;
		if((*lista) == NULL){
			*lista = novo;
		}
		else{
			aux = *lista;
			while(aux->prox != NULL){
				aux = aux->prox;
			}
			aux->prox = novo;
		}	
		dado = dado->prox;
	}
}

void criaArvore(Lista **lista){
	Lista *primeiro,*segundo;
	int soma;
	primeiro = *lista;
	segundo = primeiro->prox;
	while(segundo != NULL){
		soma = (segundo->no->frq) + (primeiro->no->frq);
		fazNo(&*lista,&segundo,&primeiro,-1,soma);
		excluir(&*lista,primeiro->no->simb);
		excluir(&*lista,segundo->no->simb);
		primeiro = *lista;
		segundo = primeiro->prox;
	}
}
