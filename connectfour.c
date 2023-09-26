#include <stdio.h>
#include <stdlib.h>

#define LINHAS 6
#define COLUNAS 7

typedef struct no
{
    int coluna;
    struct no* prox;
} No;

typedef struct pilha
{
    No* topo;
} Pilha;

typedef struct connectfour 
{
    char tabuleiro[LINHAS][COLUNAS];
    Pilha* jogadas;
} ConnectFour;

Pilha* criaPilha() 
{
    Pilha* pilha = malloc(sizeof(Pilha));
    pilha->topo = NULL;
    return pilha;
}

void push(Pilha* pilha, int coluna) 
{
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->coluna = coluna;
    novoNo->prox = pilha->topo;
    pilha->topo = novoNo;
}

int pop(Pilha* pilha) 
{
    if (pilha->topo == NULL) 
    {
        printf("ERRO\n");
        return -99;
    }
    int coluna = pilha->topo->coluna;
    No* aux = pilha->topo;
    pilha->topo = pilha->topo->prox;
    free(aux);
    return coluna;
}

void liberaPilha(Pilha* pilha) 
{
    while (pilha->topo != NULL) 
    {
        pop(pilha);
    }
    free(pilha);
}

void inicializaJogo(ConnectFour* jogo) 
{
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) 
        {
            jogo->tabuleiro[i][j] = ' ';
        }
    }
}

void mostrarTabuleiro(ConnectFour* jogo)
{
    printf(" 1 2 3 4 5 6 7\n");
    for (int i = 0; i < LINHAS; i++) 
    {
        for (int j = 0; j < COLUNAS; j++) 
        {
            printf("|%c", jogo->tabuleiro[i][j]);
        }
        printf("|\n");
    }
}

int checarVitoria(ConnectFour* jogo, int linha, int coluna) 
{
    char jogadorAtual = jogo->tabuleiro[linha][coluna];

    int contador = 1;
    int j;

    for (j = coluna - 1; j >= 0 && jogo->tabuleiro[linha][j] == jogadorAtual; j--)
    {
        contador++;
    }
    for (j = coluna + 1; j < COLUNAS && jogo->tabuleiro[linha][j] == jogadorAtual; j++) 
    {
        contador++;
    }
    if (contador >= 4) 
    {
        printf("Parabéns jogador %c, você ganhou!\n", jogadorAtual);
        return -99;
    }
    
    contador = 1;
    int i;

    for (i = linha - 1; i >= 0 && jogo->tabuleiro[i][coluna] == jogadorAtual; i--) 
    {
        contador++;
    }
    for (i = linha + 1; i < LINHAS && jogo->tabuleiro[i][coluna] == jogadorAtual; i++) 
    {
        contador++;
    }
    if (contador >= 4) 
    {
        printf("Parabéns jogador %c, você ganhou!\n", jogadorAtual);
        return -99;
    }
    return 0;
}

int checarEmpate(ConnectFour* jogo) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) 
        {
            if (jogo->tabuleiro[i][j] == ' ') 
            {
                return 0;
            }
        }
    }

    printf("Deu empate!\n");
    return -99;
}

int main() {
    ConnectFour jogo;
    jogo.jogadas = criaPilha();
    inicializaJogo(&jogo);
    int jogadorAtual = 1;
    int gameOver = 0;
    int jogadasTotais = 0;

    while (!gameOver) {
        mostrarTabuleiro(&jogo);
        printf("Jogador %c, escolha coluna de 1 a 7: ", (jogadorAtual == 1) ? 'X' : '0');
        int coluna;
        scanf("%d", &coluna);
        coluna--; 

        if (coluna < 0 || coluna >= COLUNAS) 
        {
            printf("Coluna inválida.\n");
            continue;
        }

        if (jogo.tabuleiro[0][coluna] != ' ') 
        {
            printf("Coluna cheia.\n");
            continue;
        }

        int linha;
        for (linha = LINHAS - 1; linha >= 0; linha--) 
        {
            if (jogo.tabuleiro[linha][coluna] == ' ') 
            {
                jogo.tabuleiro[linha][coluna] = (jogadorAtual == 1) ? 'X' : 'O';
                push(jogo.jogadas, coluna);
                break;
            }
        }

        if (checarVitoria(&jogo, linha, coluna)) 
        {
            mostrarTabuleiro(&jogo);
            printf("Jogador %c ganhou!\n", (jogadorAtual == 1) ? 'X' : 'O');
            gameOver = 1;
        } else if (checarEmpate(&jogo)) {
            mostrarTabuleiro(&jogo);
            printf("Deu empate!\n");
            gameOver = 1;
        }

        jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
        jogadasTotais++;
    }

    liberaPilha(jogo.jogadas);
    return 0;
}
