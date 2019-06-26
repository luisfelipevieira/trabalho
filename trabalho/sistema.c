#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "complemento.h"
#include "area.h"
#include "fornecedor.h"

void menu_principal();
void menu_fornecedor();
void menu_area();

int main(){
	
	FILE *fornecedor, *area;
	
	fornecedor = fopen("fornecedor.txt", "r");
	area = fopen("area.txt", "r");
	
	if(!fornecedor){
		
		fornecedor = fopen("fornecedor.txt", "w");
		fclose(fornecedor);
	}
	
	if(!area){
		
		area = fopen("area.txt", "w");
		fclose(area);
	}
	
	menu_principal();
	
	system("clear");
	return 0;
}

		// MENU PRINCIPAL

void menu_principal(){
	
	int x;
	
	while(1){
		
		system("clear");
		
		printf("=====================================================\n\n");
		printf("[1] - Fornecedor\n");
		printf("[2] - Area\n");
		printf("[3] - Listar fornecedor agrupado por area\n");
		printf("[4] - Sair\n\n");
		printf("=====================================================\n\n");
		
		do{
			printf("Digite o numero da opcao desejada: ");
			scanf("%d", &x);
			if(x<1 || x>4) printf("\n\t\tValor Invalido, Digite novamente!\n\n");
			
		}while(x<1 || x>4);
		
		if(x==1) menu_fornecedor();
		else if(x==2) menu_area();
		else if(x==3) listar_fornecedor_area(); // Função na biblioteca "complemento.h"
		else break;
	}
}

		// MENU FORNECEDOR

void menu_fornecedor(){
	
	int x;
	
	while(1){
		
		system("clear");
		
		printf("=====================================================\n\n");
		printf("[1] - Incluir Fornecedor\n");
		printf("[2] - Consultar Fornecedor\n");
		printf("[3] - Listar Fornecedor\n");
		printf("[4] - Excluir Fornecedor\n");
		printf("[5] - Alterar Fornecedor\n");
		printf("[6] - Voltar\n\n");
		printf("=====================================================\n\n");
		
		do{
			printf("Digite o numero da opcao desejada: ");
			scanf("%d", &x);
			if(x<1 || x>6) printf("\n\t\tValor Invalido, Digite novamente!\n\n");
			
		}while(x<1 || x>6);
		
		if(x==1) incluir_fornecedor(); // Função na biblioteca "fornecedor.h"
		else if(x==2) consultar_fornecedor(); // Função na biblioteca "fornecedor.h"
		else if(x==3) listar_fornecedor(); // Função na biblioteca "fornecedor.h"
		else if(x==4) excluir_fornecedor(); // Função na biblioteca "fornecedor.h"
		else if(x==5) alterar_fornecedor(); // Função na biblioteca "fornecedor.h"
		else break;
	}
}

		// MENU AREA

void menu_area(){
	
	int x;
	
	while(1){
		
		system("clear");
		
		printf("=====================================================\n\n");
		printf("[1] - Incluir Area\n");
		printf("[2] - Consultar Area\n");
		printf("[3] - Listar Area\n");
		printf("[4] - Excluir Area\n");
		printf("[5] - Alterar Area\n");
		printf("[6] - Voltar\n\n");
		printf("=====================================================\n\n");
		
		do{
			printf("Digite o numero da opcao desejada: ");
			scanf("%d", &x);
			if(x<1 || x>6) printf("\n\t\tValor Invalido, Digite novamente!\n\n");
			
		}while(x<1 || x>6);
		
		if(x==1) incluir_area(); // Função na biblioteca "area.h"
		else if(x==2) consultar_area(); // Função na biblioteca "area.h"
		else if(x==3) listar_area(); // Função na biblioteca "area.h"
		else if(x==4) excluir_area(); // Função na biblioteca "area.h"
		else if(x==5) alterar_area(); // Função na biblioteca "area.h"
		else break;
	}
}
