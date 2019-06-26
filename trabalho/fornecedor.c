typedef struct{
	
	char nome[50], representante[50], cnpj[20], telefone[20];
	char situacao;
	int ano, codarea;
	float caps;
	
}FORNECEDOR;
	
	// INCLUIR

void incluir_fornecedor(){
	
	FILE *arquivo;
	FORNECEDOR x;
	int pont = 0;
	
	do{
		
		printf("\nCodigo de area: ");
		scanf("%d", &x.codarea);
		
		verifica_area(x.codarea, "insdisponivel", &pont, 0, 'I'); // Função na biblioteca "complemento.h"
		
		if(pont==0) printf("\n\t\tArea inexistente! Digite novamente\n");
		
	}while(pont==0);
	
	pont = 0;
	
	printf("Nome da Empresa: ");
	scanf(" %[^\n]", x.nome);
	
	printf("Nome do Representante: ");
	scanf(" %[^\n]", x.representante);
	
	printf("CNPJ - xx.xxx.xxx/xxxx-xx: ");
	scanf(" %[^\n]", x.cnpj);
	
	printf("Capital Social (R$): ");
	scanf("%f", &x.caps);
	
	printf("Telefone - (xx)xxxxx-xxxx: ");
	scanf(" %[^\n]", x.telefone);
	
	printf("Ano de Cadastro: ");
	scanf("%d", &x.ano);
	
	do{
		printf("Situacao - (A/I): ");
		scanf(" %c", &x.situacao);
		if(x.situacao!='A' && x.situacao!='I') printf("\n\t\tSituacao invalida! Digite apenas A (Ativo) ou I (Inativo)!\n\n");
		
	}while(x.situacao!='A' && x.situacao!='I');
	
	verifica_cadastro_fornecedor(x.cnpj, &pont, 0, 'I'); // Função na biblioteca "complemento.h"
	
	if(pont==0){
		
		arquivo = fopen("fornecedor.txt", "a");
	
		if(arquivo == NULL){
			 
			printf("Erro na abertura do arquivo! Pressione enter para voltar...\n");
		
			getchar();
			getchar();	
			return;
		}
		
		fprintf(arquivo, "%d\t%s\t%s\t%s\t%.2f\t%s\t%d\t%c\n", x.codarea,
														   x.nome,
														   x.representante,
														   x.cnpj, x.caps,
														   x.telefone, x.ano, x.situacao);
	
		printf("\n\nFornecedor incluido com sucesso! Pressione enter para voltar...");
		
		fclose(arquivo);
		
	}else if(pont==1) printf("\n\nEmpresa ja possui cadastro! Pressione enter para voltar...");
		
	getchar();
	getchar();
}

	// LISTAR

