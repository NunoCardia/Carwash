#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "estruturas.h"
#include <time.h>
#define size 40

/*Funções de Verificação*/

int verifica_string(char *s)
{
    int i, j=1;
    for(i=0; i<strlen(s); i++)
    {
        if(isdigit(s[i]))
        {
        j=0;
        i = strlen(s);
        }
        else j = 1;
    }
   return j;
}


int verifica_numero(char *numero)
{
    int i, j=1;
    for(i=0; i<strlen(numero); i++)
    {
        if(!isdigit(numero[i]))
        {
			j=0;
			i = strlen(numero);
        }
		else
			j=1;
    }
   return j;
}

int hour_check(char *horas)
{
    int num;
    if(horas[4]!='0' || (horas[3]!='0' && horas[3]!='3') || (horas[0]!='0' && horas[0]!='1'))
    {
        return 0;
    }
    else if(horas[0]=='1')
    {
        if(horas[1]=='9')
        {
            return 0;
        }
        else if(horas[1]=='8' && horas[3]=='3')
        {
            return 0;
        }
    }
    else if(horas[0]=='0')
    {
        if(horas[1]!='8' && horas[1]!='9') return 0;
    }
    return 1;
}

int verifica_data(int dia,int mes,int ano)
{

    if (mes<1 || dia<1 || mes>12 || dia>31) return 0;
    if (dia>30)
    {
        if (mes==4 || mes==6 || mes==9 || mes==11) return 0;
    }
    if (dia>29 && mes==02) return 0;
    if (dia==29 && mes==02)
    {
        if(ano%4!=0) return 0;
        if(ano%100==0 && ano%400!=0) return 0;
    }
    if((get_int_len(dia)!=2 && get_int_len(dia)!=1) || (get_int_len(mes)!=2 && get_int_len(mes)!=1) || get_int_len(ano)!=4) return 0;
    return 1;
}


int check_email(char *email)
{
    int i;
    for(i=0;i<strlen(email);i++)
    {
        if(email[i]=='@')
        {
            return 1;
        }
    }
    return 0;
}

/* Funçoes Relativas a Ficheiros*/

void escrever_ficheiro_clientes(List_c lista_clientes)
{
    FILE *fp_clientes;
    List_c atual = lista_clientes->next;
    fp_clientes = fopen("dados_clientes.txt", "w");
    while(atual!= NULL)
    {
        fprintf(fp_clientes, "%d\n", atual->info.numero_cliente);
        fprintf(fp_clientes, "%s\n", atual->info.nome);
        fprintf(fp_clientes, "%s\n", atual->info.morada);
        fprintf(fp_clientes, "%s\n", atual->info.telefone);
        fprintf(fp_clientes, "%s\n", atual->info.email);
        atual = atual->next;
    }
    fclose(fp_clientes);
}

void escrever_ficheiro_reservas(List_r lista_reservas)
{
    FILE *fp_reservas;
    List_r atual = lista_reservas->next;
    fp_reservas = fopen("dados_reservas.txt", "w");
    while(atual != NULL)
    {
        fprintf(fp_reservas, "%d\n", atual->info.numero_cliente);
        fprintf(fp_reservas, "%d.%d.%d\n", atual->info.data.dia,atual->info.data.mes,atual->info.data.ano);
        fprintf(fp_reservas, "%s\n", atual->info.horas);
        fprintf(fp_reservas, "%s\n", atual->info.tipo);
        atual = atual->next;
    }
    fclose(fp_reservas);
}

void escrever_ficheiro_pre_reservas(List_r lista_pre_reservas)
{
    FILE *fp_pre_reservas;
    List_r atual = lista_pre_reservas->next;
    fp_pre_reservas = fopen("dados_pre_reservas.txt", "w");
    while(atual != NULL)
    {
        fprintf(fp_pre_reservas, "%d\n", atual->info.numero_cliente);
        fprintf(fp_pre_reservas, "%d.%d.%d\n", atual->info.data.dia,atual->info.data.mes,atual->info.data.ano);
        fprintf(fp_pre_reservas, "%s\n", atual->info.horas);
        fprintf(fp_pre_reservas, "%s\n", atual->info.tipo);
        atual = atual->next;
    }
    fclose(fp_pre_reservas);
}

