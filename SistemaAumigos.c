 //Software desenvolvido pela empresa INNOVATECH
//Devs:
	//BRENO BATISTA DE OLIVEIRA 
	//JOAO LUCAS DA SILVA 
	//LEANDRO GASQUE DE MELO 
	//MARCELO MAJARON BALIZARDO 


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#define tfstring 100
#define tfRelatorioHoras 300

//==================================== STRUCTS:

float caixa;

typedef struct{
	char nome [tfstring], cpf[tfstring], telefone[tfstring];
}voluntarios;

typedef struct{
	char nome[tfstring], descricao[tfstring];
	int qtdVoluntario, cod;
	float custo;
}projetos;

typedef struct{
	char nome[tfstring], local[tfstring];
	int dia, mes, ano, qtdVoluntario, cod;
}atividades;

typedef struct{
	char nome[tfstring], cnpj[tfstring], telefone[tfstring], contribuicao[tfstring];
}empresas;

typedef struct{
	char nome[tfstring], cpf[30], objetos[tfstring];
	float valor; // fazer um loop nas doacoes e exibir o calculo
	int dia, mes, ano;
}doacoes;

typedef struct{
	char cpf[tfstring], cnpj[tfstring];
	int codigoProjeto, codigoAtividade, qtdhoras;
	float estoque;
}lancamentos;

typedef struct
{
	char nome[tfstring], cpf[tfstring];		
	int totalHoras;	
}relatorioHoras;

//==================================== FUNCOES:

//===== MENUS:

int menuPrincipal(){
	
	int opcao;
	
    printf("\n =============== MENU ===============");
    printf("\n\n 1 - Cadastrar <Voluntario,Empresa,Projeto,Doacoes,Atividade>."); 
    printf ("\n 2 - Alterar cadastros.");
    printf("\n 3 - Excluir cadastros.");
    printf("\n 4 - Relatorios.");
    printf("\n 5 - Lancar horas.");
    printf ("\n 6 - Valor arrecadado");
    printf("\n\n 0 - Finalizar.");
    printf("\n\n ====================================");
    printf("\n\n Opcao desejada: ");
    scanf(" %d", &opcao);
    
    return opcao;
}

int menuCadastro(){
	int opcao;
	system("cls");	
    printf("\n ======= CADASTRO =======");
    printf("\n\n 1 - Voluntario.");
    printf("\n 2 - Empresa.");
    printf("\n 3 - Projeto.");
    printf ("\n 4 - Atividade.");
    printf ("\n 5 - Doacoes.");
    printf("\n\n 0 - Retornar.");
    printf("\n\n ========================");
    printf("\n\n Opcao desejada: ");
    scanf(" %d", &opcao);
    
    return opcao;
}

int menuAlterar(){
	int opcao;
	system("cls");	
    printf("\n ======= ALTERAR =======");
    printf("\n\n 1 - Voluntario.");
    printf("\n 2 - Empresa.");
    printf("\n 3 - Projeto.");
    printf("\n 4 - Atividade.");
    printf("\n\n 0 - Retornar.");
    printf("\n\n ========================");
    printf("\n\n Opcao desejada: ");
    scanf(" %d", &opcao);
    
    return opcao;
}

int menuExcluir(){
	int opcao;
	system("cls");	
    printf("\n ======== EXCLUIR ========");
    printf("\n\n 1 - Voluntario.");
	printf("\n 2 - Empresa.");
    printf("\n 3 - Projeto.");
    printf("\n 4 - Atividade.");
    printf("\n\n 0 - Retornar.");
    printf("\n\n ========================");
    printf("\n\n Opcao desejada: ");
    scanf(" %d", &opcao);
    
    return opcao;
}

int menuRelatorios(){
	
	int opcao;
	system("cls");
	
	printf ("\n ======== RELATORIOS ========");
	printf ("\n\n1 - Voluntarios");
	printf ("\n2 - Empresas");
	printf ("\n3 - Projetos");
	printf ("\n4 - Atividades");
	printf ("\n5 - Doacoes");
	printf ("\n6 - Horas Lancadas");
	printf ("\n\n0 - Retornar");
	printf("\n\n ============================");
    printf("\n\n Opcao desejada: ");
    scanf(" %d", &opcao);
	
	return opcao;
}

//===== BUSCA:

int buscaVoluntario(FILE *arquivo,char cpf[])
{
	voluntarios voluntario;
	rewind(arquivo);
	fread(&voluntario,sizeof(voluntario),1,arquivo);
	while(!feof(arquivo) && strcmp(cpf,voluntario.cpf)!=0)
	  fread(&voluntario,sizeof(voluntario),1,arquivo);
	if(!feof(arquivo))
	   return(ftell(arquivo)-sizeof(voluntario));
	else
	   return -1;
}

int buscaRegistroVoluntario(FILE *arquivo, char cpf[], voluntarios *voluntario) 
{
	int pos = buscaVoluntario(arquivo, cpf);
	
	if(pos == -1)
		return -1;
		
	fseek(arquivo, pos, 0);
	fread(&*voluntario,sizeof(*voluntario),1,arquivo);
	return 1;
}

int buscaEmpresa(FILE *arquivo,char nome[])
{
	empresas empresa;
	rewind(arquivo);
	fread(&empresa,sizeof(empresa),1,arquivo);
	while(!feof(arquivo) && strcmp(nome,empresa.cnpj)!=0)
	  fread(&empresa,sizeof(empresa),1,arquivo);
	if(!feof(arquivo))  
	   return(ftell(arquivo)-sizeof(empresa));
	else
	   return -1;   
}

int buscaProjeto(FILE *arquivo,int cod)
{
	projetos projeto;
	rewind(arquivo);
	fread(&projeto,sizeof(projeto),1,arquivo);
	while(!feof(arquivo) && cod != projeto.cod)
	  fread(&projeto,sizeof(projeto),1,arquivo);
	if(!feof(arquivo))  
	   return(ftell(arquivo)-sizeof(projeto));
	else
	   return -1;   
}

int buscaAtividade(FILE *arquivo,int cod)
{
	atividades atividade;
	rewind(arquivo);
	fread(&atividade,sizeof(atividade),1,arquivo);
	while(!feof(arquivo) && cod != atividade.cod)
	  fread(&atividade,sizeof(atividade),1,arquivo);
	if(!feof(arquivo))
	   return(ftell(arquivo)-sizeof(atividade));
	else
	   return -1;   
}

//===== VOLUNTARIO:

