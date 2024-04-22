#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Definindo a estrutura do nó da árvore
typedef struct Node {
    char data;
    struct Node *esquerda;
    struct Node *direita;
} Node;

// Função para criar um novo nó
Node* novoNo(char data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->esquerda = node->direita = NULL;
    return node;
}

// Variável global para armazenar a expressão
char expressao[100];
// Variável global para acompanhar a posição na expressão
int posicao = 0;

// Função para verificar se o caractere atual é um operador
int ehOperador(char op) {
    return (op == '+' || op == '-' || op == '*' || op == '/');
}

// Função para verificar se o caractere atual é um dígito
int ehDigito(char digito) {
    return isdigit(digito);
}

// Função para verificar se o caractere atual é um identificador
int ehIdentificador(char id) {
    return isalpha(id);
}

// Declarando a função para análise da expressão
Node* analisarExpressao();

// Função para analisar um fator
Node* analisarFator() {
    if (ehDigito(expressao[posicao]) || ehIdentificador(expressao[posicao])) {
        return novoNo(expressao[posicao++]);
    } else if (expressao[posicao] == '(') {
        posicao++;
        Node* expr = analisarExpressao();
        if (expressao[posicao] == ')') {
            posicao++;
            return expr;
        } else {
            printf("Erro: Esperado ')' na posição %d\n", posicao);
            exit(1);
        }
    } else {
        printf("Erro: Caractere inválido na posição %d\n", posicao);
        exit(1);
    }
}

// Função para analisar um termo
Node* analisarTermo() {
    Node* fator = analisarFator();
    while (expressao[posicao] == '*' || expressao[posicao] == '/') {
        char op = expressao[posicao++];
        Node* fator2 = analisarFator();
        Node* termoNode = novoNo(op);
        termoNode->esquerda = fator;
        termoNode->direita = fator2;
        fator = termoNode;
    }
    return fator;
}

// Função para analisar a expressão
Node* analisarExpressao() {
    Node* termo = analisarTermo();
    while (expressao[posicao] == '+' || expressao[posicao] == '-') {
        char op = expressao[posicao++];
        Node* termo2 = analisarTermo();
        Node* exprNode = novoNo(op);
        exprNode->esquerda = termo;
        exprNode->direita = termo2;
        termo = exprNode;
    }
    return termo;
}

// Função para imprimir a árvore
void imprimirArvore(Node* raiz, int nivel) {
    if (raiz != NULL) {
        imprimirArvore(raiz->direita, nivel + 1);
        for (int i = 0; i < nivel; i++) {
            printf("   ");
        }
        printf("%c\n", raiz->data);
        imprimirArvore(raiz->esquerda, nivel + 1);
    }
}

int main() {
    char continuar[10];
    do {
        // Lendo a expressão
        printf("Digite a expressao (ou 'sair' para encerrar): ");
        scanf("%s", expressao);

        if (strcmp(expressao, "sair") == 0) {
            break;
        }

        // Reiniciando a posição
        posicao = 0;

        // Analisando a expressão
        Node* raiz = analisarExpressao();

        // Verificando se a análise terminou corretamente
        if (expressao[posicao] == '\0') {
            printf("Expressao aceita!\n");
            printf("Lista de producoes:\n");
            // Impressão da árvore
            printf("Arvore de analise:\n");
            imprimirArvore(raiz, 0);
        } else {
            printf("Erro: Caractere inesperado na posição %d\n", posicao);
        }

    } while (1);

    return 0;
}