void ler_ficheiro_clientes(List_c lista)
{
    FILE *fp_clientes;
    List_c actual,ant;
    long Tamanho;
    char nome[size],morada[size],telefone[size],email[size],numero_cliente[size];
    ant = lista;
    if((fp_clientes = fopen("dados_clientes.txt","r")) == NULL)
    {printf("Erro ao abrir o ficheiro.\n");}
    fseek(fp_clientes,0,SEEK_END);
    Tamanho = ftell(fp_clientes);
    rewind(fp_clientes);
    while(ftell(fp_clientes)!=Tamanho)
    {
        fgets(numero_cliente,size,fp_clientes);
        fgets(nome,size,fp_clientes);
        fgets(morada,size,fp_clientes);
        fgets(telefone,size,fp_clientes);
        fgets(email,size,fp_clientes);
        if(atoi(numero_cliente) !=0)
        {
            actual = (List_c) malloc(sizeof(list_node_c));
            actual->info.numero_cliente=atoi(numero_cliente);
            strncpy(actual->info.nome,nome,size);
            strncpy(actual->info.morada,morada,size);
            strncpy(actual->info.telefone,telefone,size);
            strncpy(actual->info.email,email,size);
            actual->next=lista->next;
            ant->next=actual;
            lista->next=actual;
        }
    }
    fclose(fp_clientes);
}

void ler_ficheiro_reservas(List_r lista)
{
    FILE *fp_reservas;
    List_r novo,ant;
    long Tamanho;
    char numero_cliente[size];
    ant=lista;
    fp_reservas=fopen("dados_reservas.txt","r");
    fseek(fp_reservas,0L,SEEK_END);
    Tamanho = ftell(fp_reservas);
    rewind(fp_reservas);
    while(((ftell(fp_reservas))!=Tamanho))
    {
        fgets(numero_cliente,size,fp_reservas);
        if(atoi(numero_cliente) !=0)
        {
            novo = (List_r) malloc (sizeof (list_node_r));
            novo->info.numero_cliente=atoi(numero_cliente);
            fscanf(fp_reservas,"%d.%d.%d\n",&novo->info.data.dia,&novo->info.data.mes,&novo->info.data.ano);
            fscanf(fp_reservas,"%s\n",novo->info.horas);
            fscanf(fp_reservas,"%s",novo->info.tipo);
            novo->next=lista->next;
            ant->next=novo;
            lista->next=novo;
        }
    }
    fclose(fp_reservas);
}

void ler_ficheiro_pre_reservas(List_r lista)
{
    FILE *fp_pre_reservas;
    List_r novo,ant;
    long Tamanho;
    char numero_cliente[size];
    ant=lista;
    fp_pre_reservas=fopen("dados_pre_reservas.txt","r");
    fseek(fp_pre_reservas,0,SEEK_END);
    Tamanho=ftell(fp_pre_reservas);
    rewind(fp_pre_reservas);
    while(((ftell(fp_pre_reservas))!=Tamanho))
    {
        fgets(numero_cliente,Tamanho,fp_pre_reservas);
        if(atoi(numero_cliente) !=0)
        {
            novo = (List_r) malloc(sizeof(list_node_r));
            novo->info.numero_cliente=atoi(numero_cliente);
            fscanf(fp_pre_reservas,"%d.%d.%d\n",&novo->info.data.dia,&novo->info.data.mes,&novo->info.data.ano);
            fscanf(fp_pre_reservas,"%s\n",novo->info.horas);
            fscanf(fp_pre_reservas,"%s\n",novo->info.tipo);
            novo->next=lista->next;
            ant->next=novo;
            lista->next=novo;
        }
    }
    fclose(fp_pre_reservas);
}

/* Listas Relativas a Clientes */

void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

void procura_cliente(List_c lista, int chave, List_c *anterior, List_c *atual)
{
    *anterior=lista; *atual=lista->next;
    while((*atual)!=NULL && (*atual)->info.numero_cliente < chave)
    {
        *anterior=*atual;
        *atual=(*atual)->next;
    }
    if((*atual)!=NULL && (*atual)->info.numero_cliente !=chave)
    *atual=NULL;
}

int procura_cliente_2 (List_r lista, int chave, List_r *ant, List_r *actual)
{
     *ant = lista; *actual = lista->next;
     while ((*actual) != NULL && (*actual)->info.numero_cliente < chave)
     {
           *ant = *actual;
           *actual = (*actual)->next;
     }
     if ((*actual) != NULL && (*actual)->info.numero_cliente != chave)
     *actual = NULL;
     if((*actual)!=NULL) return 1;
     else return 0;
}

List_c cria_lista(void)
{
    List_c tmp;
    tmp = (List_c) malloc(sizeof(list_node_c));
    if(tmp != NULL)
    {
        tmp->info.numero_cliente=0;
        tmp->next=NULL;
    }
    return tmp;
}