void cadastrarVoluntario(){
	FILE *arquivo = fopen("OngVoluntarios.bin", "ab+");
	voluntarios voluntario;
	char cpf[30];
	int pos;
	
	if (arquivo == NULL) {
		printf("\nErro ao abrir o arquivo!!");
	} else {
		do {
			system("cls");
			printf("\n====================================");
			printf("\n=       CADASTRAR VOLUNTARIO       =");
			printf("\n====================================\n");
			
			printf("\nCPF: "); fflush(stdin);
			gets(cpf);
			pos=0;
			
			fseek(arquivo, 0, SEEK_SET);

			while (fread(&voluntario, sizeof(voluntario), 1, arquivo) == 1) {
				if (strcmp(voluntario.cpf, cpf) == 0) {
					pos = 1;
					printf("\n====================================");
					printf("\n=     Voluntario ja cadastrado     =");
					printf("\n====================================\n");
				}
			}

			if (pos == 0) {
				strcpy(voluntario.cpf, cpf);

				printf("Nome do voluntario: "); fflush(stdin);
				gets(voluntario.nome);

				printf("Telefone: "); fflush(stdin);
				gets(voluntario.telefone);

				fwrite(&voluntario, sizeof(voluntario), 1, arquivo);

				printf("\n======================================");
				printf("\n= Voluntario cadastrado com sucesso! =");
				printf("\n======================================\n");
				
				printf("\nDeseja cadastrar outro voluntario <s/n> ? \n");
			}
			if (pos == 1){
				printf("\nDeseja TENTAR cadastrar outro voluntario <s/n> ? \n");
			}

		} while(toupper(getche())=='S');

		fclose(arquivo);
	}
}


void alterarVoluntario(){
	FILE *arquivo = fopen ("OngVoluntarios.bin" , "rb+");
	voluntarios voluntario; char cpf[tfstring];
	int pos;
	if(arquivo == NULL)
		printf("\nErro ao abrir o arquivo !!");
	else
	{
			system("cls");
			printf("\n====================================");
			printf("\n=        ALTERAR VOLUNTARIO        =");
			printf("\n====================================\n");
			
			printf("\nCPF ou <ENTER> para cancelar: "); fflush(stdin);
			gets(voluntario.cpf);
			while(strcmp(voluntario.cpf,"\0")!=0)
			{
				pos=buscaVoluntario(arquivo,voluntario.cpf);
				if(pos==-1){
					printf("\n====================================\n");
					printf("=   VOLUNTARIO NAO CADASTRADO      =");
					printf("\n====================================\n");
				}
				  
				else
				{
					fseek(arquivo,pos,0);
					fread(&voluntario,sizeof(voluntario),1,arquivo);
					printf("\n====================================");
					printf("\n=  Dados encontrados com sucesso!  =");
					printf("\n====================================\n\n");
					printf("\nCPF: %s",voluntario.cpf);
					printf("\nNome do voluntario: %s",voluntario.nome);
					printf("\nTelefone: %s",voluntario.telefone);
					printf("\nDeseja alterar <s/n> ?\n");
					if(toupper(getche())=='S')
					{
						printf("\nNovo CPF: "); fflush(stdin);
						gets(cpf);
						
						int cpfValid = 1;
	                    fseek(arquivo, 0, SEEK_SET);
	                    while (fread(&voluntario, sizeof(voluntario), 1, arquivo) == 1) {
	                        if (strcmp(cpf, voluntario.cpf) == 0) {
	                        	printf("\n=======================================");
								printf("\n= CPF ja cadastrado, tente novamente. =");
								printf("\n=======================================\n");
	                            cpfValid = 0;
	                           
	                        }
	                    }
	                    while (!cpfValid) {
	                        printf("Digite outro CPF: "); fflush(stdin);
	                        gets(cpf);
	
	                       
	                        cpfValid = 1;
	                        fseek(arquivo, 0, SEEK_SET);
	                        while (fread(&voluntario, sizeof(voluntario), 1, arquivo) == 1) {
	                            if (strcmp(cpf,voluntario.cpf) == 0) {
	                                printf("\n=======================================");
									printf("\n= CPF ja cadastrado, tente novamente. =");
									printf("\n=======================================\n\n");
	                                cpfValid = 0; 
	                                
	                            }
	                        }
	                    }
	                    strcpy(voluntario.cpf,cpf);
	                    
						printf("\nNovo nome: "); fflush(stdin);
						gets(voluntario.nome);
						
						printf ("Novo telefone: "); fflush(stdin);
						gets(voluntario.telefone);

						fseek(arquivo,pos,0);
						fwrite(&voluntario,sizeof(voluntario),1,arquivo);
						printf("\n====================================");
						printf("\n=   Dados alterado com sucesso!    =");
						printf("\n====================================\n\n");
					}
				} 
				printf("\nCPF ou <ENTER> para cancelar:"); fflush(stdin);
		    	gets(voluntario.cpf);
			}
			fclose(arquivo);
	}	
}

void excluirVoluntario(){
	FILE *arquivo = fopen ("OngVoluntarios.bin" , "rb");
	voluntarios voluntario; char cpf[tfstring];
	int pos;
	if(arquivo == NULL)
		printf("\nErro ao abrir o arquivo !!");
	else
	{
			system("cls");
			printf("\n====================================");
			printf("\n=        EXCLUIR VOLUNTARIO        =");
			printf("\n====================================\n");
			
			printf("\nCPF ou <ENTER> para cancelar: "); fflush(stdin);
			gets(cpf);
			while(strcmp(cpf,"\0")!=0)
			{
				pos=buscaVoluntario(arquivo,cpf);
				if(pos==-1){
					printf("\n====================================\n");
					printf("=   VOLUNTARIO NAO CADASTRADO      =");
					printf("\n====================================\n");
				}
				else
				{
					fseek(arquivo,pos,0);
					fread(&voluntario,sizeof(voluntario),1,arquivo);
					printf("\n====================================");
					printf("\n=  Dados encontrados com sucesso!  =");
					printf("\n====================================\n");
					printf("\nNome do voluntario: %s",voluntario.nome);
					printf("\nCPF: %s",voluntario.cpf);
					printf("\nTelefone: %s",voluntario.telefone);
					printf("\nDeseja excluir <s/n> ?\n");
					if(toupper(getche())=='S')
					{
						FILE *temp=fopen("auxiliar.bin","wb");
						rewind(arquivo);
						fread(&voluntario,sizeof(voluntario),1,arquivo);
						while(!feof(arquivo))
						{
							if(strcmp(cpf,voluntario.cpf)!=0)
								fwrite(&voluntario,sizeof(voluntario),1,temp);
							fread(&voluntario,sizeof(voluntario),1,arquivo);
						}
						fclose(arquivo);
						fclose(temp);
						remove("OngVoluntarios.bin");
						rename("auxiliar.bin","OngVoluntarios.bin");
						printf("\n\n====================================");
						printf("\n=   Dados excluidos com sucesso!   =");
						printf("\n====================================\n");
					}
				} 
				
				printf("\nCPF ou <ENTER> para cancelar: "); fflush(stdin);
				gets(cpf);
			}
			fclose(arquivo);
	}	
}

