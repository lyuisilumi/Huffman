#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <locale.h>
#include "Tad.h"

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

void busca(Dados **dados,int simb, char frase[],int *num){
	char palavra[50];
	int i=0;
	Dados *aux = *dados;
	while(aux!=NULL && aux->simb!=simb)
		aux = aux -> prox;
	if(aux!=NULL)
	{
		while(aux->palavra[i]!='\0')
		{
			strcpy(palavra,aux->palavra);
			frase[*num]=palavra[i];
			i++;
			(*num)++;
		}
	}
	frase[*num]='\0';
}

void frase(Dados **dados,Tree *no,char cod[],char frase[]){
	int i=0,j=0;
	Tree *aux = no;
	while(cod[i]!='\0')
	{	
		if(aux->simb!=-1)
		{
			busca(&*dados,aux->simb,frase,&j);
			aux = no;
		}
		if(cod[i]=='0')
			aux = aux->esq;
		else
		if(cod[i]=='1')
			aux = aux->dir;
		i++;
	}
}

int main(void){
	setlocale(LC_ALL,"Portuguese");
	telacheia();
	char codH[501],fras[500];
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
	getch();
	system("cls");
	exibeH(lista->no);
	frase(&dados,(lista->no),codH,fras);
	getch();
	system("cls");
	printf("%s",fras);
	return 0;
}

