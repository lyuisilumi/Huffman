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