void inserir_cliente(List_c lista, int num_cliente)
{
    List_c aux;
    List_c anterior, proximo;
    int temp, j;
	char telefone[size], nome[size], morada[size], email[size];
    aux = (List_c) malloc(sizeof(list_node_c));
    puts("Insira os dados do cliente:\n");
    if(aux!=NULL)
    {
        do{
        j=0;
        clean_stdin();
        printf("Nome: "); gets(nome);
        j=verifica_string(nome);
        if(j == 0 || strlen(nome)==0){
            printf("\nERRO! Tem que inserir um nome! Insira apenas caracteres. \n"
                   "Prima ENTER para continuar.\n");
            j=0;
        }
        else if( j == 1 )
			strcpy(aux->info.nome,nome);
        } while(j!=1);
        do{
        j=0;
        printf("Morada: "); gets(morada);
        if(strlen(morada)==0){
            printf("\nERRO! Tem que inserir uma morada!\n");
            j=0;
        }
        else {
            strcpy(aux->info.morada,morada);
            j=1;
        }
        } while (j!=1);
        do{
        j=0;
        printf("Telefone: "); gets(telefone);
        j=verifica_numero(telefone);
		if(j == 0 || strlen(telefone) != 9){
            printf("\nERRO! Certifique-se de que inseriu um numero de telefone de 9 digitos. \n");
			j=0;
		}
		else if( j == 1 )
			strcpy(aux->info.telefone,telefone);
        } while (j!=1);
        do{
        j=0;
        printf("Email: "); gets(email);
        j=check_email(email);
        if(j == 0 || strlen(email)==0){
            printf("\nERRO! Insira os dados novamente. \n");
            j=0;
        }
        else if( j == 1 )
			strcpy(aux->info.email,email);
        } while(j!=1);
        aux->info.numero_cliente=num_cliente;
        printf("\nFoi atribuido o numero de cliente %d\n", aux->info.numero_cliente);
        temp=aux->info.numero_cliente;
        procura_cliente(lista,temp,&anterior,&proximo);
        aux->next=anterior->next;
        anterior->next=aux;
     }
}


void imprime_lista_cliente(List_c lista)
{
    List_c list=lista->next; /*saltar o header*/
    puts("Lista de clientes: \n");
    if(list==NULL) printf("ERRO! A lista de clientes esta vazia.\n");
    else{
        while(list!=NULL)
        {
            printf("Numero de cliente: %d",list->info.numero_cliente);
            printf("\nNome: %s", list->info.nome);
            printf("\nMorada: %s", list->info.morada);
            printf("\nTelefone: %s", list->info.telefone);
            printf("\nEmail: %s", list->info.email);
            printf("\n----------------------\n");
            list=list->next;
        }
    }
}

void elimina_cliente(List_c lista)
{
    List_c anterior, atual;
    int j;
    char temp[5];
    do{
        j=0;
        printf("Introduza o numero de cliente a eliminar: ");scanf("%s",temp);
        j=verifica_numero(temp);
        if(j==0){
            printf("ERRO! Por favor insira um numero de cliente valido.\n");
            j=0;
        }
        else j=1;
	}while(j!=1);
    procura_cliente(lista, atoi(temp), &anterior, &atual);
    if(atual!=NULL)
    {
        anterior->next=atual->next;
        free(atual);
    }
}

/*Fim de Listas Relativas a Clientes*/

/*Listas Relativas a Reservas e Pré-Reservas*/

/*void procura_reserva (List_r lista, int chave, List_r *ant, List_r *actual);*/

int get_int_len (int value)
{
  int l=1;
  while(value>9){ l++; value/=10; }
  return l;
}

char *subtrai_horas_lavagens(char horas[size])
{
    int temp1;
    char *aux=malloc(size);
    if(horas[3]=='3')
    {
        horas[3]='0';
    }

    else if(horas[3]=='0' && horas[0]!='1')
    {
        temp1=(horas[1] -'0')-1;
        horas[1]=(temp1 + '0');
        horas[3]='3';
    }
    else if(horas[3]=='0' && horas[0]=='1')
    {
        horas[0]='0';
        horas[1]='9';
        horas[3]='3';
    }
    strcpy(aux,horas);
    return aux;
}

char *soma_horas_lavagens(char horas[size])
{
    int temp;
    char *aux=malloc(size);
    if(horas[3]=='3' && horas[1]!='9')
    {
        horas[3]='0';
        temp=(horas[1]-'0')+1;
        horas[1]=temp + '0';
    }
    else if(horas[3]=='3' && horas[1]=='9')
    {
        horas[0]='1';
        horas[1]='0';
        horas[3]='0';
    }
    else if(horas[3]=='0')
    {
        horas[3]='3';
    }
    strcpy(aux,horas);
    return aux;
}

