typedef struct{
	
	char nome[50], representante[50], cnpj[20], telefone[20];
	char situacao;
	int ano, codarea;
	float caps;
	
}FORNECEDOR_COMP;

typedef struct{
	
	char nome_area[50];
	int codigo;
	
}AREA_COMP;				
									
									// FUNÇÕES RELACIONADAS A AREA
									
									
									
	// CONTADOR DE AREAS CADASTRADAS

int contador_area(){
	
	FILE *arquivo;
	char aux[100];
	int x = 0;
	
	arquivo = fopen("area.txt", "r");
	
	if(arquivo == NULL){
		 
		printf("Erro na abertura do arquivo! Pressione enter para voltar...\n");
		
		getchar();
		getchar();	
		return 0;
	}
	
	while(fgets(aux, 100, arquivo) != NULL) x++;
	
	fclose(arquivo);
	return x;
}

	// VERIFICA SE O CODIGO E NOME DE AREA INFORMADO EXISTE

void verifica_area(int aux_codigo, char aux_nome_area[], int *p, int linha, char letra){
	
	FILE *arquivo;
	int cont, i;
	
	cont = contador_area(); // Função na biblioteca "complemento.h"
	
	AREA_COMP x[cont];
	
	arquivo = fopen("area.txt", "r");
	
	if(arquivo == NULL){
		 
		printf("Erro na abertura do arquivo! Pressione enter para voltar...\n");
		
		getchar();
		getchar();	
		return;
	}
	
	for(i=0; i<cont; i++) fscanf(arquivo,"%d %[^\n]", &x[i].codigo, x[i].nome_area);
	
	if(letra=='I'){
		
		for(i=0; i<cont; i++){
		
			if(aux_codigo==x[i].codigo || strcasecmp(aux_nome_area, x[i].nome_area) == 0){
			
				*p = 1;
				break;
			}
		}
	}else if(letra=='A'){
		
		for(i=0; i<cont; i++){
		
			if(i==linha) continue;
			if(aux_codigo==x[i].codigo || strcasecmp(aux_nome_area, x[i].nome_area) == 0){
			
				*p = 1;
				break;
			}
		}
	}
	
	fclose(arquivo);
}							
									
									// FUNÇÕES RELACIONADAS AO FORNECEDOR
									
									

	// CONTADOR DE FORNECEDORES CADASTRADOS

int contador_fornecedor(){
	
	FILE *arquivo;
	char aux[250];
	int x = 0;
	
	arquivo = fopen("fornecedor.txt", "r");
	
	if(arquivo == NULL){
		 
		printf("Erro na abertura do arquivo! Pressione enter para voltar...\n");
		
		getchar();
		getchar();	
		return 0;
	}
	
	while(fgets(aux, 250, arquivo) != NULL) x++;
	
	fclose(arquivo);	
	return x;
}


	// VERIFICA SE FORNECEDOR JÁ POSSUI CADASTRO

void verifica_cadastro_fornecedor(char aux_cnpj[], int *p, int linha, char letra){
	
	FILE *arquivo;
	int cont, i;
	
	cont = contador_fornecedor(); // Função na biblioteca "complemento.h"
	
	FORNECEDOR_COMP x[cont];
	
	arquivo = fopen("fornecedor.txt", "r");
	
	if(arquivo == NULL){
		 
		printf("Erro na abertura do arquivo! Pressione enter para voltar...\n");
		*p = 0;
		
		getchar();
		getchar();	
		return;
	}
	
	for(i=0; i<cont; i++) fscanf(arquivo,"%d %[^\t] %[^\t] %s %f %[^\t] %d %c", &x[i].codarea,
																				x[i].nome,
																				x[i].representante,
																				x[i].cnpj,
																				&x[i].caps,
																				x[i].telefone,
																				&x[i].ano, &x[i].situacao);
	
	fclose(arquivo);
	
	if(letra=='I'){
		
		for(i=0; i<cont; i++){
		
			if(strcmp(aux_cnpj, x[i].cnpj) == 0){
			
				*p = 1;
				break;
			}
		}
		
	}else if(letra=='A'){
		
		for(i=0; i<cont; i++){
		
			if(i==linha) continue;
			if(strcmp(aux_cnpj, x[i].cnpj) == 0){
			
				*p = 1;
				break;
			}
		}
	}
}


									// LISTAR FORNECEDORES POR AREA



void listar_fornecedor_area(){
	
	FILE *arquivo_forn, *arquivo_area;
	int cont_area, cont_forn;
	int i, j;
	
	AREA_COMP copia;
	
	cont_area = contador_area();
	cont_forn = contador_fornecedor();
	
	AREA_COMP x[cont_area];
	FORNECEDOR_COMP y[cont_forn];
	
	// Lendo os dados de area.txt
	
	arquivo_area = fopen("area.txt", "r");
	
	if(arquivo_area == NULL){
		 
		printf("Erro na abertura do arquivo! Pressione enter para voltar...\n");
		
		getchar();
		getchar();	
		return;
	}
	
	for(i=0; i<cont_area; i++) fscanf(arquivo_area,"%d %[^\n]", &x[i].codigo, x[i].nome_area);
	
	fclose(arquivo_area);
	
	// Lendo os dados de fornecedor.txt
	
	arquivo_forn = fopen("fornecedor.txt", "r");
	
	if(arquivo_forn == NULL){
		 
		printf("Erro na abertura do arquivo! Pressione enter para voltar...\n");
		
		getchar();
		getchar();	
		return;
	}
	
	for(i=0; i<cont_forn; i++) fscanf(arquivo_forn,"%d %[^\t] %[^\t] %s %f %[^\t] %d %c", &y[i].codarea,
																				y[i].nome,
																				y[i].representante,
																				y[i].cnpj,
																				&y[i].caps,
																				y[i].telefone,
																				&y[i].ano, &y[i].situacao);
	
	fclose(arquivo_forn);
	
	// Ordenando a Area por Código
	
	for(i=0; i<cont_area; i++){
		for(j=i+1; j<cont_area; j++){
			
			if(x[j].codigo<x[i].codigo){
				
				copia = x[i];
				x[i] = x[j];
				x[j] = copia;
			}
		}
	}
    
    system("clear");
    
    for(i=0; i<cont_area; i++){
    	
    	printf("\t\t\t[%d] - %s\n\n\n", x[i].codigo, x[i].nome_area);
    	
    	printf("%-13s%-22s%-13s%-11s%s\n\n", "Area", "CNPJ", "Telefone", "Situacao", "Empresa");
    	
		for(j=0; j<cont_forn; j++){
			
			if(y[j].codarea==x[i].codigo){
				
				printf("%-7d%s\t%s\t    %c\t   %s\n", y[j].codarea,
													  	  y[j].cnpj,
													  	  y[j].telefone,
													  	  y[j].situacao, y[j].nome);
			}
		}
		
		printf("\n\n");
	}
	
	printf("Pressione enter para continuar...");
	
	getchar();
	getchar();
}
