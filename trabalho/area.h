typedef struct{
	
	char nome_area[50];
	int codigo;
	
}AREA;

    // INCLUIR

void incluir_area(){
	
	FILE *arquivo;
	AREA x;
	int pont;
	
	pont = 0;
		
	printf("\nNome da Area: ");
	scanf(" %[^\n]", x.nome_area);
	
	printf("Codigo da Area: ");
	scanf("%d", &x.codigo);
	
	verifica_area(x.codigo, x.nome_area, &pont, 0, 'I'); // Função na biblioteca "complemento.h"
	
	if(pont==0){
		
		arquivo = fopen("area.txt", "a");
	
		if(arquivo == NULL){
			 
			printf("Erro na abertura do arquivo! Pressione enter para voltar...\n");
		
			getchar();
			getchar();	
			return;
		}
		
		fprintf(arquivo, "%d\t%s\n", x.codigo, x.nome_area);
	
		printf("\n\nArea incluida com sucesso! Pressione enter para voltar...");
		
		fclose(arquivo);
		
	}else printf("\n\nArea ja cadastrada! Pressione enter para voltar...");
		
	getchar();
	getchar();
}

    // LISTAR

void listar_area(){
	
	FILE *arquivo;
	AREA copia;
	int cont, i, j, a;
	
	cont = contador_area(); // Função na biblioteca "complemento.h"
	
	AREA x[cont];
	
	arquivo = fopen("area.txt", "r");
	
	if(arquivo == NULL){
		 
		printf("Erro na abertura do arquivo! Pressione enter para voltar...\n");
		
		getchar();
		getchar();	
		return;
	}
	
	for(i=0; i<cont; i++) fscanf(arquivo,"%d %[^\n]", &x[i].codigo, x[i].nome_area);
    
    printf("\n[1] - Ordenar por codigo\n[2] - Ordenar por nome\n\n");
    
    do{
		printf("Digite o numero da opcao desejada: ");
		scanf("%d", &a);
		if(a<1 || a>2) printf("\n\t\tValor Invalido, Digite novamente!\n\n");
			
	}while(a<1 || a>2);
	
	if(a==1){
		
		for(i=0; i<cont; i++){
			for(j=i+1; j<cont; j++){
				
				if(x[j].codigo<x[i].codigo){
					
					copia = x[i];
					x[i] = x[j];
					x[j] = copia;
				}
			}
		}
		
	}else if(a==2){
		
		for(i=0; i<cont; i++){
			for(j=i+1; j<cont; j++){
				
				if(strcmp(x[j].nome_area, x[i].nome_area) < 0){
					
					copia = x[i];
					x[i] = x[j];
					x[j] = copia;
				}
			}
		}
	}
	
	system("clear");
	
	printf("%-13s%-22s\n\n", "Codigo", "Nome");
	
	for(i=0; i<cont; i++) printf("%-11d%s\n", x[i].codigo, x[i].nome_area);
	
	printf("\n\nPressione enter para continuar...");
	
	getchar();
	getchar();
	
	fclose(arquivo);
}

	// CONSULTA

void consultar_area(){

	FILE *arquivo;
	int cont, i, a, aux_codigo;
	
	a = 0;
	
	cont = contador_area(); // Função na biblioteca "complemento.h"
	
	AREA x[cont];
	
	arquivo = fopen("area.txt", "r");
	
	if(arquivo == NULL){
		 
		printf("Erro na abertura do arquivo! Pressione enter para voltar...\n");
		
		getchar();
		getchar();	
		return;
	}
	
	for(i=0; i<cont; i++) fscanf(arquivo,"%d %[^\n]", &x[i].codigo, x[i].nome_area);
	
	system("clear");
	
	printf("Digite o codigo da area a ser consultada: ");
	scanf("%d", &aux_codigo);
	
	for(i=0; i<cont; i++){
		
		if(aux_codigo==x[i].codigo){
			
			a = 1;
			
			printf("\n%-8s: %s\n", "Area", x[i].nome_area);
			printf("%-8s: %d\n", "Codigo", x[i].codigo);
		}
	}
	
	if(a==0) printf("\n\tCodigo de area: '%d' nao possui cadastro!\n", aux_codigo);
	
	printf("\nPressione enter para continuar...");
	
	getchar();
	getchar();
	
	fclose(arquivo);
}

	// ALTERAR

