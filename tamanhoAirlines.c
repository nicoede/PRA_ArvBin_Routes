#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	FILE *texto = fopen("routes.dat.txt","r");
	FILE *novo;
	char arq[2500000];
	int i=0, j=0, k=0, nCampo=0, vlrCampo=0, nLinhas=0;
	int vetorCampo[9]={0,0,0,0,0,0,0,0,0};
	int tamLinha=0, indice=0;
	char *novaTabela=NULL;

	if(texto == NULL){
	   	printf("ERRRooo!\n");
		return -1;
    }
    
    novo=fopen("routes_new.txt", "w");
    if(novo == NULL){
	   	printf("ERRRooo!\n");
		return -1;
    }
    
    fread(arq, sizeof(char), 2500000, texto);
	fclose(texto);
	for(j=0;arq[j]!='\0';j++){
		vlrCampo++;
		if((arq[j]==',')||(arq[j]=='\n')||(arq[j]=='\0')){
			vlrCampo--;
			if(nCampo==8){
				vlrCampo--;
			}
			if(vlrCampo>vetorCampo[nCampo]){
				vetorCampo[nCampo]=vlrCampo;
			}
			vlrCampo=0;
			if(arq[j]==','){
				nCampo++;
			}
			else{
				nCampo=0;
				nLinhas++;
			}
		}
	}
	printf("\n");
	for(i=0;i<9;i++){
		printf("Campo %i: %i\n", i, vetorCampo[i]);
	}
	printf("N linhas: %i\n\n", nLinhas);
	
	for(i=0;i<9;i++){	
		tamLinha+=vetorCampo[i]+1;
	}
	
	novaTabela=(char*)malloc(tamLinha*nLinhas*sizeof(char));
	
	for(j=0;arq[j]!='\0';){
		for(i=0;i<9;i++){
			for(k=0;k<vetorCampo[i];k++){
				if(arq[j]=='\r'){
					j++;
				}
				if((arq[j]!=',')&&(arq[j]!='\n')&&(arq[j]!='\0')){
					novaTabela[indice]=arq[j];
					j++;
				}
				else{
					novaTabela[indice]=' ';
				}
				indice++;
			}
			if(arq[j]=='\r'){
				j++;
			}
			novaTabela[indice]=arq[j];
			j++;
			indice++;
		}
	}
	novaTabela[indice-1]='\0';
	
	//printf("%s\n", novaTabela);
	fprintf(novo, "%s\n", novaTabela);
	fclose(novo);
	/*for(i=0;novaTabela[i]!='\0';i++){
		printf("%c", novaTabela[i]);
	}*/
		
	return 0;
}











