#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"index.h"

int main(){

	FILE *routes;
	FILE *index;
	FILE *index2;
	
	char arq[4700000];
	char ind[750000];
	char ind2dados[35000];
	char linhaInd[12];
	char chave[4]={"111"};
	
	int nCod=0, proxLinha=0;
	int i, j;
	int posIndice=0;
	int posArquivo=0, proxLinhaIndice;
	int posCod1=0, posCod2=0;
	
	node *arvore=NULL;
	node *busca=NULL;
	
	routes = fopen("routes_new.txt", "r");
	
	if(routes == NULL){
	   	printf("ERRRooo!\n");
		return -1;
	}
	
	fread(arq, sizeof(char), 4700000, routes);
	
	index = fopen("index_routes.txt", "r");
	if(index == NULL){
	   	cria_primeiro_indice(arq);
	   	index = fopen("index_routes.txt", "r");
	   	if(index == NULL){
	   		printf("Erro ao criar primeiro índice\n");
	   		return -1;
	   	}
	}
	
	fread(ind, sizeof(char), 750000, index);
	
	index2 = fopen("index_2.txt", "r");
	if(index2 == NULL){
	   	cria_segundo_indice(ind);
	   	index2 = fopen("index_2.txt", "r");
	   	if(index2 == NULL){
	   		printf("Erro ao criar segundo índice\n");
	   		return -1;
	   	}
	}

	fread(ind2dados, sizeof(char), 35000, index2);
	
	for(i=0;ind2dados[i]!='\n';i++){
	}
	proxLinha=i+1;
	
	for(i=0;ind2dados[i*proxLinha+proxLinha-1]!='\0';i++){
	}
	nCod=i;
	
	arvore = sortedArrayToBST(ind2dados, 0, nCod);
	
	
	for(i=0;ind[i]!='\n';i++){
	}
	proxLinhaIndice=i+1;
	
	j=0;
	for(i=0;(posCod1==0)||(posCod2==0);i++){
		if(arq[i]==','){
			j++;
			if(j==2){
				posCod1=i+1;
			}
			if(j==4){
				posCod2=i+1;
			}
		}
	}

	
	while(strcmp(chave, "000")!=0){
	
		printf("Insira a chave para a busca:\n");
		printf("-Informe 000 para parar-\n");
		scanf("%s", chave);
		
		busca = search(&arvore, chave);
		
		if(strcmp(chave, "000")==0){
			break;
		}
		if(busca==NULL){
			printf("Chave nao encontrada\n");
			continue;
		}
		printf("Aeroportos para os quais %s possui voos:\n", chave);
		posIndice = atoi(&(busca->data[3]));
		
		while(1){
			strncpy(linhaInd, &(ind[posIndice]), proxLinhaIndice-1);
			if(strncmp(linhaInd, chave, 3)!=0){
				break;
			}
			posArquivo = atoi(&(linhaInd[3]));
			printf("%c%c%c\n", arq[posArquivo+posCod2-posCod1], arq[posArquivo+posCod2+1-posCod1], arq[posArquivo+posCod2+2-posCod1]);
			posIndice+=proxLinhaIndice;
	
		}
	
	}	
	
	fclose(routes);
	fclose(index);
	fclose(index2);
	return 0;

}

int cmpstr(const void* a, const void* b) {
    const char* aa = *(const char**)a;
    const char* bb = *(const char**)b;
    return strcmp(aa,bb);
}

void cria_primeiro_indice(char arq[]){
	FILE *index;
	char indiceLinha[8];
	char *dados=NULL, **indice=NULL;
	int nLinhas=0, posCampo=0, proxLinha=0;
	int i, j;
	
	j=0;
	for(i=0;arq[i]!='\n';i++){
		if((arq[i]==',')&&(posCampo==0)){
			j++;
		}
		if(j==2){
			posCampo=i+1;
			j=0;
		}
	}
	proxLinha=i+1;
	
	for(i=0;arq[i*proxLinha+proxLinha-1]!='\0';i++){
	}
	nLinhas=i;
	
	indice=(char**)malloc(nLinhas*sizeof(char*));
	if(indice==NULL){
		printf("Erro alocando vetor\n");
		return;
	}
	
	dados=(char*)malloc(12*nLinhas*sizeof(char));
	if(dados==NULL){
		printf("Erro alocando vetor\n");
		return;
	}
	
	indice[0]=dados;
	for(i=12, j=1;j<nLinhas;i+=11, j++){
		indice[j]=dados+i;
	}
	
	for(i=0;i<nLinhas;i++){
		indice[i][0]=arq[i*proxLinha+posCampo];
		indice[i][1]=arq[i*proxLinha+posCampo+1];
		indice[i][2]=arq[i*proxLinha+posCampo+2];
		indice[i][3]='\0';
		sprintf(indiceLinha, "%07d", i*proxLinha+posCampo);
		strcat(indice[i], indiceLinha);
		indice[i][11]='\0';
	}
	
	qsort(indice, nLinhas, sizeof(char*), cmpstr);
	
	index = fopen("index_routes.txt", "w");
	if(index == NULL){
	   	printf("ERRRooo!\n");
		return;
	}
	
	for(i=0;i<nLinhas;i++){
		fprintf(index, "%s\n", indice[i]);
	}
	
	fclose(index);
}