void relatorioVoluntario() {
    FILE *arquivo = fopen("OngVoluntarios.bin", "rb");
    voluntarios voluntario;

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!");
        return;
    } else {
        system("cls");
        printf("\n====================================");
        printf("\n=     RELATORIOS DE VOLUNTARIOS    =");
        printf("\n====================================\n");

        int pos = 0;
        while (fread(&voluntario, sizeof(voluntario), 1, arquivo) == 1) {
                pos = 1;
                printf("\nNome: %s\n", voluntario.nome);
                printf("CPF: %s\n", voluntario.cpf);
                printf("Telefone: %s\n", voluntario.telefone);
                printf("\n====================================\n");
        }

        if (pos == 0) {
            printf("\nNAO POSSUI NENHUM VOLUNTARIO CADASTRADO!\n");
            printf("\n====================================\n");
        }

        system("pause");
        fclose(arquivo);
    }
}

//===== EMPRESA:

void cadastrarEmpresa(){
	FILE *arquivo = fopen ("OngEmpresas.bin" , "ab+");
	empresas empresa; char cnpj[tfstring]; int pos;
	if(arquivo == NULL)
		printf("\nErro ao abrir o arquivo !!");
	else
	{
		do
		{
			system("cls");
			printf("\n====================================");
			printf("\n=        CADASTRAR EMPRESAS        =");
			printf("\n====================================\n");
			
			printf ("\nCNPJ: ");fflush(stdin);
			gets(cnpj);
			
			pos = 0;
			
			fseek(arquivo, 0, SEEK_SET);

			while (fread(&empresa, sizeof(empresa), 1, arquivo) == 1) {
				if (strcmp(empresa.cnpj, cnpj) == 0) {
					pos = 1;
					printf("\n====================================");
					printf("\n=       Empresa ja cadastrada      =");
					printf("\n====================================\n");
				}
			}
			if (pos == 0){
				strcpy(empresa.cnpj, cnpj);
				
				printf ("Nome da empresa: ");fflush(stdin);
				gets (empresa.nome);
			
				printf ("Telefone: ");fflush(stdin);
				gets(empresa.telefone);
				
				printf ("Contribuicao: ");fflush(stdin);
				gets(empresa.contribuicao);
				
				fwrite(&empresa, sizeof(empresa), 1, arquivo);
				
				printf("\n====================================");
				printf("\n=  Empresa cadastrada com sucesso! =");
				printf("\n====================================\n");
				
				printf("\nDeseja cadastrar outra empresa <s/n> ? \n");
			}
			if (pos == 1){
				printf("\nDeseja TENTAR cadastrar outra empresa <s/n> ? \n");
			}
			
		}while(toupper(getche())=='S');
		fclose(arquivo);
	}	
}

void alterarEmpresa(){
	FILE *arquivo = fopen ("OngEmpresas.bin" , "rb+");
	empresas empresa; char cnpj[tfstring];
	int pos;
	if(arquivo == NULL)
		printf("\nErro ao abrir o arquivo !!");
	else
	{
			system("cls");
			printf("\n====================================");
			printf("\n=         ALTERAR EMPRESAS         =");
			printf("\n====================================\n");
			
			printf("\nCNPJ da empresa ou <ENTER> para cancelar: "); fflush(stdin);
			gets(empresa.cnpj);
			while(strcmp(empresa.cnpj,"\0")!=0)
			{
				pos=buscaEmpresa(arquivo,empresa.cnpj);
				if(pos==-1){
					printf("\n====================================\n");
					printf("=      EMPRESA NAO CADASTRADA      =");
					printf("\n====================================\n");
				}
				else
				{
					fseek(arquivo,pos,0);
					fread(&empresa,sizeof(empresa),1,arquivo);
					printf("\n====================================");
					printf("\n=  Dados encontrados com sucesso!  =");
					printf("\n====================================\n");
					printf("\nCNPJ: %s", empresa.cnpj);
					printf("\nNome da empresa: %s",empresa.nome);
					printf("\nTelefone: %s",empresa.telefone);
					printf("\nContribuicao: %s", empresa.contribuicao);
					printf("\nDeseja alterar <s/n> ?\n");
					if(toupper(getche())=='S')
					{
						printf("\nNovo CNPJ: "); fflush(stdin);
						gets(cnpj);
						
						int cnpjValid = 1;
	                    fseek(arquivo, 0, SEEK_SET);
	                    while (fread(&empresa, sizeof(empresa), 1, arquivo) == 1) {
	                        if (strcmp(cnpj,empresa.cnpj) == 0) {
	                            printf("\n==========================================");
								printf("\n=  CNPJ ja cadastrado, tente novamente.  =");
								printf("\n==========================================\n\n");
	                            cnpjValid = 0; 
	                            
	                        }
	                    }
	                    while (!cnpjValid) {
	                        printf("Digite outro CNPJ: "); fflush(stdin);
	                        gets(cnpj);
	
	                        
	                        cnpjValid = 1;
	                        fseek(arquivo, 0, SEEK_SET);
	                        while (fread(&empresa, sizeof(empresa), 1, arquivo) == 1) {
	                            if (strcmp(cnpj, empresa.cnpj) == 0) {
	                                printf("\n==========================================");
									printf("\n=  CNPJ ja cadastrado, tente novamente.  =");
									printf("\n==========================================\n");
	                                cnpjValid = 0; 
	                            }
	                        }
	                    }
	                    strcpy(empresa.cnpj,cnpj);
	                    
						printf("Novo nome: "); fflush(stdin);
						gets(empresa.nome);
						printf ("Novo telefone: "); fflush(stdin);
						gets(empresa.telefone);
						printf ("Nova contribuicao: "); fflush(stdin);
						gets(empresa.contribuicao);
						fseek(arquivo,pos,0);
						fwrite(&empresa,sizeof(empresa),1,arquivo);
						printf("\n====================================");
						printf("\n=   Dados alterado com sucesso!    =");
						printf("\n====================================\n");
					}
				} 
				printf("\nCNPJ da empresa ou <ENTER> para cancelar: "); fflush(stdin);
				gets(empresa.cnpj);
			}
			fclose(arquivo);
	}	
}