void alterar_area(){
	
	FILE *arquivo;
	int cont, linha, pont, a, i, b, aux_codigo;
	
	pont = 0;
	a = 0;
	
	cont = contador_area(); // Função na biblioteca "complemento.h"
	
	AREA x[cont];
	
	arquivo = fopen("area.txt", "r");
	
	if(arquivo == NULL){
		 
		printf("Erro na abertura do arquivo! Pressione enter para voltar...\n");
		
		getchar();
		getchar();	
		return;
	}
	
	for(i=0; i<cont; i++) fscanf(arquivo,"%d %[^\n]", &x[i].codigo, x[i].nome_area);
	
	fclose(arquivo);
	system("clear");
	
	printf("Digite o codigo da area a ser alterada: ");
	scanf("%d", &aux_codigo);
	
	for(i=0; i<cont; i++){
		
		if(aux_codigo==x[i].codigo){
			
			a = 1;
			linha = i;
			
			printf("\n\tDADOS ATUAIS\n\n");
			printf("%-8s: %s\n", "Area", x[i].nome_area);
			printf("%-8s: %d\n\n", "Codigo", x[i].codigo);
			
			break;
		}
	}
	
	if(a==0) printf("\n\tCodigo de area: '%d' nao possui cadastro!\n\nPressione enter para continuar...", aux_codigo);
	else{
		
		printf("[1] - Alterar cadastro\n[2] - Voltar\n\n");
		
		do{
			printf("Digite o numero da opcao desejada: ");
			scanf("%d", &b);
			if(b<1 || b>2) printf("\n\t\tValor Invalido, Digite novamente!\n\n");
			
		}while(b<1 || b>2);
		
		if(b==1){
			
			printf("\n\tINSIRA OS NOVOS DADOS\n\n");
		
			printf("Nome da Area: "); scanf(" %[^\n]", x[linha].nome_area);
			printf("Codigo da Area: "); scanf("%d", &x[linha].codigo);
			
			verifica_area(x[linha].codigo, x[linha].nome_area, &pont, linha, 'A'); // Função na biblioteca "complemento.h"
			
			if(pont==0){
				
				// Salvando os novos dados no arquivo
				
				arquivo = fopen("area.txt", "w");
	
				if(arquivo == NULL){
					 
					printf("Erro na abertura do arquivo!! Pressione enter para voltar...\n");
		
					getchar();
					getchar();	
					return;
				}
			
				for(i=0; i<cont; i++) fprintf(arquivo, "%d\t%s\n", x[i].codigo, x[i].nome_area);
	
				printf("\nDados Alterados! Pressione enter para continuar...");
			
				fclose(arquivo);
				
			}else printf("\n\nArea ja cadastrada! Pressione enter para voltar...");
			
		}else if(b==2) return;
	}
		
	getchar();
	getchar();
}

	// EXCLUIR

void excluir_area(){
	
	FILE *arquivo;
	int cont, linha, a, i, b, aux_codigo;
	
	a = 0;
	
	cont = contador_area(); // Função na biblioteca "complemento.h"
	
	AREA x[cont];
	
	arquivo = fopen("area.txt", "r");
	
	if(arquivo == NULL){
		 
		printf("Erro na abertura do arquivo! Pressione enter para voltar...\n");
		
		getchar();
		getchar();	
		return;
	}
	
	for(i=0; i<cont; i++) fscanf(arquivo,"%d %[^\n]", &x[i].codigo, x[i].nome_area);
	
	fclose(arquivo);
	system("clear");
	
	printf("Digite o codigo da area a ser excluida: ");
	scanf("%d", &aux_codigo);
	
	for(i=0; i<cont; i++){
		
		if(aux_codigo==x[i].codigo){
			
			a = 1;
			linha = i;
			
			printf("\n\tDADOS REFERENTE A AREA : %d\n\n", aux_codigo);
			printf("%-8s: %s\n", "Area", x[i].nome_area);
			printf("%-8s: %d\n\n", "Codigo", x[i].codigo);
			
			break;
		}
	}
	
	if(a==0) printf("\n\tCodigo de area: '%d' nao possui cadastro!\n\nPressione enter para continuar...", aux_codigo);
	else{
		
		printf("[1] - Excluir cadastro\n[2] - Voltar\n\n");
		
		do{
			printf("Digite o numero da opcao desejada: ");
			scanf("%d", &b);
			if(b<1 || b>2) printf("\n\t\tValor Invalido, Digite novamente!\n\n");
			
		}while(b<1 || b>2);
		
		if(b==1){
			
				// Inserindo os novos dados no arquivo
			
			arquivo = fopen("area.txt", "w");
	
			if(arquivo == NULL){
				 
				printf("Erro na abertura do arquivo!! Pressione enter para voltar...\n");
		
				getchar();
				getchar();	
				return;
			}
			
			for(i=0; i<cont; i++){
				
				if(i==linha) continue;
				
				fprintf(arquivo, "%d\t%s\n", x[i].codigo, x[i].nome_area);
			}
			
			printf("\nCadastro excluido com sucesso! Pressione enter para continuar...");
	
			fclose(arquivo);
			
		}else if(b==2) return;
	}
	
	getchar();
	getchar();
}