void procura_reserva (List_r lista, int chave, List_r *ant, List_r *actual)
{
     *ant = lista; *actual = lista->next;
     while ((*actual) != NULL && (*actual)->info.data.dia < chave)
     {
           *ant = *actual;
           *actual = (*actual)->next;
     }
     if ((*actual) != NULL && (*actual)->info.numero_cliente != chave)
     *actual = NULL;
}


int procura_reserva_2 (List_r lista, int chave, List_r *ant, List_r *actual)
{
     *ant = lista; *actual = lista->next;
     while ((*actual) != NULL && (*actual)->info.numero_cliente < chave)
     {
           *ant = *actual;
           *actual = (*actual)->next;
     }
     if ((*actual) != NULL && (*actual)->info.numero_cliente != chave)
     *actual = NULL;
     if((*actual)!=NULL) return 1;
     else return 0;
}


List_r criar_lista_reservas(void)
{
    List_r aux;
    aux=(List_r)malloc(sizeof(list_node_r));
    if(aux!=NULL)
    {
        aux->info.numero_cliente=0;
        aux->next=NULL;
    }
    return aux;
}

List_r criar_lista_pre_reservas(void)
{
    List_r aux;
    aux=(List_r)malloc(sizeof(list_node_r));
    if(aux!=NULL)
    {
        aux->info.numero_cliente=0;
        aux->next=NULL;
    }
    return aux;
}

void inserir_pre_reserva(List_r lista,int num, int *data, char *horas, char *tipo)
{
    List_r anterior,atual,temp;
    temp = (List_r) malloc (sizeof (list_node_r));
    if(temp!=NULL)
        {
            strcpy(temp->info.horas,horas);
            strcpy(temp->info.tipo,tipo);
            temp->info.data.dia=data[0];
            temp->info.data.mes=data[1];
            temp->info.data.ano=data[2];
            temp->info.numero_cliente=num;
            procura_reserva(lista,temp->info.data.dia,&anterior,&atual);
            temp->next=anterior->next;
            anterior->next=temp;
        }
        printf("Foi adicionado a lista de pré-reservas\n");
}

void inserir_reserva(List_r lista,int num, int *data, char *horas, char *tipo)
{
    List_r anterior,atual,temp;
    temp = (List_r) malloc (sizeof (list_node_r));
    if(temp!=NULL)
        {
            strcpy(temp->info.horas,horas);
            strcpy(temp->info.tipo,tipo);
            temp->info.data.dia=data[0];
            temp->info.data.mes=data[1];
            temp->info.data.ano=data[2];
            temp->info.numero_cliente=num;
            procura_reserva(lista,num,&anterior,&atual);
            temp->next=anterior->next;
            anterior->next=temp;
        }
        printf("Foi adicionado a lista das reservas\n");
}

int verifica_reserva(List_r lista, int *data, char *horas)
{
    int num=1;
    while(lista)
    {
        if(lista->info.data.dia==data[0] && lista->info.data.mes==data[1] && lista->info.data.ano==data[2] && strncmp(lista->info.horas,horas,5)==0)
        {
            num=0;
            return num;
        }
        else
        {
            lista=lista->next;
        }
    }
    return num;
}

int verifica_reserva1(List_r lista, int *data, char *horas, char *tipo)
{
    int num=1;
    while(lista)
    {
        if((lista->info.data.dia==data[0] && lista->info.data.mes==data[1] && lista->info.data.ano==data[2] && strncmp(lista->info.horas,horas,5)==0) && strncmp(lista->info.tipo,tipo,5)!=0)
        {
            num=0;
            return num;
        }
        if((lista->info.data.dia==data[0] && lista->info.data.mes==data[1] && lista->info.data.ano==data[2] && strncmp(lista->info.horas,horas,5)==0) && strncmp(lista->info.tipo,"manutenção",5)==0)
        {
            num=0;
            return num;
        }
        if((lista->info.data.dia==data[0] && lista->info.data.mes==data[1] && lista->info.data.ano==data[2] && strncmp(lista->info.horas,horas,5)==0) && strncmp(lista->info.tipo,"lavagem",5)==0)
        {
            num=1;
            return num;
        }
        else
        {
            lista=lista->next;
        }
    }
    return num;
}

