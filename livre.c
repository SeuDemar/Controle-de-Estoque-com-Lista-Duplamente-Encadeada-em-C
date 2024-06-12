#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>

#define MAX 10;

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = (short)x;
    coord.Y = (short)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Mostra a Tela Padrao
void telaprincipal()
{
    int t;
    system("color 0e");
    system("cls");
    gotoxy(01, 01);
    printf("+-----------------------------------------------------------------------------+");
    gotoxy(01, 02);
    printf("| Vitor Boer");
    gotoxy(60, 02);
    printf("Estrutura de Dados |");
    gotoxy(01, 04);
    printf("|");
    gotoxy(32, 02);
    printf("  UNICV");
    gotoxy(79, 04);
    printf("|");
    gotoxy(01, 03);
    printf("+-----------------------------------------------------------------------------+");
    for (t = 5; t < 24; t++)
    {
        gotoxy(01, t);
        printf("|");
        gotoxy(79, t);
        printf("|");
    }

    gotoxy(01, 22);
    printf("+-----------------------------------------------------------------------------+");
    gotoxy(02, 23);
    printf("MSG.:");
    gotoxy(01, 24);
    printf("+-----------------------------------------------------------------------------+");
}

// Área de declaração sobre coisas relacionadas a produtos 
typedef struct 
{
    int   cd_Produto;
    char  ds_Produto[50];
    char  ds_Unid_med[3];
    char  dt_Validade[11];
    float qt_Produto;
    float vl_Customedio;
    float vl_Total;

}reg_produto;

typedef struct TipoItem *TipoApontador;

typedef struct TipoItem
{
    reg_produto   conteudo;
    TipoApontador proximo;
} TipoItem;

typedef struct
{
    TipoApontador Pri_movim;
    TipoApontador Ult_movim;
}TipoLista_Prod;

// Área de declaração sobre coisas relacionadas a movimentos 
typedef struct 
{
    char  dt_Movim[11];
    int   cd_Prod_Movim;
    char  tp_Movim;
    float qt_Movim;
    float vl_Unit_Movim;
    float vl_Total_Movim;

} reg_movim;

typedef struct Tipoitem_movim *TipoApontador_movim;

typedef struct TipoItem_movim
{
    TipoApontador_movim anterior_Movim;
    reg_movim           conte_Movim;
    TipoApontador_movim proximo_Movim;
} TipoItem_movim;

typedef struct
{
    TipoApontador_movim Pri_movim;
    TipoApontador_movim Ult_movim;       
} TipoLista_movim;

void telaMenuCadProd () 
{
    int opc2;

    telaprincipal();
    
    gotoxy(03, 5);
    printf("1 - Cadastrar Produto no Final da Lista");
    gotoxy(03, 6);
    printf("2 - Cadastrar Produto no Inicio da Lista");
    gotoxy(03, 7);
    printf("3 - Cadastrar Produto em Uma Posicao da Lista");
    gotoxy(03, 8);
    printf("4 - Remover Produto em Uma Posicao da Lista");
    gotoxy(03, 9);
    printf("5 - Remover Produto na posicao da Lista");
    gotoxy(03, 10);
    printf("6 - Remover Produto no Inicio da Lista ");
    gotoxy(03, 11);
    printf("7 - Consultar Todos os Produtos");
    gotoxy(03, 12);
    printf("8 - Alterar Dados do Produto");
    gotoxy(03, 13);
    printf("9 - Retornar ao Menu Principal");
    scanf("%d", &opc2);

    switch (opc2)
    {
    case 1:

        break;
    
    default:
        break;
    }

}

void telaMenuMovim ()
{
    int opc3;

    tela();
    gotoxy(03, 5);
    printf("1 - Cadastrar Movimentacao de Estoque");
    gotoxy(03, 6);
    printf("2 - Lista Movimentacao de Estoque");
    gotoxy(03, 7);
    printf("3 - Retornar ao Menu Principal");

    switch (opc3)
    {
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    
    default:
        break;
    }
}

void iniciarListaProd(TipoLista_Prod *Lista)
{
    Lista->Pri_movim = NULL;
    Lista->Ult_movim = NULL; 
}

void iniciarListaMovim(TipoLista_movim *Lista)
{
    Lista->Pri_movim = NULL;
    Lista->Ult_movim = NULL;
}

void inserirProduto(TipoLista_Prod *lista, reg_produto produto)
{
    TipoApontador novo = (TipoApontador)malloc(sizeof(TipoItem));

    novo->conteudo = produto;
    novo->proximo = NULL;

    if (lista->Pri_movim == NULL)
    {
        lista->Pri_movim = novo;
    } else {
        TipoApontador atual = lista->Pri_movim;

        while (atual->proximo != NULL)
        {
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }
}

int main () {
    int opc;

    TipoLista_Prod  Lista_prod;
    TipoLista_movim Lista_movim;

    iniciarListaProd(&Lista_prod);
    iniciarListaMovim(&Lista_movim);
    
    do {
    tela();
    gotoxy(03, 5);
    printf("1 - Menu de Cadastros de Produtos ");
    gotoxy(03, 6);
    printf("2 - Menu de Movimentacao de Estoque");
    gotoxy(03, 7);
    printf("3 - Finalizar o programa");
    gotoxy(07, 23);
    scanf("%d", &opc);

    switch (opc)
        {
        case 1:
        telaMenuCadProd();
            break;
        case 2:
        telaMenuMovim();
            break;

        case 3:

            break;

        default:
            break;
        }
    } while (opc != 3);

    return 0;
    
}