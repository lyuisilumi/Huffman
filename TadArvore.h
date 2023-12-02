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