int verificar_reserva(List_r lista,List_r lista_1)
{
    int final,final_1,final_2, j;
    char horas[size],nome[size],tipo[size],resposta[1],check[size],check_1[size],num[size];
    char horas_1[size],horas_2[size],horas_final[size];
    int data[size],num_final,a, lavagem, manutencao;
    List_r anterior,atual;
    puts("Introduza os dados da reserva:\n");
    do{
        j=0;
        clean_stdin();
        printf("Tipo de servico: ");gets(tipo);
        j=verifica_string(tipo);
        if(j==0 || strlen(tipo)==0)
        {
            printf("ERRO! Por favor especifique se e 'Lavagem' ou 'Manutencao'.\n");
            j=0;
        }
        else j=1;
    }while(j!=1);
    do{
        j=0;
        printf("Numero de cliente: ");gets(num);
        j=verifica_numero(num);
        if(j==0 || strlen(num)==0){
                printf("ERRO! Por favor insira um numero de cliente valido.\n");
                j=0;
        }
        else j=1;
        num_final = atoi(num);
    }while(j!=1);
    do{
        j=0;
        printf("Horas da reserva (formato hh:mm): ");gets(horas);
        j=hour_check(horas);
        if(j==0){
            printf("ERRO! Essa hora nao e valida.\n");
            j=0;
        }
    }while(j!=1);
    do{
        j=0;
        printf("Data da reserva (formato dd.mm.aaaa): ");scanf("%d.%d.%d",&data[0],&data[1],&data[2]);
        j=verifica_data(data[0], data[1], data[2]);
        if(j==0){
            printf("ERRO! Essa data nao e valida.\n");
        }
    }while(j!=1);
    strcpy(horas_1,horas);strcpy(horas_2,horas);strcpy(horas_final,horas);
    final = verifica_reserva(lista,data,horas);
    if(strncmp(tipo,"lavagem",5)==0 || strncmp(tipo,"Lavagem",5)==0 )
    {
        strcpy(check,subtrai_horas_lavagens(horas_1));
        final_1 = verifica_reserva1(lista,data,check,tipo);
        final_2=1;
    }
    if(strncmp(tipo,"Manutenção",5)==0 || strncmp(tipo,"Manutençao",5)==0 || strncmp(tipo,"manutençao",5)==0 || strncmp(tipo,"manutenção",5)==0)
    {
        strcpy(check_1,soma_horas_lavagens(horas_1));
        strcpy(check,subtrai_horas_lavagens(horas_2));
        final_1 = verifica_reserva1(lista,data,check,tipo);
        final_2 = verifica_reserva1(lista,data,check_1,tipo);
    }
    if((final == 0) || (final_1 == 0) || (final_2 == 0 ))
    {
        printf("Horario ja ocupado pretende mudar?(s/n): ");clean_stdin();gets(resposta);
        if(strncmp(resposta,"s",strlen(resposta))==0)
        {
            verificar_reserva(lista,lista_1);
        }
        else
        {
            inserir_pre_reserva(lista_1,num_final,data,horas_final,tipo);
            escrever_ficheiro_pre_reservas(lista_1);
        }
    }
    else inserir_reserva(lista,num_final,data,horas,tipo);
}

void imprime_lista_pre_reservas(List_r lista)
{
    List_r list=lista->next;
    puts("Lista de reservas: \n");
    if(list!=NULL)
    {
        printf("Numero de cliente: %d\n",list->info.numero_cliente);
        printf("Data: %d.%d.%d\n", list->info.data.dia,list->info.data.mes,list->info.data.ano);
        printf("Tipo de servico: %s\n", list->info.tipo);
        printf("Horas: %s\n", list->info.horas);
        printf("\n");
        list=list->next;
    }
}

