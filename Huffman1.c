#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <locale.h>
#include "TadArvore.h"
#include "TadDados.h"

void salvarArquivoBinario(FILE *arq, Dados *dados){
	Dados aux;
	printf("\n\n\n\n\n");
	printf("-------------- Arquivo Binario Salvar --------------\n");
	while(dados != NULL){
		printf("%s\t%d\t%d\t%s\n",dados->palavra,dados->freq,dados->simb,dados->cod);
		strcpy(aux.cod,dados->cod);
		aux.freq = dados->freq;
		aux.simb = dados->simb;
		strcpy(aux.palavra,dados->palavra);
		aux.prox = NULL;
		fwrite(&aux,sizeof(aux),1,arq);
		dados = dados->prox;
	}
	printf("----------------------------------------------------\n");
}

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

int Quantidade(Dados *dados){
	Dados *aux = dados;
	int count=0;
	while(aux != NULL){
		count ++;
		aux = aux->prox;
	}
	return count;
}

void ordenaLista(Dados **dados){
	Dados *atual = *dados, *aux;
	int x, count = Quantidade(*dados), freq,simb;
	char cod[60],palavra[60];
	for(x=0; x < count-1 ;x++){
		aux = atual->prox;
		while(aux!=NULL){
			if(atual->freq > aux->freq ){
				//Copiei os conteudos do atual para as variaveis
				freq = atual->freq;
				simb = atual->simb;
				strcpy(cod,atual->cod);
				strcpy(palavra,atual->palavra);
				
				//Copiei os conteudos do Aux para o Atual
				atual->freq = aux->freq;
				atual->simb = aux->simb;
				strcpy(atual->cod,aux->cod);
				strcpy(atual->palavra,aux->palavra);
				
				//Copiei os conteudos das variÃ¡veis para o Aux
				aux->freq = freq;
				aux->simb = simb;
				strcpy(aux->cod,cod);
				strcpy(aux->palavra,palavra);
			}
			aux = aux->prox;
		}
		atual = atual->prox;
	}
}

void ExibeConteudoListaAravore(Lista **lista){
	Lista *aux = *lista;
	while(aux != NULL){
		printf("%d\n",aux->no->frq);	
		aux = aux->prox;
	}
}

void ExibeConteudoListaEncadeada(Dados *dados){
	Dados *aux = dados;
	while(aux != NULL){
		printf("%s\t%d\t%d\t%s\n",aux->palavra,aux->freq,aux->simb,aux->cod);	
		aux = aux->prox;
	}
}

void InsereListaFrase(Dados **dados, char frase[]){
	char palavra[50],space[2] = " ";
	int pos,i=0,simb=0,cont=0;
	for(pos = 0; pos<strlen(frase); pos++){
		if(frase[pos] != ' ' && frase[pos] != '.'){
			palavra[i] = frase[pos];
			palavra[i+1] = '\0';
			i++;
		}
		else{
			insereLista(&*dados,simb,1,palavra,space);
			simb++;
			i=0;
			if(frase[pos] == ' '){
				insereLista(&*dados,simb,1," ",space);
				simb++;
			}
		}
	}
	//ExibeConteudoListaEncadeada(*dados);
}

void pegarFrequencia(Dados **dados,char frase[]){
	char palavra[50],space[2] = " ";
	int pos,i=0,simb=0,cont=0;
	for(pos = 0; pos<strlen(frase); pos++){
		if(frase[pos] != ' ' && frase[pos] != '.'){
			palavra[i] = frase[pos];
			palavra[i+1] = '\0';
			i++;
		}
		else{
			if(verificaPalavra(&(*dados),palavra)){
				i=0;
			}
			else{
				insereLista(&*dados,simb,1,palavra,space);
				simb++;
				i=0;	
			}
			if(cont == 0){
				insereLista(&*dados,simb,1,space,space);
				simb++;
				cont++;
			}
			else{
				verificaPalavra(&(*dados),space);
			}
		}
	}
	//ExibeConteudoListaEncadeada(*dados);
	ordenaLista(&(*dados));
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

void pre_ordem(Tree *t,Dados **dados ,char cod[]){
	Dados *aux = *dados;
	if(t != NULL){
		if(t->simb != -1){
			while(aux != NULL){
				if(aux->simb == t->simb)
					strcpy(aux->cod,cod);
				aux = aux -> prox;
			}
		}
		strcat(cod,"0");
		pre_ordem(t->esq,&*dados,cod);
		cod[strlen(cod)-1] = '\0';
		strcat(cod,"1");
		pre_ordem(t->dir,&*dados,cod);
		cod[strlen(cod)-1] = '\0';
	}
}

void pega_cod_grava_arq(Dados *aux, Dados *dados,char palavra[]){
	Dados *auxDados;
	while(aux != NULL){
		auxDados = dados;
		while(auxDados != NULL){
			if(strcmp(aux->palavra,auxDados->palavra) == 0)
				strcat(palavra,auxDados->cod);
			auxDados = auxDados->prox;
		}
		aux = aux -> prox;
	}
	printf("\nPalavra codificada: %s",palavra);
	//Gravar no Arquivo texto
	FILE *arq = fopen("CodigoHuffman.txt","w");
	fprintf(arq,"%s\n",palavra);
	fclose(arq);
}

void telacheia() {
	keybd_event ( VK_MENU, 0x38, 0, 0 );
	keybd_event ( VK_SPACE, 0x39, 0, 0 );
	keybd_event(0x58,0,0,0);
	keybd_event ( VK_MENU, 0x38, KEYEVENTF_KEYUP, 0 );
	keybd_event ( VK_SPACE, 0x39, KEYEVENTF_KEYUP, 0 );
	keybd_event(0x58,0,KEYEVENTF_KEYUP,0);
}

int main(void){
	setlocale(LC_ALL,"Portuguese");
	telacheia();
	Dados *dados,*aux;
	Lista *lista;
	char frase[500], frase_cod[500], cod[]="";
	strcpy(frase,"Sem sacar que o espinho é seco. Sem sacar que seco é ser sol. Sem sacar que algum espinho seco secará. Se acabar não acostumando. Se acabar parado calado.Se acabar baixinho chorando. Se acabar meio abandonado.");
	initDados(&dados);
	initDados(&aux);
	initLista(&lista);
	pegarFrequencia(&dados,frase);
	criaListaArvore(dados,&lista);
	criaArvore(&lista);
	//printf("\n\n\n");
	//ExibeConteudoListaEncadeada(dados);
	//printf("\n\n\n");
	//exibeH(lista->no);
	//printf("\n\n\n");
	pre_ordem(lista->no,&dados,cod);
	printf("\n\n\n");
	
	
	//Salvar o conteudo de uma lista em um arquivo binario
	FILE *arqbinG = fopen("CodigoHuffman.dat","wb");
	salvarArquivoBinario(arqbinG,dados);
	printf("\n\n\n");
	fclose(arqbinG);
	
	
	//Digitar umas palavras que contem dentro da frase para poder codificar e gravar em um arquivo texto
	strcpy(frase_cod,"sacar o espinho seco é acabar meio abandonado.");
	printf("Palavra a ser codificada: %s\n",frase_cod);
	initDados(&aux);
	InsereListaFrase(&aux,frase_cod);
	pega_cod_grava_arq(aux,dados,cod);
	return 0;
}
