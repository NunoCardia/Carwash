#define tamanho 40

typedef struct
{
    int dia;
    int mes;
    int ano;
}Data;

typedef struct
{
    char nome[tamanho];
    char morada[tamanho];
    char telefone[tamanho];
    char email[tamanho];
    int numero_cliente;
    }Cliente;
    
typedef struct lnode_c *List_c;
typedef struct lnode_c
{
    Cliente info;
    List_c next;
    }list_node_c;
    
typedef struct
{
    Data data;
    int numero_cliente;
    char horas[tamanho];
    char tipo[tamanho];
}Reservas;

typedef struct lnode_r *List_r;
typedef struct lnode_r
{
    Reservas info;
    List_r next;
    }list_node_r;
    