void cria_segundo_indice(char ind[]){
	FILE *index;
	int proxLinha, nCod=0;
	int i, j;
	char cod[4]={"111"}, indiceLinha[7];
	char **indice2=NULL, *dados2=NULL;
	
	for(i=0;ind[i]!='\n';i++){
	}
	proxLinha=i+1;
	
	for(i=0;ind[i*proxLinha+proxLinha-1]!='\0';i++){
		if(strncmp(cod, &(ind[i*proxLinha]), 3)!=0){
			nCod++;
			strncpy(cod, &(ind[i*proxLinha]), 3);
		}
	}
	
	indice2=(char**)malloc(nCod*sizeof(char*));
	if(indice2==NULL){
		printf("Erro alocando vetor\n");
		return;
	}
	
	dados2=(char*)malloc(11*nCod*sizeof(char));
	if(dados2==NULL){
		printf("Erro alocando vetor\n");
		return;
	}
	
	indice2[0]=dados2;
	for(i=11, j=1;j<nCod;i+=10, j++){
		indice2[j]=dados2+i;
	}
	
	strncpy(cod, "111", 3);
	j=0;
	for(i=0;ind[i*proxLinha+proxLinha-1]!='\0';i++){
		if(strncmp(cod, &(ind[i*proxLinha]), 3)!=0){
			strncpy(cod, &(ind[i*proxLinha]), 3);
			strncpy(indice2[j], cod, 3);
			sprintf(indiceLinha, "%06d", i*proxLinha);
			strcat(indice2[j], indiceLinha);
			j++;
		}
	}
	
	index = fopen("index_2.txt", "w");
	for(i=0;i<nCod;i++){
		fprintf(index, "%s\n", indice2[i]);
	}
	
	fclose(index);
}

//funcoes da arvore
//fonte: http://www.thegeekstuff.com/2013/02/c-binary-tree/
/////////////////////

void insert(node ** tree, char *c)
{
    node *temp = NULL;
    if(!(*tree))
    {
        temp = (node *)malloc(sizeof(node));
        temp->left = temp->right = NULL;
        //temp->data = c;
        strcpy(temp->data, c);
        *tree = temp;
        return;
    }

    if(strcmp(c,(*tree)->data)<0)
    {
        insert(&(*tree)->left, c);
    }
    else if(strcmp(c,(*tree)->data)>0)
    {
        insert(&(*tree)->right, c);
    }

}

void print_inorder(node * tree)
{
    if (tree)
    {
        print_inorder(tree->left);
        printf("%s\n",tree->data);
        print_inorder(tree->right);
    }
}

void deltree(node * tree)
{
    if (tree)
    {
        deltree(tree->left);
        deltree(tree->right);
        free(tree);
    }
}
node* search(node ** tree, char *c)
{
    if(!(*tree))
    {
        return NULL;
    }

    if(strncmp(c,(*tree)->data, 3)<0)
    {
        search(&((*tree)->left), c);
    }
    else if(strncmp(c,(*tree)->data, 3)>0)
    {
        search(&((*tree)->right), c);
    }
    else if(strncmp(c,(*tree)->data, 3)==0)
    {
        return *tree;
    }
}

//criar arvore binaria a partir de vetor ordenado
//fonte: http://www.geeksforgeeks.org/sorted-array-to-balanced-bst/

node* sortedArrayToBST(char arr[], int start, int end)
{
    if (start > end)
      return NULL;
 
    int mid = (start + end)/2;
    char temp[11];
    
    strncpy(temp, &(arr[10*(mid-1)]), 9);
    temp[9]='\0';

    node *root = newNode(temp);
    root->left =  sortedArrayToBST(arr, start, mid-1);
    root->right = sortedArrayToBST(arr, mid+1, end);
 
    return root;
}

node* newNode(char *data)
{
    node* Node = (node*)malloc(sizeof(node));
    strcpy(Node->data, data);
    Node->left = NULL;
    Node->right = NULL;
 
    return Node;
}
