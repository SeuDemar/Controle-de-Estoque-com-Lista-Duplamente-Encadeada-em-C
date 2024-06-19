/*Autor....: Vitor Boer
Data.....: 18/06/2024
Objetivo.: Criar um Controle de Estoque 
*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <conio.h>

// Área de declaração sobre coisas relacionadas aos produtos da lista
typedef struct reg_produto
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

// Área de declaração sobre coisas relacionadas aos movimentos da lista
typedef struct reg_movim
{
    char  dt_Movim[11];
    int   cd_Prod_Movim;
    char  tp_Movim;
    float qt_Movim;
    float vl_Unit_Movim;
    float vl_Total_Movim;

} reg_movim;

typedef struct TipoItem_movim *TipoApontador_movim;

typedef struct TipoItem_movim
{
    TipoApontador_movim anterior_Movim;
    reg_movim           conte_Movim;
    TipoApontador_movim proximo_Movim;
} TipoItem_movim;

typedef struct TipoLista_movim
{
    TipoApontador_movim Pri_movim;
    TipoApontador_movim Ult_movim;       
} TipoLista_movim;

// Configurando a função GOTOXY
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = (short)x;
    coord.Y = (short)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Mostra a Tela Padrao chamada em várias funções
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

// cadastra o produto no final da lista de produtos
void CadastrarProdutoNoFinal(TipoLista_Prod *lista) {
    tela();
    
    // Aloca memória para um novo item da lista
    TipoApontador novoProduto = (TipoApontador)malloc(sizeof(TipoItem));

    if (novoProduto == NULL) {
        gotoxy(07, 23);
        printf("Erro ao alocar memória para novo produto.");
        getch();
        return;
    }

    // Área para pegar entradas do usuário
    gotoxy(3, 5);
    printf("Digite o codigo do produto.........: ");
    scanf("%d", &novoProduto->conteudo.cd_Produto);
    while (getchar() != '\n');
    gotoxy(3, 6);
    printf("Digite a descricao do produto......: ");
    fgets(novoProduto->conteudo.ds_Produto, sizeof(novoProduto->conteudo.ds_Produto), stdin);
    novoProduto->conteudo.ds_Produto[strcspn(novoProduto->conteudo.ds_Produto, "\n")] = '\0';

    gotoxy(3, 7); 
    printf("Digite a unidade de medida.........: ");
    scanf("%s", novoProduto->conteudo.ds_Unid_med);
    gotoxy(3, 8);
    printf("Digite a data de validade DDMMAAAA.: ");
    scanf("%s", novoProduto->conteudo.dt_Validade);

    // Colocando zero nos valores da lista 
    novoProduto->conteudo.qt_Produto = 0;
    novoProduto->conteudo.vl_Customedio = 0;
    novoProduto->conteudo.vl_Total = 0;

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
    printf("Produto cadastrado com sucesso!");
    getch();
}

// Função para cadastrar produto no final 
void CadastrarProdutoNoInicio(TipoLista_Prod *lista) {
    TipoApontador novoProduto = (TipoApontador)malloc(sizeof(TipoItem));

    if (novoProduto == NULL) {
        gotoxy(02, 5);
        printf("Erro ao alocar memória para novo produto.");
        return;
    }
    tela();

    // Pegar entradas do usuário nvamente
    gotoxy(3, 5);
    printf("Digite o codigo do produto.........: ");
    scanf("%d", &novoProduto->conteudo.cd_Produto);
    while (getchar() != '\n');
    gotoxy(3, 6);
    printf("Digite a descricao do produto......: ");
    fgets(novoProduto->conteudo.ds_Produto, sizeof(novoProduto->conteudo.ds_Produto), stdin);
    novoProduto->conteudo.ds_Produto[strcspn(novoProduto->conteudo.ds_Produto, "\n")] = '\0';

    gotoxy(3, 7); 
    printf("Digite a unidade de medida.........: ");
    scanf("%s", novoProduto->conteudo.ds_Unid_med);
    gotoxy(3, 8);
    printf("Digite a data de validade DDMMAAAA.: ");
    scanf("%s", novoProduto->conteudo.dt_Validade);
    gotoxy(3, 9);

    // Decalrando 0 nas variaveis novamente
    novoProduto->conteudo.qt_Produto = 0;
    novoProduto->conteudo.vl_Customedio = 0;
    novoProduto->conteudo.vl_Total = 0;


    // Define o próximo item como o atual primeiro item
    novoProduto->proximo = lista->Pri_movim;
    lista->Pri_movim = novoProduto;

    // Se a lista estiver vazia, o novo item será o único item
    if (lista->Ult_movim == NULL) {
        lista->Ult_movim = novoProduto;
    }
}

void CadastrarProdutoNaPosicao(TipoLista_Prod *lista)
{
    tela();

    int pos, i;
    gotoxy(3, 5);
    printf("Digite a posicao em que deseja inserir o produto: ");
    scanf("%d", &pos);

    TipoApontador novoProduto = (TipoApontador)malloc(sizeof(TipoItem));

    if (novoProduto == NULL)
    {
        gotoxy(02, 6);
        printf("Erro ao alocar memória para novo produto.");
        return;
    }

    gotoxy(3, 6);
    printf("Digite o codigo do produto.............: ");
    scanf("%d", &novoProduto->conteudo.cd_Produto);
    while (getchar() != '\n');
    gotoxy(3, 7);
    printf("Digite a descricao do produto......: ");
    fgets(novoProduto->conteudo.ds_Produto, sizeof(novoProduto->conteudo.ds_Produto), stdin);
    novoProduto->conteudo.ds_Produto[strcspn(novoProduto->conteudo.ds_Produto, "\n")] = '\0';
    gotoxy(3, 8);
    printf("Digite a unidade de medida.............: ");
    scanf("%s", novoProduto->conteudo.ds_Unid_med);
    gotoxy(3, 9);
    printf("Digite a data de validade (DD/MM/AAAA).: ");
    scanf("%s", novoProduto->conteudo.dt_Validade);
    gotoxy(3, 10);

    // Decalrando 0 novamente a variaveis
    novoProduto->conteudo.qt_Produto = 0;
    novoProduto->conteudo.vl_Customedio = 0;
    novoProduto->conteudo.vl_Total = 0;


    if (pos == 1)
    {
        novoProduto->proximo = lista->Pri_movim;
        lista->Pri_movim = novoProduto;

        if (lista->Ult_movim == NULL)
        {
            lista->Ult_movim = novoProduto;
        }
    }
    else
    {
        TipoApontador atual = lista->Pri_movim;
        TipoApontador anterior = NULL;

        for (i = 1; i < pos && atual != NULL; i++)
        {
            anterior = atual;
            atual = atual->proximo;
        }

        if (atual == NULL)
        {
            if (anterior != NULL)
            {
                anterior->proximo = novoProduto;
                lista->Ult_movim = novoProduto;
            }
            else
            {
                lista->Pri_movim = novoProduto;
                lista->Ult_movim = novoProduto;
            }
            novoProduto->proximo = NULL;
        }
        else
        {
            anterior->proximo = novoProduto;
            novoProduto->proximo = atual;
        }
    }

    gotoxy(7, 23);
    printf("Produto inserido na posicao %d com sucesso!", pos);
    getch();
}


// Remove o produto na posicação especifíca que o usúario queira 
void RemoverProdutoNaPosicao(TipoLista_Prod *lista)
{
    tela();

    int pos, i;
    gotoxy(3, 5);
    printf("Digite a posicao do produto que deseja remover: ");
    scanf("%d", &pos);

    if (lista->Pri_movim == NULL)
    {
        gotoxy(3, 6);
        printf("A lista esta vazia. Nenhum produto para remover.");
        getch();
        return;
    }

    TipoApontador atual = lista->Pri_movim;
    TipoApontador anterior = NULL;

    if (pos == 1)
    {
        lista->Pri_movim = atual->proximo;
        if (lista->Pri_movim == NULL)
        {
            lista->Ult_movim = NULL;
        }
        free(atual);
    }
    else
    {
        for (i = 1; i < pos && atual != NULL; i++)
        {
            anterior = atual;
            atual = atual->proximo;
        }

        if (atual == NULL)
        {
            gotoxy(3, 6);
            printf("Posicao invalida. Nenhum produto removido.\n");
            getch();
            return;
        }

        anterior->proximo = atual->proximo;
        if (anterior->proximo == NULL)
        {
            lista->Ult_movim = anterior;
        }
        free(atual);
    }

    gotoxy(7, 23);
    printf("Produto removido da posicao %d com sucesso!", pos);
    getch();
}



void RemoverProdutoNoFinal(TipoLista_Prod *lista)
{
    tela();

    if (lista->Pri_movim == NULL)
    {
        gotoxy(3, 6);
        printf("A lista esta vazia. Nenhum produto para remover.\n");
        getch();
        return;
    }

    TipoApontador atual = lista->Pri_movim;
    TipoApontador anterior = NULL;

    // Se houver apenas um item na lista
    if (atual->proximo == NULL)
    {
        lista->Pri_movim = NULL;
        lista->Ult_movim = NULL;
        free(atual);
    }
    else
    {
        // Percorre a lista até encontrar o penúltimo item
        while (atual->proximo != NULL)
        {
            anterior = atual;
            atual = atual->proximo;
        }

        anterior->proximo = NULL;
        lista->Ult_movim = anterior;
        free(atual);
    }

    gotoxy(7, 23);
    printf("Produto removido do final da lista com sucesso!\n");
    getch();
}


void RemoverProdutoNoInicio(TipoLista_Prod *lista)
{
    tela();

    if (lista->Pri_movim == NULL)
    {
        gotoxy(3, 6);
        printf("A lista esta vazia. Nenhum produto para remover.");
        getch();
        return;
    }

    // Armazena o primeiro item da lista em uma variável temporária
    TipoApontador produtoParaRemover = lista->Pri_movim;

    // Atualiza o ponteiro do primeiro item para o próximo item da lista
    lista->Pri_movim = lista->Pri_movim->proximo;

    // Se a lista ficar vazia após a remoção, atualiza o ponteiro do último item
    if (lista->Pri_movim == NULL)
    {
        lista->Ult_movim = NULL;
    }

    // Libera a memória do item removido
    free(produtoParaRemover);

    gotoxy(7, 23);
    printf("Produto removido do início da lista com sucesso!");
    getch();
}

void ListarProdutos(TipoLista_Prod *lista) {
    tela();
    int linha = 7;

    if (lista == NULL) {
        gotoxy(3, 5);
        printf("Erro: Lista não inicializada.");
        return;
    }

    if (lista->Pri_movim == NULL) {
        gotoxy(3, 5);
        printf("Nenhum produto cadastrado.");
        return;
    }

    gotoxy(2, 5);
    printf("Codigo  |  Descricao  |  UniMed  |  DTVal  |   Qt   |  Custo Medio   |  Total");
    gotoxy(1, 6);
    printf("+-----------------------------------------------------------------------------+");
    for (int l = 0; l < 15; l++){
        gotoxy(1, 7 + l);
        printf("|        |             |          |         |        |                |");
    }
    

    TipoApontador atual = lista->Pri_movim; // Inicialização correta do ponteiro
    while (atual != NULL) {  // Percorre a lista inteira
        gotoxy(2, linha);
        printf("%d", atual->conteudo.cd_Produto);
        gotoxy(12, linha);
        printf("%s", atual->conteudo.ds_Produto);
        gotoxy(25, linha);
        printf("%s", atual->conteudo.ds_Unid_med);
        gotoxy(36, linha);
        printf("%s", atual->conteudo.dt_Validade);
        gotoxy(46, linha);
        printf("%.1f", atual->conteudo.qt_Produto); 
        gotoxy(55, linha);
        printf("%.2f", atual->conteudo.vl_Customedio);
        gotoxy(72, linha);
        printf("%.2f", atual->conteudo.vl_Total);

        linha++;
        atual = atual->proximo; // Avança para o próximo produto na lista

        if (linha > 20) { // Verifica se a linha ultrapassou o limite da tela
            gotoxy(3, linha + 1);
            printf("Pressione enter para ir para a proxima pagina...");
            getch();
            tela();
            gotoxy(2, 5);
            printf("Codigo  |  Descricao  |  UniMed  |  DTVal  |   Qt   |  Custo Medio   |  Total");
            gotoxy(1, 6);
            printf("+-----------------------------------------------------------------------------+");
            linha = 7; // Reinicia a contagem de linhas
        }
    }

    gotoxy(7, 23); // Ajusta a posição para a mensagem de fim da lista
    printf("Fim da lista. Pressione qualquer tecla para sair...");
    getch();
}

void EditarProduto(TipoLista_Prod *lista) {
    tela();

    int codigo;
    char opcao;
    TipoApontador atual = lista->Pri_movim;

    gotoxy(3, 5);
    printf("Digite o codigo do produto que deseja editar: ");
    scanf("%d", &codigo);

    while (atual != NULL && atual->conteudo.cd_Produto != codigo) {
        atual = atual->proximo;
    }

    if (atual == NULL) {
        gotoxy(7, 23);
        printf("Codigo do produto %d nao encontrado.", codigo);
        getch();
        return;
    }

    // Mostrar os dados atuais do produto
    gotoxy(3, 6);
    printf("Dados atuais do produto CD %d.:", atual->conteudo.cd_Produto);
    gotoxy(3, 7);
    printf("Descricao....................: %s", atual->conteudo.ds_Produto);
    gotoxy(3, 8);
    printf("Unidade de medida............: %s", atual->conteudo.ds_Unid_med);
    gotoxy(3, 9);
    printf("Data de validade.............: %s", atual->conteudo.dt_Validade);

    // Opção para editar os campos
    gotoxy(3, 11);
    printf("Deseja editar este produto? (S/N): ");
    scanf(" %c", &opcao);

    if (opcao == 'S' || opcao == 's') {
        gotoxy(3, 13);
        printf("Digite a nova descricao do produto........: ");
        while (getchar() != '\n');  
        fgets(atual->conteudo.ds_Produto, sizeof(atual->conteudo.ds_Produto), stdin);
        atual->conteudo.ds_Produto[strcspn(atual->conteudo.ds_Produto, "\n")] = '\0';

        gotoxy(3, 14);
        printf("Digite a nova unidade de medida...........: ");
        scanf("%s", atual->conteudo.ds_Unid_med);

        gotoxy(3, 15);
        printf("Digite a nova data de validade (DDMMAAAA).: ");
        scanf("%s", atual->conteudo.dt_Validade);

        atual->conteudo.vl_Total = atual->conteudo.qt_Produto * atual->conteudo.vl_Customedio;

        gotoxy(7, 23);
        printf("Produto editado com sucesso!");
    } else {
        gotoxy(7, 23);
        printf("Edicao cancelada pelo usuario.");
    }

    getch();
}

// Função para armazenar uma nova movimentação na lista duplamente encadeada
void armazenarMovimentacao(TipoLista_movim *lista_movimentacoes) {
    // Cria um novo item de movimentação
    TipoItem_movim *novo_item = (TipoItem_movim*)malloc(sizeof(TipoItem_movim));
    
    if (novo_item == NULL) {
        printf("Erro ao alocar memória para o novo item de movimentacao");
        return;
    }
    
    // Solicita ao usuário os dados da movimentação
    tela(); 
    gotoxy(3, 5);
    printf("Digite o codigo do produto..............: ");
    scanf("%d", &novo_item->conte_Movim.cd_Prod_Movim);
    while (getchar() != '\n');

    gotoxy(3, 6);
    printf("Digite a data da movimentacao (DDMMAAAA): ");
    scanf("%s", novo_item->conte_Movim.dt_Movim);
    while (getchar() != '\n');

    gotoxy(3, 7);
    printf("Digite o tipo da movimentacao...........: ");
    scanf(" %c", &novo_item->conte_Movim.tp_Movim);
    while (getchar() != '\n');

    gotoxy(3, 8);
    printf("Digite a quantidade da movimentacao.....: ");
    scanf("%f", &novo_item->conte_Movim.qt_Movim);
    while (getchar() != '\n');

    gotoxy(3, 9);
    printf("Digite o valor unitario da movimentacao.: ");
    scanf("%f", &novo_item->conte_Movim.vl_Unit_Movim);
    while (getchar() != '\n');

    gotoxy(3, 10);
    printf("Digite o valor total da movimentacao....: ");
    scanf("%f", &novo_item->conte_Movim.vl_Total_Movim);
    while (getchar() != '\n');

    novo_item->anterior_Movim = lista_movimentacoes->Ult_movim;
    novo_item->proximo_Movim = NULL;

    // Atualiza os ponteiros da lista para incluir o novo item
    if (lista_movimentacoes->Ult_movim == NULL) {
        lista_movimentacoes->Pri_movim = novo_item;
    } else {
        lista_movimentacoes->Ult_movim->proximo_Movim = novo_item;
    }
    
    lista_movimentacoes->Ult_movim = novo_item;
    
    gotoxy(7, 23);
    printf("Movimentacao registrada com sucesso!");
}

void ListarMovimentacoes(TipoLista_movim *lista_movimentacoes) {
    tela();
    int linha = 7;

    if (lista_movimentacoes == NULL) {
        gotoxy(7, 23);
        printf("Erro: Lista não inicializada.");
        return;
    }

    if (lista_movimentacoes->Pri_movim == NULL) {
        gotoxy(7, 23);
        printf("Nenhuma movimentacao cadastrada.");
        return;
    }

    gotoxy(2, 5);
    printf("Codigo     |    Dt Movim     |     Tipo  |     Qt  |    VUnitario |  Vtotal");
    gotoxy(1, 6);
    printf("+-----------------------------------------------------------------------------+");
    for (int l = 0; l < 15; l++) {
        gotoxy(1, 7 + l);
        printf("|           |                 |           |         |              |");
    } 

    TipoItem_movim *atual = lista_movimentacoes->Pri_movim; 
    while (atual != NULL) {  
        gotoxy(2, linha);
        printf("%d", atual->conte_Movim.cd_Prod_Movim);
        gotoxy(14, linha);
        printf("%s", atual->conte_Movim.dt_Movim);
        gotoxy(32, linha);
        printf("%c", atual->conte_Movim.tp_Movim);
        gotoxy(44, linha);
        printf("%.2f", atual->conte_Movim.qt_Movim); 
        gotoxy(54, linha);
        printf("%.2f", atual->conte_Movim.vl_Unit_Movim);
        gotoxy(69, linha);
        printf("%.2f", atual->conte_Movim.vl_Total_Movim);

        linha++;
        atual = atual->proximo_Movim; // Avança para a próxima movimentação na lista

        if (linha > 20) { 
            // Verifica se a linha ultrapassou o limite da tela
            gotoxy(7, 23);
            printf("Pressione enter para ir para a próxima pagina...");
            getch();
            tela();
            gotoxy(2, 5);
            printf("Codigo  |  Data Movimentacao  |  Tipo  |  Quantidade  |  Valor Unitario  |  Valor Total");
            gotoxy(1, 6);
            printf("+-----------------------------------------------------------------------------+");
            linha = 7;
             // Reinicia a contagem de linhas
        }
    }

    // Ajusta a posição para a mensagem de fim da lista
    gotoxy(7, 23); 
    printf("Fim da lista. Pressione qualquer tecla para sair...");
    getch();
}



void telaMenuCadProd(TipoLista_Prod *lista) {
    int opc2;

    do {
        tela();
        gotoxy(3, 5);
        printf("1 - Cadastrar Produto no Final da Lista");
        gotoxy(3, 6);
        printf("2 - Cadastrar Produto no Inicio da Lista");
        gotoxy(3, 7);
        printf("3 - Cadastrar Produto em Uma Posicao da Lista");
        gotoxy(3, 8);
        printf("4 - Remover Produto em Uma Posicao da Lista");
        gotoxy(3, 9);
        printf("5 - Remover Produto no final da Lista");
        gotoxy(3, 10);
        printf("6 - Remover Produto no Inicio da Lista ");
        gotoxy(3, 11);
        printf("7 - Consultar Todos os Produtos");
        gotoxy(3, 12);
        printf("8 - Alterar Dados de um Produto");
        gotoxy(3, 13);
        printf("9 - Retornar ao Menu Principal");

        gotoxy(7, 23);
        scanf("%d", &opc2);

        switch (opc2) {
            case 1:
                CadastrarProdutoNoFinal(lista);
                break;
            case 2:
                CadastrarProdutoNoInicio(lista);
                break;
            case 3:
                CadastrarProdutoNaPosicao(lista);
                break;
            case 4:
                RemoverProdutoNaPosicao(lista);
                break;
            case 5:
                RemoverProdutoNoFinal(lista);
                break;
            case 6:
                RemoverProdutoNoInicio(lista);
                break;
            case 7:
                ListarProdutos(lista);
                break;
            case 8:
                EditarProduto(lista);
                break;
            case 9:
                gotoxy(7, 23);
                printf("Retornando ao Menu Principal...");
                getch();
                return;
            default:
                gotoxy(7, 23);
                printf("Opcao Invalida. Tente Novamente.");
                break;
        }
    } while (opc2 != 9);
}

void telaMenuMovimentacao(TipoLista_movim *lista_movimentacoes) {
    int opc4;

    do {
        tela();  // Limpa a tela e posiciona o cursor no topo
        gotoxy(3, 5);
        printf("1 - Cadastrar Movimentacao de Estoque");
        gotoxy(3, 6);
        printf("2 - Lista de Movimentacao de Estoque");
        gotoxy(3, 7);
        printf("3 - Retornar ao Menu Principal");
        gotoxy(7, 23);
        scanf("%d", &opc4);

        switch (opc4) {
            case 1:
                armazenarMovimentacao(lista_movimentacoes);
                break;
            case 2:
                ListarMovimentacoes(lista_movimentacoes);
                break;
            case 3:
                gotoxy(7, 23);
                printf("Retornando ao Menu Principal...");
                getch();
                return;
            default:
                gotoxy(7, 23);
                printf("Opção Invalida. Tente Novamente.");
                break;
        }
    } while (opc4 != 3);
}



// Área de declaração sobre coisas relacionadas a produtos 

int main() {
    int opc;

    // Inicialização da lista de produtos
    TipoLista_Prod lista_produtos;
    lista_produtos.Pri_movim = NULL;
    lista_produtos.Ult_movim = NULL;

    TipoLista_movim lista_movimentacao;
    lista_movimentacao.Pri_movim = NULL;
    lista_movimentacao.Ult_movim = NULL;

    // Loop simples que irá manter o programa rodando
    do {
        tela();
        gotoxy(03, 5);
        printf("1 - Menu de cadastros");
        gotoxy(03, 6);
        printf("2 - Menu de Movimentacao de Estoque");
        gotoxy(03, 7);
        printf("3 - Finalizar o programa");
        gotoxy(07, 23);
        scanf("%d", &opc);

        switch (opc) {
            case 1:
                telaMenuCadProd(&lista_produtos);
                break;
            case 2:
                telaMenuMovimentacao(&lista_movimentacao);
                break;
            case 3:
                return 0;
                break;
            default:
                gotoxy(9, 23);
                printf("Opcao invalidada, pressione ''enter''e tente novamente.");
                getch();
                break;
        }
    } while (opc != 3);
}
