#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>

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

#define MAX 10;

typedef struct 
{
    int ID;
    float preco;
    char cd_barra[10];
    char dt_validade[11];
}registro_item;

int main () {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    printf("1 - Menu de cadastros");
    printf("2 - Menu de Movimentação de Estoque");
    printf("3 - Finalizar o programa");
    return 0;
}