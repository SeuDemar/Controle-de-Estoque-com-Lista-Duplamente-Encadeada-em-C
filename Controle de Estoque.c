#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>

#define MAX 10;

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

// Configurando a função GOTOXy
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = (short)x;
    coord.Y = (short)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Mostra a Tela Padrao
void tela()
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

void CadastrarProdutoNoFinal(TipoLista_Prod *lista) {
    tela();
    
    // Aloca memória para um novo item da lista
    TipoApontador novoProduto = (TipoApontador)malloc(sizeof(TipoItem));

    if (novoProduto == NULL) {
        gotoxy(02, 5);
        printf("Erro ao alocar memória para novo produto.\n");
        return;
    }

    gotoxy(3, 5);
    printf("Digite o código do produto.............: ");
    scanf("%d", &novoProduto->conteudo.cd_Produto);
    gotoxy(3, 6);
    printf("Digite a descrição do produto..........: ");
    fgets(novoProduto->conteudo.ds_Produto, sizeof(novoProduto->conteudo.ds_Produto), stdin);
    //scanf(" %[^\n]s", novoProduto->conteudo.ds_Produto);
    gotoxy(3, 7); 
    printf("Digite a unidade de medida.............: ");
    scanf("%s", novoProduto->conteudo.ds_Unid_med);
    gotoxy(3, 8);
    printf("Digite a data de validade (DD/MM/AAAA).: ");
    scanf("%s", novoProduto->conteudo.dt_Validade);
    gotoxy(3, 9);
    printf("Digite a quantidade do produto.........: ");
    scanf("%f", &novoProduto->conteudo.qt_Produto);
    gotoxy(3, 10);
    printf("Digite o valor custo médio.............: ");
    scanf("%f", &novoProduto->conteudo.vl_Customedio);

    while (getchar() != '\n');

    // Calcula o valor total
    novoProduto->conteudo.vl_Total = novoProduto->conteudo.qt_Produto * novoProduto->conteudo.vl_Customedio;

    // Define o próximo item como NULL (pois será o último item da lista)
    novoProduto->proximo = NULL;

    // Se a lista estiver vazia, o novo item será o primeiro e o último item
    if (lista->Pri_movim == NULL) {
        lista->Pri_movim = novoProduto;
        lista->Ult_movim = novoProduto;
    } else {
        // Atualiza o próximo do último item atual e o último item da lista
        lista->Ult_movim->proximo = novoProduto;
        lista->Ult_movim = novoProduto;
    }

    gotoxy(7, 23);
    printf("Produto cadastrado com sucesso!\n");
    getch();
}

void telaMenuCadProd () 
{
    int opc2;

    tela();
    
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

// Área de declaração sobre coisas relacionadas a produtos 

int main () {
    int opc;

    // Criando instâncias dos ponteiros, necessário para a inicialização
    TipoLista_Prod  lista_produtos;
    TipoLista_movim lista_movim;

    // Inicialização da lista de produtos
    lista_produtos.Pri_movim = NULL;
    lista_produtos.Ult_movim = NULL;

    // Inicialização da lista de movimentações
    lista_movim.Pri_movim = NULL;
    lista_movim.Pri_movim = NULL;

    // Loop simples quer irá manter o programa rodando
    while (opc != 3)
    {
    tela();
    gotoxy(03, 5);
    printf("1 - Menu de cadastros");
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

            break;

        case 3:

            break;

        default:
            gotoxy(9, 23);
            printf("Opcao invalidada, pressione ''enter''e tente novamente.");
            getch();
            break;
        }
    };

    return 0;
}