void verificar_pre_reserva(List_r lista, List_r lista1)
{
    List_r ant,actual;
    ant = lista1;
    actual = lista1->next;
    int data[3];
    char horas[5],tipo[size],check[size],check_1[size];
    while(lista1)
    {
        if(lista!=NULL)
        {
            data[0]=lista1->info.data.dia;data[1]=lista1->info.data.mes;data[2]=lista1->info.data.ano;strcpy(horas,lista1->info.horas);
            strcpy(check_1,soma_horas_lavagens(horas));
            strcpy(check,subtrai_horas_lavagens(horas));
            if(strncmp(lista1->info.tipo,"lavagem",5)==0 || strncmp(lista1->info.tipo,"Lavagem",5)==0)
            {
                if((verifica_reserva(lista,data,horas) && verifica_reserva1(lista,data,check,lista->info.tipo)&& verifica_reserva1(lista,data,check_1,lista->info.tipo))==1)
                {
                    inserir_reserva(lista,lista1->info.numero_cliente,data,lista1->info.horas,lista1->info.tipo);
                    ant->next = actual->next;
                    free (actual);
                    printf("\nAlterada a pre-reserva para reserva, contactar cliente.\n");
                    escrever_ficheiro_pre_reservas(lista1);
                }
            }
            if(strncmp(lista1->info.tipo,"Manutenção",5)==0 || strncmp(lista1->info.tipo,"Manutençao",5)==0 || strncmp(lista1->info.tipo,"manutenção",5)==0 || strncmp(lista1->info.tipo,"manutenção",5)==0)
            {
                if((verifica_reserva(lista,data,horas) && verifica_reserva1(lista,data,check,lista->info.tipo)&& verifica_reserva1(lista,data,check_1,lista->info.tipo))==1)
                {
                    inserir_reserva(lista,lista1->info.numero_cliente,data,lista1->info.horas,lista1->info.tipo);
                    ant->next = actual->next;
                    free (actual);
                    printf("\nAlterada a pre-reserva para reserva, contactar cliente.\n");
                    escrever_ficheiro_pre_reservas(lista1);

                }
            }

        }
        else lista=criar_lista_reservas();inserir_reserva(lista,lista1->info.numero_cliente,data,lista1->info.horas,lista1->info.tipo);

        lista1 = lista1->next;
        lista=lista->next;
    }
}


void imprime_lista_reservas(List_r lista)
{
    List_r list=lista->next;
    puts("Lista de reservas: \n");
    while(list)
    {
        if(list->info.numero_cliente!=0 && list->info.numero_cliente<50)
        {
            printf("Numero de cliente: %d\n",list->info.numero_cliente);
            printf("Data: %d.%d.%d\n", list->info.data.dia,list->info.data.mes,list->info.data.ano);
            printf("Tipo de servico: %s\n", list->info.tipo);
            printf("Hora: %s\n\n", list->info.horas);
            list=list->next;
        }
        else list=list->next;
    }
}

void elimina_pre_reserva(List_r lista)
{
     List_r ant=lista;
     List_r actual=lista->next;
     char horas[size];
     int num, j,data[3];
     do{
        j=0;
        printf("Introduza a data da reserva: ");scanf("%d.%d.%d",&data[0],&data[1],&data[2]);
        clean_stdin();
        j=verifica_data(data[0], data[1], data[2]);
        if(j==0){
            printf("ERRO! Essa data nao e valida.\n");
            j=0;
        }
        else j=1;
     }while(j!=1);
     do{
        j=0;
        printf("Introduza a hora da reserva: ");gets(horas);
        j=hour_check(horas);
        if(j==0){
            printf("ERRO! Essa data nao e valida.\n");
            j=0;
        }
        else j=1;
     }while(j!=1);
     while(lista)
     {
        if((lista->info.data.dia==data[0] && lista->info.data.mes==data[1] && lista->info.data.ano==data[2] && strncmp(lista->info.horas,horas,5)==0))
        {
            ant->next=actual->next;
            free(actual);
            printf("Reserva eliminada\n");
        }
        lista=lista->next;
     }
}

void elimina_reserva(List_r lista)
{
     List_r ant=lista;
     List_r actual=lista->next;
     char horas[size];
     int num, j,data[3];
     do{
        j=0;
        printf("Introduza a data da reserva: ");scanf("%d.%d.%d",&data[0],&data[1],&data[2]);
        clean_stdin();
        j=verifica_data(data[0], data[1], data[2]);
        if(j==0){
            printf("ERRO! Essa data nao e valida.\n");
            j=0;
        }
        else j=1;
     }while(j!=1);
     do{
        j=0;
        printf("Introduza a hora da reserva: ");gets(horas);
        j=hour_check(horas);
        if(j==0){
            printf("ERRO! Essa data nao e valida.\n");
            j=0;
        }
        else j=1;
     }while(j!=1);
     while(lista)
     {
        if((lista->info.data.dia==data[0] && lista->info.data.mes==data[1] && lista->info.data.ano==data[2] && strncmp(lista->info.horas,horas,5)==0))
        {
            ant->next=actual->next;
            free(actual);
            printf("Reserva eliminada");
        }
        lista=lista->next;
     }
}

void imprime_reserva_cliente(List_r lista)
{
    char aux[size];
    int num,check2, j;
    List_r list=lista->next;
    List_r ant2,actual2;
    puts("Introduza o numero de cliente: ");
    clean_stdin();
    gets(aux);
    num=atoi(aux);
    check2=procura_reserva_2(lista,num,&ant2,&actual2);
    if(check2)
    {
        while(list)
        {
            if(list->info.numero_cliente==num)
            {
                printf("Tipo de serviço: %s\n",list->info.tipo);
                printf("Data: %d.%d.%d\n",list->info.data.dia,list->info.data.mes,list->info.data.ano);
                printf("Hora: %s\n",list->info.horas);
            }
        list=list->next;
        }
    }
    else printf("O cliente nao fez nenhuma reserva.\n");
}