void excluirEmpresa(){
	FILE *arquivo = fopen ("OngEmpresas.bin" , "rb");
	empresas empresa; char cnpj[tfstring];
	int pos;
	if(arquivo == NULL)
		printf("\nErro ao abrir o arquivo !!");
	else
	{
			system("cls");
			printf("\n====================================");
			printf("\n=         EXCLUIR EMPRESA          =");
			printf("\n====================================\n");
			
			printf("\nCNPJ ou <ENTER> para cancelar: "); fflush(stdin);
			gets(cnpj);
			while(strcmp(cnpj,"\0")!=0)
			{
				pos=buscaEmpresa(arquivo,cnpj);
				if(pos==-1){
					printf("\n====================================\n");
					printf("=      EMPRESA NAO CADASTRADA      =");
					printf("\n====================================\n");
				}
				else
				{
					fseek(arquivo,pos,0);
					fread(&empresa,sizeof(empresa),1,arquivo);
					printf("\n====================================");
					printf("\n=  Dados encontrados com sucesso!  =");
					printf("\n====================================\n");
					printf("\nNome da empresa: %s",empresa.nome);
					printf("\nCNPJ: %s", empresa.cnpj);
					printf("\nTelefone: %s",empresa.telefone);
					printf("\nContribuicao: %s", empresa.contribuicao);
					printf("\nDeseja excluir <s/n> ?\n");
					if(toupper(getche())=='S')
					{
						FILE *temp=fopen("auxiliar.bin","wb");
						rewind(arquivo);
						fread(&empresa,sizeof(empresa),1,arquivo);
						while(!feof(arquivo))
						{
							if(strcmp(cnpj,empresa.cnpj)!=0)
								fwrite(&empresa,sizeof(empresa),1,temp);
							fread(&empresa,sizeof(empresa),1,arquivo);
						}
						fclose(arquivo);
						fclose(temp);
						remove("OngEmpresas.bin");
						rename("auxiliar.bin","OngEmpresas.bin");
						printf("\n\n====================================");
						printf("\n=   Dados excluidos com sucesso!   =");
						printf("\n====================================\n");
					}
				} 
				printf("\nCNPJ ou <ENTER> para cancelar:"); fflush(stdin);
		    	gets(cnpj);
			}
			fclose(arquivo);
	}	
}
void relatorioEmpresa() {
    FILE *arquivo = fopen("OngEmpresas.bin", "rb");
    empresas empresa;

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!");
        return;
    } else {
        system("cls");
        printf("\n====================================");
        printf("\n=      RELATORIOS DE EMPRESAS      =");
        printf("\n====================================\n");

        int pos = 0;
        while (fread(&empresa, sizeof(empresa), 1, arquivo) == 1) {
                pos = 1;
                printf("\nNome da empresa: %s\n", empresa.nome);
                printf("CNPJ: %s\n", empresa.cnpj);
                printf("Telefone: %s\n", empresa.telefone);
                printf("Contribuicao: %s\n", empresa.contribuicao);
                printf("\n====================================\n");
        }

        if (pos == 0) {
            printf("\nNAO POSSUI NENHUMA EMPRESA CADASTRADA!\n");
            printf("\n====================================\n");
        }

        system("pause");
        fclose(arquivo);
    }
}

//===== PROJETO:

void cadastrarProjeto(){
	FILE *arquivo = fopen ("OngProjetos.bin" , "ab+");
	projetos projeto; int pos, cod;
	
	if(arquivo == NULL)
		printf("\nErro ao abrir o arquivo !!");
	else
	{
		do
		{
			system("cls");
			printf("\n====================================");
			printf("\n=        CADASTRAR PROJETOS        =");
			printf("\n====================================\n");
			
			printf ("\nCodigo do projeto: ");
			scanf ("%d" , &cod);
			
			pos = 0;
			
			fseek(arquivo, 0, SEEK_SET);

			while (fread(&projeto, sizeof(projeto), 1, arquivo) == 1) {
				if (cod == projeto.cod){
					pos = 1;
					printf("\n=======================================");
					printf("\n=        Projeto ja cadastrado        =");
					printf("\n=======================================\n");
				}
			}
			if (pos == 0){
				projeto.cod = cod;
				
				printf ("Nome do projeto: ");fflush(stdin);
				gets(projeto.nome);
				
				printf ("Descricao: ");fflush(stdin);
				gets(projeto.descricao);
				
				printf ("Quantidade de participantes: ");
				scanf ("%d" ,&projeto.qtdVoluntario);
				
				printf ("Custo: R$");
				scanf("%f" , &projeto.custo);
				
				fwrite(&projeto, sizeof(projeto), 1, arquivo);
				
				printf("\n====================================");
				printf("\n=  Projeto cadastrado com sucesso! =");
				printf("\n====================================\n");
				
				printf("\nDeseja cadastrar outro projeto <s/n> ? \n");
			}
			if (pos == 1){
				printf("\nDeseja TENTAR cadastrar outro projeto <s/n> ? \n");
			}
			
		}while(toupper(getche())=='S');
		fclose(arquivo);
	}	
}

