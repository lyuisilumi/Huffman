#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "TadArvore.h"
#include "TadDados.h"

char verificaPalavra(Dados **dados,char palavra[]){
	Dados *aux;
	aux = *dados;
	while(aux != NULL && stricmp(aux->palavra,palavra)!= 0)
		aux = aux->prox;
	if(aux != NULL){
		aux->freq++;
		return 1;
	}
	return 0;
}

void pegarFrequencia(Dados **dados,char frase[]){
	char palavra[50],espaco[2]= " ";
	int pos,i=0,simb=0,cont=0;
	for(pos = 0; pos<strlen(frase); pos++){
		if(frase[pos] != ' '){
			palavra[i] = frase[pos];
			palavra[i+1] = '\0';
			i++;
		}
		else{
			if(verificaPalavra(&(*dados),palavra)){
				i=0;
			}
			else{
				insereLista(&*dados,simb,1,palavra,NULL);
				simb++;
				i=0;	
			}
			if(cont == 0){
				insereLista(&*dados,simb,1,espaco,NULL);
				simb++;
				cont++;
			}
			else{
				verificaPalavra(&(*dados),espaco);
			}
		}
	}
	insereLista(&*dados,simb,1,palavra,NULL);
}

void exibeH(Tree *tree){
	static int n = -1,i;
	if(tree != NULL){
		n++;
		exibeH(tree->dir);
		for(i=0; i<5*n; i++)
			printf(" ");
		printf("(%d, %d)",tree->simb,tree->frq);
		exibeH(tree->esq);
		n--;
	}
}

int main(){
	setlocale(LC_ALL,"Portuguese");
	Dados *dados,*aux;
	Lista *lista;
	char frase[500];
	strcpy(frase,"Sem sacar que o espinho é seco. Sem sacar que seco é ser sol. Sem sacar que algum espinho seco secará. Se acabar não acostumando. Se acabar parado calado. Se acabar baixinho chorando. Se acabar meio abandonado.");
	initDados(&dados);
	initLista(&lista);
	pegarFrequencia(&dados,frase);
	aux = dados;
	while(aux != NULL){
		printf("%s\t%d\t%d\t%s\n",aux->palavra,aux->freq,aux->simb,aux->cod);	
		aux = aux->prox;
	}
	
}
