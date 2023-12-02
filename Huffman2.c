#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <locale.h>
#include "TadArvore.h"
#include "TadDados.h"

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

void leituraArquivoBinario(FILE *arq){
	Dados aux;
	printf("-------------- Arquivo Binario Leitura --------------\n");
	if(arq == NULL)
		printf("Arquivo Binario nao encontrado\n");
	else{
		fread(&aux,sizeof(aux),1,arq);
		while(!feof(arq)){
			printf("%s\t%d\t%d\t%s\n",aux.palavra,aux.freq,aux.simb,aux.cod);
			fread(&aux,sizeof(aux),1,arq);
		}
	}
	printf("-----------------------------------------------------\n");
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

void telacheia() {
	keybd_event ( VK_MENU, 0x38, 0, 0 );
	keybd_event ( VK_SPACE, 0x39, 0, 0 );
	keybd_event(0x58,0,0,0);
	keybd_event ( VK_MENU, 0x38, KEYEVENTF_KEYUP, 0 );
	keybd_event ( VK_SPACE, 0x39, KEYEVENTF_KEYUP, 0 );
	keybd_event(0x58,0,KEYEVENTF_KEYUP,0);
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

int main(void){
	setlocale(LC_ALL,"Portuguese");
	telacheia();
	char codH[500];
	Dados *dados;
	Lista *lista;
	FILE *arqtxtL = fopen("CodigoHuffman.txt","r+");
	FILE *arqbinL = fopen("CodigoHuffman.dat","rb+");
	initDados(&dados);
	initLista(&lista);
	fgets(codH,500,arqtxtL);
	criadados(&dados,&arqbinL);
	criaListaArvore(dados,&lista);
	criaArvore(&lista);
	rewind(arqbinL);
	leituraArquivoBinario(arqbinL);
	fclose(arqbinL);
	getch();
	system("cls");
	exibeH(lista->no);
	return 0;
}