void alterarProjeto(){
	FILE *arquivo = fopen ("OngProjetos.bin" , "rb+");
	projetos projeto;
	int pos, cod;
	if(arquivo == NULL)
		printf("\nErro ao abrir o arquivo !!");
	else
	{ 
			system("cls");
			printf("\n====================================");
			printf("\n=         ALTERAR PROJETOS         =");
			printf("\n====================================\n");
			
			printf("\nCodigo do projeto ou <0> para cancelar: ");
			scanf("%d" , &cod);
			while(cod != 0)
			{
				pos=buscaProjeto(arquivo,cod);
				if(pos==-1){
					printf("\n====================================");
					printf("\n=      PROJETO NAO CADASTRADO      =");
					printf("\n====================================\n");
				}
				else
				{
					fseek(arquivo,pos,0);
					fread(&projeto,sizeof(projeto),1,arquivo);
					printf("\n====================================");
					printf("\n=  Dados encontrados com sucesso!  =");
					printf("\n====================================\n");
					printf ("\nCodigo do projeto: %d" , projeto.cod);
					printf ("\nNome do Projeto: %s" , projeto.nome);
					printf("\nDescricao: %s", projeto.descricao);
					printf("\nQuantidade de participantes: %d", projeto.qtdVoluntario);
					printf ("\nCusto: R$%.2f\n" , projeto.custo);
					printf("\nDeseja alterar <s/n> ?\n");
					if(toupper(getche())=='S')
					{
						printf ("\nNovo Codigo: ");
						scanf ("%d" , &cod);
						
						int codValid = 1;
	                    fseek(arquivo, 0, SEEK_SET);
	                    while (fread(&projeto, sizeof(projeto), 1, arquivo) == 1) {
	                        if (cod == projeto.cod) {
	                            printf("\n==========================================");
								printf("\n= Codigo ja cadastrado, tente novamente. =");
								printf("\n==========================================\n");
	                            codValid = 0; 
	                            
	                        }
	                    }
	                    while (!codValid) {
	                        printf("Digite outro CODIGO: ");
	                        scanf ("%d" , &cod);
	                        
	                        codValid = 1;
	                        fseek(arquivo, 0, SEEK_SET);
	                        while (fread(&projeto, sizeof(projeto), 1, arquivo) == 1) {
	                            if (cod == projeto.cod) {
	                                printf("\n==========================================");
									printf("\n= Codigo ja cadastrado, tente novamente. =");
									printf("\n==========================================\n");
	                                codValid = 0; 
	                               
	                            }
	                        }
	                    }
						projeto.cod = cod;
						
						printf ("Novo nome: "); fflush(stdin);
						gets (projeto.nome);
						printf ("Nova descricao: "); fflush(stdin);
						gets (projeto.descricao);
						printf ("Novos participantes: ");
						scanf("%d", &projeto.qtdVoluntario);
						printf ("Novo custo: R$");
						scanf("%f", &projeto.custo);
						fseek(arquivo,pos,0);
						fwrite(&projeto,sizeof(projeto),1,arquivo);
						printf("\n====================================");
						printf("\n=   Dados alterado com sucesso!    =");
						printf("\n====================================\n");
					}
				} 
				printf("\nCodigo do projeto ou <0> para cancelar: ");
				scanf("%d" , &cod);
			}
			fclose(arquivo);	
	}
}

void excluirProjeto(){
	FILE *arquivo = fopen ("OngProjetos.bin" , "rb");
	projetos projeto;
	int pos, cod;
	if(arquivo == NULL)
		printf("\nErro ao abrir o arquivo !!");
	else
	{
			system("cls");
			printf("\n====================================");
			printf("\n=         EXCLUIR PROJETO          =");
			printf("\n====================================\n");
			
			printf("\nCodigo do projeto ou <0> para cancelar: ");
			scanf("%d" , &cod);
			while(cod!=0)
			{
				pos=buscaProjeto(arquivo,cod);
				if(pos==-1){
					printf("\n====================================\n");
					printf("=      PROJETO NAO CADASTRADO      =");
					printf("\n====================================\n");
				}
				else
				{
					fseek(arquivo,pos,0);
					fread(&projeto,sizeof(projeto),1,arquivo);
					printf("\n====================================");
					printf("\n=  Dados encontrados com sucesso!  =");
					printf("\n====================================\n");
					printf ("\nCodigo do projeto: %d" , projeto.cod);
					printf ("\nNome do Projeto: %s" , projeto.nome);
					printf("\nDescricao: %s", projeto.descricao);
					printf("\nQuantidade de participantes: %d", projeto.qtdVoluntario);
					printf ("\nCusto: R$%.2f" , projeto.custo);
					printf("\nDeseja excluir <s/n> ?\n");
					if(toupper(getche())=='S')
					{
						FILE *temp=fopen("auxiliar.bin","wb");
						rewind(arquivo);
						fread(&projeto,sizeof(projeto),1,arquivo);
						while(!feof(arquivo))
						{
							if(cod != projeto.cod)
								fwrite(&projeto,sizeof(projeto),1,temp);
							fread(&projeto,sizeof(projeto),1,arquivo);
						}
						fclose(arquivo);
						fclose(temp);
						remove("OngProjetos.bin");
						rename("auxiliar.bin","OngProjetos.bin");
						printf("\n====================================");
						printf("\n=   Dados excluidos com sucesso!   =");
						printf("\n====================================\n");
					}
				}
				printf("\nCodigo do projeto ou <0> para cancelar:");
		    	scanf("%d" , &cod);
			}
			fclose(arquivo);
	}	
}

void relatorioProjeto() {
    FILE *arquivo = fopen("OngProjetos.bin", "rb");
    projetos projeto;

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!");
        return;
    } else {
        system("cls");
        printf("\n====================================");
        printf("\n=      RELATORIOS DE PROJETOS      =");
        printf("\n====================================\n");

        int pos = 0;
        while (fread(&projeto, sizeof(projeto), 1, arquivo) == 1) {
                pos = 1;
                printf ("\nCodigo do projeto: %d\n" , projeto.cod);
                printf("\nNome do Projeto: %s\n", projeto.nome);
                printf("Descricao: %s\n", projeto.descricao);
                printf("Quantidade de participantes: %d\n", projeto.qtdVoluntario);
                printf("Custo: R$%.2f\n", projeto.custo);
                printf("\n====================================\n");
            
        }

        if (pos == 0) {
            printf("\nNAO POSSUI NENHUM PROJETO CADASTRADO!\n");
            printf("\n====================================\n");
        }

        system("pause");
        fclose(arquivo);
    }
}

//===== ATIVIDADE:

void cadastrarAtividade(){
	FILE *arquivo = fopen ("OngAtividades.bin" , "ab+");
	atividades atividade; int pos, cod;
	if(arquivo == NULL)
		printf("\nErro ao abrir o arquivo !!");
	else
	{
		do
		{
			system("cls");
			printf("\n====================================");
			printf("\n=       CADASTRAR ATIVIDADE        =");
			printf("\n====================================\n");
			
			printf ("\nCodigo da atividade: ");
			scanf ("%d" , &cod);
			
			pos = 0;
			
			fseek(arquivo, 0, SEEK_SET);

			while (fread(&atividade, sizeof(atividade), 1, arquivo) == 1) {
				if (cod == atividade.cod){
					pos = 1;
					printf("\n=============================================");
					printf("\n= Atividade ja cadastrada, tente novamente. =");
					printf("\n=============================================\n");
				}
			}
			if (pos == 0){
				atividade.cod = cod;
				
				printf ("Nome da atividade: ");fflush(stdin);
				gets(atividade.nome);
				
				printf ("Local: ");fflush(stdin);
				gets(atividade.local);
				
				printf ("Data (dd mm aaaa): ");
				scanf ("%d %d %d" , &atividade.dia, &atividade.mes, &atividade.ano);
				
				printf ("Quantidade de participantes: ");fflush(stdin);
				scanf("%d", &atividade.qtdVoluntario);
				
				fwrite(&atividade, sizeof(atividade), 1, arquivo);
				
				printf("\n=======================================");
				printf("\n=  Atividade cadastrada com sucesso!  =");
				printf("\n=======================================\n");
				
				printf("\nDeseja cadastrar outra atividade <s/n> ? \n");
			}
			if (pos == 1){
				printf("\nDeseja TENTAR cadastrar outra atividade <s/n> ? \n");
			}
		
		}while(toupper(getche())=='S');
		fclose(arquivo);
	}	

}

