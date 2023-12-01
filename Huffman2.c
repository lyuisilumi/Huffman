#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <locale.h>
#include "TadArvore.h"
#include "TadDados.h"

void leituraArquivoBinario(FILE *arq){
	Dados aux;
	printf("\n\n\n\n\n");
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
	FILE *arqbinL = fopen("CodigoHuffman.dat","rb");
	leituraArquivoBinario(arqbinL);
	fclose(arqbinL);
	return 0;
}