void listar_fornecedor(){
	
	FILE *arquivo;
	int cont, i, j, a;
	FORNECEDOR copia;
	
	cont = contador_fornecedor(); // Função na biblioteca "complemento.h"
	
	FORNECEDOR x[cont];
    
    arquivo = fopen("fornecedor.txt", "r");
    
    if(arquivo == NULL){
		 
		printf("Erro na abertura do arquivo! Pressione enter para voltar...\n");
		
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
	
	printf("\n[1] - Ordenar por Area\n[2] - Ordenar por CNPJ\n\n");
	
	do{
		printf("Digite o numero da opcao desejada: ");
		scanf("%d", &a);
		if(a<1 || a>2) printf("\n\t\tValor Invalido, Digite novamente!\n\n");
			
	}while(a<1 || a>2);
	
	if(a==1){
		
		for(i=0; i<cont; i++){
			for(j=i+1; j<cont; j++){
				
				if(x[j].codarea<x[i].codarea){
					
					copia = x[i];
					x[i] = x[j];
					x[j] = copia;
				}
			}
		}
		
	}else if(a==2){
		
		for(i=0; i<cont; i++){
			for(j=i+1; j<cont; j++){
				
				if(strcmp(x[j].cnpj, x[i].cnpj) < 0){
					
					copia = x[i];
					x[i] = x[j];
					x[j] = copia;
				}
			}
		}
	}
    
    system("clear");
	
	printf("%-13s%-22s%-13s%-11s%s\n\n", "Area", "CNPJ", "Telefone", "Situacao", "Empresa");
	
	for(i=0; i<cont; i++) printf("%-7d%s\t%s\t    %c\t   %s\n", x[i].codarea,
																x[i].cnpj,
																x[i].telefone,
																x[i].situacao, x[i].nome);
	
	printf("\n\nPressione enter para continuar...");
	
	getchar();
	getchar();
	
	fclose(arquivo);
}

	// CONSULTA

void consultar_fornecedor(){

	FILE *arquivo;
	char aux_cnpj[20];
	int cont, i, a;
	
	a = 0;
	
	cont = contador_fornecedor(); // Função na biblioteca "complemento.h"
	
	FORNECEDOR x[cont];
	
	arquivo = fopen("fornecedor.txt", "r");
	
	if(arquivo == NULL){
		 
		printf("Erro na abertura do arquivo! Pressione enter para voltar...\n");
		
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
	
	system("clear");
	
	printf("Digite o CNPJ a ser consultado: ");
	scanf(" %[^\n]", aux_cnpj);
	
	for(i=0; i<cont; i++){
		
		if(strcmp(aux_cnpj, x[i].cnpj) == 0){
			
			a = 1;
			
			printf("\n%-16s: %s\n", "Empresa", x[i].nome);
			printf("%-16s: %s\n", "Representante", x[i].representante);
			printf("%-16s: %s\n", "CNPJ", x[i].cnpj);
			printf("%-16s: %s\n", "Telefone", x[i].telefone);
			printf("%-16s: R$ %.2f\n", "Capital Social", x[i].caps);
			printf("%-16s: %d\n", "Ano de cadastro", x[i].ano);
			printf("%-16s: %d\n", "Codigo de area", x[i].codarea);
			printf("%-16s: %c\n\n", "Situacao", x[i].situacao);
		}
	}
	
	if(a==0) printf("\n\tCNPJ %s nao possui cadastro!\n", aux_cnpj);
	
	printf("\nPressione enter para continuar...");
	
	getchar();
	getchar();
	
	fclose(arquivo);
}

	// ALTERAR

void alterar_fornecedor(){
	
	FILE *arquivo;
	char aux_cnpj[20];
	int cont, linha, a, i, b, pont, pont_cnpj;
	
	pont_cnpj = 0;
	pont = 0;
	a = 0;
	
	cont = contador_fornecedor(); // Função na biblioteca "complemento.h"
	
	FORNECEDOR x[cont];
	
	arquivo = fopen("fornecedor.txt", "r");
	
	if(arquivo == NULL){
		 
		printf("Erro na abertura do arquivo! Pressione enter para voltar...\n");
		
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
	system("clear");
	
	printf("Digite o CNPJ da empresa a ser alterada: ");
	scanf(" %[^\n]", aux_cnpj);
	
	for(i=0; i<cont; i++){
		
		if(strcmp(aux_cnpj, x[i].cnpj) == 0){
			
			a = 1;
			linha = i;
			
			printf("\n\tDADOS ATUAIS\n\n");
			printf("%-16s: %s\n", "Empresa", x[i].nome);
			printf("%-16s: %s\n", "Representante", x[i].representante);
			printf("%-16s: %s\n", "CNPJ", x[i].cnpj);
			printf("%-16s: %s\n", "Telefone", x[i].telefone);
			printf("%-16s: R$ %.2f\n", "Capital Social", x[i].caps);
			printf("%-16s: %d\n", "Ano de cadastro", x[i].ano);
			printf("%-16s: %d\n", "Codigo de area", x[i].codarea);
			printf("%-16s: %c\n\n", "Situacao", x[i].situacao);
			
			break;
		}
	}
	
	if(a==0) printf("\n\tCNPJ %s nao possui cadastro!\n\nPressione enter para continuar...", aux_cnpj);
	else{
		
		printf("[1] - Alterar cadastro\n[2] - Voltar\n\n");
		
		do{
			printf("Digite o numero da opcao desejada: ");
			scanf("%d", &b);
			if(b<1 || b>2) printf("\n\t\tValor Invalido, Digite novamente!\n\n");
			
		}while(b<1 || b>2);
		
		if(b==1){
				
				// inserindo os novos dados
				
			printf("\n\tINSIRA OS NOVOS DADOS\n\n");
		
			printf("Empresa: "); scanf(" %[^\n]", x[linha].nome);
			printf("Representante: "); scanf(" %[^\n]", x[linha].representante);
			printf("CNPJ - xx.xxx.xxx/xxxx-xx: "); scanf(" %[^\n]", x[linha].cnpj);
			printf("Telefone - (xx)xxxxx-xxxx: "); scanf(" %[^\n]", x[linha].telefone);
			printf("Capital Social (R$): "); scanf("%f", &x[linha].caps);
			printf("Ano de Cadastro: "); scanf("%d", &x[linha].ano);
			do{
				printf("Codigo de area: ");
				scanf("%d", &x[linha].codarea);
		
				verifica_area(x[linha].codarea, "Indisponivel", &pont, 0, 'I'); // Função na biblioteca "complemento.h"
		
				if(pont==0) printf("\n\t\tArea inexistente! Digite novamente\n\n");
		
			}while(pont==0);
			
			do{
				printf("Situacao - (A/I): ");
				scanf(" %c", &x[linha].situacao);
				
				if(x[linha].situacao!='A' && x[linha].situacao!='I') printf("\n\t\tSituacao invalida! Digite apenas A (Ativo) ou I (Inativo)!\n\n");
		
			}while(x[linha].situacao!='A' && x[linha].situacao!='I');
			
			verifica_cadastro_fornecedor(x[linha].cnpj, &pont_cnpj, linha, 'A'); // Função na biblioteca "complemento.h"
			
			if(pont_cnpj==0){
				
				// salvando os novos dados no arquivo
			
				arquivo = fopen("fornecedor.txt", "w");
	
				if(arquivo == NULL){
					 
					printf("Erro na abertura do arquivo!! Pressione enter para voltar...\n");
		
					getchar();
					getchar();	
					return;
				}
	
				for(i=0; i<cont; i++) fprintf(arquivo, "%d\t%s\t%s\t%s\t%.2f\t%s\t%d\t%c\n", x[i].codarea,
																	   						 x[i].nome,
																	  						 x[i].representante,
																	   						 x[i].cnpj, x[i].caps,
																	   						 x[i].telefone, x[i].ano, x[i].situacao);
	
				printf("\nDados Alterados! Pressione enter para continuar...");
	
				fclose(arquivo);
				
			}else printf("\n\nCNPJ informado ja possui cadastro! Pressione enter para voltar...");
			
		}else if(b==2) return;
	}
	
	getchar();
	getchar();
}

	// EXCLUIR

void excluir_fornecedor(){
	
	FILE *arquivo;
	char aux_cnpj[20];
	int cont, linha, a, i, b;
	
	a = 0;
	
	cont = contador_fornecedor(); // Função na biblioteca "complemento.h"
	
	FORNECEDOR x[cont];
	
	arquivo = fopen("fornecedor.txt", "r");
	
	if(arquivo == NULL){
		 
		printf("Erro na abertura do arquivo! Pressione enter para voltar...\n");
		
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
	system("clear");
	
	printf("Digite o CNPJ da empresa a ser excluida: ");
	scanf(" %[^\n]", aux_cnpj);
	
	for(i=0; i<cont; i++){
		
		if(strcmp(aux_cnpj, x[i].cnpj) == 0){
			
			a = 1;
			linha = i;
			
			printf("\n\tDADOS REFERENTE AO CNPJ : %s\n\n", aux_cnpj);
			printf("%-16s: %s\n", "Empresa", x[i].nome);
			printf("%-16s: %s\n", "Representante", x[i].representante);
			printf("%-16s: %s\n", "CNPJ", x[i].cnpj);
			printf("%-16s: %s\n", "Telefone", x[i].telefone);
			printf("%-16s: R$ %.2f\n", "Capital Social", x[i].caps);
			printf("%-16s: %d\n", "Ano de cadastro", x[i].ano);
			printf("%-16s: %d\n", "Codigo de area", x[i].codarea);
			printf("%-16s: %c\n\n", "Situacao", x[i].situacao);
			
			break;
		}
	}
	
	if(a==0){
		
		printf("\n\tCNPJ %s nao possui cadastro!\n", aux_cnpj);
		printf("\nPressione enter para continuar...");
		
		getchar();
		getchar();
		
	}else{
		
		printf("[1] - Excluir cadastro\n[2] - Voltar\n\n");
		
		do{
			printf("Digite o numero da opcao desejada: ");
			scanf("%d", &b);
			if(b<1 || b>2) printf("\n\t\tValor Invalido, Digite novamente!\n\n");
			
		}while(b<1 || b>2);
		
		if(b==1){
			
			arquivo = fopen("fornecedor.txt", "w");
	
			if(arquivo == NULL){
				 
				printf("Erro na abertura do arquivo!! Pressione enter para voltar...\n");
		
				getchar();
				getchar();	
				return;
			}
			
			for(i=0; i<cont; i++){
				
				if(i==linha) continue;
				
				fprintf(arquivo, "%d\t%s\t%s\t%s\t%.2f\t%s\t%d\t%c\n", x[i].codarea,
														   			   x[i].nome,
														  			   x[i].representante,
														   			   x[i].cnpj, x[i].caps,
														   			   x[i].telefone, x[i].ano, x[i].situacao);
			}
			
			printf("\nCadastro excluido com sucesso! Pressione enter para continuar...");
	
			getchar();
			getchar();
	
			fclose(arquivo);
			
		}else if(b==2) return;
	}
}