void alterarAtividade(){
	FILE *arquivo = fopen ("OngAtividades.bin" , "rb+");
	atividades atividade;
	int pos, cod;
	if(arquivo == NULL)
		printf("\nErro ao abrir o arquivo !!");
	else
	{
			system("cls");
			printf("\n====================================");
			printf("\n=        ALTERAR ATIVIDADE         =");
			printf("\n====================================\n");
			
			printf("\nCodigo da atividade ou <0> para cancelar: ");
			scanf("%d", &cod);
			while(cod != 0)
			{
				pos=buscaAtividade(arquivo,cod);
				if(pos==-1){
					printf("\n====================================");
					printf("\n=     ATIVIDADE NAO CADASTRADA     =");
					printf("\n====================================\n");
				}
				else
				{
					fseek(arquivo,pos,0);
					fread(&atividade,sizeof(atividade),1,arquivo);
					printf("\n====================================");
					printf("\n=  Dados encontrados com sucesso!  =");
					printf("\n====================================\n");
					printf ("\nCodigo da atividade: %d" , atividade.cod);
					printf ("\nNome da Atividade: %s" , atividade.nome);
					printf("\nLocal: %s", atividade.local);
					printf ("\nData: %d/%d/%d" , atividade.dia, atividade.mes, atividade.ano);
					printf("\nQuantidade de participantes: %d\n", atividade.qtdVoluntario);
					printf("\nDeseja alterar <s/n> ?\n");
					if(toupper(getche())=='S')
					{
						printf ("Novo codigo: ");
						scanf ("%d" , &cod);
						
						int codValid = 1;
	                    fseek(arquivo, 0, SEEK_SET);
	                    while (fread(&atividade, sizeof(atividade), 1, arquivo) == 1) {
	                        if (cod == atividade.cod) {
	                            printf("\n=============================================");
								printf("\n= Atividade ja cadastrada, tente novamente. =");
								printf("\n=============================================\n");
	                            codValid = 0;
	                           
	                        }
	                    }
	
	                    while (!codValid) {
	                        printf("Digite outro CODIGO: ");
	                        scanf ("%d" , &cod);
	                        
	                        codValid = 1;
	                        fseek(arquivo, 0, SEEK_SET);
	                        while (fread(&atividade, sizeof(atividade), 1, arquivo) == 1) {
	                            if (cod == atividade.cod) {
	                                printf("\n=============================================");
									printf("\n= Atividade ja cadastrada, tente novamente. =");
									printf("\n=============================================\n");
	                                codValid = 0; 
	                                
	                            }
	                        }
	                    }
						atividade.cod = cod;
						
						printf ("\n\nNovo nome: "); fflush(stdin);
						gets (atividade.nome);
						printf ("Novo local: "); fflush(stdin);
						gets (atividade.local);
						printf ("Nova data (dd mm aaaa): ");
						scanf("%d %d %d", &atividade.dia, &atividade.mes, &atividade.ano);
						printf ("Novos participantes: ");
						scanf("%d", &atividade.qtdVoluntario);
						fseek(arquivo,pos,0);
						fwrite(&atividade,sizeof(atividade),1,arquivo);
						printf("\n====================================");
						printf("\n=   Dados alterado com sucesso!    =");
						printf("\n====================================\n\n");
					}
				} 
				printf("\nCodigo da atividade ou <0> para cancelar: ");
				scanf("%d" , &cod);
			}
			fclose(arquivo);	
		
	}
}

void excluirAtividade(){
	FILE *arquivo = fopen ("OngAtividades.bin" , "rb");
	atividades atividade;
	int pos, cod;
	if(arquivo == NULL)
		printf("\nErro ao abrir o arquivo !!");
	else
	{
			system("cls");
			printf("\n====================================");
			printf("\n=        EXCLUIR ATIVIDADE         =");
			printf("\n====================================\n");
			
			printf("\nCodigo da atividade ou <0> para cancelar: ");
			scanf("%d", &cod);
			while(cod != 0)
			{
				pos=buscaAtividade(arquivo,cod);
				if(pos==-1){
					printf("\n====================================");
					printf("\n=     ATIVIDADE NAO CADASTRADA     =");
					printf("\n====================================\n");
				}
				else
				{
					fseek(arquivo,pos,0);
					fread(&atividade,sizeof(atividade),1,arquivo);
					printf("\n====================================");
					printf("\n=  Dados encontrados com sucesso!  =");
					printf("\n====================================\n");
					printf ("\nCodigo da atividade: %d" , atividade.cod);
					printf ("\nNome da Atividade: %s" , atividade.nome);
					printf("\nLocal: %s", atividade.local);
					printf ("\nData: %d/%d/%d" , atividade.dia, atividade.mes, atividade.ano);
					printf("\nQuantidade de participantes: %d\n", atividade.qtdVoluntario);
					printf("\nDeseja excluir <s/n> ?\n");
					if(toupper(getche())=='S')
					{
						FILE *temp=fopen("auxiliar.bin","wb");
						rewind(arquivo);
						fread(&atividade,sizeof(atividade),1,arquivo);
						while(!feof(arquivo))
						{
							if(cod != atividade.cod)
								fwrite(&atividade,sizeof(atividade),1,temp);
							fread(&atividade,sizeof(atividade),1,arquivo);
						}
						fclose(arquivo);
						fclose(temp);
						remove("OngAtividades.bin");
						rename("auxiliar.bin","OngAtividades.bin");
						printf("\n====================================");
						printf("\n=   Dados excluidos com sucesso!   =");
						printf("\n====================================\n\n");
					}
				}
				printf("\nCodigo da atividade ou <0> para cancelar: ");
				scanf("%d", &cod);
			}
			fclose(arquivo);
	}	
}

void relatorioAtividade() {
    FILE *arquivo = fopen("OngAtividades.bin", "rb");
    atividades atividade;

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!");
        return;
    } else {
        system("cls");
        printf("\n====================================");
        printf("\n=     RELATORIOS DE ATIVIDADES     =");
        printf("\n====================================\n");

        int pos = 0;
        while (fread(&atividade, sizeof(atividade), 1, arquivo) == 1) {
                pos = 1;
                printf ("\nCodigo da atividade: %d" , atividade.cod);
                printf("\nNome da Atividade: %s\n", atividade.nome);
                printf("Local: %s\n", atividade.local);
                printf("Data: %d/%d/%d\n", atividade.dia, atividade.mes, atividade.ano);
                printf("Quantidade de participantes: %d\n", atividade.qtdVoluntario);
                printf("\n====================================\n");
        }

        if (pos == 0) {
            printf("\nNAO POSSUI NENHUMA ATIVIDADE CADASTRADA!\n");
            printf("\n====================================\n");
        }

        system("pause");
        fclose(arquivo);
    }
}