void ord_data_reserva(List_r lista){
	int sorted;
	do{
		List_r p,q,r;
		sorted=1;
		for(r=NULL,p=lista,q=p->next;q;r=p,p=q,q=p->next){
			if(p->info.data.ano > q->info.data.ano || p->info.data.ano==q->info.data.ano && p->info.data.mes > q->info.data.mes || p->info.data.ano==q->info.data.ano && p->info.data.mes == q->info.data.mes && p->info.data.dia > q->info.data.dia){
				if(r==NULL){
					lista=q;
					p->next=q->next;
					q->next=p;
				}
				else {
					r->next=q;
					p->next=q->next;
					q->next=p;
				}
				sorted=0;
			}
		}
	}while(!sorted);
}


/*Fim das Listas Relativas a Reservas e Pré-Reservas*/

/*funções auxiliares*/

void elimina_tudo(List_r lista, List_r lista1)
{
    List_r anterior=lista;List_r post=lista->next;
    List_r ant1=lista1;List_r actual1=lista1->next;
    int dia_a,mes_a,ano_a;
    char dia[20], *result=NULL;
    char buffer[size];
    char *token,mes[12],ano[10];
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime (dia,4,"%d",timeinfo);
    strftime (mes,4,"%m",timeinfo);
    strftime (ano,10,"%Y",timeinfo);
    dia_a=atoi(dia);mes_a=atoi(mes);ano_a=atoi(ano);
    printf("%s\n%s\n%s\n",dia,mes,ano_a);
    while(lista)
    {
        if((lista->info.data.dia=dia_a) && (lista->info.data.mes=mes_a) && (lista->info.data.ano=ano_a))
        {
            anterior->next=post->next;
            free(post);
        }
        lista=lista->next;
    }
    while(lista1)
    {
        if((lista1->info.data.dia=dia_a) && (lista1->info.data.mes=mes_a) && (lista1->info.data.ano=ano_a))
        {
            ant1->next=actual1->next;
            free(actual1);
        }
        lista1=lista1->next;
    }
    printf("Todas as reservas e pré-reservas de %d.%d.%d foram apagadas",dia_a,mes_a,ano_a);
}