//===== HORAS:

void lancarHoras(){
	FILE *arquivoV = fopen ("OngVoluntarios.bin" , "rb");
	voluntarios voluntario;
	int pos, valid, qtdhora=0, codP, codA;
	char cpf[tfstring], cnpj[tfstring];
	if(arquivoV == NULL)
		printf("\nErro ao abrir o arquivo !!");
	else
	{
			system("cls");
			printf("\n====================================");
			printf("\n=         HORAS VOLUNTARIO         =");
			printf("\n====================================\n");
			
			printf("\nCPF ou <ENTER> para cancelar: "); fflush(stdin);
			gets(cpf);
			while(strcmp(cpf,"\0")!=0)
			{
				pos=buscaVoluntario(arquivoV,cpf);
				if(pos==-1){
					printf("\n====================================\n");
					printf("=   VOLUNTARIO NAO CADASTRADO      =");
					printf("\n====================================\n");
				}
				else
				{
					fseek(arquivoV,pos,0);
					fread(&voluntario,sizeof(voluntario),1,arquivoV);
					printf("\n====================================");
					printf("\n= Voluntario encontrado com sucesso! =");
					printf("\n====================================\n\n");
					printf("\nNome do voluntario: %s",voluntario.nome);
					printf ("\nCpf do voluntario: %s" , voluntario.cpf);
					printf ("\nTelefone: %s\n" , voluntario.telefone);
					printf("\nDeseja lancar horas <s/n> ?\n");
					if(toupper(getche())=='S')
					{
						system("cls");
						FILE *arquivoP = fopen("OngProjetos.bin","rb");
						projetos projeto;
						if(arquivoP == NULL)
							printf("\nErro ao abrir o arquivo !!");
						else{
							printf("\nCodigo do Projeto ou <0> para sair: ");
							scanf("%d", &codP);
							valid = buscaProjeto(arquivoP, codP);
							if(valid == -1){
								printf("\n====================================");
								printf("\n=      PROJETO NAO CADASTRADO      =");
								printf("\n====================================\n");
							}	
							else
							{
								fclose(arquivoP);
								FILE *arquivoA = fopen("OngAtividades.bin","rb");
								valid = 0; atividades atividade;
								if(arquivoA == NULL)
									printf("\nErro ao abrir o arquivo !!");
								else
								{
									printf("\nCodigo da Atividade exercida ou <0> para sair: ");
									scanf("%d", &codA);
									valid = buscaAtividade(arquivoA, codA);
									if(valid == -1){
										printf("\n====================================");
										printf("\n=     ATIVIDADE NAO CADASTRADA     =");
										printf("\n====================================\n");
									}	
									else
									{
										fclose(arquivoA);
										FILE *arquivoE = fopen("OngEmpresas.bin","rb");
										valid = 0; empresas empresa;
										if(arquivoE == NULL)
											printf("\nErro ao abrir o arquivo !!");
										else
										{
											printf("\nCNPJ da empresa parceira ou <ENTER> para sair: "); fflush(stdin);
											gets(cnpj);
											valid = buscaEmpresa(arquivoE, cnpj);
											if(valid == -1){
												printf("\n====================================");
												printf("\n=      EMPRESA NAO CADASTRADA      =");
												printf("\n====================================\n");
											}
											else
											{
												fclose(arquivoP);
												FILE *arquivoH = fopen("OngLancamentos.bin", "ab+");
												lancamentos lancamento;
												valid = 0;
												printf("\nQuantidade de horas a ser lancadas: ");
												scanf("%d" , &qtdhora);	
												pos=0;
												if(strcmp(lancamento.cpf,voluntario.cpf)==0){
														pos=1;
														printf ("%d\n" , lancamento.qtdhoras);
														lancamento.qtdhoras = qtdhora;
														printf ("%d\n" , lancamento.qtdhoras);
												}						
												if(pos==0){
													strcpy(lancamento.cpf,voluntario.cpf);
													lancamento.qtdhoras = qtdhora;
												}								
												fwrite(&lancamento,sizeof(lancamento),1,arquivoH);
												printf("\n====================================");
												printf("\n=   Horas lancadas com sucesso!    =");
												printf("\n====================================\n");
												fclose(arquivoH);
											}
										}
									}
								}
							}
						}
					}
				} 
				printf("\n");
				system("pause");
				system("cls");
				printf("\nCPF ou <ENTER> para cancelar: "); fflush(stdin);
				gets(cpf);
			}
			fclose(arquivoV);
	}	
}

void addRelatorioHorasLancadas(lancamentos lancamento, relatorioHoras relatorios[tfRelatorioHoras], int *tlRelatorio, voluntarios voluntario)
{
	int i, pos = -1;
	relatorioHoras novoRelatorioHora;
	

	for(i = 0; i < *tlRelatorio; i++)
	{
		if(strcmp(relatorios[i].cpf, lancamento.cpf) == 0)
		{
			pos = i;
			i = *tlRelatorio;
		}
	}
	

	if(pos != -1)		
		relatorios[pos].totalHoras += lancamento.qtdhoras;
	else 
	{
		strcpy(novoRelatorioHora.cpf, voluntario.cpf);
		strcpy(novoRelatorioHora.nome, voluntario.nome);
		novoRelatorioHora.totalHoras = lancamento.qtdhoras;
		relatorios[(*tlRelatorio)++] = novoRelatorioHora;
	}
}


void relatorioHorasLancadas() {	
	
	int tlRelatorio = 0, i, aux;
	
	FILE *arqVoluntarios = fopen("OngVoluntarios.bin", "rb");		
	FILE *arqLancamentos = fopen("OngLancamentos.bin", "rb");
	
	relatorioHoras relatorioHora[tfRelatorioHoras];
	voluntarios voluntario;		
	lancamentos lancamento;	

    if (arqLancamentos == NULL || arqVoluntarios != NULL) { 
        printf("Erro ao abrir o arquivo!");
    } else {
        system("cls");
        printf("\n====================================");
        printf("\n=       RELATORIOS DE HORAS        =");
        printf("\n====================================\n");

        printf("\n======== HORAS VOLUNTARIOS ==========\n");
		
        while (fread(&lancamento, sizeof(lancamento), 1, arqLancamentos) == 1) {
        	
			aux = buscaRegistroVoluntario(arqVoluntarios, lancamento.cpf, &voluntario);
			
			if(aux != -1)
				addRelatorioHorasLancadas(lancamento, relatorioHora, &tlRelatorio, voluntario);
        }
        
        fclose(arqLancamentos);
        fclose(arqVoluntarios);
        
        for(i = 0; i<tlRelatorio; i++)
        	printf("\nNome: %s\t Total de horas: %d\n", relatorioHora[i].nome, relatorioHora[i].totalHoras);	        	
	        
        printf("\n====================================\n");
        system("pause");
    }
}