int main()
{
    List_c lista_cliente=cria_lista();
    List_r lista_reservas=criar_lista_reservas();
    List_r lista_pre_reservas=criar_lista_reservas();
    int o, n, m=1, conta_num_cliente=1;
    FILE *criar_ficheiros;
    criar_ficheiros = fopen("dados_clientes.txt", "a");
    fclose(criar_ficheiros);
    criar_ficheiros = fopen("dados_reservas.txt", "a");
    fclose(criar_ficheiros);
    criar_ficheiros = fopen("dados_pre_reservas.txt", "a");
    fclose(criar_ficheiros);
    ler_ficheiro_clientes(lista_cliente);
    ler_ficheiro_reservas(lista_reservas);
    ler_ficheiro_pre_reservas(lista_pre_reservas);

    while(1)
    {
		system("clear");
        m=1;
        printf("\nMENU PRINCIPAL\n"
               "\n"
               "Escolha uma das seguintes opcoes:\n"
               "1 - Menu do Cliente\n"
               "2 - Menu de Reservas\n"
               "3 - Menu de Pre-reservas\n"
               "0 - Sair\n"
               "\n");
        scanf("%d", &n);
        system("clear");
        switch(n)
        {
            case 1: while(m)
            {
                printf("\nMENU DE CLIENTES\n"
                       "\n"
                       "1 - Introduzir novo cliente\n"
                       "2 - Eliminar cliente\n"
                       "3 - Imprimir lista de clientes\n"
                       "0 - Voltar ao menu principal\n"
                       "\n");
                scanf("%d", &m);
                system("clear");
                switch(m)
                {
                case 1:{
                    if(lista_cliente==NULL) lista_cliente=cria_lista();
                    inserir_cliente(lista_cliente, conta_num_cliente);
                    conta_num_cliente++;escrever_ficheiro_clientes(lista_cliente);
                    } break;
                case 2:{
                    if(lista_cliente==NULL) printf("ERRO! A lista de clientes esta vazia. \nPor favor insira um cliente.\n");
                    else elimina_cliente(lista_cliente);escrever_ficheiro_clientes(lista_cliente);
                    } break;
                case 3:{
                    if(lista_cliente==NULL) printf("ERRO! A lista de clientes esta vazia. \nPor favor insira um cliente.\n");
                    else imprime_lista_cliente(lista_cliente);
                    }break;
                case 0:
                    {
                        m=0;
                    } break;
                default: printf("Por favor escolha uma opcao entre 0 e 5.\n");
                }
            } break;
            case 2: while(m)
            {
                printf("\nMENU DE RESERVAS\n"
                       "\n"
                       "1 - Inserir nova reserva\n"
                       "2 - Cancelar reserva\n"
                       "3 - Imprimir lista de reservas\n"
                       "4 - Ordenar reservas por data\n"
                       "5 - Imprimir reserva de um cliente especifico\n"
                       "6 - Eliminar reservas do dia\n"
                       "0 - Voltar ao menu principal\n"
                       "\n");
                scanf("%d", &m);
                system("clear");
                switch(m)
                {
                case 1:{
                    if(lista_cliente==NULL) printf("ERRO! Nao existe uma lista de dados de clientes. \nPor favor adicione primeiro um cliente.\n");
                    if (lista_reservas==NULL) lista_reservas=criar_lista_reservas();
                    if(lista_pre_reservas==NULL) lista_pre_reservas=criar_lista_pre_reservas();
                    verificar_reserva(lista_reservas,lista_pre_reservas);escrever_ficheiro_reservas(lista_reservas);
                    } break;
                case 2:
                    {
                        if(lista_reservas==NULL) printf("ERRO! A lista de reservas esta vazia. \nPor favor insira uma reserva.\n");
                        else
                        {
                            elimina_reserva(lista_reservas);
                            verificar_pre_reserva(lista_reservas,lista_pre_reservas);
                            escrever_ficheiro_reservas(lista_reservas);
                        }
                    } break;
                case 3:
                    {
                        if(lista_reservas==NULL) printf("ERRO! A lista de reservas esta vazia. \nPor favor insira uma reserva.\n");
                        else imprime_lista_reservas(lista_reservas);
                    } break;
                case 4:
                    {
                        if(lista_reservas==NULL) printf("ERRO! A lista de reservas esta vazia. \nPor favor insira uma reserva.\n");
                        else ord_data_reserva(lista_reservas);escrever_ficheiro_reservas(lista_reservas);
                    } break;
                case 5:
                    {
                        if(lista_reservas==NULL) printf("ERRO! A lista de reservas esta vazia. \nPor favor insira uma reserva.\n");
                        else imprime_reserva_cliente(lista_reservas);
                    } break;
                case 6:
                    {
                        elimina_tudo(lista_reservas,lista_pre_reservas);
                        escrever_ficheiro_reservas(lista_reservas);
                        escrever_ficheiro_pre_reservas(lista_pre_reservas);
                    }
               case 0:
                   {
                    m=0;
                   } break;
                default: printf("Por favor escolha uma opcao entre 0 e 5.\n");
                }
            } break;
            case 3: while(m)
            {
                printf("\nMENU DE PRE-RESERVAS\n"
                       "\n"
                       "1 - Eliminar pre-reserva\n"
                       "2 - Imprimir lista de pre-reservas\n"
                       "3 - Ordenar pre-reservas por data\n"
                       "0 - Voltar ao menu principal\n"
                       "\n");
                scanf("%d", &m);
                system("clear");
                switch(m)
                {
                case 1:
                    {
                        if(lista_pre_reservas==NULL) printf("ERRO! A lista de pre-reservas esta vazia.\n");
                        else elimina_pre_reserva(lista_pre_reservas);escrever_ficheiro_pre_reservas(lista_pre_reservas);
                    } break;
                case 2:
                    {
                        if(lista_pre_reservas==NULL) printf("ERRO! A lista de pre-reservas esta vazia.\n");
                        else imprime_lista_pre_reservas(lista_pre_reservas);
                    } break;
                case 3:
                    {
                        if(lista_pre_reservas==NULL) printf("ERRO! A lista de pre-reservas esta vazia.\n");
                        else ord_data_reserva(lista_pre_reservas);escrever_ficheiro_pre_reservas(lista_pre_reservas);
                    } break;
                case 0:
                    {
                    m=0;
                    } break;
                }
            } break;
            case 0:
            {
                printf("\nObrigado. Volte sempre!\n"
                       "\n");
                return 0;
            } break;
            system("clear");
            default: printf("Por favor escolha uma opcao entre 0 e 3.\n");
        }
    }
    return 0;
}