//===== DOACOES:

void cadastrarDoacao(){
	FILE *arquivo = fopen ("OngDoacoes.bin" , "ab+");
	doacoes doacao; int pos;
	float valor=0, teste=0;
	
	if(arquivo == NULL)
		printf("\nErro ao abrir o arquivo !!");
	else
	{
		do
		{
			system("cls");
			printf("\n====================================");
			printf("\n=        CADASTRAR DOACOES        =");
			printf("\n====================================\n"); 	
			
			printf ("\nCPF: ");fflush(stdin); 
			gets(doacao.cpf);
			
			printf ("Nome do doador: ");fflush(stdin);
			gets(doacao.nome);
			
			printf ("Valor doado: R$");
			scanf ("%f" , &doacao.valor);
			
			printf ("Outro tipo de doacao: ");fflush(stdin);
			gets(doacao.objetos);
			
			fwrite(&doacao,sizeof(doacao), 1, arquivo);
			
			printf("\n====================================");
			printf("\n=  Doacao cadastrada com sucesso!  =");
			printf("\n====================================\n");
			
			caixa += doacao.valor;
			
			printf("\nDeseja cadastrar outra doacao <s/n> ? \n");
			
		}while(toupper(getche())=='S');
		
		fclose(arquivo);
	}	
}

void relatorioDoacoes() {
    FILE *arquivo = fopen("OngDoacoes.bin", "rb");
    doacoes doacao;
    int pos = -1;
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!");
    } else {
        system("cls");
        printf("\n====================================");
        printf("\n=      RELATORIO DE DOACOES      =");
        printf("\n====================================");

        char nomeAnterior[50] = "";
        float valorTotal = 0; 
		
        int pos = 0;
        while (fread(&doacao, sizeof(doacao), 1, arquivo) == 1) {
                pos = 1;
                printf("\nNome: %s\t Valor doado: R$%.2f\n", doacao.nome, doacao.valor);
        }

        if (pos == 0) {
            printf("\nNAO POSSUI NENHUMA ATIVIDADE CADASTRADA!\n");
            printf("\n====================================\n");
        }
        
        printf("\n====================================\n");
        system("pause");
        fclose(arquivo);
    }
}

void inicializar(){
	FILE *arquivo = fopen ("OngDoacoes.bin" , "rb");
	doacoes doacao;
	caixa = 0;
	
	if(arquivo != NULL)	
		while(fread(&doacao,sizeof(doacao),1,arquivo)==1)
			caixa+=doacao.valor;		
	
	fclose(arquivo);
}

void valorArrecadado()
{
    printf("\n Valor arrecadado: R$%.2f\n", caixa);	
    printf ("\n============================\n");
    system("pause");
}

//==================================== MAIN:

int main()
{
	int op;
	
	inicializar();
		
	op = menuPrincipal();	
	
	while (op != 0){
		//MenuPrincipal
			switch(op){
				case 1: op = menuCadastro(); //MenuCadastro
					while (op != 0){
							switch(op){
								case 1: cadastrarVoluntario();
										system("cls");
								break;
								case 2: cadastrarEmpresa();
										system("cls");
								break;
								case 3: cadastrarProjeto();
										system("cls");
								break;
								case 4: cadastrarAtividade();
										system("cls");
								break;
								case 5: cadastrarDoacao();
										system("cls");
								break;
								default: system("cls");
										 printf("\n========================================");
										 printf("\n=   Opcao invalida, tente novamente!   =");
										 printf("\n========================================\n");
							}
						op = menuCadastro();
					}
				break;
				
				case 2: op = menuAlterar(); //MenuAlterar
					while (op != 0 ){
							switch(op){
								case 1: alterarVoluntario();
										system("cls");
								break;
								case 2: alterarEmpresa();
										system ("cls");
								break;
								case 3: alterarProjeto();
										system ("cls");
								break;
								case 4: alterarAtividade();
										system("cls");
								break;
								default: system("cls");
										 printf("\n========================================");
										 printf("\n=   Opcao invalida, tente novamente!   =");
										 printf("\n========================================\n");
							}
						op = menuAlterar();
					}
				break;
				
				case 3: op = menuExcluir(); // MenuExcluir
					while (op != 0){
							switch(op){
								case 1: excluirVoluntario();
										system("cls");
								break;
								case 2: excluirEmpresa();
										system("cls");
								break;
								
								case 3: excluirProjeto();
										system("cls");
								break;
								case 4: excluirAtividade();
										system("cls");
								break;
								default: system("cls");
										 printf("\n========================================");
										 printf("\n=   Opcao invalida, tente novamente!   =");
										 printf("\n========================================\n");
							}
						op = menuExcluir();
					}
				break;
				
				case 4: op = menuRelatorios();
					while (op != 0){
							switch(op){
								case 1: relatorioVoluntario();
										system("cls");
								break;
								case 2: relatorioEmpresa();
										system ("cls");
								break;
								case 3: relatorioProjeto();
										system("cls");
								break;
								case 4: relatorioAtividade();
										system("cls");
								break;
								case 5: relatorioDoacoes();
										system("cls");
								break;
								case 6: relatorioHorasLancadas();
										system("cls");
								break;
								default: system("cls");
										 printf("\n========================================");
										 printf("\n=   Opcao invalida, tente novamente!   =");
										 printf("\n========================================\n");
							}
						op = menuRelatorios();
					}
				break;
			 
				case 5: lancarHoras();
						system("cls");
				break;
				
				case 6: valorArrecadado();
						system("cls");
				break;
				
				default: system("cls");
						 printf("\n========================================");
						 printf("\n=   Opcao invalida, tente novamente!   =");
						 printf("\n========================================\n");
						 	
			}
		system("cls");
		op = menuPrincipal();		
	}
	system("cls");
	printf("\n==========================");
	printf("\n=  PROGRAMA ENCERRADO!   =");
	printf("\n==========================\n");

	return 0;
}


